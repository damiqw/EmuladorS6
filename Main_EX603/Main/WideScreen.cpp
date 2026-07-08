#include "stdafx.h"
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
#include "CustomInterface.h"
#include "Protect.h"
#include "MiniMapBrujula.h"
#include "Common.h"

#if (WIDE_SCREEN == 2)

CNewFrame QTFrame;
//===Fix Y BB
int __thiscall CNewFrame::CNewUIMyInventory(int thisa, int PosX, int PosY)
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00834420)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIGuildInfoWindow(int thisa, int PosX, int PosY)
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x007CA630)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUICharacterInfoWindow(int thisa, int PosX, int PosY)
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x0077ED70)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUICommandWindow(int thisa, int PosX, int PosY)
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x0078E7F0)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUICastleWindow(int thisa, int PosX, int PosY) //008790A2
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00879710)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIGuardWindow(int thisa, int PosX, int PosY) //008836F2
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00883AD0)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIGatemanWindow(int thisa, int PosX, int PosY) //00880B8B
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00880E20)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIGateSwitchWindow(int thisa, int PosX, int PosY) //0088258B
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00882760)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIGuildMakeWindow(int thisa, int PosX, int PosY) //007D06A8
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x007D1B40)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIMyQuestInfoWindow(int thisa, int PosX, int PosY) //0083E156,0085ED6C,0085EEBE,0085FA2D,0086003E
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x0083E1D0)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIPartyInfoWindow(int thisa, int PosX, int PosY) //0084A076
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x0084B180)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUINPCQuest(int thisa, int PosX, int PosY) //0084511B
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00845290)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIEnterBloodCastle(int thisa, int PosX, int PosY) //0087436B
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x008744C0)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CNewUIEnterDevilSquare(int thisa, int PosX, int PosY) //00877E4B
{
	return ((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x00877FA0)(thisa, PosX, PosY + (QTFrame.DisplayHeightExt / 2));
}
int __thiscall CNewFrame::CUILetterWriteWindow(int thisa, int a1, int PosX, int PosY, const char* a5,int a6,char a7)
{
	return ((int(__thiscall*)(int thisa, int a1, int PosX, int PosY, const char* a5, int a6, char a7)) 0x0049DFD0)(thisa, a1, PosX+ QTFrame.DisplayWinExt, PosY + (QTFrame.DisplayHeightExt / 2),a5,a6,a7);
}
int __thiscall CNewFrame::CNewUIMessageBoxBaseCreate(int thisa, int x, int y, int width, int height, float fPriority)
{
	return ((int(__thiscall*)(int thisa, int x, int y, int width, int height, float fPriority)) 0x00823CA0)(thisa, x + QTFrame.DisplayWinExt, y, width, height, fPriority);
}
int __thiscall CNewFrame::FixEventTime(DWORD* This, int a2, int a3)
{
	int result; // eax
	This[4] = a2 + QTFrame.DisplayWinExt; //X
	result = a3 + QTFrame.DisplayHeightExt;
	This[5] = a3 + QTFrame.DisplayHeightExt; //Y
	return result;
}

int __thiscall CNewFrame::CNewUIWindowMenuPos(DWORD* This, int a2, int a3)
{

	This[4] = a2 + QTFrame.DisplayWinExt; //X
	This[5] = (a3 + QTFrame.DisplayHeightExt)-30; //Y
	return *This;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//-- DisplaYFrame
//////////////////////////////////////////////////////////////////////////////////////////////
signed int FrameScreenWidth()
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
			v52 = 570;
	}

	return (int)(QTFrame.DisplayWin - v52);
}

//=================
int __cdecl sub_10010FF0(float a1, float a2, int a3, int a4, float a5, int a6)
{
	float v7; // [esp+8h] [ebp-10h]
	float v8; // [esp+Ch] [ebp-Ch]

	v8 = (float)QTFrame.DisplayHeight;
	v7 = (float)QTFrame.DisplayWin;
	pDrawBarForm(LODWORD(a1), LODWORD(a2), LODWORD(v7), LODWORD(v8), LODWORD(a5), a6);
	return 1;
}
//==Fix Size Model
int FixSizeItem(float a1, float a2, float a3, float a4)
{
	float SizeItem;;

	if (gProtect.m_MainInfo.ScaleItem == 0)
	{
		SizeItem = 1.0f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 1)
	{
		SizeItem = 1.2f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 2)
	{
		SizeItem = 1.3f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 3)
	{
		SizeItem = 1.4f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 4)
	{
		SizeItem = 1.5f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 5)
	{
		SizeItem = 1.6f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 6)
	{
		SizeItem = 1.7f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 7)
	{
		SizeItem = 1.8f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 8)
	{
		SizeItem = 1.9f;
	}
	else if (gProtect.m_MainInfo.ScaleItem == 9)
	{
		SizeItem = 2.0f;
	}
	
	if (pGameResolutionMode >= 3) 
	{ 
		SizeItem += 0.40f; 
	}

	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	return sub_6358A0_Addr(SizeItem, a2, a3, a4);
}

#define BmCUIControlSetPosition				((int(__thiscall*)(int This, int a2, int a3)) 0x00417EC0)

int __thiscall CNewFrame::CUIControlSetPosition(int This, int a2, int a3)
{
	int FixX = (WS_WIN_WIDTHADD + a2) + 140; //aCA SE ACOMODA EL MARCO NEGRO DE LA MAQUINA SOCKET EBELAND LO NORMAL ES 90. resolucion 800x600- actual 920
	return BmCUIControlSetPosition(This, FixX, a3);
}
//==Fix Y SelectObjects
bool FixYSelectObjects(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h + QTFrame.DisplayHeightExt);
}

//==Fix Chon NV
bool SelectObjects(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, FrameScreenWidth(), 429 + QTFrame.DisplayHeightExt);
}

bool DropItem(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, FrameScreenWidth(), 429 + QTFrame.DisplayHeightExt);
}
//===Fix Map Name TGA
void PictureMapName(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	RenderBitmap(ImageID, (FrameScreenWidth() * pWinWidthReal - 166) / 2, ((220.0f + QTFrame.DisplayHeightExt) * pWinHeightReal), Width, Height, Arg6, Arg7, ScaleX, ScaleY, ScaleSize, ScalePosition, ScaleAlpha);
}

void FCNewUIWindowMenuPos(int a1, float a2, float a3, float a4, float a5)
{

	pDrawGUI(a1, a2, a3 + QTFrame.DisplayHeightExt, a4, a5);
}

inline int GetPosXCreateCharacter()
{
	int Ret = 0;
	switch (pGameResolutionMode)
	{
	case 0: Ret = -125.f; break;//listo
	case 1: Ret = -90.f; break;//listo
	case 2: Ret = -50.f; break;//listo
	case 3: Ret = -25.f; break;//listo
	case 4: Ret = -10.f; break;//listo
	case 5: Ret = -35.f; break;//listo
	case 6: Ret = -35.f; break;//listo
	case 7: Ret = -25.f; break;//listo
	case 8: Ret = -25.f; break;//listo
	}
	return Ret;
}

