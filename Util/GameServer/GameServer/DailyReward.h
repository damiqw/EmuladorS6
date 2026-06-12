#pragma once
#if(DAILY)
#include "Protocol.h"

struct cDR_User
{
	int aIndex;
	int mDay;
	BYTE State[31];
};

struct SDHP_DAILY_REWARD_INFO_RECV
{
	PWMSG_HEAD header; // C2:04
	WORD index;
	int  result;
	char acc[11];
	char name[11];
	BYTE Status[31];
};

struct PMSG_DAILY_REWARD_RECV
{
	PBMSG_HEAD2_Origin h;
	BYTE Type;
	int  Value;
};

struct PMSG_DAILY_REWARD_USER_INFO_SEND
{
	PBMSG_HEAD2_Origin h;
	BYTE MaxDay;
	BYTE CurDay;
	BYTE FWday;
	BYTE State[31];
	DWORD Timer;
};

struct PMSG_DAILY_REWARD_DAY_INFO_SEND
{
	PBMSG_HEAD2_Origin h;
	short Type;
	BYTE Dur;
	BYTE Item[12];
	int  PeriodTime;
	int Wcoin;
	int Zen;
	char Text[100];
};

struct cDR_Config
{
	short Day;
	short Item;
	BYTE Level;
	BYTE Op1;
	BYTE Op2;
	BYTE Op3;
	BYTE Dur;
	BYTE Ex;
	BYTE Anc;
	BYTE Sk[5];
	BYTE Skbonus;
	DWORD Expire;
	int	 Wcoin;
	int  Zen;
	int  Cost;
	char Text[100];
};

class cDailyReward
{
public:
	cDailyReward();
	~cDailyReward();
	void Read(char* path);
	void OnSecondProc(int aIndex);
	void CharZero(int aIndex);
	void DGDailyInfo(LPBYTE buf);
	void GDDailySave(int aIndex);
	void CGRequest(BYTE* a, int aIndex);
	void GCDailyUserInfo(int aIndex);
	void GCDailyInfo(int day, int aIndex);
	void OnRequestInfo(int aIndex);
	void OnRequestRecvGift(int day, int aIndex);
	void ItemByteConvert(BYTE* lpMsg, int day);
	cDR_Config* GetInfo(int day);
private:
	cDR_User Users[MAX_OBJECT_USER];
	std::map<int, cDR_Config> m_Configs;
};

extern cDailyReward DailyReward;
#endif