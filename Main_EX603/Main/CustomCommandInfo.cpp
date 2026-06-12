#include "StdAfx.h"
#include "CustomCommandInfo.h"
#include "Defines.h"
#include "Interface.h"
#include "User.h"
#include "Protect.h"
#include "WideScreen.h"
#include "InterfaceElemental.h"
#include "CNewUIWindowsClient.h"
// -------------------------------------------------------------------------------

CCustomCommandInfo gCustomCommandInfo;
// -------------------------------------------------------------------------------

CCustomCommandInfo::CCustomCommandInfo()
{
	this->Init();
}
// -------------------------------------------------------------------------------

CCustomCommandInfo::~CCustomCommandInfo()
{
	// ----
}
// -------------------------------------------------------------------------------

void CCustomCommandInfo::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_COMMAND;n++)
	{
		this->m_CustomCommandInfo[n].Index = -1;
	}
	this->Count = 0;
	this->Page = 0;
}

void CCustomCommandInfo::Load(CUSTOM_COMMAND_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_COMMAND;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomCommandInfo::SetInfo(CUSTOM_COMMAND_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_COMMAND)
	{
		return;
	}
	this->Count = info.Index+1;
	this->m_CustomCommandInfo[info.Index] = info;
}

CUSTOM_COMMAND_INFO* CCustomCommandInfo::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_COMMAND)
	{
		return 0;
	}

	if(this->m_CustomCommandInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomCommandInfo[index];
}

void CCustomCommandInfo::DrawCommandWindow()
{

	if (!gInterface.Data[eCommand_MAIN].OnShow)
	{
		return;
	}

	gInterface.CheckWindowSProTecno(2);

	pSetCursorFocus = true;

	float WindowW = 420;
	float WindowH = 300;
	float MainWidth = 230.0;
	float MainHeight = 180.0;
	float StartBody = 10.0;
	float StartY = 40;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	float InfoMocNapX = (StartX + 10) + 3;
	float InfoMocNapY = (StartY + 15);

	DWORD Color = eGray100;

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX, StartY - 4, 233, 275, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 12, StartY + 15, 210, 3, gCustomMessage.GetMessage(27));
		gInterface.DrawGUI(eCommand_CLOSE, StartX + 213, StartY + 13);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + 213, StartY + 14, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eCommand_CLOSE))
		{
			// ----
			if (gInterface.Data[eCommand_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eCommand_CLOSE, gInterface.Data[eCommand_CLOSE].X, gInterface.Data[eCommand_CLOSE].Y, Color);
			//gInterface.DrawToolTip(gInterface.Data[eWindowVongQuay_CLOSE].X + 5, gInterface.Data[eWindowVongQuay_CLOSE].Y + 25, "Close");
		}
	}
	else
	{
		RenderBitmap(61322, StartX + 1, StartY + 30, 225.0, 288.f, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX + 1, StartY - 5, 225.0, 42.f, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 10, StartY + 12, 210, 3, gCustomMessage.GetMessage(27));
		gInterface.DrawGUI(eCommand_CLOSE, StartX + 7 + MainWidth - gInterface.Data[eCommand_CLOSE].Width - 7.0, StartBody + 25);
		if (gInterface.IsWorkZone(eCommand_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eCommand_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eCommand_CLOSE, gInterface.Data[eCommand_CLOSE].X, gInterface.Data[eCommand_CLOSE].Y, Color);
		}
	}

	if ((this->Page == 0 && this->Count > 25) || (this->Page == 1 && this->Count > 50) || (this->Page == 2 && this->Count > 75))
	{
		gInterface.DrawGUI(eNextCommand, StartX + MainWidth - 8, 150);
	}
	else
	{
		gInterface.ResetDrawIMG(eNextCommand);
	}

	if (this->Page == 1 || this->Page == 2 || this->Page == 3)
	{
		gInterface.DrawGUI(ePrevCommand, StartX - 20, 150);
	}
	else
	{
		gInterface.ResetDrawIMG(ePrevCommand);
	}

	for (int i = (25 * Page) + 0; i < (25 * Page) + 25; i++)
	{
		if (this->m_CustomCommandInfo[i].Index == -1)
		{
			continue;
		}

		if (this->m_CustomCommandInfo[i].Color == 1)
		{
			Color = eGold;
		}
		else if (this->m_CustomCommandInfo[i].Color == 2)
		{
			Color = eWhite;
		}
		else if (this->m_CustomCommandInfo[i].Color == 3)
		{
			Color = eOrange;
		}
		else if (this->m_CustomCommandInfo[i].Color == 4)
		{
			Color = eRed2;
		}
		else if (this->m_CustomCommandInfo[i].Color == 5)
		{
			Color = eExcellent;
		}
		else if (this->m_CustomCommandInfo[i].Color == 6)
		{
			Color = eYellow;
		}
		else if (this->m_CustomCommandInfo[i].Color == 7)
		{
			Color = eSocket;
		}
		else
		{
			Color = eGold;
		}

		int x = i;

		if (this->Page > 0)
		{
			x = x - (25 * Page);
		}

		gInterface.DrawFormat(Color, (int)StartX + 18, (int)StartBody + 65 + (x * 10), 100, 1, this->m_CustomCommandInfo[i].Command);

		//gInterface.DrawFormat(Color, (int)StartX + 112, (int)StartBody + 35 + (i*10), 100, 1, this->m_CustomCommandInfo[i].Description);
		pDrawColorText(this->m_CustomCommandInfo[i].Description, (int)StartX + 112, (int)StartBody + 65 + (x * 10), 100, 0, Color, 0, 1);
	}
}

