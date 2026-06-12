#include "StdAfx.h"
#include "Util.h"
#include "Import.h"
#include "Interface.h"
#include "ChatExpanded.h"
#include "User.h"
#include "CustomMessage.h"
#include "PrintPlayer.h"
#include "CustomQuickAddStats.h"
#include "Protect.h"
#include "InterfaceElemental.h"
#if(QuickAddStats)
QuickAddStats gQuickAddStats;
// -------------------------------------------------------------------------------

QuickAddStats::QuickAddStats()
{

}
// -------------------------------------------------------------------------------

QuickAddStats::~QuickAddStats()
{

}

DWORD CacheKeyClickStats = 0;

void QuickAddStats::Draw()
{
	if (!gInterface.CheckWindow(ObjWindow::Character))
	{
		return;
	}

	if (gInterface.m_QuickAdd == 1)
	{

	int JCResto; // eax@1
	int JCWinWidth; // eax@1
	JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
	JCResto = JCWinWidth / 2 - 320;

	float PosX1;
	float PosY1;
	float PosXT1;
	float PosX2;
	float PosY2;
	float PosXT2;
	float PosX3;
	float PosY3;
	float PosXT3;
	float PosX4;
	float PosY4;
	float PosXT4;
	float PosX5;
	float PosY5;
	float PosXT5;

	if (gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		PosX1 = 460 + Fix_DisplayWinExt + JCResto;
		PosY1 = 125;
		PosXT1 = 460 + Fix_DisplayWinExt + JCResto;
		
		PosX2 = 460 + Fix_DisplayWinExt + JCResto;
		PosY2 = 180;
		PosXT2 = 460 + Fix_DisplayWinExt + JCResto;

		PosX3 = 460 + Fix_DisplayWinExt + JCResto;
		PosY3 = 245;
		PosXT3 = 460 + Fix_DisplayWinExt + JCResto;

		PosX4 = 460 + Fix_DisplayWinExt + JCResto;
		PosY4 = 300;
		PosXT4 = 460 + Fix_DisplayWinExt + JCResto;

		PosX5 = 460 + Fix_DisplayWinExt + JCResto;
		PosY5 = 355;
		PosXT5 = 460 + Fix_DisplayWinExt + JCResto;
	}
	else if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		PosX1 = 460 + Fix_DisplayWinExt + JCResto;
		PosY1 = 180;
		PosXT1 = 460 + Fix_DisplayWinExt + JCResto;

		PosX2 = 460 + Fix_DisplayWinExt + JCResto;
		PosY2 = 225;
		PosXT2 = 460 + Fix_DisplayWinExt + JCResto;

		PosX3 = 460 + Fix_DisplayWinExt + JCResto;
		PosY3 = 285;
		PosXT3 = 460 + Fix_DisplayWinExt + JCResto;

		PosX4 = 460 + Fix_DisplayWinExt + JCResto;
		PosY4 = 330;
		PosXT4 = 460 + Fix_DisplayWinExt + JCResto;

		PosX5 = 460 + Fix_DisplayWinExt + JCResto;
		PosY5 = 375;
		PosXT5 = 460 + Fix_DisplayWinExt + JCResto;
	}
	else
	{
		PosX1 = 460;
		PosY1 = 125;
		PosXT1 = 500;

		PosX2 = 460;
		PosY2 = 180;
		PosXT2 = 500;

		PosX3 = 460;
		PosY3 = 245;
		PosXT3 = 500;

		PosX4 = 460;
		PosY4 = 300;
		PosXT4 = 500;

		PosX5 = 460;
		PosY5 = 355;
		PosXT5 = 500;
	}
		
	//gInterface.DrawFormat(eWhite, pCursorX, pCursorY, 100, 3, "X %d - Y %d, ", pCursorX, pCursorY);
	if (gInterface.IsWorkZone5(PosX1, PosY1, PosX1 + 70, PosY1 + 14))
	{
		pDrawToolTip(PosXT1 - 90, PosY1 + 4, gCustomMessage.GetMessage(181));
		//gInterface.DrawFormat(eExcellent, pCursorX, pCursorY, 100, 3, gCustomMessage.GetMessage(181));

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			OpenStatsSTRWindow();
		}
	}
	
	if (gInterface.IsWorkZone5(PosX2, PosY2, PosX2 + 70, PosY2 + 14))
	{
		pDrawToolTip(PosXT2 - 90, PosY2 + 4, gCustomMessage.GetMessage(182));
		//gInterface.DrawFormat(eExcellent, pCursorX, pCursorY, 100, 3, gCustomMessage.GetMessage(182));

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			OpenStatsAGIWindow();
		}
	}

	if (gInterface.IsWorkZone5(PosX3, PosY3, PosX3 + 70, PosY3 + 14))
	{
		pDrawToolTip(PosXT3 - 90, PosY3 + 4, gCustomMessage.GetMessage(183));
		//gInterface.DrawFormat(eExcellent, pCursorX, pCursorY, 100, 3, gCustomMessage.GetMessage(183));

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			OpenStatsVITWindow();
		}
	}

	if (gInterface.IsWorkZone5(PosX4, PosY4, PosX4 + 70, PosY4 + 14))
	{
		pDrawToolTip(PosXT4 - 90, PosY4 + 4, gCustomMessage.GetMessage(184));
		//gInterface.DrawFormat(eExcellent, pCursorX, pCursorY, 100, 3, gCustomMessage.GetMessage(184));

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			OpenStatsENEWindow();
		}
	}

	if ((gObjUser.lpPlayer->Class & 7) == 4 || (gObjUser.lpPlayer->Class & 7) == 22)
	{
		if (gInterface.IsWorkZone5(PosX5, PosY5, PosX5 + 70, PosY5 + 14))
		{
			pDrawToolTip(PosXT5 - 90, PosY5 + 4, gCustomMessage.GetMessage(185));
			//gInterface.DrawFormat(eExcellent, pCursorX, pCursorY, 100, 3, gCustomMessage.GetMessage(185));

			if (GetKeyState(VK_LBUTTON) & 0x8000)
			{
				OpenStatsCMDWindow();
				
			}
		}
	}
	}
}

