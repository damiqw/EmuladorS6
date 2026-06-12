#include "stdafx.h"
#include "LoginBox.h"
#include "Import.h"
#include "CustomFont.h"
#include "Util.h"
#include "Protect.h"
#include "Defines2.h"
#include "SEASON3B.h"
#include "Interface.h"

cAutoLogin AutoLogin;

cAutoLogin::cAutoLogin()
{
	this->showListAccount = false;
	this->selectedAccount = 0;
	this->totalSavedAcc = 0;
	this->TickCount = 0;
}

cAutoLogin::~cAutoLogin()
{
}

float getX(float x) 
{
	return x / g_fScreenRate_x;
}
float getY(float y) 
{
	return y / g_fScreenRate_x;
}

bool IsCursorInZone(short x, short y, short x2, short y2)
{
	return pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
}

BYTE DrawCButton(int IMGcode, float x, float y, float w, float h, float a6 = 64.0, float a7 = 128.0, int delay = 150, bool a9 = false)
{

	if (IsCursorInZone(x, y, getX(w), getY(h))) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7 * 2.0, w / a6, h / a7, 0, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7, w / a6, h / a7, 0, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON) && AutoLogin.lastClick + delay <= GetTickCount())
		{
			AutoLogin.lastClick = GetTickCount();
			return 2;
		}
		return 1;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, w / a6, h / a7, 0, 1, 0.0);
	}
	return 0;
}

bool WriteString(const std::string& name, const std::string& value) {
	HKEY	hKey = NULL;
	DWORD	dwDisp;
	DWORD	dwSize = value.size();

	if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
		return false;

	RegSetValueEx(hKey, name.c_str(), 0L, REG_SZ, (CONST BYTE*)value.c_str(), dwSize);
	RegCloseKey(hKey);
	return true;
}

