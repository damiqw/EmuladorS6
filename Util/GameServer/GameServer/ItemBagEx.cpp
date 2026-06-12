// ItemBagEx.cpp: implementation of the CItemBagEx class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemBagEx.h"
#include "DSProtocol.h"
#include "ItemOptionRate.h"
#include "Log.h"
#include "Map.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"
#include "Party.h"
#include "RandomManager.h"
#include "SetItemType.h"
#include "Util.h"
#include "CashShop.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemBagEx::CItemBagEx() // OK
{
	this->m_ItemBagInfo.clear();

	this->m_ItemBagItemInfo.clear();
}

void CItemBagEx::Load(char* path) // OK
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

	this->m_ItemBagInfo.clear();

	this->m_ItemBagItemInfo.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 3)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					ITEM_BAG_EX_INFO info;

					info.Index = lpMemScript->GetNumber();

					info.MapNumber = lpMemScript->GetAsNumber();

					info.m_ItemRate = lpMemScript->GetAsNumber();

					info.m_MoneyDrop = lpMemScript->GetAsNumber();

					info.m_BagUseEffect = lpMemScript->GetAsNumber();

					info.m_RewardType = lpMemScript->GetAsNumber();

					info.WCoinCMin = lpMemScript->GetAsNumber();

					info.WCoinCMax = lpMemScript->GetAsNumber();

					info.WCoinPMin = lpMemScript->GetAsNumber();

					info.WCoinPMax = lpMemScript->GetAsNumber();

					info.GoblinPMin = lpMemScript->GetAsNumber();

					info.GoblinPMax = lpMemScript->GetAsNumber();

					info.RuudMin = lpMemScript->GetAsNumber();

					info.RuudMax = lpMemScript->GetAsNumber();

					this->m_ItemBagInfo.insert(std::pair<int, ITEM_BAG_EX_INFO>(info.Index, info));

				}
				else if(section == 4)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					ITEM_BAG_EX_DROP_INFO info;

					info.Index = lpMemScript->GetNumber();

					info.Section = lpMemScript->GetAsNumber();

					info.SectionRate = lpMemScript->GetAsNumber();

					info.SetDropRate = lpMemScript->GetAsNumber();

					info.MinDropCount = lpMemScript->GetAsNumber();

					info.MaxDropCount = lpMemScript->GetAsNumber();

					for(int n=0;n < MAX_CLASS;n++){info.RequireClass[n] = lpMemScript->GetAsNumber();}

					std::map<int,ITEM_BAG_EX_INFO>::iterator it = this->m_ItemBagInfo.find(info.Index);

					if(it != this->m_ItemBagInfo.end())
					{
						it->second.DropInfo.push_back(info);
					}
				}
				else if(section >= 5)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					ITEM_BAG_EX_ITEM_INFO info;

					memset(&info,0,sizeof(info));

					info.ItemIndex = lpMemScript->GetNumber();

					info.Level = lpMemScript->GetAsNumber();

					info.Durability = lpMemScript->GetAsNumber();

					info.Option0 = lpMemScript->GetAsNumber();

					info.Option1 = lpMemScript->GetAsNumber();

					info.Option2 = lpMemScript->GetAsNumber();

					info.Option3 = lpMemScript->GetAsNumber();

					info.Option4 = lpMemScript->GetAsNumber();

					info.Option5 = lpMemScript->GetAsNumber();

					#if(GAMESERVER_UPDATE>=401)

					info.Option6 = lpMemScript->GetAsNumber();

					info.Duration = lpMemScript->GetAsNumber();

					#endif

					std::map<int,std::vector<ITEM_BAG_EX_ITEM_INFO>>::iterator it = this->m_ItemBagItemInfo.find(section);

					if(it == this->m_ItemBagItemInfo.end())
					{
						this->m_ItemBagItemInfo.insert(std::pair<int,std::vector<ITEM_BAG_EX_ITEM_INFO>>(section,std::vector<ITEM_BAG_EX_ITEM_INFO>(1,info)));
					}
					else
					{
						it->second.push_back(info);
					}
				}
				else
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CItemBagEx::GetItem(LPOBJ lpObj,CItem* lpItem) // OK
{
	for(std::map<int,ITEM_BAG_EX_INFO>::iterator it = this->m_ItemBagInfo.begin(); it != this->m_ItemBagInfo.end(); it++)
	{
		if((GetLargeRand() % 10000) < it->second.m_ItemRate)
		{
			CRandomManager RandomManager;

			for(std::vector<ITEM_BAG_EX_DROP_INFO>::iterator DropInfo = it->second.DropInfo.begin(); DropInfo != it->second.DropInfo.end(); DropInfo++)
			{
				if(DropInfo->RequireClass[lpObj->Class] != 0 && DropInfo->RequireClass[lpObj->Class] <= (lpObj->ChangeUp+1))
				{
					RandomManager.AddElement((int)(&(*DropInfo)),DropInfo->SectionRate);
				}
			}

			ITEM_BAG_EX_DROP_INFO* lpItemBagDropInfo = 0;

			if(RandomManager.GetRandomElement((int*)&lpItemBagDropInfo) == 0)
			{
				return 0;
			}

			std::map<int,std::vector<ITEM_BAG_EX_ITEM_INFO>>::iterator ItemInfo = this->m_ItemBagItemInfo.find(lpItemBagDropInfo->Section);

			if(ItemInfo == this->m_ItemBagItemInfo.end())
			{
				return 0;
			}

			if(ItemInfo->second.empty() != 0)
			{
				return 0;
			}

			ITEM_BAG_EX_ITEM_INFO* lpItemBagItemInfo = &ItemInfo->second[GetLargeRand() % ItemInfo->second.size()];

			WORD ItemIndex = lpItemBagItemInfo->ItemIndex;
			BYTE ItemLevel = lpItemBagItemInfo->Level;
			BYTE ItemOption1 = 0;
			BYTE ItemOption2 = 0;
			BYTE ItemOption3 = 0;
			BYTE ItemNewOption = 0;
			BYTE ItemSetOption = 0;
			BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF,0xFF,0xFF,0xFF,0xFF };

			gItemOptionRate.GetItemOption0(lpItemBagItemInfo->Option0,&ItemLevel);

			gItemOptionRate.GetItemOption1(lpItemBagItemInfo->Option1,&ItemOption1);

			gItemOptionRate.GetItemOption2(lpItemBagItemInfo->Option2,&ItemOption2);

			gItemOptionRate.GetItemOption3(lpItemBagItemInfo->Option3,&ItemOption3);

			gItemOptionRate.GetItemOption4(lpItemBagItemInfo->Option4,&ItemNewOption);

			gItemOptionRate.GetItemOption5(lpItemBagItemInfo->Option5,&ItemSetOption);

			gItemOptionRate.GetItemOption6(lpItemBagItemInfo->Option6,&ItemSocketOption[0]);

			gItemOptionRate.MakeNewOption(ItemIndex,ItemNewOption,&ItemNewOption);

			gItemOptionRate.MakeSetOption(ItemIndex,ItemSetOption,&ItemSetOption);

			gItemOptionRate.MakeSocketOption(ItemIndex,ItemSocketOption[0],&ItemSocketOption[0]);

			lpItem->m_Level = ItemLevel;

			lpItem->m_Durability = (float)lpItemBagItemInfo->Durability;

			lpItem->Convert(ItemIndex,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,ItemSetOption,0,0,ItemSocketOption,0xFF);

			return 1;
		}
	}

	return 0;
}

