#pragma once
#include "DefaultClassInfo.h"
#include "User.h"
#include "Protocol.h"
#include "SkillManager.h"

struct MESSAGE_INFO_MAPUSAGETIME
{
	int Index;
	char Message[256];
};

struct DATA_MAPLIST_MAPUSAGETIME
{
	int IDMap;
	int UseItemIndex;
	int UseItemLevel;
	int UseItemCount;
	int UseWC;
	int UseWP;
	int UseGP;
	int UseRuud;
	int TimeAdd;
};
#pragma pack(push, 1)
struct MAPUSAGETIME_INFO
{
	PSBMSG_HEAD	 header;
	WORD		Map;
	DWORD		Time;
};
#pragma pack(pop)

class CB_MapUsageTime
{
public:
	CB_MapUsageTime();
	virtual ~CB_MapUsageTime();
	void Load(char* path);
	std::map<int, DATA_MAPLIST_MAPUSAGETIME> m_DataMapList;
	DATA_MAPLIST_MAPUSAGETIME* CB_MapUsageTime::GetInfoMapUsageTime(int MapID);
	void CB_MapUsageTime::CheckMapUsageTime(int aIndex);
private:
	//===Mess
	std::map<int, MESSAGE_INFO_MAPUSAGETIME> m_MessageInfoBP;
	char* GetMessage(int index);
};

extern CB_MapUsageTime gCB_MapUsageTime;