#include "stdafx.h"
#include "CustomInterface.h"
#include "WideScreen.h"
#include "Import.h"
#include "Util.h"
#include "OffTrade.h"
#include "Interface.h"
#include "Defines.h"
#include "CChatEx.h"
#include "PrintPlayer.h"
#include "TMemory.h"
#include "SItemOption.h"
#include "User.h"
#include "InterfaceElemental.h"
#include "NewUISystem.h"
#include "Offset.h"
#include "Protect.h"
#include "InterfaceS8AdvancedUI.h"

signed int Bsub_9CEBF0(double a1)
{
	return (signed int)a1;
}

CInterface gInterfaceBar;
int TimerPush1;
int TimerPush2;
int JCPageSlotSkill = 0;

bool JCEventButton(int x, int y, int w, int h)
{
	int JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	return pCheckMouseOver(x, y, w, h) && *(BYTE*)0x8793386;
}

void WideAttributoBP(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	int JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	RenderBitmap(31299, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void WideAttributoSD(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	float JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	RenderBitmap(31300, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

//int ReHP = 55000;
void WideRedHP(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	float JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	RenderBitmap(31298, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	/*if(ReHP >= 55000){
	RenderBitmap(ReHP, PosX + JCResto, PosY, Width,  Height,  Arg6,  Arg7,  ScaleX,  ScaleY,  ScaleSize,  ScalePosition, ScaleAlpha);
	ReHP++;
	if(ReHP == 55024){ReHP = 55000;}
	}*/

}

//int ReHPG = 55089;
void WideGreenHP(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	float JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	RenderBitmap(31297, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	//if(ReHPG >= 55089){
	//	RenderBitmap(ReHPG, PosX + JCResto, PosY, Width,  Height,  Arg6,  Arg7,  ScaleX,  ScaleY,  ScaleSize,  ScalePosition, ScaleAlpha);
	//	ReHPG++;
	//	if(ReHPG == 55099){ReHPG = 55089;}
	//}
}

//int ReMP = 55025;
void WideBlueMP(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	float JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	RenderBitmap(31296, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	/*if(ReMP >= 55025){
	RenderBitmap(ReMP, PosX + JCResto, PosY, Width,  Height,  Arg6,  Arg7,  ScaleX,  ScaleY,  ScaleSize,  ScalePosition, ScaleAlpha);
	ReMP++;
	if(ReMP == 55049){ReMP = 55025;}
	}*/
}

void RenderGUI(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawGUI(ImageID, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height);
}

void InterfaceLeft(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int JCResto = Fix_DisplayWinExt;

	float x = PosX + JCResto - 70.28048780487805;
	RenderBitmap(CBImgDecor, x, Fix_DisplayHeightExt + PosY, 70.28048780487805, 51, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0.0);

	pDrawGUI(ImageID, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height);
}
void InterfaceMiddle(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int v38; // [sp+14h] [bp-28h]@1

	pDrawGUI(ImageID, PosX + Fix_DisplayWinExt, Fix_DisplayHeightExt + PosY, Width, Height);

	v38 = *(DWORD*)(GetInstance() + 28);

	ChangeButtonInfo2((char*)(v38 + 56), Fix_DisplayWinExt + 489, Fix_DisplayHeightExt + 429, 30, 41); //-- cashshop

	ChangeButtonInfo2((char*)(v38 + 228), Fix_DisplayWinExt + 519, Fix_DisplayHeightExt + 429, 30, 41); //-- character

	ChangeButtonInfo2((char*)(v38 + 400), Fix_DisplayWinExt + 549, Fix_DisplayHeightExt + 429, 30, 41); //-- inventario

	ChangeButtonInfo2((char*)(v38 + 572), Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41); //-- friend list

	ChangeButtonInfo2((char*)(v38 + 744), Fix_DisplayWinExt + 609, Fix_DisplayHeightExt + 429, 30, 41); //-- system config

}
void InterfaceRight(int ImageID, float PosX, float PosY, float Width, float Height)
{
	RenderBitmap(CBImgDecor, PosX + Fix_DisplayWinExt + Width, Fix_DisplayHeightExt + PosY, 70.28048780487805, Height, 0.8785000443, 0.0, -0.8785000443, 0.6409999728, 1, 1, 0.0);

	pDrawGUI(ImageID, Fix_DisplayWinExt + PosX, Fix_DisplayHeightExt + PosY, Width, Height);

	/*if (gMuHelper.PkMode != true)
	{
		pDrawButton(531022, Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41, 0.0, 0);
	}
	else
	{
		pDrawButton(531022, Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41, 0.0, 41);

		gInterface.DrawFormat(eBlue, 5, 87, 200, 1, "Chế độ PK đang (bật)");

	}

	if (pCheckMouseOver(Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41))
	{

		gInterface.DrawToolTip(Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 413, "Chuyển Chế Độ PK");

		if (pIsKeyRelease(VK_LBUTTON))
		{
			if (GetTickCount() >= gRenderMap.DataMap.TimerEventVK + 200)
			{
				pDrawButton(531022, Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41, 0.0, 82);
				if (gMuHelper.PkMode != true)
				{
					gMuHelper.PkMode = true;

				}
				else
				{
					gMuHelper.PkMode = false;

					pDrawButton(531022, Fix_DisplayWinExt + 579, Fix_DisplayHeightExt + 429, 30, 41, 0.0, 41);
				}

				gRenderMap.DataMap.TimerEventVK = GetTickCount();
			}

		}
	}*/
}

void JCRenderBarExp(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	RenderBitmap(ImageID, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void JCJCRenderBarExpAdd(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawBarForm(PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height, Arg5, Arg6);
}

bool JCCheckMouseTooltip(int a1, int a2, int a3, int a4)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	return pCheckMouseOver(a1 + JCResto, Fix_DisplayHeightExt + a2, a3, a4);
}

int JCTooltipDraw(int X, int Y, LPCSTR Text)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	return pDrawToolTip(X + JCResto, Fix_DisplayHeightExt + Y, Text);
}

double JCRenderNumber(float a1, float a2, int a3, float a4)
{
	double result; // st7@2
	float v5; // ST44_4@5
	float v6; // ST38_4@5
	signed int i; // [sp+38h] [bp-30h]@3
	float v8; // [sp+3Ch] [bp-2Ch]@3
	signed int v9; // [sp+44h] [bp-24h]@3
	char v10[32]; // [sp+48h] [bp-20h]@3
	float v11; // [sp+70h] [bp+8h]@3

	EnableAlphaTest(1);
	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290) * 12.0;
		itoa(a3, v10, 10);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.4000000119209290) * 16.0;
			RenderBitmap(31337, v11, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}

	return result;
}

void RenderNumber(float a4, float a5, int Number, float a7)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawGUI(87969, JCResto + 0.0, Fix_DisplayHeightExt + 480.0 - 12.0, 640.0, 12.0);

	JCRenderNumber(a4 + JCResto, Fix_DisplayHeightExt + a5, Number, a7);
}

void RenderButtonQuest(DWORD ModelID, float X, float Y, float W, float H, float CurrentX, float CurrentY)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawButton(ModelID, X + JCResto, Fix_DisplayHeightExt + Y, W, H, CurrentX, CurrentY);
}

__declspec(naked) void RenderSlotQ()
{
	static DWORD Addr_JMP = 0x00895A73;
	static int JCResto;
	static int JCResto1;
	static float RenderPotionX = 10.0f;
	static float RenderNumberX = 30.0f;
	static float RenderPotionY = 453.0f;
	static float RenderNumberY = 445.0f;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	JCResto1 = Fix_DisplayHeightExt;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	RenderNumberY += JCResto1;
	RenderPotionY += JCResto1;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x18] ; |
		JMP[Addr_JMP]; \main1.008977D0
	}
}

__declspec(naked) void RenderSlotW()
{
	static DWORD Addr_JMP = 0x00895AE8;
	static float RenderPotionX = 48.0f;
	static float RenderNumberX = 68.0f;
	static int JCResto;
	static int JCResto1;
	static float RenderPotionY = 445.0f;
	static float RenderNumberY = 453.0f;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	JCResto1 = Fix_DisplayHeightExt;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	RenderNumberY += JCResto1;
	RenderPotionY += JCResto1;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x20] ; |
		JMP[Addr_JMP]; \main1.00897BD0
	}
}

__declspec(naked) void RenderSlotE()
{
	static DWORD Addr_JMP = 0x00895B5D;
	static float RenderPotionX = 86.0f;
	static float RenderNumberX = 106.0f;
	static int JCResto;
	static int JCResto1;
	static float RenderPotionY = 445.0f;
	static float RenderNumberY = 453.0f;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	JCResto1 = Fix_DisplayHeightExt;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	RenderNumberY += JCResto1;
	RenderPotionY += JCResto1;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x28] ; |
		JMP[Addr_JMP]; \main1.00895760
	}
}

__declspec(naked) void RenderSlotR()
{
	static DWORD Addr_JMP = 0x00895BD2;
	static float RenderPotionX = 124.0f;
	static float RenderNumberX = 144.0f;
	static int JCResto;
	static int JCResto1;
	static float RenderPotionY = 445.0f;
	static float RenderNumberY = 453.0f;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	JCResto1 = Fix_DisplayHeightExt;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	RenderNumberY += JCResto1;
	RenderPotionY += JCResto1;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x30] ; |
		JMP[Addr_JMP]; \main1.008979C0
	}
}