void QuickAddStats::OpenStatsSTRWindow()
{

	if ((GetTickCount() - gInterface.Data[eSTATSADD_MAIN_STR].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eSTATSADD_MAIN_STR].EventTick = GetTickCount();
	gInterface.Data[eSTATSADD_MAIN_STR].OnShow ^= 1;
}

void QuickAddStats::OpenStatsAGIWindow()
{

	if ((GetTickCount() - gInterface.Data[eSTATSADD_MAIN_AGI].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eSTATSADD_MAIN_AGI].EventTick = GetTickCount();
	gInterface.Data[eSTATSADD_MAIN_AGI].OnShow ^= 1;
}

void QuickAddStats::OpenStatsVITWindow()
{

	if ((GetTickCount() - gInterface.Data[eSTATSADD_MAIN_VIT].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eSTATSADD_MAIN_VIT].EventTick = GetTickCount();
	gInterface.Data[eSTATSADD_MAIN_VIT].OnShow ^= 1;
}

void QuickAddStats::OpenStatsENEWindow()
{

	if ((GetTickCount() - gInterface.Data[eSTATSADD_MAIN_ENE].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eSTATSADD_MAIN_ENE].EventTick = GetTickCount();
	gInterface.Data[eSTATSADD_MAIN_ENE].OnShow ^= 1;
}

void QuickAddStats::OpenStatsCMDWindow()
{

	if ((GetTickCount() - gInterface.Data[eSTATSADD_MAIN_CMD].EventTick) < 500)
	{
		return;
	}

	gInterface.Data[eSTATSADD_MAIN_CMD].EventTick = GetTickCount();
	gInterface.Data[eSTATSADD_MAIN_CMD].OnShow ^= 1;
}


void QuickAddStats::DrawStatsAddWindow_STR()
{

	if (!gInterface.Data[eSTATSADD_MAIN_STR].OnShow)
	{
		return;
	}

	int ObjectCount = 1;
	
	char szCharNames[1][32];
	memcpy(szCharNames[0], gCustomMessage.GetMessage(175), sizeof(szCharNames[0]));
	
	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX01,
	};

	if (gInterface.Data[eSTATSADD_MAIN_STR].ByClose == false)
	{
		
	}
	else
	{	
		gInterface.Data[eSTATSADD_MAIN_STR].Close();
	
		
		for (int i = 0; i<ObjectCount; i++)
		{
			gInterface.Data[ObjectIDs[i]].Attribute = false;

		}
			
	}

	// ----
	float MainHeight = 130;
	float MainWidth = 230.0;
	float StartY = 50.0;
	float StartX;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
		StartY = (480 / 2) - (MainHeight / 2);
	}
	// ----
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gElemental.gDrawWindowCustomEX700Mini(StartX, StartY, MainWidth, MainHeight, eSTATSADD_MAIN_STR, gCustomMessage.GetMessage(174));
	}
	else
	{
		gElemental.gDrawWindowCustom(StartX, StartY, MainWidth, MainHeight + 10, eSTATSADD_MAIN_STR, gCustomMessage.GetMessage(174));
	}
	// ----
	DWORD StatPoints = ViewPoint;

	for (int i = 0; i<ObjectCount; i++)
	{
		StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	// ----
	//gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gCustomMessage.GetMessage(174));
	
	if (gInterface.Data[eSTATSADD_MAIN_STR].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX01].Attribute = 1;
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN_STR].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX - 38, StartY + 34 + ((i + 1) * 21), 210, 3, szCharNames[i]);
		gInterface.DrawFormat(eWhite, StartX + 45, StartY + 34 + ((i + 1) * 21), 210, 3, gInterface.Data[ObjectIDs[i]].StatValue);
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21), Color);
		}
	}

	gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, ScaleY);
	}

	if (gInterface.Data[eSTATSADD_MAIN_STR].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN_STR].FirstLoad = false;
	}
}

