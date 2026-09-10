// OfflineMode.cpp: implementacion del sistema Offline Mu Helper
// Basado en el proyecto de referencia Fonte-Legendary-Pyke-main
// Adaptado al proyecto S6 Legacy (LEGADO-4.3) con PickUP corregido

#include "StdAfx.h"
#include "OfflineMode.h"
#include "OfflineRestore.h"
#include "User.h"
#include "GameMain.h"
#include "Message.h"
#include "MapManager.h"
#include "Util.h"
#include "Notice.h"
#include "Map.h"
#include "SkillManager.h"
#include "Party.h"
#include "CustomAttack.h"
#include "ServerInfo.h"
#include "ObjectManager.h"
#include "Viewport.h"
#include "EffectManager.h"
#include "ItemManager.h"
#include "MapServerManager.h"
#include "ItemLevel.h"
#include "Log.h"

OfflineMode g_OfflineMode;

OfflineMode::OfflineMode()
{
	this->m_bLoadedDB = false;

	for(int n = 0; n < MAX_CLASS; n++)
	{
		this->m_MUOffHelperAttackDelay[n] = 1000;
		this->m_MUOffHelperMinDelay[n] = 500;
	}
}
// ----------------------------------------------------------------------------------------------

OfflineMode::~OfflineMode()
{
}

void OfflineMode::ReadOffLine(char* section, char* path)
{
	this->m_MUOffHelperEnabled[0] = GetPrivateProfileInt(section, "MuOffHelperEnabled_AL0", 1, path);
	this->m_MUOffHelperEnabled[1] = GetPrivateProfileInt(section, "MuOffHelperEnabled_AL1", 1, path);
	this->m_MUOffHelperEnabled[2] = GetPrivateProfileInt(section, "MuOffHelperEnabled_AL2", 1, path);
	this->m_MUOffHelperEnabled[3] = GetPrivateProfileInt(section, "MuOffHelperEnabled_AL3", 1, path);
	this->m_MUOffHelperTimer[0] = GetPrivateProfileInt(section, "MuOffHelperTime_AL0", -1, path);
	this->m_MUOffHelperTimer[1] = GetPrivateProfileInt(section, "MuOffHelperTime_AL1", -1, path);
	this->m_MUOffHelperTimer[2] = GetPrivateProfileInt(section, "MuOffHelperTime_AL2", -1, path);
	this->m_MUOffHelperTimer[3] = GetPrivateProfileInt(section, "MuOffHelperTime_AL3", -1, path);

	int globalBaseDelay = GetPrivateProfileInt(section, "MuOffHelperAttackDelay", 1000, path);
	int globalMinDelay = GetPrivateProfileInt(section, "MuOffHelperMinDelay", 500, path);

	const char* classNames[MAX_CLASS] = { "DW", "DK", "FE", "MG", "DL", "SU", "RF" };

	for(int n = 0; n < MAX_CLASS; n++)
	{
		char keyBase[64], keyMin[64];
		wsprintf(keyBase, "MuOffHelperAttackDelay_%s", classNames[n]);
		wsprintf(keyMin, "MuOffHelperMinDelay_%s", classNames[n]);

		this->m_MUOffHelperAttackDelay[n] = GetPrivateProfileInt(section, keyBase, globalBaseDelay, path);
		this->m_MUOffHelperMinDelay[n] = GetPrivateProfileInt(section, keyMin, globalMinDelay, path);
	}

	LogAdd(LOG_RED, "[OfflineMode] ReadOffLine -> AL0:%d(%dmin) AL1:%d(%dmin) AL2:%d(%dmin) AL3:%d(%dmin)",
		m_MUOffHelperEnabled[0], m_MUOffHelperTimer[0],
		m_MUOffHelperEnabled[1], m_MUOffHelperTimer[1],
		m_MUOffHelperEnabled[2], m_MUOffHelperTimer[2],
		m_MUOffHelperEnabled[3], m_MUOffHelperTimer[3]);

	LogAdd(LOG_BLUE, "[OfflineMode] Delays -> DW:%d/%d DK:%d/%d FE:%d/%d MG:%d/%d DL:%d/%d SU:%d/%d RF:%d/%d",
		this->m_MUOffHelperAttackDelay[CLASS_DW], this->m_MUOffHelperMinDelay[CLASS_DW],
		this->m_MUOffHelperAttackDelay[CLASS_DK], this->m_MUOffHelperMinDelay[CLASS_DK],
		this->m_MUOffHelperAttackDelay[CLASS_FE], this->m_MUOffHelperMinDelay[CLASS_FE],
		this->m_MUOffHelperAttackDelay[CLASS_MG], this->m_MUOffHelperMinDelay[CLASS_MG],
		this->m_MUOffHelperAttackDelay[CLASS_DL], this->m_MUOffHelperMinDelay[CLASS_DL],
		this->m_MUOffHelperAttackDelay[CLASS_SU], this->m_MUOffHelperMinDelay[CLASS_SU],
		this->m_MUOffHelperAttackDelay[CLASS_RF], this->m_MUOffHelperMinDelay[CLASS_RF]);
}

