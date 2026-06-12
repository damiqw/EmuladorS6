#include "stdafx.h"
#if(DAILY)
#include "DailyReward.h"
#include "Import.h"
#include "CustomFont.h"
#include <ctime>
#include "Interface.h"
#include "Defines.h"
#include "Common.h"
#include "User.h"
#include "CustomMessage.h"
#include "Protect.h"
#include "WideScreen.h"
#include "SEASON3B.h"
#include "InterfaceElemental.h"
#include "NewInterface.h"
#include "Antilag.h"
#include "CNewUIWindowsClient.h"

cDailyReward DailyReward;

cDailyReward::cDailyReward()
{
	this->Init();
	#if(MOVECUSTOM==1)
	this->Moving = false;
	this->ultimoX = 120;
    this->ultimoY = 70;
    #endif
}

cDailyReward::~cDailyReward()
{
}

void cDailyReward::Init()
{
	this->SetWindow(false);
	this->SetRect(120, 70, 400, 255);
	this->SetTitle("", 0xc1c1c1ff, 0x0, 1);
	this->SelectedDay = 1;
}

unsigned char last_day_of_month(int year, unsigned char month) 
{
	return month != 2 ? ((month ^ (month >> 3))) | 30 :
		year % 4 ? 29 : 28;
}

void cDailyReward::ClearDayGift()
{
	this->DayInfo = false;
	this->Type = -1;
	this->Level = 0;
	this->Ex = 0;
	this->Zen = 0;
	this->Wcoin = 0;
}

int ImgTag100 = 0;
void cDailyReward::DrawIcon() //focus move box daily
{

	if (gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(MoveList)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(Guild)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(eJewelBank_MAIN)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(FriendList)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(MuHelper)
		|| gInterface.CheckWindow(Quest)
		|| gInterface.CheckWindow(Lugard)
		|| gInterface.CheckWindow(Jerint)
		|| gInterface.CheckWindow(GoldenArcher1)
		|| gInterface.CheckWindow(GoldenArcher2)
		|| gInterface.CheckWindow(NPC_Duel)
		|| gInterface.CheckWindow(NPC_Devin)
		|| gInterface.CheckWindow(GuardNPC)
		|| gInterface.CheckWindow(SeniorNPC)
		|| gInterface.CheckWindow(GuardNPC2)
		|| gInterface.CheckWindow(CastleGateSwitch)
		|| gInterface.CheckWindow(CatapultNPC)
		|| gInterface.CheckWindow(CreateGuild)
		|| gInterface.CheckWindow(ExpandWarehouse)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(ChatWindow)
		|| gInterface.CheckWindow(CommandWindow))
	{
		return;
	}

	if (ButtonDaily == 0)
	{
		float Active_x;

		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			Active_x = (MAX_WIN_WIDTH / 2) + 60;
		}
		else
		{
			Active_x = (640 / 2) + 80;
		}

		float Active_y = 2;
		//gInterface.DrawButtonRender(eINVASION_MAIN_OPEN, Active_x, Active_y, 0, 0);

		if (pCheckMouseOver(Active_x, Active_y, 110.0, 20.0))
		{
			nInterface.ActiveLockMouse = GetTickCount() + 500;
		}

		gElemental.gDrawButton(Active_x, Active_y, 80, 12, gCustomMessage.GetMessage(106));

		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			if (pCheckInMouse((MAX_WIN_WIDTH / 2) + 59, 2, 83, 20.0) && IsRelease(VK_LBUTTON)) //
			{
				gInterface.Data[eMAIN_DailySystem].OnShow = true;
				DailyReward.OpenWindow(true);
				//this->Page = 0;
			}
		}
		else
		{
			if (pCheckInMouse((640 / 2) + 59, 2, 83, 20.0) && IsRelease(VK_LBUTTON)) //
			{
				gInterface.Data[eMAIN_DailySystem].OnShow = true;
				DailyReward.OpenWindow(true);
				//this->Page = 0;
			}
		}
	}
}

