#include "stdafx.h"
#include "FixAttack.h"
#include "User.h"
#include "Defines.h"
#include "Object.h"
#include "Util.h"
#include "TMemory.h"
#include "Import.h"

static DWORD ATTACK_RET = 0x00550A16;
static WORD CLASS = 0;
static WORD STR_SPEED = 0;
static WORD MAG_SPEED = 0;

__declspec(naked) void PositionGuildMakeCreate()
{
	static float PositionXUpdateEditGuildMark = 35.00000000000000;
	static DWORD m_UpdateEditGuildMark = 0x007D00BF;

	_asm {
		FADD DWORD PTR DS : [PositionXUpdateEditGuildMark]
			JMP[m_UpdateEditGuildMark]
	}

}

__declspec(naked) void FixVisualAttackSpeed()
{
	_asm
	{
		MOV EAX, DWORD PTR DS : [0x8128AC8]
		MOVZX ECX, WORD PTR DS : [EAX + 0xB]
		MOV CLASS, CX
		MOVZX ECX, WORD PTR DS : [EAX + 0x54]
		MOV STR_SPEED, CX
		MOVZX ECX, WORD PTR DS : [EAX + 0x60]
		MOV MAG_SPEED, CX
	}
	// --------------------------------------------

	gObjUser.MagickAttack = gObjUser.GetActiveSkill();

	// --------------------------------------------	
// -> Dark Knight

	if (CLASS == 1 || CLASS == 9 || CLASS == 25)
	{
		if (STR_SPEED > 3000)
		{
			STR_SPEED = 3189;
		}
	}

	// --------------------------------------------	
	// -> Dark Wizard

	if (CLASS == 0 || CLASS == 8 || CLASS == 24)
	{
		if (gObjUser.MagickAttack == 9 ||
			gObjUser.MagickAttack == 385 ||
			gObjUser.MagickAttack == 487 ||
			gObjUser.MagickAttack == 8 ||
			gObjUser.MagickAttack == 13 ||
			gObjUser.MagickAttack == 382 ||
			gObjUser.MagickAttack == 484 ||
			gObjUser.MagickAttack == 38 ||
			gObjUser.MagickAttack == 387 ||
			gObjUser.MagickAttack == 391 ||
			gObjUser.MagickAttack == 392 ||
			gObjUser.MagickAttack == 393 ||
			gObjUser.MagickAttack == 39 ||
			gObjUser.MagickAttack == 378 ||
			gObjUser.MagickAttack == 483 ||
			gObjUser.MagickAttack == 5)
		{
			if (MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if (MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if (MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if (MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if (MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		else if (gObjUser.MagickAttack == 14)
		{
			if (MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}
	}

	// --------------------------------------------	
	// -> Elf

	if (CLASS == 2 || CLASS == 10 || CLASS == 26)
	{
		if (gObjUser.MagickAttack == 24 ||
			gObjUser.MagickAttack == 414 ||
			gObjUser.MagickAttack == 418)
		{
			if (STR_SPEED > 508 /*&& STR_SPEED < 550*/)
			{
				STR_SPEED = 500;
			}
		}

		else if (gObjUser.MagickAttack == 52 ||
			gObjUser.MagickAttack == 51 ||
			gObjUser.MagickAttack == 424 ||
			gObjUser.MagickAttack == 416)
		{
			if (STR_SPEED > 400)
			{
				STR_SPEED = 400;
			}
		}

	}

	// --------------------------------------------	
	// -> Magic Gladiator

	if (CLASS == 3 || CLASS == 19)
	{
		if (gObjUser.MagickAttack == 55 ||
			gObjUser.MagickAttack == 490)
		{
			if (STR_SPEED > 1368)
			{
				STR_SPEED = 1368;
			}
		}
		if (gObjUser.MagickAttack == 9 ||
			gObjUser.MagickAttack == 385 ||
			gObjUser.MagickAttack == 487 ||
			gObjUser.MagickAttack == 8 ||
			gObjUser.MagickAttack == 13 ||
			gObjUser.MagickAttack == 382 ||
			gObjUser.MagickAttack == 484 ||
			gObjUser.MagickAttack == 39 ||
			gObjUser.MagickAttack == 378 ||
			gObjUser.MagickAttack == 483 ||
			gObjUser.MagickAttack == 5)
		{
			if (MAG_SPEED > 450 && MAG_SPEED < 480)
			{
				MAG_SPEED = 450;
			}
			else if (MAG_SPEED > 600 && MAG_SPEED < 690)
			{
				MAG_SPEED = 600;
			}
			else if (MAG_SPEED > 850 && MAG_SPEED < 1105)
			{
				MAG_SPEED = 850;
			}
			else if (MAG_SPEED > 1350 && MAG_SPEED < 2355)
			{
				MAG_SPEED = 1350;
			}
			else if (MAG_SPEED > 2850)
			{
				MAG_SPEED = 2850;
			}
		}
		if (gObjUser.MagickAttack == 14)
		{
			if (MAG_SPEED > 3276)
			{
				MAG_SPEED = 3276;
			}
		}
	}

	// --------------------------------------------	
	// -> Dark Lord

	if (CLASS == 4 || CLASS == 20)
	{
		if (gObjUser.MagickAttack == 78 ||
			gObjUser.MagickAttack == 518)
		{
			if (STR_SPEED > 249 && STR_SPEED < 264)
			{
				STR_SPEED = 249;
			}
			else if (STR_SPEED > 324 && STR_SPEED < 367)
			{
				STR_SPEED = 324;
			}
			else if (STR_SPEED > 449 && STR_SPEED < 575)
			{
				STR_SPEED = 449;
			}
			else if (STR_SPEED > 699 && STR_SPEED < 1200)
			{
				STR_SPEED = 699;
			}
			else if (STR_SPEED > 1449)
			{
				STR_SPEED = 1449;
			}
		}
	}

	// --------------------------------------------	
	// -> Rage Fighter

	/*if( CLASS == Monk || CLASS == 22 )
	{
		if( gObjUser.MagickAttack == 261 ||
			gObjUser.MagickAttack == 490 ||
			gObjUser.MagickAttack == 265 ||
			gObjUser.MagickAttack == 555 )
		{
			if(STR_SPEED > 754 && STR_SPEED < 1087)
			{
				STR_SPEED = 754;
			}
		}
	}*/

	// --------------------------------------------

	_asm
	{
		MOVZX ECX, WORD PTR DS : [STR_SPEED]
			MOV DWORD PTR SS : [EBP - 0x28] , ECX
				FILD DWORD PTR SS : [EBP - 0x28]
				FMUL QWORD PTR DS : [0x0D27C88] ; FLOAT 0.0010007200189989805
				FSTP DWORD PTR SS : [EBP - 0x10]
				MOVZX EAX, WORD PTR DS : [MAG_SPEED]
				MOV DWORD PTR SS : [EBP - 0x2C] , EAX
					FILD DWORD PTR SS : [EBP - 0x2C]
					FMUL QWORD PTR DS : [0x0D27C88] ; FLOAT 0.0010007200189989805
					FSTP DWORD PTR SS : [EBP - 0x0C]
					MOVZX EDX, WORD PTR DS : [MAG_SPEED]
					MOV DWORD PTR SS : [EBP - 0x30] , EDX
						FILD DWORD PTR SS : [EBP - 0x30]
						FMUL QWORD PTR DS : [0x0D281C0] ; FLOAT 0.002000000094994903
						FSTP DWORD PTR SS : [EBP - 0x4]
						FLD DWORD PTR SS : [EBP - 0x10]

						JMP ATTACK_RET
	}
}
// --------------------------------------------------------------------------------------------	

static DWORD RETURN_attack2 = 0x0055157D;

__declspec(naked) void FixVisualAttackSpeed2()
{
	_asm
	{
		MOVZX EDX, WORD PTR DS : [STR_SPEED]
			JMP RETURN_attack2
	}
}
// --------------------------------------------------------------------------------------------	

void __declspec(naked) WeaponHandBC1()
{
	static DWORD Return = 0x00561747;
	_asm { MOV EDX, DWORD PTR SS : [EBP + 0x8] }
	if (pMapNumber == 11 || pMapNumber == 12
		|| pMapNumber == 13 || pMapNumber == 14
		|| pMapNumber == 15 || pMapNumber == 16
		|| pMapNumber == 17 || pMapNumber == 52)
	{
		_asm { MOV BYTE PTR DS : [EDX + 0xE] , 0 }
	}
	else
	{
		_asm { MOV BYTE PTR DS : [EDX + 0xE] , 1 }
	}
	_asm { JMP[Return] }
}

void __declspec(naked) WeaponHandBC2()
{
	static DWORD Return = 0x0057DDDE;
	_asm { MOV ECX, DWORD PTR SS : [EBP + 0x8] }
	if (pMapNumber == 11 || pMapNumber == 12
		|| pMapNumber == 13 || pMapNumber == 14
		|| pMapNumber == 15 || pMapNumber == 16
		|| pMapNumber == 17 || pMapNumber == 52)
	{
		_asm { MOV BYTE PTR DS : [ECX + 0xE] , 0 }
	}
	else
	{
		_asm { MOV BYTE PTR DS : [ECX + 0xE] , 1 }
	}
	_asm { JMP[Return] }
}

void FixVisualSpeedAttack()
{
	//SetCompleteHook(0xE9, 0x00561740, &WeaponHandBC1);
	//SetCompleteHook(0xE9, 0x0057DDD7, &WeaponHandBC2);

	SetOp((LPVOID)0x005509CE, (LPVOID)FixVisualAttackSpeed, ASM::JMP);
	SetOp((LPVOID)0x00551573, (LPVOID)FixVisualAttackSpeed2, ASM::JMP);

	SetByte((PVOID)(0x007D14E5 + 2), 25);// NAME guild create
	SetByte((PVOID)(0x007D157D + 2), 30); // textura marco del los colores del guild
	SetByte((PVOID)(0x007CFEB8 + 3), 35);//MouseX
	SetCompleteHook(0xE9, 0x007D00B9, &PositionGuildMakeCreate);
}
// --------------------------------------------------------------------------------------------	
