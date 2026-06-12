// ItemLevel.h: interface for the CItemLevel class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct ITEM_LEVEL_INFO
{
	int index;
	int ItemIndex;
	int Level;
	char Name[50];
};

class CItemLevel
{
public:
	CItemLevel();
	virtual ~CItemLevel();
	void Load(char* path);
	bool CheckItemlevel(int index, int level);
	char* GetItemName(int ItemIndex, int Level);
	
	std::map<int, ITEM_LEVEL_INFO> m_ItemLevelInfo;
	//std::vector<ITEM_LEVEL_INFO> m_ItemLevelInfo;
};

extern CItemLevel gItemLevel;