void QuickAddStats::DrawStatsAddWindow_AGI()
{

	if (!gInterface.Data[eSTATSADD_MAIN_AGI].OnShow)
	{
		return;
	}

	int ObjectCount = 1;
	
	char szCharNames[1][32];
	memcpy(szCharNames[0], gCustomMessage.GetMessage(176), sizeof(szCharNames[0]));
	
	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX02,
	};

	if (gInterface.Data[eSTATSADD_MAIN_AGI].ByClose == false)
	{
		
	}
	else
	{	
		gInterface.Data[eSTATSADD_MAIN_AGI].Close();
	
		
		for (int i = 0; i<ObjectCount; i++)
		{
			gInterface.Data[ObjectIDs[i]].Attribute = false;

		}
			
	}

	// ----
	float MainHeight = 130;
	float MainWidth = 230.0;
	float StartY = 50.0;
	float StartX;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
		StartY = (480 / 2) - (MainHeight / 2);
	}
	// ----
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gElemental.gDrawWindowCustomEX700Mini(StartX, StartY, MainWidth, MainHeight, eSTATSADD_MAIN_AGI, gCustomMessage.GetMessage(174));
	}
	else
	{
		gElemental.gDrawWindowCustom(StartX, StartY, MainWidth, MainHeight + 10, eSTATSADD_MAIN_AGI, gCustomMessage.GetMessage(174));
	}
	// ----
	DWORD StatPoints = ViewPoint;

	for (int i = 0; i<ObjectCount; i++)
	{
		StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	// ----
	//gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gCustomMessage.GetMessage(174));
	
	if (gInterface.Data[eSTATSADD_MAIN_AGI].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX02].Attribute = 1;
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN_AGI].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX - 38, StartY + 34 + ((i + 1) * 21), 210, 3, szCharNames[i]);
		gInterface.DrawFormat(eWhite, StartX + 45, StartY + 34 + ((i + 1) * 21), 210, 3, gInterface.Data[ObjectIDs[i]].StatValue);
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21), Color);
		}
	}

	gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, ScaleY);
	}

	//login_me
	//newui_button_cancel
	//newui_button_ok
	if (gInterface.Data[eSTATSADD_MAIN_AGI].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN_AGI].FirstLoad = false;
	}
}

void QuickAddStats::DrawStatsAddWindow_VIT()
{

	if (!gInterface.Data[eSTATSADD_MAIN_VIT].OnShow)
	{
		return;
	}

	int ObjectCount = 1;
	
	char szCharNames[1][32];
	memcpy(szCharNames[0], gCustomMessage.GetMessage(177), sizeof(szCharNames[0]));
	
	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX03,
	};

	if (gInterface.Data[eSTATSADD_MAIN_VIT].ByClose == false)
	{
		
	}
	else
	{	
		gInterface.Data[eSTATSADD_MAIN_VIT].Close();
	
		
		for (int i = 0; i<ObjectCount; i++)
		{
			gInterface.Data[ObjectIDs[i]].Attribute = false;

		}
			
	}

	float MainHeight = 130;
	float MainWidth = 230.0;
	float StartY = 50.0;
	float StartX;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
		StartY = (480 / 2) - (MainHeight / 2);
	}
	// ----
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gElemental.gDrawWindowCustomEX700Mini(StartX, StartY, MainWidth, MainHeight, eSTATSADD_MAIN_VIT, gCustomMessage.GetMessage(174));
	}
	else
	{
		gElemental.gDrawWindowCustom(StartX, StartY, MainWidth, MainHeight + 10, eSTATSADD_MAIN_VIT, gCustomMessage.GetMessage(174));
	}
	// ----
	DWORD StatPoints = ViewPoint;

	for (int i = 0; i<ObjectCount; i++)
	{
		StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	// ----
	//gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gCustomMessage.GetMessage(174));
	
	if (gInterface.Data[eSTATSADD_MAIN_VIT].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX03].Attribute = 1;
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN_VIT].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX +28, StartY + 28 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX - 38, StartY + 34 + ((i + 1) * 21), 210, 3, szCharNames[i]);
		gInterface.DrawFormat(eWhite, StartX + 45, StartY + 34 + ((i + 1) * 21), 210, 3, gInterface.Data[ObjectIDs[i]].StatValue);
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21), Color);
		}
	}

	gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, ScaleY);
	}

	if (gInterface.Data[eSTATSADD_MAIN_VIT].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN_VIT].FirstLoad = false;
	}
}

