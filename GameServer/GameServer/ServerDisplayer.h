// ServerDisplayer.h: interface for the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#define GlobalFont "Arial"
#define MAX_LOG_TEXT_LINE 41
#define MAX_LOG_TEXT_SIZE 100

#define MAX_LOGCONNECT_TEXT_LINE 13
#define MAX_LOGCONNECT_TEXT_SIZE 55

#define MAX_LOGGLOBAL_TEXT_LINE 8
#define MAX_LOGGLOBAL_TEXT_SIZE 100

#define Spk_vRed		RGB(139, 000, 000) // 
#define Spk_vWhite		RGB(255, 255, 255) // 
#define Spk_vBlue		RGB(000, 000, 255) // 
#define Spk_vGreen		RGB(000, 255, 000) // 
#define Spk_vDarkGreen	RGB(000, 100, 000) // 
#define Spk_vSilver		RGB(120, 120, 120) // 
#define Spk_vBlack		RGB(000, 000, 000) // 
#define Spk_vPink		RGB(224, 224, 224) // 

enum eLogColor
{
	LOG_BLACK = 0,
	LOG_RED = 1,
	LOG_GREEN = 2,
	LOG_BLUE = 3,
	LOG_BOT = 4,
	LOG_USER = 5,
	LOG_EVENT = 6,
	LOG_ALERT = 7,
	LOG_DARKGREEN = 8,
};

struct LOG_DISPLAY_INFO
{
	char text[MAX_LOG_TEXT_SIZE];
	eLogColor color;
};

struct LOGCONNECT_DISPLAY_INFO
{
	char text[MAX_LOGCONNECT_TEXT_SIZE];
	eLogColor color;
};

struct LOGGLOBAL_DISPLAY_INFO
{
	char text[MAX_LOGGLOBAL_TEXT_SIZE];
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
	void PaintAllInfo();
	void LogTextPaint(); //este
	void LogTextPaintConnect();
	void LogTextPaintGlobalMessage();
	void CServerDisplayer::ShowEventDisplay(RECT rect, HDC hdc, LPCSTR StringName, int EventName, int X1, int X2, int Y);

	//void PaintName();
	void PaintEventTime();
	void PaintInvasionTime();
	void PaintCustomEventTime(); 
	void LogAddText(eLogColor color,char* text,int size);
	void LogAddTextConnect(eLogColor color,char* text,int size);
	void LogAddTextGlobal(eLogColor color,char* text,int size);
	void PaintOnline();
	void PaintUpdate();
	int EventBc;
	int EventDs;
	int EventCc;
	int EventIt;
	int EventCustomLottery;
	int EventCustomBonus;
	int EventCustomQuiz;
	int EventMoss;
	int EventDrop;
	int EventTvT;
	int EventGvG;
	int LukeHelper;
	int EventInvasion[30];
	int EventCustomArena[30];
	int EventCs;
	int EventCsState;
	int EventCastleDeep;
	int EventCryWolf;
	int EventCryWolfState;
private:
	HWND m_hwnd;
	HFONT m_font;
	HFONT m_font2;
	HFONT m_font3;
	HFONT m_font4;
	HFONT m_font5;
	HBRUSH m_brush[5];
	LOG_DISPLAY_INFO m_log[MAX_LOG_TEXT_LINE];
	LOGCONNECT_DISPLAY_INFO m_logConnect[MAX_LOGCONNECT_TEXT_LINE];
	LOGGLOBAL_DISPLAY_INFO m_logGlobal[MAX_LOGGLOBAL_TEXT_LINE];
	int m_count;
	int m_countConnect;
	int m_countGlobal;
};

extern CServerDisplayer gServerDisplayer;
