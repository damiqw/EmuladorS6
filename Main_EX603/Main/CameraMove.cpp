#include "StdAfx.h"
#if(FPS_60 == 1)
#include "Util.h"
#include "Protect.h"
#include "CustomMap.h"
#include "CameraMove.h"

int FpsTime = 0;
int FpsCount = 0;
int AnimationFrameConstant;
CCameraMove g_CameraWalkInstance;

CCameraMove::CCameraMove(void)
{
}

CCameraMove::~CCameraMove(void)
{
}

void CalcFPS()
{
	((void(__cdecl*)()) 0x00542EF0)(); FpsCount++;

	if (GetTickCount() >= (FpsTime + 999))
	{
		AnimationFrameConstant = FpsCount / 1.5;
		FpsTime = GetTickCount();
		FpsCount = 0;

	}
}

void UpdateTourWayPoint(int This, int WayPoint, float fDirVector1, float fDirVector2, float fTourDirVector1, float fTourDirVector2)
{
	float DelT = DelTtime * AnimationFrameConstant;

	*((float*)This + 12) = (fDirVector1 * *(float*)(WayPoint + 20) * DelT) + *((float*)This + 12);
	*((float*)This + 13) = (fDirVector2 * *(float*)(WayPoint + 20) * DelT) + *((float*)This + 13);
	*((float*)This + 23) = (fTourDirVector1 * *(float*)(WayPoint + 20) * DelT) + *((float*)This + 23);
	*((float*)This + 24) = (fTourDirVector2 * *(float*)(WayPoint + 20) * DelT) + *((float*)This + 24);
}

void UpdatePlaySpeed(int AnimationFrame, float Speed)
{
	float DelT = AnimationFrameConstant * DelTtime;

	if (AnimationFrameConstant < 45)
	{
		DelT = 1.0f;
	}

	*(float*)AnimationFrame += (Speed * DelT);
}

__declspec(naked) void CCameraMove::CameraTourWay()
{
	static DWORD addr = 0x004DEA1B;

	_asm
	{
		push    ecx
		fld     dword ptr ss : [ebp - 0x34]
		fstp    dword ptr ss : [esp]
		push    ecx
		fld     dword ptr ss : [ebp - 0x38]
		fstp    dword ptr ss : [esp]
		push    ecx
		fld     dword ptr ss : [ebp - 0x24]
		fstp    dword ptr ss : [esp]
		push    ecx
		fld     dword ptr ss : [ebp - 0x28]
		fstp    dword ptr ss : [esp]
		mov     eax, dword ptr ss : [ebp - 0xC]
		push    eax //-- push 2
		mov     edx, dword ptr ss : [ebp - 0x88]
		push    edx //-- push 1
		call[UpdateTourWayPoint]
		JMP[addr]
	}
}

__declspec(naked) void TestingPlayAnimation()
{
	static DWORD addr = 0x00545211;

	_asm
	{
		push    edx
		fld     dword ptr ss : [ebp + 0x14]
		fstp    dword ptr ss : [esp]
		mov     eax, dword ptr ss : [ebp + 0x8]
		push    eax
		call[UpdatePlaySpeed]
		JMP[addr]
	}
}

//void __declspec(naked) FixEffects()
//{
//	static DWORD JmpBack = 0x0062F6CA;
//
//	_asm
//	{
//		Cmp Dword Ptr Ds : [0x00E61E18], 0;
//		Je EXIT;
//		Cmp Dword Ptr Ds : [0x00E61E18], 3;
//		Je EXIT;
//		Push Dword Ptr[0xD3D5E4];
//		Jmp JmpBack;
//	EXIT:
//		Push Dword Ptr[0xD3D5D4];
//		Jmp JmpBack;
//	}
//}



void fCameraMoveAccel(int This)
{
	*(float*)(This + 20) = 48.f;
}

void __declspec(naked) RotateCameraTourWay()
{
	static DWORD JmpBack = 0x004DE536;
	static float fSpeed = 1.f;

	fSpeed = 1.f * AnimationFrameConstant * DelTtime;

	_asm
	{
		mov     eax, dword ptr ss : [ebp - 0xC]
		push    eax //-- push 2
		call[fCameraMoveAccel]
		fld     dword ptr ds : [fSpeed]
		fstp    dword ptr ss : [ebp - 0x30]
		Jmp     JmpBack;
	}
}

int activespeedmove = 0;

