#include "stdafx.h"
#include "Interface.h"
#include "BuyVip.h"
#include "Item.h"
#include "User.h"
#include "Util.h"
#include "Object.h"
#include "Defines.h"
#include "CustomFont.h"
#include "NewInterface.h"
#include "CustomMessage.h"
#include "Protect.h"
#include "Defines2.h"
#include "WideScreen.h"
#include "InterfaceElemental.h"
#include "CNewUIWindowsClient.h"

CUSTOM_BUYVIPS_INFO gBuyVips[MAX_CUSTOM_BUYVIPS];

cBuyVip gBuyVip;

cBuyVip::cBuyVip()
{
	this->Init();
}

cBuyVip::~cBuyVip()
{
}

void cBuyVip::Init()
{
	this->Click = false;
	this->ClearBuyVipList();
}

void cBuyVip::ClearBuyVipList() // OK
{
	for (int n = 0; n < MAX_CUSTOM_BUYVIPS; n++)
	{
		gBuyVips[n].Index = -1;
		gBuyVips[n].Exp = -1;
		gBuyVips[n].Drop = -1;
		gBuyVips[n].Days = -1;
		gBuyVips[n].Coin1 = -1;
		gBuyVips[n].Coin2 = -1;
		gBuyVips[n].Coin3 = -1;
		memset(gBuyVips[n].VipName, 0, sizeof(gBuyVips[n].VipName));
	}
}

void cBuyVip::InsertBuyVip(PMSG_BUYVIP_LIST* lpInfo) // OK
{
	for (int n = 0; n < MAX_CUSTOM_BUYVIPS; n++)
	{
		if (gBuyVips[n].Index == -1)
		{
			gBuyVips[n].Index = lpInfo->Index;
			gBuyVips[n].Exp = lpInfo->Exp;
			gBuyVips[n].Drop = lpInfo->Drop;
			gBuyVips[n].Days = lpInfo->Days;
			gBuyVips[n].Coin1 = lpInfo->Coin1;
			gBuyVips[n].Coin2 = lpInfo->Coin2;
			gBuyVips[n].Coin3 = lpInfo->Coin3;
			memcpy(gBuyVips[n].VipName, lpInfo->VipName, sizeof(gBuyVips[n].VipName));
			return;
		}
	}
}

void cBuyVip::Load()
{

}