bool JCEventMouseSkill(int a1)
{
	bool result; // al@2
	unsigned __int8 v5; // ST4F_1@3
	int v6; // ST0C_4@7
	int v7; // ST08_4@7
	int v8; // ST04_4@7
	int v9; // eax@7
	int v10; // ST0C_4@11
	int v11; // ST08_4@11
	int v12; // ST04_4@11
	int v13; // eax@11
	int v14; // ST0C_4@16
	int v15; // ST08_4@16
	int v16; // ST04_4@16
	int v17; // eax@16
	int v18; // ST0C_4@21
	int v19; // ST08_4@21
	int v20; // ST04_4@21
	int v21; // eax@21
	int v22; // ST0C_4@30
	int v23; // ST08_4@30
	int v24; // ST04_4@30
	int v25; // eax@30
	int v26; // ST0C_4@34
	int v27; // ST08_4@34
	int v28; // ST04_4@34
	int v29; // eax@34
	int v30; // ST0C_4@38
	int v31; // ST08_4@38
	int v32; // ST04_4@38
	int v33; // eax@38
	int v34; // ST0C_4@45
	int v35; // ST08_4@45
	int v36; // ST04_4@45
	int v37; // eax@45
	int v38; // ST0C_4@68
	int v39; // ST08_4@68
	int v40; // ST04_4@68
	int v41; // eax@68
	int v42; // ST0C_4@92
	int v43; // ST08_4@92
	int v44; // ST04_4@92
	int v45; // eax@92
	int v46; // ST0C_4@98
	int v47; // ST08_4@98
	int v48; // ST04_4@98
	int v49; // eax@98
	int v50; // ST0C_4@102
	int v51; // ST08_4@102
	int v52; // ST04_4@102
	int v53; // eax@102
	int v54; // ST0C_4@107
	int v55; // ST08_4@107
	int v56; // ST04_4@107
	int v57; // eax@107
	int v58; // ST0C_4@118
	int v59; // ST08_4@118
	int v60; // ST04_4@118
	int v61; // eax@118
	int v62; // [sp+Ch] [bp-54h]@1
	signed int j; // [sp+10h] [bp-50h]@116
	int v64; // [sp+18h] [bp-48h]@84
	signed int i; // [sp+20h] [bp-40h]@73
	unsigned __int16 v66; // [sp+24h] [bp-3Ch]@53
	signed int v67; // [sp+2Ch] [bp-34h]@40
	signed int v68; // [sp+30h] [bp-30h]@40
	unsigned __int16 v69; // [sp+38h] [bp-28h]@76
	float v70; // [sp+40h] [bp-20h]@5
	float v71; // [sp+40h] [bp-20h]@28
	float v72; // [sp+40h] [bp-20h]@40
	float v73; // [sp+40h] [bp-20h]@73
	float v74; // [sp+40h] [bp-20h]@116
	float v75; // [sp+44h] [bp-1Ch]@5
	float v76; // [sp+44h] [bp-1Ch]@28
	float v77; // [sp+44h] [bp-1Ch]@73
	char v78; // [sp+4Bh] [bp-15h]@73
	float v79; // [sp+4Ch] [bp-14h]@73
	signed int v80; // [sp+50h] [bp-10h]@73
	int v81; // [sp+54h] [bp-Ch]@73
	float v82; // [sp+58h] [bp-8h]@5
	float v83; // [sp+58h] [bp-8h]@28
	float v84; // [sp+58h] [bp-8h]@40
	float v85; // [sp+58h] [bp-8h]@85
	float v86; // [sp+58h] [bp-8h]@116
	float v87; // [sp+5Ch] [bp-4h]@5
	float v88; // [sp+5Ch] [bp-4h]@28
	float v89; // [sp+5Ch] [bp-4h]@40
	float v90; // [sp+5Ch] [bp-4h]@73
	float v91; // [sp+5Ch] [bp-4h]@116
	int JCResto; // eax@1

	v62 = a1;
	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (pCheckEffectPlayer((DWORD*)(dword_7BC4F04 + 1260), 98))
	{
		*(BYTE*)(v62 + 64) = 0;
		result = 1;
	}
	else
	{
		v5 = *(BYTE*)(dword_8128AC8 + 118);
		*(BYTE*)(v62 + 65) = 0;
		if ((signed int)v5 > 0)
		{
			//-- skill using
			if (gProtect.m_MainInfo.CustomInterfaceType == Season1
				|| gProtect.m_MainInfo.CustomInterfaceType == Season2)
			{
				v82 = 310.0f + JCResto;
				v87 = Fix_DisplayHeightExt + 447.05;
				v70 = 20.0;
				v75 = 28.0;
			}
			else if (gProtect.m_MainInfo.CustomInterfaceType == Ex700
				|| gProtect.m_MainInfo.CustomInterfaceType == Legends || gProtect.m_MainInfo.CustomInterfaceType == Diablo)
			{
				//-- skill using
				v82 = JCResto + 308.0; //-- x
				v87 = Fix_DisplayHeightExt + 445.5; //--y
				v70 = 20.0; //-- w
				v75 = 22.0; //-- h
			}
			else
			{
				v82 = 385.0 + JCResto;
				v87 = Fix_DisplayHeightExt + 431.0;
				v70 = 32.0;
				v75 = 38.0;
			}

			if (*(DWORD*)(v62 + 80)
				|| byte_8793384
				|| (v6 = sub_9CEBF0(v75),
					v7 = sub_9CEBF0(v70),
					v8 = sub_9CEBF0(v87),
					v9 = sub_9CEBF0(v82),
					pCheckMouseOver(v9, v8, v7, v6) != 1))
			{
				if (*(DWORD*)(v62 + 80) != 1
					|| byte_8793384
					|| (v10 = sub_9CEBF0(v75),
						v11 = sub_9CEBF0(v70),
						v12 = sub_9CEBF0(v87),
						v13 = sub_9CEBF0(v82),
						pCheckMouseOver(v13, v12, v11, v10)))
				{
					if (*(DWORD*)(v62 + 80) != 1
						|| byte_8793384 != 1 && byte_8793380 != 1
						|| (v14 = (int)(v75),
							v15 = (int)(v70),
							v16 = (int)(v87),
							v17 = (int)(v82),
							pCheckMouseOver(v17, v16, v15, v14) != 1))
					{
						if (*(DWORD*)(v62 + 80) != 2 || byte_8793384 || byte_8793380)
						{
							if (*(DWORD*)(v62 + 80) == 1)
							{
								*(BYTE*)(v62 + 65) = 1;
								*(DWORD*)(v62 + 68) = *(BYTE*)(dword_7BC4F04 + 50);
								*(DWORD*)(v62 + 72) = (int)(v82 - 5.0);
								*(DWORD*)(v62 + 76) = (int)(v87);
								result = 0;
							}
							else if (*(DWORD*)(v62 + 80) == 2)
							{
								result = 0;
							}
							else
							{
								//-- skill bar
								if (gProtect.m_MainInfo.CustomInterfaceType == Season1
									|| gProtect.m_MainInfo.CustomInterfaceType == Season2)
								{
									v88 = Fix_DisplayHeightExt + 490.0;
									v71 = 160.0;
									v76 = 38.0;
									v83 = 222.0 + JCResto;
								}
								else if (gProtect.m_MainInfo.CustomInterfaceType == Ex700
									|| gProtect.m_MainInfo.CustomInterfaceType == Legends || gProtect.m_MainInfo.CustomInterfaceType == Diablo)
								{
									v83 = JCResto + 331.5; //-- x
									v88 = Fix_DisplayHeightExt + 443.5; //-- y
									v71 = 112.5; //-- width
									v76 = 38.0; //-- height
								}
								else
								{
									v88 = Fix_DisplayHeightExt + 431.0;
									v71 = 160.0;
									v76 = 38.0;
									v83 = 222.0 + JCResto;
								}

								if (*(DWORD*)(v62 + 80)
									|| byte_8793384
									|| (v22 = sub_9CEBF0(v76),
										v23 = sub_9CEBF0(v71),
										v24 = sub_9CEBF0(v88),
										v25 = sub_9CEBF0(v83),
										pCheckMouseOver(v25, v24, v23, v22) != 1))
								{
									if (*(DWORD*)(v62 + 80) != 3
										|| byte_8793384
										|| (v26 = sub_9CEBF0(v76),
											v27 = sub_9CEBF0(v71),
											v28 = sub_9CEBF0(v88),
											v29 = sub_9CEBF0(v83),
											pCheckMouseOver(v29, v28, v27, v26)))
									{
										if (*(DWORD*)(v62 + 80) != 3
											|| byte_8793384 != 1
											|| (v30 = sub_9CEBF0(v76),
												v31 = sub_9CEBF0(v71),
												v32 = sub_9CEBF0(v88),
												v33 = sub_9CEBF0(v83),
												pCheckMouseOver(v33, v32, v31, v30) != 1))
										{
											if (gProtect.m_MainInfo.CustomInterfaceType == Season1
												|| gProtect.m_MainInfo.CustomInterfaceType == Season2)
											{
												v84 = 190.0 + JCResto;
												v89 = Fix_DisplayHeightExt + 490.0;
												v72 = 32.0;
												v68 = 0;
											}
											else if (gProtect.m_MainInfo.CustomInterfaceType == Ex700
												|| gProtect.m_MainInfo.CustomInterfaceType == Legends || gProtect.m_MainInfo.CustomInterfaceType == Diablo)
											{
												v84 = JCResto + 309.0; //-- x
												v89 = Fix_DisplayHeightExt + 443.5; //-- y
												v72 = 22.5; //-- witdh
												v68 = 0; //-- height
											}
											else
											{
												v84 = 190.0 + JCResto;
												v89 = Fix_DisplayHeightExt + 431.0;
												v72 = 32.0;
												v68 = 0;
											}
											v67 = *(BYTE*)(v62 + 20) != 1 ? 1 : 6;
											while (v68 < 5)
											{
												v84 = v84 + v72;
												if (v67 == 10)
													v67 = 0;
												v34 = (int)((float)38.0);
												v35 = (int)(v72);
												v36 = (int)(v89);
												v37 = (int)(v84);
												if (pCheckMouseOver(v37, v36, v35, v34) == 1)
												{
													if (*(DWORD*)(v62 + 4 * v67 + 24) == -1)
													{
														if (*(DWORD*)(v62 + 80) == 3)
														{
															*(BYTE*)(v62 + 65) = 0;
															*(DWORD*)(v62 + 68) = -1;
														}
														if (*(DWORD*)(v62 + 80) == 4 && !byte_8793384)
															*(DWORD*)(v62 + 80) = 0;
													}
													else
													{
														v66 = *(WORD*)(dword_8128AC8 + 2 * *(DWORD*)(v62 + 4 * v67 + 24) + 120);
														if (v66
															&& ((signed int)v66 < 67 || (signed int)v66 > 72)
															&& *(BYTE*)(dword_8128ABC + 88 * v66 + 55) != 3)
														{
															if (*(DWORD*)(v62 + 80) == 3)
															{
																*(BYTE*)(v62 + 65) = 1;
																*(DWORD*)(v62 + 68) = *(DWORD*)(v62 + 4 * v67 + 24);
																*(DWORD*)(v62 + 72) = (int)(v84 - 5.0);
																*(DWORD*)(v62 + 76) = (int)(v89);
																return 1;
															}
															if (*(DWORD*)(v62 + 80) == 4 && !byte_8793384)
															{
																if (*(DWORD*)(v62 + 68) == *(DWORD*)(v62 + 4 * v67 + 24))
																{
																	*(DWORD*)(v62 + 80) = 0;
																	*(WORD*)(v62 + 84) = *(WORD*)(dword_8128AC8
																		+ 2 * *(BYTE*)(dword_7BC4F04 + 50)
																		+ 120);
																	*(BYTE*)(dword_7BC4F04 + 50) = *(BYTE*)(v62 + 4 * v67 + 24);
																	PlayBuffer(25, 0, 0);
																	return 0;
																}
																*(DWORD*)(v62 + 80) = 0;
															}
														}
													}
												}
												++v68;
												++v67;
											}
											if (*(DWORD*)(v62 + 80) == 4)
											{
												if (byte_8793384
													|| (v38 = (int)((float)38.0),
														v39 = (int)((float)160.0),
														v40 = (int)((float)431.0),
														v41 = (int)((float)222.0),
														pCheckMouseOver(v41, v40, v39, v38)))
												{
													result = 0;
												}
												else
												{
													*(DWORD*)(v62 + 80) = 0;
													result = 1;
												}
											}
											else if (*(BYTE*)(v62 + 64))
											{
												v80 = 0;
												v78 = 0;
												v90 = Fix_DisplayHeightExt + 349.0; //-- y
												v73 = 24.0; //-- width
												v77 = 29.5; //-- height
												v79 = JCResto + 191.0; //-- x
												v81 = *(DWORD*)(v62 + 80);
												for (i = 0; i < 150; ++i)
												{
													v69 = *(WORD*)(dword_8128AC8 + 2 * i + 120);
													if (v69
														&& ((signed int)v69 < 67 || (signed int)v69 > 72)
														&& *(BYTE*)(dword_8128ABC + 88 * v69 + 55) != 3)
													{
														if (v80 == 10)
															v90 = v90 + v77;
														if (v80 == 20)
															v90 = v90 - v77;
														if (v80 >= 10 && v80 < 20)
														{
															v85 = (double)(v80 - 10) * v73 + v79;
														}
														else if (v80 >= 20)
														{
															v85 = (double)(v80 - 20) * v73 + v79;
														}
														else
														{
															v85 = (double)v80 * v73 + v79;
														}
														++v80;

														if (JCPageSlotSkill == 0)
														{
															if (v80 >= 21)
																continue;
														}
														else
														{
															if (v80 < 21)
																continue;
														}
														v42 = (int)(v77);
														v43 = (int)(v73);
														v44 = (int)(v90);
														v45 = (int)(v85);
														if (pCheckMouseOver(v45, v44, v43, v42) == 1)
														{
															v78 = 1;
															if (!*(DWORD*)(v62 + 80) && !byte_8793384)
															{
																*(DWORD*)(v62 + 80) = 5;
																break;
															}
														}
														if (*(DWORD*)(v62 + 80) == 5 && byte_8793384 == 1)
														{
															v46 = (int)(v77);
															v47 = (int)(v73);
															v48 = (int)(v90);
															v49 = (int)(v85);
															if (pCheckMouseOver(v49, v48, v47, v46) == 1)
															{
																*(DWORD*)(v62 + 80) = 6;
																break;
															}
														}
														if (*(DWORD*)(v62 + 80) == 5 && !byte_8793384)
														{
															v50 = (int)(v77);
															v51 = (int)(v73);
															v52 = (int)(v90);
															v53 = (int)(v85);
															if (pCheckMouseOver(v53, v52, v51, v50) == 1)
															{
																*(BYTE*)(v62 + 65) = 1;
																*(DWORD*)(v62 + 68) = i;
																*(DWORD*)(v62 + 72) = (int)(v85);
																*(DWORD*)(v62 + 76) = (int)(v90);
															}
														}
														if (*(DWORD*)(v62 + 80) == 6 && !byte_8793384 && *(DWORD*)(v62 + 68) == i)
														{
															v54 = (int)(v77);
															v55 = (int)(v73);
															v56 = (int)(v90);
															v57 = (int)(v85);
															if (pCheckMouseOver(v57, v56, v55, v54) == 1)
															{
																*(DWORD*)(v62 + 80) = 0;
																*(WORD*)(v62 + 84) = *(WORD*)(dword_8128AC8 + 2 * *(BYTE*)(dword_7BC4F04 + 50) + 120);
																*(BYTE*)(dword_7BC4F04 + 50) = i;
																*(BYTE*)(v62 + 64) = 0;
																PlayBuffer(25, 0, 0);
																return 0;
															}
														}
													}
												}
												if (v81 == *(DWORD*)(v62 + 80))
												{
													if (*(DWORD*)(dword_7BC4F04 + 676))
													{
														v86 = JCResto + 191.0;
														v91 = Fix_DisplayHeightExt + 379.0;
														v74 = 24.0;
														for (j = 150; j < 154; ++j)
														{
															v58 = (int)((float)38.0);
															v59 = (int)(v74);
															v60 = (int)(v91);
															v61 = (int)(v86);
															if (pCheckMouseOver(v61, v60, v59, v58) == 1)
															{
																v78 = 1;
																if (!*(DWORD*)(v62 + 80) && !byte_8793384)
																{
																	*(DWORD*)(v62 + 80) = 5;
																	return 1;
																}
																if (*(DWORD*)(v62 + 80) == 5 && byte_8793384 == 1)
																{
																	*(DWORD*)(v62 + 80) = 6;
																	return 0;
																}
																if (*(DWORD*)(v62 + 80) == 5)
																{
																	*(BYTE*)(v62 + 65) = 1;
																	*(DWORD*)(v62 + 68) = j;
																	*(DWORD*)(v62 + 72) = (int)(v86);
																	*(DWORD*)(v62 + 76) = (int)(v91);
																}
																if (*(DWORD*)(v62 + 80) == 6 && !byte_8793384 && *(DWORD*)(v62 + 68) == j)
																{
																	*(DWORD*)(v62 + 80) = 0;
																	*(WORD*)(v62 + 84) = *(WORD*)(dword_8128AC8 + 2 * *(BYTE*)(dword_7BC4F04 + 50) + 120);
																	*(BYTE*)(dword_7BC4F04 + 50) = j;
																	*(BYTE*)(v62 + 64) = 0;
																	PlayBuffer(25, 0, 0);
																	return 0;
																}
															}
															v86 = v86 + v74;
														}
													}
													if (v78 || *(DWORD*)(v62 + 80) != 5)
													{
														if (v78 || byte_8793384 || *(DWORD*)(v62 + 80) != 6)
														{
															if (*(DWORD*)(v62 + 80) == 6)
															{
																if (byte_8793384)
																{
																	result = 0;
																}
																else
																{
																	*(DWORD*)(v62 + 80) = 0;
																	result = 1;
																}
															}
															else
															{
																result = 1;
															}
														}
														else
														{
															*(DWORD*)(v62 + 80) = 0;
															result = 0;
														}
													}
													else
													{
														*(DWORD*)(v62 + 80) = 0;
														result = 1;
													}
												}
												else
												{
													result = !*(DWORD*)(v62 + 80) || *(DWORD*)(v62 + 80) == 5;
												}
											}
											else
											{
												result = 1;
											}
										}
										else
										{
											*(DWORD*)(v62 + 80) = 4;
											result = 0;
										}
									}
									else
									{
										*(DWORD*)(v62 + 80) = 0;
										result = 1;
									}
								}
								else
								{
									*(DWORD*)(v62 + 80) = 3;
									result = 1;
								}
							}
						}
						else
						{
							v18 = (int)(v75);
							v19 = (int)(v70);
							v20 = (int)(v87);
							v21 = (int)(v82);
							if (pCheckMouseOver(v21, v20, v19, v18) == 1)
							{
								*(BYTE*)(v62 + 64) = *(BYTE*)(v62 + 64) == 0;
								PlayBuffer(25, 0, 0);
								*(DWORD*)(v62 + 80) = 0;
								result = 0;
							}
							else
							{
								*(DWORD*)(v62 + 80) = 0;
								result = 1;
							}
						}
					}
					else
					{
						*(DWORD*)(v62 + 80) = 2;
						result = 0;
					}
				}
				else
				{
					*(DWORD*)(v62 + 80) = 0;
					result = 1;
				}
			}
			else
			{
				*(DWORD*)(v62 + 80) = 1;
				result = 1;
			}
		}
		else
		{
			result = 1;
		}
	}

	return result;
}
// 7BC4F04: using guessed type int dword_7BC4F04;
// 8128ABC: using guessed type int dword_8128ABC;
// 8128AC8: using guessed type int dword_8128AC8;
// 8793380: using guessed type char byte_8793380;
// 8793384: using guessed type char byte_8793384;
int JCSkillScale = 0;

