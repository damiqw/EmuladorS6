#pragma once

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

class cCustomFlag
{
public:
	cCustomFlag();
	virtual ~cCustomFlag();
	void Init();
	void Load(char* path);
	void SetInfo(CUSTOM_FLAG_INFO info);
public:
	CUSTOM_FLAG_INFO m_CustomFlagInfo[MAX_CUSTOM_FLAG];
}; extern cCustomFlag gCustomFlag;