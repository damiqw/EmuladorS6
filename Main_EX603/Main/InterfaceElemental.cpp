#include "stdafx.h"
#include "Interface.h"
#include "InterfaceElemental.h"
#include "CNewUIWindowsClient.h"
#include "Import.h"
#include "TMemory.h"
#include "Defines.h"
#include "Protect.h"
#include "User.h"
#include "CustomFont.h"

CElemental gElemental;

CElemental::CElemental()
{
	this->MsgBoxType = -1;
	this->MsgBoxCallback = 0;
	this->MsgLine = 0;
	//this->m_OptionRate.clear();
	//this->m_Counter.clear();
	this->LockButtonHover = 0;
}


CElemental::~CElemental()
{
}


void CElemental::DrawMessageBox()
{
	if (!gInterface.Data[eWindowMessageBox].OnShow)
	{
		return;
	}

	int Main_Font_Height = 14;
	float CuaSoW = 190;
	float CuaSoH = 90+(this->MsgLine*10);
	float StartX;
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (CuaSoW / 2);
	}
	else
	{
		StartX = (640 / 2) - (CuaSoW / 2);
	}
	float StartY = 45.0;
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	gElemental.gDrawWindowCustom(StartX, StartY, CuaSoW, CuaSoH, eWindowMessageBox, this->MsgBoxCaption);
	gElemental.DrawTextA((HFONT)pFontNormal, StartX , StartY+35, 0xFFFFFFFF, 0x0, CuaSoW, 0, 3, this->MsgBoxText);
	if (this->MsgBoxType == 0)
	{
		float BtnHeight = 20.0;
		float BtnWidth = 120.0;
		if (gElemental.gDrawButton(StartX + CuaSoW / 2 - (BtnWidth / 2), StartY + CuaSoH - BtnHeight - 10, BtnWidth, Main_Font_Height, "CLOSE"))
		{
			gInterface.Data[eWindowMessageBox].OnShow = 0;
		}
	}
	else if (this->MsgBoxType == 1)
	{
		float BtnHeight = 20.0;
		float BtnWidth = 55.0;
		if (gElemental.gDrawButton(StartX + CuaSoW / 2 - (BtnWidth + 7.5), StartY + CuaSoH - BtnHeight - 10, BtnWidth, Main_Font_Height, "OKAY"))
		{
			this->MsgBoxCallback(this);
			this->MsgBoxCallback = 0;
			gInterface.Data[eWindowMessageBox].OnShow = 0;
		}

		if (gElemental.gDrawButton(StartX + CuaSoW / 2 + (7.5), StartY + CuaSoH - BtnHeight - 10, BtnWidth, Main_Font_Height, "CLOSE"))
		{
			gInterface.Data[eWindowMessageBox].OnShow = 0;
		}
	}
	pGLSwitch();
	EnableAlphaTest(0);

}
int DemDong(char* chuoi)
{
	int length = strlen(chuoi), dem = 0;
	for (int i = 0; i < length; i++)
		if (chuoi[i] == '#')
			dem++;
	return dem / 2;
}
void CElemental::OpenMessageBox(char* caption, char* Format, ...)
{
	if (gInterface.Data[eWindowMessageBox].OnShow)
	{
		return;
	}

	char text[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(text, Format, va);
	va_end(va);
	this->MsgLine = 0;
	memset(this->MsgBoxCaption, 0, sizeof(this->MsgBoxCaption));
	memset(this->MsgBoxText, 0, sizeof(this->MsgBoxText));

	memcpy(this->MsgBoxCaption, caption, sizeof(this->MsgBoxCaption));
	memcpy(this->MsgBoxText, text, sizeof(this->MsgBoxText));
	this->MsgLine = DemDong(this->MsgBoxText);
	gInterface.Data[eWindowMessageBox].OnShow = true;
	this->MsgBoxType = 0;
	pSetCursorFocus = true;
}

void CElemental::OpenMessageBoxOkCancel(PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, char* caption, char* Format, ...)
{
	if (gInterface.Data[eWindowMessageBox].OnShow)
	{
		return;
	}

	char text[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(text, Format, va);
	va_end(va);

	this->MsgLine = 0;
	memset(this->MsgBoxCaption, 0, sizeof(this->MsgBoxCaption));
	memset(this->MsgBoxText, 0, sizeof(this->MsgBoxText));

	memcpy(this->MsgBoxCaption, caption, sizeof(this->MsgBoxCaption));
	memcpy(this->MsgBoxText, text, sizeof(this->MsgBoxText));
	this->MsgLine = DemDong(this->MsgBoxText);
	//gInterface.DrawMessage(1, "DDDD %d %d", this->MsgLine, DemDong(this->MsgBoxText));
	gInterface.Data[eWindowMessageBox].OnShow = true;
	this->MsgBoxType = 1;
	this->MsgBoxCallback = pCallbackFunc;
	pSetCursorFocus = true;
}

void CElemental::gDrawWindowCustomEX700(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}
	pSetCursorFocus = true; //Khoa Chuot

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		this->LockMouse = GetTickCount() + 500;
	}

	float ScaleW = (1024 / CuaSoW) / pWinWidthReal;
	float ScaleH = (1024 / CuaSoH) / pWinHeightReal;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	int CloseX = StartX + CuaSoW - 20.0f;
	int CloseY = StartY;

	this->DrawFrame(0xF1007, StartX, StartY, 1024, 1024, 0.0, 0.0, 1024, 1024, ScaleW, ScaleH, 0);

	gInterface.DrawFormat(eShinyGreen, StartX, StartY + 30, CuaSoW, 3, WindowName);

	if (nInterface.Drawbutton(nInterface.CloseWindowsUP, CloseX, CloseY+30, "") || GetKeyState(VK_ESCAPE) & 0x4000)
	{
		PlayBuffer(25, 0, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		gInterface.Data[eNumWindow].OnShow ^= 1;
		gInterface.Data[eNumWindow].EventTick = GetTickCount();
		pSetCursorFocus = false; // mo khoa
	}

	if (pCheckMouseOver(CloseX, CloseY+30, 20, 19))
	{
		gInterface.DrawToolTip(gObjUser.m_CursorX-20, gObjUser.m_CursorY, "Close");
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

void CElemental::gDrawWindowCustomEX700Ranking(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}
	pSetCursorFocus = true; //Khoa Chuot

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		this->LockMouse = GetTickCount() + 500;
	}

	float ScaleW = (1024 / CuaSoW) / pWinWidthReal;
	float ScaleH = (1024 / CuaSoH) / pWinHeightReal;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	int CloseX = StartX + CuaSoW - 20.0f;
	int CloseY = StartY;

	this->DrawFrame(0xF1007, StartX, StartY, 1024, 1024, 0.0, 0.0, 1024, 1024, ScaleW, ScaleH, 0);

	gInterface.DrawFormat(eShinyGreen, StartX, StartY + 25, CuaSoW, 3, WindowName);

	if (nInterface.Drawbutton(nInterface.CloseWindowsUP, CloseX-5, CloseY + 25, "") || GetKeyState(VK_ESCAPE) & 0x4000)
	{
		PlayBuffer(25, 0, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		gInterface.Data[eNumWindow].OnShow ^= 1;
		gInterface.Data[eNumWindow].EventTick = GetTickCount();
		pSetCursorFocus = false; // mo khoa
	}

	if (pCheckMouseOver(CloseX-5, CloseY + 25, 20, 19))
	{
		gInterface.DrawToolTip(gObjUser.m_CursorX - 20, gObjUser.m_CursorY, "Close");
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

void CElemental::gDrawWindowCustomEX700Mini(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}
	pSetCursorFocus = true; //Khoa Chuot

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		this->LockMouse = GetTickCount() + 500;
	}

	float ScaleW = (1024 / CuaSoW) / pWinWidthReal;
	float ScaleH = (1024 / CuaSoH) / pWinHeightReal;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	int CloseX = StartX + CuaSoW - 20.0f;
	int CloseY = StartY;

	this->DrawFrame(0xF1007, StartX, StartY, 1024, 1024, 0.0, 0.0, 1024, 1024, ScaleW, ScaleH, 0);

	gInterface.DrawFormat(eShinyGreen, StartX, StartY + 10, CuaSoW, 3, WindowName);

	if (nInterface.Drawbutton(nInterface.CloseWindowsUP, CloseX, CloseY + 10, "") || GetKeyState(VK_ESCAPE) & 0x4000)
	{
		PlayBuffer(25, 0, 0);
		glColor3f(1.0f, 0.0f, 0.0f);
		gInterface.Data[eNumWindow].OnShow ^= 1;
		gInterface.Data[eNumWindow].EventTick = GetTickCount();
		pSetCursorFocus = false; // mo khoa
	}

	if (pCheckMouseOver(CloseX, CloseY + 10, 20, 19))
	{
		gInterface.DrawToolTip(gObjUser.m_CursorX - 20, gObjUser.m_CursorY, "Close");
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

void CElemental::gDrawWindowCustom(float StartX, float StartY, float CuaSoW, float CuaSoH, int eNumWindow, char* WindowName)
{
	if (!gInterface.Data[eNumWindow].OnShow)
	{
		return;
	}
	pSetCursorFocus = true; //Khoa Chuot

	if (pCheckMouseOver(StartX, StartY, CuaSoW, CuaSoH) == 1)
	{
		this->LockMouse = GetTickCount() + 500;
	}

	float ScaleW = (225 / CuaSoW) / pWinWidthReal;
	float ScaleH = (225 / CuaSoH) / pWinHeightReal;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	this->DrawFrame(31322, StartX, StartY, 225, 225, 0.0, 0.0, 270, 225, ScaleW, ScaleH); //khung goc ben trai tren

	//==== NGang Tren va Duoi
	for (int i = StartX + 10; i < (StartX + CuaSoW) - 10; i += 10)
	{
		pDrawButton(31353, i, StartY, 10.0, 64.0, 60.0, 0); //khung goc ben trai tren
		pDrawButton(31357, i, (StartY + CuaSoH) - 45.0, 10.0, 45.0, 60.0, 0); //khung goc ben trai tren
	}

	//=== Nen va thanh doc 2 trai phai
	for (int doc = StartY + 10; doc < (StartY + CuaSoH) - 10; doc += 10)
	{
		pDrawButton(31355, StartX, doc, 21.0, 10, 0, 0); //Khung giua ben trai
		pDrawButton(31356, (StartX + CuaSoW) - 21.0, doc, 21.0, 10, 0, 0); //Khung giua ben phai
	}
	pDrawButton(31353, StartX, StartY, 60.0, 64.0, 0, 0); //khung goc ben trai tren
	pDrawButton(31353, (StartX + CuaSoW) - 60.0, StartY, 60.0, 64.0, 130.0, 0); //khung goc ben phai tren

	pDrawButton(31357, StartX, (StartY + CuaSoH) - 45.0, 60.0, 45.0, 0, 0); //khung goc ben trai duoi
	pDrawButton(31357, (StartX + CuaSoW) - 60.0, (StartY + CuaSoH) - 45.0, 60.0, 45.0, 130.0, 0); //khung goc ben phai duoi

	gInterface.DrawFormat(eShinyGreen, StartX, StartY + 7, CuaSoW, 3, WindowName);
	pGLSwitch();
	EnableAlphaTest(0);
}

void CElemental::gInfoBox(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float bAlpha, int Arg6)
{
	float Red = (float)((bkcolor & 0xff000000) >> 24) / 255.0f;
	float Green = (float)((bkcolor & 0x00ff0000) >> 16) / 255.0f;
	float Blue = (float)((bkcolor & 0x0000ff00) >> 8) / 255.0f;
	float Alpha = (float)(bkcolor & 0x000000ff) / 255.0f;
	if (bAlpha > 0) { Alpha -= (bAlpha / 255.0f); }
	pSetBlend(1);
	if (bkcolor)
	{
		glColor4f(Red, Green, Blue, Alpha);
		pDrawBarForm(PosX, PosY, Width + 6.5, Height + 5, 0, Arg6); //central
	}
	float RightX = PosX - 2.0f;
	float LeftX = (PosX + Width) - 2.0f;
	float TopY = PosY - 2.0f;
	float DownY = (PosY + Height) - 2.0f;
	bool horizontal = true;
	bool vertical = true;
	//--
	float IniciarX = PosX - 2.0f;
	float w = 14.0f;
	//--
	float IniciarY = PosY - 2.0f;
	float H = 14.0f;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	while (vertical || horizontal)
	{
		if (vertical)
		{
			IniciarX += 14.0f;

			if ((IniciarX + w) > LeftX)
			{
				vertical = false;
				w = LeftX - IniciarX;
			}
			pDrawGUI(31344, IniciarX, TopY, w, 14.0f); //Ngang

			pDrawGUI(31345, IniciarX, DownY, w, 14.0f); //Ngang 2
		}
		//-- abajo
		if (horizontal)
		{
			IniciarY += 14.0f;

			if ((IniciarY + H) > DownY)
			{
				horizontal = false;
				H = DownY - IniciarY;
			}

			pDrawGUI(31346, RightX, IniciarY, 14.0f, H); // Doc 1

			pDrawGUI(31347, LeftX, IniciarY, 14.0f, H); //Doc 2
		}
	}

	pDrawGUI(31340, RightX, TopY, 14.0f, 14.0f); //Goc tren ben trai

	pDrawGUI(31341, LeftX, TopY, 14.0f, 14.0f); //Goc tren ben phai

	pDrawGUI(31342, RightX, DownY, 14.0f, 14.0f);  //Goc duoi trai

	pDrawGUI(31343, LeftX, DownY, 14.0f, 14.0f);  //Goc Duoi phai

	pGLSwitch();
	EnableAlphaTest(0);
}


void CElemental::DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp) {
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.0);
}

bool CElemental::gDrawButtonProTecno(float PosX, float PosY, float SizeButton, int FontSize, char* ButtonText, float mSizeButtonW, bool IsEnter)
{
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;

	if (mSizeButtonW != 0)
	{
		SizeButtonW = mSizeButtonW;
	}
	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;
	float ScaleX = 0.0, ScaleY = 0.227;
	HFONT FontTextButton = CreateFontA(FontSize, 0, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3u, 0, "Arial");
	//=====================Button 1
	if (pCheckMouseOver(StartX, StartY, SizeButtonW, SizeButtonH) == 1 && !gElemental.LockButtonHover)
	{
		gElemental.DelayMouseLock = 30;
		ScaleX = ScaleY;
		if (GetTickCount() - gInterface.Data[eTIME].EventTick > 500) //Click
		{
			if (GetKeyState(VK_LBUTTON) & 0x8000)
			{

				ScaleX = ScaleY * 2;
				gInterface.Data[eTIME].EventTick = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
			}
		}
	}
	if ((GetKeyState(VK_RETURN) & 0x8000) && IsEnter)
	{
		gInterface.CloseWindow(ChatWindow);
		PlayBuffer(25, 0, 0);
		mreturn = true;

	}
	//31563
	//RenderBitmap(31563, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);

	RenderBitmap(31326, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, ScaleX, 0.830, ScaleY, 1, 1, 0);
	
	this->DrawText(FontTextButton, StartX, StartY + (SizeButtonH / 2) - (FontSize / 2.5), 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, ButtonText); //Buoc Vao
	//=====================================
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	DeleteObject(FontTextButton);
	DeleteObject(ButtonText);
	pGLSwitch();
	EnableAlphaTest(0);
	return mreturn;
}

bool CElemental::gDrawButtonKings(float PosX, float PosY, float SizeButton, int FontSize, LPCSTR Text, ...)
{

	char ButtonText[2048];
	int BuffLen = sizeof(ButtonText) - 1;
	ZeroMemory(ButtonText, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(ButtonText, BuffLen, Text, args);
	va_end(args);


	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;
	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;
	float ScaleX = 0.0012, ScaleY = 0.227;
	//HFONT FontTextButton = CreateFontA(FontSize, Main_Font_Width, 0, 0, 700, Main_Font_Italic, Main_Font_Underline, Main_Font_StrikeOut, 0x1, 0, 0, Main_Font_Quality, 0, "Tahoma");
	//HFONT FontTexInfoEvent = CreateFontA(16, FontHeight-7, 0, 0, 400, 0, 0, 0, 1u, 0, 0, 3u, 0, "Tahoma");
	//=====================Button 1
	if (pCheckMouseOver(StartX, StartY, SizeButtonW, SizeButtonH) == 1)
	{
		ScaleX = ScaleY;
		if (GetTickCount() - gInterface.Data[eTIME].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(0.72f, 0.438f, 0.0432f);

				ScaleX = ScaleY * 2;
				gInterface.Data[eTIME].EventTick = GetTickCount();
				mreturn = true;
			}
		}
	}
	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		RenderBitmap(0x7A5E, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, ScaleX, 0.830, ScaleY, 1, 1, 0);
	}
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(71524, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, ScaleX, 0.830, ScaleY, 1, 1, 0);
	}
	//RenderBitmap(31563, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	//CustomFont.Draw(FontTexInfoEvent, StartX, StartY + (SizeButtonH / 2) - (FontSize / 2.5), 0xE6FCF7FF, 0x0, SizeButtonW, 0, 3, ButtonText); //Buoc Vao
	gInterface.DrawFormat(eWhite, StartX, StartY + (SizeButtonH / 2) - (FontSize / 2.5), SizeButtonW, 3, ButtonText);
	//=====================================
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau

	pGLSwitch();
	EnableAlphaTest(0);
	return mreturn;
}

