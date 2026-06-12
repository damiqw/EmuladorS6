#include "stdafx.h"
#include "Font.h"
#include "Offset.h"
#include "Util.h"

int FontSize;

DWORD FontCharSet;

char FontName[100];

int ReadFontFile(char* path) // OK
{	
	FontSize = GetPrivateProfileInt("FontInfo","FontSize",13,path);
	
	FontCharSet = GetPrivateProfileInt("FontInfo","FontCharSet",1,path);
	
	GetPrivateProfileString("FontInfo","FontName","Tahoma",FontName,sizeof(FontName),path);

	return GetPrivateProfileInt("FontInfo","ChangeFontSwitch",0,path);
}

void InitFont() // OK
{
	if(ReadFontFile(".\\Settings.ini") != 0)
	{
		SetCompleteHook(0xE8,0x004D2882,&FontNormal);
		
		SetCompleteHook(0xE8,0x004D28EB,&FontBool);
		
		SetCompleteHook(0xE8,0x004D2957,&FontBig);
		
		SetCompleteHook(0xE8,0x004D29C1,&FontFixed);

		SetByte(0x004D2887,0x90);
		
		SetByte(0x004D28F0,0x90);
		
		SetByte(0x004D295C,0x90);
		
		SetByte(0x004D29C6,0x90);
	}
}

void ReloadFont() // OK
{
	*(HFONT*)0x00E8C588 = FontNormal();

	*(HFONT*)0x00E8C58C = FontBool();

	*(HFONT*)0x00E8C590 = FontBig();

	*(HFONT*)0x00E8C594 = FontFixed();

	*(DWORD*)MAIN_FONT_SIZE = FontSize;

	((void(*)())0x00630BC0)();
}

HFONT FontNormal() // OK
{
	return CreateFont(FontSize,0,0,0,FW_NORMAL,0,0,0,FontCharSet,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,FontName);
}

HFONT FontBool() // OK
{
	return CreateFont(FontSize,0,0,0,FW_BOLD,0,0,0,FontCharSet,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,FontName);
}

HFONT FontBig() // OK
{
	return CreateFont(FontSize*2,0,0,0,FW_BOLD,0,0,0,FontCharSet,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,FontName);
}

HFONT FontFixed() // OK
{
	return CreateFont(FontSize,0,0,0,FW_NORMAL,0,0,0,FontCharSet,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,NONANTIALIASED_QUALITY,DEFAULT_PITCH|FF_DONTCARE,FontName);
}