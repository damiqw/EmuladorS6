#pragma once

#include "Protocol.h"
#include "Object.h"
#define ITEM_BASE_MODEL 1171
// ---

#define MAX_ITEM_BANK 10

#define ITEMS_LEVEL(x)		(x << 3)
#define pGetItemBmdStruct(ItemId)   (ItemBmdStruct*)(*(DWORD*)0x8128AC0 + sizeof(ItemBmdStruct) * ItemId)
#define SET_ITEMOPT_LEVEL(x)  (x << 3)
#define MAX_ITEM_SLOT 30

struct CUSTOM_JEWELBANK_DATA
{
	int ItemBank[MAX_ITEM_SLOT];
};

struct PSBMSG_JEWELBANK_SEND
{
	PSBMSG_HEAD header; 
	int slot;
};

struct PSBMSG_JEWELBANKWITHDRAW_SEND
{
	PSBMSG_HEAD header; 
	int type;
	int count;
};

struct PSBMSG_JEWELBANK_UPDATE_SEND
{
	PSBMSG_HEAD header;
};

struct PSBMSG_JEWELBANK_RECV
{
	PSBMSG_HEAD h;

	int ItemBank[MAX_ITEM_SLOT];
	BYTE JewelEnable;
	BYTE JewelMaxCount;
	BYTE MAX_PAGES;
};
class CCustomJewelBank
{
	public:
	CCustomJewelBank();
	void Load();
	void DrawJewelBankWindow();
	void OpenWindow();
	bool CommandNext(DWORD Event);
	bool CommandPrev(DWORD Event);
	bool EventJewelBankWindow_Close(DWORD Event);
	bool EventJewelBankWithDraw(DWORD Event);
	void JewelBankWithDrawSend(int type, int count);
	void JewelBankSend(int slot);
	void GCCustomJewelBankInfoRecv(PSBMSG_JEWELBANK_RECV* lpMsg);
	void	SetPosGone();
	
	CUSTOM_JEWELBANK_DATA m_Data;
	bool IsOpen;
	short StatusLoad;
	DWORD StatusTick;
	int Loading;
	DWORD OpenTestDelay;
	float PosItemBank[MAX_ITEM_SLOT];
	BYTE JewelEnable;
	BYTE JewelMaxCount;
	BYTE MAX_PAGES;
	int Page;	
};
extern CCustomJewelBank gCustomJewelBank;