void JCSkillSelectBar(int JCMainSelect)
{
	float v4; // ST18_4@17
	float v5; // ST14_4@17
	int v7; // [sp+20h] [bp-2Ch]@13
	int v8; // [sp+24h] [bp-28h]@7
	int v9; // [sp+2Ch] [bp-20h]@18
	signed int v10; // [sp+30h] [bp-1Ch]@2
	float v11; // [sp+34h] [bp-18h]@4
	signed int i; // [sp+40h] [bp-Ch]@4
	float v13; // [sp+44h] [bp-8h]@4
	float v14; // [sp+48h] [bp-4h]@4
	int JCResto; // eax@1

	JCMainSelect = *(DWORD*)(GetInstance() + 32);
	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (gProtect.m_MainInfo.CustomInterfaceType != Ex700
		&& gProtect.m_MainInfo.CustomInterfaceType != Legends && gProtect.m_MainInfo.CustomInterfaceType != Diablo)
	{

		if ((signed int)*(BYTE*)(dword_8128AC8 + 118) > 0)
		{
			v10 = 1;
			if (*(BYTE*)(JCMainSelect + 20))
				v10 = 6;
			v13 = 190.0 + JCResto;
			v14 = 431.0 + Fix_DisplayHeightExt;
			v11 = 32.0;

			if (gProtect.m_MainInfo.CustomInterfaceType != Season1
				&& gProtect.m_MainInfo.CustomInterfaceType != Season2)
			{
				for (i = 0; i < 5; ++i)
				{
					v13 = v13 + v11;
					v8 = i + v10;
					if (i + v10 == 10)
						v8 = 0;
					if (*(DWORD*)(JCMainSelect + 4 * v8 + 24) != -1
						&& (*(DWORD*)(JCMainSelect + 4 * v8 + 24) < 120
							|| *(DWORD*)(JCMainSelect + 4 * v8 + 24) >= 124
							|| *(DWORD*)(dword_7BC4F04 + 676)))
					{
						v7 = dword_8128ABC + 88 * *(WORD*)(dword_8128AC8 + 2 * *(DWORD*)(JCMainSelect + 4 * v8 + 24) + 120);
						if (!v7 || *(BYTE*)(v7 + 55) != 3)
						{
							if (*(BYTE*)(dword_7BC4F04 + 50) == *(DWORD*)(JCMainSelect + 4 * v8 + 24))
								pDrawGUI(31313, v13, v14, v11, 38.0);

							v4 = v14 + 6.0;
							v5 = v13 + 6.0;
							JCSkillScale = 0;
							JCLoadSkill(JCMainSelect, *(DWORD*)(JCMainSelect + 4 * v8 + 24), v5, v4, 20.0, 28.0);
						}
					}
				}
			}

			v9 = dword_8128ABC + 88 * *(WORD*)(dword_8128AC8 + 2 * *(BYTE*)(dword_7BC4F04 + 50) + 120);

			if (v9 && *(BYTE*)(v9 + 55) != 3)
			{
				JCSkillScale = 0;
				if (gProtect.m_MainInfo.CustomInterfaceType != Season1
					&& gProtect.m_MainInfo.CustomInterfaceType != Season2)
				{
					JCLoadSkill(JCMainSelect, *(BYTE*)(dword_7BC4F04 + 50), JCResto + 392.0, Fix_DisplayHeightExt + 437.0, 20.0, 28.0);
				}
				else
				{
					JCLoadSkill(JCMainSelect, *(BYTE*)(dword_7BC4F04 + 50), JCResto + 310.0f, 447.0 + Fix_DisplayHeightExt, 20.0, 28.0);
				}
			}
		}
	}
	else
	{
		if ((signed int)*(BYTE*)(dword_8128AC8 + 118) > 0)
		{
			v10 = 1;
			if (*(BYTE*)(JCMainSelect + 20))
				v10 = 6;
			v13 = JCResto + 309;
			v14 = Fix_DisplayHeightExt + 443.5f;
			v11 = 22.5;

			for (i = 0; i < 5; ++i)
			{
				v13 = v13 + v11;
				v8 = i + v10;
				if (i + v10 == 10)
					v8 = 0;
				if (*(DWORD*)(JCMainSelect + 4 * v8 + 24) != -1
					&& (*(DWORD*)(JCMainSelect + 4 * v8 + 24) < 120
						|| *(DWORD*)(JCMainSelect + 4 * v8 + 24) >= 124
						|| *(DWORD*)(dword_7BC4F04 + 676)))
				{
					v7 = dword_8128ABC + 88 * *(WORD*)(dword_8128AC8 + 2 * *(DWORD*)(JCMainSelect + 4 * v8 + 24) + 120);
					if (!v7 || *(BYTE*)(v7 + 55) != 3)
					{
						if (*(BYTE*)(dword_7BC4F04 + 50) == *(DWORD*)(JCMainSelect + 4 * v8 + 24))
							RenderBitmap(51500, v13, v14, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);
						v4 = v14 + 2.0;
						v5 = v13 + 2.0;
						JCSkillScale = 1;
						JCLoadSkill(JCMainSelect, *(DWORD*)(JCMainSelect + 4 * v8 + 24), v5, v4, 20.0, 28.0);
						JCSkillScale = 0;
					}
				}
			}

			v9 = dword_8128ABC + 88 * *(WORD*)(dword_8128AC8 + 2 * *(BYTE*)(dword_7BC4F04 + 50) + 120);

			if (v9 && *(BYTE*)(v9 + 55) != 3)
			{
				RenderBitmap(51500, JCResto + 306, Fix_DisplayHeightExt + 443.5f, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);
				JCSkillScale = 1;
				JCLoadSkill(JCMainSelect, *(BYTE*)(dword_7BC4F04 + 50), JCResto + 308, Fix_DisplayHeightExt + 445.5f, 20.0, 28.0);
				JCSkillScale = 0;
			}
		}
	}
}
// 7BC4F04: using guessed type int dword_7BC4F04;
// 8128ABC: using guessed type int dword_8128ABC;
// 8128AC8: using guessed type int dword_8128AC8;

void JCSkillRaven(int JCMainSelect)
{
	float v4; // ST18_4@7
	float v5; // ST14_4@7
	signed int i; // [sp+1Ch] [bp-14h]@2
	float v8; // [sp+20h] [bp-10h]@2
	float v9; // [sp+24h] [bp-Ch]@2
	float v10; // [sp+28h] [bp-8h]@2
	float v11; // [sp+2Ch] [bp-4h]@2
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (*(DWORD*)(dword_7BC4F04 + 676))
	{
		v10 = JCResto + 191.0;
		v11 = Fix_DisplayHeightExt + 379.0;
		v8 = 24.0;
		v9 = 38.0;
		for (i = 150; i < 154; ++i)
		{
			if (i == *(BYTE*)(dword_7BC4F04 + 50))
				RenderBitmap(51500, v10 + 4.0, v11 + 4.0, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);

			v4 = v11 + 6.0;
			v5 = v10 + 6.0;
			JCSkillScale = 1;
			JCLoadSkill(JCMainSelect, i, v5, v4, 20.0, 28.0);
			JCSkillScale = 0;
			v10 = v10 + v8;
		}
	}
}
// 7BC4F04: using guessed type int dword_7BC4F04;

void SwitchEventSkill(int num, int x, int y)
{
	int JCMainSelect; // [sp+30h] [bp-2Ch]@15

	JCMainSelect = *(DWORD*)(GetInstance() + 32);
	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if ((signed int)*(BYTE*)(dword_8128AC8 + 118) > 0 && *(BYTE*)(JCMainSelect + 64) == 1)
	{

		RenderBitmap(61547, x + 245, y + 12, 17, 42, 0.0, 0.0, 0.2399999946, 1.0, 1, 1, 0);
		if (num > 20)
		{
			if (JCPageSlotSkill == 1)
			{
				//-- Boton Arriba
				if (JCEventButton(x + 247, y + 14, 13, 13))
				{

					JCPageSlotSkill = 0;
					RenderBitmap(61547, x + 247, y + 14, 13, 13, 0.3870000243, 0.4429999888, 0.1380000114, 0.2490001172, 1, 1, 0);
					PlayBuffer(25, 0, 0);
				}
				else
				{
					RenderBitmap(61547, x + 247, y + 14, 13, 13, 0.3870000243, 0.7100000381, 0.1380000114, 0.2490001172, 1, 1, 0);
				}
			}
			else
			{
				RenderBitmap(61547, x + 247, y + 14, 13, 13, 0.3870000243, 0.1729999632, 0.1380000114, 0.2490001172, 1, 1, 0);
			}
			//-- Boton Abajo
			if (JCPageSlotSkill == 0)
			{
				if (JCEventButton(x + 247, y + 38, 13, 13))
				{
					JCPageSlotSkill = 1;
					RenderBitmap(61547, x + 247, y + 38, 13, 13, 0.2470000237, 0.4429999888, 0.1380000114, 0.2490001172, 1, 1, 0);
					PlayBuffer(25, 0, 0);
				}
				else
				{
					RenderBitmap(61547, x + 247, y + 38, 13, 13, 0.2470000237, 0.7100000381, 0.1380000114, 0.2490001172, 1, 1, 0);

				}
			}
			else
			{
				RenderBitmap(61547, x + 247, y + 38, 13, 13, 0.2470000237, 0.1729999632, 0.1380000114, 0.2490001172, 1, 1, 0);
			}
		}
		else
		{
			pSetCursorFocus = false;
			//-- Arriba
			RenderBitmap(61547, x + 247, y + 14, 13, 13, 0.3870000243, 0.1729999632, 0.1380000114, 0.2490001172, 1, 1, 0);
			//-- Abajo
			RenderBitmap(61547, x + 247, y + 38, 13, 13, 0.2470000237, 0.1729999632, 0.1380000114, 0.2490001172, 1, 1, 0);
		}
	}
}

char JCSkillSwitchBar(int JCMainSelect)
{
	float v4; // ST18_4@26
	float v5; // ST14_4@26
	char v9; // [sp+37h] [bp-25h]@9
	float v10; // [sp+38h] [bp-24h]@3
	signed int v11; // [sp+3Ch] [bp-20h]@3
	signed int v12; // [sp+40h] [bp-1Ch]@6
	float v13; // [sp+44h] [bp-18h]@3
	float v14; // [sp+48h] [bp-14h]@3
	signed int i; // [sp+50h] [bp-Ch]@3
	float v16; // [sp+54h] [bp-8h]@16
	float v17; // [sp+58h] [bp-4h]@3
	int JCResto; // eax@1

	JCMainSelect = *(DWORD*)(GetInstance() + 32);
	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if ((signed int)*(BYTE*)(dword_8128AC8 + 118) > 0 && *(BYTE*)(JCMainSelect + 64) == 1)
	{

		v17 = Fix_DisplayHeightExt + 349.0;
		v13 = 24.0; //-- separación
		v14 = 29.5;
		v10 = JCResto + 191.0;
		v11 = 0;

		RenderBitmap(61546, JCResto + 191.3, Fix_DisplayHeightExt + 350.0, 243.5, 60.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0);

		for (i = 0; i < 150; ++i)
		{
			v12 = *(WORD*)(dword_8128AC8 + 2 * i + 120);
			if (*(WORD*)(dword_8128AC8 + 2 * i + 120) && (v12 < 67 || v12 > 72))
			{
				v9 = *(BYTE*)(dword_8128ABC + 88 * v12 + 55);

				if (v9 != 1 && v9 != 3)
				{
					if (v11 == 10)
						v17 = v17 + v14;
					if (v11 == 20)
						v17 = v17 - v14;
					if (v11 >= 10 && v11 < 20)
					{
						v16 = (double)(v11 - 10) * v13 + v10;
					}
					else if (v11 >= 20)
					{
						v16 = (double)(v11 - 20) * v13 + v10;
					}
					else
					{
						v16 = (double)v11 * v13 + v10;
					}

					++v11;

					if (JCPageSlotSkill == 0)
					{
						if (v11 >= 21)
							continue;
					}
					else
					{
						if (v11 < 21)
							continue;
					}
					if (i == *(BYTE*)(dword_7BC4F04 + 50))
						RenderBitmap(51500, v16 + 4.0, v17 + 4.0, 20.0f, 24.0f, 0.1600000411f, 0.1000000089f, 0.6397998333f, 0.4179990888f, 1, 1, 0);

					v4 = v17 + 6.0;
					v5 = v16 + 6.0;

					JCSkillScale = 1;
					JCLoadSkill(JCMainSelect, i, v5, v4, 20.0, 28.0);
					JCSkillScale = 0;
				}
			}
		}
		JCSkillRaven(JCMainSelect);
	}

	if (*(BYTE*)(JCMainSelect + 65) == 1 && *(DWORD*)(JCMainSelect + 16))
	{
		JCMultiSkillLine(*(DWORD*)(JCMainSelect + 16), 5.5, (int)0x815040, JCMainSelect, 0, 0);

#if(FPS_60 == 1)
		* (BYTE*)(JCMainSelect + 65) = 1; //<<<<<<<<<<<
#else 
		* (BYTE*)(JCMainSelect + 65) = 0; // find me
#endif
	}

	SwitchEventSkill(v11, JCResto + 191.0, Fix_DisplayHeightExt + 349.0);

	pGLSwitch();
	EnableAlphaTest(0);

	return 1;
}
// 7BC4F04: using guessed type int dword_7BC4F04;
// 8128ABC: using guessed type int dword_8128ABC;
// 8128AC8: using guessed type int dword_8128AC8;

