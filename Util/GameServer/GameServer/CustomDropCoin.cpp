// CustomDropCoin.cpp: implementation of the CCustomDropCoin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomDropCoin.h"
#include "BonusManager.h"
#include "CrywolfSync.h"
#include "DSProtocol.h"
#include "Map.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Monster.h"
#include "RandomManager.h"
#include "ServerInfo.h"
#include "Util.h"
#include "CashShop.h"
#include "Message.h"
#include "Notice.h"

CCustomDropCoin gCustomDropCoin;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomDropCoin::CCustomDropCoin() // OK
{
	this->m_CustomDropCoinInfo.clear();
}

CCustomDropCoin::~CCustomDropCoin() // OK
{

}

void CCustomDropCoin::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_CustomDropCoinInfo.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_COIN_DROP_INFO info;

			memset(&info,0,sizeof(info));

			info.MapNumber = lpMemScript->GetNumber();

			info.MonsterClass = lpMemScript->GetAsNumber();

			info.MonsterLevelMin = lpMemScript->GetAsNumber();

			info.MonsterLevelMax = lpMemScript->GetAsNumber();

			info.Coin1 = lpMemScript->GetAsNumber();

			info.Coin2 = lpMemScript->GetAsNumber();

			info.Coin3 = lpMemScript->GetAsNumber();

			info.Ruud = lpMemScript->GetAsNumber();

			this->m_CustomDropCoinInfo.push_back(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}


void CCustomDropCoin::AddMonsterBonus(LPOBJ lpMonster, LPOBJ lpObj)
{
	CRandomManager RandomManager;

	for(std::vector<CUSTOM_COIN_DROP_INFO>::iterator it=this->m_CustomDropCoinInfo.begin();it != this->m_CustomDropCoinInfo.end();it++)
	{
		if(it->MapNumber != -1 && it->MapNumber != lpObj->Map)
		{
			continue;
		}

		if(it->MonsterClass != -1 && it->MonsterClass != lpObj->Class)
		{
			continue;
		}

		if(it->MonsterLevelMin != -1 && it->MonsterLevelMin > lpObj->Level)
		{
			continue;
		}

		if(it->MonsterLevelMax != -1 && it->MonsterLevelMax < lpObj->Level)
		{
			continue;
		}

		if (OBJECT_RANGE(lpObj->PartyNumber) != 0)
		{
				PARTY_INFO* lpParty = &gParty.m_PartyInfo[lpObj->PartyNumber];

				for(int n=0;n < MAX_PARTY_USER;n++)
				{
					if (OBJECT_RANGE(lpParty->Index[n]) != 0 && lpObj->Index != lpParty->Index[n])
					{
						if(lpObj->Map == gObj[lpParty->Index[n]].Map && gObjCalcDistance(lpObj,&gObj[lpParty->Index[n]]) < MAX_PARTY_DISTANCE)
						{
							if (it->Coin1 > 0)
							{
								gObj[lpParty->Index[n]].Coin1 = it->Coin1;
							}
							else if (it->Coin2 > 0)
							{
								gObj[lpParty->Index[n]].Coin2 = it->Coin2;
							}
							else if (it->Coin3 > 0)
							{
								gObj[lpParty->Index[n]].Coin3 = it->Coin3;
							}
							else if (it->Ruud > 0)
							{
								gObj[lpParty->Index[n]].Ruud = it->Ruud;
							}

							gCashShop.GDCashShopAddPointSaveSend(lpParty->Index[n],0, it->Coin1, it->Coin2, it->Coin3,it->Ruud);
				
							gCashShop.CGCashShopPointRecv(lpParty->Index[n]);

							this->SendNotify(lpParty->Index[n],it->Coin1, it->Coin2, it->Coin3,it->Ruud, gMessage.GetMessage(800));
						}
					}
				}
		}
		
		gCashShop.GDCashShopAddPointSaveSend(lpObj->Index,0, it->Coin1, it->Coin2, it->Coin3,it->Ruud);
		// ----
		gCashShop.CGCashShopPointRecv(lpObj->Index);

		// ----
		this->SendNotify(lpObj->Index,it->Coin1, it->Coin2, it->Coin3,it->Ruud, gMessage.GetMessage(801));
				

	}

	return;
}
// -------------------------------------------------------------------------------

void CCustomDropCoin::SendNotify(int UserIndex, int Coin1, int Coin2, int Coin3, int Ruud, char* Text)
{
	// ----
	if( Coin1 > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(802), Text, Coin1);
	}
	// ----
	if( Coin2 > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(803), Text, Coin2);
	}
	// ----
	if( Coin3 > 0 )
	{
		gNotice.GCNoticeSend(UserIndex,1,0,0,0,0,0,gMessage.GetMessage(804), Text, Coin3);
	}
	if (Ruud > 0)
	{
		gNotice.GCNoticeSend(UserIndex, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(805), Text, Ruud);
	}
}