// OfflineRestore.cpp: implementation of the COfflineRestore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OfflineRestore.h"
#include "CustomAttack.h"
#include "CustomStore.h"
#include "OfflineMode.h"
#include "PersonalShop.h"
#include "DSProtocol.h"
#include "JSProtocol.h"
#include "ServerInfo.h"
#include "GameMain.h"
#include "Util.h"

COfflineRestore gOfflineRestore;

#define OFFLINE_RESTORE_MAGIC 0x4F464652 // 'OFFR'
#define OFFLINE_RESTORE_VERSION 3
#define OFFLINE_RESTORE_XOR_KEY 0x5A

struct OFFLINE_RESTORE_HEADER
{
	DWORD Header;
	DWORD Version;
	DWORD Count;
};

COfflineRestore::COfflineRestore()
{
	this->m_Enabled = 1;
	this->m_Delay = 10;
	this->m_StartTick = 0;
	this->m_RestorationStarted = false;
	this->m_RestorationFinished = false;
	this->m_LastStepTick = 0;
	this->m_QueueIndex = 0;
	this->m_OfflineData.clear();
	this->m_RestoreQueue.clear();
	InitializeCriticalSection(&this->m_critical);
}

COfflineRestore::~COfflineRestore()
{
	DeleteCriticalSection(&this->m_critical);
}

void COfflineRestore::Init()
{
	this->m_StartTick = GetTickCount();
	this->m_RestorationStarted = false;
	this->m_RestorationFinished = false;
	this->m_LastStepTick = 0;
	this->m_QueueIndex = 0;
	this->m_RestoreQueue.clear();

	this->LoadData();
}

void COfflineRestore::ReadConfig(char* section, char* path)
{
	this->m_Enabled = GetPrivateProfileInt(section, "OfflineRestoreSwitch", 1, path);
	this->m_Delay = GetPrivateProfileInt(section, "OfflineRestoreDelay", 10, path);
}

static void XorCrypt(char* dest, const char* src, size_t len)
{
	for (size_t i = 0; i < len; ++i)
	{
		dest[i] = src[i] ^ OFFLINE_RESTORE_XOR_KEY;
	}
}

void COfflineRestore::LoadData()
{
	EnterCriticalSection(&this->m_critical);

	this->m_OfflineData.clear();

	char szPath[MAX_PATH];
	wsprintfA(szPath, ".\\Data\\OfflineRestore.dat");

	HANDLE hFile = CreateFileA(szPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		OFFLINE_RESTORE_HEADER header;
		DWORD dwRead = 0;

		if (ReadFile(hFile, &header, sizeof(header), &dwRead, NULL) && dwRead == sizeof(header))
		{
			if (header.Header == OFFLINE_RESTORE_MAGIC && header.Version == OFFLINE_RESTORE_VERSION)
			{
				for (DWORD i = 0; i < header.Count; ++i)
				{
					OFFLINE_RESTORE_DATA data;
					if (ReadFile(hFile, &data, sizeof(data), &dwRead, NULL) && dwRead == sizeof(data))
					{
						// Desencriptar password
						char plainPass[11] = { 0 };
						XorCrypt(plainPass, data.Password, sizeof(data.Password));
						memcpy(data.Password, plainPass, sizeof(data.Password));

						this->m_OfflineData[std::string(data.Account)] = data;
					}
				}
			}
		}

		CloseHandle(hFile);
	}

	LogAdd(LOG_BLUE, "[OfflineRestore] Loaded %d offline character(s) from persistence file", (int)this->m_OfflineData.size());

	LeaveCriticalSection(&this->m_critical);
}