bool WriteDword(const std::string& name, DWORD value) {
	HKEY	hKey = NULL;
	DWORD	dwDisp;
	DWORD	dwSize = sizeof(DWORD);

	if (ERROR_SUCCESS != RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
		return false;

	RegSetValueEx(hKey, name.c_str(), 0L, REG_DWORD, (BYTE*)&value, dwSize);
	RegCloseKey(hKey);
	return true;
}

void cAutoLogin::SaveAccount(char* ID, char* PW, bool Save)
{
	char zKey[50];
	int i;
	if (AutoLogin.totalSavedAcc > 0) {
		//clear all for sure, infact we can clear the rest for performance
		for (i = 1; i < MAX_ACCOUNT_SAVE; i++) {
			sprintf(zKey, "ID_%d", i + 1);
			WriteString(zKey, "");
			sprintf(zKey, "PW_%d", i + 1);
			WriteString(zKey, "");
		}
		//save new data
		int successCount = 1;
		for (i = 0; i < AutoLogin.totalSavedAcc; i++) {
			if (successCount >= MAX_ACCOUNT_SAVE) {
				break;
			}
			if (strcmp(ID, AutoLogin.saved_acc[i].ID) == 0) { //duplicate account
				continue;
			}
			sprintf(zKey, "ID_%d", successCount + 1);
			WriteString(zKey, AutoLogin.saved_acc[i].ID);
			sprintf(zKey, "PW_%d", successCount + 1);
			WriteString(zKey, AutoLogin.saved_acc[i].PW);
			successCount++;
		}
	}
	WriteString("ID", ID);
	WriteString("PW", PW);
	WriteDword("SavePass", Save ? 1 : 0);
}
void cAutoLogin::DoRequestLogin()
{
	int Struct = _Instance() + 16968;

	InputBox_GetText(*(DWORD*)(Struct + 848), AutoLogin.iUser, 11);
	InputBox_GetText(*(DWORD*)(Struct + 852), AutoLogin.iPassword, 11);
	if (AutoLogin.savePass) {
		AutoLogin.SaveAccount(AutoLogin.iUser, AutoLogin.iPassword, 1);
		AutoLogin.ReadConfigs();
	}
	else {
		WriteDword("SavePass", 0);
	}
	//do it
	RequestLogin(_Instance() + 16968);
}
void cAutoLogin::TongleAccount(LPVOID pClass)
{
	AutoLogin.SetShowListAccount(!AutoLogin.GetShowListAccount());
}
void cAutoLogin::RemoveAccount(LPVOID pClass)
{
	if (AutoLogin.selectedAccount < 0 && AutoLogin.selectedAccount >= AutoLogin.totalSavedAcc)
	{
		return;
	}

	if (AutoLogin.selectedAccount == 0) {
		WriteString("ID", "");
		WriteString("PW", "");
	}
	else {
		char zKey[50];

		sprintf(zKey, "ID_%d", AutoLogin.selectedAccount + 1);
		WriteString(zKey, "");
		sprintf(zKey, "PW_%d", AutoLogin.selectedAccount + 1);
		WriteString(zKey, "");
	}
	AutoLogin.ReadConfigs();
}

int cAutoLogin::GetSelectedAccount()
{
	return this->selectedAccount;
}
bool cAutoLogin::GetShowListAccount(bool checkTick)
{
	return this->showListAccount || (checkTick && this->TickCount + 250 >= GetTickCount());
}
void cAutoLogin::SetShowListAccount(bool show)
{
	this->showListAccount = show;
}

void cAutoLogin::SetTickCount(DWORD tick)
{
	this->TickCount = tick;
}

inline int GetPosLogin()
{
	int Ret = 0;
	switch (pGameResolutionMode)
	{
	case 0: Ret = 30.f; break;
	case 1: Ret = 25.f; break;
	case 2: Ret = 35.f; break;
	case 3: Ret = 35.f; break;
	case 4: Ret = 27.f; break;
	case 5: Ret = 40.f; break;
	case 6: Ret = 25.f; break;
	case 7: Ret = 18.f; break;
	case 8: Ret = 12.f; break;
	}
	return Ret;
}

inline int GetPosShowLogin()
{
	int Ret = 0;
	switch (pGameResolutionMode)
	{
	case 0: Ret = 07.f; break;  //640x480
	case 1: Ret = 07.f; break;  //800x600
	case 2: Ret = 17.f; break;  //1024x768
	case 3: Ret = 17.f; break;  //1280x1024
	case 4: Ret = 10.f; break;  //1366x768
	case 5: Ret = 20.f; break;  //1440x900
	case 6: Ret = 06.f; break;  //1600x900
	case 7: Ret = 02.f; break;  //1680x1050
	case 8: Ret = -03.f; break; //1920x1080
	}
	return Ret;
}

void CButtonAutoLogin(int This, int a2)
{
	CUIRenderText_SetFont((int)pTextThis(), *(int*)0xE8C594);

	float startX;
	float startY;

	int JCResto = (pWinWidth / pWinHeightReal / 2) - 320;

	startX = JCResto + (640.0 - getX(329)) / 2;

	if (pGameResolutionMode == 0)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(245)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 1)
	{
		startY = Fix_DisplayHeightExt + (480.0 - getY(320)) * 2.0 / 3.0; //para la resolucion 820, save login
	}
	else if (pGameResolutionMode == 2)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(325)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 3)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(325)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 4)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 5)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(375)) * 2.0 / 3.0; //1440
	}
	else if (pGameResolutionMode == 6)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 7)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(375)) * 2.0 / 3.0;
	}
	else if (pGameResolutionMode == 8)
	{
		startY = Fix_DisplayHeightExt + (470.0 - getY(375)) * 2.0 / 3.0;
	}

	int Struct = _Instance() + 16968;

	if (!AutoLogin.GetShowListAccount(false))
	{
		if (IsCursorInZone(startX + getX(250.0), startY + getY(135) + GetPosLogin(), getX(15), getY(15)))
		{
			if (pIsKeyRelease(VK_LBUTTON))
			{
				RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(135) + GetPosLogin(), 15.0, 15.0, 0.0, 0.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
				AutoLogin.savePass = !AutoLogin.savePass;
				PlayBuffer(25, 0, 0);
			}
		}
		if (!AutoLogin.savePass)
		{
			RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(135) + GetPosLogin(), 15.0, 15.0, 0.0, 15.0 / 32.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
		}
		else
		{
			RenderBitmap(0x7B69, startX + getX(250.0), startY + getY(135) + GetPosLogin(), 15.0, 15.0, 0.0, 0.0, 15.0 / 16.0, 15.0 / 32.0, 0, 1, 0.0);
		}
	}

	AutoLogin.DrawButton(0x7ABE, startX + getX(245.0), startY + getY(108) + GetPosShowLogin(), 17.0, 17.0, 15.0, 13.0, 16.0, 64.0, cAutoLogin::TongleAccount);
	
	CustomFont.Draw((HFONT)pFontNormal, startX + getX(110), (startY + getY(138) + GetPosLogin()) - 2, 0xffffffD1, 0x0, getX(138), 0, 4, GlobalText(GlobalLine, 3842)); //Save Account/Password

	if (AutoLogin.GetShowListAccount(false))
	{
		int i;
		glAlphaFunc(GL_GREATER, 0.0f);
		EnableAlphaTest(true);
		glColor4f(1.f, 1.f, 1.f, 1.f);

		RenderBitmap(31322, startX + getX(109), startY + getY(128) + GetPosShowLogin(), 155.0, 102.0, 0.0, 36.0 / 256.0, 112.0 / 128.0, 144.0 / 256.0, 0, 1, 0.0);
		for (i = 1; i < 5; i++)
		{
			RenderBitmap(31582, startX + getX(109), startY + getY(128 + 20 * i) + GetPosShowLogin(), 155.0, 2.0, 0.0, 0.0, 82.0 / 128.0, 2.0 / 2.0, 0, 1, 0.0);
		}
		for (i = 0; i < AutoLogin.totalSavedAcc; i++)
		{
			if (IsCursorInZone(startX + getX(115), startY + getY(131 + 20 * i) + GetPosShowLogin(), getX(150), getY(20)))
			{
				AutoLogin.SetSelectedAccount(i);
				CustomFont.Draw((HFONT)pFontNormal, startX + getX(115), startY + getY(131 + 20 * i) + GetPosShowLogin(), 0x0, 0x00000080, getX(150), getY(20), 0, " ");
				AutoLogin.DrawButton(0x7B42, startX + getX(235.0), startY + getY(132.5 + 20 * i) + GetPosShowLogin(), 15.0, 15.0, 11.0, 11.0, 16.0, 32.0, cAutoLogin::RemoveAccount, false);
				if (pIsKeyRelease(VK_LBUTTON) && IsCursorInZone(startX + getX(115), startY + getY(131 + 20 * i) + GetPosShowLogin(), getX(120), getY(20)))
				{
					AutoLogin.Login(i, false);
					AutoLogin.SetShowListAccount(false);
					AutoLogin.SetTickCount(GetTickCount() + 900);
				}
			}
			CustomFont.Draw((HFONT)pFontNormal, startX + getX(115 + 30), startY + getY(135 + 20 * i) + GetPosShowLogin(), 0xffffffD1, 0x0, getX(90), getY(18), 3, AutoLogin.saved_acc[i].ID);
		}

		RenderBitmap(31580, startX + getX(109), startY + getY(128) + GetPosShowLogin(), 155.0, 20.0, 0.0, 0.0, 112.0 / 128.0, 44.0 / 64.0, 0, 1, 0.0);
		for (i = 0; i < 8; i++)
		{
			RenderBitmap(31580, startX + getX(109), startY + getY(148 + 9.0 * i) + GetPosShowLogin(), 155.0, 10.0, 0.0, 0.0, 112.0 / 128.0, 14.5 / 16.0, 0, 1, 0.0);
		}
		RenderBitmap(31581, startX + getX(109), startY + getY(212.5) + GetPosShowLogin(), 155.0, 20.0, 0.0, 0.0, 112.0 / 128.0, 44.0 / 64.0, 0, 1, 0.0);
	}
}