void cBuyVip::Draw()
{
	if (!gInterface.Data[eVip_MAIN].OnShow)
	{
		return;
	}

	if (gProtect.m_MainInfo.EnableVipShop != 1)
	{
		this->CloseTestWindow();
		return;
	}

	if (gInterface.CheckWindow(ObjWindow::MoveList) || gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::SkillTree) || gInterface.CheckWindow(ObjWindow::FullMap)
		|| (gInterface.CheckWindow(Inventory)
			&& gInterface.CheckWindow(ExpandInventory)
			&& gInterface.CheckWindow(Store))
		|| (gInterface.CheckWindow(Inventory)
			&& gInterface.CheckWindow(Warehouse)
			&& gInterface.CheckWindow(ExpandWarehouse)))
	{
		this->CloseTestWindow();
		return;
	}

	gInterface.CheckWindowSProTecno(1);

	pSetCursorFocus = true;

	// ----
	float WindowW = 420;
	float WindowH = 300;
	float MainWidth = 230.0;
	float MainHeight = 180.0;
	float StartBody = 40.0;
	float StartY = 40.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	float InfoMocNapX = (StartX + 10) + 3;
	float InfoMocNapY = (StartY + 15);
	// ----

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX, StartY - 4, 233, 275, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 12, StartY + 15, 210, 3, gCustomMessage.GetMessage(26));
		gInterface.DrawGUI(eVip_CLOSE, StartX + 213, StartY + 13);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + 213, StartY + 14, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eVip_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eVip_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eVip_CLOSE, gInterface.Data[eVip_CLOSE].X, StartY, Color);
		}
	}
	else
	{
		RenderBitmap(61322, StartX + 1, StartY + 30, 225.0, 288.f, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX + 1, StartY - 5, 225.0, 42.f, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 10, StartY + 14, 210, 3, gCustomMessage.GetMessage(26));
		gInterface.DrawGUI(eVip_CLOSE, StartX + 6 + MainWidth - gInterface.Data[eVip_CLOSE].Width - 7.0, StartBody - 4);
		if (gInterface.IsWorkZone(eVip_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eVip_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eVip_CLOSE, gInterface.Data[eVip_CLOSE].X, gInterface.Data[eVip_CLOSE].Y, Color);
		}
	}

	// ----
	int LineY = gInterface.DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 35, 210, 1, gCustomMessage.GetMessage(6), gObjUser.lpPlayer->Name);
	LineY = gInterface.DrawFormat(eGold, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(14));
	LineY = gInterface.DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(7));
	LineY = gInterface.DrawFormat(eWhite, (int)StartX + 30, (int)LineY, 210, 1, gCustomMessage.GetMessage(8));
	// ----
	gInterface.DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 95 - 2, 210, 1, "Plan");
	gInterface.DrawFormat(eGold, (int)StartX + 80, (int)StartBody + 95 - 2, 210, 1, "Exp");
	gInterface.DrawFormat(eGold, (int)StartX + 130, (int)StartBody + 95 - 2, 210, 1, "Drop");
	gInterface.DrawFormat(eGold, (int)StartX + 170, (int)StartBody + 95 - 2, 210, 1, "Time");
	// ----

	if (gProtect.m_MainInfo.VipTypes < 1 || gProtect.m_MainInfo.VipTypes > 3)
	{
		gProtect.m_MainInfo.VipTypes = 3;
	}

	for (int i = 0; i < gProtect.m_MainInfo.VipTypes; i++)
	{
		gInterface.DrawFormat(eWhite, (int)StartX + 30, (int)StartBody + 110 + (12 * i) - 5, 210, 1, gBuyVips[i].VipName);
		// ----
		gInterface.DrawFormat(eWhite, (int)StartX + 80, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gBuyVips[i].Exp);
		// ----
		gInterface.DrawFormat(eWhite, (int)StartX + 130, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "+%d%%", gBuyVips[i].Drop);
		// ----
		gInterface.DrawFormat(eWhite, (int)StartX + 170, (int)StartBody + 110 + (12 * i) - 5, 210, 1, "%d day(s)", gBuyVips[i].Days);

		pDrawGUI(0x7B5E, StartX + 30, StartBody + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
		pDrawGUI(0x7B5E, StartX + 30 + 82, StartBody + 110 + (12 * i) + 9 - 5, 82.0, 2.0);
	}

	if (gProtect.m_MainInfo.VipTypes > 0)
	{
		// ---- bronze start 
		if (gInterface.IsWorkZone(eVip_BRONZE))
		{
			if (gInterface.Data[eVip_BRONZE].OnClick)
				gInterface.DrawButton(eVip_BRONZE, StartX + 64, 195, 0, 58);
			else
				gInterface.DrawButton(eVip_BRONZE, StartX + 64, 195, 0, 29);
			// ----
			gInterface.DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
			gInterface.DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gBuyVips[0].Coin1);
			gInterface.DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gBuyVips[0].Coin2);
			gInterface.DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gBuyVips[0].Coin3);
		}
		else
			gInterface.DrawButton(eVip_BRONZE, StartX + 64, 195, 0, 0);
		// ----
		gInterface.DrawFormat(eWhite, (int)StartX + 80, 195 + 9, 160, 1, gCustomMessage.GetMessage(9), gBuyVips[0].VipName);

		// ---- bronze end ------------------------------------
	}

	if (gProtect.m_MainInfo.VipTypes > 1)
	{
		// ---- Silver start ------------------------------------
		if (gInterface.IsWorkZone(eVip_SILVER))
		{
			if (gInterface.Data[eVip_SILVER].OnClick)
				gInterface.DrawButton(eVip_SILVER, StartX + 64, 225, 0, 58);
			else
				gInterface.DrawButton(eVip_SILVER, StartX + 64, 225, 0, 29);
			// ----
			gInterface.DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
			gInterface.DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gBuyVips[1].Coin1);
			gInterface.DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gBuyVips[1].Coin2);
			gInterface.DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gBuyVips[1].Coin3);
		}
		else
			gInterface.DrawButton(eVip_SILVER, StartX + 64, 225, 0, 0);

		gInterface.DrawFormat(eWhite, (int)StartX + 80, 225 + 9, 160, 1, gCustomMessage.GetMessage(9), gBuyVips[1].VipName);
		// ---- silver end ------------------------------------
	}

	if (gProtect.m_MainInfo.VipTypes > 2)
	{
		// ---- gold start ------------------------------------
		if (gInterface.IsWorkZone(eVip_GOLD))
		{
			if (gInterface.Data[eVip_GOLD].OnClick)
				gInterface.DrawButton(eVip_GOLD, StartX + 64, 255, 0, 58);
			else
				gInterface.DrawButton(eVip_GOLD, StartX + 64, 255, 0, 29);
			// ----
			gInterface.DrawFormat(eGold, (int)StartX + 30, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(10));
			gInterface.DrawFormat(eGold, (int)StartX + 70, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(11), gBuyVips[2].Coin1);
			gInterface.DrawFormat(eGold, (int)StartX + 120, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(12), gBuyVips[2].Coin2);
			gInterface.DrawFormat(eGold, (int)StartX + 160, (int)StartBody + 142, 210, 1, gCustomMessage.GetMessage(13), gBuyVips[2].Coin3);
		}
		else
			gInterface.DrawButton(eVip_GOLD, StartX + 64, 255, 0, 0);

		gInterface.DrawFormat(eWhite, (int)StartX + 80, 255 + 9, 160, 1, gCustomMessage.GetMessage(9), gBuyVips[2].VipName);
		// ---- gold end ------------------------------------
	}
}

