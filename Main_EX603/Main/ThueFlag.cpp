#include "StdAfx.h"
#if(FLAG)
#include "ThueFlag.h"
#include "Import.h"
#include "Interface.h"
#include "CustomFont.h"
#include "Character.h"
#include "Util.h"
#include "TMemory.h"
#include "Defines.h"
#include "Common.h"
#include "CustomMessage.h"
#include "Protect.h"
#include "CNewUIWindowsClient.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "InterfaceElemental.h"
#include "UIController.h"

cThueFlag ThueFlag;

cThueFlag::cThueFlag()
{
	this->Init();
	#if(MOVECUSTOM==1)
	this->Moving = false;
	this->ultimoX = 220;
    this->ultimoY = 70;
    #endif
}

cThueFlag::~cThueFlag()
{

}

bool IsWorkZone102(float x, float y, float x2, float y2)
{
	bool result = GetForegroundWindow() == pGameWindow && pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
	return result;
}

void cThueFlag::SetRect(float a1, float a2, float a3, float a4)
{
	this->x = a1;
	this->y = a2;
	this->w = a3;
	this->h = a4;
}

bool cThueFlag::CheckRect()
{
	return this->Drawing && pCheckMouseOver(x, y, w, h);
	return gInterface.Data[eMAIN_ThueFlag].OnShow = true && pCheckMouseOver(x, y, w, h);
}

void cThueFlag::Init()
{
	this->Drawing = false;
#if(MOVECUSTOM==0)
	this->SetRect(120, 70, 400, 255);
#endif

}

void cThueFlag::OpenFlag()
{
	if ((GetTickCount() - gInterface.Data[eMAIN_ThueFlag].EventTick) > 300)
	{
		gInterface.Data[eMAIN_ThueFlag].EventTick = GetTickCount();

		if (gInterface.Data[eMAIN_ThueFlag].OnShow)
		{
			ThueFlag.SendRequest(0x2, 0);
			gInterface.Data[eMAIN_ThueFlag].OnShow = 0;
			return;
		}
		ThueFlag.SendRequest(0x0, ThueFlag.Selected);
		gInterface.Data[eMAIN_ThueFlag].OnShow ^= 1;
	}
}

void cThueFlag::Draw()
{
	if (gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::FriendList) || gInterface.CheckWindow(ObjWindow::MoveList)
		|| gInterface.CheckWindow(ObjWindow::Party) || gInterface.CheckWindow(ObjWindow::Quest) || gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild) || gInterface.CheckWindow(ObjWindow::Trade) || gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox) || gInterface.CheckWindow(ObjWindow::CommandWindow) || gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop) || gInterface.CheckWindow(ObjWindow::Inventory) || gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore) || gInterface.CheckWindow(ObjWindow::Character) || gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle) || gInterface.CheckWindow(ObjWindow::CreateGuild) || gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC) || gInterface.CheckWindow(ObjWindow::GuardNPC2) || gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC) || gInterface.CheckWindow(ObjWindow::CrywolfGate) || gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options) || gInterface.CheckWindow(ObjWindow::Help) || gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree) || gInterface.CheckWindow(ObjWindow::GoldenArcher1) || gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1) || gInterface.CheckWindow(ObjWindow::LuckyCoin2) || gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus) || gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1) || gInterface.CheckWindow(ObjWindow::QuestList2) || gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::NPC_Dialog) || gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia) || gInterface.CheckWindow(ObjWindow::NPC_ChaosMix) || gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse) || gInterface.CheckWindow(ObjWindow::MuHelper))
	{
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;
		return;
	}
	if (!gInterface.Data[eMAIN_ThueFlag].OnShow)
	{
		return;
	}

	float MainWidth = 200.0;
	float MainHigh = 300.0;

	gInterface.CheckWindowSProTecno(8);

	pSetCursorFocus = true;

	h=MainHigh;
	w=MainWidth;

	int JCResto;
	#if(WIDE_SCREEN == 2)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
    #else
    JCResto = 0;
    #endif
