#include "stdafx.h"
#include "PKNotice.h"
#include "CustomMessage.h"
#include "Defines.h"
#include "Interface.h"
#include "Util.h"
#include "Object.h"
#include "Import.h"
#include "SEASON3B.h"
#include "CustomFont.h"
#include "PartyBar.h"
#include "Protect.h"

PKNotice gPKNotice;

PKNotice::PKNotice()
{
	this->m_DataNoticePK.clear();
}

void PKNotice::DrawNoticePKSystem()
{
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
		|| gInterface.CheckWindow(ObjWindow::MuHelper))
	{
		return;
	}

	if (this->m_DataNoticePK.empty()) return;

	for (int i = 0; i < this->m_DataNoticePK.size(); i++)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			float StartXText = MAX_WIN_WIDTH - ((QTPary.PartyMemberCount > 0) ? 260 : 185) + this->m_DataNoticePK[i].Delay;
			CustomFont.Draw(CustomFont.FontNormal, StartXText, 30 + 15 * i, this->m_DataNoticePK[i].Color, 0x00000000A5, 180.0, 0, 3, this->m_DataNoticePK[i].Mess);
			if (this->m_DataNoticePK[i].Time <= GetTickCount())
			{
				if (StartXText > MAX_WIN_WIDTH)
				{
					this->m_DataNoticePK.erase(this->m_DataNoticePK.begin() + i);
				}
				else
				{
					this->m_DataNoticePK[i].Delay += 5;
				}
			}
		}
		else
		{
			float StartXText = 640 - ((QTPary.PartyMemberCount > 0) ? 260 : 185) + this->m_DataNoticePK[i].Delay;
			CustomFont.Draw(CustomFont.FontNormal, StartXText, 30 + 15 * i, this->m_DataNoticePK[i].Color, 0x00000000A5, 180.0, 0, 3, this->m_DataNoticePK[i].Mess);
			if (this->m_DataNoticePK[i].Time <= GetTickCount())
			{
				if (StartXText > 480)
				{
					this->m_DataNoticePK.erase(this->m_DataNoticePK.begin() + i);
				}
				else
				{
					this->m_DataNoticePK[i].Delay += 5;
				}
			}
		}
	}
}