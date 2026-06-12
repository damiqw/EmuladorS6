#include "stdafx.h"
#include "Import.h"
#include "Util.h"
#include "Defines.h"
#include "Interface.h"
#include "Protect.h"
#include "PrintPlayer.h"
#include "Common.h"
#include "Resolution.h"
#include "OptionPanel.h"
#include "ShowInfoItemDrop.h"
#include "Offset.h"
#include "Font.h"
#include "cfreetype.h"
#include "CustomFont.h"
#include "InterfaceElemental.h"
#include "EventInvasion.h"
#include "NewInterface.h"
#include "WingInvisible.h"

int dword_10407904;
int dword_10407908;
int dword_1040790C;
int dword_10407910;
int dword_10407914;
int dwrod_10136618;
int Resolucion;
int TickCountPro;
float flt_1040F5CC;
int dword_1040F5E8;
float flt_1040F5D0;
float flt_1040F5D4;
float flt_1040F5D8;
int dword_1040F5E0;

LONG __cdecl SetResolucion(BYTE Data)
{
	HKEY hKey;
	DWORD dwType, dwSize;
	DWORD buffer;
	LONG result;

	unsigned long type = REG_DWORD, size = 1024;

	RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, KEY_ALL_ACCESS, &hKey);
	DWORD value = Data;

	RegSetValueEx(hKey, TEXT("Resolution"), 0, REG_DWORD, (const BYTE*)&value, sizeof(value));

	RegCloseKey(hKey);

	result = RegOpenKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, KEY_READ, &hKey);
	RegQueryValueEx(hKey, "Resolution", NULL, &type, (LPBYTE)&buffer, &size);
	RegCloseKey(hKey);
	pGameResolutionMode = buffer;
	switch (buffer)
	{
	case 0:
		pWinWidth = 640;
		pWinHeight = 480;
		break;
		// --
	case 1:
		pWinWidth = 800;
		pWinHeight = 600;

		break;
		// --
	case 2:
		pWinWidth = 1024;
		pWinHeight = 768;
		break;
		// --
	case 3:
		pWinWidth = 1280;
		pWinHeight = 1024;
		break;
		// --
	case 4:
		pWinWidth = 1360;
		pWinHeight = 768;
		break;
		// --
	case 5:
		pWinWidth = 1440;
		pWinHeight = 900;
		break;
		// --
	case 6:
		pWinWidth = 1600;
		pWinHeight = 900;
		break;
		// --
	case 7:
		pWinWidth = 1680;
		pWinHeight = 1050;
		break;
		// --
	case 8:
		pWinWidth = 1920;
		pWinHeight = 1080;
		break;
		// --
	default:
		pWinWidth = 1024;
		pWinHeight = 768;
		break;
	}
	return 1;
}


int sub_10012730(int a1)
{
	int v1; // esi@1
	DWORD *v2; // eax@1
	int result; // eax@1

	FontSize = a1;
	pWinFontHeight = a1;
	FontSize = a1;
	v1 = a1;

	pWinFontHeight = a1;
	dword_10407904 = a1;
	dword_10407908 = a1;
	dword_1040790C = a1 + 1;
	dword_10407910 = a1;
	dword_10407914 = a1;

	pFontBold = FontBool(); 
	pFontNormal2 = FontFixed(); 
	pFontBigBold = FontBig(); 
	pFontNormal = FontNormal();
	cfreetype::Instance()->Recreate(); 
	v2 = (DWORD *)pWindowThis();
	sub_830B70(v2[45], *v2, 1, 1);
	//v1 = a1 - 11;
	char szSize[16];
	sprintf_s(szSize, " %d", a1);
	result = WritePrivateProfileStringA("FontInfo", "FontSize", szSize, ".\\Settings.ini");

	return result;

}