void cDailyReward::Draw()
{
	if (!gInterface.Data[eMAIN_DailySystem].OnShow)
	{
		DrawIcon();
		return;
	}

	if (pPlayerState < GameProcess)
	{
		return;
	}

	if (gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::MoveList)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Trade)
		|| gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow)
		|| gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop)
		|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle)
		|| gInterface.CheckWindow(ObjWindow::CreateGuild)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC2)
		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)
		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)
		|| gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList)
		|| gInterface.CheckWindow(ObjWindow::ChatWindow)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options)
		|| gInterface.CheckWindow(ObjWindow::Help)
		|| gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)
		|| gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)
		|| gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1)
		|| gInterface.CheckWindow(ObjWindow::QuestList2)
		|| gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)
		|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)
		|| gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)
		|| gInterface.CheckWindow(ObjWindow::MuHelper)
		)
	{

		this->CloseWindow(true);
	}

	gInterface.CheckWindowSProTecno(4);

	pSetCursorFocus = true;

	if (!CheckWindow())
	{
		DrawIcon();
		return;
	}
	//this->DrawBase();

	if (!gInterface.Data[eMAIN_DailySystem].OnShow)
	{
		return;
	}
	float MainWidth = 400.0;
	float MainHigh = 255.0;
	
	float X = 120;
	float Y= 70;
	//x=X;
	y=Y;
	h=MainHigh;
	w=MainWidth;

	int JCResto;
	#if(WIDE_SCREEN == 2)
	JCResto =  pWinWidth / pWinHeightReal/ 2 -320;
    #else
    JCResto = 0;
    #endif
	x =X+JCResto;
	x = this->ultimoX;
	y = this->ultimoY;
	float curX = pCursorX >=JCResto+ MAX_WIN_WIDTH ? 0 : pCursorX;
	float curY = pCursorY >= MAX_WIN_HEIGHT ? 0 : pCursorY;

	if (gInterface.IsWorkZone(JCResto+x+120, y, JCResto+329 / (resizeGuiRate * resizeGuiScaleRateX), 72 / (resizeGuiRate * resizeGuiScaleRateY), true)) 
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
		x = x < JCResto-220 ? JCResto-220 : x;
		x = x > JCResto+260 ? JCResto+260 : x;
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

	float WindowW = 420;
	float WindowH = 300;
	float StartBody = 80.0;
	float StartY = 60;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float InfoMocNapX = (StartX + 10) + 3;
	float InfoMocNapY = (StartY + 15);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, (JCResto + x - 399 + MainWidth), y - 3, 405, 260, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, (JCResto + x - 300 + MainWidth), y + 16, 210, 3, gCustomMessage.GetMessage(106));
		gInterface.DrawGUI2(OBJECT_DAILY_SYSTEM_CLOSE, JCResto + x - 20 + MainWidth, y + 13);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, JCResto + x - 20 + MainWidth, y + 14, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		// ----
		if (gInterface.IsWorkZone(OBJECT_DAILY_SYSTEM_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(OBJECT_DAILY_SYSTEM_CLOSE, gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].X, gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].Y, Color);
		}
	}
	else
	{
		RenderBitmap(61322, (JCResto + x - 396 + MainWidth), y - 8, 395, 350, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, (JCResto + x - 396 + MainWidth), y - 8, 395, 41, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, (JCResto + x - 302 + MainWidth), y + 10, 210, 3, gCustomMessage.GetMessage(106));
		gInterface.DrawGUI2(OBJECT_DAILY_SYSTEM_CLOSE, JCResto + x - 34 + MainWidth, y - 8);
		if (gInterface.IsWorkZone(OBJECT_DAILY_SYSTEM_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(OBJECT_DAILY_SYSTEM_CLOSE, gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].X, gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].Y, Color);
		}
	}

	glAlphaFunc(GL_GREATER, 0.25f);

	if (_Title->Enable)
	CustomFont.Draw(_Title->Bold ? CustomFont.FontBold : CustomFont.FontNormal, JCResto+x, y + 12, _Title->Color, _Title->Background, w, 0, 3, _Title->Title);


	char* DoW[] = { "LUNES", "MARTES", "MIERCOL", "JUEVES", "VIERNES", "SABADO", "DOMINGO" };

	float sW = 35, sH = 38;
	int i, v1, v2, v3, v4, v5;
	v3 = this->FWday;
	v4 = this->MaxDay;

	for (i = 0; i < 7; i++)
	{
		CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 15 + sW * i, y + 35, 0xffffffff, 0xc1c1c150, sW - 2, 0, 3, DoW[i]);
	}

	float SizeButtonW = 45;
	float SizeButtonH = 29;

	if (Loaded)
	{
		for (i = v3; i < (v3 + v4); i++)
		{
			v1 = i % cDR_SPLIT_DAY;
			v2 = (i - v1) / cDR_SPLIT_DAY;
			v5 = i - v3 + 1;
			//
			if (SelectedDay == v5)
			{
				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 15 + sW * v1, y + 52 + v2 * sH, 0xffffffff, 0x00ff007f, sW - 2, sH - 2, 3, " ");
			}
			if (SelectedDay == v5 && State[v5 - 1] == 0)
			{
				RenderBitmap(531020, JCResto + x + 5 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0);
				//RenderBitmap1(178, x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				//RenderBitmap(531020, JCResto+x + 5 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
			//else if (IsWorkZone(JCResto+x + 15 + sW * v1, y + 52 + v2 * sH, sW - 2, sH - 2, true))
			else if (CheckMouseIn(JCResto+x + 15 + sW * v1, y + 52 + v2 * sH, sW - 2, sH - 2))
			{
				RenderBitmap(531020, JCResto + x + 5 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0);
				//RenderBitmap1(178, x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				//RenderBitmap(531020,JCResto+ x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
                if (GetAsyncKeyState(VK_LBUTTON))
                {
                    SelectedDay = v5;
                    if (State[v5 - 1] == 0)
                    {
                        this->SendRequest(0x01, SelectedDay);
                        this->ClearDayGift();
                    }
                }
			}
			else if (State[v5 - 1] == 0) //
			{
				RenderBitmap(531020, JCResto + x + 5 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0);
				//RenderBitmap1(178, x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				//RenderBitmap(531020, JCResto+ x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
			else
			{
				RenderBitmap(531021,   JCResto+ x + 5 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, SizeButtonW, SizeButtonH, 0.0, 0.0, 0.8785000443, 0.6409999728, 1, 1, 0);
				//RenderBitmap1(179, x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
				//RenderBitmap(531021, JCResto+ x + 7 + sW * v1 + (sW - 16) / 2, y + 48 + v2 * sH, 45, 45, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
			}
			//CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 15 + sW * v1, y + 52 + v2 * sH + sH - 13, 0xffffffff, (v5) != today.tm_mday ? 0x00000050 : 0x00ff007f, sW - 2, 12, 3, "%d", v5);
			CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 15 + sW * v1, y + 52 + v2 * sH + sH - 13, 0xffffffff, (v5) != gObjUser.m_TodayDaily ? 0x00000050 : 0x00ff007f, sW - 2, 12, 3, "%d", v5);
		}

		if (SelectedDay != 0)
		{
			if (State[SelectedDay - 1] != 0)
			{
				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 260, y + 50, 0xffffffff, 0x00000050, 130, 0, 3, "Complete", Wcoin);
			}
			else if (DayInfo)
			{
				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 260, y + 50, 0xffffffff, 0x00000050, 130, 0, 3, "Wcoin : %d", Wcoin);
				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 260, y + 65, 0xffffffff, 0x00000050, 130, 0, 3, "Zen : %d", Zen);

				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 260, y + 80, 0xffffffff, 0x00ff007f, 130, 0, 3, Text);

				//if (SelectedDay <= today.tm_mday)
				if (SelectedDay <= gObjUser.m_TodayDaily)
				{
					this->DrawButton(0x79346, JCResto + x - 5 + 75 * 4, y + h - 50, 73, 27, 128.0, 128.0, DailyReward.RecvGiftAction);
					if ((GetTickCount() - gInterface.Data[eTIME].EventTick) > 4000)
					{
						if (gElemental.gDrawButton(JCResto + x - 5 + 75 * 4, y + h - 50, 120, 11, "Recibir", 70) && (GetTickCount() - gInterface.Data[eTIME].EventTick) > 4000)
						{

						}
					}
				}

				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 280, y + 100, 0xffffffff, 0x00000050, 90, 90, 3, " ");

				gInterface.DrawItem(JCResto+x + 280, y + 100, 90, 90, this->Type, this->Level, this->Ex, 0, 0);


				if (IsWorkZone(JCResto+x + 280, y + 100, 90, 90, true))
				{
					gInterface.DrawItemToolTipText((void*)&Item, *(int*)0x879340C, *(int*)0x8793410 + 25);
					glColor3f(1, 1, 1);
					pSetBlend(false);
				}
			}
			else
			{
				CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 260, y + 50, 0xffffffff, 0x00000050, 130, 0, 3, "No Data...", Wcoin);
			}
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontNormal, JCResto+x + 60, y + 50, 0xffffffff, 0x00000050, 200, 0, 3, "No Data...");
	}
	
}