void DoLoginWinCreate(int)
{
	int Struct = _Instance() + 16968;
	LoginWinCreate(Struct);
	AutoLogin.ReadConfigs();
	if (AutoLogin.savePass) {
		InputBox_SetText(*(DWORD*)(Struct + 848), AutoLogin.saved_acc[0].ID);
		InputBox_SetText(*(DWORD*)(Struct + 852), AutoLogin.saved_acc[0].PW);
	}
	else {
		InputBox_SetText(*(DWORD*)(Struct + 848), AutoLogin.saved_acc[0].ID);
		InputBox_SetText(*(DWORD*)(Struct + 852), "");
	}
	AutoLogin.SetShowListAccount(false);
	AutoLogin.SetSelectedAccount(0);
}

void cAutoLogin::Login(char* id, char* pw, bool pressOK)
{
	int Struct = _Instance() + 16968;
	InputBox_SetText(*(DWORD*)(Struct + 848), id);
	InputBox_SetText(*(DWORD*)(Struct + 852), pw);
	if (pressOK) {
		DoRequestLogin();
	}
}

void cAutoLogin::Login(int acc, bool pressOK)
{
	if (acc < 0 && acc >= AutoLogin.totalSavedAcc)
	{
		return;
	}
	int Struct = _Instance() + 16968;
	InputBox_SetText(*(DWORD*)(Struct + 848), AutoLogin.saved_acc[acc].ID);
	InputBox_SetText(*(DWORD*)(Struct + 852), AutoLogin.saved_acc[acc].PW);
	if (pressOK) {
		DoRequestLogin();
	}
}