bool CItemBagEx::DropItem(LPOBJ lpObj,int map,int x,int y) // OK
{
	DWORD CoinC;
	DWORD CoinP;
	DWORD GoblinP;
	DWORD Ruud;
	
	for (std::map<int, ITEM_BAG_EX_INFO>::iterator it = this->m_ItemBagInfo.begin(); it != this->m_ItemBagInfo.end(); it++)
	{
		if (it->second.m_RewardType != 0)
		{
			CoinC = (it->second.WCoinCMax > 0) ? it->second.WCoinCMin + rand() % ((it->second.WCoinCMax + 1) - it->second.WCoinCMin) : 0;

			CoinP = (it->second.WCoinPMax > 0) ? it->second.WCoinPMin + rand() % ((it->second.WCoinPMax + 1) - it->second.WCoinPMin) : 0;

			GoblinP = (it->second.GoblinPMax > 0) ? it->second.GoblinPMin + rand() % ((it->second.GoblinPMax + 1) - it->second.GoblinPMin) : 0;

			Ruud = (it->second.RuudMax > 0) ? it->second.RuudMin + rand() % ((it->second.RuudMax + 1) - it->second.RuudMin) : 0;

			gCashShop.GDCashShopAddPointSaveSend(lpObj->Index, 0, (CoinC > 0) ? CoinC : 0, (CoinP > 0) ? CoinP : 0, (GoblinP > 0) ? GoblinP : 0, (Ruud > 0) ? Ruud : 0);

			gCashShop.CGCashShopPointRecv(lpObj->Index);

			if (CoinC > 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(37), CoinC, gMessage.GetMessage(38));
			}

			if (CoinP > 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(37), CoinP, gMessage.GetMessage(39));
			}

			if (GoblinP > 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(37), GoblinP, gMessage.GetMessage(40));
			}

			if (Ruud > 0)
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(37), Ruud, gMessage.GetMessage(41));
			}


			if (it->second.m_RewardType != 2)
			{
				return 1;
			}
		}
	
	
		if(it->second.MapNumber != -1 && it->second.MapNumber != map)
		{
			continue;
		}

		if((GetLargeRand() % 10000) < it->second.m_ItemRate)
		{
			CRandomManager RandomManager;

			for(std::vector<ITEM_BAG_EX_DROP_INFO>::iterator DropInfo = it->second.DropInfo.begin(); DropInfo != it->second.DropInfo.end(); DropInfo++)
			{
				if(DropInfo->RequireClass[lpObj->Class] != 0 && DropInfo->RequireClass[lpObj->Class] <= (lpObj->ChangeUp+1))
				{
					RandomManager.AddElement((int)(&(*DropInfo)),DropInfo->SectionRate);
				}
			}

			ITEM_BAG_EX_DROP_INFO* lpItemBagDropInfo = 0;

			if(RandomManager.GetRandomElement((int*)&lpItemBagDropInfo) == 0)
			{
				continue;
			}

			int DropCount = (lpItemBagDropInfo->MinDropCount+(GetLargeRand() % ((lpItemBagDropInfo->MaxDropCount - lpItemBagDropInfo->MinDropCount)+1)));

			for(int n = 0; n < DropCount; n++)
			{
				int px = x;
				int py = y;

				if(DropCount > 1 || it != this->m_ItemBagInfo.begin() || (gMap[map].CheckAttr(px,py,4) != 0 || gMap[map].CheckAttr(px,py,8) != 0))
				{
					if(gObjGetRandomFreeLocation(map,&px,&py,2,2,10) == 0)
					{
						px = lpObj->X;
						py = lpObj->Y;
					}
				}

				if((GetLargeRand() % 10000) < lpItemBagDropInfo->SetDropRate || lpItemBagDropInfo->Section == -1)
				{
					gSetItemType.MakeRandomSetItem(lpObj->Index,map,px,py);
					continue;
				}

				if((GetLargeRand() % 10000) >= it->second.m_ItemRate)
				{
					gMap[map].MoneyItemDrop(it->second.m_MoneyDrop,x,y);
					continue;
				}

				std::map<int,std::vector<ITEM_BAG_EX_ITEM_INFO>>::iterator ItemInfo = this->m_ItemBagItemInfo.find(lpItemBagDropInfo->Section);

				if(ItemInfo == this->m_ItemBagItemInfo.end() || ItemInfo->second.empty() != 0)
				{
					continue;
				}

				ITEM_BAG_EX_ITEM_INFO* lpItemBagItemInfo = &ItemInfo->second[GetLargeRand() % ItemInfo->second.size()];

				WORD ItemIndex = lpItemBagItemInfo->ItemIndex;
				BYTE ItemLevel = lpItemBagItemInfo->Level;
				BYTE ItemDur = lpItemBagItemInfo->Durability;
				BYTE ItemOption1 = 0;
				BYTE ItemOption2 = 0;
				BYTE ItemOption3 = 0;
				BYTE ItemNewOption = 0;
				BYTE ItemSetOption = 0;
				BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF,0xFF,0xFF,0xFF,0xFF };

				gItemOptionRate.GetItemOption0(lpItemBagItemInfo->Option0,&ItemLevel);

				gItemOptionRate.GetItemOption1(lpItemBagItemInfo->Option1,&ItemOption1);

				gItemOptionRate.GetItemOption2(lpItemBagItemInfo->Option2,&ItemOption2);

				gItemOptionRate.GetItemOption3(lpItemBagItemInfo->Option3,&ItemOption3);

				gItemOptionRate.GetItemOption4(lpItemBagItemInfo->Option4,&ItemNewOption);

				gItemOptionRate.GetItemOption5(lpItemBagItemInfo->Option5,&ItemSetOption);

				gItemOptionRate.GetItemOption6(lpItemBagItemInfo->Option6,&ItemSocketOption[0]);

				gItemOptionRate.MakeNewOption(ItemIndex,ItemNewOption,&ItemNewOption);

				gItemOptionRate.MakeSetOption(ItemIndex,ItemSetOption,&ItemSetOption);

				gItemOptionRate.MakeSocketOption(ItemIndex,ItemSocketOption[0],&ItemSocketOption[0]);

				GDCreateItemSend(lpObj->Index,map,px,py,ItemIndex,ItemLevel,ItemDur,ItemOption1,ItemOption2,ItemOption3,lpObj->Index,ItemNewOption,ItemSetOption,0,0,ItemSocketOption,0xFF,((lpItemBagItemInfo->Duration>0)?((DWORD)time(0)+lpItemBagItemInfo->Duration):0));
			}
		}

		switch (it->second.m_BagUseEffect)
		{
		case 1:
			GCServerCommandSend(lpObj->Index, 0, lpObj->X, lpObj->Y);
			break;
		case 2:
			GCServerCommandSend(lpObj->Index, 2, lpObj->X, lpObj->Y);
			break;
		case 3:
			GCServerCommandSend(lpObj->Index, 58, SET_NUMBERHB(lpObj->Index), SET_NUMBERLB(lpObj->Index));
			break;
		}
	}

	return 1;
}