void ReloadGame()
{

	double v4; // st7
	int result; // eax
	float v6; // [esp+2Ch] [ebp-10h]
	float v7; // [esp+38h] [ebp-4h]
	float a1;
	float a2;
	a2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
	*(DWORD*)0x879326C = +OpenglWindowWidth / 2;
	*(DWORD*)0x8793268 = OpenglWindowY + OpenglWindowHeight / 2;
	*(DWORD*)0x8793264 = pWinWidth - *(DWORD*)0x8793268;
	v7 = (double)(unsigned int)pWinHeight / (double)OpenglWindowHeight;
	v6 = a1 * 0.5 * 3.141592025756836 / 180.0;
	*(float*)0x8793274 = sub_5DD400(v6) / (double)(OpenglWindowWidth / 2) * a2;
	v4 = sub_5DD400(v6);
	result = OpenglWindowHeight / 2;
	*(float*)0x8793270 = v4 / (double)(OpenglWindowHeight / 2) * v7;
}


void ChangeResolution(int a1, int a2)
{
	int v2;		// esi@1
	DWORD v3;	// edi@1
	int v4;		// eax@2
	int v5;		// eax@2
	DWORD* v6;	// esi@2
	v2 = a2;
	v3 = a1;

	if (pMUIsLoaded)
	{
		pWinWidth = a1;
		pWinHeight = a2;

		

		DWORD window_style;

		if (pIsWindowMode == 1)
		{
			window_style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_CAPTION;
		}
		else
		{
			window_style = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_CLIPCHILDREN | WS_SYSMENU | WS_THICKFRAME | WS_CAPTION;
		}

		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			pWinWidthReal = (double)(unsigned int)a1 / MAX_WIN_WIDTH;
			pWinHeightReal = (double)(unsigned int)a2 / MAX_WIN_HEIGHT;
		}
		else
		{
			pWinWidthReal = (double)(unsigned int)a1 / 640;
			pWinHeightReal = (double)(unsigned int)a2 / 480;
			ReloadGame();
		}
		
		
		tagRECT rect;
		rect.left = 0;
		rect.top = 0;
		rect.right = pWinWidth;
		rect.bottom = pWinHeight;

		AdjustWindowRect(&rect, window_style, 0);

		rect.right -= rect.left;
		rect.bottom -= rect.top;

		int pos_x = (GetSystemMetrics(SM_CXSCREEN) - rect.right) / 2;
		int pos_y = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) / 2;

		SetWindowPos(*(HWND*)(MAIN_WINDOW), HWND_TOP, pos_x, pos_y, rect.right, rect.bottom, /*SWP_NOMOVE | */SWP_SHOWWINDOW | SWP_FRAMECHANGED);

		ReloadFont();
		//pReloadFont();
		sub_596AC0_Addr(1);
		int this1 = (int)sub_482B70_Addr();
		*(DWORD*)(this1 + 40) = (int)pWinWidth;
		*(DWORD*)(this1 + 44) = (int)pWinHeight;
		int this2 = (int)sub_407B20();
		*(DWORD*)(this2 + 40) = (int)pWinWidth;
		*(DWORD*)(this2 + 44) = (int)pWinHeight;
		DWORD* window = (DWORD*)GetInstance();
		sub_785870_Addr(window[3], *window, window[4], 0, 382);
		sub_830B70_Addr(window[45], *window, 1, 1);


		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			ShellExecute(GetDesktopWindow(), "OPEN", gProtect.m_MainInfo.ClientName, nullptr, nullptr, SW_SHOWDEFAULT);
			SendMessage(*(HWND*)MAIN_WINDOW, WM_CLOSE, 0, 0);

			SetDouble(oCam_ClipX, 6500.0f);
			SetDouble(oCam_ClipXCS, 4100.0f);
		}
		else
		{
			SetDouble(oCam_ClipX, 2000.0f);
			SetDouble(oCam_ClipXCS, 2000.0f);
		}
		
		
	}

}