void JCShowSlotSkill(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	if (JCSkillScale == 1)
	{
		RenderBitmap(ImageID, PosX, PosY, 16.0f, 20.0f, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	}
	else
	{
		RenderBitmap(ImageID, PosX, PosY, Width, Height, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
	}
}

void JCShownumberSkill(float x, float y, int number, float scale)
{
	if (JCSkillScale == 1)
	{
		JCRenderNumber(x - 5.0f, y - 5.0f, number, 0.9);
	}
	else
	{
		JCRenderNumber(x, y, number, 1.0);
	}

}

void JCShowTimerBar(int Skillnumber, float x, float y, float w, float h)
{
	if (JCSkillScale == 1)
	{
		JCTimerSkillBar(Skillnumber, x, y, 16.0f, 20.0f);
	}
	else
	{
		JCTimerSkillBar(Skillnumber, x, y, w, h);
	}
}

int JCStacknumberpotion(float x, float y, int number)
{
	pSetBlend(1);

	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal - 640;

	return JCRenderNumber(x, y, number, 1.0);
}

void JCItemStacknumber(float x, float y, int number, float scale)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal - 640;

	JCRenderNumber(x + JCResto, y, number, scale);
}

bool JCCheckSkillHelper(int x, int y, int w, int h)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal - 640;

	return pCheckMouseOver(x + JCResto, y, w, h);
}

void RenderGUIFull(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal - 640;

	pDrawGUI(ImageID, PosX + JCResto, Fix_DisplayHeightExt + PosY, Width, Height);
}


__declspec(naked) void JCPrintSkillHelper()
{
	static DWORD Addr_JMP = 0x007F9D0A;
	static DWORD Addr_CALL1 = 0x007FDBA0;
	static DWORD Addr_CALL2 = 0x00861110;
	static DWORD Addr_CALL3 = 0x00861200;
	static int JCResto;

	JCResto = pWinWidth / pWinHeightReal - 640;

	_asm
	{
		PUSH ECX
		FLD DWORD PTR DS : [0xD254E4]
		FSTP DWORD PTR SS : [ESP]
		PUSH ECX
		FLD DWORD PTR DS : [0xD23F68]
		FSTP DWORD PTR SS : [ESP]
		LEA ECX, DWORD PTR SS : [EBP - 0x8]
		CALL Addr_CALL1
		MOV EAX, DWORD PTR DS : [EAX]
		MOV ECX, DWORD PTR DS : [EAX + 0x8]
		ADD ECX, 6
		MOV DWORD PTR SS : [EBP - 0x38] , ECX
		FILD DWORD PTR SS : [EBP - 0x38]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		LEA ECX, DWORD PTR SS : [EBP - 0x8]
		CALL Addr_CALL1
		MOV EDX, DWORD PTR DS : [EAX]
		MOV EAX, DWORD PTR DS : [EDX + 0x4]
		ADD EAX, 6
		ADD EAX, JCResto
		MOV DWORD PTR SS : [EBP - 0x3C] , EAX
		FILD DWORD PTR SS : [EBP - 0x3C]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		LEA ECX, DWORD PTR SS : [EBP - 0x8]
		CALL Addr_CALL1
		MOV ECX, DWORD PTR DS : [EAX]
		MOV EDX, DWORD PTR DS : [ECX]
		PUSH EDX
		CALL Addr_CALL2
		MOV ECX, EAX
		CALL Addr_CALL3
		MOV ECX, EAX; |
		JMP[Addr_JMP]; \main1.008977D0
	}
}


//========================================
//-------------- DOWGRADE ----------------
//========================================

double JCRenderNumberEx(float a1, float a2, int a3, float a4)
{
	double result; // st7@2
	float v5; // ST44_4@5
	float v6; // ST38_4@5
	signed int i; // [sp+38h] [bp-30h]@3
	float v8; // [sp+3Ch] [bp-2Ch]@3
	signed int v9; // [sp+44h] [bp-24h]@3
	char v10[32]; // [sp+48h] [bp-20h]@3
	float v11; // [sp+70h] [bp+8h]@3

	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290) * 12.0;
		itoa(a3, v10, 10);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.400000011920929) * 16.0;
			RenderBitmap(31337, v11, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}

	return result;
}


void JCExpBarDowngrade(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	int Addradd;
	float RenderW;

	Addradd = QTFrame.DisplayWinExt;
	RenderW = (Width / 629.0f) * 198.0f;

	RenderBitmap(ImageID, 220.0f + Addradd, Fix_DisplayHeightExt + 434.5f, RenderW, 6.0f, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void JCMoveExpBarDowngrade(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	int Addradd;
	float RenderW;
	float JCCoordX;

	Addradd = QTFrame.DisplayWinExt;
	RenderW = (Width / 629.0f) * 198.0f;

	if (PosX == 2.0f)
	{
		JCCoordX = 220.0f;
	}
	else
	{
		JCCoordX = ((PosX - 2.0f) / 629.0) * 198.0f + 220.0f;
	}

	RenderBitmap(ImageID, JCCoordX + Addradd, Fix_DisplayHeightExt + 434.5f, RenderW, 6.0f, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void JCExpBarDowngradeAdd(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	int Addradd;
	float RenderW;
	float JCCoordX;

	Addradd = QTFrame.DisplayWinExt;
	RenderW = (Width / 629.0f) * 198.0f;

	if (PosX == 2.0f)
	{
		JCCoordX = 220.0f;
	}
	else
	{
		JCCoordX = ((PosX - 2.0f) / 629.0) * 198.0f + 220.0f;
	}

	pDrawBarForm(JCCoordX + Addradd, Fix_DisplayHeightExt + 434.5f, RenderW, 6.0f, Arg5, Arg6);
}

bool pCheckExpBarCurrent(int x, int y, int w, int h)
{
	int Addradd;
	Addradd = QTFrame.DisplayWinExt;

	return pCheckMouseOver(220 + Addradd, Fix_DisplayHeightExt + 435, 198, 6);
}

int JCTooltipExpCurrent(int X, int Y, LPCSTR Text)
{
	int Addradd;
	Addradd = QTFrame.DisplayWinExt;

	return pDrawToolTip(220 + Addradd, Fix_DisplayHeightExt + Y, Text);
}

void RenderNumberExp2(float a4, float a5, int Number, float a7)
{
	int Addradd;
	Addradd = QTFrame.DisplayWinExt;

	JCRenderNumberEx(425 + Addradd, Fix_DisplayHeightExt + 431.5, Number, a7);
}

int InterfaceButton(char* This, int X, int Y, int Width, int Height)
{
	return 1;
}

void JInterfaceLeft(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int Addradd; // eax@1

	Addradd = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawGUI(ImageID, PosX + Addradd, Fix_DisplayHeightExt + PosY, Width, Height);

	float x = PosX + Addradd - 70.28048780487805;

	RenderBitmap(87968, x, Fix_DisplayHeightExt + PosY, 70.28048780487805, 51, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0.0);


	EnableAlphaBlend();

	glColor3f(1.0, 0.89999998, 0.69999999);
	JCRenderNumberEx(22 + Addradd, Fix_DisplayHeightExt + PosY + 34, pGetUserCoorX, 0.9499999881);

	glColor3f(1.0, 0.89999998, 0.69999999);
	JCRenderNumberEx(46 + Addradd, Fix_DisplayHeightExt + PosY + 34, pGetUserCoorY, 0.9499999881);
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	EnableAlphaTest(1);

	//RenderBitmap(2336, PosX + Addradd - 20.0, Fix_DisplayHeightExt +362.0, 117.0, 75.0, 0.0, 0.0, 0.8999999762, 0.5600000024, 1, 1, 0.0);
}

void JInterfaceMiddle(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int Addradd; // eax@1

	Addradd = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawGUI(ImageID, PosX + Addradd, Fix_DisplayHeightExt + PosY, Width, Height);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//-- DisplaYFrame
//////////////////////////////////////////////////////////////////////////////////////////////
signed int FrameScreenWidth2()
{
	signed int v52; // [sp+0h] [bp-4h]@11

	if (pCheckWindow((LPVOID)GetInstance(), 13) && pCheckWindow((LPVOID)GetInstance(), 16)
		|| pCheckWindow((LPVOID)GetInstance(), 8)
		|| pCheckWindow((LPVOID)GetInstance(), 12)
		|| pCheckWindow((LPVOID)GetInstance(), 9)
		|| pCheckWindow((LPVOID)GetInstance(), 7)
		|| pCheckWindow((LPVOID)GetInstance(), 14)
		|| pCheckWindow((LPVOID)GetInstance(), 15)
		|| pCheckWindow((LPVOID)GetInstance(), 60)
		|| pCheckWindow((LPVOID)GetInstance(), 76))
	{

		v52 = 380;
	}
	else
	{
		if (pCheckWindow((LPVOID)GetInstance(), 16)
			&& (pCheckWindow((LPVOID)GetInstance(), 4)
				|| pCheckWindow((LPVOID)GetInstance(), 69)))
		{
			v52 = 380;
		}
		else
		{
			if (pCheckWindow((LPVOID)GetInstance(), 16) && pCheckWindow((LPVOID)GetInstance(), 11))
			{
				v52 = 380;
			}
			else
			{
				if (pCheckWindow((LPVOID)GetInstance(), 27))
				{
					v52 = 380;
				}
				else
				{
					if (pCheckWindow((LPVOID)GetInstance(), 13)
						|| pCheckWindow((LPVOID)GetInstance(), 16)
						|| pCheckWindow((LPVOID)GetInstance(), 3)
						|| pCheckWindow((LPVOID)GetInstance(), 21)
						|| pCheckWindow((LPVOID)GetInstance(), 6)
						|| pCheckWindow((LPVOID)GetInstance(), 22)
						|| pCheckWindow((LPVOID)GetInstance(), 23)
						|| pCheckWindow((LPVOID)GetInstance(), 24)
						|| pCheckWindow((LPVOID)GetInstance(), 4)
						|| pCheckWindow((LPVOID)GetInstance(), 18)
						|| pCheckWindow((LPVOID)GetInstance(), 10)
						|| pCheckWindow((LPVOID)GetInstance(), 5)
						|| pCheckWindow((LPVOID)GetInstance(), 25)
						|| pCheckWindow((LPVOID)GetInstance(), 26)
						|| pCheckWindow((LPVOID)GetInstance(), 19)
						|| pCheckWindow((LPVOID)GetInstance(), 20)
						|| pCheckWindow((LPVOID)GetInstance(), 58)
						|| pCheckWindow((LPVOID)GetInstance(), 59)
						|| pCheckWindow((LPVOID)GetInstance(), 62)
						|| pCheckWindow((LPVOID)GetInstance(), 73)
						|| pCheckWindow((LPVOID)GetInstance(), 68)
						|| pCheckWindow((LPVOID)GetInstance(), 69)
						|| pCheckWindow((LPVOID)GetInstance(), 70)
						|| pCheckWindow((LPVOID)GetInstance(), 66)
						|| pCheckWindow((LPVOID)GetInstance(), 75)
						|| pCheckWindow((LPVOID)GetInstance(), 74))
					{
						v52 = 190;
					}
					else
					{
						if (pCheckWindow((LPVOID)GetInstance(), 79))
						{
							if (pCheckWindow((LPVOID)GetInstance(), 80))
								v52 = 380;
							else
								v52 = 190;
						}
						else
						{
							v52 = 0;
						}
					}
				}
			}
		}
	}
	if (pCheckWindow((LPVOID)GetInstance(), 77))
	{
		if (sub_7D6270(*(DWORD*)(GetInstance() + 300), 0))
			v52 = 570;
		else
			v52 = 380;
	}
	else
	{
		if (pCheckWindow((LPVOID)GetInstance(), 78))
		{
			v52 = 570;

		}
	}

	return (int)(QTFrame.DisplayWin - v52);
}


void JInterfaceRight(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int v38; // [sp+14h] [bp-28h]@1
	int Addradd; // eax@1

	v38 = *(DWORD*)(GetInstance() + 28);
	Addradd = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawGUI(ImageID, PosX + Addradd, Fix_DisplayHeightExt + PosY, Width, Height);

	RenderBitmap(87968, PosX + Addradd + Width, Fix_DisplayHeightExt + PosY, 70.28048780487805, Height, 0.8785000443, 0.0, -0.8785000443, 0.6409999728, 1, 1, 0.0);

	ChangeButtonInfo2((char*)(v38 + 228), 379 + Addradd, Fix_DisplayHeightExt + 449, 25, 25); //-- character
	ChangeButtonInfo2((char*)(v38 + 400), 409 + Addradd, Fix_DisplayHeightExt + 449, 25, 25); //-- Inventory
	ChangeButtonInfo2((char*)(v38 + 572), 581 + Addradd, Fix_DisplayHeightExt + 432, 52, 18); //-- Frient List
	ChangeButtonInfo2((char*)(v38 + 744), 5 + Addradd, Fix_DisplayHeightExt + 432, 52, 18); //-- Menu Fast

	if (pCheckWindow(pWindowThis(), 16)) //-- char
	{
		pDrawButton(88900, 379 + Addradd, Fix_DisplayHeightExt + 449, 26, 28, 0, 0);
	}
	if (pCheckWindow(pWindowThis(), 1)) //-- frient
	{
		pDrawButton(88901, 581 + Addradd, Fix_DisplayHeightExt + 432, 52, 18, 0, 0);
	}
	if (pCheckWindow(pWindowThis(), 13)) //-- inv
	{
		pDrawButton(88902, 409 + Addradd, Fix_DisplayHeightExt + 449, 26, 28, 0, 0);
	}
	if (pCheckWindow(pWindowThis(), 34)) //-- fast menu
	{
		pDrawButton(88903, 5 + Addradd, Fix_DisplayHeightExt + 432, 52, 18, 0, 0);
	}
	if (pCheckWindow(pWindowThis(), 3)) //-- party
	{
		pDrawButton(88904, 348 + Addradd, Fix_DisplayHeightExt + 449, 26, 28, 0, 0);
	}
	if (pCheckWindow(pWindowThis(), 6)) //-- Guild
	{
		pDrawButton(88905, 579 + Addradd, Fix_DisplayHeightExt + PosY + 27, 56, 22, 0, 0);
	}

	if (pCheckMouseOver(348 + Addradd, 449, 25, 25))
	{
		pDrawToolTip(348 + Addradd, 449 - 10, "Party");

		if (*(BYTE*)0x8793386)
		{
			if (GetTickCount() >= TimerPush1 + 300)
			{
				if (pCheckWindow(pWindowThis(), 3)) //-- party
				{
					pCloseWindow(pWindowThis(), 3);
				}
				else
				{
					pOpenWindow(pWindowThis(), 3);
				}
				TimerPush1 = GetTickCount();
			}
		}
	}

	if (pCheckMouseOver(581 + Addradd, Fix_DisplayHeightExt + 454, 52, 18))
	{
		pDrawToolTip(581 + Addradd, Fix_DisplayHeightExt + 454 - 10, "Guild");

		if (*(BYTE*)0x8793386)
		{
			if (GetTickCount() >= TimerPush2 + 300)
			{
				if (pCheckWindow(pWindowThis(), 6)) //-- party
				{
					pCloseWindow(pWindowThis(), 6);
				}
				else
				{
					pOpenWindow(pWindowThis(), 6);
				}
				TimerPush2 = GetTickCount();
			}
		}
	}

	int WinWidth; // eax@1
	WinWidth = pWinWidth / pWinHeightReal;

	if (WinWidth != FrameScreenWidth2() || pCheckWindow(pWindowThis(), SkillTree)
		|| pCheckWindow(pWindowThis(), CashShop) || pCheckWindow(pWindowThis(), FullMap)
		|| pCheckWindow(pWindowThis(), FastMenu) || pCheckWindow(pWindowThis(), FriendList)
		|| pMapNumber == 39 //Kanturu
		|| pMapNumber == 58 //Selupam
		|| pMapNumber == 64 //Duel Arena
		|| pMapNumber == 65 //Doppelganger
		|| pMapNumber == 66 //Doppelganger
		|| pMapNumber == 67 //Doppelganger
		|| pMapNumber == 68 //Doppelganger
		|| pMapNumber == 69 //Imperial Guardian
		|| pMapNumber == 70 //Imperial Guardian
		|| pMapNumber == 71 //Imperial Guardian
		|| pMapNumber == 72 //Imperial Guardian
		|| pMapNumber == 11	//Blood Castle
		|| pMapNumber == 12	//Blood Castle
		|| pMapNumber == 13	//Blood Castle
		|| pMapNumber == 14	//Blood Castle
		|| pMapNumber == 15	//Blood Castle
		|| pMapNumber == 16	//Blood Castle
		|| pMapNumber == 17	//Blood Castle
		|| pMapNumber == 52	//Blood Castle
		|| pMapNumber == 9	//Devil Square
		|| pMapNumber == 32	//Devil Square
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 45	//Illusion Temple
		|| pMapNumber == 46	//Illusion Temple
		|| pMapNumber == 47	//Illusion Temple
		|| pMapNumber == 48	//Illusion Temple
		|| pMapNumber == 49	//Illusion Temple
		|| pMapNumber == 50	//Illusion Temple
		|| pMapNumber == 18	//Chaos Castle
		|| pMapNumber == 19	//Chaos Castle
		|| pMapNumber == 20	//Chaos Castle
		|| pMapNumber == 21	//Chaos Castle
		|| pMapNumber == 22	//Chaos Castle
		|| pMapNumber == 23	//Chaos Castle
		|| pMapNumber == 53	//Chaos Castle
		|| pMapNumber == 34 //Crywolf
		|| pMapNumber == 30 //Valley/CastleSiege
		|| pMapNumber == 65 /*DuelArena*/)
	{
		return;
	}
	//RenderBitmap(2336, PosX + Addradd + Width - 95.0, Fix_DisplayHeightExt +362.0, 117.0, 75.0, 0.8999999762, 0.0, -0.8999999762, 0.5600000024, 1, 1, 0.0);

}


void JPrintAtributoPlayer(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentX, float CurrentY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	float v3; // ST58_4@49
	float v5; // ST50_4@49
	float v19; // [sp+A4h] [bp-134h]@44
	float v18; // [sp+A8h] [bp-130h]@48
	float v21; // [sp+B4h] [bp-124h]@48
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	if (ImageID == 31296 || ImageID == 31297 || ImageID == 31298) //-- Current HP || mp
	{
		v19 = (PosY - (float)432.0) / (float)39.0f;

		v21 = v19 * (float)52.0f + (float)429.0f;

		v18 = (float)52.0f - v19 * (float)52.0f;

		v3 = (1.0 - v19) * 52.0f / 65.56341823475827;

		v5 = v19 * 52.0f / 65.56341823475827;

		if (31296 == ImageID)
		{
			RenderBitmap(ImageID, 489.0400085 + Addradd, Fix_DisplayHeightExt + v21, 52.0f, v18, 0.0, v5, 0.823125124, v3, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(ImageID, 98.0f + Addradd, Fix_DisplayHeightExt + v21, 52.0f, v18, 0.0, v5, 0.823125124, v3, 1, 1, 0.0);
		}
	}
	else //-- Current AG || SD
	{
		v19 = (PosY - (float)431.0) / (float)39.0f;
		//--
		v21 = v19 * (float)38 + (float)435.2000122;

		v18 = (float)38 - v19 * (float)38;

		v3 = (1.0 - v19) * (float)38 / (float)67.37588527048441;

		v5 = v19 * (float)38 / (float)67.37588527048441;

		if (ImageID == 31299)
		{
			RenderBitmap(ImageID, 552.0f + Addradd, Fix_DisplayHeightExt + v21, 13.5f, v18, CurrentX, v5, 0.9319999814f, v3, 1, 1, 0.0);
		}
		else
		{
			if (gProtect.m_MainInfo.CustomInterfaceType == Season2)
			{
				RenderBitmap(ImageID, 73.59999847 + Addradd, Fix_DisplayHeightExt + v21, 13.5, v18, CurrentX, v5, 0.9319999814, v3, 1, 1, 0.0);
			}
		}
	}
}

bool JCheckAtributoPlayer(int a1, int a2, int a3, int a4)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	if (a1 == 158)
	{
		return pCheckMouseOver(98 + Addradd, Fix_DisplayHeightExt + 429, 52, 52);
	}
	else if (a1 == 437)
	{
		return pCheckMouseOver(490 + Addradd, Fix_DisplayHeightExt + 429, 52, 52);
	}
	else if (a1 == 420)
	{
		return pCheckMouseOver(552 + Addradd, Fix_DisplayHeightExt + 435, 13, 38);
	}
	else
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == Season2)
		{
			return pCheckMouseOver(73 + Addradd, Fix_DisplayHeightExt + 435, 13, 38);
		}
		else
		{
			return false;
		}

	}
}

int JInfoAtributoPlayer(int a1, int a2, LPCSTR Text)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	if (a1 == 158)
	{
		return pDrawToolTip(98 + Addradd, Fix_DisplayHeightExt + 405, Text);
	}
	else if (a1 == 400)
	{
		return pDrawToolTip(535 + Addradd, Fix_DisplayHeightExt + 405, Text);
	}
	else if (a1 == 437)
	{
		return pDrawToolTip(488 + Addradd, Fix_DisplayHeightExt + 405, Text);
	}
	else
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == Season1)
		{
			return 1;
		}
		else
		{
			return pDrawToolTip(46 + Addradd, Fix_DisplayHeightExt + 405, Text);
		}
	}
}

