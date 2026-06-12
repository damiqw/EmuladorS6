// ServerDisplayer.cpp: implementation of the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerDisplayer.h"
#include "ClientManager.h"
#include "Log.h"
#include "Resource.h"
#include "SocketManager.h"
#include "Util.h"

CServerDisplayer gServerDisplayer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerDisplayer::CServerDisplayer() // OK
{
	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		memset(&this->m_log[n],0,sizeof(this->m_log[n]));
	}

	this->m_font = CreateFont(50,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font2 = CreateFont(24,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	this->m_font3 = CreateFont(15,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"MS Sans Serif");
	this->m_font4 = CreateFont(20,0,0,0,FW_THIN,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_DONTCARE,"Times");
	
	this->m_brush[0] = CreateSolidBrush(RGB(100, 100, 255));		
	this->m_brush[1] = CreateSolidBrush(RGB(120, 120, 120));	
	this->m_brush[2] = CreateSolidBrush(RGB(49, 54, 56));	
	this->m_brush[3] = CreateSolidBrush(RGB(0, 0, 0));
	this->m_brush[4] = CreateSolidBrush(RGB(49, 54, 56));

	strcpy_s(this->m_DisplayerText[0],"");
	strcpy_s(this->m_DisplayerText[1],"");
}

CServerDisplayer::~CServerDisplayer() // OK
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_font2);
	DeleteObject(this->m_font3);
	DeleteObject(this->m_font4);
	DeleteObject(this->m_brush[0]);
	DeleteObject(this->m_brush[1]);
	DeleteObject(this->m_brush[2]);
	DeleteObject(this->m_brush[3]);
	DeleteObject(this->m_brush[4]);
}

void CServerDisplayer::Init(HWND hWnd) // OK
{
	this->m_hwnd = hWnd;

	gLog.AddLog(1,"LOG");

	gLog.AddLog(1,"LOG\\HACK_LOG");
}

void CServerDisplayer::Run() // OK
{
	this->LogTextPaint();
	this->PaintBarInfo();
	this->SetWindowName();
	this->PaintName();
	this->PaintAllInfo();
	this->PaintUpdate();	
}

void CServerDisplayer::SetWindowName() // OK
{
	char buff[256];

	wsprintf(buff, "[%s] %s", HACKSERVER_VERSION, HACKSERVER_CLIENT);

	SetWindowText(this->m_hwnd,buff);

	RECT rect;

	GetClientRect(this->m_hwnd,&rect);
}

void CServerDisplayer::PaintBarInfo() // OK
{
	HWND hWndStatusBar = GetDlgItem(this->m_hwnd,IDC_STATUSBAR);

	char buff[256];

	wsprintf(buff,"UserCount: %d/%d",GetUserCount(),MAX_CLIENT);
	SendMessage(hWndStatusBar,SB_SETTEXT,0,(LPARAM)buff);

	wsprintf(buff,"QueueSize: %d/%d",gSocketManager.GetQueueSize(),MAX_MAIN_PACKET_SIZE);
	SendMessage(hWndStatusBar,SB_SETTEXT,1,(LPARAM)buff);

	SendMessage(hWndStatusBar,SB_SETTEXT,2,0);

	ShowWindow(hWndStatusBar,SW_MAXIMIZE);

	ShowWindow(hWndStatusBar,SW_RESTORE);
}

void CServerDisplayer::PaintAllInfo() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	long Medida = rect.right - 0;

	Medida = Medida / 2;

	rect.right = rect.right - 0 - Medida;
	//--
	rect.top = rect.top + 60;

	rect.bottom = rect.top + 25;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font4);

	int state = 0;

	for (int n = 0; n < MAX_CLIENT; n++)
	{
		if (gClientManager[n].CheckState() == 0)
		{
			continue;
		}

		if ((GetTickCount() - gClientManager[n].m_PacketTime) <= 60000)
		{
			state = 1;
			break;
		}
	}

	if (state == 0)
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[1]);
		TextOut(hdc,115,50,this->m_DisplayerText[0],strlen(this->m_DisplayerText[0]));
		DrawText(hdc, "STANDBY MODE", sizeof("STANDBY MODE"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		SetTextColor(hdc, RGB(250, 250, 250));
		FillRect(hdc, &rect, this->m_brush[0]);
		TextOut(hdc,115,50,this->m_DisplayerText[1],strlen(this->m_DisplayerText[1]));
		DrawText(hdc, "ACTIVE MODE", sizeof("ACTIVE MODE"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	SelectObject(hdc,OldFont);
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::PaintName() // OK nombre
{
	RECT rect;
	GetClientRect(this->m_hwnd,&rect);

	rect.top = 0;

	rect.bottom = 60;

	rect.right= rect.right - 0;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font);

	SetTextColor(hdc,RGB(250, 250, 250));

	FillRect(hdc,&rect,this->m_brush[2]);

	DrawText(hdc, HACKSERVER_CLIENT, sizeof(HACKSERVER_CLIENT), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc,OldFont);

	SetBkMode(hdc,OldBkMode);
	
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::PaintUpdate() // OK Season6
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	long Medida = rect.right - 0;

	Medida = Medida / 2;

	rect.right = rect.right - 0;

	rect.left = Medida + 2;
	//--
	rect.top = rect.top + 60;

	rect.bottom = rect.top + 25;

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc, TRANSPARENT);

	HFONT OldFont = (HFONT) SelectObject(hdc, this->m_font4);

	SetTextColor(hdc, RGB(250, 250, 250));
	
	FillRect(hdc, &rect, this->m_brush[0]);

	DrawText(hdc, UPDATE_NAME, sizeof(UPDATE_NAME), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(hdc, OldFont);
	SetBkMode(hdc, OldBkMode);
	ReleaseDC(this->m_hwnd, hdc);
}

void CServerDisplayer::LogTextPaint() // OK
{
	RECT rect;

	GetClientRect(this->m_hwnd,&rect);

	HDC hdc = GetDC(this->m_hwnd);

	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	FillRect(hdc,&rect,this->m_brush[3]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font3);

	int line = MAX_LOG_TEXT_LINE;

	int count = (((this->m_count-1)>=0)?(this->m_count-1):(MAX_LOG_TEXT_LINE-1));

	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		switch(this->m_log[count].color)
		{
			case LOG_BLACK:
				SetTextColor(hdc,RGB(255,255,255));
				break;
			case LOG_RED:
				SetTextColor(hdc,RGB(239,0,0));
				break;
			case LOG_GREEN:
				SetTextColor(hdc,RGB(0,255,0));
				break;
			case LOG_BLUE:
				SetTextColor(hdc,RGB(0, 152, 239));
				break;
		}

		int size = strlen(this->m_log[count].text);

		if(size > 1)
		{
			TextOut(hdc,0,(65+(line*15)),this->m_log[count].text,size);
			line--;
		}

		count = (((--count)>=0)?count:(MAX_LOG_TEXT_LINE-1));
	}

	SelectObject(hdc,OldFont);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogAddText(eLogColor color,char* text,int size) // OK
{
	size = ((size>=MAX_LOG_TEXT_SIZE)?(MAX_LOG_TEXT_SIZE-1):size);

	memset(&this->m_log[this->m_count].text,0,sizeof(this->m_log[this->m_count].text));

	memcpy(&this->m_log[this->m_count].text,text,size);

	this->m_log[this->m_count].color = color;

	this->m_count = (((++this->m_count)>=MAX_LOG_TEXT_LINE)?0:this->m_count);

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}
