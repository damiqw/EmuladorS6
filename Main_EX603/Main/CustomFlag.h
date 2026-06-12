#pragma once

#include "stdafx.h"

#define MAX_CUSTOM_FLAG 100

struct CUSTOM_FLAG_INFO
{
	int Index;
	int ItemIndex;
	char ModelName[32];
	int ColorR;
	int ColorG;
	int ColorB;
};

class CCustomFlag
{
public:
	CCustomFlag();
	virtual ~CCustomFlag();
	void Init();
	void Load(CUSTOM_FLAG_INFO* info);
	void SetInfo(CUSTOM_FLAG_INFO info);
	CUSTOM_FLAG_INFO* GetInfo(int index);
	CUSTOM_FLAG_INFO* GetInfoByItem(int ItemIndex);
public:
	CUSTOM_FLAG_INFO m_CustomFlagInfo[MAX_CUSTOM_FLAG];
};

extern CCustomFlag gCustomFlag;