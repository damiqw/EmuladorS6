#pragma once

#include "Protocol.h"
#include <map>
#include <vector>

#ifndef INVENTORY_WEAR_SIZE
#define INVENTORY_WEAR_SIZE 12
#endif

struct CUSTOM_ITEM_COLOR_DATA_CLIENT
{
	DWORD Serial;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct PMSG_CUSTOM_ITEM_COLOR_NPC_OPEN_RECV
{
	PSBMSG_HEAD header;
	int CostType;
	int CostValue;
};

struct PMSG_CUSTOM_ITEM_COLOR_REQ_SEND
{
	PSBMSG_HEAD header;
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct PMSG_CUSTOM_ITEM_COLOR_ANS_RECV
{
	PSBMSG_HEAD header;
	BYTE Result;
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

struct VIEWPORT_ITEM_COLOR_NODE_RECV
{
	BYTE Slot;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
	DWORD Serial;
};

struct PMSG_VIEWPORT_CUSTOM_ITEM_COLOR_RECV
{
	PSWMSG_HEAD header;
	WORD TargetIndex;
	BYTE Count;
};

struct EQUIPPED_DYE_ITEM
{
	BYTE Slot;
	WORD ItemIndex;
	char SlotName[32];
	char ItemName[64];
};

class CCustomItemColor
{
public:
	CCustomItemColor();
	virtual ~CCustomItemColor();

	void Init();
	void InstallRenderHooks();
	void OpenWindow(int costType, int costValue);
	void CloseWindow();
	bool IsWindowOpen() const { return this->m_WindowOpen; }
	void SetSelectedSlot(BYTE slot, WORD itemIndex = 0xFFFF) { this->m_SelectedSlot = slot; this->m_SelectedItemIndex = itemIndex; }

	void UpdateEquippedList();
	void DrawWindow();
	void UpdateMouse();

	void RecvNpcOpen(PMSG_CUSTOM_ITEM_COLOR_NPC_OPEN_RECV* lpMsg);
	void RecvAnswer(PMSG_CUSTOM_ITEM_COLOR_ANS_RECV* lpMsg);
	void RecvViewportSync(PMSG_VIEWPORT_CUSTOM_ITEM_COLOR_RECV* lpMsg);

	void SendApplyRequest();

	bool GetItemColorBySerial(DWORD serial, float* outColor);
	bool GetEquippedItemColor(int itemIndex, float* outColor);
	bool GetCharacterSlotColor(ObjectPreview* pChar, int modelIndex, float* outColor);

public:
	bool m_WindowOpen;
	int m_CostType;
	int m_CostValue;
	BYTE m_SelectedSlot;
	WORD m_SelectedItemIndex;
	BYTE m_ColorR;
	BYTE m_ColorG;
	BYTE m_ColorB;
	bool m_DraggingR;
	bool m_DraggingG;
	bool m_DraggingB;

	std::vector<EQUIPPED_DYE_ITEM> m_EquippedList;
	int m_EquippedListIndex;

	std::map<DWORD, CUSTOM_ITEM_COLOR_DATA_CLIENT> m_ItemColorMap;
	std::map<WORD, std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>> m_ViewportColorMap;
};

extern CCustomItemColor gCustomItemColor;
extern ObjectPreview* g_pCurrentRenderingPreview;
int __cdecl HookDrawViewPort(DWORD ObjectPointer, DWORD ModelPointer, int a3);
