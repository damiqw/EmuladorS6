#include "stdafx.h"
#include "AtlansAbbys.h"
#include "Util.h"


void __declspec(naked) CSetPlayerSwimStop()
{
	static DWORD CReturn = 0x0054EE7F;
	_asm
	{
			CMP DWORD PTR DS:[0xE61E18],7
			je ReturnLoad
			CMP DWORD PTR DS:[0xE61E18],93//ID del Mapa
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CSetPlayerSwimWalk()
{
	static DWORD CReturn = 0x0054FFBE;
	_asm
	{
			CMP DWORD PTR DS:[0xE61E18],7
			je ReturnLoad
			CMP DWORD PTR DS:[0xE61E18],93//ID del Mapa
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CRenderCharacterBackItem_Swim()
{
	static DWORD CReturn = 0x005880B4;
	_asm
	{
			CMP DWORD PTR DS:[0xE61E18],7
			je ReturnLoad
			CMP DWORD PTR DS:[0xE61E18],93//ID del Mapa
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp CReturn
	}
}

void __declspec(naked) CPlayWalkSound_Swim()
{
	static DWORD CReturn = 0x00560CED;
	_asm
	{
			CMP DWORD PTR DS:[0xE61E18],7
			je ReturnLoad
			CMP DWORD PTR DS:[0xE61E18],93//ID del Mapa
			je ReturnLoad
			// ---
		ReturnLoad :
		// ---
		jmp CReturn
	}
}

void InitAtlansAbbys()
{
	SetCompleteHook(0xE9, 0x0054EE78, &CSetPlayerSwimStop);
	SetCompleteHook(0xE9, 0x0054FFB7, &CSetPlayerSwimWalk);
	SetCompleteHook(0xE9, 0x005880AD, &CRenderCharacterBackItem_Swim);
	SetCompleteHook(0xE9, 0x00560CE6, &CPlayWalkSound_Swim);
}