#include "stdafx.h"
#include "ItemShopValue.h"
#include "Defines.h"
#include "Offset.h"
#include "HealthBar.h"
#include "Protect.h"
#include "Util.h"
#include "Font.h"

ItemPrice gItemPrice;

ItemPrice::ItemPrice()
{
	this->Init();
}

ItemPrice::~ItemPrice()
{

}

int StackItems[MAX_ITEMSTACK] =
{ 6688, 6689, 6690, 6288, 6290, 7168, 7169, 7170, 7171, 7172, 7173, 7174, 7175, 7176, 7197, 7203, 7204, 7205,
7206, 7207, 7008, 7214, 7215, 7216, 7217, 7218, 7238, 7239, 7253, 7254, 7255, 7256, 7257, 7258, 7268, 7269, 7278, 7301, 7389 };

void ItemPrice::Init()
{
	for (int n = 0; n < MAX_ITEMPRICE; n++)
	{
		this->m_ItemPrice[n].Index = -1;
		this->m_ItemPrice[n].ItemIndex = -1;
	}
	this->showtype = 0;
	this->showbuyprice = 0;
	this->showsellprice = 0;
	SetCompleteHook(0xFF, 0x007E44D3, &this->ShowBuyPrice);
	SetCompleteHook(0xFF, 0x007E452F, &this->ShowSellPrice);

	
}

void ItemPrice::Load(CUSTOM_ITEMPRICE* info)
{
	for (int n = 0; n < MAX_ITEMPRICE; n++)
	{
		this->SetInfo(info[n]);
	}

}

void ItemPrice::SetInfo(CUSTOM_ITEMPRICE info)
{
	if (info.Index < 0 || info.Index >= MAX_ITEMPRICE)
	{
		return;
	}
	
	this->m_ItemPrice[info.Index] = info;
}

bool ItemPrice::CheckItem(ObjectItem* lpItem, __int64* Price, int* Divisor)
{
	for (int i = 0; i < MAX_ITEMPRICE; i++)
	{
		if (this->m_ItemPrice[i].Index == -1 || this->m_ItemPrice[i].ItemIndex == -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (lpItem->ItemID != this->m_ItemPrice[i].ItemIndex)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (GET_ITEMOPT_LEVEL(lpItem->Level) != this->m_ItemPrice[i].Level && this->m_ItemPrice[i].Level != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		int ExcellentOpt = lpItem->ExcellentOption;

		if (ExcellentOpt > 63)
		{
			ExcellentOpt -= 64;
		}

		if (ExcellentOpt != this->m_ItemPrice[i].Grade && this->m_ItemPrice[i].Grade != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		////console.Log("", "Anc [%d %d] OptionEx [%d %d] Grade [%d]", this->m_ItemPrice[i].AncOption, lpItem->AncientOption, this->m_ItemPrice[i].OptionEx, lpItem->Is380Item, this->m_ItemPrice[i].Grade);

		if (this->m_ItemPrice[i].AncOption != lpItem->AncientOption && this->m_ItemPrice[i].AncOption != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		if (this->m_ItemPrice[i].OptionEx != lpItem->Is380Item && this->m_ItemPrice[i].OptionEx != -1)
		{
			this->showbuyprice = 0;
			this->showsellprice = 0;
			continue;
		}

		for (int n = 0; n < MAX_ITEMSTACK; n++)
		{
			if (lpItem->ItemID == StackItems[n])
			{
				int SellPrice;

				if (this->m_ItemPrice[i].SellPrice == -1)
				{
					SellPrice = (this->m_ItemPrice[i].BuyPrice * lpItem->Durability) / 3;
				}
				else
				{
					SellPrice = (this->m_ItemPrice[i].SellPrice * lpItem->Durability);
				}
				////console.Log(FUNC, "%d durability [%d] total price [%d]", lpItem->ItemID, lpItem->Durability, this->m_ItemPrice[i].Value*lpItem->Durability);
				*Price = this->m_ItemPrice[i].BuyPrice * lpItem->Durability;
				*Divisor = SellPrice;
				this->showtype = this->m_ItemPrice[i].Type;
				this->showbuyprice = this->m_ItemPrice[i].BuyPrice * lpItem->Durability;
				this->showsellprice = SellPrice;
				return true;
			}
		}
		int SellPrice;

		if (this->m_ItemPrice[i].SellPrice == -1)
		{
			SellPrice = this->m_ItemPrice[i].BuyPrice / 3;
		}
		else
		{
			SellPrice = this->m_ItemPrice[i].SellPrice;
		}

		*Price = this->m_ItemPrice[i].BuyPrice;
		*Divisor = SellPrice;
		this->showtype = this->m_ItemPrice[i].Type;
		this->showbuyprice = this->m_ItemPrice[i].BuyPrice;
		this->showsellprice = SellPrice;
		return true;
	}
	return false;
}

void ItemPrice::Test(DWORD a1, const char* a2, char* Price)
{
	//g_Console.AddMessage(5,"%s",(char*)0x81C0AE0);

	pShowPrice(a1, a2, Price);
}

void ItemPrice::ShowBuyPrice(DWORD a1, const char* a2, char* Price)
{
	if (gItemPrice.showbuyprice > 0)
	{
		if (gItemPrice.showtype == 0)
		{
			pShowPrice(a1, "Buy Price: %s Zen", Price);
		}
		// 1 - Credits, 2 - WCoinC, 3 - WCoinP, 4 - Goblin Points
		else if (gItemPrice.showtype == 1)
		{
			pShowPrice(a1, "Buy Price: %s %s", Price, gCustomMessage.GetMessage(58));
		}
		else if (gItemPrice.showtype == 2)
		{
			pShowPrice(a1, "Buy Price: %s %s", Price, gCustomMessage.GetMessage(59));
		}
		else if (gItemPrice.showtype == 3)
		{
			pShowPrice(a1, "Buy Price: %s %s", Price, gCustomMessage.GetMessage(60));
		}
		else if (gItemPrice.showtype == 4)
		{
			pShowPrice(a1, "Buy Price: %s %s", Price, gCustomMessage.GetMessage(69));
		}
		else
		{
			pShowPrice(a1, "Buy Price: %s Zen", Price);
		}
	}
	else
	{
		pShowPrice(a1, "Buy Price: %s Zen", Price);
	}
}

void ItemPrice::ShowSellPrice(DWORD a1, const char* a2, char* Price)
{
	if (gItemPrice.showsellprice > 0)
	{
		if (gItemPrice.showtype == 0)
		{
			pShowPrice(a1, "Sell Price: %s Zen", Price);
		}
		else if (gItemPrice.showtype == 1)
		{
			pShowPrice(a1, "Sell Price: %s %s", Price, gCustomMessage.GetMessage(58));
		}
		else if (gItemPrice.showtype == 2)
		{
			pShowPrice(a1, "Sell Price: %s %s", Price, gCustomMessage.GetMessage(59));
		}
		else if (gItemPrice.showtype == 3)
		{
			pShowPrice(a1, "Sell Price: %s %s", Price, gCustomMessage.GetMessage(60));
		}
		else if (gItemPrice.showtype == 4)
		{
			pShowPrice(a1, "Sell Price: %s %s", Price, gCustomMessage.GetMessage(69));
		}
		else
		{
			pShowPrice(a1, "Sell Price: %s Zen", Price);
		}
	}
	else
	{
		pShowPrice(a1, "Sell Price: %s Zen", Price);
	}
}