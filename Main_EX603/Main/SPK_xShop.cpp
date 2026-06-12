#include "stdafx.h"
#include "SPK_xShop.h"
#include "MemScript.h"
#include "Util.h"
#include "Interface.h"
#include "Defines.h"
#include "InterfaceElemental.h"
#include "CBNewUiEx.h"
#include "CustomFont.h"
#include "Config.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "CNewUIWindowsClient.h"

#if(CustomXShop)

CNewCashShop gNewCashShop;

#define MAX_STRING_LENGTH 50

CNewUIScrollBar* ListShop = nullptr;
CNewUIScrollBar* ListItemBan = nullptr;
int MaxListShopInPage = 10;
int MaxListItemShopInPage = 21;
int SelectTypeShop = 1;
int SeclectClass = -1;
int ViTriMua = -1;

CNewCashShop::CNewCashShop()
{
	this->Init();
}

void CNewCashShop::Init()
{
	this->ListItemCashShop.clear();
	this->DanhSachCashShop.clear();
}

void CNewCashShop::DrawItemToolTipText(void* item, int x, int y)
{
	static DWORD mem = 0;
	_asm
	{
		PUSH 0
		PUSH 0
		PUSH 0
		PUSH item
		PUSH y
		PUSH x
		MOV mem, 0x00861110
		CALL mem
		MOV ECX, EAX
		MOV mem, 0x00861AA0
		CALL mem
		MOV ECX, EAX
		MOV mem, 0x007E3E30
		CALL mem
	}
}
void CNewCashShop::SendPacketToProtocol11(BYTE* lpMsg)
{
	gNewCashShop.DanhSachCashShop.clear();
	PMSG_CASHSHOP_SEND* mRecv = (PMSG_CASHSHOP_SEND*)lpMsg;
	for (int i = 0; i < mRecv->count; i++)
	{
		ListShopSend lpInfo = *(ListShopSend*)(((BYTE*)lpMsg) + sizeof(PMSG_CASHSHOP_SEND) + (sizeof(ListShopSend) * i));
		gNewCashShop.DanhSachCashShop.push_back(lpInfo);
	}
	gInterface.Data[eCustomShop].OnShow ^= 1;
}

void CNewCashShop::SendPacketToProtocol12(BYTE* lpMsg)
{
	gNewCashShop.ListItemCashShop.clear();
	PMSG_LISTITEMSHOP_SEND* mRecv = (PMSG_LISTITEMSHOP_SEND*)lpMsg;
	for (int i = 0; i < mRecv->count; i++)
	{
		LISTITEMCASHSHOP_SENDINFO lpInfo = *(LISTITEMCASHSHOP_SENDINFO*)(((BYTE*)lpMsg) + sizeof(PMSG_LISTITEMSHOP_SEND) + (sizeof(LISTITEMCASHSHOP_SENDINFO) * i));
		INFO_SHOP_ITEM infoItemLocal = { 0 };
		infoItemLocal.SizeBMD = lpInfo.SizeBMD;
		infoItemLocal.PriceType = lpInfo.PriceType;
		infoItemLocal.Price = lpInfo.Price;

		for (int n = 0; n < MAX_CLASS; n++)
		{
			infoItemLocal.Class[n] = lpInfo.Class[n];
		}
		infoItemLocal.Index = lpInfo.Index;
		infoItemLocal.TypeItem = lpInfo.TypeItem;
		infoItemLocal.Item = *((ObjectItem * (__thiscall*)(int, BYTE*)) 0x007E1B10)(*(DWORD*)(((int(*)()) 0x861110)() + 36), lpInfo.Item);
		infoItemLocal.Item.Durability = lpInfo.Dur;
		if (lpInfo.PeriodTime)
		{
			infoItemLocal.Item.PeriodItem = 1;
			infoItemLocal.Item.ExpireDateConvert = lpInfo.PeriodTime;
		}
		gNewCashShop.ListItemCashShop.push_back(infoItemLocal);

	}
}
void CNewCashShop::OpenCustomShop()
{
	if ((GetTickCount() - gInterface.Data[eCustomShop].EventTick) > 300)
	{
		gInterface.Data[eCustomShop].EventTick = GetTickCount();

		if (gInterface.Data[eCustomShop].OnShow)
		{
			gInterface.Data[eCustomShop].OnShow = 0;
			return;
		}
		XULY_CGPACKET pMsg;
		pMsg.header.set(0xD5, 0x13, sizeof(pMsg));
		pMsg.ThaoTac = 1; //
		DataSend((LPBYTE)&pMsg, pMsg.header.size);

		pMsg.header.set(0xD5, 0x12, sizeof(pMsg));
		pMsg.ThaoTac = 1; //
		DataSend((LPBYTE)&pMsg, pMsg.header.size);
	}
}

