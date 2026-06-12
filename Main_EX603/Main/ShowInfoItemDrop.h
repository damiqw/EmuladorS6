#pragma once
#include "Object.h"

#define SetItemAttrInt				((void(__stdcall*)(int pItem, BYTE byLevel, BYTE byOption1, BYTE byOptionEx)) 0x007E22A0)
#define Render_ItemName				((void(__cdecl*)(int Index, int o, int ItemLevel, int ItemOption, int ItemExtOption, signed int a6, bool Sort)) 0x005C6980)
#define RenderItemInfo				((void(__thiscall*)(int This, int sx,int sy, int ip,bool Sell, int Inventype, bool bItemTextListBoxUse)) 0x007E3E30)
#define GetUI3D										((int(__thiscall*)(int thisa))0x00861AA0)
#define GetInstance										((int(*)()) 0x00861110)

#define IsPressKey(key) ((int(*)(int))0x791070)(key)
#define IsRepeatKey(key) ((int(*)(int))0x791090)(key)

class ShowInventoryGX
{
public:
	ShowInventoryGX(void);
	virtual ~ShowInventoryGX(void);
	void Init();
	static void RenderItemName(int Index, int o, int ItemLevel, int ItemOption, int a5, signed int ItemExtOption, bool Sort);

};

extern ShowInventoryGX g_ShowInventoryGX;