bool __fastcall event_options_window(int this_, LPVOID)
{
	int volume_width = 124;

	int volume_x = nInterface.OPTION_WINDOW->X + 130;
	int volume_y = nInterface.OPTION_WINDOW->Y + 215;

	if (pCheckMouseOver(volume_x, volume_y - 4, volume_width, 10))
	{
		int volume_value = *(DWORD*)(this_ + 200);

		if (pMouseWheelValue <= 0)
		{
			if (pMouseWheelValue < 0)
			{
				pMouseWheelValue = 0;
				if ((int)-- * (DWORD*)(this_ + 200) < 0)
					*(DWORD*)(this_ + 200) = 0;
			}
		}
		else
		{
			pMouseWheelValue = 0;
			if ((int)++ * (DWORD*)(this_ + 200) > 10)
				*(DWORD*)(this_ + 200) = 10;
		}

		if (pKeyIsPressed(1))
		{
			int volume_value_width = pCursorX - volume_x;

			if (volume_value_width >= 0)
			{
				float v5 = (double)volume_value_width * (10.0 / volume_width);
				*(DWORD*)(this_ + 200) = floor(v5) + (volume_value_width >= 95 ? 1 : 0);
			}
			else
			{
				*(DWORD*)(this_ + 200) = 0;
			}
		}

		if (volume_value != *(DWORD*)(this_ + 200))
			sub_4D5B70_Addr(*(DWORD*)(this_ + 200));
	}

	for (int i = 0; i < 5; i++)
	{
		if (gInterface.IsWorkZone7(eGameOptionsEffectsButton1 + i) && pKeyIsPressed(1))
			*(DWORD*)(this_ + 204) = i;
	}

	return true;
}

int game_options_effect_values[5] = { 5, 7, 9, 11, 13 };