bool CElemental::gDrawButton(float PosX, float PosY, float SizeButton, int FontSize, char* ButtonText , float mSizeButtonW)
{
	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);
	//============Button
	float SizeButtonW = SizeButton;
	float SizeButtonH = (SizeButton * 20) / 100;
	if (mSizeButtonW != 0)
	{
		SizeButtonW = mSizeButtonW;
	}

	float StartX = PosX;
	float StartY = PosY;
	bool mreturn = false;
	
	//=====================Button 1
	if (pCheckMouseOver(StartX, StartY, SizeButtonW, SizeButtonH) == 1 && !this->LockButtonHover)
	{
		glColor3f(1.0f, 0.6742f, 0.15f);
		if (GetTickCount() - gInterface.Data[eWindowElemental].EventTick > 300) //Click
		{
			if (GetKeyState(1) & 0x8000)
			{

				glColor3f(0.72f, 0.438f, 0.0432f);


				gInterface.Data[eWindowElemental].EventTick = GetTickCount();
				mreturn = true;
			}
		}
	}
	else {
		glColor3f(1.0f, 1.0f, 1.0f);

	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(61535, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.5035384717, 0.2215384692, 1, 1, 0);
	}
	else
	{
		RenderBitmap(31563, StartX, StartY, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.64999998, 0.80000001, 1, 1, 0);
	}
	gInterface.DrawFormat(eGold, StartX, StartY + (SizeButtonH / 2) - (FontSize / 2.5), SizeButtonW, 3, ButtonText);
	//=====================================
	glColor3f(1.0f, 1.0f, 1.0f); //Xoa mau
	DeleteObject(ButtonText);
	pGLSwitch();
	EnableAlphaTest(0);
	return mreturn;
}