inline int GetPosYCreateCharacter()
{
	int Ret = 0;
	switch (pGameResolutionMode)
	{
	case 0: Ret = -12.f; break;   //640x480//listo
	case 1: Ret = 23.f; break;	  //800x600//listo
	case 2: Ret = 49.f; break;	  //1024x768//listo
	case 3: Ret = 45.f; break;	  //1280x1024//listo
	case 4: Ret = 56.f; break;	  //1366x768//listo
	case 5: Ret = 56.f; break;	  //1440x900//listo
	case 6: Ret = 56.f; break;	  //1600x900//listo
	case 7: Ret = 109.f; break;	  //1680x1050//listo
	case 8: Ret = 106.f; break;	  //1920x1080//listo
	}
	return Ret;
}

void CBRenderCreateCharacter(GLint a1, int a2, GLsizei width, GLsizei height)
{
	switch (pGameResolutionMode)
	{
	case 0:
		JCBeginOpengl(320 - (310 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 520 / pWinWidthReal, 245 / pWinHeightReal);//1280x768
		break;//listo
	case 1:
		JCBeginOpengl(320 - (310 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 500 / pWinWidthReal, 265 / pWinHeightReal);//1280x768
		break;//listo
	case 2:
		JCBeginOpengl(320 - (260 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 360 / pWinWidthReal, 210 / pWinHeightReal);//1280x768
		break;//listo
	case 3:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 320 / pWinWidthReal, 215 / pWinHeightReal);//1024x768
		break;//listo
	case 4:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 280 / pWinWidthReal, 185 / pWinHeightReal);//1024x768
		break;//listo
	case 5:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 350 / pWinWidthReal, 190 / pWinHeightReal);//1024x768
		break;//listo
	case 6:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 350 / pWinWidthReal, 190 / pWinHeightReal);//1024x768
		break;//listo
	case 7:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 350 / pWinWidthReal, 170 / pWinHeightReal);//1024x768
		break;//listo
	case 8:
		JCBeginOpengl(320 - (280 / 2) / pWinWidthReal + GetPosXCreateCharacter(), 75 / pWinHeightReal + GetPosYCreateCharacter(), 350 / pWinWidthReal, 170 / pWinHeightReal);//1024x768
		break;//listo
	}

}

