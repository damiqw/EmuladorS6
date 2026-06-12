#pragma once

#include "Item.h"
#include "380ItemOption.h"

#define MAX_CUSTOM_JEWEL_DISABLE 500


struct CUSTOM_JEWEL_DISABLE_INFO
{
	int Index;
	int ItemIndex;
};

class CCustomJewelDisable
{
public:
	CCustomJewelDisable();
	virtual ~CCustomJewelDisable();
	void Init();
	void Load(char* path);
	CUSTOM_JEWEL_DISABLE_INFO* GetInfo(int index);
	void SetInfo(CUSTOM_JEWEL_DISABLE_INFO info);
	CUSTOM_JEWEL_DISABLE_INFO* GetInfoByItem(int ItemIndex);
	bool CheckCustomJewelDisableByItem(int ItemIndex);
	int JewelOfBless;
	int JewelOfSoul;
	int JewelOfLife;

public:
	CUSTOM_JEWEL_DISABLE_INFO m_CustomJewelDisableInfo[MAX_CUSTOM_JEWEL_DISABLE];
};

extern CCustomJewelDisable gCustomJewelDisable;