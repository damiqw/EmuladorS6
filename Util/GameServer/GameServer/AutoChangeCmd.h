//////////////////////////////////////////////////////////////////////

#ifndef AUTOCHANGECMD_H
#define AUTOCHANGECMD_H

struct AUTOCHANGE_ITEM_DATA
{
	WORD ItemID;
	BYTE CoinType;
	DWORD CoinValue;
};

#pragma once
class CAutoChangeCmd
{
public:
	CAutoChangeCmd();
	virtual ~CAutoChangeCmd();

	void LoadFile(char* szFile);
	int AutoChange(int aIndex);

private:
	bool m_bSystemEnable;
	std::map<int, AUTOCHANGE_ITEM_DATA> m_mapChangeData;
};

extern CAutoChangeCmd g_AutoChangeCmd;

#endif

//////////////////////////////////////////////////////////////////////
// iDev.Games - MuOnline S9EP2 IGC9.5 - TRONG.WIN - DAO VAN TRONG     
//////////////////////////////////////////////////////////////////////