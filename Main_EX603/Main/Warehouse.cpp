#include "stdafx.h"
#include "Warehouse.h"
#include "Interface.h"
#include "Defines.h"
#include "Util.h"
#include "Protect.h"
int BauID = 0;
int BauQtd = 0;
BYTE BauLock = FALSE;

CWarehouse gWarehouse;


void CWarehouse::StorageLoad()
{
	SetCompleteHook(0xE8, 0x00857B10, &StorageBauTitle);
}

void CWarehouse::StorageBauTitle(char* a, char* b, char* c, int d)
{
	if (BauLock >= 1)
	{
		char Storage[80];

		sprintf(Storage, "%s [%d/%d]", c, BauID, BauQtd);

		wsprintf(a, Storage, c, d);
	}
	else
	{
		wsprintf(a, b, c, d);
	}
}

void CWarehouse::ButtonsDraw()
{

	if (BauLock <= 0)
	{
		return;
	}

	if (!gInterface.CheckWindow(ObjWindow::Warehouse))
	{
		return;
	}
	// ---
	float PosX;
	float PosY;

	
	
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		int JCResto; // eax@1
		int JCWinWidth; // eax@1
		JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
		JCResto = JCWinWidth / 2 - 320;

		PosX = 301.0 + Fix_DisplayWinExt + JCResto;
		PosY = 22.0;

		gInterface.DrawFormat(eYellow, PosX, PosY + 15, 125, 3, "Warehouse [%d/%d]", BauID, BauQtd);
	}
	else if (gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		int JCResto; // eax@1
		int JCWinWidth; // eax@1
		JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
		JCResto = JCWinWidth / 2 - 320;

		PosX = 291.0 + Fix_DisplayWinExt + JCResto;
		PosY = 2.0;
	}
	else
	{
		PosX = 293.0;
		PosY = 2.0;
	}
	// ---
	gInterface.DrawGUI(eWAREHOUSE_LEFT, PosX, PosY);
	// ---
	if (gInterface.IsWorkZone(eWAREHOUSE_LEFT))
	{
		DWORD Color = eGray100;
		// ---
		if (gInterface.Data[eWAREHOUSE_LEFT].OnClick)
		{
			Color = eGray150;
		}
		// ---
		gInterface.DrawColoredGUI(eWAREHOUSE_LEFT, gInterface.Data[eWAREHOUSE_LEFT].X, gInterface.Data[eWAREHOUSE_LEFT].Y, Color);
		// ---
		gInterface.DrawToolTip(gInterface.Data[eWAREHOUSE_LEFT].X + 5, gInterface.Data[eWAREHOUSE_LEFT].Y + 25, "Previous Warehouse");
	}
	// ---
	PosX += 3 + (5 * gInterface.Data[eWAREHOUSE_LEFT].Height);
	// ---
	gInterface.DrawGUI(eWAREHOUSE_RIGHT, PosX, PosY);
	// ---
	if (gInterface.IsWorkZone(eWAREHOUSE_RIGHT))
	{
		DWORD Color = eGray100;
		// ---
		if (gInterface.Data[eWAREHOUSE_RIGHT].OnClick)
		{
			Color = eGray150;
		}
		// ---
		gInterface.DrawColoredGUI(eWAREHOUSE_RIGHT, gInterface.Data[eWAREHOUSE_RIGHT].X, gInterface.Data[eWAREHOUSE_RIGHT].Y, Color);
		// ---
		gInterface.DrawToolTip(gInterface.Data[eWAREHOUSE_RIGHT].X + 5, gInterface.Data[eWAREHOUSE_RIGHT].Y + 25, "Next Warehouse");
	}
}

bool CWarehouse::ButtonEvent_Main(DWORD Event)
{
	// ---
	this->ButtonClick_Event(Event, eWAREHOUSE_LEFT);
	this->ButtonClick_Event(Event, eWAREHOUSE_RIGHT);
	// ---
	return true;
}

bool CWarehouse::ButtonClick_Event(DWORD Event, int ObjectId)
{
	if (BauLock <= 0)
	{
		return 0;
	}

	if (!gInterface.CheckWindow(ObjWindow::Warehouse))
	{
		return false;
	}
	// ---
	float PosX;
	float PosY;

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		int JCResto; // eax@1
		int JCWinWidth; // eax@1
		JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
		JCResto = JCWinWidth / 2 - 320;

		PosX = 301.0 + Fix_DisplayWinExt + JCResto;
		PosY = 22.0;
	}
	else if (gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		int JCResto; // eax@1
		int JCWinWidth; // eax@1
		JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
		JCResto = JCWinWidth / 2 - 320;

		PosX = 291.0 + Fix_DisplayWinExt + JCResto;
		PosY = 2.0;
	}
	else
	{
		PosX = 293.0;
		PosY = 2.0;
	}
	// ---
	DWORD CurrentTick = GetTickCount();
	// ---
	if (ObjectId == eWAREHOUSE_RIGHT)
	{
		PosX += 3 + (5 * gInterface.Data[eWAREHOUSE_LEFT].Height);
	}
	// ---
	if (gInterface.IsWorkZone(PosX, PosY, PosX + 23, PosY + 28))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[ObjectId].EventTick);
		// ---
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[ObjectId].OnClick = true;
			return true;
		}
		// ---
		gInterface.Data[ObjectId].OnClick = false;
		// ---
		if (Delay < 700)
		{
			return false;
		}
		// ---
		gInterface.Data[ObjectId].EventTick = GetTickCount();
		// ---
		if (ObjectId == eWAREHOUSE_RIGHT)
		{
			if (BauID >= BauQtd)
			{
				return false;
			}
			// ---
			BauID++;
		}
		else
		{
			if (BauID <= 0)
			{
				return false;
			}
			// --
			BauID--;
		}
		// ---
		this->CGWarehouseIDSend(BauID);
		// ---
		return false;
	}
}

void CWarehouse::GCReqWarehouseUserCountRecv(PMSG_WAREHOUSEINFO_RECV* lpMsg)
{
	BauID = lpMsg->BauID;
	BauQtd = lpMsg->BauQtd;
	BauLock = lpMsg->BauLock;
}

void CWarehouse::CGWarehouseIDSend(int BauID)
{
	PMSG_WAREHOUSE_CHANGE_SEND pMsg;
	pMsg.header.set(0xF3, 0xF7, sizeof(pMsg));
	pMsg.BauID = BauID;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}