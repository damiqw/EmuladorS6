#pragma once

#define MAX_ITEMPRICE	5000
#define MAX_ITEMSTACK	39
#include "Object.h"

#define sub_41FF80_Addr			((int(__thiscall*)(int a1)) 0x41FF80)
#define sub_401C10_Addr			((int(*)()) 0x401C10)
#define sub_9593B0_Addr			((BOOL(__thiscall*)(void *This, HDC hdc, LPCSTR lpMultiByteStr, int a4, LPSIZE psizl)) 0x9593B0)

#define pShowPrice				((int(*)(int a1, const char *a2, ...)) 0x9CF6AA)
#define pGetMoneyFormat			((void(__cdecl*)(double Value, char * Buff, int Arg3)) 0x5C1170)
#define pConvertTaxGold			((void(__cdecl*)(DWORD Value, char * Buff)) 0x5C1560)

struct CUSTOM_ITEMPRICE
{
	int Index;
	int ItemIndex;
	int Level;
	int Grade;
	int AncOption;
	int OptionEx;
	int Type;
	int BuyPrice;
	int SellPrice;
};

struct Coord
{
	int X;
	int Y;
};

class ItemPrice
{
public:
	ItemPrice();
	virtual ~ItemPrice();
	void Init();
	void Load(CUSTOM_ITEMPRICE* info);
	void SetInfo(CUSTOM_ITEMPRICE info);
	bool CheckItem(ObjectItem* lpItem, __int64* Price, int* Divisor);
	static void ShowBuyPrice(DWORD a1, const char* a2, char* Price);
	static void ShowSellPrice(DWORD a1, const char* a2, char* Price);
	static void Test(DWORD a1, const char* a2, char* Price);
	CUSTOM_ITEMPRICE m_ItemPrice[MAX_ITEMPRICE];
	//std::vector<CUSTOM_ITEMPRICE> m_ItemPrice;
	int		showtype;
	int		showsellprice;
	int		showbuyprice;
}; extern ItemPrice gItemPrice;