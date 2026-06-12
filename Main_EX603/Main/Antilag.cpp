#include "stdafx.h"
#include "Antilag.h"
#include "User.h"
#include "Interface.h"
#include "Protocol.h"
#include "TMemory.h"
#include "Defines.h"
#include "Common.h"
#include "Util.h"
#include "Performance.h"
#include "WingInvisible.h"
#include "Protect.h"
#include "CustomFont.h"
#include "WideScreen.h"
#include "NewInterface.h"
#include "CNewUIWindowsClient.h"

int ButtonReset;
int ButtonMasterReset;
int ButtonActive;
int ButtonDaily;

cAntiLagSystem gAntiLagSystem;

cAntiLagSystem::cAntiLagSystem()
{
	this->Init();
}

cAntiLagSystem::~cAntiLagSystem()
{
}

void cAntiLagSystem::Init()
{
	this->Click = false;
}

void cAntiLagSystem::Load()
{

}

int TickCount;

// Estructura de offsets para cada resolucion
struct AntiLagPanelOffsets
{
	float windowX;         // x base del OPTION_WINDOW ajustado
	int   col2OffsetX;     // cuanto salta BotonX para la segunda columna (+= N)
	float labelOffset;     // offset X del texto label respecto a BotonX
};

static AntiLagPanelOffsets GetPanelOffsets()
{
	AntiLagPanelOffsets off;

	// Con el nuevo centrado por MAX_WIN_WIDTH/2, col2OffsetX es fijo para todas las resoluciones.
	// col2OffsetX = separacion entre el inicio del boton ON de col izquierda y el inicio del boton ON de col derecha.
	// Aumenta este valor si las columnas se solapan, disminuyelo si quedan muy separadas.
	off.windowX = 0.0f;   // ya no se usa (el centrado lo hace la formula MAX_WIN_WIDTH/2)
	off.col2OffsetX = 105;    // <-- AJUSTA ESTE VALOR: separa las dos columnas
	off.labelOffset = -137.0f;

	return off;
}

