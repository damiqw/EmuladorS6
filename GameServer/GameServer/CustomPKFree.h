#pragma once

#include "User.h"

struct PK_ZONE_INFO
{
	int map;
	int startX;
	int startY;
	int endX;
	int endY;
	int type;
};

class CPKZone
{
public:
	CPKZone();
	~CPKZone();

	void Load(char* path);

	bool CheckAttackZone(LPOBJ lpObj, LPOBJ lpTarget);
	bool CheckZoneMurderLevel(LPOBJ lpObj, LPOBJ lpTarget);

private:
	std::vector<PK_ZONE_INFO> m_PkZoneInfo;
};

extern CPKZone gPKZone;