void RenderWindowsOption(int a1)
{
	float x; // [sp+2Ch] [bp-8h]@1
	float y; // ST34_4@1
	int This; // [sp+74h] [bp-4h]@1

	This = *(DWORD *)(GetInstance() + 160);

	*(signed int *)(This + 16) = 320 - (140 / 2);
	x = (double)*(signed int *)(This + 16);
	y = (double)*(signed int *)(This + 20);

	//pSetCursorFocus = true;

	sub_779410((char *)(This + 24), x + 55, y + 250, 0, 0);

	
	//===
	Resolucion = pWinWidth;
	int BotonX = 40;
	int BotonY = 50;

	
	x = nInterface.OPTION_WINDOW->X;
	y = nInterface.OPTION_WINDOW->Y;

	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if ((nInterface.OPTION_WINDOW->X == -1) && (nInterface.OPTION_WINDOW->Y == -1))
		{
			x = (MAX_WIN_WIDTH / 2) - (nInterface.OPTION_WINDOW->Width / 2);
			y = (MAX_WIN_HEIGHT / 2) - (nInterface.OPTION_WINDOW->Height / 2);
		}
	}
	else
	{
		if ((nInterface.OPTION_WINDOW->X == -1) && (nInterface.OPTION_WINDOW->Y == -1))
		{
			x = (640 / 2) - (nInterface.OPTION_WINDOW->Width / 2);
			y = (480 / 2) - (nInterface.OPTION_WINDOW->Height / 2);
		}
	}

	x -= 20;

	//glColor4f(1.0, 0.2, 0.2, 0.80000001);
	//pDrawBarForm(x+21.5, y+1.5, 265, 15, 0, 0);
	//gElemental.gInfoBox(x+20, y,260,240,0x00000096,0,0);
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		nInterface.DrawWindowBGEX700(nInterface.OPTION_WINDOW, gCustomMessage.GetMessage(44), 158);
	}
	else
	{
		nInterface.DrawWindowOption(nInterface.OPTION_WINDOW, gCustomMessage.GetMessage(44), 158);
	}

	/*pDrawGUI(0xF2102, x+275, y+2.5, 11.0f, 11.0f);
	
	if(pCheckMouseOver(x+275, y+2.5, 11.0, 11.0))
	{
		pDrawColorButton(0xF2102,x+275, y+2.5, 11, 11, 0, 0, pMakeColor(255, 204, 20, 130));
	}
	if (pCheckInMouse(x+275, y+2.5, 11.0, 11.0) && IsRelease(VK_LBUTTON)) //
	{
		PlayBuffer(25, 0, 0);
		pCloseWindow(pWindowThis(), Options);
	}*/
	

	//gInterface.DrawFormat(eWhite, x+20, y+5, 260, 3, pGetTextLine2(pTextLineThis, 3899));

	gInterface.DrawFormat(eWhite, x + BotonX - 30, y - 10 + BotonY, 135.0, 3, pGetTextLine_(pTextLineThis, 3900));

	if (Resolucion == 640)
	{
	//	glColor3f(1.0f, 0.2f, 0.2f);
	//	RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	//	gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "640x480");
	//	glColor3f(1.0f, 1.0f, 1.0f);
	//}
	//else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	//{
	//	glColor3f(0.0f, 1.0f, 1.0f);
	//	RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	//	gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "640x480");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(640, 480);
				SetResolucion(0);
				Resolucion = 640;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		//glColor3f(1.0f, 1.0f, 1.0f);
		//RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		//gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "640x480");
	}

	BotonY += 16;

	if (Resolucion == 800)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "920x600");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "920x600");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(920, 600);
				SetResolucion(1);
				Resolucion = 800;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "920x600");
	}

	BotonY += 16;

	if (Resolucion == 1024)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1024x768");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1024x768");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1024, 768);
				SetResolucion(2);
				Resolucion = 1024;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1024x768");
	}

	BotonY += 16;

	if (Resolucion == 1280)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1280x1024");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1280x1024");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1280, 1024);
				SetResolucion(3);
				Resolucion = 1280;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1280x1024");
	}

	BotonY += 16;

	if (Resolucion == 1360)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1360x768");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1360x768");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1360, 768);
				SetResolucion(4);
				Resolucion = 1360;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1360x768");
	}

	BotonY += 16;

	if (Resolucion == 1440)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1440x900");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1440x900");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1440, 900);
				SetResolucion(5);
				Resolucion = 1440;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1440x900");
	}

	BotonY += 16;

	if (Resolucion == 1600)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1600x900");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1600x900");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1600, 900);
				SetResolucion(6);
				Resolucion = 1536;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1600x900");
	}

	BotonY += 16;

	if (Resolucion == 1680)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1680x1050");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1680x1050");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1680, 1050);
				SetResolucion(7);
				Resolucion = 1650;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1680x1050");
	}

	BotonY += 16;

	if (Resolucion == 1920)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1920x1080");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 75, 15) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1920x1080");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ChangeResolution(1920, 1080);
				SetResolucion(8);
				Resolucion = 1920;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 75.0, 15.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 75.0, 3, "1920x1080");
	}

	BotonY += 15;

	gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 10, 75.0, 3, pGetTextLine_(pTextLineThis, 3901));//"Font Size"

	BotonY += 20;

	BotonX = 35;

	if (FontSize == 8)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "8");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "8");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(8);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "8");
	}

	BotonX += 14;

	if (FontSize == 9)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "9");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "9");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(9);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "9");
	}

	BotonX += 14;

	if (FontSize == 10)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "10");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "10");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(10);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "10");
	}

	BotonX += 14;

	if (FontSize == 11)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "11");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "11");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(11);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "11");
	}

	BotonX += 15;

	if (FontSize == 12)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "12");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "12");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(12);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "12");
	}

	BotonX += 15;

	if (FontSize == 13)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "13");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 14, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "13");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				sub_10012730(13);
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 14.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 14.0, 3, "13");
	}

}

void RenderOptionText(int a1)
{
	int This; // [sp+74h] [bp-4h]@1
	float x; // [sp+2Ch] [bp-8h]@1
	float y; // ST34_4@1
	char buffer[255]; // ST08_4@1

	This = *(DWORD *)(GetInstance() + 160);
	
	x = (double)*(signed int *)(This + 16);
	y = (double)*(signed int *)(This + 20);

	x = nInterface.OPTION_WINDOW->X;
	y = nInterface.OPTION_WINDOW->Y;

	x += 90;
}