void cAntiLagSystem::Draw()
{
	if (!gInterface.Data[eADDPOINT_MAIN].OnShow)
	{
		return;
	}

	if (gInterface.CheckWindow(CashShop))
	{
		return;
	}

	gInterface.CheckWindowSProTecno(7);

	pSetCursorFocus = true;

	float WindowW = 420;
	float WindowH = 300;
	float MainWidth, MainHeight;
	MainWidth = 230.0;
	MainHeight = 283.0;
	float StartBody = 80.0;
	float StartY = 110;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	float InfoMocNapX = (StartX + 10) + 3;
	float InfoMocNapY = (StartY + 15);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX - 11, StartY - 7, 255, 245, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, (int)StartX + 12, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(109));
		gInterface.DrawGUI(eADDPOINT_CLOSE, StartX + 223, StartY + 7);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + 223, StartY + 8, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eADDPOINT_CLOSE))
		{
			DWORD Color = eOrion;

			if (gInterface.Data[eADDPOINT_CLOSE].OnClick)
			{
				Color = eOrion;
			}

			gInterface.DrawColoredGUI(eADDPOINT_CLOSE, gInterface.Data[eADDPOINT_CLOSE].X, gInterface.Data[eADDPOINT_CLOSE].Y, Color);
		}
	}
	else
	{
		RenderBitmap(61322, StartX - 10, StartY + 15, 255, 280, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX - 10, StartY - 15, 255, 42, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawGUI(eADDPOINT_CLOSE, StartX + 21 + MainWidth - gInterface.Data[eADDPOINT_CLOSE].Width - 2, StartBody + 15);
		gInterface.DrawFormat(eGold, (int)StartX + 14, (int)StartBody + 34, 210, 3, gCustomMessage.GetMessage(109));

		if (gInterface.IsWorkZone(eADDPOINT_CLOSE))
		{
			DWORD Color = eOrion;

			if (gInterface.Data[eADDPOINT_CLOSE].OnClick)
			{
				Color = eOrion;
			}

			gInterface.DrawColoredGUI(eADDPOINT_CLOSE, gInterface.Data[eADDPOINT_CLOSE].X, gInterface.Data[eADDPOINT_CLOSE].Y, Color);
		}
	}

	float x;
	float y;
	int This;

	This = *(DWORD*)(GetInstance() + 160);

	*(signed int*)(This + 16) = 320 - (140 / 2);
	x = (double)*(signed int*)(This + 16);
	y = (double)*(signed int*)(This + 20);

	// Obtener offsets segun resolucion actual
	AntiLagPanelOffsets panelOff = GetPanelOffsets();

	int BotonX = 40;
	int BotonY = -70;

	// Posicion centrada en pantalla, independiente de OPTION_WINDOW
	float panelWidth = 160.0f;  // ancho visual aproximado del panel AntiLag
	float panelHeight = 165.0f;  // alto visual aproximado del panel AntiLag
	x = StartX + 35.0f;
	y = StartY + 84.0f;

	// =====================================================
	// COLUMNA IZQUIERDA
	// =====================================================

	// --- Static Effect ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Static Effect");

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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte(0x771310, 0xC3);
				DisableStaticEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableStaticEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte(0x771310, 0x55);
				DisableStaticEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableStaticEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eOrion, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OFF");
	}

	BotonX -= 24;
	BotonY += 17;

	// --- Glow Effect ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Glow Effect");

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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				DisableGlowEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableGlowEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				DisableGlowEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableGlowEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Effe Dynami ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Effe Dynami");

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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte(0x74CD30, 0xC3);
				SetByte(0x00608FB0, 0xC3);
				SetDword((0x0072D1BA + 3), 0);
				DisableDynamicEffect = 1;
				WritePrivateProfileStringA("AntiLag", "DisableDynamicEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte(0x74CD30, 0x55);
				SetByte(0x00608FB0, 0x55);
				SetDword((0x0072D1BA + 3), 500);
				DisableDynamicEffect = 0;
				WritePrivateProfileStringA("AntiLag", "DisableDynamicEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Invisibility ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Invisibility");

	if (testFunctionInvItem2 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				DelectlpViewPlayerOn_Hook();
				testFunctionInvItem2 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableInvisibility", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem2 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				DelectlpViewPlayerOff_Hook();
				testFunctionInvItem2 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableInvisibility", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Invisi Wing ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Invisi Wing");

	if (testFunctionInvItem5 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x588661, 0x90, 0x5);
				SetByte(0x0051EC90, 0xC3);
				SetByte(0x0051EE20, 0xC3);
				testFunctionInvItem5 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableCloack", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem5 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x00588661, (LPVOID)0x005655C0, ASM::CALL);
				SetByte(0x0051EC90, 0x55);
				SetByte(0x0051EE20, 0x55);
				testFunctionInvItem5 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableCloack", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Invi Weapon ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 136, y + BotonY + 1, 210, 3, "Invi Weapon");

	if (testFunctionInvItem6 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x576DDB, 0x90, 0x5);
				MemorySet(0x5883F4, 0x90, 0x5);
				testFunctionInvItem6 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableWeapons", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem6 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x00576DDB, (LPVOID)0x005655C0, ASM::CALL);
				SetOp((LPVOID)0x005883F4, (LPVOID)0x005655C0, ASM::CALL);
				testFunctionInvItem6 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableWeapons", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Slash Effect ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Slash Effect");

	if (testFunctionInvItem12 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x0055C763, 0x90, 0x5);
				testFunctionInvItem12 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableSlashEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem12 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x0055C763, (LPVOID)0x006D9070, ASM::CALL);
				testFunctionInvItem12 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableSlashEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Transparency ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 134, y + BotonY + 1, 210, 3, "Transparency");

	if (testFunctionInvItem == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				InvisibleItem1();
				testFunctionInvItem = 1;
				WritePrivateProfileStringA("AntiLag", "Transparency", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				InvisibleItem2();
				InvisibleItemX();
				testFunctionInvItem = 0;
				WritePrivateProfileStringA("AntiLag", "Transparency", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Effect +15 ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Effect +15");

	if (testFunctionInvItem7 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x0057655B, 0x90, 0x5);
				testFunctionInvItem7 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableEffect15", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem7 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x0057655B, (LPVOID)0x006097B0, ASM::CALL);
				testFunctionInvItem7 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableEffect15", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- TimerBar ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "TimerBar");

	if (TimerBar == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				TimerBar = 1;
				WritePrivateProfileStringA("AntiLag", "TimerBar", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (TimerBar == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				TimerBar = 0;
				WritePrivateProfileStringA("AntiLag", "TimerBar", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	// =====================================================
	// COLUMNA DERECHA  -- salto X dependiente de resolucion
	// =====================================================
	BotonX -= 24;  // reset al inicio de columna izquierda
	BotonX += panelOff.col2OffsetX;   // salto a columna derecha segun resolucion
	BotonY -= 153; // volver al primer renglon

	// --- Object Rend ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Object Rend");

	if (testFunctionInvItem8 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte((PVOID)(0x005DE2B2), 1);
				testFunctionInvItem8 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableObjectRender", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem8 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetByte((PVOID)(0x005DE2B2), 0);
				testFunctionInvItem8 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableObjectRender", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Terrain Rend ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 136, y + BotonY + 1, 210, 3, "Terrain Rend");

	if (testFunctionInvItem9 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				testFunctionInvItem9 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableTerrainRender", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem9 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				testFunctionInvItem9 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableTerrainRender", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Exce Effect ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Exce Effect");

	if (testFunctionInvItem10 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetRange(0x0060954D, 7, 0x90);
				SetOp(0x0060954D, (LPVOID)DisableExcellentGlow002_on, 0xE9);
				SetRange(0x0060F04C, 7, 0x90);
				SetOp(0x0060F04C, (LPVOID)DisableExcellentGlow003_on, 0xE9);
				testFunctionInvItem10 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableExcellenEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem10 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetRange(0x0060954D, 7, 0x90);
				SetOp(0x0060954D, (LPVOID)DisableExcellentGlow002_off, 0xE9);
				SetRange(0x0060F04C, 7, 0x90);
				SetOp(0x0060F04C, (LPVOID)DisableExcellentGlow003_off, 0xE9);
				testFunctionInvItem10 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableExcellenEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Zen Drop ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Zen Drop");

	if (testFunctionInvItem11 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x005F8924, 0x90, 0x5);
				testFunctionInvItem11 = 1;
				WritePrivateProfileStringA("AntiLag", "ReduceZenDrop", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem11 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x005F8924, (LPVOID)0x0095A1E0, ASM::CALL);
				testFunctionInvItem11 = 0;
				WritePrivateProfileStringA("AntiLag", "ReduceZenDrop", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Birds Effect ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Birds Effect");

	if (testFunctionInvItem13 == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MemorySet(0x00649131, 0x90, 0x5);
				MemorySet(0x0064926D, 0x90, 0x5);
				MemorySet(0x006492E8, 0x90, 0x5);
				MemorySet(0x00647E5F, 0x90, 0x5);
				MemorySet(0x00647F9B, 0x90, 0x5);
				MemorySet(0x00648016, 0x90, 0x5);
				MemorySet(0x005AE36E, 0x90, 0x5);
				MemorySet(0x005AE48C, 0x90, 0x5);
				MemorySet(0x005AE507, 0x90, 0x5);
				testFunctionInvItem13 = 1;
				WritePrivateProfileStringA("AntiLag", "DisableBirdsEffect", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (testFunctionInvItem13 == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				SetOp((LPVOID)0x00649131, (LPVOID)0x006D9070, ASM::CALL);
				SetOp((LPVOID)0x0064926D, (LPVOID)0x0072D1B0, ASM::CALL);
				SetOp((LPVOID)0x006492E8, (LPVOID)0x006EFF10, ASM::CALL);
				SetOp((LPVOID)0x00647E5F, (LPVOID)0x006D9070, ASM::CALL);
				SetOp((LPVOID)0x00647F9B, (LPVOID)0x0072D1B0, ASM::CALL);
				SetOp((LPVOID)0x00648016, (LPVOID)0x006EFF10, ASM::CALL);
				SetOp((LPVOID)0x005AE36E, (LPVOID)0x006D9070, ASM::CALL);
				SetOp((LPVOID)0x005AE48C, (LPVOID)0x0072D1B0, ASM::CALL);
				SetOp((LPVOID)0x005AE507, (LPVOID)0x006EFF10, ASM::CALL);
				testFunctionInvItem13 = 0;
				WritePrivateProfileStringA("AntiLag", "DisableBirdsEffect", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Button Reset ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 136, y + BotonY + 1, 210, 3, "Button Reset");

	if (ButtonReset == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				ButtonReset = 1;
				WritePrivateProfileStringA("AntiLag", "DisableButtonReset", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (ButtonReset == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ButtonReset = 0;
				WritePrivateProfileStringA("AntiLag", "DisableButtonReset", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Button Master ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 134, y + BotonY + 1, 210, 3, "Button Master");

	if (ButtonMasterReset == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				ButtonMasterReset = 1;
				WritePrivateProfileStringA("AntiLag", "DisableButtonMasterReset", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (ButtonMasterReset == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ButtonMasterReset = 0;
				WritePrivateProfileStringA("AntiLag", "DisableButtonMasterReset", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Button Active ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 134, y + BotonY + 1, 210, 3, "Button Active");

	if (ButtonActive == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				ButtonActive = 1;
				WritePrivateProfileStringA("AntiLag", "DisableButtonActive", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (ButtonActive == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ButtonActive = 0;
				WritePrivateProfileStringA("AntiLag", "DisableButtonActive", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Button Daily ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Button Daily");

	if (ButtonDaily == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				ButtonDaily = 1;
				WritePrivateProfileStringA("AntiLag", "DisableButtonDaily", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (ButtonDaily == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				ButtonDaily = 0;
				WritePrivateProfileStringA("AntiLag", "DisableButtonDaily", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	BotonX -= 24;
	BotonY += 17;

	// --- Disable Ping ---
	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "Disable Ping");

	if (DisablePing == 1)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				DisablePing = 1;
				WritePrivateProfileStringA("AntiLag", "DisablePing", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	if (DisablePing == 0)
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
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				DisablePing = 0;
				WritePrivateProfileStringA("AntiLag", "DisablePing", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
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

	// =====================================================
	// FILA INFERIOR: MiniMapType (centrado, debajo de ambas columnas)
	// =====================================================
	// Calcular el centro del panel entre las dos columnas
	int miniMapBaseX;
	if (MAX_WIN_WIDTH >= 2560)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1920)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1680)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1600)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1440)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1366)
	{
		miniMapBaseX = -4;
	}
	else if (MAX_WIN_WIDTH >= 1280)
	{
		miniMapBaseX = -4;
	}
	else
	{
		// 1024x768
		miniMapBaseX = -4;
	}

	// BotonX actualmente en col2 + 24; recalcular centro entre col izquierda y col derecha
	// Col izq base = 40, col der base = 40 + col2OffsetX
	// Centro aprox = 40 + col2OffsetX/2
	BotonX = 40 + (panelOff.col2OffsetX / 2) + miniMapBaseX;
	BotonY += 28;

	nInterface.DrawBarForm(x + BotonX - 58, y + BotonY, 103, 13, 0.2, 0.0, 0.0, 0.6);
	gInterface.DrawFormat(eOrion, x + BotonX - 137, y + BotonY + 1, 210, 3, "MiniMapType");

	if (MiniMapType == 1)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "1");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "1");
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				MiniMapType = 1;
				WritePrivateProfileStringA("Setting", "MiniMapType", " 1", ".\\Settings.ini");
				TickCount = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "1");
	}

	BotonX += 24;

	if (MiniMapType == 2)
	{
		glColor3f(0.2f, 1.0f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "2");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "2");
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				MiniMapType = 2;
				WritePrivateProfileStringA("Setting", "MiniMapType", " 2", ".\\Settings.ini");
				TickCount = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "2");
	}

	BotonX += 24;

	if (MiniMapType == 0)
	{
		glColor3f(1.0f, 0.2f, 0.2f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OF");
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else if (pCheckMouseOver(x + BotonX, y + BotonY, 24, 13) == 1)
	{
		glColor3f(0.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OF");
		if (GetTickCount() - TickCount > 300)
		{
			if (GetKeyState(1) & 0x8000)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				MiniMapType = 0;
				WritePrivateProfileStringA("Setting", "MiniMapType", " 0", ".\\Settings.ini");
				TickCount = GetTickCount();
			}
		}
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		RenderBitmap(31563, x + BotonX, y + BotonY, 24.0, 13.0, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
		gInterface.DrawFormat(eWhite, x + BotonX, y + BotonY + 3.5, 24.0, 3, "OF");
	}
}

bool cAntiLagSystem::EventUsersPanelAntiLag_CLOSE(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eADDPOINT_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eADDPOINT_MAIN].OnShow || !gInterface.IsWorkZone(eADDPOINT_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eADDPOINT_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eADDPOINT_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eADDPOINT_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eADDPOINT_MAIN].Close();
	// ----
	return false;
}
