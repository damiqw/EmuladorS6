#include "stdafx.h"
#include "GCCharacterS13.h"
#include "PrintPlayer.h"
#include "Defines.h"
#include "TMemory.h"
#include "Util.h"
#include "Interface.h"
#include "zzzMathLib.h"
#include "Offset.h"
#include "User.h"
#include "CustomRankUser.h"
#include "Protect.h"
#include "MiniMap.h"

CSCharacterS13 gCSCharacterS13;

void CSCharacterS13::Load()
{
	gInterface.BindObject(CharacterSelect, 51522, 85, 150, 219, 178);
	gInterface.BindObject(CharacterSelect_Button1, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button2, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button3, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button4, 51519, 150, 35, -1, -1);
	gInterface.BindObject(CharacterSelect_Button5, 51519, 150, 35, -1, -1);
	//gInterface.BindObject(CharacterSelect_Button6, 51519, 150, 35, -1, -1);

	SetCompleteHook(0xE8, 0x004D5EE6, this->SelectChar);

	SetDword((PVOID)(0x004D752F + 1), 51522);
	SetDword((PVOID)(0x004D7563 + 1), 51522);

	SetDword((PVOID)(0x004053A2 + 1), 51522); //remove deco.tga
	SetDword((PVOID)(0x00401D2F + 1), 51522);	//remove characterex

	SetByte((PVOID)(0x004053D3 + 1), 0); //REMOVE BARRA CINZA
	SetCompleteHook(0xE8, 0x004D6C3E, this->OpenCharacterSceneData);

	SetDword((PVOID)(0x004D6C73), 0);
	SetByte((PVOID)(0x00402106), 0);
}

void CSCharacterS13::OpenCharacterSceneData()
{
	if (gProtect.m_MainInfo.SelectCharacterType == 3)
	{
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\CharacterSelect_Button.tga", 51519, 0x2601, 0x2901, 1, 0);
	}

	pLoadImage("Custom\\Interface\\none.tga", 51522, 0x2601, 0x2901, 1, 0);
	pLoadImage("Effect\\magic_ground1_3.jpg", 32779, GL_LINEAR, GL_REPEAT, 1, 0);
	//
	((void(__cdecl*)())0x006312E0)();
}

void CharacterSelect360()
{
	for (int i = 0; i < 5; i++)
	{
		int v5 = pGetPreviewStruct(pPreviewThis(), i);
		int v8 = v5 + 776;
		if (gInterface.IsWorkZone(CharacterSelect))
		{
			*(float*)(v8 + 272) = *(float*)(v8 + 272) + 5.0;  //AQUI É A VELOCIDADE DO GIRO DA 360
		}
		else
		{
			*(float*)(v8 + 272) = 70;
		}
	}
}

inline int GetPosSelectChar()
{
	int Ret = 0;
	switch (pGameResolutionMode)
	{
	case 0: Ret = 05.f; break;	//640x480
	case 1: Ret = 05.f; break;	//800x600
	case 2: Ret = 85.f; break;	//1024x768
	case 3: Ret = 185.f; break;	//1280x1024 Actual
	case 4: Ret = 210.f; break;	//1366x768
	case 5: Ret = 250.f; break;	//1440x900
	case 6: Ret = 285.f; break;	//1600x900
	case 7: Ret = 200.f; break;	//1680x1050
	case 8: Ret = 270.f; break;	//1920x1080
	}
	return Ret;
}