void JInfoAtributoHP(float a4, float a5, int Number, float a7)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	JCRenderNumberEx(98 + 25.0f + Addradd, Fix_DisplayHeightExt + 470, Number, a7);
}

void JInfoAtributoMP(float a4, float a5, int Number, float a7)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	JCRenderNumberEx(490 + 30.0f + Addradd, Fix_DisplayHeightExt + 470, Number, a7);
}

void JInfoAtributoAG(float a4, float a5, int Number, float a7)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;

	JCRenderNumberEx(552 + 10.0f + Addradd, Fix_DisplayHeightExt + 470, Number, a7);
}

void JInfoAtributoSD(float a4, float a5, int Number, float a7)
{
	int Addradd; // ST50_4@02

	Addradd = QTFrame.DisplayWinExt;
	if (gProtect.m_MainInfo.CustomInterfaceType == Season2)
	{
		JCRenderNumberEx(73 + 15.0f + Addradd, Fix_DisplayHeightExt + 470, Number, a7);
	}
}

//----- (00812120) --------------------------------------------------------
//double sub_812120()
//{
//	return 2.6;
//}

DWORD RenderSlot;

__declspec(naked) void ShadowColorCheck()
{
	static DWORD jmpBack = 0x007DB30F;

	__asm
	{
		mov     eax, [ebp - 0x1C]
		movzx   ecx, byte ptr[eax + 0x60]
		mov		RenderSlot, ecx
		jmp[jmpBack]
	}
}

void RenderItemBox(DWORD ID, float x, float y, float w, float h)
{
	RenderBitmap(31072, x, y, w, h, 0, 0, 1.0, 1.0, 1, 1, 0.0);

	switch (RenderSlot)
	{
	case 0:
		break;
	case 1:
		EnableAlphaTest(1);
		glColor4f(1.0, 1.0, 0.0, 0.30000001);//glColor4f(1.0, 1.0, 0.0, 0.60000001);
		break;
	case 2:
		EnableAlphaTest(1);
		glColor4f(1.0, 0.66000003, 0.0, 0.30000001);//glColor4f(1.0, 0.66000003, 0.0, 0.60000001);
		break;
	case 3:
		EnableAlphaTest(1);
		glColor4f(0.89000001, 0.10900001, 0.10900001, 0.30000001);//glColor4f(1.0, 0.33000001, 0.0, 0.60000001);
		break;
	case 4:
		EnableAlphaTest(1);
		glColor4f(1.0, 0.0, 0.0, 0.40000001);
		break;
	case 5:
		EnableAlphaTest(1);
		glColor4f(1.0, 0.2, 0.1, 0.40000001);
		break;
	default:
		RenderBitmap(31071, x, y, w, h, 0, 0, 1.0, 1.0, 1, 1, 0.0);
		break;
	}

	if (RenderSlot >= 1 && RenderSlot <= 5)
	{
		pDrawBarForm(x, y, w, h, 0.0, 0);
		pGLSupremo();
		EnableAlphaTest(1);
	}

	RenderSlot = -1;
}

__declspec(naked) void RenderSlotDwongradeQ()
{
	static DWORD Addr_JMP = 0x00895A73;
	static float RenderPotionY = Fix_DisplayHeightExt + 453.0f;
	static float RenderNumberY = Fix_DisplayHeightExt + 445.0f;

	static int Addradd;
	static float RenderPotionX = 210.0f;
	static float RenderNumberX = 227.0f;

	Addradd = QTFrame.DisplayWinExt;

	RenderNumberX += Addradd;
	RenderPotionX += Addradd;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x18] ; |
		JMP[Addr_JMP]; \main1.008977D0
	}
}

__declspec(naked) void RenderSlotDwongradeW()
{
	static DWORD Addr_JMP = 0x00895AE8;
	static float RenderPotionY = Fix_DisplayHeightExt + 453.0f;
	static float RenderNumberY = Fix_DisplayHeightExt + 445.0f;

	static int Addradd;
	static float RenderPotionX = 240.0f;
	static float RenderNumberX = 257.0f;

	Addradd = QTFrame.DisplayWinExt;

	RenderNumberX += Addradd;
	RenderPotionX += Addradd;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x20] ; |
		JMP[Addr_JMP]; \main1.00897BD0
	}
}

__declspec(naked) void RenderSlotDwongradeE()
{
	static DWORD Addr_JMP = 0x00895B5D;
	static float RenderPotionY = Fix_DisplayHeightExt + 453.0f;
	static float RenderNumberY = Fix_DisplayHeightExt + 445.0f;

	static int Addradd;
	static float RenderPotionX = 270.0f;
	static float RenderNumberX = 287.0f;

	Addradd = QTFrame.DisplayWinExt;

	RenderNumberX += Addradd;
	RenderPotionX += Addradd;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x28] ; |
		JMP[Addr_JMP]; \main1.00895760
	}
}

__declspec(naked) void RenderSlotDwongradeR()
{
	static DWORD RButtonAddress = 0x00895C0C;

	_asm
	{
		jmp RButtonAddress
	}
}
//========================================
//----------FINISH DOWGRADE --------------
//========================================