//	x =X+JCResto;
	x = this->ultimoX;
	y = this->ultimoY;
	float curX = pCursorX >=JCResto+ MAX_WIN_WIDTH ? 0 : pCursorX;
	float curY = pCursorY >= MAX_WIN_HEIGHT ? 0 : pCursorY;

	if (gInterface.IsWorkZone(JCResto+x, y, JCResto+300 / (resizeGuiRate * resizeGuiScaleRateX), 72 / (resizeGuiRate * resizeGuiScaleRateY), true)) 
	{	
		if (!this->Moving && GetKeyState(VK_LBUTTON) & 0x8000)
		{
			this->Moving = true;
			this->mX = curX;
			this->mY = curY;
		}	
	}

	if (this->Moving)
	{
		x = this->ultimoX + (curX - this->mX);
		y = this->ultimoY + (curY - this->mY);
		x = x < JCResto+20 ? JCResto+20 : x;
		x = x > JCResto+450 ? JCResto+450 : x;
		y = y < 20 ? 20 : y;
		y = y > 175 ? 175 : y;
	}

	if (this->Moving && !(GetKeyState(VK_LBUTTON) & 0x8000)) 
	{
		this->Moving = false;
		this->ultimoX = x;
		this->ultimoY = y;
	}

	//==========
	glAlphaFunc(GL_GREATER, 0.0f);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, x + JCResto - 9, y - 15, 220, 260, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, x + JCResto - 1, y + 3, 210, 3, gCustomMessage.GetMessage(28));
		gInterface.DrawGUI2(OBJECT_FLAG_SYSTEM_CLOSE, JCResto + x + 7 + MainWidth - gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].Width, y + 1);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, JCResto + x + 7 + MainWidth - gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].Width, y + 2, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(OBJECT_FLAG_SYSTEM_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(OBJECT_FLAG_SYSTEM_CLOSE, gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].X, gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].Y, Color);
		}
	}
	else
	{
		RenderBitmap(61322, x+JCResto, y +41.5, 200.0, 258.f, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, x+JCResto, y , 200.0, 42.f, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, JCResto + x, y + 18, w, 3, gCustomMessage.GetMessage(28));
		gInterface.DrawGUI2(OBJECT_FLAG_SYSTEM_CLOSE, JCResto + x + 4 + MainWidth - gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].Width, y);
		if (gInterface.IsWorkZone(OBJECT_FLAG_SYSTEM_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(OBJECT_FLAG_SYSTEM_CLOSE, gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].X, gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].Y, Color);
		}
	}

	if (pIsKeyRelease(VK_LBUTTON) && gInterface.IsWorkZone4(x + 410, y + 35, 20, 18))
	{
		this->SendRequest(0x2, 0);
		this->Drawing = false;
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;
	}

	glAlphaFunc(GL_GREATER, 0.25f);

	THUE_FLAG_DATA* skin = this->FindId(this->Selected);

	this->DrawButton(32331, JCResto + x + 14 + 13 * 4, y + h - 102.5, 73, 27, 128.0, 128.0, ThueFlag.BuyAction);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->DrawButton(32345, JCResto + x + 14 + 10 * 1, y + h - 190, 20, 23, 35.0, 128.0, ThueFlag.PrevAction);
		this->DrawButton(32346, JCResto + x + 14 + 36.5 * 4, y + h - 190, 20, 23, 35.0, 128.0, ThueFlag.NextAction);
	}
	else
	{
		this->DrawButton(32342, JCResto + x + 14 + 10 * 1, y + h - 190, 20, 23, 35.0, 128.0, ThueFlag.PrevAction);
		this->DrawButton(32343, JCResto + x + 14 + 36.5 * 4, y + h - 190, 20, 23, 35.0, 128.0, ThueFlag.NextAction);
	}

	if (skin != 0)
	{
		if (gInterface.IsWorkZone1(JCResto+x+70, y+200, JCResto+x+140, y+220))
		{
			pSetBlend(1);
			glColor4f(0.0, 0.0, 0.0, 0.8);
			pDrawBarForm(JCResto+145+x, y+200, 80, 20, 0.0f, 0);
			pGLSwitchBlend();
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
			pSetBlend(0);

			gInterface.DrawFormat(eExcellent, JCResto+150+x, y + 205, 150, 1, "Price: %d WcoinC", skin->Price);
		}

		if (gInterface.IsWorkZone1(JCResto+x+60, y+80, JCResto+x+130, y+160))
		{
			pSetBlend(1);
			glColor4f(0.0, 0.0, 0.0, 0.8);
			pDrawBarForm(JCResto+145+x, y+100, 60, 50, 0.0f, 0);
			pGLSwitchBlend();
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
			pSetBlend(0);

			gInterface.DrawFormat(eExcellent, JCResto+150+x, y + 105, 150, 1, "Attack: %d",skin->Value1);
			gInterface.DrawFormat(eExcellent, JCResto+150+x, y + 115, 150, 1, "Def: %d"   ,skin->Value2);
			gInterface.DrawFormat(eExcellent, JCResto+150+x, y + 125, 150, 1, "HP: %d"    ,skin->Value3);
			gInterface.DrawFormat(eExcellent, JCResto+150+x, y + 135, 150, 1, "Mana: %d"  ,skin->Value4);
		}
		gInterface.NewModelRender3D(JCResto+x + 55, y +50, 100, 100, 6816 + skin->Id , 0, 1, 0, 0);

		if (this->Selected <= skin->Value10)
		{
			gInterface.DrawFormat(eGold, JCResto+x + 4 + 10 * 2, y + 35, 150, 3, "Active");
			CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 14 + 13 * 4, y + h -92.5, 0xffffffff, 0x0, 73, 0, 3, skin->Skin != this->Skin ? "Use" : "Dont Use");
		}
		else if (this->Selected > skin->Value10)
		{
			gInterface.DrawFormat(eRed, JCResto+x + 4 + 10 * 2, y + 35, 150, 3, " Dont Active");
			CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 14 + 13 * 4, y + h -92.5, 0xffffffff, 0x0, 73, 0, 3, "Buy");
		}
	}
	else
	{
		char buf[25];
		int step = GetTickCount() / 1000 % 4;
		sprintf(buf, "Loading data%%.%ds", step);

		CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 25, y + 50 + 13 * 1, 0xffffffff, 0x0, 150, 0, 0, buf, "...");
	}
}