void OfflineMode::OnHelperpAlreadyConnected(LPOBJ lpObj) // OK
{
	if(lpObj->m_OfflineMode != 0)
	{
		gObjDel(lpObj->Index);
		lpObj->m_OfflineMode = 0;
		lpObj->MuOffHelperTime = 0;
	}
}

bool gObjIsOfflineAccount(char* account, char* HardwareId)
{
	if (account == 0 || account[0] == '\0')
	{
		return false;
	}

	for (int i = OBJECT_START_USER; i < MAX_OBJECT; i++)
	{
		if (gObj[i].Connected >= OBJECT_CONNECTED)
		{
			if (gObj[i].m_OfflineMode != 0 || gObj[i].AttackCustomOffline != 0 || gObj[i].PShopCustomOffline != 0)
			{
				if (strncmp(account, gObj[i].Account, 10) == 0)
				{
					if (HardwareId != 0 && HardwareId[0] != '\0')
					{
						if (strcmp(gObj[i].HardwareId, HardwareId) == 0)
						{
							return true;
						}
					}
					else
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

void OfflineMode::Start(CG_OFFMODE_RESULT* aRecv, int aIndex)
{
	if (!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(gMapManager.GetMapHelperEnable(lpObj->Map) == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, "[Helper] Disable in this map");
		return;
	}

	if(this->m_MUOffHelperEnabled[lpObj->AccountLevel] == 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(64));
		return;
	}

	// Bloquear en mapas de eventos
	switch(lpObj->Map)
	{
	case MAP_CASTLE_SIEGE:
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "[OfflineMode] Disable in Castle Siege map");
		return;
	case MAP_CRYWOLF:
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "[OfflineMode] Disable in Crywolf map");
		return;
	}

	// Copiar la configuracion del Helper enviada por el cliente
	/*+172*/lpObj->HuntingRange = aRecv->HuntingRange;
	//--
	lpObj->RecoveryPotionOn = aRecv->RecoveryPotionOn;
	lpObj->RecoveryPotionPercent = aRecv->RecoveryPotionPercent;
	lpObj->RecoveryHealOn = (lpObj->Class == CLASS_FE) ? aRecv->RecoveryHealOn : 0;
	lpObj->RecoveryHealPercent = (lpObj->Class == CLASS_FE) ? aRecv->RecoveryHealPercent : 0;
	lpObj->RecoveryDrainOn = (lpObj->Class == CLASS_SU) ? aRecv->RecoveryDrainOn : 0;
	lpObj->RecoveryDrainPercent = (lpObj->Class == CLASS_SU) ? aRecv->RecoveryDrainPercent : 0;
	//--
	lpObj->DistanceLongOn = aRecv->DistanceLongOn;
	lpObj->DistanceReturnOn = aRecv->DistanceReturnOn;
	lpObj->DistanceMin = aRecv->DistanceMin;
	lpObj->SkillBasicID = aRecv->SkillBasicID;
	lpObj->SkillSecond1ID = aRecv->SkillSecond1ID;
	lpObj->SkillSecond2ID = aRecv->SkillSecond2ID;
	lpObj->OfflineComboStep = 0;
	lpObj->ComboOn = (lpObj->Class == CLASS_DK) ? aRecv->ComboOn : 0;
	//--
	lpObj->PartyModeOn = aRecv->PartyModeOn;
	lpObj->PartyModeHealOn = (lpObj->Class == CLASS_FE) ? aRecv->PartyModeHealOn : 0;
	lpObj->PartyModeHealPercent = (lpObj->Class == CLASS_FE) ? aRecv->PartyModeHealPercent : 0;
	lpObj->PartyModeBuffOn = aRecv->PartyModeBuffOn;
	//--
	lpObj->BuffOn = aRecv->BuffOn;
	lpObj->BuffSkill[0] = aRecv->BuffSkill[0];
	lpObj->BuffSkill[1] = aRecv->BuffSkill[1];
	lpObj->BuffSkill[2] = aRecv->BuffSkill[2];
	lpObj->ObtainRange = (DWORD)aRecv->ObtainRange;
	lpObj->ObtainRepairOn = aRecv->ObtainRepairOn;
	lpObj->ObtainPickNear = (aRecv->ObtainPickNear != 0) ? 1 : 0;
	lpObj->ObtainPickSelected = aRecv->ObtainPickSelected;
	lpObj->ObtainPickJewels = (aRecv->ObtainPickJewels != 0) ? 1 : 0;
	lpObj->ObtainPickAncient = (aRecv->ObtainPickAncient != 0) ? 1 : 0;
	lpObj->ObtainPickMoney = (aRecv->ObtainPickMoney != 0) ? 1 : 0;
	lpObj->ObtainPickExcellent = (aRecv->ObtainPickExcellent != 0) ? 1 : 0;
	lpObj->ObtainPickExtra = (aRecv->ObtainPickExtra != 0) ? 1 : 0;
	lpObj->ObtainPickExtraCount = aRecv->ObtainPickExtraCount;

	for(int i = 0; i < lpObj->ObtainPickExtraCount; ++i)
	{
		memcpy(lpObj->ObtainPickItemList[i], aRecv->ObtainPickItemList[i], sizeof(lpObj->ObtainPickItemList[i]));
	}

	// Guardar posicion de inicio y configurar modo offline
	lpObj->m_OfflineCoordX = lpObj->X;
	lpObj->m_OfflineCoordY = lpObj->Y;
	lpObj->m_OfflineTimeResetMove = GetTickCount();
	lpObj->AttackCustomDelay = GetTickCount();
	lpObj->MuOffHelperTime = this->m_MUOffHelperTimer[lpObj->AccountLevel] * 600;
	lpObj->m_OfflineSocket = true;
	CloseClient(aIndex);
	lpObj->m_OfflineSocket = false;
	lpObj->m_OfflineMode = 1;
	gOfflineRestore.SaveOffline(lpObj, OFFLINE_RESTORE_HELPER);
}

void OfflineMode::OnAttackSecondProcHelper(LPOBJ lpObj) // OK
{
	if(lpObj->m_OfflineMode != 0)
	{
		lpObj->CheckSumTime = GetTickCount();
		lpObj->ConnectTickCount = GetTickCount();
		// Evitar que los sistemas de recompensa online se apliquen cuando esta offline
		lpObj->OnlineRewardCoin1 = ((gServerInfo.m_OnlineRewardOfflineSystems == 0) ? GetTickCount() : lpObj->OnlineRewardCoin1);
		lpObj->OnlineRewardCoin2 = ((gServerInfo.m_OnlineRewardOfflineSystems == 0) ? GetTickCount() : lpObj->OnlineRewardCoin2);
		lpObj->OnlineRewardCoin3 = ((gServerInfo.m_OnlineRewardOfflineSystems == 0) ? GetTickCount() : lpObj->OnlineRewardCoin3);
	}
}

// Funcion auxiliar: reparar equipamiento automaticamente
static void MuOffHelperRepair(int aIndex)
{
	if (!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	for(int n = 0; n < INVENTORY_WEAR_SIZE; ++n)
	{
		if(lpObj->Inventory[n].IsItem() != 0)
		{
			int money = gItemManager.RepairItem(lpObj, &lpObj->Inventory[n], n, 1);

			if(money != 0)
			{
				gObjectManager.CharacterCalcAttribute(aIndex);
			}
		}
	}
}

// Funcion auxiliar: movimiento simulado para recoger items o perseguir monstruos
static void AnimationMove(int aIndex, int x, int y)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->Teleport != 0)
	{
		return;
	}

	if(gObjCheckMapTile(lpObj, 1) != 0)
	{
		return;
	}

	if((GetTickCount() - lpObj->LastMoveTime) < 100)
	{
		return;
	}

	if(gEffectManager.CheckStunEffect(lpObj) != 0 || gEffectManager.CheckImmobilizeEffect(lpObj) != 0)
	{
		return;
	}

	if(lpObj->SkillSummonPartyTime != 0)
	{
		lpObj->SkillSummonPartyTime = 0;
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(272));
	}

	lpObj->Dir = 0;
	lpObj->Rest = 0;
	lpObj->PathCur = 0;
	lpObj->PathCount = 0;
	lpObj->LastMoveTime = GetTickCount();

	memset(lpObj->PathX, 0, sizeof(lpObj->PathX));
	memset(lpObj->PathY, 0, sizeof(lpObj->PathY));
	memset(lpObj->PathOri, 0, sizeof(lpObj->PathOri));

	lpObj->TX = x;
	lpObj->TY = y;
	lpObj->PathCur = 0;
	lpObj->PathCount = 0;
	lpObj->PathStartEnd = 1;
	lpObj->PathX[0] = x;
	lpObj->PathY[0] = y;
	lpObj->PathDir[0] = lpObj->Dir;
	lpObj->X = x;
	lpObj->Y = y;
	lpObj->TX = x;
	lpObj->TY = y;
	lpObj->OldX = x;
	lpObj->OldY = y;
	lpObj->ViewState = 0;

	gMap[lpObj->Map].SetStandAttr(lpObj->TX, lpObj->TY);

	PMSG_MOVE_SEND pMsg;

	pMsg.header.set(PROTOCOL_CODE1, sizeof(pMsg));
	pMsg.index[0] = SET_NUMBERHB(lpObj->Index);
	pMsg.index[1] = SET_NUMBERLB(lpObj->Index);
	pMsg.x = (BYTE)lpObj->TX;
	pMsg.y = (BYTE)lpObj->TY;
	pMsg.dir = lpObj->Dir << 4;

	for(int n = 0; n < MAX_VIEWPORT; n++)
	{
		if(lpObj->VpPlayer2[n].type == OBJECT_USER)
		{
			if(lpObj->VpPlayer2[n].state != OBJECT_EMPTY && lpObj->VpPlayer2[n].state != OBJECT_DIECMD && lpObj->VpPlayer2[n].state != OBJECT_DIED)
			{
				DataSend(lpObj->VpPlayer2[n].index, (BYTE*)&pMsg, pMsg.header.size);
			}
		}
	}
}