void JCurrentExp(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	float RenderW;
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	RenderW = (Width / 629.0f) * 518.125f;

	RenderBitmap(ImageID, JCResto + 60.0f, Fix_DisplayHeightExt + 474.0f, RenderW, 3.0f, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void JCurrentMoveExp(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentMoveX, float CurrentMoveY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)
{
	float RenderW;
	float JCCoordX;
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	RenderW = (Width / 629.0f) * 518.125f;

	if (PosX == 2.0f)
	{
		JCCoordX = 60.0f;
	}
	else
	{
		JCCoordX = ((PosX - 2.0f) / 629.0) * 518.125f + 60.0f;
	}

	RenderBitmap(ImageID, JCResto + JCCoordX, Fix_DisplayHeightExt + 474.0f, RenderW, 3.0f, CurrentMoveX, CurrentMoveY, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void JCurrentAddExp(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6)
{
	float RenderW;
	float JCCoordX;
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	RenderW = (Width / 629.0f) * 518.125f;

	if (PosX == 2.0f)
	{
		JCCoordX = 60.0f;
	}
	else
	{
		JCCoordX = ((PosX - 2.0f) / 629.0) * 518.125f + 60.0f;
	}

	pDrawBarForm(JCResto + JCCoordX, Fix_DisplayHeightExt + 474.0f, RenderW, 3.0f, Arg5, Arg6);
}

bool JCheckExpBarCurrent(int x, int y, int w, int h)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	return pCheckMouseOver(JCResto + 60, 474 + Fix_DisplayHeightExt, 518, 3);
}

int JTooltipExpCurrent(int X, int Y, LPCSTR Text)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	return pDrawToolTip(JCResto + 220, Y + Fix_DisplayHeightExt, Text);
}

void JBarNumberExp(float a4, float a5, int Number, float a7)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	JCRenderNumberEx(JCResto + 604.375, Fix_DisplayHeightExt + 470, Number, 0.90);
}

void JAttributoPlayer(int ImageID, float PosX, float PosY, float Width, float Height, float CurrentX, float CurrentY, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	int JCResto; // eax@1
	float v3; // ST58_4@49
	float v4; // ST54_4@49
	float v5; // ST50_4@49
	float v19; // [sp+A4h] [bp-134h]@44
	float v18; // [sp+A8h] [bp-130h]@48
	float v21; // [sp+B4h] [bp-124h]@48

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (ImageID == 31296 || ImageID == 31297 || ImageID == 31298) //-- Current HP || mp
	{
		v19 = (PosY - (float)432.0) / (float)39.0f; //-- recuperar información current life

		v18 = (float)59.0f - v19 * (float)59.0f; //-- nuevo tamaño Height

		v3 = (1.0 - v19) * 59.0f / 59.83772449279798; //-- Scale Y

		v5 = v19 * 59.0f / 59.83772449279798; //-- Current Drop Y

		if (31296 == ImageID) //-- Mana
		{
			//-- mana
			RenderBitmap(51501, JCResto + 464.5f, Fix_DisplayHeightExt + 410.0f, 59.5f, 59.0f, 0.0, 0.0, 0.986000061f, 0.986000061f, 1, 1, 0.0); //-- Life

			v21 = v19 * (float)59.0f + (float)410.0; //-- nueva posición Y
			RenderBitmap(ImageID, JCResto + 464.5f, Fix_DisplayHeightExt + v21, 59.5f, v18, 0.0, v5, 0.986000061f, v3, 1, 1, 0.0); //-- Mana
		}
		else
		{
			//-- vida
			RenderBitmap(51502, JCResto + 107.5f, Fix_DisplayHeightExt + 409.5f, 62.0f, 59.0f, 0.0, 0.0, 0.986000061f, 0.986000061f, 1, 1, 0.0); //-- Life

			v21 = v19 * (float)59.0f + (float)409.5; //-- nueva posición Y
			RenderBitmap(ImageID, JCResto + 107.5f, Fix_DisplayHeightExt + v21, 62.0f, v18, 0.0, v5, 0.986000061f, v3, 1, 1, 0.0); //-- Life
		}
	}
	else //-- Current AG || SD
	{
		v19 = (PosY - (float)431.0) / (float)39.0f; //-- recuperar información current

		if (ImageID == 31299)	//-- ag
		{
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				v21 = v19 * (float)59.0 + (float)398.0f; //-- translate X
				v18 = (float)59.0 - v19 * (float)59.0; //-- Width
				v3 = (1.0 - v19) * (float)59.0 / (float)62.5; //-- current scale x
				v5 = v19 * (float)59.0 / (float)62.5; //-- current move x
			}
			else
			{
				v21 = v19 * (float)70 + (float)395.0f; //-- translate X
				v18 = (float)70 - v19 * (float)70; //-- Width
				v3 = (1.0 - v19) * (float)70 / (float)73.68421144930749; //-- current scale x
				v5 = v19 * (float)70 / (float)73.68421144930749; //-- current move x
			}

			RenderBitmap(31299, JCResto + v21, Fix_DisplayHeightExt + 427.875f, v18, 9.375f, v5, 0.0, v3, 1.0, 1, 1, 0.0);
		}
		else	//-- sd
		{
			v18 = (float)65.3 - v19 * (float)65.3; //-- Width
			v3 = (1.0 - v19) * (float)65.3 / (float)68.44864186545482; //-- current scale x

			RenderBitmap(31300, JCResto + 179.975, Fix_DisplayHeightExt + 427.875f, v18, 9.375f, 0.0, 0.0, v3, 1.0, 1, 1, 0.0);
		}
	}
}

bool JAttributoCheck(int a1, int a2, int a3, int a4)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (a1 == 158)
	{
		return pCheckMouseOver(JCResto + 108, Fix_DisplayHeightExt + 410, 62, 59); //-- HP
	}
	else if (a1 == 437)
	{
		return pCheckMouseOver(JCResto + 465, Fix_DisplayHeightExt + 410, 59, 59); //-- MP
	}
	else if (a1 == 420)
	{
		return pCheckMouseOver(JCResto + 395, Fix_DisplayHeightExt + 428, 70, 13);
	}
	else
	{
		return pCheckMouseOver(JCResto + 180, Fix_DisplayHeightExt + 428, 65, 13);
	}
}

int JAttributoTooltip(int a1, int a2, LPCSTR Text)
{
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	if (a1 == 158)
	{
		return pDrawToolTip(JCResto + 108, Fix_DisplayHeightExt + 395, Text); //-- HP
	}
	else if (a1 == 437)
	{
		return pDrawToolTip(JCResto + 465, Fix_DisplayHeightExt + 395, Text); //-- MP
	}
	else if (a1 == 400)
	{
		return pDrawToolTip(JCResto + 395, Fix_DisplayHeightExt + 415, Text);	//-- AG
	}
	else
	{
		return pDrawToolTip(JCResto + 180, Fix_DisplayHeightExt + 415, Text);	//-- SD
	}
}

void JExInterfaceLeft(int ImageID, float PosX, float PosY, float Width, float Height)
{

	float v5; // [sp+20h] [bp-4h]@1
	int JCResto; // eax@1
	char JCPrintText[256]; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	v5 = 480.0 - (float)73.0;

	JCGetAttribute(); //-- attributo hp mana

	RenderBitmap(31293, PosX + JCResto, Fix_DisplayHeightExt + v5, 640, 73, 0.0, 0.0, 0.9129598141, 0.8629598618, 1, 1, 0.0);

	JCGetAttributeSD(); //-- attributo SD
	JCGetAttributeAG(); //-- attributo AG

	pSetFont(pTextThis(), (int)pFontBold);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 240, 240, 240, 255);

	ZeroMemory(JCPrintText, sizeof(JCPrintText));
	wsprintf(JCPrintText, pGetTextLine_(pTextLineThis, 1181), ViewCurHP, ViewMaxHP);

	pDrawText(pTextThis(), JCResto + 107 - 5, Fix_DisplayHeightExt + 439, JCPrintText, 70, 0, (LPINT)3, 0);
	//--
	ZeroMemory(JCPrintText, sizeof(JCPrintText));
	wsprintf(JCPrintText, pGetTextLine_(pTextLineThis, 1181), ViewCurMP, ViewMaxMP);

	pDrawText(pTextThis(), JCResto + 464, Fix_DisplayHeightExt + 439, JCPrintText, 70, 0, (LPINT)3, 0);
	//--
	ZeroMemory(JCPrintText, sizeof(JCPrintText));
	wsprintf(JCPrintText, pGetTextLine_(pTextLineThis, 1181), ViewCurSD, ViewMaxSD);

	pDrawText(pTextThis(), JCResto + 180, Fix_DisplayHeightExt + 429, JCPrintText, 65, 0, (LPINT)3, 0);
	//--
	ZeroMemory(JCPrintText, sizeof(JCPrintText));
	wsprintf(JCPrintText, pGetTextLine_(pTextLineThis, 1181), ViewCurBP, ViewMaxBP);

	pDrawText(pTextThis(), JCResto + 395, Fix_DisplayHeightExt + 429, JCPrintText, 70, 0, (LPINT)3, 0);

	pSetFont(pTextThis(), *(DWORD*)0xE8C588);
}

void JExInterfaceMiddle2(int ImageID, float PosX, float PosY, float Width, float Height)
{
	return;
}

int JCEventPush;

void JExInterfaceMiddle1(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int JCResto; // eax@1
	int active; // eax@1
	float x = 0; // eax@1
	float y = Fix_DisplayHeightExt; // eax@1
	float current1x = 0; // eax@1
	float current2x = 0; // eax@1
	float currenty = 0; // eax@1
	float scalex = 0; // eax@1
	float scaley = 0; // eax@1
	int tooltip = 0; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	for (int k = 0; k < 6; k++)
	{
		active = 0;

		switch (k)
		{
		case 0: //-- XShop
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 45.5;
			}
			else
			{
				x = JCResto + 43.5;
			}
			y = PosY + 20.5;
			current1x = 0.0;
			current2x = 0.4490998983;
			currenty = 0.0;
			scalex = 0.4400001168;
			scaley = 0.1120510176;

			tooltip = 3421;

			if (pCheckWindow(pWindowThis(), CashShop))
			{
				active = 1;
			}
			break;
		case 1: //-- Character
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 69.0;
			}
			else
			{
				x = JCResto + 67.5;
			}

			y = PosY + 20.5;
			current1x = -0.00400000019;
			current2x = 0.4480998516;
			currenty = 0.1110010222;
			scalex = 0.4390001297;
			scaley = 0.111051023;

			tooltip = 362;

			if (pCheckWindow(pWindowThis(), Character))
			{
				active = 1;
			}
			break;
		case 2: //-- Inventory
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 93.5;
			}
			else
			{
				x = JCResto + 92.0;
			}

			y = PosY + 20.5;
			current1x = 0.0;
			current2x = 0.4480998516;
			currenty = 0.2205000073;
			scalex = 0.4390001297;
			scaley = 0.111051023;

			tooltip = 363;

			if (pCheckWindow(pWindowThis(), Inventory))
			{
				active = 1;
			}
			break;
		case 3: //-- Quest
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 529.0;
			}
			else
			{
				x = JCResto + 527.0;
			}

			y = PosY + 21;
			current1x = -0.00400000019;
			current2x = 0.4480998516;
			currenty = 0.3330999911;
			scalex = 0.4390001297;
			scaley = 0.111051023;

			tooltip = 3427;

			if (pCheckWindow(pWindowThis(), Quest))
			{
				active = 1;
			}
			break;
		case 4: //-- FrientList
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 553.0;
			}
			else
			{
				x = JCResto + 552.0;
			}

			y = PosY + 21;
			current1x = 0.0;
			current2x = 0.4430998564;
			currenty = 0.4431000054;
			scalex = 0.4390001297;
			scaley = 0.111051023;

			tooltip = 3428;

			if (pCheckWindow(pWindowThis(), FriendList))
			{
				active = 1;
			}
			break;
		case 5: //-- Settings
			if (gProtect.m_MainInfo.CustomInterfaceType == 4)
			{
				x = JCResto + 577.0;
			}
			else
			{
				x = JCResto + 576.0;
			}

			y = PosY + 19.5;
			current1x = 0.0;
			current2x = 0.4440999031;
			currenty = 0.5538001657;
			scalex = 0.4400001168;
			scaley = 0.111551024;

			tooltip = 3429;

			if (pCheckWindow(pWindowThis(), FastMenu))
			{
				active = 1;
			}
			break;
		}

		if (pCheckMouseOver(x, Fix_DisplayHeightExt + y, 20.5, 20.5))
		{
			pDrawToolTip(x, Fix_DisplayHeightExt + PosY + 10, pGetTextLine_(pTextLineThis, tooltip));
		}

		if (JCEventButton(x, Fix_DisplayHeightExt + y, 20.5, 20.5))
		{
			RenderBitmap(0x901, x, Fix_DisplayHeightExt + y, 20.5, 20.5, current2x, currenty, scalex, scaley, 1, 1, 0.0);

			if (k == 3) //-- Evento Boton Quest
			{
				if (GetTickCount() >= JCEventPush + 200)
				{
					if (pCheckWindow(pWindowThis(), Quest))
					{
						pCloseWindow(pWindowThis(), Quest);
					}
					else
					{
						pOpenWindow(pWindowThis(), Quest);
						PlayBuffer(25, 0, 0);
					}
					JCEventPush = GetTickCount();
				}
			}
		}
		else
		{
			RenderBitmap(0x901, x, Fix_DisplayHeightExt + y, 20.5, 20.5, (active == 1) ? current2x : current1x, currenty, scalex, scaley, 1, 1, 0.0);
		}
	}
}

void JExInterfaceRight(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int v38; // [sp+14h] [bp-28h]@1
	int JCResto; // eax@1

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	v38 = *(DWORD*)(GetInstance() + 28);

	ChangeButtonInfo2((char*)(v38 + 56), JCResto + 43, Fix_DisplayHeightExt + PosY + 20, 20, 20); //-- cashshop
	ChangeButtonInfo2((char*)(v38 + 228), JCResto + 68, Fix_DisplayHeightExt + PosY + 20, 20, 20); //-- character
	ChangeButtonInfo2((char*)(v38 + 400), JCResto + 92, Fix_DisplayHeightExt + PosY + 20, 20, 20); //-- Inventory

	ChangeButtonInfo2((char*)(v38 + 744), JCResto + 576, Fix_DisplayHeightExt + PosY + 20, 20, 20); //-- Menu Fast
	ChangeButtonInfo2((char*)(v38 + 572), JCResto + 552, Fix_DisplayHeightExt + PosY + 20, 20, 20); //-- Friend List
}


__declspec(naked) void RenderEx700SlotQ()
{
	static DWORD Addr_JMP = 0x00895A73;
	static float RenderPotionY = Fix_DisplayHeightExt + 445.5f;
	static float RenderNumberY = Fix_DisplayHeightExt + 460.0f;
	static float RenderPotionX = 189.0f;
	static float RenderNumberX = 206.0f;
	static int JCResto;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x18] ; |
		JMP[Addr_JMP]; \main1.008977D0
	}
}

__declspec(naked) void RenderEx700SlotW()
{
	static DWORD Addr_JMP = 0x00895AE8;
	static float RenderPotionY = Fix_DisplayHeightExt + 445.5f;
	static float RenderNumberY = Fix_DisplayHeightExt + 460.0f;
	static float RenderPotionX = 217.0f;
	static float RenderNumberX = 234.0f;
	static int JCResto;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x20] ; |
		JMP[Addr_JMP]; \main1.00897BD0
	}
}

__declspec(naked) void RenderEx700SlotE()
{
	static DWORD Addr_JMP = 0x00895B5D;
	static float RenderPotionY = Fix_DisplayHeightExt + 445.5f;
	static float RenderNumberY = Fix_DisplayHeightExt + 460.0f;
	static float RenderPotionX = 247.0f;
	static float RenderNumberX = 261.0f;
	static int JCResto;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x28] ; |
		JMP[Addr_JMP]; \main1.00895760
	}
}