void CCameraMove::CPhysicsCloth_InitForces(int This)
{
	int m_iNumVertices = *(int*)(This + 52);
	int m_iNumHor = *(int*)(This + 44);
	int m_pVertices = *(int*)(This + 56);

	int iSeed = ((MoveSceneFrame / 10) * 101) % m_iNumVertices;

	int o = *(int*)(This + 4);
	int Type = *(int*)(o + 48);
	WORD CurrentAction = *(WORD*)(o + 18);

	activespeedmove = 0;

	if (Type == 1163 &&
		((CurrentAction >= 15 && CurrentAction <= 24)  //-- PLAYER_WALK_MALE //-- PLAYER_WALK_SWIM
			|| (CurrentAction >= 34 && CurrentAction <= 37)   //-- PLAYER_FLY //-- PLAYER_RUN_RIDE_WEAPON
			|| CurrentAction == 74   //-- PLAYER_FLY_RIDE
			|| CurrentAction == 75   //-- PLAYER_FLY_RIDE_WEAPON
			|| CurrentAction == 77   //-- PLAYER_DARKLORD_WALK
			|| CurrentAction == 79   //-- PLAYER_RUN_RIDE_HORSE
			|| (CurrentAction >= 110 && CurrentAction <= 121)  //-- PLAYER_FENRIR_RUN
			|| (CurrentAction >= 126 && CurrentAction <= 129)  //-- PLAYER_FENRIR_WALK
			|| CurrentAction == 143   //-- PLAYER_WALK_TWO_HAND_SWORD_TWO
			|| CurrentAction == 144   //-- PLAYER_RUN_TWO_HAND_SWORD_TWO

			|| CurrentAction == 25	//run wing
			|| CurrentAction == 32	//run wing
			|| CurrentAction == 27	//run wing
			|| CurrentAction == 30	//run wing
			|| CurrentAction == 34	//run wing
			|| CurrentAction == 11	//run wing
			|| CurrentAction == 35	//run wing
			|| CurrentAction == 31	//run wing
			|| CurrentAction == 12	//run wing
			|| CurrentAction == 53	//run wing
			|| CurrentAction == 52	//run wing
			))
	{
		activespeedmove = 1.f;
	}

	for (int iVertex = 0; iVertex < m_iNumVertices; ++iVertex)
	{
		float m_fWind = *(float*)(This + 68);
		int m_dwType = *(DWORD*)(This + 20);

		UpdateForce(m_pVertices + iVertex * 160, abs(iSeed % m_iNumHor - iVertex % m_iNumHor) + abs(iSeed / m_iNumHor - iVertex / m_iNumHor), m_dwType, m_fWind);
	}
}

void CCameraMove::CPhysicsVertex_Move(CPhysicsVertex This, float fTime)
{
	float fSpeed = 1.f;
	float Time = fTime;

	if (AnimationFrameConstant > 25)
	{
		fSpeed = AnimationFrameConstant * DelTtime;
		Time *= fSpeed;
	}

	if (!(This->m_byState & PVS_FIXEDPOS) && activespeedmove == FALSE)
	{
		for (int i = 0; i < 3; ++i)
		{
			This->m_vVel[i] += (This->m_vForce[i] * s_fInvOfMass * fTime) * fSpeed;
			This->m_vPos[i] += (This->m_vVel[i] * Time);
		}
	}
}

void RenderCharacterBackItem(int w, int o, int Type)
{
	float PlaySpeed = (AnimationFrameConstant * DelTtime);

	PlaySpeed = 0.40f; //fix?

	if (Type == 1)
	{
		if (*(WORD*)(o + 18) != 34 && *(WORD*)(o + 18) != 35)
			*(float*)(w + 20) = 0.25f * PlaySpeed;
		else
			*(float*)(w + 20) = 0.55f * PlaySpeed;
	}

	if (Type == 2)
	{
		if (*(WORD*)(o + 18) != 34 && *(WORD*)(o + 18) != 35)
			*(float*)(w + 20) = 0.25f * PlaySpeed;
		else
			*(float*)(w + 20) = 0.55f * PlaySpeed;
	}

	if (Type == 3)
	{
		if (*(WORD*)(o + 18) != 34 && *(WORD*)(o + 18) != 35)
		{
			*(float*)(w + 20) = 0.25f * PlaySpeed;
		}
		else if (*(WORD*)w == 7351)
		{
			*(float*)(w + 20) = 0.4f * PlaySpeed;
		}
		else
		{
			*(float*)(w + 20) = 0.55f * PlaySpeed;
		}
	}
}

void __declspec(naked) SpeedCharacterBackItem1()
{
	static DWORD JmpBack = 0x005882A5;

	_asm
	{
		push    1
		mov     edx, dword ptr ss : [ebp + 0xC]
		push    edx
		mov     eax, dword ptr ss : [ebp - 0x20]
		push    eax
		call[RenderCharacterBackItem]
		Jmp     JmpBack
	}
}

void __declspec(naked) SpeedCharacterBackItem2()
{
	static DWORD JmpBack = 0x0058848E;

	_asm
	{
		push    2
		mov     edx, dword ptr ss : [ebp + 0xC]
		push    edx
		mov     eax, dword ptr ss : [ebp - 0x5C]
		push    eax
		call[RenderCharacterBackItem]
		Jmp     JmpBack
	}
}

