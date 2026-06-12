// ItemValue.h: interface for the CItemValue class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Item.h"
#include "Protocol.h"

struct ITEM_VALUE_INFO
{
	int Index;
	int Level;
	int Grade;
	int AncOption;
	int OptionEx;
	int Type;
	int BuyPrice;
	int SellPrice;
};

enum ItemPriceType
{
	ZEN = 0,
	WCOINC = 1,
	WCOINP = 2,
	WCOING = 3,
	RUUD = 4,
};

struct PMSG_SEND_ITEM_VALUE
{
	PSWMSG_HEAD header;
	BYTE count;
	BYTE is_first;
};

class CItemValue
{
public:
	CItemValue();
	virtual ~CItemValue();
	void Load(char* path);
	bool GetItemValue(CItem* lpItem, int* type, int* BuyPrice, int* SellPrice);
private:
	//std::map<int, ITEM_VALUE_INFO> m_ItemValueInfo;
	std::vector<ITEM_VALUE_INFO> m_ItemValueInfo;
};

extern CItemValue gItemValue;