void CElemental::PrintDropBox(float PosX, float PosY, float Width, float Height, float Arg5, int Arg6, float gradiente)
{
	EnableAlphaTest(1);

	pSetCursorFocus = true;
	glColor4f(0.0, 0.0, 0.0, gradiente/*0.80000001*/);
	pDrawBarForm(PosX, PosY, Width, Height, Arg5, Arg6); //central

	float RightX = PosX - 8.0f;
	float LeftX = (PosX + Width) - 8.0f;
	float TopY = PosY - 8.0f;
	float DownY = (PosY + Height) - 8.0f;
	bool horizontal = true;
	bool vertical = true;
	//--
	float IniciarX = PosX - 8.0f;
	float w = 16.0f;
	//--
	float IniciarY = PosY - 8.0f;
	float H = 16.0f;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	while (vertical || horizontal)
	{
		if (vertical)
		{
			IniciarX += 16.0f;

			if ((IniciarX + w) > LeftX)
			{
				vertical = false;
				w = LeftX - IniciarX;
			}
			pDrawGUI(71512, IniciarX, TopY, w, 16.0f); //arriba

			pDrawGUI(71517, IniciarX, DownY, w, 16.0f); //abajo
		}
		//-- abajo
		if (horizontal)
		{
			IniciarY += 16.0f;

			if ((IniciarY + H) > DownY)
			{
				horizontal = false;
				H = DownY - IniciarY;
			}

			pDrawGUI(71514, RightX, IniciarY, 16.0f, H); // Lado Izquierdo

			pDrawGUI(71515, LeftX, IniciarY, 16.0f, H); //Lado Derecho
		}
	}

	pDrawGUI(71511, RightX, TopY, 16.0f, 16.0f); //esquina arriba izquierda

	pDrawGUI(71513, LeftX, TopY, 16.0f, 16.0f); //esquina arriba derecha

	pDrawGUI(71516, RightX, DownY, 16.0f, 16.0f);  //esquina abajo izquierda

	pDrawGUI(71518, LeftX, DownY, 16.0f, 16.0f);  //esquina abajo derecha

	pGLSwitch();
	EnableAlphaTest(0);
}

