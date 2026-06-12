#include "stdafx.h"
#include "EventInvasion.h"
#include "CustomMessage.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "Util.h"
#include "Object.h"
#include "Import.h"
#include "Character.h"
#include "CNewUIWindowsClient.h"
#include "CustomMonster.h"
#include "SEASON3B.h"
#include "InterfaceElemental.h"
#include "Protect.h"
#include "Common.h"
#include "Antilag.h"

EventInvasion gEventInvasion;


int CloseInvasion;
int NextInvasion;
int PrewInvasion;

EventInvasion::EventInvasion()
{
	gInterface.Data[eINVASION_NextEvent].EventTick = GetTickCount();
	gInterface.Data[eINVASION_PrevEvent].EventTick = GetTickCount();
}

void EventInvasion::ImageLoad()
{
}

void EventInvasion::BinObeject()
{
	gInterface.BindObject(eINVASION_MAIN, 31461, 190, 50, -1, -1);
	gInterface.BindObject(eINVASION_MAIN_OPEN, 31461, 110, 15, -1, -1);
	gInterface.BindObject(eINVASION_NextEvent, 31659, 22, 20, -1, -1);
	gInterface.BindObject(eINVASION_PrevEvent, 31658, 22, 20, -1, -1);
}
void EventInvasion::OpenMain()
{
	if (gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(ExpandWarehouse)
		|| gInterface.CheckWindow(MuHelper)
		|| gInterface.CheckWindow(Quest)
		|| gInterface.CheckWindow(NPC_Devin)
		|| gInterface.CheckWindow(DevilSquare)
		|| gInterface.CheckWindow(GuardNPC)
		|| gInterface.CheckWindow(CastleGateSwitch)
		|| gInterface.CheckWindow(GoldenArcher2)
		|| gInterface.CheckWindow(LuckyCoin1)
		|| gInterface.CheckWindow(LuckyCoin2)
		|| gInterface.CheckWindow(BloodCastle))
	{
		return;
	}

	bool check = false;

	for (int i = 0; i < MAX_INVASION; i++)
	{
		if (this->m_Info[i].State == 2)
		{
			check = true;
		}
	}

	if (ButtonActive == 0)
	{
		if (check)
		{
			float Active_x;

			if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				Active_x = (MAX_WIN_WIDTH / 2) - 40;
			}
			else
			{
				Active_x = (640 / 2) - 40;
			}
			nInterface.ACTIVE_INVASION_WINDOW->onShow = true;
			float Active_y = 2;
			//gInterface.DrawButtonRender(eINVASION_MAIN_OPEN, Active_x, Active_y, 0, 0);

			if (pCheckMouseOver(Active_x, Active_y, 110.0, 20.0))
			{
				nInterface.ActiveLockMouse = GetTickCount() + 500;
			}

			gElemental.gDrawButton(Active_x, Active_y, 80, 12, gCustomMessage.GetMessage(16));

			if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				if (pCheckInMouse((MAX_WIN_WIDTH / 2) - 40, 2, 83, 20.0) && IsRelease(VK_LBUTTON)) //
				{
					gInterface.Data[eINVASION_MAIN].OnShow = true;
					nInterface.ACTIVE_INVASION_WINDOW->onShow = true;
					//this->Page = 0;
				}
			}
			else
			{
				if (pCheckInMouse((640 / 2) - 40, 2, 83, 20.0) && IsRelease(VK_LBUTTON)) //
				{
					gInterface.Data[eINVASION_MAIN].OnShow = true;
					nInterface.ACTIVE_INVASION_WINDOW->onShow = true;
					//this->Page = 0;
				}
			}
			
		}
		else
		{
			nInterface.ACTIVE_INVASION_WINDOW->onShow = false;
			gInterface.Data[eINVASION_MAIN].OnShow = false;
		}
	}
}