void COfflineRestore::SaveData()
{
	char szPath[MAX_PATH];
	char szTemp[MAX_PATH];
	wsprintfA(szPath, ".\\Data\\OfflineRestore.dat");
	wsprintfA(szTemp, ".\\Data\\OfflineRestore.tmp");

	HANDLE hFile = CreateFileA(szTemp, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	OFFLINE_RESTORE_HEADER header;
	header.Header = OFFLINE_RESTORE_MAGIC;
	header.Version = OFFLINE_RESTORE_VERSION;
	header.Count = (DWORD)this->m_OfflineData.size();

	DWORD dwWritten = 0;
	WriteFile(hFile, &header, sizeof(header), &dwWritten, NULL);

	for (std::map<std::string, OFFLINE_RESTORE_DATA>::iterator it = this->m_OfflineData.begin(); it != this->m_OfflineData.end(); ++it)
	{
		OFFLINE_RESTORE_DATA data = it->second;

		// Encriptar password antes de escribir
		char cipherPass[11] = { 0 };
		XorCrypt(cipherPass, data.Password, sizeof(data.Password));
		memcpy(data.Password, cipherPass, sizeof(data.Password));

		WriteFile(hFile, &data, sizeof(data), &dwWritten, NULL);
	}

	CloseHandle(hFile);

	// Escritura atomica para proteger ante crashes mientras se escribe
	MoveFileExA(szTemp, szPath, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);
}

void COfflineRestore::SaveOffline(LPOBJ lpObj, int type)
{
	if (lpObj == 0 || lpObj->Connected < OBJECT_LOGGED)
	{
		return;
	}

	EnterCriticalSection(&this->m_critical);

	OFFLINE_RESTORE_DATA data;
	memset(&data, 0, sizeof(data));

	memcpy(data.Account, lpObj->Account, sizeof(data.Account));
	memcpy(data.Password, lpObj->Password, sizeof(data.Password));
	memcpy(data.Name, lpObj->Name, sizeof(data.Name));
	memcpy(data.IpAddr, lpObj->IpAddr, sizeof(data.IpAddr));
	memcpy(data.HardwareId, lpObj->HardwareId, sizeof(data.HardwareId));
	data.Type = (BYTE)type;
	data.Map = (BYTE)lpObj->Map;
	data.X = (BYTE)lpObj->X;
	data.Y = (BYTE)lpObj->Y;

	if (type == OFFLINE_RESTORE_ATTACK)
	{
		data.Skill = (WORD)lpObj->AttackCustomSkill;
		data.AutoBuff = (BYTE)lpObj->AttackCustomAutoBuff;
		data.DisablePvp = (BYTE)lpObj->DisablePvp;
		data.AutoReset = (BYTE)lpObj->AutoResetEnable;
		for (int i = 0; i < 5; ++i)
		{
			data.AutoResetStats[i] = lpObj->AutoResetStats[i];
		}
	}
	else if (type == OFFLINE_RESTORE_HELPER)
	{
		data.HuntingRange = (WORD)lpObj->HuntingRange;
		data.RecoveryPotionOn = lpObj->RecoveryPotionOn;
		data.RecoveryPotionPercent = lpObj->RecoveryPotionPercent;
		data.RecoveryHealOn = lpObj->RecoveryHealOn;
		data.RecoveryHealPercent = lpObj->RecoveryHealPercent;
		data.RecoveryDrainOn = lpObj->RecoveryDrainOn;
		data.RecoveryDrainPercent = lpObj->RecoveryDrainPercent;
		data.DistanceLongOn = lpObj->DistanceLongOn;
		data.DistanceReturnOn = lpObj->DistanceReturnOn;
		data.DistanceMin = lpObj->DistanceMin;
		data.SkillBasicID = (WORD)lpObj->SkillBasicID;
		data.SkillSecond1ID = (WORD)lpObj->SkillSecond1ID;
		data.SkillSecond2ID = (WORD)lpObj->SkillSecond2ID;
		data.ComboOn = lpObj->ComboOn;
		data.PartyModeOn = lpObj->PartyModeOn;
		data.PartyModeHealOn = lpObj->PartyModeHealOn;
		data.PartyModeHealPercent = lpObj->PartyModeHealPercent;
		data.PartyModeBuffOn = lpObj->PartyModeBuffOn;
		data.BuffOn = lpObj->BuffOn;
		data.BuffSkill[0] = lpObj->BuffSkill[0];
		data.BuffSkill[1] = lpObj->BuffSkill[1];
		data.BuffSkill[2] = lpObj->BuffSkill[2];
		data.ObtainRange = lpObj->ObtainRange;
		data.ObtainRepairOn = lpObj->ObtainRepairOn;
		data.ObtainPickNear = lpObj->ObtainPickNear;
		data.ObtainPickSelected = lpObj->ObtainPickSelected;
		data.ObtainPickJewels = lpObj->ObtainPickJewels;
		data.ObtainPickAncient = lpObj->ObtainPickAncient;
		data.ObtainPickMoney = lpObj->ObtainPickMoney;
		data.ObtainPickExcellent = lpObj->ObtainPickExcellent;
		data.ObtainPickExtra = lpObj->ObtainPickExtra;
		data.ObtainPickExtraCount = lpObj->ObtainPickExtraCount;
		for (int i = 0; i < lpObj->ObtainPickExtraCount && i < 12; ++i)
		{
			memcpy(data.ObtainPickItemList[i], lpObj->ObtainPickItemList[i], sizeof(lpObj->ObtainPickItemList[i]));
		}
	}
	else if (type == OFFLINE_RESTORE_STORE)
	{
		memcpy(data.StoreName, lpObj->PShopText, sizeof(data.StoreName));
		data.StoreType = (BYTE)lpObj->PShopCustomType;
	}

	this->m_OfflineData[std::string(lpObj->Account)] = data;

	this->SaveData();

	LeaveCriticalSection(&this->m_critical);

	LogAdd(LOG_BLUE, "[OfflineRestore] Saved [%s][%s] Type: %d (Map: %d, X: %d, Y: %d)",
		data.Account, data.Name, data.Type, data.Map, data.X, data.Y);
}

void COfflineRestore::RemoveOffline(char* account)
{
	if (account == 0 || account[0] == '\0')
	{
		return;
	}

	EnterCriticalSection(&this->m_critical);

	std::map<std::string, OFFLINE_RESTORE_DATA>::iterator it = this->m_OfflineData.find(std::string(account));

	if (it != this->m_OfflineData.end())
	{
		this->m_OfflineData.erase(it);
		this->SaveData();
		LogAdd(LOG_BLUE, "[OfflineRestore] Removed [%s] from persistence file", account);
	}

	LeaveCriticalSection(&this->m_critical);
}

bool COfflineRestore::GetOfflineData(char* account, OFFLINE_RESTORE_DATA* lpData)
{
	if (account == 0 || lpData == 0)
	{
		return false;
	}

	EnterCriticalSection(&this->m_critical);

	std::map<std::string, OFFLINE_RESTORE_DATA>::iterator it = this->m_OfflineData.find(std::string(account));

	bool found = false;

	if (it != this->m_OfflineData.end())
	{
		*lpData = it->second;
		found = true;
	}

	LeaveCriticalSection(&this->m_critical);

	return found;
}

void COfflineRestore::MainProc()
{
	if (this->m_Enabled == 0 || this->m_RestorationFinished)
	{
		return;
	}

	if (gJoinServerConnection.CheckState() == 0 || gDataServerConnection.CheckState() == 0)
	{
		return;
	}

	if ((GetTickCount() - this->m_StartTick) < (DWORD)(this->m_Delay * 1000))
	{
		return;
	}

	if (!this->m_RestorationStarted)
	{
		this->m_RestorationStarted = true;
		this->m_RestoreQueue.clear();
		this->m_QueueIndex = 0;

		EnterCriticalSection(&this->m_critical);

		for (std::map<std::string, OFFLINE_RESTORE_DATA>::iterator it = this->m_OfflineData.begin(); it != this->m_OfflineData.end(); ++it)
		{
			this->m_RestoreQueue.push_back(it->first);
		}

		LeaveCriticalSection(&this->m_critical);

		LogAdd(LOG_BLUE, "[OfflineRestore] Starting auto-reconnection of %d character(s)...", (int)this->m_RestoreQueue.size());

		if (this->m_RestoreQueue.empty())
		{
			this->m_RestorationFinished = true;
			return;
		}
	}

	// Throttle: reconnect 1 account every 400ms to maintain stability
	if ((GetTickCount() - this->m_LastStepTick) < 400)
	{
		return;
	}

	this->m_LastStepTick = GetTickCount();

	while (this->m_QueueIndex < this->m_RestoreQueue.size())
	{
		std::string acc = this->m_RestoreQueue[this->m_QueueIndex++];

		OFFLINE_RESTORE_DATA data;
		if (!this->GetOfflineData((char*)acc.c_str(), &data))
		{
			continue;
		}

		if (gObjFindByAcc(data.Account) != 0)
		{
			LogAdd(LOG_BLUE, "[OfflineRestore] Account [%s] already online, skipping", data.Account);
			continue;
		}

		const char* restoreIp = (data.IpAddr[0] != '\0') ? data.IpAddr : "127.0.0.1";

		int aIndex = gObjAddSearch(0, (char*)restoreIp);

		if (aIndex < 0)
		{
			LogAdd(LOG_RED, "[OfflineRestore] Max users reached. Halting restore process.");
			this->m_RestorationFinished = true;
			return;
		}

		gObjAdd(0, (char*)restoreIp, aIndex);

		LPOBJ lpObj = &gObj[aIndex];

		lpObj->LoginMessageSend++;
		lpObj->LoginMessageCount++;
		lpObj->ConnectTickCount = GetTickCount();
		lpObj->ClientTickCount = GetTickCount();
		lpObj->ServerTickCount = GetTickCount();

		lpObj->MapServerMoveRequest = 0;
		lpObj->LastServerCode = -1;
		lpObj->DestMap = -1;
		lpObj->DestX = 0;
		lpObj->DestY = 0;

		lpObj->Socket = INVALID_SOCKET;
		lpObj->m_OfflineRestoreType = data.Type;
		memcpy(lpObj->Account, data.Account, sizeof(lpObj->Account));
		memcpy(lpObj->Password, data.Password, sizeof(lpObj->Password));
		memcpy(lpObj->m_OfflineRestoreName, data.Name, sizeof(lpObj->m_OfflineRestoreName));
		memcpy(lpObj->HardwareId, data.HardwareId, sizeof(lpObj->HardwareId));

		char account[11] = { 0 };
		char password[11] = { 0 };
		memcpy(account, data.Account, sizeof(account) - 1);
		memcpy(password, data.Password, sizeof(password) - 1);

		GJConnectAccountSend(aIndex, account, password, (char*)restoreIp);

		LogAdd(LOG_BLUE, "[OfflineRestore] Restoring [%s][%s] Type: %d (Slot: %d, IP: %s, PassLen: %d)",
			data.Account, data.Name, data.Type, aIndex, restoreIp, (int)strlen(password));

		return; // Process next character in next tick
	}

	this->m_RestorationFinished = true;
	LogAdd(LOG_BLUE, "[OfflineRestore] Auto-reconnection process finished successfully.");
}

void COfflineRestore::OnCharacterInfoRecv(LPOBJ lpObj)
{
	if (lpObj == 0 || lpObj->m_OfflineRestoreType == OFFLINE_RESTORE_NONE)
	{
		return;
	}

	OFFLINE_RESTORE_DATA data;
	if (!this->GetOfflineData(lpObj->Account, &data))
	{
		lpObj->m_OfflineRestoreType = OFFLINE_RESTORE_NONE;
		return;
	}

	// Restaurar ubicacion si el mapa coincide y las coordenadas difieren
	if (lpObj->Map == data.Map && (lpObj->X != data.X || lpObj->Y != data.Y))
	{
		gObjTeleport(lpObj->Index, data.Map, data.X, data.Y);
	}

	int restoreType = lpObj->m_OfflineRestoreType;
	lpObj->m_OfflineRestoreType = OFFLINE_RESTORE_NONE;

	if (restoreType == OFFLINE_RESTORE_ATTACK)
	{
		lpObj->AttackCustom = 1;
		lpObj->AttackCustomOffline = 1;
		lpObj->AttackCustomOfflineTime = 0;
		lpObj->AttackCustomSkill = data.Skill;
		lpObj->AttackCustomDelay = GetTickCount();
		lpObj->AttackCustomZoneX = data.X;
		lpObj->AttackCustomZoneY = data.Y;
		lpObj->AttackCustomZoneMap = data.Map;
		lpObj->AttackCustomAutoBuff = data.AutoBuff;
		lpObj->DisablePvp = data.DisablePvp;
		lpObj->AutoResetEnable = data.AutoReset;
		for (int i = 0; i < 5; ++i)
		{
			lpObj->AutoResetStats[i] = data.AutoResetStats[i];
		}

		LogAdd(LOG_BLUE, "[OfflineRestore] Restored OffAttack for [%s][%s]", lpObj->Account, lpObj->Name);
	}
	else if (restoreType == OFFLINE_RESTORE_HELPER)
	{
		lpObj->m_OfflineMode = 1;
		lpObj->HuntingRange = data.HuntingRange;
		lpObj->RecoveryPotionOn = data.RecoveryPotionOn;
		lpObj->RecoveryPotionPercent = data.RecoveryPotionPercent;
		lpObj->RecoveryHealOn = data.RecoveryHealOn;
		lpObj->RecoveryHealPercent = data.RecoveryHealPercent;
		lpObj->RecoveryDrainOn = data.RecoveryDrainOn;
		lpObj->RecoveryDrainPercent = data.RecoveryDrainPercent;
		lpObj->DistanceLongOn = data.DistanceLongOn;
		lpObj->DistanceReturnOn = data.DistanceReturnOn;
		lpObj->DistanceMin = data.DistanceMin;
		lpObj->SkillBasicID = data.SkillBasicID;
		lpObj->SkillSecond1ID = data.SkillSecond1ID;
		lpObj->SkillSecond2ID = data.SkillSecond2ID;
		lpObj->OfflineComboStep = 0;
		lpObj->ComboOn = data.ComboOn;
		lpObj->PartyModeOn = data.PartyModeOn;
		lpObj->PartyModeHealOn = data.PartyModeHealOn;
		lpObj->PartyModeHealPercent = data.PartyModeHealPercent;
		lpObj->PartyModeBuffOn = data.PartyModeBuffOn;
		lpObj->BuffOn = data.BuffOn;
		lpObj->BuffSkill[0] = data.BuffSkill[0];
		lpObj->BuffSkill[1] = data.BuffSkill[1];
		lpObj->BuffSkill[2] = data.BuffSkill[2];
		lpObj->ObtainRange = data.ObtainRange;
		lpObj->ObtainRepairOn = data.ObtainRepairOn;
		lpObj->ObtainPickNear = data.ObtainPickNear;
		lpObj->ObtainPickSelected = data.ObtainPickSelected;
		lpObj->ObtainPickJewels = data.ObtainPickJewels;
		lpObj->ObtainPickAncient = data.ObtainPickAncient;
		lpObj->ObtainPickMoney = data.ObtainPickMoney;
		lpObj->ObtainPickExcellent = data.ObtainPickExcellent;
		lpObj->ObtainPickExtra = data.ObtainPickExtra;
		lpObj->ObtainPickExtraCount = data.ObtainPickExtraCount;
		for (int i = 0; i < data.ObtainPickExtraCount && i < 12; ++i)
		{
			memcpy(lpObj->ObtainPickItemList[i], data.ObtainPickItemList[i], sizeof(lpObj->ObtainPickItemList[i]));
		}

		lpObj->m_OfflineCoordX = data.X;
		lpObj->m_OfflineCoordY = data.Y;
		lpObj->m_OfflineTimeResetMove = GetTickCount();
		lpObj->AttackCustomDelay = GetTickCount();
		lpObj->MuOffHelperTime = g_OfflineMode.m_MUOffHelperTimer[lpObj->AccountLevel] * 600;

		LogAdd(LOG_BLUE, "[OfflineRestore] Restored OffHelper for [%s][%s]", lpObj->Account, lpObj->Name);
	}
	else if (restoreType == OFFLINE_RESTORE_STORE)
	{
		lpObj->PShopOpen = 1;
		lpObj->PShopCustom = 1;
		lpObj->PShopCustomType = data.StoreType;
		lpObj->PShopCustomOffline = 1;
		lpObj->PShopCustomOfflineTime = 0;
		lpObj->PShopCustomTime = gCustomStore.m_CustomStoreTime[lpObj->AccountLevel] * 60;
		memcpy(lpObj->PShopText, data.StoreName, sizeof(lpObj->PShopText));

		gPersonalShop.GCPShopOpenSend(lpObj->Index, 1);
		gPersonalShop.GCPShopTextChangeSend(lpObj->Index);

		LogAdd(LOG_BLUE, "[OfflineRestore] Restored OffStore for [%s][%s]", lpObj->Account, lpObj->Name);
	}
}