void RenderOptionPanel(int a1)
{
	int This; // [sp+74h] [bp-4h]@1
	float x; // [sp+2Ch] [bp-8h]@1
	float y; // ST34_4@1

	This = *(DWORD *)(GetInstance() + 160);
	
	x = (double)*(signed int *)(This + 16);
	y = (double)*(signed int *)(This + 20);

	x = nInterface.OPTION_WINDOW->X;
	y = nInterface.OPTION_WINDOW->Y;

	x += 80;

	int BotonX = 140;
	int BotonY = 40;
//--
	pSetFont(pTextThis(), (int) pFontNormal);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	sub_4200F0_Addr(pTextThis(), 0);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.3);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 386), 0, 0,(LPINT) 1, 0); //-- Attack Automatic
	
	
	if (*(BYTE *)( This + 196) == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 196) = 1;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (*(BYTE *)( This + 196) == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 196) = 0;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.6);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 387), 0, 0,(LPINT) 1, 0); //-- Beep Sound
	

	if (*(BYTE *)( This + 197) == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 197) = 1;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (*(BYTE *)( This + 197) == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 197) = 0;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.3);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 919), 0, 0,(LPINT) 1, 0); //-- Slide Help
	

	if (*(BYTE *)( This + 198) == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 198) = 1;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (*(BYTE *)( This + 198) == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				*(BYTE *)( This + 198) = 0;
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.6);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3903), 0, 0,(LPINT) 1, 0); //-- User HPBar
	

	if (UserHpBar == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				UserHpBar = 1;
				WritePrivateProfileStringA("Other", "UserHpBar", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (UserHpBar == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				UserHpBar = 0;
				WritePrivateProfileStringA("Other", "UserHpBar", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.3);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3904), 0, 0,(LPINT) 1, 0); //-- Monster HPBar
	

	if (MonsterHpBar == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				MonsterHpBar = 1;
				WritePrivateProfileStringA("Other", "MonsterHpBar", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (MonsterHpBar == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				MonsterHpBar = 0;
				WritePrivateProfileStringA("Other", "MonsterHpBar", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.6);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3905), 0, 0,(LPINT) 1, 0); //-- Disable Static Effect
	

	if (DisableStaticEffect == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableStaticEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableStaticEffect", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (DisableStaticEffect == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableStaticEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableStaticEffect", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.3);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3906), 0, 0,(LPINT) 1, 0); //-- Disable Dynamic Effect
	

	if (DisableDynamicEffect == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableDynamicEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableDynamicEffect", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (DisableDynamicEffect == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableDynamicEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableDynamicEffect", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.6);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3907), 0, 0,(LPINT) 1, 0); //-- Disable Glow Effect
	

	if (DisableGlowEffect == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableGlowEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableGlowEffect", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (DisableGlowEffect == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableGlowEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableGlowEffect", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	////////////////////////////////////////////////////////////////////////////////////
	///

	BotonX -= 24;
	BotonY += 17;

	nInterface.DrawBarForm(x + 25, y + BotonY, 164, 13, 0.2, 0.0, 0.0, 0.6);//bg
	pDrawText(pTextThis(), x + 27, y + BotonY + 3.5, pGetTextLine_(pTextLineThis, 3909), 0, 0,(LPINT) 1, 0); //-- Disable Shadows
	

	if (DisableShadows == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableShadows = 1;
				KG_ActiveShades_1();
				WritePrivateProfileStringA("AntiLag", "DisableShadows", " 1", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "ON");
	}

	BotonX += 24;

	if (DisableShadows == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
		if (GetTickCount() - TickCountPro > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(1.0f, 0.0f, 0.0f);
				DisableShadows = 0;
				KG_ActiveShades_2();
				WritePrivateProfileStringA("AntiLag", "DisableShadows", " 0", ".\\Settings.ini");
				TickCountPro = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}
	//pDrawButton(31593, x + 27, y + 37, 15, 15, 0, ( *(BYTE *)( This + 196) ) ? 0.0 : 15.0); //-- Attack Automatic

	//pDrawButton(31593, x + 27, y + 57, 15, 15, 0, ( *(BYTE *)( This + 197) ) ? 0.0 : 15.0); //-- Beep Sound
	
	//pDrawButton(31593, x + 27, y + 77, 15, 15, 0, ( *(BYTE *)( This + 198) ) ? 0.0 : 15.0); //-- Slide Show

//-- Volumen
/*	//pDrawButton(71523, x + 27, y + 122+BotonV, 18, 15, 0, 0);
	gInterface.DrawFormat(eWhite, x + 27, y + 197, 124.0, 1, pGetTextLine2(pTextLineThis, 3902));
	pDrawGUI(31596, x + 55, y + 194, 124.0, 16.0);
	if ( *(DWORD *)(This + 200) > 0 )
	{
		pDrawGUI(31597, x + 55, y + 194, (double)*(signed int *)(This + 200) * 12.4, 16.0);
	}

	//-- Effects
	//pDrawButton(71523, x + 27, y + 122+BotonV, 18, 15, 0, 0);
	gInterface.DrawFormat(eWhite, x + 27, y + 228, 141.0, 1, "Effects");
	pDrawGUI(31594, x + 45, y + 218, 141.0, 29.0);
	if (*(DWORD*)(This + 204) > 0)
	{
		pDrawGUI(31595, x + 45, y + 218, (double)*(signed int*)(This + 204) * 28.0, 29.0);
	}
	*/
	// volume
	gInterface.DrawFormat(eWhite, x + 90, y + 200, 0, 1, pGetTextLine_(pTextLineThis, 3902));

	gInterface.DrawFormat(eWhite, x + 30, y + 232, 0, 1, "Effects Glow");

	const int volume_width = 124;

	const int volume_x = nInterface.OPTION_WINDOW->X + 130;
	const int volume_y = nInterface.OPTION_WINDOW->Y + 215;

	gInterface.DrawBarForm2(volume_x, volume_y, volume_width, 2, 1.0, 1.0, 1.0, 1.0);

	const float volume_value = (double)*(int*)(This + 200) * (volume_width / 10);

	gInterface.DrawBarForm2(volume_x + volume_value, volume_y - 4, 3, 10, 1.0, 0.0, 0.0, 1.0);

	// effects
	for (int i = 0; i < 5; i++)
	{
		MU_4float* current_color = &gInterface.base_black;

		if (i <= *(int*)(This + 204))
			current_color = &gInterface.base_color_selected;

		char text[5];
		itoa(game_options_effect_values[i], text, 10);
		
		gInterface.DrawButton7(eGameOptionsEffectsButton1 + i, nInterface.OPTION_WINDOW->X + 160 + (i * 20), nInterface.OPTION_WINDOW->Y + 230, 19, 15, current_color, &gInterface.MenuButtonClick, &gInterface.base_color_hover, text);
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

void InitOptionPanel()
{
	SetCompleteHook(0xE9, 0x008494B0, &RenderWindowsOption);

	SetCompleteHook(0xE9, 0x00849730, &RenderOptionText);
	SetCompleteHook(0xE9, 0x008499E0, &RenderOptionPanel);

	SetDword(0x00D479A8, (DWORD)&event_options_window);

	gInterface.base = MU_4float(1.0, 0.0, 0.0, 0.6);

	gInterface.base_black = MU_4float(0.0, 0.0, 0.0, 0.8);

	gInterface.base_color_selected = MU_4float(0.5, 0.0, 0.0, 1.0);

	gInterface.base_color_hover = MU_4float(0.5, 0.2, 0.2, 1.0);
}