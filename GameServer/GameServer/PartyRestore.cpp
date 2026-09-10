// PartyRestore.cpp: implementation of the CPartyRestore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PartyRestore.h"
#include "Party.h"
#include "PartySearch.h"
#include "ServerInfo.h"
#include "Util.h"

CPartyRestore gPartyRestore;

#define PARTY_RESTORE_MAGIC 0x50545952 // 'PTYR'
#define PARTY_RESTORE_VERSION 1

struct PARTY_RESTORE_FILE_HEADER
{
	DWORD Header;
	DWORD Version;
	DWORD PartyCount;
	DWORD SearchCount;
};

CPartyRestore::CPartyRestore()
{
	this->m_Parties.clear();
	this->m_PartyNumberToID.clear();
	this->m_PartySearch.clear();
	this->m_NextPartyID = 1;
	InitializeCriticalSection(&this->m_critical);
}

CPartyRestore::~CPartyRestore()
{
	DeleteCriticalSection(&this->m_critical);
}

void CPartyRestore::Init()
{
	EnterCriticalSection(&this->m_critical);
	this->m_Parties.clear();
	this->m_PartyNumberToID.clear();
	this->m_PartySearch.clear();
	this->m_NextPartyID = 1;
	LeaveCriticalSection(&this->m_critical);

	this->LoadData();
}

void CPartyRestore::LoadData()
{
	EnterCriticalSection(&this->m_critical);

	FILE* file = fopen(".\\Data\\PartyRestore.dat", "rb");

	if (file == 0)
	{
		LeaveCriticalSection(&this->m_critical);
		return;
	}

	PARTY_RESTORE_FILE_HEADER header;

	if (fread(&header, sizeof(header), 1, file) != 1)
	{
		fclose(file);
		LeaveCriticalSection(&this->m_critical);
		return;
	}

	if (header.Header != PARTY_RESTORE_MAGIC || header.Version != PARTY_RESTORE_VERSION)
	{
		fclose(file);
		LeaveCriticalSection(&this->m_critical);
		return;
	}

	for (DWORD i = 0; i < header.PartyCount; ++i)
	{
		PARTY_RESTORE_INFO party;
		if (fread(&party, sizeof(party), 1, file) == 1)
		{
			party.ActivePartyNumber = -1;
			party.CreateTick = GetTickCount();
			for (int m = 0; m < party.Count; ++m)
			{
				party.Members[m].DisconnectTick = GetTickCount();
			}

			this->m_Parties[party.PartyID] = party;

			if (party.PartyID >= this->m_NextPartyID)
			{
				this->m_NextPartyID = party.PartyID + 1;
			}
		}
	}

	for (DWORD j = 0; j < header.SearchCount; ++j)
	{
		PARTY_SEARCH_RESTORE_DATA searchData;
		if (fread(&searchData, sizeof(searchData), 1, file) == 1)
		{
			std::string key(searchData.Name);
			std::transform(key.begin(), key.end(), key.begin(), tolower);
			this->m_PartySearch[key] = searchData;

			REGISTERED_INFO regInfo;
			memset(&regInfo, 0, sizeof(regInfo));
			memcpy(regInfo.Name, searchData.Name, sizeof(regInfo.Name));
			regInfo.aIndex = -1;
			regInfo.IsOnline = false;
			regInfo.OnlyGuild = searchData.OnlyGuild;
			regInfo.OnlyAlliance = searchData.OnlyAlliance;
			regInfo.OneClass = searchData.OneClass;
			regInfo.DarkWizard = searchData.DarkWizard;
			regInfo.DarkKnight = searchData.DarkKnight;
			regInfo.Elf = searchData.Elf;
			regInfo.MagicGladiator = searchData.MagicGladiator;
			regInfo.DarkLord = searchData.DarkLord;
			regInfo.Summoner = searchData.Summoner;
			regInfo.RageFighter = searchData.RageFighter;
			regInfo.Level = searchData.Level;
			regInfo.RequirePassword = searchData.RequirePassword;
			memcpy(regInfo.Password, searchData.Password, sizeof(regInfo.Password));

			gPartySearch.m_Registered[key] = regInfo;
		}
	}

	fclose(file);

	LogAdd(LOG_BLUE, "[PartyRestore] Loaded %d parties and %d party search entries from PartyRestore.dat",
		(int)this->m_Parties.size(), (int)this->m_PartySearch.size());

	LeaveCriticalSection(&this->m_critical);
}