void QuickAddStats::DrawStatsAddWindow_ENE()
{

if (!gInterface.Data[eSTATSADD_MAIN_ENE].OnShow)
	{
		return;
	}

	int ObjectCount = 1;
	
	char szCharNames[1][32];
	memcpy(szCharNames[0], gCustomMessage.GetMessage(178), sizeof(szCharNames[0]));
	
	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX04,
	};

	if (gInterface.Data[eSTATSADD_MAIN_ENE].ByClose == false)
	{
		
	}
	else
	{	
		gInterface.Data[eSTATSADD_MAIN_ENE].Close();
	
		
		for (int i = 0; i<ObjectCount; i++)
		{
			gInterface.Data[ObjectIDs[i]].Attribute = false;

		}
			
	}

	float MainHeight = 130;
	float MainWidth = 230.0;
	float StartY = 50.0;
	float StartX;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
		StartY = (480 / 2) - (MainHeight / 2);
	}
	// ----
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gElemental.gDrawWindowCustomEX700Mini(StartX, StartY, MainWidth, MainHeight, eSTATSADD_MAIN_ENE, gCustomMessage.GetMessage(174));
	}
	else
	{
		gElemental.gDrawWindowCustom(StartX, StartY, MainWidth, MainHeight + 10, eSTATSADD_MAIN_ENE, gCustomMessage.GetMessage(174));
	}
	// ----
	DWORD StatPoints = ViewPoint;

	for (int i = 0; i<ObjectCount; i++)
	{
		StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	// ----
	//gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gCustomMessage.GetMessage(174));
	
	if (gInterface.Data[eSTATSADD_MAIN_ENE].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX04].Attribute = 1;
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN_ENE].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX - 38, StartY + 34 + ((i + 1) * 21), 210, 3, szCharNames[i]);
		gInterface.DrawFormat(eWhite, StartX + 45, StartY + 34 + ((i + 1) * 21), 210, 3, gInterface.Data[ObjectIDs[i]].StatValue);
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21), Color);
		}
	}

	gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, ScaleY);
	}

	if (gInterface.Data[eSTATSADD_MAIN_ENE].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN_ENE].FirstLoad = false;
	}
}

void QuickAddStats::DrawStatsAddWindow_CMD()
{

if (!gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		return;
	}

	int ObjectCount = 1;

	char szCharNames[1][32];
	memcpy(szCharNames[0], gCustomMessage.GetMessage(179), sizeof(szCharNames[0]));
	
	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX05,
	};

	if (gInterface.Data[eSTATSADD_MAIN_CMD].ByClose == false)
	{
		
	}
	else
	{	
		gInterface.Data[eSTATSADD_MAIN_CMD].Close();
	
		
		for (int i = 0; i<ObjectCount; i++)
		{
			gInterface.Data[ObjectIDs[i]].Attribute = false;

		}
			
	}

	float MainHeight = 130;
	float MainWidth = 230.0;
	float StartY = 50.0;
	float StartX;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
		StartY = (480 / 2) - (MainHeight / 2);
	}
	// ----
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		gElemental.gDrawWindowCustomEX700Mini(StartX, StartY, MainWidth, MainHeight, eSTATSADD_MAIN_CMD, gCustomMessage.GetMessage(174));
	}
	else
	{
		gElemental.gDrawWindowCustom(StartX, StartY, MainWidth, MainHeight + 10, eSTATSADD_MAIN_CMD, gCustomMessage.GetMessage(174));
	}
	// ----
	DWORD StatPoints = ViewPoint;

	for (int i = 0; i<ObjectCount; i++)
	{
		StatPoints -= atoi(gInterface.Data[ObjectIDs[i]].StatValue);
	}
	// ----
	//gInterface.DrawFormat(eGold, StartX + 10, StartY + 8, 210, 3, gCustomMessage.GetMessage(174));
	
	if (gInterface.Data[eSTATSADD_MAIN_CMD].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_STATBOX05].Attribute = 1;
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[eSTATSADD_MAIN_CMD].FirstLoad == true)
		{
			sprintf(gInterface.Data[ObjectIDs[i]].StatValue, "0");
		}
		gInterface.DrawAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21));
		gInterface.DrawFormat(eWhite, StartX - 38, StartY + 34 + ((i + 1) * 21), 210, 3, szCharNames[i]);
		gInterface.DrawFormat(eWhite, StartX + 45, StartY + 34 + ((i + 1) * 21), 210, 3, gInterface.Data[ObjectIDs[i]].StatValue);
	}

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
		{
			DWORD Color = eGray100;
			gInterface.DrawColoredAnimatedGUI(ObjectIDs[i], StartX + 28, StartY + 28 + ((i + 1) * 21), Color);
		}
	}

	gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, 0);

	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (gInterface.Data[eSTATSADD_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		gInterface.DrawAnimatedButton(eSTATSADD_BTN_OK, StartX + 85, StartY + 84, 0, ScaleY);
	}

	if (gInterface.Data[eSTATSADD_MAIN_CMD].FirstLoad == true)
	{
		gInterface.Data[eSTATSADD_MAIN_CMD].FirstLoad = false;
	}
}

