// CustomDropCoin.h: interface for the CCustomDropCoin class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "User.h"

struct CUSTOM_COIN_DROP_INFO
{
	int MapNumber;
	int MonsterClass;
	int MonsterLevelMin;
	int MonsterLevelMax;
	int Coin1;
	int Coin2;
	int Coin3;
	int Ruud;
};

class CCustomDropCoin
{
public:
	CCustomDropCoin();
	virtual ~CCustomDropCoin();
	void Load(char* path);
	void AddMonsterBonus(LPOBJ lpMonster, LPOBJ lpObj);
	void SendNotify(int UserIndex, int Coin1, int Coin2, int Coin3,int Ruud, char* Text);
private:
	std::vector<CUSTOM_COIN_DROP_INFO> m_CustomDropCoinInfo;
};

extern CCustomDropCoin gCustomDropCoin;