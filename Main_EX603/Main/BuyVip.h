#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Interface.h"
#include "Import.h"

#define MAX_CUSTOM_BUYVIPS 3

struct CUSTOM_BUYVIPS_INFO
{
	int Index;
	int Exp;
	int Drop;
	int Days;
	int Coin1;
	int Coin2;
	int Coin3;
	char VipName[32];
};

struct BUYPREMIUM_REQ
{
	PSBMSG_HEAD h;
	int	VipType;
};

class cBuyVip
{
public:
	cBuyVip();
	~cBuyVip();

	void Init();
	void Load();
	void Draw();
	void DrawConfirm();
	void ClearBuyVipList();
	void InsertBuyVip(PMSG_BUYVIP_LIST* lpInfo);
	void BuyStatus(int VipType);

	bool		EventVipWindow_Main(DWORD Event);
	bool		EventVipWindow_Close(DWORD Event);
	bool		EventVipWindow_Bronze(DWORD Event);
	bool		EventVipWindow_Silver(DWORD Event);
	bool		EventVipWindow_Gold(DWORD Event);

	int ActivePage;
	int ActiveSend;
	int FreePoint;
	bool Click;
	int PointX;
	bool m_Loaded;

	bool CheckTestWindow()
	{
		return gInterface.Data[eVip_MAIN].OnShow;
	};

	void	OpenTestWindow()
	{
		gInterface.Data[eVip_MAIN].OnShow = true; pSetCursorFocus = true;
	};

	void    CloseTestWindow()
	{
		gInterface.Data[eVip_MAIN].OnShow = false; pSetCursorFocus = false;
	};
	DWORD OpenTestDelay;
	int JanelaConfirmVip;
};
extern cBuyVip gBuyVip;
