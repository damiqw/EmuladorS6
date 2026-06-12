// InvasionManager.h: interface for the CInvasionManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"
#include "Map.h"

#define MAX_INVASION 30
#define MAX_INVASION_MONSTER 500
#define MAX_INVASION_RESPAWN_GROUP 20

enum eInvasionState
{
	INVASION_STATE_BLANK = 0,
	INVASION_STATE_EMPTY = 1,
	INVASION_STATE_START = 2,
};

struct INVASION_START_TIME
{
	int Year;
	int Month;
	int Day;
	int DayOfWeek;
	int Hour;
	int Minute;
	int Second;
};

struct INVASION_RESPWAN_INFO
{
	int Group;
	int Map;
	int Stage;
};

struct INVASION_MONSTER_INFO
{
	int Group;
	int MonsterClass;
	int Range;
	int Map;
	int X;
	int Y;
	int TX;
	int TY;
	int Count;
	int Stage;
	int RegenType;
	int RegenTime;
};

#if(INFO_EVENTINVASION)
struct INVASION_MONTER_INFO_SEND
{
	int Index;
	int Class;
	int Count;
	int CountMax;
	char Name[50];
};

struct INVASION_INFO_MONTER
{
	int Class;
	int Count;
	int CountMax;
	int RegenTime;
	int RegenType;
	int RegenTimeSave;
};
struct INVASION_INFO_SEND
{
	int Index;
	int State;
	int RemainTime;
	char NameInvasion[128];
	int Page;
};

//**********************************************//
//************ Packet Base *********************//
//**********************************************//
#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )
struct PWMSG_HEAD_MK
{

public:
	void set(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
	{
		lpBuf[0] = 0xC2;
		lpBuf[1] = SET_NUMBERH(size);
		lpBuf[2] = SET_NUMBERL(size);
		lpBuf[3] = head;
		lpBuf[4] = sub;
	}

	BYTE c;
	BYTE sizeH;
	BYTE sizeL;
	BYTE headcode;
	BYTE subcode;
};


struct PMSG_INVASION_INFO
{
	PWMSG_HEAD_MK h;
	INVASION_INFO_SEND Info[MAX_INVASION];
};

struct EVENT_INVASION_ACTION
{
	PSBMSG_HEAD h;
	int index;
};

struct PMSG_INVASION_INFO_MONTER
{
	PWMSG_HEAD_MK h;
	INVASION_INFO_MONTER Info[MAX_INVASION_RESPAWN_GROUP];
};
#endif

struct INVASION_INFO
{
	int Index;
	int State;
	int RemainTime;
	int TargetTime;
	int TickCount;
	int MonsterIndex[MAX_INVASION_MONSTER];
	int RespawnMessage;
	int DespawnMessage;
	int Effect;
	int BossIndex;
	int BossCount[MAX_MAP];
	int BossMessage;
	int InvasionTime;
	std::vector<INVASION_START_TIME> StartTime;
	std::vector<INVASION_RESPWAN_INFO> RespawnInfo[MAX_INVASION_RESPAWN_GROUP];
	std::vector<INVASION_MONSTER_INFO> MonsterInfo;
#if(INFO_EVENTINVASION)
	INVASION_INFO_MONTER InfoMonter[MAX_INVASION_RESPAWN_GROUP];
	int AlarmMinSave;
	int AlarmMinLeft;
	int AlarmTime;
	char AlertMessage[128];
#endif
};

class CInvasionManager
{
public:
	CInvasionManager();
	virtual ~CInvasionManager();
	void Init();
	void Load(char* path);
	void MainProc();
	void ProcState_BLANK(INVASION_INFO* lpInfo);
	void ProcState_EMPTY(INVASION_INFO* lpInfo);
	void ProcState_START(INVASION_INFO* lpInfo);
	void SetState(INVASION_INFO* lpInfo,int state);
	void SetState_BLANK(INVASION_INFO* lpInfo);
	void SetState_EMPTY(INVASION_INFO* lpInfo);
	void SetState_START(INVASION_INFO* lpInfo);
	void CheckSync(INVASION_INFO* lpInfo);
	int GetState(int index);
	int GetRemainTime(int index);
	bool AddMonster(INVASION_INFO* lpInfo,int aIndex);
	bool DelMonster(INVASION_INFO* lpInfo,int aIndex);
	int* GetMonster(INVASION_INFO* lpInfo,int aIndex);
	void CleanMonster(INVASION_INFO* lpInfo);
	void ClearMonster(INVASION_INFO* lpInfo);
	int GetMonsterCount(INVASION_INFO* lpInfo);
	void MonsterDieProc(LPOBJ lpObj,LPOBJ lpTarget);
	void CheckEvent(LPOBJ lpObj);
	void ForceStart(int index);
	INVASION_INFO m_InvasionInfo[MAX_INVASION];
#if(INFO_EVENTINVASION)
	void SendMain(LPOBJ lpObj);
	void SendMonter(int aIndex, EVENT_INVASION_ACTION* aRecv);
	void CheckRegenTimeMonter();
#endif
private:
	DWORD GetTickCountInvasionActive;
	
};

extern CInvasionManager gInvasionManager;