void EventInvasion::Draw()
{
	if (!gInterface.Data[eINVASION_MAIN].OnShow)
	{
		return;
	}
	
	if (!nInterface.ACTIVE_INVASION_WINDOW->onShow)
	{
		return;
	}


	if (gInterface.CheckWindow(Party)
		|| gInterface.CheckWindow(Guild)
		//|| gInterface.CheckWindow(MoveList)
		|| gInterface.CheckWindow(Trade)
		|| gInterface.CheckWindow(Warehouse)
		|| gInterface.CheckWindow(ChaosBox)
		|| gInterface.CheckWindow(CommandWindow)
		|| gInterface.CheckWindow(PetInfo)
		|| gInterface.CheckWindow(Shop)
		//|| gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Store)
		|| gInterface.CheckWindow(OtherStore)
		//|| gInterface.CheckWindow(Character)
		|| gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(SkillTree)
		|| gInterface.CheckWindow(NPC_Titus)
		|| gInterface.CheckWindow(CashShop)
		|| gInterface.CheckWindow(FullMap)
		|| gInterface.CheckWindow(NPC_Dialog)
		|| gInterface.CheckWindow(GensInfo)
		|| gInterface.CheckWindow(NPC_Julia)
		|| gInterface.CheckWindow(ExpandInventory)
		|| gInterface.CheckWindow(ExpandWarehouse)
		|| gInterface.CheckWindow(MuHelper)
		|| gInterface.CheckWindow(Quest)
		|| gInterface.CheckWindow(NPC_Devin)
		|| gInterface.CheckWindow(DevilSquare)
		|| gInterface.CheckWindow(GuardNPC)
		|| gInterface.CheckWindow(CastleGateSwitch)
		|| gInterface.CheckWindow(GoldenArcher2)
		|| gInterface.CheckWindow(LuckyCoin1)
		|| gInterface.CheckWindow(LuckyCoin2)
		|| gInterface.CheckWindow(BloodCastle))
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		nInterface.DrawWindowActiveInvasionEX700(nInterface.ACTIVE_INVASION_WINDOW, "", 157);
	}
	else
	{
		nInterface.DrawWindowActiveInvasion(nInterface.ACTIVE_INVASION_WINDOW, "", 157);
	}
	
	float StartX = nInterface.ACTIVE_INVASION_WINDOW->X;
	float StartY = nInterface.ACTIVE_INVASION_WINDOW->Y;
	float WindowW = nInterface.ACTIVE_INVASION_WINDOW->Width;
	float WindowH = nInterface.ACTIVE_INVASION_WINDOW->Height;

	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if ((nInterface.ACTIVE_INVASION_WINDOW->X == -1))
		{
			StartX = (MAX_WIN_WIDTH / 2) - (nInterface.ACTIVE_INVASION_WINDOW->Width / 2);
		}
	}
	else
	{
		if ((nInterface.ACTIVE_INVASION_WINDOW->X == -1))
		{
			StartX = (640 / 2) - (nInterface.ACTIVE_INVASION_WINDOW->Width / 2);
		}
	}

	//gElemental.gInfoBox(StartX, StartY, 200, 250, 0x00000096, 0, 0);
		//---------------------------------------------------------------------------------------------------------------------------------------------------------------

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartY += 10;
	}

		if (this->Page < this->Count - 1)
		{
			gInterface.DrawGUI(eINVASION_NextEvent, StartX + 130, StartY + 5);
			//RenderBitmap(31659, StartX + 90, StartY + 18, 17, 18, 0, 0, 1.0, 1.0, true, true, 0.0);
			//gInterface.DrawGUI(eNextMenu, StartX + 165, StartY + 21);
			if (pCheckInMouse(StartX + 130, StartY + 5, 22, 20) && IsRelease(VK_LBUTTON) && GetTickCount() - gInterface.Data[eINVASION_NextEvent].EventTick > 500) //-- next
			{
				gInterface.Data[eINVASION_NextEvent].EventTick = GetTickCount();
				if (this->Page < this->Count - 1)
				{
					PlayBuffer(25, 0, 0);
					this->Page++;
				}
			}
		}

		if (this->Page > 0)
		{
			gInterface.DrawGUI(eINVASION_PrevEvent, StartX+ 30, StartY + 5);
			//RenderBitmap(31658, StartX + 30, StartY + 18, 17, 18, 0, 0, 1.0, 1.0, true, true, 0.0);
			//gInterface.DrawGUI(ePrevMenu, StartX + 10, StartY + 21);
			if (pCheckInMouse(StartX + 30, StartY + 5, 22, 20) && IsRelease(VK_LBUTTON) && GetTickCount() - gInterface.Data[eINVASION_PrevEvent].EventTick > 500) //-- prew
			{
				gInterface.Data[eINVASION_PrevEvent].EventTick = GetTickCount();
				if (this->Page > 0)
				{
					PlayBuffer(25, 0, 0);
					this->Page--;
				}
			}
		}
		//
		int ContenX = StartX + 50 - 90;
		int ContenY = (int)StartY - 20;

		int tmp = 0;

		for (int i = 0; i < MAX_INVASION; i++)
		{
			if (this->m_Info[i].State == 2 && this->m_Info[i].Page == this->Page)
			{
				EVENT_INVASION_ACTION pRequest;
				pRequest.h.set(0xD3, 0x4C, sizeof(pRequest));
				pRequest.index = this->m_Info[i].Index;
				DataSend((BYTE*)& pRequest, pRequest.h.size);
				
				char text2[30];
				int totalseconds;
				int hours;
				int minutes;
				int seconds;
				int days;
				totalseconds = this->m_Info[i].RemainTime;
				hours = totalseconds / 3600;
				minutes = (totalseconds / 60) % 60;
				seconds = totalseconds % 60;

				if (hours > 23)
				{
					days = hours / 24;
					wsprintf(text2, "%d day(s)+", days);
				}
				else
				{
					wsprintf(text2, "(%02d:%02d:%02d)", hours, minutes, seconds);
				}
				ContenY += 30; // for move up or down the text
				gInterface.DrawFormat(eGold, ContenX + 105 - 25, ContenY -3, 100, 3, "%s", this->m_Info[i].NameInvasion);
				gInterface.DrawFormat(eExcellent,ContenX + 105 - 25, ContenY + 4, 100, 3, "%s", text2);


				for (int j = 0; j < 20; j++)
				{
					if (this->m_Monter[j].Class > 0)
					{
						if (this->m_Monter[j].RegenType == 1 && this->m_Monter[j].Count == 0)
						{
							char text3[30];
							int totalseconds2;
							int hours2;
							int minutes2;
							int seconds2;
							int days2;
							totalseconds2 = this->m_Monter[j].RegenTime / 1000;
							hours2 = totalseconds2 / 3600;
							minutes2 = (totalseconds2 / 60) % 60;
							seconds2 = totalseconds2 % 60;

							if (hours2 > 23)
							{
								days2 = hours2 / 24;
								wsprintf(text3, "%d day(s)+", days2);
							}
							else
							{
								wsprintf(text3, "(%02d:%02d:%02d)", hours2, minutes2, seconds2);
							}

							//gInterface.DrawFormat(eOrange, ContenX + 105 - 45, ContenY + 33 + (j * 10), 200, 1, "-%s (%d/%d) lượt tiếp theo sau: %s", this->m_Monter[j].Name, this->m_Monter[j].Count, this->m_Monter[j].CountMax, text3);
							gInterface.DrawFormat(eOrange, ContenX + 105 - 45, ContenY + 33 + (j * 10), 200, 1, "-%s (%d/%d) Next turn: %s", pGetMonsterName(this->m_Monter[j].Class), this->m_Monter[j].Count, this->m_Monter[j].CountMax, text3);

						}
						else
						{
							if (this->m_Monter[j].Count == 0)
							{
								gInterface.DrawFormat(eGray100, ContenX + 105 - 45, ContenY + 33 + (j * 10), 200, 1, "-%s (Killed)", pGetMonsterName(this->m_Monter[j].Class), this->m_Monter[j].Count, this->m_Monter[j].CountMax);
							}
							else
							{
								gInterface.DrawFormat(eWhite, ContenX + 105 - 45, ContenY + 33 + (j * 10), 200, 1, "-%s (%d/%d)", pGetMonsterName(this->m_Monter[j].Class), this->m_Monter[j].Count, this->m_Monter[j].CountMax);
								//gInterface.DrawMessage(1, "-%s", this->m_Monter[j].Name);
							}

							if (pCheckMouseOver(ContenX + 105 - 45, ContenY + 33 + (j * 10), 190, 10) && this->m_Monter[j].Count != 0)
							{
								if (pCheckMouseOver(ContenX + 105 - 45, ContenY + 33 + (j * 10), 190, 10) && this->m_Monter[j].Count != 0)
								{
								
								float x1 = drawx + 200;
								float y1 = (int)ContenY + 33;

								gElemental.gInfoBox(ContenX + 105 - 5+120, ContenY + 33 + (j * 10), 90, 150, 0x00000096, 0, 0);
								character.DrawMonster(ContenX + 105 +125, ContenY + 33 + (j * 10)  ,80, 140 ,oMonster1 + (j * 10) + (this->Page + this->m_Info[i].Index), this->m_Monter[j].Class, 0.5);
								gInterface.DrawFormat(eGold, ContenX + 105 - 45, ContenY + 33 + (j * 10), 200, 1, "-%s (%d/%d)", pGetMonsterName(this->m_Monter[j].Class), this->m_Monter[j].Count, this->m_Monter[j].CountMax);
							}
						}
					}
				}

			}
		}
	}
}

