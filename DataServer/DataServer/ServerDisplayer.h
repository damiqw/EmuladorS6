// ServerDisplayer.h: interface for the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define MAX_LOG_TEXT_LINE 29
#define MAX_LOG_TEXT_SIZE 150
#define XMTEAM_vRed			RGB(139, 000, 000) // Đỏ Huyết
#define XMTEAM_vWhite		RGB(255, 255, 255) // Trắng
#define XMTEAM_vBlue		RGB(000, 000, 255) // Xanh Dương
#define XMTEAM_vGreen		RGB(000, 255, 000) // Xanh Lá Sáng
#define XMTEAM_vDarkGreen	RGB(000, 100, 000) // Xanh Lá Tối
#define XMTEAM_vSilver		RGB(120, 120, 120) // Màu Bạc
#define XMTEAM_vBlack		RGB(000, 000, 000) // Màu Đen
#define XMTEAM_vPink		RGB(224, 224, 224) // Màu Hồng


enum eLogColor
{
	LOG_BLACK = 0,
	LOG_RED = 1,
	LOG_GREEN = 2,
	LOG_BLUE = 3,
	LOG_DARKGREEN = 4,
};

struct LOG_DISPLAY_INFO
{
	char text[MAX_LOG_TEXT_SIZE];
	eLogColor color;
};

class CServerDisplayer
{
public:
	CServerDisplayer();
	virtual ~CServerDisplayer();
	void Init(HWND hWnd);
	void Run();
	void SetWindowName();
	void PaintBarInfo();
	void PaintName();
	void PaintUpdate();
	void PaintAllInfo();
	void LogTextPaint();
	void LogAddText(eLogColor color,char* text,int size);
private:
	HWND m_hwnd;
	HFONT m_font;
	HFONT m_font2;
	HFONT m_font3;
	HFONT m_font4;
	HBRUSH m_brush[5];
	HFONT XMTEAM_gFont3;
	LOG_DISPLAY_INFO m_log[MAX_LOG_TEXT_LINE];
	int m_count;
	char m_DisplayerText[2][64];
};

extern CServerDisplayer gServerDisplayer;