void OfflineMode::Attack(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == FALSE)
	{
		return;
	}

	if(!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_OfflineMode == 0)
	{
		return;
	}

	// Si el personaje esta en zona segura, terminar modo offline
	if(gServerInfo.InSafeZone(aIndex) == true)
	{
		this->OnHelperpAlreadyConnected(lpObj);
		return;
	}

	// Contar el tiempo y desconectar si expiro
	if(lpObj->MuOffHelperTime > 0)
	{
		if((--lpObj->MuOffHelperTime) == 0)
		{
			gObjDel(lpObj->Index);
			lpObj->m_OfflineMode = 0;
			lpObj->MuOffHelperTime = 0;
		}
	}

	this->RenderAutoPote(aIndex);

	this->RenderAutoBuffParty(aIndex);

	this->RenderAttack(aIndex);

	// Reparar si esta activado
	if(lpObj->ObtainRepairOn != 0)
	{
		MuOffHelperRepair(aIndex);
	}
}

void OfflineMode::RenderAutoPote(int aIndex) // OK
{
	if(!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	// AUTO POTION HP
	if(lpObj->RecoveryPotionOn != 0)
	{
		if(lpObj->Life > 0 && lpObj->Life < ((lpObj->MaxLife * lpObj->RecoveryPotionPercent) / 100))
		{
			PMSG_ITEM_USE_RECV pMsg;

			pMsg.header.set(0x26, sizeof(pMsg));

			pMsg.SourceSlot = 0xFF;

			pMsg.SourceSlot = ((pMsg.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 3), -1) : pMsg.SourceSlot);
			pMsg.SourceSlot = ((pMsg.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 2), -1) : pMsg.SourceSlot);
			pMsg.SourceSlot = ((pMsg.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 1), -1) : pMsg.SourceSlot);

			pMsg.TargetSlot = 0xFF;
			pMsg.type = 0;

			if(INVENTORY_FULL_RANGE(pMsg.SourceSlot) != 0)
			{
				gItemManager.CGItemUseRecv(&pMsg, lpObj->Index);
			}
		}
	}

	// RECOVERY HEALING ELF
	if(lpObj->RecoveryHealOn != 0 && lpObj->Class == CLASS_FE)
	{
		CSkill* RenderSkillHealing = gSkillManager.GetSkill(lpObj, SKILL_HEAL);

		if(RenderSkillHealing != 0)
		{
			if(lpObj->Life > 0 && lpObj->Life < ((lpObj->MaxLife * lpObj->RecoveryHealPercent) / 100))
			{
				gSkillManager.UseAttackSkill(lpObj->Index, lpObj->Index, RenderSkillHealing);
			}
		}
	}
}

