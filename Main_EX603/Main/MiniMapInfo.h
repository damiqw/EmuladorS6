#pragma once

#include "Protocol.h"
#include <vector>

#define MAX_PLAYER_PARTY 10

#pragma pack(push, 1)

struct MINIMAP_PARTY_INFO_RECV
{
	PSWMSG_HEAD header; // C1:E7:01
	BYTE count;
};

struct MINIMAP_PARTY_INFO
{
	char name[11];
	BYTE map;
	BYTE x;
	BYTE y;
};

struct MINIMAP_INFO_RECV
{
	PSBMSG_HEAD header; // C1:E7:03
	BYTE index;
	BYTE group;
	BYTE type;
	BYTE flag;
	BYTE x;
	BYTE y;
	char text[31];
};

struct MINIMAP_SPOT_INFO
{
	BYTE index;
	BYTE group;
	BYTE type;
	BYTE flag;
	BYTE x;
	BYTE y;
	char text[31];
};

#pragma pack(pop)

class cMiniMap
{
public:
	cMiniMap();
	~cMiniMap();
	void ClearPartyInfo();
	void RecvPartyInfo(MINIMAP_PARTY_INFO_RECV* lpMsg);
	void InsertPartyInfo(MINIMAP_PARTY_INFO* lpInfo);
	void RecvMiniMapInfo(MINIMAP_INFO_RECV* lpMsg);
	// ----
	MINIMAP_PARTY_INFO gPartyInfo[MAX_PLAYER_PARTY];
	int ListsCount;
	std::vector<MINIMAP_SPOT_INFO> m_MiniMapSpotInfo;
	// ----
}; extern cMiniMap gMiniMap;