void cAutoLogin::ReadConfigs()
{
	HKEY hKey;
	DWORD dwDisp;
	DWORD dwSize;
	if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, "SOFTWARE\\Webzen\\Mu\\Config", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisp))
	{
		//==============
		AutoLogin.totalSavedAcc = 0;
		char zKey[50];
		for (int i = 0; i < MAX_ACCOUNT_SAVE; i++) {
			if (i) {
				sprintf(zKey, "ID_%d", i + 1);
			}
			else {
				sprintf(zKey, "ID");
			}
			dwSize = 11;
			if (RegQueryValueEx(hKey, zKey, 0, NULL, (LPBYTE)AutoLogin.saved_acc[AutoLogin.totalSavedAcc].ID, &dwSize) != ERROR_SUCCESS ||
				dwSize < 1)
			{
				ZeroMemory(AutoLogin.saved_acc[AutoLogin.totalSavedAcc].ID, sizeof(AutoLogin.saved_acc[AutoLogin.totalSavedAcc].ID));
				continue;
			}
			if (i) {
				sprintf(zKey, "PW_%d", i + 1);
			}
			else {
				sprintf(zKey, "PW");
			}
			dwSize = 11;
			if (RegQueryValueEx(hKey, zKey, 0, NULL, (LPBYTE)AutoLogin.saved_acc[AutoLogin.totalSavedAcc].PW, &dwSize) != ERROR_SUCCESS ||
				dwSize < 1)
			{
				ZeroMemory(AutoLogin.saved_acc[AutoLogin.totalSavedAcc].PW, sizeof(AutoLogin.saved_acc[AutoLogin.totalSavedAcc].PW));
				continue;
			}
			AutoLogin.saved_acc[AutoLogin.totalSavedAcc].index = i;
			AutoLogin.totalSavedAcc++;
		}
		dwSize = sizeof(int);
		if (RegQueryValueEx(hKey, "SavePass", 0, NULL, (LPBYTE)&AutoLogin.savePass, &dwSize) != ERROR_SUCCESS)
		{
			AutoLogin.savePass = false;
		}
	}

	AutoLogin.savePass = true;
}
void cAutoLogin::Load()
{
	this->lastClick = 0;
	//read data
	this->ReadConfigs();

	//end

	SetCompleteHook(0xE8, 0x0040B5A9, &CButtonAutoLogin); // o day
	SetCompleteHook(0xE8, 0x0040B400, &DoRequestLogin);
	SetCompleteHook(0xE8, 0x0040B44F, &DoRequestLogin);
	SetCompleteHook(0xE8, 0x00483711, &DoLoginWinCreate);
}

void cAutoLogin::DrawButton(int IMGcode, float x, float y, float w, float h, float uw, float uh, float a8, float a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	if (IsCursorInZone(x, y, getX(w), getY(h)))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9 * 2.0, uw / a8, uh / a9, 0, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9, uw / a8, uh / a9, 0, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / a8, uh / a9, 0, 1, 0.0);
	}
	return;
}

void cAutoLogin::DrawButton(int IMGcode, float x, float y, float w, float h, float uw, float uh, float a8, float a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, bool a11) 
{
	if (IsCursorInZone(x, y, getX(w), getY(h))) 
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9, uw / a8, uh / a9, 0, 1, 0.0);
		if (pIsKeyRelease(VK_LBUTTON) || (a11 && GetKeyState(VK_LBUTTON) & 0x8000))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else 
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / a8, uh / a9, 0, 1, 0.0);
	}
	return;
}