void CPartyRestore::SaveData()
{
	EnterCriticalSection(&this->m_critical);

	FILE* file = fopen(".\\Data\\PartyRestore.tmp", "wb");

	if (file == 0)
	{
		LeaveCriticalSection(&this->m_critical);
		return;
	}

	PARTY_RESTORE_FILE_HEADER header;
	header.Header = PARTY_RESTORE_MAGIC;
	header.Version = PARTY_RESTORE_VERSION;
	header.PartyCount = (DWORD)this->m_Parties.size();
	header.SearchCount = (DWORD)this->m_PartySearch.size();

	if (fwrite(&header, sizeof(header), 1, file) != 1)
	{
		fclose(file);
		DeleteFileA(".\\Data\\PartyRestore.tmp");
		LeaveCriticalSection(&this->m_critical);
		return;
	}

	for (std::map<DWORD, PARTY_RESTORE_INFO>::iterator it = this->m_Parties.begin(); it != this->m_Parties.end(); ++it)
	{
		if (fwrite(&it->second, sizeof(PARTY_RESTORE_INFO), 1, file) != 1)
		{
			fclose(file);
			DeleteFileA(".\\Data\\PartyRestore.tmp");
			LeaveCriticalSection(&this->m_critical);
			return;
		}
	}

	for (std::map<std::string, PARTY_SEARCH_RESTORE_DATA>::iterator itS = this->m_PartySearch.begin(); itS != this->m_PartySearch.end(); ++itS)
	{
		if (fwrite(&itS->second, sizeof(PARTY_SEARCH_RESTORE_DATA), 1, file) != 1)
		{
			fclose(file);
			DeleteFileA(".\\Data\\PartyRestore.tmp");
			LeaveCriticalSection(&this->m_critical);
			return;
		}
	}

	fflush(file);
	fclose(file);

	MoveFileExA(".\\Data\\PartyRestore.tmp", ".\\Data\\PartyRestore.dat",
		MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH);

	LeaveCriticalSection(&this->m_critical);
}

void CPartyRestore::SaveParty(int partyNumber)
{
	if (gParty.IsParty(partyNumber) == 0)
	{
		this->RemoveParty(partyNumber);
		return;
	}

	EnterCriticalSection(&this->m_critical);

	DWORD partyID = 0;
	std::map<int, DWORD>::iterator itID = this->m_PartyNumberToID.find(partyNumber);
	if (itID != this->m_PartyNumberToID.end())
	{
		partyID = itID->second;
	}
	else
	{
		partyID = this->m_NextPartyID++;
		this->m_PartyNumberToID[partyNumber] = partyID;
	}

	PARTY_RESTORE_INFO prevInfo;
	bool hasPrev = false;
	std::map<DWORD, PARTY_RESTORE_INFO>::iterator itPrev = this->m_Parties.find(partyID);
	if (itPrev != this->m_Parties.end())
	{
		prevInfo = itPrev->second;
		hasPrev = true;
	}

	PARTY_RESTORE_INFO partyInfo;
	memset(&partyInfo, 0, sizeof(partyInfo));
	partyInfo.PartyID = partyID;
	partyInfo.ActivePartyNumber = partyNumber;
	partyInfo.CreateTick = hasPrev ? prevInfo.CreateTick : GetTickCount();
	partyInfo.Count = 0;

	for (int n = 0; n < MAX_PARTY_USER; ++n)
	{
		int memberIndex = gParty.m_PartyInfo[partyNumber].Index[n];
		if (OBJECT_RANGE(memberIndex) != 0)
		{
			LPOBJ lpMember = &gObj[memberIndex];
			memcpy(partyInfo.Members[partyInfo.Count].Name, lpMember->Name, sizeof(partyInfo.Members[partyInfo.Count].Name));
			partyInfo.Members[partyInfo.Count].Slot = (BYTE)n;
			partyInfo.Members[partyInfo.Count].DisconnectTick = 0;
			partyInfo.Count++;
		}
		else if (hasPrev)
		{
			for (int p = 0; p < prevInfo.Count; ++p)
			{
				if (prevInfo.Members[p].Slot == n && prevInfo.Members[p].Name[0] != '\0')
				{
					memcpy(partyInfo.Members[partyInfo.Count].Name, prevInfo.Members[p].Name, sizeof(partyInfo.Members[partyInfo.Count].Name));
					partyInfo.Members[partyInfo.Count].Slot = (BYTE)n;
					partyInfo.Members[partyInfo.Count].DisconnectTick = prevInfo.Members[p].DisconnectTick;
					partyInfo.Count++;
					break;
				}
			}
		}
	}

	if (partyInfo.Count > 0)
	{
		this->m_Parties[partyID] = partyInfo;
	}
	else
	{
		this->m_Parties.erase(partyID);
		this->m_PartyNumberToID.erase(partyNumber);
	}

	LeaveCriticalSection(&this->m_critical);

	this->SaveData();
}

