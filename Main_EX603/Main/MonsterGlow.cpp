#include "stdafx.h"
#include "MonsterGlow.h"
#include "TMemory.h"
#include "Defines.h"
#include "Import.h"
#include "Util.h"
#include "CustomMonsterGlow.h"

//--
char RenderMonsterObjectMesh( int a1, int a2 )
{
	float v5; // ST58_4@2
	float v6; // ST50_4@2
	char result; // al@2
	float v8; // ST48_4@3
	float v9; // ST40_4@3
	float v10; // ST38_4@5
	float v11; // ST30_4@5
	float v12; // ST28_4@6
	float v13; // ST20_4@6

	switch ( *(DWORD *)(a1 + 48) )
	{
		case 0x2E9:
			BeginRender(1.0);
			*(float *)(a2 + 72) = 0.89999998;
			*(float *)(a2 + 76) = 0.89999998;
			*(float *)(a2 + 80) = 0.89999998;
			*(BYTE *)(a2 + 136) = 0;
			v5 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;
			v6 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;
			RenderMesh(a2, 0, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), v6, v5, -1);
			RenderMesh(
				a2,
				0,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			RenderMesh(
				a2,
				1,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			EndRender( );
			result = 1;
			break;
		case 0x2EA:
			BeginRender(1.0);
			*(float *)(a2 + 72) = 0.89999998;
			*(float *)(a2 + 76) = 0.89999998;
			*(float *)(a2 + 80) = 0.89999998;
			RenderMesh(
				a2,
				0,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			RenderMesh(
				a2,
				1,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			RenderMesh(
				a2,
				2,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = 0;
			v8 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0006000000284984708;
			v9 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0006000000284984708;
			RenderMesh(a2, 3, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), v9, v8, -1);
			RenderMesh(
				a2,
				3,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			EndRender( );
			result = 1;
			break;
		case 0x2ED:
			BeginRender(1.0);
			*(float *)(a2 + 72) = 1.0;
			*(float *)(a2 + 76) = 1.0;
			*(float *)(a2 + 80) = 1.0;
			*(BYTE *)(a2 + 136) = 0;
			RenderMesh(
				a2,
				0,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(float *)(a2 + 72) = 1.0;
			*(float *)(a2 + 76) = 0.0;
			*(float *)(a2 + 80) = 0.0;
			RenderMesh(
				a2,
				0,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			*(float *)(a2 + 72) = 1.0;
			*(float *)(a2 + 76) = 1.0;
			*(float *)(a2 + 80) = 1.0;
			RenderMesh(
				a2,
				1,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = 1;
			RenderMesh(
				a2,
				2,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(float *)(a2 + 72) = 0.5;
			*(float *)(a2 + 76) = 0.0;
			*(float *)(a2 + 80) = 0.0;
			RenderMesh(
				a2,
				2,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			EndRender( );
			result = 1;
			break;
		case 0x346:
			BeginRender(1.0);
			*(float *)(a2 + 72) = 0.89999998;
			*(float *)(a2 + 76) = 0.89999998;
			*(float *)(a2 + 80) = 0.89999998;
			RenderMesh(
				a2,
				0,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			RenderMesh(
				a2,
				1,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			RenderMesh(
				a2,
				2,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = 0;
			v10 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0006000000284984708;
			v11 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0006000000284984708;
			RenderMesh(a2, 3, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), v11, v10, -1);
			RenderMesh(
				a2,
				3,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			EndRender( );
			result = 1;
			break;
		case 0x347:
			BeginRender(1.0);
			*(float *)(a2 + 72) = 0.89999998;
			*(float *)(a2 + 76) = 0.89999998;
			*(float *)(a2 + 80) = 0.89999998;
			*(BYTE *)(a2 + 136) = 0;
			v12 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;
			v13 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;
			RenderMesh(a2, 0, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), v13, v12, -1);
			RenderMesh(
				a2,
				0,
				70,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			*(BYTE *)(a2 + 136) = -1;
			RenderMesh(
				a2,
				1,
				2,
				*(float *)(a1 + 152),
				*(DWORD *)(a1 + 68),
				*(float *)(a1 + 100),
				*(float *)(a1 + 104),
				*(float *)(a1 + 108),
				-1);
			EndRender( );
			result = 1;
			break;
		default:
			result = 0;
		
			if(  gCustomMonsterGlow.CheckCustomByMonster(MonsterID(*(DWORD *)(a1 + 48))) )
			{
				BeginRender(1.0);

				*(BYTE *)(a2 + 136) = 0;
				for( int k = 0 ; k < 12 ; k++ )
				{
					RenderMesh(a2, k, 2, *(float *)(a1 + 152), *(DWORD *)(a1 + 68), *(float *)(a1 + 100), v13, v12, -1);
				}
			}

			for(std::vector<CUSTOM_MONSTERGLOW_INFO>::iterator it = gCustomMonsterGlow.m_CustomGlowInfo.begin(); it != gCustomMonsterGlow.m_CustomGlowInfo.end(); it++)
			{
				if(it->MonsterID == MonsterID(*(DWORD *)(a1 + 48)))
				{

					*(float *)(a2 + 72) = (float)(it->ColorR / 255.0f);
					*(float *)(a2 + 76) = (float)(it->ColorG / 255.0f);
					*(float *)(a2 + 80) = (float)(it->ColorB / 255.0f);

					v5 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;
					v6 = (double)(-(int) *(float*)0x5EF5A1C % 10000) * 0.0003000000142492354;

					RenderMesh(
						a2,
						it->EffectIndex,
						68,
						*(float *)(a1 + 152),
						*(DWORD *)(a1 + 68),
						*(float *)(a1 + 100),
						v6,
						v5,
						32042);

					RenderMesh(
						a2,
						it->EffectIndex,
						72,
						*(float *)(a1 + 152),
						*(DWORD *)(a1 + 68),
						*(float *)(a1 + 100),
						v6,
						v5,
						32113);
				}
			}

			if(  gCustomMonsterGlow.CheckCustomByMonster( MonsterID(*(DWORD *)(a1 + 48)) ) )
			{
				*(BYTE *)(a2 + 136) = -1;
				EndRender( );
				result = 1;
			}
			break;
	}

	return result;
}

void __declspec(naked) GoldenMonster( )
{
	DWORD dwItem;
	static DWORD MonsterID;
	static DWORD Addr1_JMP = 0x005704EE;
	static DWORD Addr2_JMP = 0x0056FCF7;
	static int MonsterGolden;

	_asm
	{
		Mov edx, [EBP + 0x8]
		Movsx eax, word ptr[edx + 0x84]
		Mov MonsterID, eax
	}

	MonsterGolden = gCustomMonsterGlow.CheckCustomByMonsterGolden(MonsterID);

	if ( MonsterID == 38
		|| MonsterID == 43
		|| MonsterID == 44
		|| MonsterID == 52
		|| MonsterID == 59
		|| MonsterID == 67
		|| MonsterID >= 78 && MonsterID <= 83
		|| MonsterID >= 493 && MonsterID <= 502
		|| MonsterGolden != 0 ) 
	{
		_asm
		{
			JMP [Addr2_JMP]
		}
	}
	else
	{
		_asm
		{
			JMP [Addr1_JMP]
		}
	}
}

void __declspec(naked) GoldenMonster2( )
{
	static DWORD MonsterID;
	static DWORD Address1 = 0x005703A1;
	static DWORD Address2 = 0x0056FD73;
	static int MonsterGolden;

	_asm
	{
		Mov edx, [EBP + 0x8]
		Movsx eax, word ptr[edx + 0x84]
		Mov MonsterID, eax
	}

	MonsterGolden = gCustomMonsterGlow.CheckCustomByMonsterbrightness(MonsterID);

	if ( MonsterID == 43 || MonsterID == 44
		|| MonsterID >= 78 && MonsterID<=83
		|| MonsterID >= 493 && MonsterID <= 502
		|| MonsterGolden != 0 ) 
	{
		_asm
		{
			JMP Address2
		}
	}
	else
	{
		_asm
		{
			JMP Address1
		}
	}
}

void InitloadGlow()
{
	//--
	SetCompleteHook(0xE8, 0x008C5BB5, &RenderMonsterObjectMesh);
	//--
	SetRange(0x0056FC5E, 10, ASM::NOP);
	SetOp(0x0056FC5E, (LPVOID)GoldenMonster, ASM::JMP); // enable golden monster 7
	//--
	SetRange(0x0056FD1A, 10, ASM::NOP);
	SetOp(0x0056FD1A, (LPVOID)GoldenMonster2, ASM::JMP); // more bright 9
}