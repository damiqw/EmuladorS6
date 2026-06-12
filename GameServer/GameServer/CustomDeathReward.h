#pragma once


#include "User.h"

struct REWARD_ZONE_INFO
{
	int map;
	int startX;
	int startY;
	int endX;
	int endY;
	DWORD zen;
	DWORD coin1;
	DWORD coin2;
	DWORD coin3;
	DWORD ruud;
	int pktype;
};

class CCustomDeathReward
{
public:
	CCustomDeathReward();
	~CCustomDeathReward();

	void Load(char* path);

	void CheckRewardZone(LPOBJ lpObj, LPOBJ lpTarget);

private:
	std::vector<REWARD_ZONE_INFO> m_CustomDeathRewardInfo;
};

extern CCustomDeathReward gCustomDeathReward;