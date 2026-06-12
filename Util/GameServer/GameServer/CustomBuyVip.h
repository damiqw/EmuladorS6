// CustomItem.h: interface for the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_CUSTOM_BUYVIP 3
#include "Protocol.h"

struct BUYPREMIUM_REQ
{
	PSBMSG_HEAD h;
	int	VipType;
};

#if(FLAG)
struct BUYFLAG_REQ
{
	PSBMSG_HEAD h;
	int	Flag;
};
struct CANCELFLAG_REQ
{
	PSBMSG_HEAD h;
	int	Flag;
};
#endif

struct CUSTOM_BUYVIP_INFO
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

struct PMSG_BUYVIP_LIST_SEND
{
	PSWMSG_HEAD header; // C1:F3:E6
	BYTE count;
};

struct PMSG_BUYVIP_LIST
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

class CCustomBuyVip
{
public:
	CCustomBuyVip();
	virtual ~CCustomBuyVip();
	void Init();
	void Load(char* path);
	void BuyVip(int aIndex, BUYPREMIUM_REQ* lpMsg);
	void BuyVipDone(LPOBJ lpObj);
	bool GCBuyVipSend(int aIndex);
	void ReloadBuyVipInterface();
#if(FLAG)
	void BuyFlag(int aIndex, BUYFLAG_REQ* lpMsg);
	void CancelFlag(int aIndex, CANCELFLAG_REQ* lpMsg);
#endif
public:
	std::map<int, CUSTOM_BUYVIP_INFO> m_CustomBuyVipInfo;
};

extern CCustomBuyVip gCustomBuyVip;