__declspec(naked) void RenderEx700SlotR()
{
	static DWORD Addr_JMP = 0x00895BD2;
	static float RenderPotionY = Fix_DisplayHeightExt + 445.5f;
	static float RenderNumberY = Fix_DisplayHeightExt + 460.0f;
	static float RenderPotionX = 277.0f;
	static float RenderNumberX = 291.0f;
	static int JCResto;

	JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	RenderNumberX += JCResto;
	RenderPotionX += JCResto;

	_asm
	{
		PUSH ECX; / Arg4
		FLD DWORD PTR DS : [RenderNumberY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg3
		FLD DWORD PTR DS : [RenderNumberX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg2
		FLD DWORD PTR DS : [RenderPotionY] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		PUSH ECX; | Arg1
		FLD DWORD PTR DS : [RenderPotionX] ; |
		FSTP DWORD PTR SS : [ESP] ; |
		MOV ECX, DWORD PTR SS : [EBP - 0x30] ; |
		JMP[Addr_JMP]; \main1.008979C0
	}
}

void JCCashShopLand(BYTE Mode)
{
	int v4; // ST10_4@1
	int JCResto; // ST10_4@1

	EnableAlphaTest(Mode);

	v4 = *(DWORD*)(GetInstance() + 252);

	for (int i = 0; i < 9; ++i)
	{
		//-- boton buy
		ChangeButtonInfo2((char*)(v4 + 172 * i + 168), *(DWORD*)(v4 + 36) + 122 * (i % 3) + 162, 121 * (i / 3) + 126, 52, 26);
	}
}

int JCCashShopModel(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, int a8, char a9)
{
	int v4; // ST10_4@1

	v4 = *(DWORD*)(GetInstance() + 252);

	return pDrawItemModel(PosX + *(DWORD*)(v4 + 36), PosY, Width, Height, ItemID, a6, a7, a8, a9);
}
//----- (00942EE0) --------------------------------------------------------
int sub_942EE0(int _this, int a2, int a3)
{
	int v4; // eax@1
	int JCResto; // ST10_4@1

	v4 = *(DWORD*)(GetInstance() + 252);

	JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	*(DWORD*)(v4 + 36) = JCResto;
	*(DWORD*)(v4 + 40) = 0;
	return 1;
}

bool JCCheckBannerShop(int x, int y, int w, int h)
{
	int v4; // eax@1

	v4 = *(DWORD*)(GetInstance() + 252);

	return pCheckMouseOver(*(DWORD*)(v4 + 36) + x, y, w, h);
}

void JCBannerShop(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int v4; // ST10_4@1

	v4 = *(DWORD*)(GetInstance() + 252);

	pDrawGUI(ImageID, PosX + *(DWORD*)(v4 + 36), PosY, Width, Height);
}

void BackPanelCash(int ImageID, float PosX, float PosY, float Width, float Height)
{
	pDrawGUI(ImageID, PosX, PosY, 640.0, 429.0);
}

__declspec(naked) void SlideShow()
{
	static DWORD Addr = 0x00425489;
	static DWORD CallMe = 0x00417EC0;
	_asm
	{
		PUSH 0; / Arg2 = 00000000
		PUSH 0; | Arg1 = 00000000
		MOV ECX, DWORD PTR SS : [EBP - 0x4] ; |
		ADD ECX, 0x4; |
		CALL CallMe; \main1.00417EC0
		PUSH 0; / Arg2 = 00000000
		PUSH 0; | Arg1 = 00000000
		MOV ECX, DWORD PTR SS : [EBP - 0x4] ; |
		ADD ECX, 0x8EC; |
		CALL CallMe; \main1.00417EC0
		JMP[Addr]; / Timerproc = NULL
	}
}

//----Illus
//----Illus //===Bach Long Dien

double JCRenderNumberIllus(float a1, float a2, int a3, float a4)
{
	double result; // st7@2
	float v5; // ST44_4@5
	float v6; // ST38_4@5
	signed int i; // [sp+38h] [bp-30h]@3
	float v8; // [sp+3Ch] [bp-2Ch]@3
	signed int v9; // [sp+44h] [bp-24h]@3
	char v10[32]; // [sp+48h] [bp-20h]@3
	float v11; // [sp+70h] [bp+8h]@3

	EnableAlphaTest(1);
	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290); // * 12.0
		itoa(a3, v10, 10);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.4000000119209290)/* * 16.0*/;
			RenderBitmap(31337, v11, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}

	return result;
}

void FixMiniMapIllus(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	RenderBitmap(ImageID, PosX + QTFrame.DisplayWinCDepthBox, PosY + QTFrame.DisplayHeightExt, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void FixMiniMapIllusBtnUD(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	RenderBitmap(ImageID, PosX + QTFrame.DisplayWinCDepthBox, PosY + QTFrame.DisplayHeightExt, Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}


int __thiscall CNewFrame::BtnIllus(char* thisa, int X, int Y, int Width, int Height)
{

	return ChangeButtonInfo2(thisa, X + QTFrame.DisplayWinCDepthBox, Y + QTFrame.DisplayHeightExt, Width, Height);
}



void FixRenderImageIllus(int a1, float a2, float a3, float a4, float a5)
{

	pDrawGUI(a1, a2 + QTFrame.DisplayWinExt, a3, a4, a5);
}


void FixNumberIllus(float a4, float a5, int Number, float a7)
{
	int JCResto = (int)pWinWidth / pWinHeightReal - 640;
	//pDrawGUI(87969, JCResto + 0.0, 480.0 - 12.0, 640.0, 12.0);

	JCRenderNumberIllus(a4 + JCResto, a5 + QTFrame.DisplayHeightExt, Number, a7);
}

void FixNumberTimeIllus2(float a4, float a5, int Number, float a7)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	//pDrawGUI(87969, JCResto + 0.0, 480.0 - 12.0, 640.0, 12.0);

	JCRenderNumber(a4 + QTFrame.DisplayWinCDepthBox, a5 + QTFrame.DisplayHeightExt, Number, a7);
}

void __cdecl RenderTipTextListIllus(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	((void(__cdecl*)(int a1, int a2, int a3, int a4, int a5, int a6, int a7)) 0x005BF700)(a1 + QTFrame.DisplayWinCDepthBox, a2 + QTFrame.DisplayHeightExt, a3, a4, a5, a6, a7);
}
bool CheckMouseTooltipIllus(int a1, int a2, int a3, int a4)
{

	return pCheckMouseOver(a1 + QTFrame.DisplayWinCDepthBox, a2 + QTFrame.DisplayHeightExt, a3, a4);
}

void DrawHp(float a1, float a2, int Value, float a4)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	if (gProtect.m_MainInfo.CustomInterfaceType == 5 || gProtect.m_MainInfo.CustomInterfaceType == 6)
	{

		pDrawBar(a1 - 15.0f, 445.0f, ViewCurHP, 1.0f);

	}
	else
	{
		pDrawBar(a1 + JCResto, Fix_DisplayHeightExt + 445.0f, ViewCurHP, 1.0f);
	}
}

void DrawMp(float a1, float a2, int Value, float a4)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 5 || gProtect.m_MainInfo.CustomInterfaceType == 6)
	{
		pDrawBar(a1 + JCResto, Fix_DisplayHeightExt + 445.0f, ViewCurMP, 1.0f);
	}
}


void DrawSD(float a1, float a2, int Value, float a4)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawBar(a1 + JCResto, Fix_DisplayHeightExt + 460.0f, ViewCurSD, 1.0f);

}

void DrawBP(float a1, float a2, int Value, float a4)
{
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	pDrawBar(a1 + JCResto, Fix_DisplayHeightExt + 460.0f, ViewCurBP, 1.0f);

}

__declspec(naked) void ChatFix()
{
	static DWORD ChatFix_buff = 0x00787BAD;
	_asm
	{
		FLD DWORD PTR DS : [0xD43849]
		jmp[ChatFix_buff]
	}
}

void sub_81A5B0(int a1)
{
	char MasterSkill_1[256] = { 0 }; // eax@6
	char MasterSkill_2[256] = { 0 }; // eax@6
	char MasterSkill_3[256] = { 0 }; // eax@6
	int v26; // ST18_4@6
	int v36; // [sp+10h] [bp-14Ch]@1

	v36 = a1;
	int JCResto; // eax@1
	int JCWinWidth; // eax@1
	JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
	JCResto = JCWinWidth / 2 - 320;

	pSetTextColor(pTextThis(), 0xFFu, 0x9Bu, 0, 0xFFu);
	//-- 1751 "Peace: %d"
	v26 = *(DWORD*)(v36 + 300);
	wsprintf(MasterSkill_1, pGetTextLine_(pTextLineThis, v26), gInterfaceBar.MasterPoint_1);
	pDrawText(pTextThis(), 92 + JCResto, 40, MasterSkill_1, 0, 0, (PINT)1, 0);
	//-- 1752 "Wisdom: %d"
	v26 = *(DWORD*)(v36 + 300) + 1;
	wsprintf(MasterSkill_2, pGetTextLine_(pTextLineThis, v26), gInterfaceBar.MasterPoint_2);
	pDrawText(pTextThis(), 302 + JCResto, 40, MasterSkill_2, 0, 0, (PINT)1, 0);
	//-- 1753 "Overcome: %d"
	v26 = *(DWORD*)(v36 + 300) + 2;
	wsprintf(MasterSkill_3, pGetTextLine_(pTextLineThis, v26), gInterfaceBar.MasterPoint_3);
	pDrawText(pTextThis(), 513 + JCResto, 40, MasterSkill_3, 0, 0, (PINT)1, 0);
}

__declspec(naked) void ResetPoint()
{
	static DWORD Addr_JMP = 0x00651C9C;
	static DWORD Sumatoria;
	static DWORD Addr;

	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 8]
		MOV DWORD PTR SS : [EBP - 4] , EAX
	}

	gInterfaceBar.MasterPoint_1 = 0;
	gInterfaceBar.MasterPoint_2 = 0;
	gInterfaceBar.MasterPoint_3 = 0;

	_asm
	{
		JMP[Addr_JMP]
	}
}

__declspec(naked) void sub_819D60()
{
	static DWORD Addr_JMP = 0x00819EC9;
	static DWORD Sumatoria;
	static DWORD Addr;

	_asm
	{
		MOVZX ECX, BYTE PTR SS : [EBP - 0x64]
		MOV Addr, ECX
		MOVZX ECX, BYTE PTR SS : [EBP + 0xC]
		MOV Sumatoria, ECX
	}

	if (Addr == 0)
	{
		gInterfaceBar.MasterPoint_1 += Sumatoria;
		Addr_JMP = 0x00819E7A;
	}
	else if (Addr == 1)
	{
		gInterfaceBar.MasterPoint_2 += Sumatoria;
		Addr_JMP = 0x00819E95;
	}
	else if (Addr == 2)
	{
		gInterfaceBar.MasterPoint_3 += Sumatoria;
		Addr_JMP = 0x00819EB0;
	}

	_asm
	{
		JMP[Addr_JMP]
	}
}

__declspec(naked) void Render_81A1BE()
{
	static DWORD Addr_JMP = 0x0081AAA1;
	static DWORD Addr;

	_asm
	{
		MOV EDX, DWORD PTR SS : [EBP - 0x14C]
		MOV Addr, EDX
	}

	sub_81A5B0(Addr);

	_asm
	{
		JMP[Addr_JMP]
	}
}


