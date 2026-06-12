#include "stdafx.h"
#include "RuudTokenSellTemplate.h"
#include "MemScript.h"
#include "Path.h"
#include "Util.h"
#include "Message.h"
#include "Notice.h"
#include "ItemManager.h"
#include "DSProtocol.h"
#include "CashShop.h"
#include "SocketItemType.h"

RuudTokenSellTemplate g_RuudTokenSellTemplate;

RuudTokenSellTemplate::RuudTokenSellTemplate()
{
	for (int i = 0; i < MAX_CLASSTOKENSELL_INFO; i++)
	{
		for (int n = 0; n < MAX_RUUDTOKENSELL_INFO; n++)
		{
			RuudTokenSell[ i ].JRShop[ n ].byItemType = -1;
			RuudTokenSell[ i ].JRShop[ n ].wItemIndex = -1;
			RuudTokenSell[ i ].JRShop[ n ].shPageShop = -1;
			RuudTokenSell[ i ].JRShop[ n ].wSlotIndex = -1;
			RuudTokenSell[ i ].JRShop[ n ].dwRuudCount = -1;
		}
	}
}

RuudTokenSellTemplate::~RuudTokenSellTemplate()
{
}

void InsertRuudItemOption(int Class, int Slot, int ItemIndex,int ItemLevel,int ItemDurability,int ItemOption1,int ItemOption2,int ItemOption3,int ItemNewOption,int Anc, int JOH, int OpEx, int Socket1, int Socket2, int Socket3, int Socket4, int Socket5, int ItemValue) // OK
{
	ITEM_INFO ItemInfo;

	if(gItemManager.GetInfo(ItemIndex, &ItemInfo) == 0)
	{
		return;
	}

	g_RuudTokenSellTemplate.RuudTokenSell[ Class ].m_Item[ Slot ].m_Level = ItemLevel;
	g_RuudTokenSellTemplate.RuudTokenSell[ Class ].m_Item[ Slot ].m_Durability = (float)((ItemDurability==0)?gItemManager.GetItemDurability(ItemIndex,ItemLevel,ItemNewOption,0):ItemDurability);

	BYTE ItemSocketOption[MAX_SOCKET_OPTION] = {0xFF,0xFF,0xFF,0xFF,0xFF};

	int qtd;

	if ( gSocketItemType.CheckSocketItemType(ItemIndex) == 1 )
	{
		qtd = gSocketItemType.GetSocketItemMaxSocket( ItemIndex );

		ItemSocketOption[0] = (BYTE)((qtd > 0)?((Socket1 != 255)?Socket1:255):255);
		ItemSocketOption[1] = (BYTE)((qtd > 1)?((Socket2 != 255)?Socket2:255):255);
		ItemSocketOption[2] = (BYTE)((qtd > 2)?((Socket3 != 255)?Socket3:255):255);
		ItemSocketOption[3] = (BYTE)((qtd > 3)?((Socket4 != 255)?Socket4:255):255);
		ItemSocketOption[4] = (BYTE)((qtd > 4)?((Socket5 != 255)?Socket5:255):255);
		//this->m_Item[slot].m_SocketOptionBonus = gSocketItemOption.GetSocketItemBonusOption(this->m_Item);
	}
	
	g_RuudTokenSellTemplate.RuudTokenSell[ Class ].m_Item[ Slot ].Convert(ItemIndex,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,Anc,JOH,OpEx,ItemSocketOption,0xFF);

	g_RuudTokenSellTemplate.RuudTokenSell[ Class ].m_Item[ Slot ].m_PcPointValue = ItemValue;

	return;
}