void OfflineMode::RenderAutoBuffParty(int aIndex) // OK
{
	if(!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	// AUTOBUFF PROPIO
	if(lpObj->BuffOn != 0)
	{
		for(int n = 0; n < 3; n++)
		{
			if(lpObj->BuffSkill[n] > 0)
			{
				CSkill* RenderBuff = gSkillManager.GetSkill(lpObj, lpObj->BuffSkill[n]);

				if(RenderBuff != 0)
				{
					int effect = gSkillManager.GetSkillEffect(RenderBuff->m_index);

					if(effect != -1 && gEffectManager.CheckEffect(lpObj, effect) == 0)
					{
						gSkillManager.UseAttackSkill(lpObj->Index, lpObj->Index, RenderBuff);
					}
				}
			}
		}
	}

	// MODO PARTY ON: solo si PartyModeOn esta activo y el personaje esta efectivamente en un party valido
	if(lpObj->PartyModeOn != 0 && gParty.IsParty(lpObj->PartyNumber) != 0)
	{
		// PARTY HEAL ELF
		if(lpObj->PartyModeHealOn != 0 && lpObj->Class == CLASS_FE)
		{
			CSkill* RenderPartyHealing = gSkillManager.GetSkill(lpObj, SKILL_HEAL);

			if(RenderPartyHealing != 0)
			{
				for(int i = 0; i < MAX_PARTY_USER; i++)
				{
					int memberIndex = gParty.m_PartyInfo[lpObj->PartyNumber].Index[i];

					if(OBJECT_RANGE(memberIndex) == 0 || memberIndex == lpObj->Index)
					{
						continue;
					}

					if(gObjIsConnectedGP(memberIndex) == 0)
					{
						continue;
					}

					LPOBJ lpTarget = &gObj[memberIndex];

					if(lpTarget->Live == 0 || lpTarget->State != OBJECT_PLAYING)
					{
						continue;
					}

					if(lpTarget->Map != lpObj->Map)
					{
						continue;
					}

					if(gObjCalcDistance(lpObj, lpTarget) > MAX_PARTY_DISTANCE)
					{
						continue;
					}

					if(gSkillManager.CheckSkillRange(RenderPartyHealing->m_index, lpObj->X, lpObj->Y, lpTarget->X, lpTarget->Y) == 0)
					{
						continue;
					}

					if(lpTarget->Life > 0 && lpTarget->Life < ((lpTarget->MaxLife * lpObj->PartyModeHealPercent) / 100))
					{
						gSkillManager.UseAttackSkill(lpObj->Index, lpTarget->Index, RenderPartyHealing);
						break;
					}
				}
			}
		}

		// PARTY BUFF
		if(lpObj->PartyModeBuffOn != 0)
		{
			for(int i = 0; i < MAX_PARTY_USER; i++)
			{
				int memberIndex = gParty.m_PartyInfo[lpObj->PartyNumber].Index[i];

				if(OBJECT_RANGE(memberIndex) == 0 || memberIndex == lpObj->Index)
				{
					continue;
				}

				if(gObjIsConnectedGP(memberIndex) == 0)
				{
					continue;
				}

				LPOBJ lpTarget = &gObj[memberIndex];

				if(lpTarget->Live == 0 || lpTarget->State != OBJECT_PLAYING)
				{
					continue;
				}

				if(lpTarget->Map != lpObj->Map)
				{
					continue;
				}

				if(gObjCalcDistance(lpObj, lpTarget) > MAX_PARTY_DISTANCE)
				{
					continue;
				}

				for(int n = 0; n < 3; n++)
				{
					if(lpObj->BuffSkill[n] > 0)
					{
						CSkill* RenderPartyBuff = gSkillManager.GetSkill(lpObj, lpObj->BuffSkill[n]);

						if(RenderPartyBuff != 0)
						{
							int effect = gSkillManager.GetSkillEffect(RenderPartyBuff->m_index);

							if(effect != -1 && gEffectManager.CheckEffect(lpTarget, effect) == 0)
							{
								if(gSkillManager.CheckSkillRange(RenderPartyBuff->m_index, lpObj->X, lpObj->Y, lpTarget->X, lpTarget->Y) != 0)
								{
									gSkillManager.UseAttackSkill(lpObj->Index, lpTarget->Index, RenderPartyBuff);
								}
							}
						}
					}
				}
			}
		}
	}
}

void OfflineMode::RenderAttack(int aIndex)
{
	if(!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];
	int caminar = 0;
	int distance = (lpObj->HuntingRange > 0) ? lpObj->HuntingRange : 6;

	CSkill* SkillRender = 0;

	// Seleccionar skill: si es Summoner con drain y tiene poca vida, usar drain
	if(lpObj->Life < ((lpObj->MaxLife * lpObj->RecoveryDrainPercent) / 100) && lpObj->RecoveryDrainOn != 0)
	{
		SkillRender = gSkillManager.GetSkill(lpObj, SKILL_DRAIN_LIFE);
	}
	else if(lpObj->Class == CLASS_DK && lpObj->ComboOn != 0)
	{
		// Si expiro la ventana de combo (3 seg), reiniciar al primer paso para sincronizar con skill tipo 0
		if(lpObj->ComboSkill.m_time < GetTickCount())
		{
			lpObj->OfflineComboStep = 0;
		}

		WORD skillIds[3] = { (WORD)lpObj->SkillBasicID, (WORD)lpObj->SkillSecond1ID, (WORD)lpObj->SkillSecond2ID };

		// Intentar formar secuencia de combo: [0] = Tipo 0 (Arma), [1] = Tipo 1 A, [2] = Tipo 1 B
		CSkill* comboSkills[3] = { 0, 0, 0 };

		for(int i = 0; i < 3; i++)
		{
			if(skillIds[i] > 0 && skillIds[i] != 0xFFFF)
			{
				CSkill* lpSkill = gSkillManager.GetSkill(lpObj, skillIds[i]);
				if(lpSkill != 0)
				{
					int type = lpObj->ComboSkill.GetSkillType(lpSkill->m_skill);
					if(type == 0 && comboSkills[0] == 0)
					{
						comboSkills[0] = lpSkill;
					}
					else if(type == 1)
					{
						if(comboSkills[1] == 0)
						{
							comboSkills[1] = lpSkill;
						}
						else if(comboSkills[2] == 0 && comboSkills[1]->m_skill != lpSkill->m_skill)
						{
							comboSkills[2] = lpSkill;
						}
					}
				}
			}
		}

		if(comboSkills[0] != 0 && comboSkills[1] != 0 && comboSkills[2] != 0)
		{
			SkillRender = comboSkills[lpObj->OfflineComboStep % 3];
		}
		else
		{
			// Si no forman combo completo, rotar entre los skills validos configurados
			int validCount = 0;
			CSkill* validSkills[3];
			for(int i = 0; i < 3; i++)
			{
				if(skillIds[i] > 0 && skillIds[i] != 0xFFFF)
				{
					CSkill* lpSkill = gSkillManager.GetSkill(lpObj, skillIds[i]);
					if(lpSkill != 0)
					{
						validSkills[validCount++] = lpSkill;
					}
				}
			}

			if(validCount > 0)
			{
				SkillRender = validSkills[lpObj->OfflineComboStep % validCount];
			}
			else
			{
				SkillRender = gSkillManager.GetSkill(lpObj, lpObj->SkillBasicID);
			}
		}
	}
	else
	{
		SkillRender = gSkillManager.GetSkill(lpObj, lpObj->SkillBasicID);
	}

	if(SkillRender == 0)
	{
		return;
	}

	int atacar = 0;
	int tObjNum = -1;

	if(gCustomAttack.GetTargetMonster(lpObj, SkillRender->m_index, &tObjNum) != 0)
	{
		atacar = 0;

		if(gObj[tObjNum].Live == 0 || gObj[tObjNum].State == OBJECT_EMPTY || gObj[tObjNum].RegenType != 0)
		{
			return;
		}

		if(OBJMAX_RANGE(tObjNum) == FALSE)
		{
			return;
		}

		if(gObj[tObjNum].Type != OBJECT_MONSTER)
		{
			return;
		}

		if(gServerInfo.InSafeZone(tObjNum) == true)
		{
			return;
		}

		// Verificar que el monstruo este dentro del rango de caza desde la coordenada inicial
		int disOrigin = (int)sqrt((float)((gObj[tObjNum].X - lpObj->m_OfflineCoordX) * (gObj[tObjNum].X - lpObj->m_OfflineCoordX) + (gObj[tObjNum].Y - lpObj->m_OfflineCoordY) * (gObj[tObjNum].Y - lpObj->m_OfflineCoordY)));

		if(disOrigin > distance)
		{
			return;
		}

		bool bInRange = (gSkillManager.CheckSkillRange(SkillRender->m_index, lpObj->X, lpObj->Y, gObj[tObjNum].X, gObj[tObjNum].Y) != 0
			|| gSkillManager.CheckSkillRadio(SkillRender->m_index, lpObj->X, lpObj->Y, gObj[tObjNum].X, gObj[tObjNum].Y) != 0);

		if(bInRange)
		{
			caminar = 0;
			atacar = 1;
		}
		else
		{
			// Si Long Distance esta desactivado, no perseguir monstruos fuera de rango
			if(lpObj->DistanceLongOn == 0)
			{
				return;
			}

			// Si Long Distance esta activado, avanzar 1 casilla hacia el monstruo sin salirse del rango original
			int dirX = (gObj[tObjNum].X > lpObj->X) ? 1 : ((gObj[tObjNum].X < lpObj->X) ? -1 : 0);
			int dirY = (gObj[tObjNum].Y > lpObj->Y) ? 1 : ((gObj[tObjNum].Y < lpObj->Y) ? -1 : 0);
			int targetX = lpObj->X + dirX;
			int targetY = lpObj->Y + dirY;

			int newDisOrigin = (int)sqrt((float)((targetX - lpObj->m_OfflineCoordX) * (targetX - lpObj->m_OfflineCoordX) + (targetY - lpObj->m_OfflineCoordY) * (targetY - lpObj->m_OfflineCoordY)));

			if(newDisOrigin <= distance && gMap[lpObj->Map].CheckAttr(targetX, targetY, 1) == 0)
			{
				AnimationMove(lpObj->Index, targetX, targetY);
			}

			bInRange = (gSkillManager.CheckSkillRange(SkillRender->m_index, lpObj->X, lpObj->Y, gObj[tObjNum].X, gObj[tObjNum].Y) != 0
				|| gSkillManager.CheckSkillRadio(SkillRender->m_index, lpObj->X, lpObj->Y, gObj[tObjNum].X, gObj[tObjNum].Y) != 0);

			if(bInRange)
			{
				atacar = 1;
			}
		}

		if(atacar != 0)
		{
			// Auto pocion de mana si no alcanza
			if(lpObj->Mana < gSkillManager.GetSkillMana(SkillRender->m_index))
			{
				PMSG_ITEM_USE_RECV pMsgMP;

				pMsgMP.header.set(0x26, sizeof(pMsgMP));
				pMsgMP.SourceSlot = 0xFF;

				pMsgMP.SourceSlot = ((pMsgMP.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 6), -1) : pMsgMP.SourceSlot);
				pMsgMP.SourceSlot = ((pMsgMP.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 5), -1) : pMsgMP.SourceSlot);
				pMsgMP.SourceSlot = ((pMsgMP.SourceSlot == 0xFF) ? gItemManager.GetInventoryItemSlot(lpObj, GET_ITEM(14, 4), -1) : pMsgMP.SourceSlot);

				pMsgMP.TargetSlot = 0xFF;
				pMsgMP.type = 0;

				if(INVENTORY_FULL_RANGE(pMsgMP.SourceSlot) != 0)
				{
					gItemManager.CGItemUseRecv(&pMsgMP, lpObj->Index);
				}
				else
				{
					return;
				}
			}

			DWORD speed = (lpObj->PhysiSpeed > 0) ? (DWORD)lpObj->PhysiSpeed : 20;

			if((lpObj->Class == CLASS_DW || lpObj->Class == CLASS_SU) && (DWORD)lpObj->MagicSpeed > speed)
			{
				speed = (DWORD)lpObj->MagicSpeed;
			}

			int classNum = (lpObj->Class >= 0 && lpObj->Class < MAX_CLASS) ? lpObj->Class : CLASS_DK;

			// Retardo calibrado por raza: base configurable (def: 1000ms) reducida suavemente por la velocidad
			DWORD baseDelay = (this->m_MUOffHelperAttackDelay[classNum] > 0) ? (DWORD)this->m_MUOffHelperAttackDelay[classNum] : 1000;
			DWORD minDelay = (this->m_MUOffHelperMinDelay[classNum] > 0) ? (DWORD)this->m_MUOffHelperMinDelay[classNum] : 500;

			DWORD reduction = speed * 3;
			DWORD attackDelay = (baseDelay > reduction) ? (baseDelay - reduction) : minDelay;

			if(attackDelay < minDelay)
			{
				attackDelay = minDelay;
			}

			if((GetTickCount() - ((DWORD)lpObj->AttackCustomDelay)) >= attackDelay)
			{
				lpObj->AttackCustomDelay = GetTickCount();

				// Ataques normales (no AoE ni especiales)
				if(SkillRender->m_skill != SKILL_FLAME
					&& SkillRender->m_skill != SKILL_TWISTER
					&& SkillRender->m_skill != SKILL_EVIL_SPIRIT
					&& SkillRender->m_skill != SKILL_HELL_FIRE
					&& SkillRender->m_skill != SKILL_AQUA_BEAM
					&& SkillRender->m_skill != SKILL_BLAST
					&& SkillRender->m_skill != SKILL_INFERNO
					&& SkillRender->m_skill != SKILL_TRIPLE_SHOT
					&& SkillRender->m_skill != SKILL_IMPALE
					&& SkillRender->m_skill != SKILL_MONSTER_AREA_ATTACK
					&& SkillRender->m_skill != SKILL_PENETRATION
					&& SkillRender->m_skill != SKILL_FIRE_SLASH
					&& SkillRender->m_skill != SKILL_FIRE_SCREAM)
				{
					if(SkillRender->m_skill != SKILL_DARK_SIDE)
					{
						PMSG_DURATION_SKILL_ATTACK_RECV pMsg;

						pMsg.header.set(0x1E, sizeof(pMsg));

						#if(GAMESERVER_UPDATE>=701)
						pMsg.skillH = SET_NUMBERHB(0);
						pMsg.skillL = SET_NUMBERLB((((GetLargeRand() % 100) >= 25) ? 1 : 0));
						#else
						pMsg.skill[0] = SET_NUMBERHB(SkillRender->m_index);
						pMsg.skill[1] = SET_NUMBERLB(SkillRender->m_index);
						#endif

						pMsg.x = (BYTE)gObj[tObjNum].X;
						pMsg.y = (BYTE)gObj[tObjNum].Y;
						pMsg.dir = (gSkillManager.GetSkillAngle(gObj[tObjNum].X, gObj[tObjNum].Y, lpObj->X, lpObj->Y) * 255) / 360;
						pMsg.dis = 0;
						pMsg.angle = (gSkillManager.GetSkillAngle(lpObj->X, lpObj->Y, gObj[tObjNum].X, gObj[tObjNum].Y) * 255) / 360;

						#if(GAMESERVER_UPDATE>=803)
						pMsg.indexH = SET_NUMBERHB(lpObj->TargetNumber);
						pMsg.indexL = SET_NUMBERLB(lpObj->TargetNumber);
						#else
						pMsg.index[0] = SET_NUMBERHB(tObjNum);
						pMsg.index[1] = SET_NUMBERLB(tObjNum);
						#endif

						pMsg.MagicKey = 0;

						gSkillManager.CGDurationSkillAttackRecv(&pMsg, lpObj->Index);
					}
					else
					{
						gCustomAttack.SendRFSkillAttack(lpObj, tObjNum, SkillRender->m_index);
					}
				}
				else
				{
					gCustomAttack.SendMultiSkillAttack(lpObj, tObjNum, SkillRender->m_index);
				}

				if(lpObj->Class == CLASS_DK && lpObj->ComboOn != 0)
				{
					lpObj->OfflineComboStep = (lpObj->OfflineComboStep + 1) % 3;
				}
			}
		}
	}
}

