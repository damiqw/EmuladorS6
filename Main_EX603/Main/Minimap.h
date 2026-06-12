#pragma once
#include "Protocol.h"
#include "Defines2.h"
#undef FogColor

#define BITMAP_EHUDMAP 31473

BITMAP_t* GetTextureInfo(int index);
void DrawSubImage(int textureId, float x, float y, float width, float height, float x1, float x2, float y1, float y2, int color = 0xFFFFFFFF);

//--/TAP FULLMAP
//----- (00790DF0) --------------------------------------------------------
//----- (00638130) --------------------------------------------------------
#define sub_82B7A0 ((char(__thiscall*)(signed int a4, signed int a5))0x0082B7A0)
#define sub_8875E0 ((char(__cdecl*)(DWORD a1))0x008875E0)
#define sub_635CF0 ((void (__stdcall*)(signed int a4))0X00635CF0)
#define TERRAIN_INDEX			((int(__cdecl*)(int x,int y)) 0x005D66F0)
#define Hero										*(DWORD*)0x007BC4F04
//Mover MiniMapa
//

#define pCursorX				*(int*)0x879340C//(1.04e) -- (1.05g)->*(int*)0x08B156EC
#define pCursorY				*(int*)0x8793410//(1.04e) -- (1.05g)->*(int*)0x08B156F0

#define MAX_MINI_MAP 200

struct AUTOMOVE_REQ
{
	PSBMSG_HEAD h;
	int	TYPE;
};
struct LoadTypeMap
{
	/*+0*/   DWORD ModelID;
	/*+4*/   DWORD XSW_Minimap_Frame;
	/*+8*/   DWORD YSW_Minimap_Frame;
	/*+12*/  DWORD XSW_Minimap;
	/*+16*/  DWORD YSW_Minimap;
	/*+20*/  DWORD XSW_Time_Frame;
	/*+24*/  DWORD YSW_Time_Frame;
	/*+92*/  DWORD This_92;
	/*+96*/  DWORD This_96;
	/*+100*/ DWORD DropMoveUserX;
	/*+104*/ DWORD DropMoveUserY;
	/*+108*/ DWORD This_108;
	/*+112*/ DWORD This_112;
	/*+116*/ float CurrentMoveX;
	/*+120*/ float CurrentMoveY;
	/*+124*/ DWORD Scale;
	/*+126*/ DWORD TimerEventVK;
	/*+128*/ float Alpha;
};

class CMinimap
{
public:
	CMinimap();
	virtual ~CMinimap();
	void MiniMapload();
	char MapRender(int a1);
	void AutoSendMove();
	void CGAutoMove(int Type);
public:
	LoadTypeMap DataMap;
	//MoverMiniMapa
	DWORD DelayMove;
	bool Moving;
	short maxX;
	short maxY;
	DWORD ultimoX;
	DWORD ultimoY;
	void UpdateX(float X, float Y = 0);
}; extern CMinimap gRenderMap;