// OfflineRestore.h: interface for the COfflineRestore class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

enum eOfflineRestoreType
{
	OFFLINE_RESTORE_NONE = 0,
	OFFLINE_RESTORE_ATTACK = 1,
	OFFLINE_RESTORE_STORE = 2,
	OFFLINE_RESTORE_HELPER = 3,
};

struct OFFLINE_RESTORE_DATA
{
	char Account[11];
	char Password[11];
	char Name[11];
	char IpAddr[16];
	char HardwareId[37];
	BYTE Type; // eOfflineRestoreType
	BYTE Map;
	BYTE X;
	BYTE Y;
	// OffAttack settings
	WORD Skill;
	BYTE AutoBuff;
	BYTE DisablePvp;
	BYTE AutoReset;
	int AutoResetStats[5];
	// OffHelper settings
	WORD HuntingRange;
	BYTE RecoveryPotionOn;
	BYTE RecoveryPotionPercent;
	BYTE RecoveryHealOn;
	BYTE RecoveryHealPercent;
	BYTE RecoveryDrainOn;
	BYTE RecoveryDrainPercent;
	BYTE DistanceLongOn;
	BYTE DistanceReturnOn;
	DWORD DistanceMin;
	WORD SkillBasicID;
	WORD SkillSecond1ID;
	WORD SkillSecond2ID;
	BYTE ComboOn;
	BYTE PartyModeOn;
	BYTE PartyModeHealOn;
	BYTE PartyModeHealPercent;
	BYTE PartyModeBuffOn;
	BYTE BuffOn;
	WORD BuffSkill[3];
	DWORD ObtainRange;
	BYTE ObtainRepairOn;
	BYTE ObtainPickNear;
	BYTE ObtainPickSelected;
	BYTE ObtainPickJewels;
	BYTE ObtainPickAncient;
	BYTE ObtainPickMoney;
	BYTE ObtainPickExcellent;
	BYTE ObtainPickExtra;
	BYTE ObtainPickExtraCount;
	char ObtainPickItemList[12][16];
	// OffStore settings
	char StoreName[37];
	BYTE StoreType;
};

class COfflineRestore
{
public:
	COfflineRestore();
	virtual ~COfflineRestore();
	void Init();
	void ReadConfig(char* section, char* path);
	void MainProc();
	void SaveOffline(LPOBJ lpObj, int type);
	void RemoveOffline(char* account);
	bool GetOfflineData(char* account, OFFLINE_RESTORE_DATA* lpData);
	void OnCharacterInfoRecv(LPOBJ lpObj);
private:
	void LoadData();
	void SaveData();
private:
	int m_Enabled;
	int m_Delay;
	DWORD m_StartTick;
	bool m_RestorationStarted;
	bool m_RestorationFinished;
	DWORD m_LastStepTick;
	std::map<std::string, OFFLINE_RESTORE_DATA> m_OfflineData;
	std::vector<std::string> m_RestoreQueue;
	size_t m_QueueIndex;
	CRITICAL_SECTION m_critical;
};

extern COfflineRestore gOfflineRestore;
