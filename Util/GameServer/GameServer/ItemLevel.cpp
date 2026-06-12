// ItemLevel.cpp: implementation of the CItemLevel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ItemLevel.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Util.h"

CItemLevel gItemLevel;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItemLevel::CItemLevel() // OK
{
	this->m_ItemLevelInfo.clear();
}

CItemLevel::~CItemLevel() // OK
{

}
/*
void CItemLevel::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_ItemLevelInfo.clear();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			ITEM_LEVEL_INFO info;

			info.ItemIndex = SafeGetItem(GET_ITEM(lpMemScript->GetNumber(), lpMemScript->GetAsNumber()));

			info.Level = lpMemScript->GetAsNumber();

			strcpy_s(info.Name, lpMemScript->GetAsString());

			this->m_ItemLevelInfo.push_back(info);
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}
*/

void CItemLevel::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_ItemLevelInfo.clear();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			ITEM_LEVEL_INFO info;

			memset(&info, 0, sizeof(info));

			static int Index = 0;

			info.index = Index++;

			info.ItemIndex = (lpMemScript->GetNumber() * 512) + lpMemScript->GetAsNumber();

			info.Level = lpMemScript->GetAsNumber();

			strcpy_s(info.Name, lpMemScript->GetAsString());

			this->m_ItemLevelInfo.insert(std::pair<int, ITEM_LEVEL_INFO>(info.index, info));
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}
bool CItemLevel::CheckItemlevel(int index, int level) // OK
{
	//for (std::vector<ITEM_LEVEL_INFO>::iterator it = this->m_ItemLevelInfo.begin(); it != this->m_ItemLevelInfo.end(); it++)
	for (std::map<int, ITEM_LEVEL_INFO>::iterator it = this->m_ItemLevelInfo.begin(); it != this->m_ItemLevelInfo.end(); it++)
	{
		if (it->second.ItemIndex != index || it->second.Level != level)
		{
			continue;
		}

		return 1;
	}

	return 0;
}
char* CItemLevel::GetItemName(int ItemIndex, int Level)
{
	for (std::map<int, ITEM_LEVEL_INFO>::iterator it = this->m_ItemLevelInfo.begin(); it != this->m_ItemLevelInfo.end(); it++)
	{
		if (it->second.ItemIndex == ItemIndex && it->second.Level == Level)
		{
			return it->second.Name;
		}
	}
	return gItemManager.GetItemName(ItemIndex);
}