// Auxiliar: determinar si un item es joya
static bool isJewels(int index)
{
	if(index == GET_ITEM(12, 15) ||
		index == GET_ITEM(14, 13) ||
		index == GET_ITEM(14, 14) ||
		index == GET_ITEM(14, 16) ||
		index == GET_ITEM(14, 22) ||
		index == GET_ITEM(14, 31) ||
		index == GET_ITEM(14, 42))
	{
		return true;
	}
	return false;
}

// Auxiliar: comprobar si el nombre del item esta en la lista personalizada
static bool itemListPickUp(int Index, int Level, LPOBJ lpObj)
{
	for(int i = 0; i < lpObj->ObtainPickExtraCount; i++)
	{
		if(strstr(gItemLevel.GetItemName(Index, Level), lpObj->ObtainPickItemList[i]) != NULL)
		{
			return true;
		}
	}
	return false;
}

int OfflineMode::PickUP(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == FALSE)
	{
		return 0;
	}

	if(!gObjIsConnectedGP(aIndex))
	{
		return 0;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_OfflineMode == 0)
	{
		return 0;
	}

	if(gServerInfo.InSafeZone(aIndex) == true)
	{
		this->OnHelperpAlreadyConnected(lpObj);
		return 0;
	}

	int distance = lpObj->ObtainRange;
	int map_num = gObj[aIndex].Map;

	if(gObj[aIndex].DieRegen != 0)
	{
		return 0;
	}

	if(MAP_RANGE(map_num) == FALSE)
	{
		return 0;
	}

	// Recorrer los items en el suelo del mapa iterando MAX_MAP_ITEM
	for(int n = 0; n < MAX_MAP_ITEM; n++)
	{
		if(gMap[map_num].m_Item[n].m_Live == 0)
		{
			continue;
		}

		if(gMap[map_num].m_Item[n].m_State != OBJECT_CREATE && gMap[map_num].m_Item[n].m_State != OBJECT_PLAYING)
		{
			continue;
		}

		CMapItem* lpItem = &gMap[map_num].m_Item[n];

		if(lpItem->IsItem() == 0)
		{
			continue;
		}

		// Calcular distancia al item
		int ix = lpItem->m_X;
		int iy = lpItem->m_Y;
		int dis = (int)sqrt((float)((lpObj->X - ix) * (lpObj->X - ix) + (lpObj->Y - iy) * (lpObj->Y - iy)));

		if(dis > distance)
		{
			continue;
		}

		int iItemIndex = lpItem->m_Index;
		int iItemLevel = lpItem->m_Level;

		bool pickUp = false;

		// Filtros de recogida
		if(lpObj->ObtainPickNear != 0)
		{
			pickUp = true;
		}

		if(!pickUp && lpObj->ObtainPickMoney != 0 && iItemIndex == GET_ITEM(14, 15))
		{
			pickUp = true;
		}

		if(!pickUp && lpObj->ObtainPickJewels != 0 && isJewels(iItemIndex))
		{
			pickUp = true;
		}

		if(!pickUp && lpObj->ObtainPickExcellent != 0 && lpItem->m_NewOption != 0)
		{
			pickUp = true;
		}

		if(!pickUp && lpObj->ObtainPickAncient != 0 && lpItem->m_SetOption != 0)
		{
			pickUp = true;
		}

		if(!pickUp && lpObj->ObtainPickExtra != 0 && itemListPickUp(iItemIndex, iItemLevel, lpObj))
		{
			pickUp = true;
		}

		if(pickUp)
		{
			PMSG_ITEM_GET_RECV pMsg;
			pMsg.header.set(0x22, sizeof(pMsg));
			pMsg.index[0] = SET_NUMBERHB(n);
			pMsg.index[1] = SET_NUMBERLB(n);

			gItemManager.CGItemGetRecv(&pMsg, aIndex);
		}
	}

	return 1;
}