void QuickAddStats::EventStatsAddWindow_STR(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN_STR].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX01,
	};

	int ObjectCount = 1;

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 0; i<0; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<0; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_STR].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Str = atoi(gInterface.Data[eSTATSADD_STATBOX01].StatValue);
		CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_STR].Close();
	}

	// ----
	return;
}

void QuickAddStats::EventStatsAddWindow_AGI(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN_AGI].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX02,
	};

	int ObjectCount = 1;

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 0; i<0; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<0; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_AGI].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Agi = atoi(gInterface.Data[eSTATSADD_STATBOX02].StatValue);
		CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_AGI].CloseAnimated(15);
	}

	// ----
	return;
}

void QuickAddStats::EventStatsAddWindow_VIT(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN_VIT].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX03,
	};

	int ObjectCount = 1;

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 0; i<0; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<0; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_VIT].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Vit = atoi(gInterface.Data[eSTATSADD_STATBOX03].StatValue);
		CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_VIT].CloseAnimated(15);
	}

	// ----
	return;
}

void QuickAddStats::EventStatsAddWindow_ENE(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN_ENE].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[1] =
	{
		eSTATSADD_STATBOX04,
	};

	int ObjectCount = 1;

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 0; i<0; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<0; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_ENE].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Ene = atoi(gInterface.Data[eSTATSADD_STATBOX04].StatValue);
		CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_ENE].CloseAnimated(15);
	}

	// ----
	return;
}

void QuickAddStats::EventStatsAddWindow_CMD(DWORD Event)
{
	if (!gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		return;
	}

	DWORD CurrentTick = GetTickCount();

	int ObjectIDs[5] =
	{
		eSTATSADD_STATBOX05,
	};

	int ObjectCount = 1;

	for (int i = 0; i<ObjectCount; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<ObjectCount; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}

	for (int i = 0; i<0; i++)
	{
		if (gInterface.IsWorkZone(ObjectIDs[i]))
		{
			DWORD Delay = (CurrentTick - gInterface.Data[ObjectIDs[i]].EventTick);
			// ----
			if (Event == WM_LBUTTONDOWN)
			{
				gInterface.Data[ObjectIDs[i]].OnClick = true;
				return;
			}
			// ----
			gInterface.Data[ObjectIDs[i]].OnClick = false;
			// ----
			if (Delay < 500)
			{
				return;
			}
			gInterface.Data[ObjectIDs[i]].EventTick = GetTickCount();

			for (int j = 0; j<0; j++)
			{
				gInterface.Data[ObjectIDs[j]].Attribute = 0;
			}

			gInterface.Data[ObjectIDs[i]].Attribute = 1;
		}
	}


	if (gInterface.IsWorkZone(eSTATSADD_BTN_OK))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_BTN_OK].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_BTN_OK].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_BTN_OK].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_CMD].CloseAnimated(15);
		PMSG_UPDATE_STATS_SEND pMsg;
		pMsg.Com = atoi(gInterface.Data[eSTATSADD_STATBOX05].StatValue);
		
		CGSendStatsAdd(pMsg);
	}

	if (gInterface.IsWorkZone(eSTATSADD_CLOSE))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[eSTATSADD_CLOSE].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[eSTATSADD_CLOSE].OnClick = true;
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return;
		}
		// ----
		gInterface.Data[eSTATSADD_CLOSE].EventTick = GetTickCount();
		gInterface.Data[eSTATSADD_MAIN_CMD].CloseAnimated(15);
	}

	// ----
	return;
}
#endif