void CInterface::Load()
{
	//illusion

	//-- Illus //===Bach Long Dien
	SetCompleteHook(0xE8, 0x0086D5DE, &FixMiniMapIllusBtnUD);	//0x7BC8u	"Interface\\newui_ctskillup.jpg", 		
	SetCompleteHook(0xE8, 0x0086D60F, &FixMiniMapIllusBtnUD);	//0x7BC9u	"Interface\\newui_ctskilldown.jpg", 
	SetCompleteHook(0xE8, 0x0086D5AA, &FixMiniMapIllusBtnUD);	//0x7BBEu	"Interface\\newui_Bt_clearness_illusion.jpg"
	SetCompleteHook(0xE8, 0x0086D5C3, &CNewFrame::BtnIllus);//-text btn 0x7BC8u
	SetCompleteHook(0xE8, 0x0086D5F4, &CNewFrame::BtnIllus);//-text btn 0x7BC9u
	SetCompleteHook(0xE8, 0x0086D625, &CNewFrame::BtnIllus);//-text btn 0x7BBEu


	SetCompleteHook(0xE8, 0x0086D5C3, &CNewFrame::BtnIllus);//-text btn 0x7BBEu

	//----skill
	SetCompleteHook(0xE8, 0x0086E095, &FixNumberTimeIllus2);	// number point RenderNumber
	SetCompleteHook(0xE8, 0x0086E10D, &FixNumberTimeIllus2);	// number point RenderNumber
	SetCompleteHook(0xE8, 0x0086E01D, &FixMiniMapIllus);	//0x7A4Du | 0x7A53u	"Interface\\newui_skill2.jpg" | "Interface\\newui_non_skill2.jpg" 

	//--NumberSkill
	//---hover text on mouse
	SetCompleteHook(0xE8, 0x0086E3AD, &RenderTipTextListIllus);
	SetCompleteHook(0xE8, 0x0086E4D4, &RenderTipTextListIllus);
	SetCompleteHook(0xE8, 0x0086E5F9, &RenderTipTextListIllus);

	SetCompleteHook(0xE8, 0x0086E235, &CheckMouseTooltipIllus);
	SetCompleteHook(0xE8, 0x0086E3FD, &CheckMouseTooltipIllus);
	SetCompleteHook(0xE8, 0x0086E524, &CheckMouseTooltipIllus);

	//===Bach Long Dien

	SetCompleteHook(0xE8, 0x0086A4C4, &FixRenderImageIllus); //illusion_success ~ illusion_failure
	SetCompleteHook(0xE8, 0x0086A507, &FixRenderImageIllus);//illusion_success ~ illusion_failure

	//---TextNumber 
	SetCompleteHook(0xE8, 0x0086F25C, &FixNumberIllus);
	SetCompleteHook(0xE8, 0x0086F298, &FixNumberIllus);
	SetCompleteHook(0xE8, 0x0086F2D4, &FixNumberIllus);
	//----timeDown
	SetCompleteHook(0xE8, 0x0086E79F, &FixMiniMapIllusBtnUD);  // dau :
	SetCompleteHook(0xE8, 0x0086E830, &FixNumberTimeIllus2);	 // Time
	SetCompleteHook(0xE8, 0x0086E861, &FixNumberTimeIllus2);	 // Time
	SetCompleteHook(0xE8, 0x0086E8D2, &FixNumberTimeIllus2);	 // Time
	SetCompleteHook(0xE8, 0x0086E903, &FixNumberTimeIllus2);	 // Time
	SetCompleteHook(0xE8, 0x0086E6E9, &FixMiniMapIllus);	//0x7BCAu	 "Interface\\newui_ctgametimeframe.tga", 
	//-----------------
	SetCompleteHook(0xE8, 0x0086EB03, &FixMiniMapIllus);	//0x7BBCu	 "Interface\\newui_ctminmapframe.tga", 			
	SetCompleteHook(0xE8, 0x0086EA7A, &FixMiniMapIllus);	//0x7BBDu	 "Interface\\newui_ctminmap.jpg", 				
	SetCompleteHook(0xE8, 0x0086F0DC, &FixMiniMapIllus);	//0x7BBFu	 "Interface\\newui_ctminmap_Relic.tga", 		
	SetCompleteHook(0xE8, 0x0086ED1A, &FixMiniMapIllus);	//0x7BC0u	 "Interface\\newui_ctminmap_TeamA_box.tga", 	
	SetCompleteHook(0xE8, 0x0086EFAF, &FixMiniMapIllus);	//0x7BC1u	 "Interface\\newui_ctminmap_TeamA_member.tga", 	
	SetCompleteHook(0xE8, 0x0086EDCF, &FixMiniMapIllus);	//0x7BC2u	 "Interface\\newui_ctminmap_TeamA_npc.tga", 	
	SetCompleteHook(0xE8, 0x0086EC69, &FixMiniMapIllus);	//0x7BC3u	 "Interface\\newui_ctminmap_TeamB_box.tga", 	
	SetCompleteHook(0xE8, 0x0086EF3C, &FixMiniMapIllus);	//0x7BC4u	 "Interface\\newui_ctminmap_TeamB_member.tga", 	
	SetCompleteHook(0xE8, 0x0086EBB8, &FixMiniMapIllus);	//0x7BC5u	 "Interface\\newui_ctminmap_TeamB_npc.tga", 	
	SetCompleteHook(0xE8, 0x0086F218, &FixMiniMapIllus);	//0x7BC6u	 "Interface\\newui_ctminmap_Hero.tga", 			
	SetCompleteHook(0xE8, 0x0086EA0B, &FixMiniMapIllus);	//0x7BC7u	 "Interface\\newui_ctskillframe.tga", 			

	//--------------------------------------------------------------------------------------------------------------------------

	SetCompleteHook(0xE9, 0x00425468, &SlideShow);
	//-- MasterSkill
	//JCInterfaceMaster.Load( );
	//-- Inventory
	/*SetCompleteHook(0xE8, 0x007DC9E6, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCA78, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCB05, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCB96, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCC16, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCCA8, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCD35, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCDB4, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCE51, &JCItemStacknumber); //-- Number Stack
	SetCompleteHook(0xE8, 0x007DCEE7, &JCItemStacknumber); //-- Number Stack*/
	//--
	SetCompleteHook(0xE9, 0x00895600, &JCStacknumberpotion); //-- Number Stack

	SetCompleteHook(0xE8, 0x00814F0D, &JCShowTimerBar);
	SetCompleteHook(0xE8, 0x00814E63, &JCShownumberSkill);
	SetCompleteHook(0xE8, 0x00814DC1, &JCShowSlotSkill);
	SetCompleteHook(0xE8, 0x00814D4D, &JCShowSlotSkill);
	SetCompleteHook(0xE9, 0x008126C0, &JCEventMouseSkill); //-- Skill event
	SetCompleteHook(0xE9, 0x00813970, &JCSkillSwitchBar); //-- Skill Switch
	SetCompleteHook(0xE8, 0x0080F833, &JCSkillSelectBar); //-- Skill barr / Select

	SetCompleteHook(0xE9, 0x00651C96, &ResetPoint); //-- Obtain Skill Point Reset
	SetCompleteHook(0xE9, 0x00819E66, &sub_819D60); //-- Obtain Skill Point
	SetCompleteHook(0xE9, 0x0081A999, &Render_81A1BE);


	switch (gProtect.m_MainInfo.CustomInterfaceType)
	{
	case Classic:


		SetOp((LPVOID)0x0080FF28, (LPVOID)DrawHp, ASM::CALL);
		SetOp((LPVOID)0x008100BB, (LPVOID)DrawMp, ASM::CALL);

		SetOp((LPVOID)0x00810389, (LPVOID)DrawBP, ASM::CALL);
		SetOp((LPVOID)0x00810659, (LPVOID)DrawSD, ASM::CALL);
		//FrameChat.Load( );
		//SetCompleteHook(0xE9, 0x007DFA60, &PetHPBarEx);
		//-- Slot consumables
		SetCompleteHook(0xE9, 0x00895A48, &RenderSlotQ);
		SetCompleteHook(0xE9, 0x00895ABD, &RenderSlotW);
		SetCompleteHook(0xE9, 0x00895B32, &RenderSlotE);
		SetCompleteHook(0xE9, 0x00895BA7, &RenderSlotR);
		//-- ExpBar || Master Exp
		//SetCompleteHook(0xE8, 0x0080FF28, &RenderNumber); //-- HP
		//SetCompleteHook(0xE8, 0x008100BB, &RenderNumber); //-- MP
		//SetCompleteHook(0xE8, 0x00810389, &RenderNumber); //-- SD
		//SetCompleteHook(0xE8, 0x00810659, &RenderNumber); //-- BP
		//-- ExpBar || Master Exp
		SetCompleteHook(0xE8, 0x00810F45, &RenderNumber); //-- EXP
		SetCompleteHook(0xE8, 0x008117EE, &RenderNumber); //-- MASTEREXP

		//-- Tooltip Attributos hp mp bp sd
		SetCompleteHook(0xE8, 0x0080FFA7, &JCTooltipDraw);
		SetCompleteHook(0xE8, 0x0081013A, &JCTooltipDraw);
		SetCompleteHook(0xE8, 0x00810408, &JCTooltipDraw);
		SetCompleteHook(0xE8, 0x008106EA, &JCTooltipDraw);
		//-- check atributos hp mp bp sd
		SetCompleteHook(0xE8, 0x0080FF56, &JCCheckMouseTooltip);
		SetCompleteHook(0xE8, 0x008100E9, &JCCheckMouseTooltip);
		SetCompleteHook(0xE8, 0x008103B7, &JCCheckMouseTooltip);
		SetCompleteHook(0xE8, 0x00810699, &JCCheckMouseTooltip);
		//-- barra de experiencia/ master experiencia
		SetCompleteHook(0xE8, 0x00810A1A, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00810BE5, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00810D2C, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00810DC3, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00810EF0, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x008112A6, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x0081147F, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x008115C9, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00811660, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00811790, &JCRenderBarExp);
		SetCompleteHook(0xE8, 0x00810A97, &JCJCRenderBarExpAdd);
		SetCompleteHook(0xE8, 0x00810C62, &JCJCRenderBarExpAdd);
		SetCompleteHook(0xE8, 0x00810E40, &JCJCRenderBarExpAdd);
		SetCompleteHook(0xE8, 0x00811323, &JCJCRenderBarExpAdd);
		SetCompleteHook(0xE8, 0x008114FC, &JCJCRenderBarExpAdd);
		SetCompleteHook(0xE8, 0x008116DD, &JCJCRenderBarExpAdd);

		SetCompleteHook(0xE8, 0x00810FE7, &JTooltipExpCurrent);
		SetCompleteHook(0xE8, 0x00811890, &JTooltipExpCurrent);
		//--
		SetCompleteHook(0xE8, 0x00810F97, &JCheckExpBarCurrent);
		SetCompleteHook(0xE8, 0x00811840, &JCheckExpBarCurrent);
		//-- imagenes centrales bar
		SetCompleteHook(0xE8, 0x008119E6, &RenderButtonQuest);
		SetCompleteHook(0xE8, 0x0080F92D, &InterfaceLeft);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080F968, &InterfaceMiddle);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080F9A3, &InterfaceRight);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080FA02, &InterfaceMiddle);	//-- Letter Print
		//-- attributo hp mana
		SetCompleteHook(0xE8, 0x0080FEEF, &WideRedHP);	//-- Red Hp
		SetCompleteHook(0xE8, 0x0080FE56, &WideGreenHP);	//-- Letter Print
		SetCompleteHook(0xE8, 0x00810083, &WideBlueMP);	//-- Letter Print
		//-- attributo sd bp
		SetCompleteHook(0xE8, 0x00810354, &WideAttributoBP);	//-- bp Print
		SetCompleteHook(0xE8, 0x00810624, &WideAttributoSD);	//-- sd Print

		SetByte(0x004D128F, 0x1D); //fix screen 640x320

		//--fix icon small
		/*SetFloat((DWORD)(0x00D43220), 8);
		SetFloat((DWORD)(0x00D43224), 12);
		SetByte((DWORD)(0x00777E70), 0x16);*/

		//SetByte((DWORD)(0x007D399F + 1), 0xFF); // disable T
		//SetCompleteHook(0xE9, 0x007D399F, 0x007D39D8); //  disable (T)
		//SetCompleteHook (0xE9,0x0077EB65,0x0077EC0E); // disable (T) Quest  Menu Key C 
		//MemorySet(0x0062F876, 0x90, 0x30);			//-> Disable ViewMap (Key TAB)

		break;
	case Ex700:
		gCChatEx.Load();

		InitSeason15();

		SetRange((LPVOID)0x00787BA7, 5, ASM::NOP);
		SetJmp((LPVOID)0x00787BA7, ChatFix);

		SetCompleteHook(0xE9, 0x00895A48, &RenderEx700SlotQ);
		SetCompleteHook(0xE9, 0x00895ABD, &RenderEx700SlotW);
		SetCompleteHook(0xE9, 0x00895B32, &RenderEx700SlotE);
		SetCompleteHook(0xE9, 0x00895BA7, &RenderEx700SlotR);

		//SetCompleteHook(0xE9, 0x007DFA60, &PetHPBarEx);

		//SetCompleteHook(0xE9, 0x00812120, &sub_812120); //--
		//-- Experiencia
		SetCompleteHook(0xE8, 0x00810F45, &JBarNumberExp);
		SetCompleteHook(0xE8, 0x008117EE, &JBarNumberExp);
		//--
		SetCompleteHook(0xE8, 0x00810FE7, &JTooltipExpCurrent);
		SetCompleteHook(0xE8, 0x00811890, &JTooltipExpCurrent);
		//--
		SetCompleteHook(0xE8, 0x00810F97, &JCheckExpBarCurrent);
		SetCompleteHook(0xE8, 0x00811840, &JCheckExpBarCurrent);
		//--
		SetCompleteHook(0xE8, 0x00810A1A, &JCurrentExp);
		SetCompleteHook(0xE8, 0x00810BE5, &JCurrentMoveExp);
		SetCompleteHook(0xE8, 0x00810D2C, &JCurrentExp);
		SetCompleteHook(0xE8, 0x00810DC3, &JCurrentExp);
		SetCompleteHook(0xE8, 0x00810EF0, &JCurrentExp);
		//--
		SetCompleteHook(0xE8, 0x008112A6, &JCurrentExp);
		SetCompleteHook(0xE8, 0x0081147F, &JCurrentMoveExp);
		SetCompleteHook(0xE8, 0x008115C9, &JCurrentExp);
		SetCompleteHook(0xE8, 0x00811660, &JCurrentExp);
		SetCompleteHook(0xE8, 0x00811790, &JCurrentExp);
		//--
		SetCompleteHook(0xE8, 0x00810A97, &JCurrentAddExp);
		SetCompleteHook(0xE8, 0x00810C62, &JCurrentAddExp);
		SetCompleteHook(0xE8, 0x00810E40, &JCurrentAddExp);
		SetCompleteHook(0xE8, 0x00811323, &JCurrentAddExp);
		SetCompleteHook(0xE8, 0x008114FC, &JCurrentAddExp);
		SetCompleteHook(0xE8, 0x008116DD, &JCurrentAddExp);
		//--
		MemorySet(0x0080F845, 0x90, 0x5); //-- eliminar attributo hp mana
		MemorySet(0x0080F855, 0x90, 0x5); //-- eliminar attributo hp mana
		MemorySet(0x0080F84D, 0x90, 0x5); //-- eliminar attributo hp mana
		MemorySet(0x0080FF28, 0x90, 0x5); //-- eliminar attributo hp mana number
		MemorySet(0x008100BB, 0x90, 0x5); //-- eliminar attributo hp mana number
		MemorySet(0x00810389, 0x90, 0x5); //-- eliminar attributo hp mana number
		MemorySet(0x00810659, 0x90, 0x5); //-- eliminar attributo hp mana number
		//-- attributo hp mana
		SetCompleteHook(0xE8, 0x0080FEEF, &JAttributoPlayer);	//-- hp
		SetCompleteHook(0xE8, 0x0080FE56, &JAttributoPlayer);	//-- hp venom
		SetCompleteHook(0xE8, 0x00810083, &JAttributoPlayer);	//-- mana
		SetCompleteHook(0xE8, 0x00810624, &JAttributoPlayer);	//-- SD
		SetCompleteHook(0xE8, 0x00810354, &JAttributoPlayer);	//-- AG
		SetCompleteHook(0xE8, 0x0080FF56, &JAttributoCheck);	//-- HP
		SetCompleteHook(0xE8, 0x008100E9, &JAttributoCheck);	//-- MP
		SetCompleteHook(0xE8, 0x00810699, &JAttributoCheck);	//-- SD
		SetCompleteHook(0xE8, 0x008103B7, &JAttributoCheck);	//-- AG
		//--
		SetCompleteHook(0xE8, 0x0080FFA7, &JAttributoTooltip);	//-- HP
		SetCompleteHook(0xE8, 0x0081013A, &JAttributoTooltip);	//-- MP
		SetCompleteHook(0xE8, 0x00810408, &JAttributoTooltip);	//-- AG
		SetCompleteHook(0xE8, 0x008106EA, &JAttributoTooltip);	//-- SD
		//-- imagenes centrales bar
		MemorySet(0x0080F258, 0x90, 0x5); //-- Menu in-game
		SetCompleteHook(0xE8, 0x0080F92D, &JExInterfaceLeft);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080F968, &JExInterfaceMiddle1);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080F9A3, &JExInterfaceRight);	//-- Letter Print
		SetCompleteHook(0xE8, 0x0080FA02, &JExInterfaceMiddle2);	//-- Letter Print
		break;
	}
}