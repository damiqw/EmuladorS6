#pragma once

#include "User.h"
#include "Protocol.h"

struct CUSTOM_ITEM_COLOR_NPC_INFO
{
	int Enable;
	int NPCClass;
	int Map;
	int PosX;
	int PosY;
	int CostType; // 0: WCoinC, 1: WCoinP, 2: GoblinPoint, 3: Money
	int CostValue;
};

struct CUSTOM_ITEM_COLOR_ALLOW_INFO
{
	int ItemIndex;
};

struct CUSTOM_ITEM_COLOR_DATA
{
	DWORD Serial;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

// Packets
struct PMSG_CUSTOM_ITEM_COLOR_NPC_OPEN
{
	PSBMSG_HEAD header;
	int CostType;
	int CostValue;
};

struct PMSG_CUSTOM_ITEM_COLOR_REQ
{
	PSBMSG_HEAD header;
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct PMSG_CUSTOM_ITEM_COLOR_ANS
{
	PSBMSG_HEAD header;
	BYTE Result; // 0: Fail, 1: Success
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct VIEWPORT_ITEM_COLOR_NODE
{
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
	DWORD Serial;
	short ItemID;
	int Level;
	BYTE ExcellentOption;
	BYTE AncientOption;
};

struct PMSG_VIEWPORT_CUSTOM_ITEM_COLOR
{
	PSWMSG_HEAD header;
	WORD TargetIndex;
	BYTE Count;
};

struct SDHP_CUSTOM_ITEM_COLOR_SAVE_SEND
{
	PSBMSG_HEAD header;
	DWORD Serial;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct SDHP_CUSTOM_ITEM_COLOR_LOAD_SEND
{
	PSBMSG_HEAD header;
	WORD AccountIndex;
};

struct SDHP_CUSTOM_ITEM_COLOR_NODE
{
	DWORD Serial;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct SDHP_CUSTOM_ITEM_COLOR_LOAD_RECV
{
	PSWMSG_HEAD header;
	WORD AccountIndex;
	WORD Count;
};

class CCustomItemColor
{
public:
	CCustomItemColor();
	virtual ~CCustomItemColor();

	void LoadFile(char* path);
	bool NpcTalk(LPOBJ lpNpc, LPOBJ lpObj);
	void CGItemColorRecv(PMSG_CUSTOM_ITEM_COLOR_REQ* lpMsg, int aIndex);
	void SendViewportItemColor(LPOBJ lpObj, int aTargetIndex);
	void SendViewportList(LPOBJ lpObj);
	
	void DGItemColorSaveSend(DWORD serial, BYTE r, BYTE g, BYTE b);
	void DGItemColorLoadSend(int aIndex);
	void GDItemColorLoadRecv(SDHP_CUSTOM_ITEM_COLOR_LOAD_RECV* lpMsg);

	bool IsAllowedItem(int itemIndex);
	void SetItemColor(DWORD serial, BYTE r, BYTE g, BYTE b);
	bool GetItemColor(DWORD serial, BYTE& r, BYTE& g, BYTE& b);

private:
	CUSTOM_ITEM_COLOR_NPC_INFO m_NpcInfo;
	std::vector<CUSTOM_ITEM_COLOR_ALLOW_INFO> m_AllowItems;
	std::map<DWORD, CUSTOM_ITEM_COLOR_DATA> m_ItemColorMap;
};

extern CCustomItemColor gCustomItemColor;
