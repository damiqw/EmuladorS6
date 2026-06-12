//////////////////////////////////////////////////////////////////////

#ifndef ITEMCHANGECMD_H
#define ITEMCHANGECMD_H

struct ITEMCHANGE_ITEM_DATA
{
	WORD ItemID;
	BYTE CoinType;
	DWORD CoinValue;
};

#pragma once
class CItemChangeCmd
{
public:
	CItemChangeCmd();
	virtual ~CItemChangeCmd();

	void LoadFile(char* szFile);
	int ItemChange(int aIndex);

private:
	bool m_bSystemEnable;
	std::map<int, ITEMCHANGE_ITEM_DATA> m_mapChangeData;
};

extern CItemChangeCmd g_ItemChangeCmd;

#endif

//////////////////////////////////////////////////////////////////////
// iDev.Games - MuOnline S9EP2 IGC9.5 - TRONG.WIN - DAO VAN TRONG     
//////////////////////////////////////////////////////////////////////