void CElemental::DrawText(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...) 
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char* Line = strtok(Buff, "\n##");

	while (Line != NULL)
	{
		pSetFont(pTextThis(), (int)font);
		pSetTextColor(pTextThis(), (color & 0xff000000) >> 24, (color & 0x00ff0000) >> 16, (color & 0x0000ff00) >> 8, color & 0x000000ff);
		pSetBackgroundTextColor(pTextThis(), (bkcolor & 0xff000000) >> 24, (bkcolor & 0x00ff0000) >> 16, (bkcolor & 0x0000ff00) >> 8, bkcolor & 0x000000ff);
		pDrawText(pTextThis(), PosX, PosY, Line, Width, Height, (LPINT)Align, 0);
		PosY += 10;
		Line = strtok(NULL, "\n##");
		pSetFont(pTextThis(), (int)pFontNormal);
	}
}

void CElemental::gInfoBoxColor(float PosX, float PosY, float Width, float Height, DWORD bkcolor, float Arg5, int Arg6)
{
	float Red = (float)((bkcolor & 0xff000000) >> 24) / 255.0f;
	float Green = (float)((bkcolor & 0x00ff0000) >> 16) / 255.0f;
	float Blue = (float)((bkcolor & 0x0000ff00) >> 8) / 255.0f;
	float Alpha = (float)(bkcolor & 0x000000ff) / 255.0f;
	pSetBlend(1);
	if (bkcolor)
	{
		glColor4f(Red, Green, Blue, Alpha);
		pDrawBarForm(PosX, PosY, Width + 6.5, Height + 5, Arg5, Arg6); //central
	}
	pGLSwitch();
	pSetBlend(0);
	EnableAlphaTest(0);
}

void CElemental::gItemBoxInv(int X, int Y, int Doc, int Ngang, int Use)
{
	float v6;
	float v7;
	GLfloat red;
	GLfloat green;
	int j;
	int i;

	for (i = 0; i < Doc; ++i)
	{
		for (j = 0; j < Ngang; ++j)
		{
			pSetBlend(1);
			if (Use)
			{
				glColor4f(0.30000001, 0.5, 0.5, 0.60000002);
			}
			else
			{
				glColor4f(0.3, 0.3, 0.3, 0.60000002);
			}
			v7 = (float)(Y + 20 * i);
			v6 = (float)(X + 20 * j);
			pDrawBarForm(LODWORD(v6), LODWORD(v7), 20.0, 20.0, 0.0, 0);
			pSetBlend(true);
			glColor3f(1.0, 1.0, 1.0);
			green = (float)(Y + 20 * i);
			red = (float)(X + 20 * j);
			pDrawGUI(31339, LODWORD(red), LODWORD(green), 21.0, 21.0);
			pGLSwitch();
			EnableAlphaTest(0);
		}
	}
}