bool cBuyVip::EventVipWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eVip_CLOSE].EventTick);
	if (!gInterface.Data[eVip_MAIN].OnShow || !gInterface.IsWorkZone(eVip_CLOSE))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eVip_CLOSE].OnClick = true;
		return true;
	}
	gInterface.Data[eVip_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	gInterface.Data[eVip_CLOSE].EventTick = GetTickCount();
	this->CloseTestWindow();
	return false;
}
// ----------------------------------------------------------------------------------------------

bool cBuyVip::EventVipWindow_Bronze(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eVip_BRONZE].EventTick);
	// ----
	if (!gInterface.Data[eVip_MAIN].OnShow || !gInterface.IsWorkZone(eVip_BRONZE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eVip_BRONZE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eVip_BRONZE].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eVip_BRONZE].EventTick = GetTickCount();
	this->JanelaConfirmVip = 1;
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool cBuyVip::EventVipWindow_Silver(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eVip_SILVER].EventTick);
	// ----
	if (!gInterface.Data[eVip_MAIN].OnShow || !gInterface.IsWorkZone(eVip_SILVER))
	{
		return false;
	}
	if (gProtect.m_MainInfo.VipTypes < 2)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eVip_SILVER].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eVip_SILVER].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eVip_SILVER].EventTick = GetTickCount();
	this->JanelaConfirmVip = 2;
	// ----
	return false;
}

// ----------------------------------------------------------------------------------------------
bool cBuyVip::EventVipWindow_Gold(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eVip_GOLD].EventTick);
	// ----
	if (!gInterface.Data[eVip_MAIN].OnShow || !gInterface.IsWorkZone(eVip_GOLD))
	{
		return false;
	}
	if (gProtect.m_MainInfo.VipTypes < 3)
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eVip_GOLD].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eVip_GOLD].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eVip_GOLD].EventTick = GetTickCount();
	this->JanelaConfirmVip = 3;
	// ----
	return false;
}
// ----------------------------------------------------------------------------------------------

bool cBuyVip::EventVipWindow_Main(DWORD Event)
{
	this->EventVipWindow_Close(Event);
	this->EventVipWindow_Bronze(Event);
	this->EventVipWindow_Silver(Event);
	this->EventVipWindow_Gold(Event);
	// ----
	return true;
}

void cBuyVip::DrawConfirm()
{
	if (this->JanelaConfirmVip != 0)
	{
		pSetCursorFocus = true;

		float MainWidth = 230.0;
		float MainHeight = 130.0;
		float StartBody = 90.0;
		float StartY = 90.0;
		float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		float MainCenter = StartX + (MainWidth / 3);
		float ButtonX = MainCenter - (float)(29.0 / 2);

		gInterface.DrawGUI(eCONFIRM_MAIN, StartX, StartY + (float)2.0);
		gInterface.DrawGUI(eVip_TITLE, StartX, StartY);
		StartY = gInterface.DrawRepeatGUI(eVip_FRAME, StartX, StartY + (float)5.0, 5);
		gInterface.DrawGUI(eVip_FOOTER, StartX, StartY);

		gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

		gInterface.DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

		gInterface.DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, 0);

		if (gInterface.IsWorkZone(eCONFIRM_BTN_OK))
		{
			int ScaleY = 30;
			// ----

			if (pIsKeyPress(1))
			{
				if (this->JanelaConfirmVip == 1)
				{
					this->BuyStatus(1);
				}
				if (this->JanelaConfirmVip == 2)
				{
					this->BuyStatus(2);
				}
				if (this->JanelaConfirmVip == 3)
				{
					this->BuyStatus(3);
				}
				this->JanelaConfirmVip = 0;
				ScaleY = 60;
			}
			// ----
			gInterface.DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, ScaleY);
		}

		gInterface.DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, 0);

		if (gInterface.IsWorkZone(eCONFIRM_BTN_CANCEL))
		{
			int ScaleY = 30;
			// ----
			if (pIsKeyPress(1))
			{
				this->JanelaConfirmVip = 0;
				ScaleY = 60;
			}
			// ----
			gInterface.DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, ScaleY);
		}
	}
}

void cBuyVip::BuyStatus(int VipType)
{
	BUYPREMIUM_REQ pRequest;
	pRequest.h.set(0xF3, 0xF0, sizeof(pRequest));
	pRequest.VipType = VipType;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}