void CPartyRestore::RemoveParty(int partyNumber)
{
	EnterCriticalSection(&this->m_critical);

	std::map<int, DWORD>::iterator itID = this->m_PartyNumberToID.find(partyNumber);
	if (itID != this->m_PartyNumberToID.end())
	{
		DWORD partyID = itID->second;
		this->m_Parties.erase(partyID);
		this->m_PartyNumberToID.erase(itID);
	}

	LeaveCriticalSection(&this->m_critical);

	this->SaveData();
}

void CPartyRestore::SavePartySearch(char* name)
{
	if (name == 0 || name[0] == '\0')
	{
		return;
	}

	std::string key(name);
	std::transform(key.begin(), key.end(), key.begin(), tolower);

	EnterCriticalSection(&this->m_critical);

	std::map<std::string, REGISTERED_INFO>::iterator it = gPartySearch.m_Registered.find(key);
	if (it != gPartySearch.m_Registered.end())
	{
		PARTY_SEARCH_RESTORE_DATA data;
		memset(&data, 0, sizeof(data));
		memcpy(data.Name, it->second.Name, sizeof(data.Name));
		data.OnlyGuild = it->second.OnlyGuild;
		data.OnlyAlliance = it->second.OnlyAlliance;
		data.OneClass = it->second.OneClass;
		data.DarkWizard = it->second.DarkWizard;
		data.DarkKnight = it->second.DarkKnight;
		data.Elf = it->second.Elf;
		data.MagicGladiator = it->second.MagicGladiator;
		data.DarkLord = it->second.DarkLord;
		data.Summoner = it->second.Summoner;
		data.RageFighter = it->second.RageFighter;
		data.Level = it->second.Level;
		data.RequirePassword = it->second.RequirePassword;
		memcpy(data.Password, it->second.Password, sizeof(data.Password));

		this->m_PartySearch[key] = data;
	}
	else
	{
		this->m_PartySearch.erase(key);
	}

	LeaveCriticalSection(&this->m_critical);

	this->SaveData();
}

void CPartyRestore::RemovePartySearch(char* name)
{
	if (name == 0 || name[0] == '\0')
	{
		return;
	}

	std::string key(name);
	std::transform(key.begin(), key.end(), key.begin(), tolower);

	EnterCriticalSection(&this->m_critical);
	this->m_PartySearch.erase(key);
	LeaveCriticalSection(&this->m_critical);

	this->SaveData();
}