void CCustomCommandInfo::OpenCommandWindow()
{
	if (gInterface.Data[eCommand_MAIN].OnShow == true)
	{
		gInterface.Data[eCommand_MAIN].OnShow = false;
		pSetCursorFocus = false;
		return;
	}

	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[eCommand_MAIN].EventTick);

	if(Delay < 1500 )
	{
		gInterface.Data[eCommand_MAIN].OnShow = false;
		return;
	}

	gInterface.CloseCustomWindow();
	gInterface.Data[eCommand_MAIN].EventTick = GetTickCount();
	gInterface.Data[eCommand_MAIN].OnShow = true;
	pSetCursorFocus = true;

}

bool CCustomCommandInfo::EventCommandWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCommand_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eCommand_MAIN].OnShow || !gInterface.IsWorkZone(eCommand_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCommand_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCommand_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCommand_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eCommand_MAIN].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}

bool CCustomCommandInfo::CommandNext(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[eNextCommand].EventTick);
	DWORD Delay2		= (CurrentTick - gInterface.Data[ePrevCommand].EventTick);

	if( !gInterface.Data[eCommand_MAIN].OnShow )
	{
		return false;
	}
	
	if( !gInterface.IsWorkZone7(eNextCommand) )
	{
		return false;
	}

	if( Event == WM_LBUTTONDOWN )
	{
		gInterface.Data[eNextCommand].OnClick = true;
		return true;
	}

	if( Delay < 100 || Delay2 < 100 )
	{
		return false;
	}
	
	gInterface.Data[eNextCommand].OnClick = false;
	
	this->Page++;
	
	gInterface.Data[eNextCommand].EventTick = GetTickCount();
	

	return true;
}

bool CCustomCommandInfo::CommandPrev(DWORD Event)
{
	DWORD CurrentTick	= GetTickCount();
	DWORD Delay			= (CurrentTick - gInterface.Data[ePrevCommand].EventTick);
	DWORD Delay2		= (CurrentTick - gInterface.Data[eNextCommand].EventTick);

	if( !gInterface.Data[eCommand_MAIN].OnShow )
	{
		return false;
	}
	
	if( !gInterface.IsWorkZone7(ePrevCommand) )
	{
		return false;
	}

	if( Event == WM_LBUTTONDOWN )
	{
		gInterface.Data[ePrevCommand].OnClick = true;
		return true;
	}

	if( Delay < 100 || Delay2 < 100 )
	{
		return false;
	}
	
	gInterface.Data[ePrevCommand].OnClick = false;
	
	gInterface.Data[ePrevCommand].EventTick = GetTickCount();

	this->Page--;
	
	return true;
}


