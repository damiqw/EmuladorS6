#include "stdafx.h"
#include "WingInvisible.h"
#include "Defines.h"
#include "WinDef.h"
#include "TMemory.h"
#include "Util.h"
#include "Object.h"
#include "Import.h"

DWORD	SetInvisibleEffect_PointerYY;
DWORD	SetInvisibleEffect_BuffYY;
DWORD	ObjectPointer;

__declspec(naked) void ItemInvisible1()
{

	static DWORD m_aaaaab = 0x0060B37A;

		_asm
		{
		mov SetInvisibleEffect_BuffYY, esi
		mov ecx, dword ptr ss : [ebp + 8]
		mov esi, dword ptr ds : [ecx + 0x30]
		mov SetInvisibleEffect_PointerYY, esi
		mov esi, SetInvisibleEffect_BuffYY
		}
		if(SetInvisibleEffect_PointerYY != 0x1EA5
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 15) 
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 30)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 31)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 136)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 137)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 138)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 139)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 140)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 141)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 142)
		|| SetInvisibleEffect_PointerYY != ITEM2(12, 143)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 14)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 16)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 31)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 42)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 13)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 41)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 43)
		|| SetInvisibleEffect_PointerYY != ITEM2(14, 44))
		{
		_asm
		{
			jmp [m_aaaaab]
		}
	}
}

void InvisibleItem1()
{
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible1);
}

//********************

DWORD	SetInvisibleEffect_PointerY;
DWORD	SetInvisibleEffect_BuffY;

__declspec(naked) void ItemInvisible2()
{
	static DWORD m_aaaaaa = 0x0060B41D;
		_asm
		{
		mov SetInvisibleEffect_BuffY, esi
		mov ecx, dword ptr ss : [ebp + 8]
		mov esi, dword ptr ds : [ecx + 0x30]
		jmp [m_aaaaaa]
		}
}

void InvisibleItem2()
{
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible2);
}

DWORD	SetInvisibleEffect_PointerX;
DWORD	SetInvisibleEffect_BuffX;

Naked(InvisibleEffectX)
{
	_asm
	{
		mov SetInvisibleEffect_BuffX, esi
		// ----
		mov ecx, dword ptr ss : [ebp + 8]
		mov esi, dword ptr ds : [ecx + 0x30]
		mov SetInvisibleEffect_PointerX, esi
		// ----
		mov esi, SetInvisibleEffect_BuffX
	}

	if (SetInvisibleEffect_PointerX == 0x1EA5
		|| SetInvisibleEffect_PointerX == ITEM2(13, 18))
	{

		_asm
		{
			mov SetInvisibleEffect_BuffX, 0x0060B37A
			jmp SetInvisibleEffect_BuffX
		}
	}
	else
	{
		_asm
		{
			mov SetInvisibleEffect_BuffX, 0x0060B41D
			jmp SetInvisibleEffect_BuffX
		}
	}
}

/*InvisibleWings*/
void KG_ActivateInvisibleWings_1()
{
	MemorySet(0x588661, 0x90, 0x5);
}

void KG_ActivateInvisibleWings_2()
{
	SetOp((LPVOID)0x00588661, (LPVOID)0x005655C0, ASM::CALL);
}

/*Effect15*/
void KG_ActivateEffect15_1()
{
	MemorySet(0x0057655B, 0x90, 0x5);
}

void KG_ActivateEffect15_2()
{
	SetOp((LPVOID)0x0057655B, (LPVOID)0x006097B0, ASM::CALL);
}

void KG_ActiveShades_1() 
{
	SetByte(0x0054A270, 0xC3);
}

void KG_ActiveShades_2() 
{
	SetByte(0x0054A270, 0x55);
}

void KG_ActivateInvisibleArmors_1()
{
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible1);
}

void KG_ActivateInvisibleArmors_2() 
{
	SetCompleteHook(0xE9, 0x0060B36A, &ItemInvisible2);
}

void KG_ActivateInvisibleArmors_X()
{
	SetRange((LPVOID)0x0060B36A, 10, ASM::NOP); //12
	SetCompleteHook(0xE9, 0x0060B36A, &InvisibleEffectX);
}

/*InvisibleWeapons*/
void KG_ActivateInvisibleWeapons_1()
{
	MemorySet(0x576DDB, 0x90, 0x5);
	MemorySet(0x5883F4, 0x90, 0x5);
}

void KG_ActivateInvisibleWeapons_2()
{
	SetOp((LPVOID)0x00576DDB, (LPVOID)0x005655C0, ASM::CALL);
	SetOp((LPVOID)0x005883F4, (LPVOID)0x005655C0, ASM::CALL);
}

//********************

void InvisibleItemX()
{
	SetRange((LPVOID)0x0060B36A, 10, ASM::NOP); //12
	SetCompleteHook(0xE9, 0x0060B36A, &InvisibleEffectX);
}