// MonsterMove.h: interface for the CMonsterMove class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct MONSTER_MOVE_SPAWN
{
	int MonsterClass;
	int Map;
	int X;
	int Y;
	int Dir;
	int MoveTime;
};

struct MONSTER_MOVE_INFO
{
	int Index;
	int MonsterIndex;
	DWORD CreateTime;
	DWORD MoveTime;
	std::vector<MONSTER_MOVE_SPAWN> SpawnInfo;
};

class CMonsterMove
{
public:
	CMonsterMove();
	virtual ~CMonsterMove();
	void Load(char* path);
	void SetInfo(int MonsterClass);
	void SetSpawnInfo(MONSTER_MOVE_SPAWN info);
	void MainProc();
private:
	std::map<int,MONSTER_MOVE_INFO> m_MonsterMoveInfo;
};

extern CMonsterMove gMonsterMove;