void __declspec(naked) SpeedCharacterBackItem3()
{
	static DWORD JmpBack = 0x005885AA;

	_asm
	{
		push    3
		mov     eax, dword ptr ss : [ebp + 0xC]
		push    eax
		mov     ecx, dword ptr ss : [ebp - 0x6C]
		push    ecx
		call[RenderCharacterBackItem]
		Jmp     JmpBack
	}
}
#define CPhysicsClothMove						((BOOL(__thiscall*)(int This, float a2)) 0x0051E2C0)
//----- (0051E270) --------------------------------------------------------
int __thiscall CCameraMove::CPhysicsClothMove2(void* This, float a2, int a3)
{
	//int i; // [esp+8h] [ebp-4h]
	//a3 = 2;
	//for (i = 0; i < a3; ++i)
	{
		if (!CPhysicsClothMove((int)This, a2))
			return 0;
	}
	return 1;
}


//----- (00545180) BMD::PlayAnimation--------------------------------------------------------
char __thiscall CCameraMove::PlayAnimation(int Bis, int a2, int a3, int a4, float a5, int a6, int a7)
{

	float DelT = AnimationFrameConstant * DelTtime;

	if (AnimationFrameConstant < 45)
	{
		DelT = 1.0f;
	}
	signed int v8; // eax
	int v10; // [esp+18h] [ebp-10h]
	float v11; // [esp+1Ch] [ebp-Ch]
	char v12; // [esp+23h] [ebp-5h]
	signed int v13; // [esp+24h] [ebp-4h]

	v12 = 1;
	if (!a2 || !a3 || !a4 || *(__int16*)(Bis + 38) > 0 && *(unsigned __int16*)(Bis + 160) >= *(__int16*)(Bis + 38))
		return 1;
	if (!*(WORD*)(Bis + 38) || *(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8) <= 1)
		return 1;

	v13 = (signed int)(*(float*)a2);

	*(float*)a2 = *(float*)a2 + (a5 * DelT); // Speed Fix

	if (v13 != (signed int)(*(float*)a2))
	{
		*(WORD*)a4 = *(WORD*)(Bis + 160);
		*(float*)a3 = (float)v13;
	}
	if (*(float*)a2 <= 0.0)
		*(float*)a2 = (double)*(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8)
		- 1.0
		+ *(float*)a2;
	if (*(BYTE*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160)))
	{
		if (*(float*)a2 >= (double)*(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8))
		{
			*(float*)a2 = (double)*(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8)
				- 0.009999999776482582;
			v12 = 0;
		}
	}
	else
	{
		if (*(BYTE*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 10))
			v10 = *(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8) - 1;
		else
			v10 = *(__int16*)(*(DWORD*)(Bis + 48) + 16 * *(unsigned __int16*)(Bis + 160) + 8);
		if (*(DWORD*)(0xE609E8) == 4)
		{
			v11 = *(float*)a2 + 2.0;
		}
		else if (*(DWORD*)(0xE61E18) == 39 && *(WORD*)(Bis + 160) == 7)
		{
			v11 = *(float*)a2 + 1.0;
		}
		else
		{
			v11 = *(float*)a2;
		}
		if (v11 >= (double)v10)
		{
			v8 = (signed int)(*(float*)a2);
			*(float*)a2 = (double)(v8 % v10) + *(float*)a2 - (double)v8;
			v12 = 0;
		}
	}
	*(float*)(Bis + 164) = *(float*)a2;
	*(WORD*)(Bis + 168) = (signed int)(*(float*)(Bis + 164));
	return v12;
}
void CCameraMove::Init()
{
	//-- 60 FPS: 0x11
	//-- 40 FPS: 0x1A
	//-- 25 FPS: 0x28
	//SetByte(0x004DA3AC + 3, 0x11); //-- 40
	//SetDword(0x004DA3B2 + 1, 0x11); //-- 40
	//SetDword(0x004DA3DD + 3, 0x11); //-- 40
	SetByte(0x0059788E + 1, 0x14); //-- Fix Notice Midd
	SetByte(0x00597895 + 2, 0xA); //-- Fix Notice Midd
	SetCompleteHook(0xE8, 0x004D9D0E, &CalcFPS); //ok
	//SetCompleteHook(0xE9, 0x0062F6C5, &FixEffects);
	SetCompleteHook(0xE9, 0x00588277, &SpeedCharacterBackItem1);
	SetCompleteHook(0xE9, 0x00588460, &SpeedCharacterBackItem2);
	SetCompleteHook(0xE9, 0x00588560, &SpeedCharacterBackItem3);

	SetByte(0x00813BF1 + 3, 1); //-- Fix Tooltip SkillBar
	SetByte(0x004EBD01 + 6, 1); //-- Fix Tooltip Ancient
	//SetCompleteHook(0xE9, 0x00545204, &TestingPlayAnimation);

	SetCompleteHook(0xE9, 0x0051CB60, &CCameraMove::CPhysicsVertex_Move);
	//SetCompleteHook(0xE9, 0x0051E440, &CCameraMove::CPhysicsCloth_InitForces);

	SetCompleteHook(0xE9, 0x0051E270, &CCameraMove::CPhysicsClothMove2);

	//SetCompleteHook(0xE9, 0x00545180, &CCameraMove::PlayAnimation);
	//--
	//SetCompleteHook(0xE9, 0x004DE4E9, &RotateCameraTourWay);
	SetCompleteHook(0xE9, 0x004DE9AF, &CCameraMove::CameraTourWay);
}
#endif