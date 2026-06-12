#include "stdafx.h"
#include "CustomJewelDisable.h"
#include "CustomWing.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "ObjectManager.h"
#include "ServerInfo.h"
#include "SetItemType.h"
#include "SocketItemType.h"
#include "Util.h"

CCustomJewelDisable gCustomJewelDisable;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomJewelDisable::CCustomJewelDisable() // OK
{
	this->Init();
}

CCustomJewelDisable::~CCustomJewelDisable() // OK
{

}

void CCustomJewelDisable::Init() // OK
{
	for (int n = 0; n < MAX_CUSTOM_JEWEL_DISABLE; n++)
	{
		this->m_CustomJewelDisableInfo[n].Index = -1;
	}

	this->JewelOfBless = 0;
	this->JewelOfSoul = 0;
	this->JewelOfLife = 0;
}

void CCustomJewelDisable::Load(char* path) // OK
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

	this->Init();

	this->JewelOfBless = 0;
	this->JewelOfSoul = 0;
	this->JewelOfLife = 0;

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while (true)
			{
				if (section == 0)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					CUSTOM_JEWEL_DISABLE_INFO info;

					memset(&info, 0, sizeof(info));

					info.Index = lpMemScript->GetNumber();

					info.ItemIndex = lpMemScript->GetAsNumber();

					this->JewelOfBless = lpMemScript->GetAsNumber();

					this->JewelOfSoul = lpMemScript->GetAsNumber();

					this->JewelOfLife = lpMemScript->GetAsNumber();

					this->SetInfo(info);
				}
				else
				{
					break;
				}
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomJewelDisable::SetInfo(CUSTOM_JEWEL_DISABLE_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_CUSTOM_JEWEL_DISABLE)
	{
		return;
	}

	this->m_CustomJewelDisableInfo[info.Index] = info;
}

CUSTOM_JEWEL_DISABLE_INFO* CCustomJewelDisable::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_CUSTOM_JEWEL_DISABLE)
	{
		return 0;
	}

	if (this->m_CustomJewelDisableInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomJewelDisableInfo[index];
}

CUSTOM_JEWEL_DISABLE_INFO* CCustomJewelDisable::GetInfoByItem(int ItemIndex) // OK
{
	for (int n = 0; n < MAX_CUSTOM_JEWEL_DISABLE; n++)
	{
		CUSTOM_JEWEL_DISABLE_INFO* lpInfo = this->GetInfo(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}

bool CCustomJewelDisable::CheckCustomJewelDisableByItem(int ItemIndex) // OK
{
	if (this->GetInfoByItem(ItemIndex) != 0)
	{
		return 1;
	}

	return 0;
}