void CPartyRestore::OnCharacterLogin(LPOBJ lpObj)
{
	if (lpObj == 0 || lpObj->Name[0] == '\0')
	{
		return;
	}

	EnterCriticalSection(&this->m_critical);

	DWORD targetPartyID = 0;
	BYTE targetSlot = 0;
	bool found = false;

	for (std::map<DWORD, PARTY_RESTORE_INFO>::iterator it = this->m_Parties.begin(); it != this->m_Parties.end(); ++it)
	{
		for (int m = 0; m < it->second.Count; ++m)
		{
			if (_stricmp(it->second.Members[m].Name, lpObj->Name) == 0)
			{
				targetPartyID = it->first;
				targetSlot = it->second.Members[m].Slot;
				it->second.Members[m].DisconnectTick = 0;
				found = true;
				break;
			}
		}
		if (found)
		{
			break;
		}
	}

	if (found)
	{
		PARTY_RESTORE_INFO& info = this->m_Parties[targetPartyID];
		int partyNumber = info.ActivePartyNumber;

		if (partyNumber != -1 && gParty.IsParty(partyNumber) != 0)
		{
			gParty.m_PartyInfo[partyNumber].Index[targetSlot] = lpObj->Index;
			lpObj->PartyNumber = partyNumber;

			int activeCount = 0;
			for (int n = 0; n < MAX_PARTY_USER; ++n)
			{
				if (OBJECT_RANGE(gParty.m_PartyInfo[partyNumber].Index[n]) != 0)
				{
					activeCount++;
				}
			}
			gParty.m_PartyInfo[partyNumber].Count = activeCount;
			gParty.GCPartyListSend(partyNumber);

			LogAdd(LOG_BLUE, "[PartyRestore] Reconnected [%s] to existing party [%d] slot [%d]", lpObj->Name, partyNumber, (int)targetSlot);
		}
		else
		{
			int newPartyNumber = -1;
			for (int n = 0; n < MAX_OBJECT; ++n)
			{
				if (gParty.m_PartyInfo[n].Count == 0)
				{
					newPartyNumber = n;
					break;
				}
			}

			if (newPartyNumber != -1)
			{
				info.ActivePartyNumber = newPartyNumber;
				this->m_PartyNumberToID[newPartyNumber] = targetPartyID;

				for (int i = 0; i < MAX_PARTY_USER; ++i)
				{
					gParty.m_PartyInfo[newPartyNumber].Index[i] = -1;
				}

				gParty.m_PartyInfo[newPartyNumber].Index[targetSlot] = lpObj->Index;
				gParty.m_PartyInfo[newPartyNumber].Count = 1;
				lpObj->PartyNumber = newPartyNumber;

				gParty.GCPartyListSend(newPartyNumber);

				LogAdd(LOG_BLUE, "[PartyRestore] Instantiated restored party [%d] for [%s] slot [%d]", newPartyNumber, lpObj->Name, (int)targetSlot);
			}
		}
	}

	std::string key(lpObj->Name);
	std::transform(key.begin(), key.end(), key.begin(), tolower);

	std::map<std::string, PARTY_SEARCH_RESTORE_DATA>::iterator itSearch = this->m_PartySearch.find(key);
	if (itSearch != this->m_PartySearch.end())
	{
		std::map<std::string, REGISTERED_INFO>::iterator itReg = gPartySearch.m_Registered.find(key);
		if (itReg != gPartySearch.m_Registered.end())
		{
			itReg->second.aIndex = lpObj->Index;
			itReg->second.IsOnline = true;
		}
		else
		{
			REGISTERED_INFO regInfo;
			memset(&regInfo, 0, sizeof(regInfo));
			memcpy(regInfo.Name, itSearch->second.Name, sizeof(regInfo.Name));
			regInfo.aIndex = lpObj->Index;
			regInfo.IsOnline = true;
			regInfo.OnlyGuild = itSearch->second.OnlyGuild;
			regInfo.OnlyAlliance = itSearch->second.OnlyAlliance;
			regInfo.OneClass = itSearch->second.OneClass;
			regInfo.DarkWizard = itSearch->second.DarkWizard;
			regInfo.DarkKnight = itSearch->second.DarkKnight;
			regInfo.Elf = itSearch->second.Elf;
			regInfo.MagicGladiator = itSearch->second.MagicGladiator;
			regInfo.DarkLord = itSearch->second.DarkLord;
			regInfo.Summoner = itSearch->second.Summoner;
			regInfo.RageFighter = itSearch->second.RageFighter;
			regInfo.Level = itSearch->second.Level;
			regInfo.RequirePassword = itSearch->second.RequirePassword;
			memcpy(regInfo.Password, itSearch->second.Password, sizeof(regInfo.Password));

			gPartySearch.m_Registered[key] = regInfo;
		}
	}

	LeaveCriticalSection(&this->m_critical);
}

