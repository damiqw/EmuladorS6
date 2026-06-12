#pragma once
//--/TAP FULLMAP
//----- (00790DF0) --------------------------------------------------------
//----- (00638130) --------------------------------------------------------
#include "Protocol.h"
#include "MiniMap.h"
#define pDrawMapFull ((void(__cdecl*)(int ModelID, float x, float y, float Width, float Heigth, float Rotacion))0x00638130)
#define sub_82B7A0 ((char(__thiscall*)(signed int a4, signed int a5))0x0082B7A0)
#define sub_8875E0 ((char(__cdecl*)(DWORD a1))0x008875E0)
#define sub_635CF0 ((void (__stdcall*)(signed int a4))0X00635CF0)
#define rFileOpen ((int(__cdecl*)(char* FileName, char* Mode)) 0x9D0040) //1.04E
#define rFileClose ((signed int(__cdecl*)(int a1))0x9CFC26) //1.04E 


struct BUTTON
{
	float x;
	float y;
	int Event;
};

struct MINI_MAP
{
/*+4*/		float x;
/*+8*/		float y;
/*+*/		float W;
/*+*/		float H;
/*+12*/		float Minimapx;
/*+16*/		float Minimapy;
/*+20*/		float TimeBarx;
/*+24*/		float TimeBary;
/*+116*/	float ZoomX;
/*+120*/	float ZoomY;
/*+128*/	float alpha;
	BUTTON Trans;
	BUTTON zoom;
};

class CMinimapB
{
public:
	CMinimapB();
	virtual ~CMinimapB();
	void MiniMaploadB();
public:
	DWORD DelayMove;
	bool Moving;
	short maxX;
	short maxY;
	DWORD ultimoX;
	DWORD ultimoY;
	LoadTypeMap DataMap;
	MINI_MAP DataMapOld;
}; extern CMinimapB gRenderMapB;