void GLCreateWindowEx( )
{
	int FrameWin;
	int FrameWinMid;
	int FrameWinExt;
	int FrameWinCDepthBox;

	((signed int (*)())0x004D0FC0)( );
	//*(float*)0xE7C3D4 = (double)(unsigned int)pWinHeight / 480.0;
	double v0; // st3
	//if (pGameResolutionMode <= 1)
	//{
	//	pWinWidthReal = (double)pWinWidth / 640.0;
	//	pWinHeightReal = (double)pWinHeight / 480.0;
	//}
	//else
	
		if (pGameResolutionMode <= 1)
		{
			pWinWidthReal = (double)pWinWidth / 920.0;
			pWinHeightReal = (double)pWinHeight / 600.0;
		}
		else if (pGameResolutionMode <= 6)
		{
			pWinWidthReal = 1.25;
			pWinHeightReal = 1.25;
			
		}
		else
		{
			if (gProtect.m_MainInfo.ScaleWidescreen == 0)
			{
				pWinWidthReal = 1.50; //Best 2.0 value
				pWinHeightReal = 1.50;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 1)
			{
				pWinWidthReal = 1.55; //Best 2.0 value
				pWinHeightReal = 1.55;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 2)
			{
				pWinWidthReal = 1.60; //Best 2.0 value
				pWinHeightReal = 1.60;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 3)
			{
				pWinWidthReal = 1.65; //Best 2.0 value
				pWinHeightReal = 1.65;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 4)
			{
				pWinWidthReal = 1.70; //Best 2.0 value
				pWinHeightReal = 1.70;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 5)
			{
				pWinWidthReal = 1.75; //Best 2.0 value
				pWinHeightReal = 1.75;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 6)
			{
				pWinWidthReal = 1.80; //Best 2.0 value
				pWinHeightReal = 1.80;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 7)
			{
				pWinWidthReal = 1.85; //Best 2.0 value
				pWinHeightReal = 1.85;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 8)
			{
				pWinWidthReal = 1.90; //Best 2.0 value
				pWinHeightReal = 1.90;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 9)
			{
				pWinWidthReal = 1.95; //Best 2.0 value
				pWinHeightReal = 1.95;
			}
			else if (gProtect.m_MainInfo.ScaleWidescreen == 10)
			{
				pWinWidthReal = 2.00; //Best 2.0 value
				pWinHeightReal = 2.00;
			}
		}

	

	FrameWinCDepthBox = (int)(pWinWidth / pWinWidthReal - 920); //dejar asi esto configura los TIEMPO EN LOS EVENTOS interface
	FrameWin = (int)pWinWidth / pWinWidthReal;
	FrameWinMid = (int)pWinWidth / pWinWidthReal / 2;
	FrameWinExt = (int)pWinWidth / pWinWidthReal / 2 - 320;

	QTFrame.DisplayWinCDepthBox = (int)pWinWidth / pWinWidthReal - 640;
	QTFrame.DisplayWin = (int)pWinWidth / pWinWidthReal;
	QTFrame.DisplayWinMid = (int)pWinWidth / pWinWidthReal / 2;
	QTFrame.DisplayWinExt = (int)pWinWidth / pWinWidthReal / 2 - 320;
	QTFrame.DisplayWinReal = (int)QTFrame.DisplayWin / 640.0;
	//--
	QTFrame.DisplayHeight = (int)((double)pWinHeight / pWinHeightReal);
	QTFrame.DisplayHeightExt = (int)((double)QTFrame.DisplayHeight - 480.0);
	//--

	int Win1 = (int)FrameWin - 190;					// - DisplayWin Open1;
	int Win2 = (int)FrameWin - 380;					// - DisplayWin Open2;
	int Win3 = (int)FrameWin - 570;					// - DisplayWin Open3;
	int WinC = (int)FrameWinMid - 50;					// - DisplayWin OpenCentral;
	int BoxGobil = (int)FrameWin - 380;					// - DisplayWin OpenCentral;
//--
	SetFloat(0x82AFEF, (QTFrame.DisplayHeight*0.5)); //-- Effect

	SetDword(0x0059792D+1,( FrameWinMid));			//-- Notice

	SetDword(0x00597927 +1,( 0x12C+ QTFrame.DisplayHeightExt));			

	SetDouble(0xD23AB8, FrameWin); //-- Fix Lech Text  Button
//--
	SetDword(0x0094880C+1, (FrameWinMid - 95));		//-- Box0 BuyCash
	SetDword(0x0094880C+1, (FrameWinMid - 99));		//-- Box1 BuyCash
	SetDword(0x0094A2AC+1, (FrameWinMid - 107));	//-- Box2 BuyCash
	SetDword(0x0094B4A7+1, (FrameWinMid - 95));		//-- Box3 BuyCash
	SetDword(0x0094BDCD+1, (FrameWinMid - 95));		//-- Box4 BuyCash
	SetDword(0x0094C89C+1, (FrameWinMid - 105));	//-- Box5 BuyCash
	SetDword(0x0094DA8A+1, (FrameWinMid - 105));	//-- Box6 BuyCash
	SetDword(0x0094F0EA+1, (FrameWinMid - 95));		//-- Box7 BuyCash
	SetDword(0x0094FE7C+1, (FrameWinMid - 105));	//-- Box8 BuyCash
	SetDword(0x00950934+1, (FrameWinMid - 95));		//-- Box9 BuyCash
	SetDword(0x009515B1+1, (FrameWinMid - 95));		//-- Box10 BuyCash
	SetDword(0x0085A10F+1, (FrameWinMid - 95));		//-- WindowsOption
//--
	SetDword((0x0085A6A8+1), Win1); // inventory X OK
	SetDword((0x0085A8AE+1), Win1); //CNewUICastleWindow
	SetDword((0x0085A92D+1), Win1); //CNewUIGuardWindow
	SetDword((0x0085A9AC+1), Win1); //CNewUIGatemanWindow Tidus
	SetDword((0x0085AA2B+1), Win1); //CNewUIGateSwitchWindow
	SetDword((0x0085AB41+1), Win1); //CNewUIGuildInfoWindow
	SetDword((0x0085ABCF+1), Win1); //CNewUIGuildMakeWindow
	SetDword((0x0085AD78+1), Win1); //CNewUICharacterInfoWindow
	SetDword((0x0085AE06+1), Win1); //CNewUIMyQuestInfoWindow
	SetDword((0x0085AE94+1), Win1); //CNewUIPartyInfoWindow
	SetDword((0x0085AFB0+1), Win1); //CNewUINPCQuest
	SetDword((0x0085B048+1), Win1); //CNewUIEnterBloodCastle
	SetDword((0x0085B0D6+1), Win1); //CNewUIEnterDevilSquare
	SetDword((0x0085B4D9+1), Win1); //CNewUICommandWindow
	//==
	SetDword((0x0085B56D+1), Win1); //CNewUICatapultWindow
	SetDword((0x0085C020+1), Win1); //CNewUIGoldBowmanWindow
	SetDword((0x0085C0B4+1), Win1); //CNewUIGoldBowmanLena
	SetDword((0x0085C270+1), Win1); //CNewUIDuelWatchWindow
	SetDword((0x0085C4C0+1), Win1); //CNewUIDoppelGangerWindow
	SetDword((0x0085C5F2+1), Win1); //CNewUINPCDialogue
	SetDword((0x0085C686+1), Win1); //CNewUIQuestProgress
	SetDword((0x0085C71A+1), Win1); //CNewUIQuestProgressByEtc
	SetDword((0x0085C7AE+1), Win1); //CNewUIEmpireGuardianNPC
	SetDword((0x0085C977+1), Win1); //CNewUIUnitedMarketPlaceWindow
	SetDword((0x007F8277+3), Win1); //-- skill helper CNewUIMacro::LoadSkillList
	SetDword((0x0085CC36+1), Win1); //CNewUIMacro
	SetDword((0x0085F78B+1), Win1); //CNewUIQuestProgressByEtc
	//SetDword((0x0085F789+1), 0x15); //CNewUIQuestProgressByEtc
	SetDword((0x0085F87A+1), Win1); //CNewUIGensRanking
	SetDword((0x0085FA1A+1), Win1);
	SetDword((0x0085FA45+1), Win1);
	SetDword((0x0085FA8B+1), Win1);
	SetDword((0x0085FD25+1), Win1);
	SetDword((0x0085FE8D+1), Win1);
	SetDword((0x00860033+1), Win1);
	//--
	//
	SetDword((0x0085A731+1), Win2);
	SetDword((0x0085A7B0+1), Win2);

	SetDword((0x0085A82F+1), Win2);	// seed 

	SetDword((0x0085AAB3+1), Win2); //CNewUIStorageInventory
	SetDword((0x0085AC5F+1), Win2); //CNewUIMyShopInventory
	SetDword((0x0085ACEA+1), Win2); //CNewUIPurchaseShopInventory::SetPos 0084FA90
	SetDword((0x0085B1F5+1), Win2); //CNewUITrade
	SetDword((0x0085C148+1), Win2); //CNewUIRegistrationLuckyCoin
	SetDword((0x0085C1DC+1), Win2); //CNewUIExchangeLuckyCoin
	SetDword((0x0085CA15+1), Win2); //CNewUILuckyItemWnd::SetPos 007F0460
	SetDword((0x0085CAA9+1), Win2); //CNewUIInvenExpansion
	SetDword((0x0085CB3D+1), Win2); //CNewUIStorageExpansion
	SetDword((0x0085CCCA+1), Win2);//CNewUIMacroSub AutoMu
	SetDword((0x0085ED59+1), Win2); //CNewUIMyQuestInfoWindow::SetPos  0083E1D0
	SetDword((0x0085EDF7+1), Win2);//CNewUIMyInventory::SetPos 00834420
	SetDword((0x0085EE7E+1), Win2);
	SetDword((0x0085EEAB+1), Win2);
	SetDword((0x0085F0F1+1), Win2);
	SetDword((0x0085F7B6+1), Win2);
	//--
	SetDword((0x007D5953+1), Win2);
	SetDword((0x007D5997+1), Win2);//<-- Viewport
	SetDword((0x007D59BB+1), Win2);//CNewUIMixInventory::SetPos 0082C340
	SetDword((0x007D59FF+2), Win2);//<-- Viewport
	SetDword((0x007D5A24+1), Win2); //CNewUINPCShop::SetPos 00846B90
	SetDword((0x007D5A68+2), Win2);//<-- Viewport
	SetDword((0x007D5A8D+1), Win2);//CNewUIPurchaseShopInventory::SetPos
	SetDword((0x007D5AD1+1), Win2);//<-- Viewport
	SetDword((0x007D5AF5+1), Win2);
	SetDword((0x007D5B39+2), Win2);//<-- Viewport
	SetDword((0x007D5B5E+1), Win2);
	SetDword((0x007D5BA2+2), Win2);//<-- Viewport
	SetDword((0x007D5BC9+1), Win2);
	SetDword((0x007D5C0D+1), Win2);//<-- Viewport
	SetDword((0x007D5C59+2), Win2);//<-- Viewport
	SetDword((0x007D5C89+1), Win2);
	SetDword((0x007D5CB5+1), Win2); //-- 
	
	//--
	//===Fix Box
	SetCompleteHook(0xE8, 0x00791BD0, &QTFrame.CNewUIMessageBoxBaseCreate); //Box Master Skill Up
	SetCompleteHook(0xE8, 0x00791C40, &QTFrame.CNewUIMessageBoxBaseCreate); //CNewUICommonMessageBox
	SetCompleteHook(0xE8, 0x00792E80, &QTFrame.CNewUIMessageBoxBaseCreate); //0x00792E4A
	SetCompleteHook(0xE8, 0x00792F30, &QTFrame.CNewUIMessageBoxBaseCreate); //0x00792EFA
	SetCompleteHook(0xE8, 0x007A0C58, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A0C1F
	SetCompleteHook(0xE8, 0x007A229F, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A2266
	SetCompleteHook(0xE8, 0x007A3534, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A34EF
	SetCompleteHook(0xE8, 0x007A47CC, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A4796
	SetCompleteHook(0xE8, 0x007A557C, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A5546
	SetCompleteHook(0xE8, 0x007A703E, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A6FF6
	SetCompleteHook(0xE8, 0x007A8227, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A81F1
	SetCompleteHook(0xE8, 0x007A8ED1, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A8E9B
	SetCompleteHook(0xE8, 0x007A9331, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A92FB
	SetCompleteHook(0xE8, 0x007A9A11, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A99DB CChaosCastleResultMsgBox
	SetCompleteHook(0xE8, 0x007A9EC7, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007A9E91 //Box Gobil
	SetCompleteHook(0xE8, 0x007AAB57, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007AAB21
	SetCompleteHook(0xE8, 0x007AB8EF, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007AB8B9
	SetCompleteHook(0xE8, 0x007AC60F, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007AC5D9
	SetCompleteHook(0xE8, 0x007AD597, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007AD561
	SetCompleteHook(0xE8, 0x007ADDF7, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007ADDC1
	SetCompleteHook(0xE8, 0x007AE642, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007AE601
	SetCompleteHook(0xE8, 0x007B26C2, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B2681
	SetCompleteHook(0xE8, 0x007B2FF2, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B2FB1
	SetCompleteHook(0xE8, 0x007B3AA2, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B3A61
	SetCompleteHook(0xE8, 0x007B4632, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B45F1
	SetCompleteHook(0xE8, 0x007B5332, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B52F1
	SetCompleteHook(0xE8, 0x007B5D22, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B5CE1
	SetCompleteHook(0xE8, 0x007B670E, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B66CD
	SetCompleteHook(0xE8, 0x007B74C7, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B7491
	SetCompleteHook(0xE8, 0x007B85C2, &QTFrame.CNewUIMessageBoxBaseCreate); //0x007B7491
	SetCompleteHook(0xE8, 0x00947A52, &QTFrame.CNewUIMessageBoxBaseCreate); //Box CashShop CMsgBoxIGSBuyConfirm


	//-- Add Ext
	/////test
	//SetDword((0x00EBC0F4+3), WinC);
	/////main.exe+EBC0F4 
	SetCompleteHook(0xE8, 0x0041F53F, &QTFrame.CUIControlSetPosition); //Fix List Mix Socket

	SetDword((0x0081A5EA+1), (0x1CA+FrameWinExt));						//-- Check Masterskill tooltip
	SetDword((0x0081A652+1), (0x1DA+FrameWinExt));						//-- tooltip
	SetDword((0x0042B036+1), (0x1EA+FrameWinExt));						//TextBox(CashShop)
	SetDword((0x009448A8+2), (0xA2+FrameWinExt));						//-- Buttons(BUY)InGameShop
	SetDword((0x004D7D99+1), (0x14F+FrameWinExt));						//-- Texto Copy
	SetDword((0x004D7E1D+1), (0x14F+FrameWinExt));						//-- Texto Copy
	SetDword((0x008192C1+6), (0x0B+FrameWinExt));						//MasterSkill Tree1
	SetDword((0x008192DB+6), (0xDD+FrameWinExt));						//MasterSkill Tree2
	SetDword((0x008192F5+6), (0x1AF+FrameWinExt));						//MasterSkill Tree3
	SetDword((0x00819440+1), (0x263+FrameWinExt));						//Button Closed MasterSkill
	//-- Add resto
	
	//-----------------------TEST ILUS plate
	//SetDword((0x0037298), (0xBA+FrameWinCDepthBox));				//ISSLUS 0x00379284
	//0x0085B446

	//SetDword(0x0086E955+3, (0x3C+FrameWinCDepthBox));  //-- TEST
	//SetDword((0x0086CC72+1),(0x199+FrameWinCDepthBox) );  //-- TEST ITME
	//SetDword(0x0086EA00+3,(0x186+FrameWinCDepthBox));  //-- TEST

	//SetDword(0x00865398+3,(0xCA +FrameWinCDepthBox));

	//SetDword((0x00865398), (0xCA+WinC));
	//------------------------------------------------------

	SetDword((0x0085B445+1), (0x199+FrameWinCDepthBox));				//WarScore
	SetDword((0x0085B9EF+1), (0x1FD+FrameWinCDepthBox));				//DuelScore
	SetDword((0x0082AAAD+1), (0x265+FrameWinCDepthBox));				//-- Button Close Map
	//
	SetDword((0x0085C55E+1), (0x19D+FrameWinCDepthBox));				//BloodCastleTimer
	//
	//SetDword((0x0085B3B1+1), (0x201+FrameWinCDepthBox));				//-- ChaosCastle
	SetDword((0x0085B3B1 + 1), (320 + QTFrame.DisplayWinExt / 2 + 150)); //-- ChaosCastleTimer
	SetDword((0x0085BB11+1), (0x1E6+FrameWinCDepthBox));				//-- CastleSiege
	//-- General 0x280
	SetDword((0x004D7D6F+2), (QTFrame.DisplayWin));				//-- Texto Server copy
	SetDword((0x004D7D8B+2), (QTFrame.DisplayWin));				//-- Texto copy
	SetDword((0x004D7E04+2), (QTFrame.DisplayWin));				//-- Texto copy
	SetDword((0x004D7E8A+2), (QTFrame.DisplayWin));				//-- Texto copy
	SetDword((0x004D06F4+4), (QTFrame.DisplayWin));				//-- Cursor Limite
	SetDword((0x004D0700+4), (QTFrame.DisplayWin));				//-- Cursor Limite
	//==
	SetDword((0x004D071D+4), ((0x1E0+ QTFrame.DisplayHeightExt) - 50));				//-- Cursor Limite Y
	SetDword((0x004D0729+4), ((0x1E0 + QTFrame.DisplayHeightExt) - 50));				//-- Cursor Limite Y
	SetDword((0x00779CCD+3), (QTFrame.DisplayWin));				//-- Tooltip Limite
	SetDword((0x00635B5A+2), (QTFrame.DisplayWin));				//-- PlayerDialog
	SetDword((0x006359C2+1), (QTFrame.DisplayWin));				//-- ItemModel
	SetDword((0x0040F7B7+1), (QTFrame.DisplayWin));				//-- Store Dialog X
	SetDword((0x0040F7DC+1), (QTFrame.DisplayHeight));			//-- Store Dialog Y
	//==
	SetDword((0x0085ECA6 + 1), (0x186 + FrameWinExt));							//-- WindowsFriends X Open
	SetDword((0x0085ECA1 + 1), (0x103 + QTFrame.DisplayHeightExt));				//-- WindowsFriends Y Open
	SetDword((0x007C3210 + 1), (0x103 + QTFrame.DisplayHeightExt));				//-- WindowsFriends Y Open
	SetDword((0x007C3217 + 1), (0x103 + QTFrame.DisplayHeightExt));				//-- WindowsFriends Y Open
	SetDword((0x0048832F + 3), (FrameWinExt));									//-- AddFriend X Open
	SetDword((0x0048833C + 3), (0x14C + QTFrame.DisplayHeightExt));				//-- AddFriend Y Open

	
	//
	SetDword((0x0048BC81+2), (0x280+FrameWinCDepthBox));				//-- friend list X
	SetDword((0x0048BC8C+1), (0x280+FrameWinCDepthBox));				//-- friend list X

	SetDword((0x0048BCEC + 2), (0x1E0 + QTFrame.DisplayHeightExt) - 50);				//-- friend listY
	SetDword((0x0048BCF7 + 1), (0x1E0 + QTFrame.DisplayHeightExt) - 50);				//-- friend listY
	//
	//SetDword((0x0048BE6D + 2), (0x1E0 + Fix_DisplayHeightExt) - 50);				//-- friend listY
	//SetDword((0x0048BE77 + 1), (0x1E0 + Fix_DisplayHeightExt) - 50);				//-- friend listY

	//==
	SetDword(0x004D7D7D + 1, (QTFrame.DisplayHeight)); //Fix Y Text CoppytRi
	SetDword(0x004D7E12 + 1, (QTFrame.DisplayHeight)); //Fix Y Text CoppytRi
	SetDword(0x004D7E98 + 1, (QTFrame.DisplayHeight)); //Fix Y Text CoppytRi

	SetDword((DWORD)(0x0085A426), QTFrame.DisplayHeightExt + 382); // Y ChatInput
	//SetByte((DWORD)(0x0085A42B), 0);	 // X 
	//SetByte((DWORD)(0x00785965), 72);	 // Text
	//Fix Camera
	SetFloat(0x00D27BFC, 40);
	SetFloat(0x087933D8, -45);
	SetFloat(0x00D27B88, -48.5);
	SetDouble(0x00D255A0, 150);

	//for what?
	SetDouble(oCam_ClipX, 5500.0f);
	SetDouble(oCam_ClipXCS, 1800.0f);
	SetFloat(0x00D2C894, 4100.0f);
	SetFloat(0x00D2C8A8, 4300);
	SetFloat(0x00D2570C, 3100);

	SetCompleteHook(0xE8, 0x0040464E, &CBRenderCreateCharacter);
	SetCompleteHook(0xE9, 0x00868590, &QTFrame.CNewUIWindowMenuPos); //Fix CNewUIWindowMenu
	SetCompleteHook(0xE8, 0x00868B2D, &FCNewUIWindowMenuPos); //Button Info


	SetCompleteHook(0xE8, 0x00875366, &QTFrame.FixEventTime); //CNewUIBloodCastle
	SetCompleteHook(0xE8, 0x00872F76, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x00776EA6, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x00894596, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x0088F0D6, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x0086CAC6, &QTFrame.FixEventTime); //BLD
	SetCompleteHook(0xE8, 0x0088C4F6, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x00877506, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x00875AD6, &QTFrame.FixEventTime);
	SetCompleteHook(0xE8, 0x007C0816, &QTFrame.FixEventTime);
	//Bach Long Dien
	//SetCompleteHook(0xE8, 0x008690C6, &QTFrame.BFixPosX);//CNewUICursedTempleEnter
	//SetCompleteHook(0xE8, 0x00869ED6, &QTFrame.BFixPosX);//CNewUICursedTempleResult

	SetDword((0x0085BCC4 + 1), (205  +QTFrame.DisplayWinExt)); //CNewUICursedTempleEnter
	SetDword((0x0085BDE9 + 1), (205 + QTFrame.DisplayWinExt)); //CNewUICursedTempleResult

	//== Fix Text Time Event &Nhan Thuong Blood
	SetCompleteHook(0xE8, 0x004E7A58, &QTFrame.FixTextXY); //Button Info
	//RenderMatch
	SetDword(0x008737DF + 3, (320+QTFrame.DisplayWinExt)); //Text Blood
	SetDword(0x0087262F + 3, (320+QTFrame.DisplayWinExt)); //Text CC

	SetCompleteHook(0xE8, 0x0048E23C, (int)FixSizeItem); //
	SetCompleteHook(0xE8, 0x004D5D57, (int)FixSizeItem); //
	SetCompleteHook(0xE8, 0x007729B3, (int)FixSizeItem); //
	SetCompleteHook(0xE8, 0x007C70E8, (int)FixSizeItem); //
	SetCompleteHook(0xE8, 0x008545D8, (int)FixSizeItem); //
	SetCompleteHook(0xE8, 0x00943CB8, (int)FixSizeItem); //
	////===Fix Size Button Text //Crash
	//SetDword(0x0077A646 + 1, (Fix_DisplayWin)); //
	//SetDword(0x00779C57 + 1, (Fix_DisplayWin)); //
	//SetDword(0x00779A7A + 1, (Fix_DisplayWin)); //
	//SetDword(0x00779C7D + 1, (Fix_DisplayHeight)); //
	//SetDword(0x00779AA0 + 1, (Fix_DisplayHeight)); //
	//SetDword(0x0077A66C + 1, (Fix_DisplayHeight)); //

	//==Fix Wide 2

	int JCWinWidth = pWinWidth / pWinHeightReal;

	SetDword(0x004283CA + 1, JCWinWidth - (640 - 465)); // fix CastleGuard GuildList position

	SetCompleteHook(0xE8, 0x008240A9, &sub_10010FF0); //Fix DrawBarForm
	SetDword(0x004D931E + 6, QTFrame.DisplayHeight); //Size Y Click
	SetDword(0x00635B71 + 2, QTFrame.DisplayHeight); //Size Y Click

	SetCompleteHook(0xE8, 0x005B834E, &SelectObjects); //-- Fix Chon Nhan Vat
	SetCompleteHook(0xE8, 0x00834700, &DropItem); //-- Fix Drop item
	SetCompleteHook(0xE8, 0x00480020, &PictureMapName);					//-- Tga Map
	SetCompleteHook(0xE8, 0x004800A8, &PictureMapName);					//-- Tga Map
}
//////////////////////////////////////////////////////////////////////////////////////////////
//-- WideScreen Principal
//////////////////////////////////////////////////////////////////////////////////////////////
double CNewDisplaYOpenGLW(float a1)
{
	return (float)((double) a1 * pWinWidthReal);
}
double CNewDisplaYOpenGLH(float a1)
{
	return (float)((double)a1 * pWinHeightReal);
}

double CNewDisplaYOpenGL2W(float a1)
{
	return (float)((double) a1 * 1.25);
}

signed int FrameOpenGLWidth( )
{
	return 640;
}

signed int FrameOpenGLWidthView( )
{
	if((gInterface.CheckWindow(Inventory) || gInterface.CheckWindow(ExpandInventory) || gInterface.CheckWindow(Character)))
	{
		glColor4f(0.0, 0.0, 0.0, 0.0); 
		return 860;
	}
	else
	{
			glColor4f(0.0, 0.0, 0.0, 0.0); 
			return 1000;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
int FrameMasterSkill(int thisa)
{
	int result; // eax@1

	*(DWORD *)(thisa + 20) = QTFrame.DisplayWinExt;
	*(DWORD *)(thisa + 24) = 0;
	*(DWORD *)(thisa + 28) = 640;
	result = thisa;
	*(DWORD *)(thisa + 32) = 428;
	return result;
}

void FrameMasterDisplay(DWORD id, float x, float y, float w, float h)
{
	pDrawGUI(id, x, y, w, 428);
}

int PaintMatrixModel(float PosX, float PosY, float Width, float Height, int ItemID, int a6, int a7, int a8, char a9)
{
	int v4; // ST10_4@1

	v4 = *(DWORD *)(GetInstance( ) + 252);

	return pDrawItemModel(PosX + *(DWORD *)(v4 + 36), PosY, Width, Height, ItemID, a6, a7, a8, a9);
}

void FrameShopDisplayBuy(float x, float y, float w, float h, float arg5, int arg6 )
{
	pDrawBarForm(x, y, (double)QTFrame.DisplayWin, h, arg5, arg6);
}

BYTE __thiscall CNewFrame::FrameHelperDisplay(int thisa, int a2, int x, int y)
{
	int DisplayFrameX;

	DisplayFrameX = QTFrame.DisplayWin - 190;

	return CNewUIMainFrameHelper(thisa, a2, DisplayFrameX, y);
}

BYTE __thiscall CNewFrame::FrameShopDisplay(int thisa, int a2, int x, int y)
{
	int DisplayFrameX;

	DisplayFrameX = x + QTFrame.DisplayWinExt;

	return InitCashShop(thisa, a2, DisplayFrameX, y);
}

int __thiscall CNewFrame::GetDisplayPosX(BYTE * thisa)
{
	*(signed int *)((int)(thisa + 4) + 0) = QTFrame.DisplayWinMid - 105;

	return (int)(thisa + 4);
}

bool CheckBannerShop(int x, int y, int w, int h)
{
	int v4; // eax@1

	v4 = *(DWORD *)(GetInstance( ) + 252);

	return pCheckMouseOver(*(DWORD *)(v4 + 36) + x, y, w, h);
}

void PaintBannerShop(int ImageID, float PosX, float PosY, float Width, float Height)
{
	int v4; // ST10_4@1

	v4 = *(DWORD *)(GetInstance( ) + 252);

	pDrawGUI(ImageID, *(DWORD *)(v4 + 36) + PosX, PosY, Width,  Height);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenStore(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameStoreMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenChaos(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameChaosMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

BYTE * __thiscall CNewFrame::CNewUIMainFrameOpenShop(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameShopMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY , Ext);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenOtherStore(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameOtherStoreMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenLucky(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameLuckyMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenExt(int thisa, int PosX, int PosY)
{
	return CNewUIMainFrameInvExtMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenBault(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameBaulMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

int __thiscall CNewFrame::CNewUIMainFrameOpenTrade(int thisa, int PosX, int PosY, int Ext)
{
	return CNewUIMainFrameTradeMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY, Ext);
}

BYTE * __thiscall CNewFrame::CNewUIMainFrameOpenBaultExt(int thisa, int PosX, int PosY)
{
	return CNewUIMainFrameBaulExtMove(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY);
}

int __thiscall CNewFrame::CNewUIMainFrameView(int thisa, int PosX, int PosY)
{
	return CNewUIMainFrameControl(thisa, PosX + QTFrame.DisplayWinCDepthBox, PosY);
}

int __thiscall CNewFrame::CNewUIMainInfoButtonGens(char *thisa, int X, int Y, int Width, int Height)
{
	return ChangeButtonInfo2(thisa, X + QTFrame.DisplayWinCDepthBox, Y, Width, Height);
}

int __thiscall CNewFrame::CNewUIMainPaintFont(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin)
{
	return CNewPictureFont(thisa, PosX + QTFrame.DisplayWinExt, PosY, Text, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}
//////////////////////////////////////////////////////////////////////////////////////////////
void CNewRenderSands(int Picture, float PictureX, float PictureY, float Widht, float a5, float a6, float a7, float a8, float a9)
{
	RenderBitmapUV(Picture, PictureX, PictureY, Widht + QTFrame.DisplayWinCDepthBox, QTFrame.DisplayHeight, a6, a7, a8, a9);
}

void PictureMuLogo(int ImageID, float PosX, float PosY, float Width, float Height, float Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, float ScaleAlpha)
{
	RenderBitmap(ImageID,  PosX + QTFrame.DisplayWinExt, PosY, Width,  Height,  Arg6,  Arg7,  ScaleX,  ScaleY,  ScaleSize,  ScalePosition, ScaleAlpha);
}

int __thiscall CNewFrame::FixTextXY(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin)
{
	return CNewPictureFont(thisa, PosX + QTFrame.DisplayWinExt, PosY+ QTFrame.DisplayHeightExt, Text, nCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

//----- (00636480) --------------------------------------------------------
void CNewLogoPaint(GLint a1, int a2, GLsizei width, GLsizei height)
{
	float JCWinWidth; // ST04_4@3
	unsigned int x; // [sp+20h] [bp+8h]@1
	
	JCWinWidth = (double)(unsigned int)pWinWidth / 640.0;
	
	x = ( a1 * pWinWidthReal ) / JCWinWidth;
	width =  ( a1 * pWinWidthReal ) / JCWinWidth;

	JCBeginOpengl(x, a2, width, height);
}

void SeedEmpy(int ImageID, float PosX, float PosY, float Width, float Height)
{
	pDrawGUI(ImageID,  PosX + QTFrame.DisplayWinExt + 50, PosY, Width,  Height);
	glColor4f(0.0, 0.0, 0.0, 1.0); //--
}
//-------
DWORD Bdword_ConvertX(float a1)
{
	//return a1 * 1.25;
	return (DWORD)(pWinWidthReal * a1);
}
DWORD dword_ConvertY(float a1)
{
	//return a1 * 1.25;
	return (DWORD)(pWinHeightReal * a1);
}

__declspec (naked) void BObjDialogBox()
{
	static DWORD main_addr = 0x00635B6C;
	static int renderWin = 0x280u;
	static int a2;

	_asm
	{
		MOV EDX,DWORD PTR SS:[EBP+0XC]
		MOV EAX,DWORD PTR DS:[EDX]
		MOV a2, EAX
	}

		renderWin = pWinWidth / pWinHeightReal;
		a2 = renderWin * a2 / pWinWidth;

	_asm
	{
		MOV EAX, a2
		MOV ECX,DWORD PTR SS:[EBP+0xC]
		MOV DWORD PTR DS:[ECX],EAX
		JMP[main_addr]
	}
}

__declspec (naked) void BConverCursor()
{
	static DWORD main_addr = 0x004D06B7;
	static DWORD main_call = 0x009CEBF0;

	_asm
	{
		FILD DWORD PTR SS:[EBP-0x10C4]
		FDIV DWORD PTR DS:[0xE7C3D8]
		CALL main_call
		MOV DWORD PTR DS:[0x879340C],EAX
		JMP[main_addr]
	}
}
__declspec (naked) void BConvertModelX()
{
	static DWORD main_addr = 0x006359E2;
	static DWORD ModelX;
	static DWORD ModelY;

	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP + 0x8]
		MOV ModelX, EAX
	}

	ModelX = Bdword_ConvertX(ModelX);

	_asm
	{
		MOV EAX, ModelX
		MOV DWORD PTR SS : [EBP + 0x8] , EAX
		MOV EAX, DWORD PTR SS : [EBP + 0xC]
		MOV ModelY, EAX
	}

	ModelY = dword_ConvertY(ModelY);

	_asm
	{
		MOV EAX, ModelY
		MOV DWORD PTR SS : [EBP + 0xC] , EAX
		JMP[main_addr]
	}
}

void __cdecl BBeginOpengl(GLint a1, int a2, GLsizei width, GLsizei height)
{

	//g_Console.AddMessage(3, "BeginOpengl %d %d %d %d",a1,a2, width, height);
	//if (height == 430)
	//{
	//	height = 480;
	//}
	GLfloat x; // [esp+4h] [ebp-14h]
	GLfloat y; // [esp+8h] [ebp-10h]
	GLfloat z; // [esp+Ch] [ebp-Ch]
	float v7; // [esp+10h] [ebp-8h]
	float v8; // [esp+14h] [ebp-4h]
	unsigned int v9; // [esp+20h] [ebp+8h]
	unsigned int v10; // [esp+24h] [ebp+Ch]
	signed int widtha; // [esp+28h] [ebp+10h]
	signed int heighta; // [esp+2Ch] [ebp+14h]
	GLfloat FogColor = 0.1171875;
	v9 = pWinWidth * a1 / (pWinWidth / 1.25);
	v10 = pWinHeight * a2 / (pWinHeight / 1.25);
	widtha = pWinWidth * width / 640;
	heighta = pWinHeight * height / 480;
	glMatrixMode(0x1701u);
	glPushMatrix();
	glLoadIdentity();
	glViewport2(v9, v10, widtha, heighta);
	v8 = *(float*)0xE61E3C * 1.399999976158142;
	v7 = (double)widtha / (double)heighta;
	gluPerspective2(*(float*)0xE61E40, v7, *(float*)0xE61E38, v8);
	glMatrixMode(0x1700u);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(*(float*)0x87933D4, 0.0, 1.0, 0.0);
	if (!*(BYTE*)0x87933F8)
		glRotatef(*(float*)0x87933D0, 1.0, 0.0, 0.0);
	glRotatef(*(float*)0x87933D8, 0.0, 0.0, 1.0);
	z = -*(float*)0x87933E4;
	y = -*(float*)0x87933E0;
	x = -*(float*)0x87933DC;
	glTranslatef(x, y, z);
	glDisable(0xBC0u);
	glEnable(0xDE1u);
	glEnable(0xB71u);
	glEnable(0xB44u);
	glDepthMask(1u);
	*(BYTE*)0x879325C = 0;
	*(BYTE*)0x8793260 = 1;
	*(BYTE*)0x879325F = 1;
	*(BYTE*)0x879325E = 1;
	*(BYTE*)0x879325D = 1;
	glDepthFunc(0x203u);
	glAlphaFunc(0x204u, 0.25);
	if (*(BYTE*)0x87933F9)
	{
		glEnable(0xB60u);
		glFogi(0xB65u, 9729);
		glFogf(0xB62u, *(float*)0xE61E44);
		glFogfv(0xB66u, &FogColor);
	}
	else
	{
		glDisable(0xB60u);
	}
	// sub_635830((int)&unk_87933A0);
	sub_635830_Addr((LPVOID)0x87933A0);
}

void CNewFrame::InitFrameOpenGL( )
{
	//-- Seed
	SetCompleteHook(0xE8, 0x00934286, &SeedEmpy);
	SetCompleteHook(0xE8, 0x00855868, &SeedEmpy);
	SetCompleteHook(0xE8, 0x0085589F, &SeedEmpy);
	SetCompleteHook(0xE8, 0x0088643F, &SeedEmpy);
	SetCompleteHook(0xE8, 0x008863F9, &SeedEmpy);
	//----
	SetCompleteHook(0xE8, 0x0040464E, &CNewLogoPaint);					//-- Print Logo

	SetCompleteHook(0xE8, 0x004D7C0D, &PictureMuLogo);					//-- Logo SelectServer
	SetCompleteHook(0xE8, 0x004D7C98, &PictureMuLogo);					//-- Logo SelectServer
	SetCompleteHook(0xE8, 0x0081AA9C, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081AA42, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081A9E8, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081A977, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081A944, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081A73D, &CNewUIMainPaintFont);			//-- Texto masterskill
	SetCompleteHook(0xE8, 0x0081A6F4, &CNewUIMainPaintFont);			//-- Texto masterskill
	//////////////////////////////////////////////////////////////////////////////////////////////
	//-- Open Windows 3
	//////////////////////////////////////////////////////////////////////////////////////////////
	SetCompleteHook(0xE8, 0x007C57B9, &CNewUIMainInfoButtonGens);		//-- Boton Gens
	SetCompleteHook(0xE8, 0x00856486, &CNewUIMainFrameOpenBaultExt);	//-- BaultExt
	SetCompleteHook(0xE8, 0x0085F1B9, &CNewUIMainFrameOpenBaultExt);	//-- BaultExt
	SetCompleteHook(0xE8, 0x007D61EF, &CNewUIMainFrameView);			//-- Trade
	SetCompleteHook(0xE8, 0x007D619E, &CNewUIMainFrameView);			//-- Trade
	SetCompleteHook(0xE8, 0x007D6150, &CNewUIMainFrameOpenTrade);		//-- Trade
	SetCompleteHook(0xE8, 0x007D6100, &CNewUIMainFrameView);			//-- Baul
	SetCompleteHook(0xE8, 0x007D60B0, &CNewUIMainFrameOpenBault);		//-- Baul
	SetCompleteHook(0xE8, 0x007D6060, &CNewUIMainFrameOpenExt);			//-- Ext
	SetCompleteHook(0xE8, 0x007D601C, &CNewUIMainFrameView);			//-- Lucky
	SetCompleteHook(0xE8, 0x007D5FCE, &CNewUIMainFrameOpenLucky);		//-- Lucky
	SetCompleteHook(0xE8, 0x007D5F7E, &CNewUIMainFrameView);			//-- OtherStore
	SetCompleteHook(0xE8, 0x007D5F30, &CNewUIMainFrameOpenOtherStore);	//-- OtherStore
	SetCompleteHook(0xE8, 0x007D5EE0, &CNewUIMainFrameView);			//-- Shop
	SetCompleteHook(0xE8, 0x007D5E92, &CNewUIMainFrameOpenShop);		//-- Shop
	SetCompleteHook(0xE8, 0x007D5E42, &CNewUIMainFrameView);			//-- Chaos
	SetCompleteHook(0xE8, 0x007D5DF4, &CNewUIMainFrameOpenChaos);		//-- Chaos
	SetCompleteHook(0xE8, 0x007D5DA4, &CNewUIMainFrameView);			//-- Store
	SetCompleteHook(0xE8, 0x007D5D56, &CNewUIMainFrameOpenStore);		//-- Store
	//===Fix Y BB
	//SetCompleteHook(0xE8, 0x008337A0, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x0085EE0A, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x0085EE91, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x0085FA58, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x0085FD38, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x0085FEA0, &CNewUIMyInventory);			//-- Inventory
	//SetCompleteHook(0xE8, 0x007CA270, &CNewUIGuildInfoWindow);			//-- CNewUIGuildInfoWindow
	//SetCompleteHook(0xE8, 0x0077E8F6, &CNewUICharacterInfoWindow);			//-- CNewUICharacterInfoWindow
	//SetCompleteHook(0xE8, 0x0078DC56, &CNewUICommandWindow);			//-- CNewUICommandWindow
	////SetCompleteHook(0xE8, 0x008790A2, &CNewUICastleWindow);			//--
	//SetCompleteHook(0xE8, 0x008836F2, &CNewUIGuardWindow);			//--
	//SetCompleteHook(0xE8, 0x00880B8B, &CNewUIGatemanWindow);			//--
	//SetCompleteHook(0xE8, 0x0088258B, &CNewUIGateSwitchWindow);			//--
	//SetCompleteHook(0xE8, 0x007D06A8, &CNewUIGuildMakeWindow);			//--
	//SetCompleteHook(0xE8, 0x0083E156, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0085ED6C, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x007D06A8, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0085EEBE, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0085FA2D, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0086003E, &CNewUIMyQuestInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0084A076, &CNewUIPartyInfoWindow);			//--
	//SetCompleteHook(0xE8, 0x0084511B, &CNewUINPCQuest);			//--
	//SetCompleteHook(0xE8, 0x0087436B, &CNewUIEnterBloodCastle);			//--
	//SetCompleteHook(0xE8, 0x00877E4B, &CNewUIEnterDevilSquare);			//--

	SetCompleteHook(0xE8, 0x00493127, &CUILetterWriteWindow);				//-- Send Mail
	SetCompleteHook(0xE8, 0x00494DA6, &CUILetterWriteWindow);				//-- Send Mail
	SetCompleteHook(0xE8, 0x00497D0B, &CUILetterWriteWindow);				//-- Send Mail
	SetCompleteHook(0xE8, 0x00497EA4, &CUILetterWriteWindow);				//-- Send Mail

//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
	//-- Init FrameWin General
	SetCompleteHook(0xE8, 0x0081A146, &FrameMasterDisplay);				//-- Letter Print
	SetCompleteHook(0xE8, 0x0081A199, &FrameMasterDisplay);				//-- Letter Print
	SetCompleteHook(0xE8, 0x00819415, &FrameMasterSkill);				//-- Letter Print
	SetCompleteHook(0xE8, 0x0085CC50, &FrameHelperDisplay);				//-- Letter Print
	SetCompleteHook(0xE8, 0x0085C446, &FrameShopDisplay);				//-- Letter Print
	SetCompleteHook(0xE8, 0x00943D7F, &PaintMatrixModel);				//-- ItemModel CashShop
	SetCompleteHook(0xE8, 0x008240A9, &FrameShopDisplayBuy);			//-- Letter Print
	SetCompleteHook(0xE8, 0x00945114, &PaintBannerShop);				//-- Model CashShop
	SetCompleteHook(0xE8, 0x00945180, &CheckBannerShop);				//-- Model CashShop
	//--
	SetCompleteHook(0xE9, 0x005C6E80, &FrameScreenWidth); //fix repair slot items
	//--
	SetCompleteHook(0xE8, 0x004D2180, &GLCreateWindowEx);				//-- Letter Print
	//--
	//////////////////////////////////////////////////////////////////////////////////////////////
	//-- Auto Scale Screen principal
	//////////////////////////////////////////////////////////////////////////////////////////////
	SetCompleteHook(0xE9, 0x00636420, &CNewDisplaYOpenGLW);
	SetCompleteHook(0xE9, 0x00636450, &CNewDisplaYOpenGLH);
	//////////////////////////////////////////////////////////////////////////////////////////////
	//-- Paint FrameOpenGl
	//////////////////////////////////////////////////////////////////////////////////////////////
	//--
	

	SetDword(0x004D9746 + 3, 480); //Size Background

	SetCompleteHook(0xE8, 0x0040F2E9, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x004D714E, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x004D79E7, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x004D9756, &FrameOpenGLWidth); //-- Camara General Renderizado Live View  // FrameOpenGLWidthView
	//--
	SetCompleteHook(0xE8, 0x005DB4D5, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB1AA, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB22F, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB322, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB3A7, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB46D, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB4AD, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB534, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB5C4, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB628, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB68C, &FrameOpenGLWidth); //-- Camara General Renderizado
	SetCompleteHook(0xE8, 0x005DB6ED, &FrameOpenGLWidth); //-- Camara General Renderizado
//////////////////////////////////////////////////////////////////////////////////////////////
// Cursor Wide
//////////////////////////////////////////////////////////////////////////////////////////////
	SetCompleteHook(0xE8, 0x005B97DC,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x005B984C,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x005B9904,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008C2E0F,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008C2E7F,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008CC713,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008CC788,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008D99B8,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008D9A2D,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008EF47B,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008EF4ED,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008EF5C5,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x008EF65A,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x00914FC9,&CNewRenderSands);
	SetCompleteHook(0xE8, 0x0091503E,&CNewRenderSands);

	//----

	SetCompleteHook(0xE9, 0x00635B55, &BObjDialogBox);   // 
	SetCompleteHook(0xE9, 0x004D06A1, &BConverCursor);   //
	//--
	SetCompleteHook(0xE9, 0x006359B6, &BConvertModelX);		//-- Model Print //

	gInterfaceBar.Load();
}

#endif