#pragma once

#define pSetTextSize				((int(__thiscall*)(LPVOID This, HFONT a2)) 0x420120)
#define pSetBackgroundTextColor		((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x004200B0)

struct eColor {
	BYTE red;
	BYTE grn;
	BYTE blu;
	BYTE opl;
};

class eCustomFont
{
public:
	eCustomFont();
	~eCustomFont();
	void load();
	void Draw(HFONT font, int PosX, int PosY, DWORD color, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	void DrawMultipleColor(HFONT font, int PosX, int PosY, DWORD bkcolor, int Width, int Height, BYTE Align, LPCTSTR Text, ...);
	eColor	SinWaveColor(float frc1, float frc2, float frc3, BYTE phs1, BYTE phs2, BYTE phs3, BYTE center, BYTE width, BYTE step);

	HFONT	FontNormal;
	HFONT	FontBold;
	HFONT	FontSize15;
	HFONT	FontSize18;
	HFONT	FontSize19;
	HFONT	FontSize20;
	HFONT	FontSize25;
	HFONT	FontSize30;
};

extern eCustomFont CustomFont;
char* BNumberFormat(int Number);