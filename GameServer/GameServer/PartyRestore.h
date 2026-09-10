// PartyRestore.h: interface for the CPartyRestore class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"
#include "Party.h"
#include "PartySearch.h"

struct PARTY_RESTORE_MEMBER
{
	char Name[11];
	BYTE Slot;
	DWORD DisconnectTick;
};

struct PARTY_RESTORE_INFO
{
	DWORD PartyID;
	int ActivePartyNumber;
	DWORD CreateTick;
	int Count;
	PARTY_RESTORE_MEMBER Members[MAX_PARTY_USER];
};

struct PARTY_SEARCH_RESTORE_DATA
{
	char Name[11];
	bool OnlyGuild;
	bool OnlyAlliance;
	bool OneClass;
	bool DarkWizard;
	bool DarkKnight;
	bool Elf;
	bool MagicGladiator;
	bool DarkLord;
	bool Summoner;
	bool RageFighter;
	int Level;
	bool RequirePassword;
	char Password[20];
};

class CPartyRestore
{
public:
	CPartyRestore();
	virtual ~CPartyRestore();
	void Init();
	void ReadConfig(char* section, char* path);
	void LoadData();
	void SaveData();
	void SaveParty(int partyNumber);
	void RemoveParty(int partyNumber);
	void RemoveMemberBySlot(int partyNumber, BYTE slot);
	void SavePartySearch(char* name);
	void RemovePartySearch(char* name);
	void OnCharacterLogin(LPOBJ lpObj);
	void OnCharacterClose(LPOBJ lpObj);
	void MainProc();
	bool IsEnabled() { return this->m_Enabled != 0; }
private:
	CRITICAL_SECTION m_critical;
	std::map<DWORD, PARTY_RESTORE_INFO> m_Parties;
	std::map<int, DWORD> m_PartyNumberToID;
	std::map<std::string, PARTY_SEARCH_RESTORE_DATA> m_PartySearch;
	DWORD m_NextPartyID;
	int m_Enabled;
	int m_Timeout;
	int m_TimeoutOnlyIfEmpty;
};

extern CPartyRestore gPartyRestore;