void CharacterCharacteristics(int a1, float a2)
{
	char* Name;
	char* Status;
	int Class;
	char Reset[256];
	char Level[256];
	float X = 471 + Fix_DisplayWinExt;
	float Y = 51;
	int This = (int)sub_482B70() + 36744;
	int Hero00 = This;
	Hero00 = *(DWORD*)(This + 4) + 368 * a1;
	//
	Name = strcpy((char*)Hero00 + 176, (const char*)(*((DWORD*)Hero00 + 42) + 56));
	Status = (char*)Hero00 + 240;
	Class = sub_587620(*(BYTE*)(*(DWORD*)(Hero00 + 168) + 19));
	gInterface.DrawFormat(eGold, X + 35 + GetPosSelectChar(), Y + 20 + a2, 190, 2, (const char*)Name);
	gInterface.DrawFormat(eWhite180, X + 11 + GetPosSelectChar(), Y + 7 + a2, 190, 0, (const char*)Class);
	gInterface.DrawFormat(eWhite180, X - 50 + GetPosSelectChar(), Y + 7 + a2, 190, 4, (const char*)Status);
	wsprintf(Level, "Level: %d", *(WORD*)(*(DWORD*)(Hero00 + 168) + 130));
	pSetTextColor(pTextThis(), 255, 189, 25, 0xFF);
	pDrawText(pTextThis(), X - 50 + GetPosSelectChar(), Y + 20 + a2, Level, 190, 0, (LPINT)4, 0);
}

void CharacterTeleport(int a1, float a2, float a3, float a4)
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::SwitchCharacter)
	{
		int v5 = pGetPreviewStruct(pPreviewThis(), a1);
		int v8 = v5 + 776;
		if (v5)
		{
			*(float*)(v8 + 156) = 0.30000001;
			*(float*)(v8 + 160) = 0.30000001;
			*(float*)(v8 + 164) = 0.30000001;
			*(float*)(v8 + 252) = a2;
			*(float*)(v8 + 256) = a3;
			*(float*)(v8 + 272) = a4;
		}
	}
}