bool cDailyReward::AllowedGift()
{
	return Loaded && State[SelectedDay - 1] == 0 && SelectedDay <= CurDay;
}
void cDailyReward::SendRequest(BYTE type, int value)
{
	PMSG_DAILY_REWARD_SEND pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFF, 0x02, sizeof(pRequest));
	pRequest.Type = type;
	pRequest.Value = value;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}

void cDailyReward::RecvGiftAction(LPVOID pClass)
{
	cDailyReward* This = (cDailyReward*)pClass;

	if (This->AllowedGift())
	{
		This->SendRequest(0x02, This->SelectedDay);
		gInterface.Data[eMAIN_DailySystem].OnShow = false;
	}
}

void cDailyReward::OnOpen()
{
	this->Loaded = false;
	this->DayInfo = false;
	this->SendRequest(0x0, 0x0);

}
void cDailyReward::OnClose()
{
}

void cDailyReward::ToggleWindow(bool mode)
{
	SetWindow(!CheckWindow(), mode);
	gInterface.Data[eMAIN_DailySystem].Open();
	
}
void cDailyReward::OpenWindow(bool mode)
{
	SetWindow(true, mode);
	
}
void cDailyReward::CloseWindow(bool mode)
{
	SetWindow(false, mode);
	
}
void cDailyReward::SetWindow(bool state, bool mode)
{
	this->Drawing = state;
	if (mode)
		CheckWindow() ? OnOpen() : OnClose();
}