static void XacNhanMuaShop(LPVOID pClass)
{
	XULY_CGPACKET_SSHOP pMsg;
	pMsg.header.set(0xD5, 0x11, sizeof(pMsg));
	pMsg.Shop = SelectTypeShop; //
	pMsg.ViTri = ViTriMua;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}

char* MyClassID[7] =
{ 
	"DW", 
	"DK", 
	"ELF", 
	"MG", 
	"DL", 
	"SM", 
	"RF" 
};
char* MoneyType[5] =
{
	"Zen", // 0
	"WC", // 1
	"WP", // 2
	"WG", // 3
	"PcPoint", // 3
};

void CNewCashShop::DrawShop()
{
	if (CheckShopWindows)
	{
		gInterface.Data[eCustomShop].OnShow = 0;
		return;
	}

	if (!gInterface.Data[eCustomShop].OnShow)
	{
		if (ListShop) ListShop = nullptr;
		if (ListItemBan) ListItemBan = nullptr;
		if (SelectTypeShop != 1) SelectTypeShop = 1;
		if (SeclectClass != -1) SeclectClass = -1;
		return;
	}

	gInterface.CheckWindowSProTecno(6);

	pSetCursorFocus = true;

	float WindowW = 480;
	float WindowH = 300;
	float MainWidth, MainHeight;
	MainWidth = 230.0;
	MainHeight = 283.0;
	gInterface.Data[eCustomShop].Width = WindowW;
	float StartBody = 30.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2) - 115;
	float StartY = 55;

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX - 1, StartY - 10, 462, 315, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 125, StartY + 14, 210, 3, gCustomMessage.GetMessage(108));
		gInterface.DrawGUI(eCustomShop_CLOSE_MAIN, StartX + 433, StartY + 10);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + 433, StartY + 11, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eCustomShop_CLOSE_MAIN))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eCustomShop_CLOSE_MAIN].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eCustomShop_CLOSE_MAIN, gInterface.Data[eCustomShop_CLOSE_MAIN].X, StartY, Color);
		}
	}
	else
	{
		RenderBitmap(61322, StartX + 6, StartY - 4, 444, 388.f, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX + 6, StartY - 4, 444, 41.f, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 124, StartY + 14, 210, 3, gCustomMessage.GetMessage(108));
		gInterface.DrawGUI(eCustomShop_CLOSE_MAIN, StartX + 415, StartY - 3);
		if (gInterface.IsWorkZone(eCustomShop_CLOSE_MAIN))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eCustomShop_CLOSE_MAIN].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eCustomShop_CLOSE_MAIN, gInterface.Data[eCustomShop_CLOSE_MAIN].X, gInterface.Data[eCustomShop_CLOSE_MAIN].Y, Color);
		}
	}

	{
		pSetCursorFocus = true;
		pSetBlend(true);
		glColor3f(1.0, 1.0, 1.0);
		float InfoMocNapX = (StartX + 10) + 3;
		float InfoMocNapY = (StartY + 65);
		float TyleInfoYeuCau = 7.5f;
		float WInfo = (WindowW - 20) / 10;
		float WProcess = (WInfo * (TyleInfoYeuCau - 2.7));
		float WButton = 80;
		float HInfo = WindowH - 100;
		float MoveXScroll = 96.0f;
		pSetCursorFocus = true;
		int DataListShop = this->DanhSachCashShop.size();

		CustomFont.Draw(CustomFont.FontBold, InfoMocNapX, StartY + 285, 0xEBA000FF, 0, WindowW - 20, 0, 3, gConfig.TEXT_XSHOP[0]);
		gElemental.gInfoBox(InfoMocNapX, InfoMocNapY - 5, 85, HInfo + 10, 0x00000096, 0, 0);

		gElemental.gInfoBox(InfoMocNapX + 95, InfoMocNapY - 5, WindowW - 150, HInfo + 10, 0x00000096, 0, 0);

		CustomFont.Draw(CustomFont.FontBold, InfoMocNapX + 1, InfoMocNapY - 5, 0xFFFFFFFF, 0xEBA000FF, 90, 0, 3, gConfig.TEXT_XSHOP[1]);
		CustomFont.Draw(CustomFont.FontBold, InfoMocNapX + 96, InfoMocNapY - 5, 0xFFFFFFFF, 0xEBA000FF, WindowW - 145, 0, 3, gConfig.TEXT_XSHOP[2]);

		char MemCoin[4][255];

		for (int x = 0; x < 4; x++)
		{
			ZeroMemory(MemCoin[x], sizeof(MemCoin[x]));
		}

		wsprintf(MemCoin[0], "WC: %d", Coin1);
		wsprintf(MemCoin[1], "WP: %d", Coin2);
		wsprintf(MemCoin[2], "GP: %d", Coin3);
		//wsprintf(MemCoin[3], "PcPoint: %d", PcPoint);

		for (int X = 0; X < 3; X++)
		{
			gElemental.gDrawButton(InfoMocNapX - 60 + (80 * (X + 1)), InfoMocNapY - 30, 90, 11, "", 70);
			gInterface.DrawFormat(eGold, InfoMocNapX - 69.02 + (80 * (X + 1)), InfoMocNapY - 24, 90, 3,"%s", MemCoin[X]);
		}
		
		if (!ListShop)
		{
			ListShop = new CNewUIScrollBar();
			ListShop->Create((StartX)+MoveXScroll, InfoMocNapY + 20, HInfo);
			if (ListShop)
			{
				ListShop->SetMaxPos((DataListShop <= MaxListShopInPage) ? 0 : (DataListShop / MaxListShopInPage) - 1);
				ListShop->SetPos((StartX)+MoveXScroll, InfoMocNapY + 10);
			}
		}
		if (ListShop) // where is cpp of pcpoint and inventory ?
		{
			ListShop->MouseWheelWindow = pCheckMouseOver(InfoMocNapX + MoveXScroll - 5, InfoMocNapY, 90, HInfo + 10);
			ListShop->Render();
			ListShop->UpdateMouseEvent();
			ListShop->Update();
		}

		float KhoangCachYMocNap = 19;
		int MixItemListPage = ListShop->GetCurPos();
		int MaxList = 0;
		for (int n = (MixItemListPage * MaxListShopInPage); n < DataListShop; n++)
		{
			if (gElemental.gDrawButton(InfoMocNapX + 6, InfoMocNapY + 10, 90, 11, this->DanhSachCashShop[n].Name, WButton - 10))
			{
				ListItemBan = nullptr;
				SeclectClass = -1;
				SelectTypeShop = this->DanhSachCashShop[n].IndexShop;
				XULY_CGPACKET pMsg;
				pMsg.header.set(0xD5, 0x12, sizeof(pMsg));
				pMsg.ThaoTac = SelectTypeShop;
				DataSend((LPBYTE)&pMsg, pMsg.header.size);
			}
			InfoMocNapY = InfoMocNapY + (KhoangCachYMocNap);
			MaxList++;
			if (MaxList >= MaxListShopInPage) break;
		}
		int DataListItem = this->ListItemCashShop.size();
		if (!ListItemBan)
		{
			ListItemBan = new CNewUIScrollBar();
			ListItemBan->Create((StartX + WindowW) - 48, InfoMocNapY + 35, HInfo);

			if (ListItemBan)
			{
				ListItemBan->SetMaxPos((DataListItem <= MaxListItemShopInPage) ? 0 : (DataListItem / MaxListItemShopInPage));
				ListItemBan->SetPos((StartX + WindowW) - 48, StartY + 75);
			}
		}
		if (ListItemBan)
		{
			ListItemBan->MouseWheelWindow = pCheckMouseOver(StartX + 102, StartY + 75, WindowW - 110, 300);
			ListItemBan->Render();
			ListItemBan->UpdateMouseEvent();
			ListItemBan->Update();
		}
		float PosXBoxItemGoc = StartX + 115;
		float PosXBoxItem = StartX + 115;
		float PosYBoxItem = StartY + 80;
		float WBox = 50;
		float KhoangCach = 85;
		int CountNgang = 0;
		int CountDoc = 0;
		int ItemListPage = ListItemBan->GetCurPos();
		int BBShowInfoItem = -1;

		for (int n = (ItemListPage * MaxListItemShopInPage); n < DataListItem; n++)
		{
			ItemBmdStruct* is = pGetItemBmdStruct(this->ListItemCashShop[n].Index);
			int size = max(is->ItemWidth, is->ItemHeight);

			float itemScale = 1.0;
			float addY = 0;
			switch (size)
			{
				case 4: addY = -5; break;
				case 3: addY = -3; break;
				case 2: addY = -1; break;
			}
			
			if (this->ListItemCashShop[n].Class[SeclectClass] == 0)
			{
				continue;
			}
			if (pCheckMouseOver(PosXBoxItem, PosYBoxItem, WBox, WBox - 5))
			{
				gElemental.gInfoBoxColor(PosXBoxItem + 1, PosYBoxItem + 2, WBox - 17, WBox - 16, 0x26E0A596, 0, 0);
				gElemental.gItemBoxInv(PosXBoxItem, PosYBoxItem, 2, 2, 0);
				BBShowInfoItem = n;
			}
			else
			{
				gElemental.gItemBoxInv(PosXBoxItem, PosYBoxItem, 2, 2, 0);
			}
			float SidX;
			if (SelectTypeShop && this->ListItemCashShop[n].TypeItem == 7 || this->ListItemCashShop[n].TypeItem == 8 || this->ListItemCashShop[n].TypeItem == 9 || this->ListItemCashShop[n].TypeItem == 10 || this->ListItemCashShop[n].TypeItem == 11)
			{
				SidX = 10;
			}
			else
			{
				SidX = 0;
			}
			gInterface.DrawItem3D(PosXBoxItem - 2, PosYBoxItem + addY - SidX, WBox, WBox, this->ListItemCashShop[n].Index, this->ListItemCashShop[n].Item.Level, this->ListItemCashShop[n].Item.ExcellentOption, this->ListItemCashShop[n].Item.AncientOption, 0, 1.0 / this->ListItemCashShop[n].SizeBMD);//Show Item
			CustomFont.Draw(CustomFont.FontNormal, PosXBoxItem, PosYBoxItem - 8, 0xffffffff, 0x00ff007f, WBox - 9, 0, 3, "%d", this->ListItemCashShop[n].Price);

			char GetTypePrice[255];
			ZeroMemory(GetTypePrice, sizeof(GetTypePrice));
			wsprintf(GetTypePrice, gConfig.TEXT_XSHOP[3], MoneyType[this->ListItemCashShop[n].PriceType]);
			if (gElemental.gDrawButton(PosXBoxItem - 1, PosYBoxItem + 42, 80, 11, GetTypePrice, WBox - 8)) //"Xem"
			{
				ViTriMua = n;
				gElemental.OpenMessageBoxOkCancel(XacNhanMuaShop, gConfig.TEXT_XSHOP[4], BGetItemName(this->ListItemCashShop[ViTriMua].Item.ItemID, this->ListItemCashShop[ViTriMua].Item.Level), this->ListItemCashShop[n].Price, MoneyType[this->ListItemCashShop[n].PriceType]);
			}

			PosXBoxItem += KhoangCach - 40;
			CountDoc++;
			CountNgang++;
			if (CountNgang >= 7)
			{
				PosXBoxItem = PosXBoxItemGoc;
				PosYBoxItem += KhoangCach - 17;
				CountNgang = 0;
			}
			if (CountDoc >= MaxListItemShopInPage) break;
		}
		if (BBShowInfoItem != -1)
		{
			this->DrawItemToolTipText((void*)&this->ListItemCashShop[BBShowInfoItem].Item, *(int*)0x879340C, *(int*)0x8793410 + 25);
			glColor3f(1, 1, 1);
			pSetBlend(false);
		}
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
	}
}

bool CNewCashShop::EventCustomShopWindows_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eCustomShop_CLOSE_MAIN].EventTick);
	// ----
	if (!gInterface.Data[eCustomShop].OnShow || !gInterface.IsWorkZone(eCustomShop_CLOSE_MAIN))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eCustomShop_CLOSE_MAIN].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eCustomShop_CLOSE_MAIN].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eCustomShop_CLOSE_MAIN].EventTick = GetTickCount();
	gInterface.Data[eCustomShop].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}
#endif