void CSCharacterS13::SelectChar()
{
	gObjUser.Refresh();
	if (*(DWORD*)(MAIN_SCREEN_STATE) == ObjState::SwitchCharacter)
	{
		float X = 471 + Fix_DisplayWinExt;
		float Y = 51;

		//
		if (!*(BYTE*)((int)sub_482B70() + 33948))
		{
			//Create Select
			//0
			if (!*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 0) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button1))
				{
					if (gInterface.Data[CharacterSelect_Button1].OnClick)
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 51, 0, 70);
						sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 51, 0, 35);
					}
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 51, 0, 0);
				}
				gInterface.DrawFormat(eWhite180, X - 29 + GetPosSelectChar(), Y + 13, 210, 3, "Empty Character Slot");
			}
			//1
			if (!*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 1) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button2))
				{
					if (gInterface.Data[CharacterSelect_Button2].OnClick)
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 88, 0, 70);
						sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 88, 0, 35);
					}
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 88, 0, 0);
				}
				gInterface.DrawFormat(eWhite180, X - 29 + GetPosSelectChar(), 88 + 13, 210, 3, "Empty Character Slot");
			}
			//2
			if (!*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 2) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button3))
				{
					if (gInterface.Data[CharacterSelect_Button3].OnClick)
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 125, 0, 70);
						sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 125, 0, 35);
					}
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 125, 0, 0);
				}
				gInterface.DrawFormat(eWhite180, X - 29 + GetPosSelectChar(), 125 + 13, 210, 3, "Empty Character Slot");
			}

			//3
			if (!*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 3) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button4))
				{
					if (gInterface.Data[CharacterSelect_Button4].OnClick)
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 162, 0, 70);
						sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 162, 0, 35);
					}
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 162, 0, 0);
				}
				gInterface.DrawFormat(eWhite180, X - 29 + GetPosSelectChar(), 162 + 13, 210, 3, "Empty Character Slot");
			}
			//4
			if (!*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 4) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button5))
				{
					if (gInterface.Data[CharacterSelect_Button5].OnClick)
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 199, 0, 70);
						sub_483B20((int)sub_482B70(), (int)sub_482B70() + 33936);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 199, 0, 35);
					}
				}
				else
				{
					gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), 199, 0, 0);
				}
				gInterface.DrawFormat(eWhite180, X - 29 + GetPosSelectChar(), 199 + 13, 210, 3, "Empty Character Slot");
			}

			//Character Select
			CharacterSelect360();

			if (*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 0) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button1))
				{

					if (gInterface.Data[CharacterSelect_Button1].OnClick)
					{
						PlayBuffer(25, 0, 0);
						SelectedHero = 0;
						if (gProtect.m_MainInfo.SelectCharacterType == 3)
						{
							CharacterTeleport(0, 13629.0, 12339.0, 90.0);
							CharacterTeleport(1, 0.0, 13539.0, 90.0);
							CharacterTeleport(2, 0.0, 13539.0, 90.0);
							CharacterTeleport(3, 0.0, 13539.0, 90.0);
							CharacterTeleport(4, 0.0, 13539.0, 90.0);

						}
						else
						{
							CharacterTeleport(0, 8172.84083, 19265.57287, 90.0);
							CharacterTeleport(1, 0.0, 8171.84083, 90.0);
							CharacterTeleport(2, 0.0, 8171.84083, 90.0);
							CharacterTeleport(3, 0.0, 8171.84083, 90.0);
							CharacterTeleport(4, 0.0, 8171.84083, 90.0);
						}
						gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y, 0, 70);
					}
					else
					{
						if (SelectedHero == 0)
						{
							gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y, 0, 70);
						}
						else
						{
							gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y, 0, 35);
						}
					}

					if (SelectedHero == 0)
					{
						SelectedCharacter = 0;
					}
				}
				else
				{
					if (SelectedHero == 0)
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button1, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y, 0, 0);
					}
				}
				CharacterCharacteristics(0, 0);
			}
			//1
			if (*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 1) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button2))
				{

					if (gInterface.Data[CharacterSelect_Button2].OnClick)
					{
						PlayBuffer(25, 0, 0);
						SelectedHero = 1;
						if (gProtect.m_MainInfo.SelectCharacterType == 3)
						{
							CharacterTeleport(1, 13629.0, 12339.0, 90.0);
							CharacterTeleport(0, 0.0, 13539.0, 90.0);
							CharacterTeleport(2, 0.0, 13539.0, 90.0);
							CharacterTeleport(3, 0.0, 13539.0, 90.0);
							CharacterTeleport(4, 0.0, 13539.0, 90.0);
						}
						else
						{
							CharacterTeleport(1, 8172.84083, 19265.57287, 90.0);
							CharacterTeleport(0, 0.0, 8171.94083, 90.0);
							CharacterTeleport(2, 0.0, 8171.94083, 90.0);
							CharacterTeleport(3, 0.0, 8171.94083, 90.0);
							CharacterTeleport(4, 0.0, 8171.94083, 90.0);
						}
						gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 37, 0, 70);
					}
					else
					{
						if (SelectedHero == 1)
						{
							gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 37, 0, 70);
						}
						else
						{
							gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 37, 0, 35);
						}
					}
					SelectedCharacter = SelectedHero;
				}
				else
				{
					if (SelectedHero == 1)
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 37, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button2, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 37, 0, 0);
					}
				}
				CharacterCharacteristics(1, 37);
			}
			//2
			if (*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 2) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button3))
				{

					if (gInterface.Data[CharacterSelect_Button3].OnClick)
					{
						PlayBuffer(25, 0, 0);
						SelectedHero = 2;
						if (gProtect.m_MainInfo.SelectCharacterType == 3)
						{
							CharacterTeleport(2, 13629.0, 12339.0, 90.0);
							CharacterTeleport(0, 0.0, 13539.0, 90.0);
							CharacterTeleport(1, 0.0, 13539.0, 90.0);
							CharacterTeleport(3, 0.0, 13539.0, 90.0);
							CharacterTeleport(4, 0.0, 13539.0, 90.0);
						}
						else
						{
							CharacterTeleport(2, 8172.84083, 19265.57287, 90.0);
							CharacterTeleport(0, 0.0, 8171.94083, 90.0);
							CharacterTeleport(1, 0.0, 8171.94083, 90.0);
							CharacterTeleport(3, 0.0, 8171.94083, 90.0);
							CharacterTeleport(4, 0.0, 8171.94083, 90.0);
						}
						gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 74, 0, 70);
					}
					else
					{
						if (SelectedHero == 2)
						{
							gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 74, 0, 70);
						}
						else
						{
							gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 74, 0, 35);
						}
					}

					SelectedCharacter = SelectedHero;
				}
				else
				{
					if (SelectedHero == 2)
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 74, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button3, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 74, 0, 0);
					}
				}
				CharacterCharacteristics(2, 74);
			}
			//3
			if (*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 3) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button4))
				{

					if (gInterface.Data[CharacterSelect_Button4].OnClick)
					{
						PlayBuffer(25, 0, 0);
						SelectedHero = 3;
						if (gProtect.m_MainInfo.SelectCharacterType == 3)
						{
							CharacterTeleport(3, 13629.0, 12339.0, 90.0);
							CharacterTeleport(0, 0.0, 13539.0, 90.0);
							CharacterTeleport(1, 0.0, 13539.0, 90.0);
							CharacterTeleport(2, 0.0, 13539.0, 90.0);
							CharacterTeleport(4, 0.0, 13539.0, 90.0);
						}
						else
						{
							CharacterTeleport(3, 8172.84083, 19265.57287, 90.0);
							CharacterTeleport(0, 0.0, 8171.94083, 90.0);
							CharacterTeleport(1, 0.0, 8171.94083, 90.0);
							CharacterTeleport(2, 0.0, 8171.94083, 90.0);
							CharacterTeleport(4, 0.0, 8171.94083, 90.0);
						}
						gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 111, 0, 70);
					}
					else
					{
						if (SelectedHero == 3)
						{
							gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 111, 0, 70);
						}
						else
						{
							gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 111, 0, 35);
						}
					}
					SelectedCharacter = SelectedHero;
				}
				else
				{
					if (SelectedHero == 3)
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 111, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button4, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 111, 0, 0);
					}
				}

				CharacterCharacteristics(3, 111);
			}
			//4
			if (*(BYTE*)(pGetPreviewStruct(pPreviewThis(), 4) + 780))
			{
				if (gInterface.IsWorkZone(CharacterSelect_Button5))
				{

					if (gInterface.Data[CharacterSelect_Button5].OnClick)
					{
						PlayBuffer(25, 0, 0);
						SelectedHero = 4;
						if (gProtect.m_MainInfo.SelectCharacterType == 3)
						{
							CharacterTeleport(4, 13629.0, 12339.0, 90.0);
							CharacterTeleport(0, 0.0, 13539.0, 90.0);
							CharacterTeleport(1, 0.0, 13539.0, 90.0);
							CharacterTeleport(2, 0.0, 13539.0, 90.0);
							CharacterTeleport(3, 0.0, 13539.0, 90.0);
						}
						else
						{
							CharacterTeleport(4, 8172.84083, 19265.57287, 90.0);
							CharacterTeleport(0, 0.0, 8171.94083, 90.0);
							CharacterTeleport(1, 0.0, 8171.94083, 90.0);
							CharacterTeleport(2, 0.0, 8171.94083, 90.0);
							CharacterTeleport(3, 0.0, 8171.94083, 90.0);
						}
						gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 148, 0, 70);
					}
					else
					{
						if (SelectedHero == 4)
						{
							gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 148, 0, 70);
						}
						else
						{
							gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 148, 0, 35);
						}
					}

					SelectedCharacter = SelectedHero;
				}
				else
				{
					if (SelectedHero == 4)
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 148, 0, 70);
					}
					else
					{
						gInterface.DrawButton(CharacterSelect_Button5, 471 + Fix_DisplayWinExt + GetPosSelectChar(), Y + 148, 0, 0);
					}
				}
				CharacterCharacteristics(4, 148);
			}
		}
	}
	((void(__cdecl*)())0x005BB0B0)();
}

void CSCharacterS13::SelectCharButton(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	// ----
	if (*(DWORD*)(MAIN_SCREEN_STATE) != ObjState::SwitchCharacter)
	{
		return;
	}
	// ----
	if (gInterface.IsWorkZone(CharacterSelect_Button1))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button1].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button1].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button1].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button1].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button2))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button2].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button2].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button2].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button2].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button3))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button3].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button3].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button3].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button3].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button4))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button4].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button4].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button4].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button4].EventTick = GetTickCount();
		// ----
	}
	else if (gInterface.IsWorkZone(CharacterSelect_Button5))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[CharacterSelect_Button5].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[CharacterSelect_Button5].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button5].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[CharacterSelect_Button5].EventTick = GetTickCount();
		// ----
	}
}