void cDailyReward::GCRecvUserInfo(BYTE* a)
{
	PMSG_DAILY_REWARD_USER_INFO_RECV* Data = (PMSG_DAILY_REWARD_USER_INFO_RECV*)a;
	this->CurDay = Data->CurDay;
	this->MaxDay = Data->MaxDay;
	this->FWday = Data->FWday;
	this->Timer = Data->Timer;

	for (int i = 0; i < 31; i++)
	{
		this->State[i] = Data->State[i];
	}

	if (State[CurDay - 1] == 0)
	{
		Blink = true;
	}
	else
	{
		Blink = false;
	}

	Loaded = true;
}
int cDailyReward::CheckItemInfo(signed int a1)
{
	if (a1 > 3092)
	{
		if (a1 > 4661)
		{
			if (a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173))
				return 0;
		}
		else if (a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)))
		{
			return 0;
		}

		return 1;
	}

	if (a1 >= 3089)
		return 1;

	if (a1 > 2071)
	{
		if (a1 != 2580 && (a1 <= 2589 || a1 > 2592))
			return 0;
		return 1;
	}

	if (a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28))
		return 1;

	return 0;
}

void cDailyReward::GCRecvDayInfo(BYTE* a)
{
	PMSG_DAILY_REWARD_DAY_INFO_RECV* Data = (PMSG_DAILY_REWARD_DAY_INFO_RECV*)a;

	DayInfo = true;
	if (Data->Type != -1)
	{
		this->Type = Data->Type;

		DWORD dwAddress;
		int a5;
		int a6;
		int a7;
		int a8;
		int a9;
		DWORD a10;

		dwAddress = (DWORD)&this->Item;

		*(WORD *)dwAddress = Data->Type;
		a5 = Data->Dur;
		*(BYTE *)(dwAddress + 22) = a5;
		a6 = Data->Item[3];
		*(BYTE *)(dwAddress + 23) = a6;
		a7 = Data->Item[4];
		*(BYTE *)(dwAddress + 24) = a7;
		a8 = Data->Item[5];
		*(BYTE *)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
		*(BYTE *)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
		*(BYTE *)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
		a9 = Data->Item[6];
		*(WORD *)(dwAddress + 69) = (a9 & 0xF0) >> 4;
		*(WORD *)(dwAddress + 71) = a9 & 0xF;

		a10 = (DWORD)&Data->Item[7];

		if (a10)
		{
			*(BYTE *)(dwAddress + 79) = 5;

			for (int i = 0; i < 5; ++i)
				*(BYTE *)(i + dwAddress + 74) = *(BYTE *)(i + a10);

			for (int j = 0; j < 5; ++j)
			{
				if (*(BYTE *)(j + a10) == 255)
				{
					*(BYTE *)(dwAddress + 79) = j;
					break;
				}

				if (*(BYTE *)(j + a10) == 254)
				{
					*(BYTE *)(j + dwAddress + 80) = -1;
				}
				else
				{
					*(BYTE *)(j + dwAddress + 80) = *(BYTE *)(j + a10) % 50;
					*(BYTE *)(j + dwAddress + 85) = *(BYTE *)(j + a10) / 50 + 1;
				}
			}

			if (this->CheckItemInfo(*(WORD *)dwAddress))
			{
				*(BYTE *)(dwAddress + 90) = a9;
				*(WORD *)(dwAddress + 69) = 0;
				*(WORD *)(dwAddress + 71) = 0;
			}
			else
			{
				*(BYTE *)(dwAddress + 90) = -1;
			}
		}
		else
		{
			*(BYTE *)(dwAddress + 79) = 0;
		}

		*(BYTE *)(dwAddress + 96) = 0;
		*(DWORD *)(dwAddress + 103) = 1;

		if (Data->PeriodTime)
		{
			this->Item.PeriodItem = 1;
			this->Item.ExpireDateConvert = Data->PeriodTime;
		}

		((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)(&this->Item, Data->Item[1], Data->Item[3], Data->Item[4]);
	}
	this->Zen = Data->Zen;
	this->Wcoin = Data->Wcoin;
	memcpy_s(Text, 100, Data->Text, 100);
}
int cDailyReward::Button(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].EventTick);
	if (!gInterface.Data[eMAIN_DailySystem].OnShow || !gInterface.IsWorkZone(OBJECT_DAILY_SYSTEM_CLOSE))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].OnClick = true;
		return true;
	}
	gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	gInterface.Data[OBJECT_DAILY_SYSTEM_CLOSE].EventTick = GetTickCount();
	this->CloseJewelWindow();
	return false;
}
#endif