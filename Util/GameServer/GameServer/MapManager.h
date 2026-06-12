// MapManager.h: interface for the CMapManager class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct MAP_MANAGER_INFO
{
	int Index;
	int NonPK;
	int ViewRange;
	int ExperienceRate;
	int MasterExperienceRate;
	int ItemDropRate;
	int ExcItemDropRate;
	int SetItemDropRate;
	int SocketItemDrop;
	int HelperEnable;
	int GensBattle;
	int PkDropItem;
	int MonsterHPBar;
	int TradeEnable;
	int CustomStore;
	int CustomAttack;
	int CustomPick;
	int ChatEnable;
	int PartyEnable;
	int DuelEnable;
	int SpawnGate;
	int RespawnGate;
	char Name[32];
};

class CMapManager
{
public:
	CMapManager();
	virtual ~CMapManager();
	void Load(char* path);
	int IsValidMap(int index);
	int GetMapNonPK(int index);
	int GetMapNonOutlaw(int index);
	int GetMapViewRange(int index);
	int GetMapExperienceRate(int index);
	int GetMapMasterExperienceRate(int index);
	int GetMapItemDropRate(int index);
	int GetMapExcItemDropRate(int index);
	int GetMapSetItemDropRate(int index);
	int GetMapSocketItemDrop(int index);
	int GetMapHelperEnable(int index);
	int GetMapGensBattle(int index);
	int GetMapPkDropItem(int index);
	int GetMapMonsterHPBar(int index);
	int GetMapTradeEnable(int index);
	int GetMapCustomStore(int index);
	int GetMapCustomAttack(int index);
	int GetMapCustomPick(int index);
	int GetMapChatEnable(int index);
	int GetMapPartyEnable(int index);
	int GetMapDuelEnable(int index);
	int GetSpawnGate(int index);
	int GetRespawnGate(int index);
	char* GetMapName(int index);
public:
	std::map<int,MAP_MANAGER_INFO> m_MapManagerInfo;
};

extern CMapManager gMapManager;
