#pragma once
// -------------------------------------------------------------------------------
#include "User.h"
// -------------------------------------------------------------------------------

struct CUSTOMBUFF_MONSTER
{
	DWORD	MonsterID;
	int		MapNumber;
	int		Effect;
	int		Type;
	int		Power[4];
	int		Duration;
	// ----
	CUSTOMBUFF_MONSTER()
	{
		ZeroMemory(this, sizeof(*this));
	}
};
// -------------------------------------------------------------------------------

class CustomBuffMonster
{
public:
			CustomBuffMonster();
			~CustomBuffMonster();
	// ----
	void	Init();
	void	Load(char* path);
	// ----
	int		GetMonsterSlot(int Class, int Map);
	// ----
	void	AddMonsterBonus(LPOBJ lpObj, LPOBJ lpTarget);
	// ----
public:
	bool	m_IsLoaded;
	int		m_MonsterLoaded;
	// ----
	std::vector<CUSTOMBUFF_MONSTER> m_MobsData;
	// ----
}; extern CustomBuffMonster gCustomBuffMonster;
// -------------------------------------------------------------------------------