void EventInvasion::GCListEvent(PMSG_INVASION_INFO* lpMsg)
{
	this->Count = 0;
	memset(this->m_Info, 0, sizeof(this->m_Info));
	for (int i = 0; i < MAX_INVASION; i++)
	{
		this->m_Info[i].Index = lpMsg->Info[i].Index;
		this->m_Info[i].State = lpMsg->Info[i].State;
		this->m_Info[i].RemainTime = lpMsg->Info[i].RemainTime;
		memcpy(this->m_Info[i].NameInvasion, lpMsg->Info[i].NameInvasion, 32);
		this->m_Info[i].Page = lpMsg->Info[i].Page;
		if (lpMsg->Info[i].State == 2)
		{
			this->Count++;
		}
	}
}

void EventInvasion::GCListMonter(PMSG_INVASION_INFO_MONTER* lpMsg)
{
	int tmp = 0;
	for (int i = 0; i < 20; i++)
	{
		this->m_Monter[i].Class = lpMsg->Info[i].Class;
		this->m_Monter[i].Count = lpMsg->Info[i].Count;
		this->m_Monter[i].CountMax = lpMsg->Info[i].CountMax;
		this->m_Monter[i].RegenTime = lpMsg->Info[i].RegenTime;
		this->m_Monter[i].RegenType = lpMsg->Info[i].RegenType;
		if (this->m_Monter[i].Class > 0)
		{
			tmp++;
		}
	}
	this->HightFix = tmp;
}

bool EventInvasion::EventActiveInvasion_CLOSE(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eINVASION_CLOSE].EventTick);
	// ----
	if (!gInterface.Data[eINVASION_MAIN].OnShow || !gInterface.IsWorkZone(eINVASION_CLOSE))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eINVASION_CLOSE].OnClick = true;
		return true;
	}
	// ----
	gInterface.Data[eINVASION_CLOSE].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	gInterface.Data[eINVASION_CLOSE].EventTick = GetTickCount();
	gInterface.Data[eINVASION_MAIN].Close();
	// ----
	return false;
}