void CPartyRestore::OnCharacterClose(LPOBJ lpObj)
{
	if (lpObj == 0 || lpObj->PartyNumber < 0 || gParty.IsParty(lpObj->PartyNumber) == 0)
	{
		return;
	}

	EnterCriticalSection(&this->m_critical);

	int partyNumber = lpObj->PartyNumber;
	for (int n = 0; n < MAX_PARTY_USER; ++n)
	{
		if (gParty.m_PartyInfo[partyNumber].Index[n] == lpObj->Index)
		{
			gParty.m_PartyInfo[partyNumber].Index[n] = -1;

			std::map<int, DWORD>::iterator itID = this->m_PartyNumberToID.find(partyNumber);
			if (itID != this->m_PartyNumberToID.end())
			{
				std::map<DWORD, PARTY_RESTORE_INFO>::iterator itP = this->m_Parties.find(itID->second);
				if (itP != this->m_Parties.end())
				{
					for (int m = 0; m < itP->second.Count; ++m)
					{
						if (itP->second.Members[m].Slot == n)
						{
							itP->second.Members[m].DisconnectTick = GetTickCount();
							break;
						}
					}
				}
			}

			LogAdd(LOG_BLUE, "[PartyRestore] Vacated slot [%d] in party [%d] for character [%s] (transition to client)",
				n, partyNumber, lpObj->Name);
			break;
		}
	}

	LeaveCriticalSection(&this->m_critical);
}

void CPartyRestore::MainProc()
{
	EnterCriticalSection(&this->m_critical);

	DWORD currentTick = GetTickCount();
	DWORD timeout = (DWORD)(gServerInfo.m_PartyReconnectTime > 0 ? gServerInfo.m_PartyReconnectTime * 1000 : 300000);

	for (std::map<DWORD, PARTY_RESTORE_INFO>::iterator it = this->m_Parties.begin(); it != this->m_Parties.end();)
	{
		int partyNumber = it->second.ActivePartyNumber;
		bool partyAlive = (partyNumber != -1 && gParty.IsParty(partyNumber) != 0);

		int onlineCount = 0;
		if (partyAlive)
		{
			for (int n = 0; n < MAX_PARTY_USER; ++n)
			{
				if (OBJECT_RANGE(gParty.m_PartyInfo[partyNumber].Index[n]) != 0)
				{
					onlineCount++;
				}
			}
		}

		bool erased = false;

		// Clean up members that exceeded timeout
		for (int m = 0; m < it->second.Count;)
		{
			if (it->second.Members[m].DisconnectTick != 0 && (currentTick - it->second.Members[m].DisconnectTick) > timeout)
			{
				BYTE timedOutSlot = it->second.Members[m].Slot;

				if (partyAlive && gParty.m_PartyInfo[partyNumber].Index[timedOutSlot] == -1)
				{
					if (timedOutSlot == 0 && onlineCount > 0)
					{
						gParty.ChangeLeader(partyNumber, 0);
					}
				}

				for (int k = m; k < it->second.Count - 1; ++k)
				{
					it->second.Members[k] = it->second.Members[k + 1];
				}
				it->second.Count--;
				continue;
			}
			m++;
		}

		if (it->second.Count == 0)
		{
			if (partyAlive)
			{
				gParty.Destroy(partyNumber);
			}
			if (partyNumber != -1)
			{
				this->m_PartyNumberToID.erase(partyNumber);
			}
			it = this->m_Parties.erase(it);
			erased = true;
		}

		if (!erased)
		{
			++it;
		}
	}

	LeaveCriticalSection(&this->m_critical);
}