void OfflineMode::regresar(int aIndex)
{
	if(OBJMAX_RANGE(aIndex) == FALSE)
	{
		return;
	}

	if(!gObjIsConnectedGP(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];

	if(lpObj->m_OfflineMode == 0)
	{
		return;
	}

	if(gServerInfo.InSafeZone(aIndex) == true)
	{
		return;
	}

	int distance = (lpObj->HuntingRange > 0) ? lpObj->HuntingRange : 6;
	int dis = (int)sqrt((float)((lpObj->X - lpObj->m_OfflineCoordX) * (lpObj->X - lpObj->m_OfflineCoordX) + (lpObj->Y - lpObj->m_OfflineCoordY) * (lpObj->Y - lpObj->m_OfflineCoordY)));

	if(dis == 0)
	{
		return;
	}

	bool shouldReturn = false;

	if(dis > distance)
	{
		if((GetTickCount() - lpObj->m_OfflineTimeResetMove) > 2000)
		{
			shouldReturn = true;
		}
	}
	else if(lpObj->DistanceReturnOn != 0)
	{
		DWORD returnDelay = (lpObj->DistanceMin > 0) ? (lpObj->DistanceMin * 1000) : 3000;
		if((GetTickCount() - lpObj->m_OfflineTimeResetMove) > returnDelay)
		{
			shouldReturn = true;
		}
	}

	if(shouldReturn)
	{
		lpObj->m_OfflineTimeResetMove = GetTickCount();
		AnimationMove(aIndex, lpObj->m_OfflineCoordX, lpObj->m_OfflineCoordY);
	}
}

