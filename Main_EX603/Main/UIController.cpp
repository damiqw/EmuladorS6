#include "stdafx.h"
#include "UIController.h"
#include "Interface.h"

cUIController UIController;

cUIController::cUIController()
{
}

cUIController::~cUIController()
{
}

float cUIController::nearly(float a1)
{
	int step = 0;
	do {
		float cur = (float)pow(2.0, step++);
		if (a1 <= cur)
			return cur;
	} while (true);
}


void cUIController::Button(int IMGcode, float x, float y, float w, float h, float a6, float a7, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc) {
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7 * 2.0, w / a6, h / a7, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7, w / a6, h / a7, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, w / a6, h / a7, 1, 1, 0.0);
	}
	return;
}
void cUIController::Button(int IMGcode, float x, float y, float w, float h, float a6, float a7, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, float uw, float uh) {
	if (gInterface.IsWorkZone4(x, y, uw, uh)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, uw, uh, 0.0, h / a7 * 2.0, w / a6, h / a7, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, uw, uh, 0.0, h / a7, w / a6, h / a7, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else {
		RenderBitmap(IMGcode, x, y, uw, uh, 0.0, 0.0, w / a6, h / a7, 1, 1, 0.0);
	}
	return;
}
void cUIController::Button(int IMGcode, float x, float y, float w, float h, float uw, float uh, float a8, float a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, bool a11) {
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / a9, uw / a8, uh / a9, 1, 1, 0.0);
		if (pIsKeyRelease(VK_LBUTTON) || (a11 && GetKeyState(VK_LBUTTON) & 0x8000))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / a8, uh / a9, 1, 1, 0.0);
	}
	return;
}

int cUIController::Button(int IMGcode, float x, float y, float w, float h, float uw, float uh, int a8, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	float _w = this->nearly(uw),
		_uh = uh * (float)a8,
		_h = this->nearly(_uh);
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * 2.0, uw / _w, uh / _h, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * 1.0, uw / _w, uh / _h, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return 2;
		}
		return 1;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, uw / _w, uh / _h, 1, 1, 0.0);
	}
	return 0;
}

void cUIController::Button(int IMGcode, float x, float y, float w, float h, float uw, float uh, int a8, const BYTE *a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	float _w = this->nearly(uw),
		_uh = uh * (float)a8,
		_h = this->nearly(_uh);
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[2], uw / _w, uh / _h, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[1], uw / _w, uh / _h, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[0], uw / _w, uh / _h, 1, 1, 0.0);
	}
	return;
}

DWORD CacheKeyClick = 0;
bool cUIController::BButton(int IMGcode, float x, float y, float w, float h, float uw, float uh, int a8, const BYTE* a9)
{
	float _w = this->nearly(uw),
		_uh = uh * (float)a8,
		_h = this->nearly(_uh);
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[2], uw / _w, uh / _h, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[1], uw / _w, uh / _h, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON) && GetTickCount()>CacheKeyClick+300)
		{
			CacheKeyClick = GetTickCount();
			return 1;
		}
		return 0;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[0], uw / _w, uh / _h, 1, 1, 0.0);
	}
	return 0;
}
void cUIController::Button(int IMGcode, float x, float y, float w, float h, float uw, float uh, int a8, const BYTE *a9, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc, int pCallbackValue)
{
	float _w = this->nearly(uw),
		_uh = uh * (float)a8,
		_h = this->nearly(_uh);
	if (gInterface.IsWorkZone4(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[2], uw / _w, uh / _h, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[1], uw / _w, uh / _h, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			this->CallBackValue = pCallbackValue;
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[0], uw / _w, uh / _h, 1, 1, 0.0);
	}
	return;
}

bool cUIController::Button(int IMGcode, float x, float y, float w, float h, float uw, float uh, int a8, const BYTE* a9)
{
	float _w = this->nearly(uw),
		_uh = uh * (float)a8,
		_h = this->nearly(_uh);
	if (gInterface.IsWorkZone(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[2], uw / _w, uh / _h, 1, 1, 0.0);
		}
		else {
			RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[1], uw / _w, uh / _h, 1, 1, 0.0);
		}
		return true;
	}
	else {
		RenderBitmap(IMGcode, x, y, w, h, 0.0, uh / _h * (float)a9[0], uw / _w, uh / _h, 1, 1, 0.0);
	}
	return false;
}

bool cUIController::Button(int IMGcode, float x, float y, float w, float h, const int* a6)
{
	if (gInterface.IsWorkZone(x, y, w, h)) {
		if (GetKeyState(VK_LBUTTON) & 0x8000) {
			pDrawColorButton(IMGcode, x, y, w, h, 0, 0, a6[2]);
		}
		else {
			pDrawColorButton(IMGcode, x, y, w, h, 0, 0, a6[1]);
		}
		return true;
	}
	else {
		pDrawColorButton(IMGcode, x, y, w, h, 0, 0, a6[0]);
	}
	return false;
}

int cUIController::GetCallBackValue()
{
	return this->CallBackValue;
}