void cThueFlag::SendRequest(BYTE type, int value)
{
	PMSG_THUE_FLAG_SEND pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFF, 0x03, sizeof(pRequest));
	pRequest.Type = type;
	pRequest.Value = value;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}

void cThueFlag::RecvData(BYTE* a)
{
	PMSG_THUE_FLAG_RECV* Packet = (PMSG_THUE_FLAG_RECV*)a;

	this->Skin = Packet->Skin;

	if (Packet->Data.Id == -1)
	{
		return;
	}

	this->Selected = Packet->Data.Id;

	THUE_FLAG_DATA* skin = this->FindId(Packet->Data.Id);

	if (skin != 0)
	{
		skin->Id = Packet->Data.Id;
		skin->Skin = Packet->Data.Skin;
		skin->Price = Packet->Data.Price;
		skin->Value1 = Packet->Data.Value1;
		skin->Value2 = Packet->Data.Value2;
		skin->Value3 = Packet->Data.Value3;
		skin->Value4 = Packet->Data.Value4;
		skin->Value10 = Packet->Data.Value10;
	}
	else
	{
		THUE_FLAG_DATA new_skin;
		new_skin.Id = Packet->Data.Id;
		new_skin.Skin = Packet->Data.Skin;
		new_skin.Price = Packet->Data.Price;
		new_skin.Value1 = Packet->Data.Value1;
		new_skin.Value2 = Packet->Data.Value2;
		new_skin.Value3 = Packet->Data.Value3;
		new_skin.Value4 = Packet->Data.Value4;
		new_skin.Value10 = Packet->Data.Value10;


		this->m_Data.push_back(new_skin);
		return;
	}
}

void cThueFlag::Clear()
{

	this->TickCount = 0;
	this->Skin = 0;
	this->Selected = 0;
	this->m_Data.clear();

}

THUE_FLAG_DATA* cThueFlag::FindSkin(int id)
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		if (this->m_Data[i].Skin == id)
		{
			return &this->m_Data[i];
		}
	}
	return 0;
}

THUE_FLAG_DATA* cThueFlag::FindId(int id)
{
	for (int i = 0; i < this->m_Data.size(); i++)
	{
		if (this->m_Data[i].Id == id)
		{
			return &this->m_Data[i];
		}
	}
	return 0;
}

void cThueFlag::DrawButton(int IMGcode, float x, float y, float w, float h, float a6, float a7, PUSHEVENT_CALLBACK_LPVOID pCallbackFunc)
{
	if (pCheckMouseOver(x, y, w, h))
	{
		pSetCursorFocus = true;

		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7 * 2.0, w / a6, h / a7, 1, 1, 0.0);
		}
		else
		{
			RenderBitmap(IMGcode, x, y, w, h, 0.0, h / a7, w / a6, h / a7, 1, 1, 0.0);
		}
		if (pIsKeyRelease(VK_LBUTTON))
		{
			pCallbackFunc(this);
			return;
		}
		return;
	}
	else
	{
		RenderBitmap(IMGcode, x, y, w, h, 0.0, 0.0, w / a6, h / a7, 1, 1, 0.0);
	}
	return;
}

void cThueFlag::BuyAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;

	THUE_FLAG_DATA* skin = This->FindId(This->Selected);

	if (skin != 0)
	{
		if (skin->Skin == abs(This->Skin))
		{
			This->SendRequest(0x3, abs(This->Skin) >= 0);
		}
		else
		{
			This->SendRequest(0x1, This->Selected);
		}
	}
	//gInterface.Data[eMAIN_ThueFlag].OnShow = true;
}

void cThueFlag::NextAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;

	This->SendRequest(0x0, This->Selected + 1);
}

void cThueFlag::PrevAction(LPVOID pClass)
{
	cThueFlag* This = (cThueFlag*)pClass;
	if (This->Selected > 0)
	{
		This->SendRequest(0x0, This->Selected - 1);
	}
}

bool cThueFlag::EventCustomFlahWindows_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eMAIN_ThueFlag].OnShow || !gInterface.IsWorkZone(OBJECT_FLAG_SYSTEM_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[OBJECT_FLAG_SYSTEM_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eMAIN_ThueFlag].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}
#endif