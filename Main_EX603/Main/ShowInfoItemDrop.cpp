#include "StdAfx.h"
#include "Util.h"
#include "SEASON3B.h"
#include "ShowInfoItemDrop.h"
#include "Interface.h"
#include "Protect.h"

ShowInventoryGX g_ShowInventoryGX;

ShowInventoryGX::ShowInventoryGX(void)
{
}

ShowInventoryGX::~ShowInventoryGX(void)
{
}

void CreateItemTooltip(int item_t)
{
	int itemshow = (int)(item_t + 2);
	POINT RenderPos;

	int sx = MouseX - 15;
	int sy = MouseY;
	char* item = new char[0x6Bu];
	memcpy(item, (const void *)itemshow, 0x6Bu);

	if (*(WORD *)itemshow < 7168)
	{	
		SetItemAttrInt((int)item, *(BYTE *)(itemshow + 2), *(BYTE *)(itemshow + 23), *(BYTE *)(itemshow + 24));
		//CHANGE TRUE TO FALSE IF NOT WORK
		RenderItemInfo(GetUI3D(GetInstance()), sx, sy, (int)item, 0, 0, true);
	}
}


void ShowInventoryGX::RenderItemName(int This, int Index, int o, int ItemLevel, int ItemOption, int ItemExtOption, bool Sort)
{
	if(gProtect.m_MainInfo.ItemTooltipDropType == 1)
	{
		if (!IsRepeatKey(VK_MENU)) 
		{
			return;
		}
	}
	Render_ItemName(This, Index, o, ItemLevel, ItemOption, ItemExtOption, Sort);
	CreateItemTooltip((int)&*(LPVOID*)0x81F6C00 + 848 * Index);
}

void ShowInventoryGX::Init()
{
	SetCompleteHook(0xE8, 0x00842AC7, &ShowInventoryGX::RenderItemName);
}