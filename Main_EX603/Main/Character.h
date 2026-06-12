#pragma once
#include "stdafx.h"
#define TextureEnable						*(BYTE*)0x08793260
#define DepthTestEnable						*(BYTE*)0x0879325F
#define CullFaceEnable						*(BYTE*)0x0879325E
#define DepthMaskEnable						*(BYTE*)0x0879325D
#define pIsButtonPressed		((int(__cdecl*)(int ButtonNumber)) 0x791070)
#define pIsKeyNone				((bool(__cdecl*)(int)) 0x791030)
#define pIsKeyRelease			((bool(__cdecl*)(int)) 0x791050)
#define pIsKeyPress				((bool(__cdecl*)(int)) 0x791070)
#define pIsKeyRepeat			((bool(__cdecl*)(int)) 0x791090)
#define MouseLButton			*(bool*)0x8793386
#define _BYTE		BYTE
#define _WORD		WORD
#define _DWORD		DWORD

enum CustomObjectID //0-99
{
	oTestObject = 9999,
	oMonster1 = 9998,
	oMonster2 = 9997,
	oMonster3 = 9996,
	oMonster4 = 9995,
	oMonster5 = 9994,
	oMonster6 = 9993,
	oMonster7 = 9992,
	oMonster8 = 9991,
	oMonster9 = 9990,
	oMonster10 = 9989,
	oHero1 = 9987,
	oHero2 = 9986,
	oHero3 = 9985,
	oHero4 = 9984,
	oHero5 = 9983,
	oHero6 = 9982,
	oHero7 = 9981,
	oHero8 = 9980,
	oHero9 = 9979,
	oMonster11 = 9978,
	oMonster12 = 9977,
	oMonster13 = 9976,
	oMonster14 = 9975,
	oMonster15 = 9974,
	oMonster16 = 9973,
	oMonster17 = 9972,
	oMonster18 = 9971,
	oMonster19 = 9970,
	oMonster20 = 9969,
	oViewCharItems = 9968,
};

class cCharacter
{
public:
	cCharacter();
	~cCharacter();
	void Init();
	void cCharacter::ClearPetCache(int Type);
	void DrawHero(float x, float y, float w, float h, int Id);
	void DrawHero(float x, float y, float w, float h);
	void DrawClone(float x, float y, float w, float h);
	int  CreateHero(int Index, short Class, bool clearItems = false);
	void CharSetSlotItem(int C, int Slot, int Id, int Level, int Ex, int Ancient);
	void SetZoom(float zoom = 1.f) { this->rot[2] = zoom; }
	void Zoom(MOUSEHOOKSTRUCTEX* Mouse, WPARAM wParam);
	void SetZoom(float min, float max, float speed, float defaultZoom) { this->LimitZoom[0] = min; this->LimitZoom[1] = max; this->LimitZoom[2] = speed; this->LimitZoom[3] = defaultZoom; this->rot[2] = defaultZoom; }
	bool Rotate(float x, float y, float w, float h, float* rot, float speed, float defaultRot = 90.f);
	void Draw(int c, float x, float y, float w, float h, float rot = 90.f, float zoom = 1.f);
	void Draw2(int c, float x, float y, float w, float h, float rot = 90.f, float zoom = 1.f);
	void SetChangeSkin(int Skin);
	void DrawMonster(float x, float y, float w, float h, int IndexModel, int Class, float Size =1.f);
	int CreateMonster(int Index, short Class);
	void cCharacter::BDrawHeroTop(float x, float y, float w, float h, int Id, float Scale, int Class);
	void ViewItems(float x, float y, float w, float h, int Class);
	void cCharacter::UpdateItemChar(int Id, int Slot, int IndexItem, int Level, int Ex, int Ancient);
	int Key;
	float Rot;
	
private:
	bool Rotating;
	bool Zoomming;
	float LimitZoom[4];
	float rot[3];
};

extern cCharacter character;