void RuudTokenSellTemplate::Load_RuudTokenSell(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox("[RuudTokenSellTemplate] Info file Load Fail [%s]", path);
		delete lpMemScript;
		return;
	}

	int Conut = 0;

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

			__tagRuudTokenSell info;

			info.byItemType = lpMemScript->GetNumber();

			info.wItemIndex = lpMemScript->GetAsNumber();

			int Class = lpMemScript->GetAsNumber();

			info.shPageShop = lpMemScript->GetAsNumber();

			info.wSlotIndex = lpMemScript->GetAsNumber();

			info.dwRuudCount = lpMemScript->GetAsNumber();

			if( info.shPageShop > 5 || info.wSlotIndex > 5 )
			{
				continue;
			}

			int ItemIndex = GET_ITEM(info.byItemType, info.wItemIndex);

			int ItemLevel = lpMemScript->GetAsNumber();

			int ItemDurability = lpMemScript->GetAsNumber();

			int ItemOption1 = lpMemScript->GetAsNumber();

			int ItemOption2 = lpMemScript->GetAsNumber();

			int ItemOption3 = lpMemScript->GetAsNumber();

			int ItemNewOption = lpMemScript->GetAsNumber();

			int AncOption = lpMemScript->GetAsNumber();

			int JOH	= lpMemScript->GetAsNumber();

			int OpEx = lpMemScript->GetAsNumber();

			int Socket1 = lpMemScript->GetAsNumber();

			int Socket2 = lpMemScript->GetAsNumber();

			int Socket3 = lpMemScript->GetAsNumber();

			int Socket4 = lpMemScript->GetAsNumber();

			int Socket5 = lpMemScript->GetAsNumber();

			int Slot = ((info.shPageShop - 1) * 5) + info.wSlotIndex - 1;

			if( Class >= 0 && Class < MAX_CLASS )
			{
				this->RuudTokenSell[ Class ].JRShop[ Slot ] = info;
				InsertRuudItemOption(Class, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
			}
			else
			{
				this->RuudTokenSell[ 0 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(0, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 1 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(1, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 2 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(2, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 3 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(3, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 4 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(4, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 5 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(5, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
				//--
				this->RuudTokenSell[ 6 ].JRShop[ Slot ] = info;
				InsertRuudItemOption(6, Slot, ItemIndex,ItemLevel,ItemDurability,ItemOption1,ItemOption2,ItemOption3,ItemNewOption,AncOption,JOH,OpEx,Socket1,Socket2,Socket3,Socket4,Socket5,0);
			}

			Conut++;
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void RuudTokenSellTemplate::GCShopItemListSend(LPOBJ lpObj)
{
	BYTE send[2048];

	PMSG_RUUD_ITEM_LIST_SEND pMsg;

	pMsg.header.set(0xEA, 0);

	int size = sizeof(pMsg);

	pMsg.type = 0;

	pMsg.count = 0;

	PMSG_RUUD_ITEM_LIST info;

	for ( int k = 0 ; k < MAX_RUUDTOKENSELL_INFO ; k++ )
	{
		info.slot = ((this->RuudTokenSell[lpObj->Class].JRShop->shPageShop - 1) * 5) + this->RuudTokenSell[lpObj->Class].JRShop->wSlotIndex - 1 ;

		info.dwRuudSell = this->RuudTokenSell[lpObj->Class].JRShop[k].dwRuudCount;

		gItemManager.ItemByteConvert(info.ItemInfo, this->RuudTokenSell[lpObj->Class].m_Item[ k ]);

		memcpy(&send[size], &info,sizeof(info));
		size += sizeof(info);

		pMsg.count++;
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);
	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));

	DataSend(lpObj->Index,send,size);
}

void RuudTokenSellTemplate::_RecvRuudBUY(PMSG_BUY_ITEMRUUD_RECV * lpMsg, int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];
	int ItemID;

	for ( int k = 0 ; k < MAX_RUUDTOKENSELL_INFO ; k++ )
	{
		if( this->RuudTokenSell[lpObj->Class].JRShop[ k ].shPageShop == lpMsg->PAGE
			&& this->RuudTokenSell[lpObj->Class].JRShop[ k ].wSlotIndex == lpMsg->SLOT )
		{
			if ( this->RuudTokenSell[lpObj->Class].JRShop[ k ].dwRuudCount > lpObj->Ruud )
			{
				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(834));
				return;
			}
			else
			{
				ItemID = GET_ITEM(this->RuudTokenSell[lpObj->Class].JRShop[ k ].byItemType, this->RuudTokenSell[lpObj->Class].JRShop[ k ].wItemIndex);

				ITEM_INFO ItemInfo;
				if( gItemManager.GetInfo(ItemID, &ItemInfo) == 0 )
				{
					return;
				}

				int crear = 0;

				int MaxY = ( gItemManager.GetInventoryMaxValue( lpObj )-INVENTORY_WEAR_SIZE ) / 8;

				for( int y = 0 ; y < MaxY; y++ )
				{
					for( int x = 0 ; x < 8; x++ )
					{
						if( lpObj->InventoryMap[((y*8)+x)] == 0xFF )
						{
							BYTE slot = gItemManager.InventoryRectCheck(lpObj->Index, x, y, ItemInfo.Width, ItemInfo.Height);

							if(slot != 0xFF)
							{
								if( crear == 0 )
								{
									BYTE ItemSocketOption[MAX_SOCKET_OPTION] = { 0xFF,0xFF,0xFF,0xFF,0xFF };

								GDCreateItemSend(lpObj->Index,
									0xEB,
									0,
									0,
									ItemID,
									(BYTE)0,
									0,
									0,
									0,
									0,
									lpObj->Index,
									0,
									0,
									0,
									0,
									ItemSocketOption,
									0,
									0);
									//--
									crear = 1;

									gCashShop.GDCashShopSubPointSaveSend(lpObj->Index,0,0,0,0,this->RuudTokenSell[lpObj->Class].JRShop[ k ].dwRuudCount);
									//-- Ruud Update
									gCashShop.CGCashShopPointRecv(lpObj->Index);
								}
							}
						}
					}
				}
			
				if ( crear == 0 )
				{
					gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(824));
					return;
				}
			}
		}
	}
}