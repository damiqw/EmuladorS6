//////////////////////////////////////////////////////////////////////
// ChangeCmd.cpp
#include "stdafx.h"
#include "ItemChangeCmd.h"
#include "user.h"
#include "Util.h"
#include "ItemManager.h"
#include "DSProtocol.h"
#include "GensSystem.h"
#include "GameMain.h"
#include "CashShop.h"
#include "MemScript.h"

CItemChangeCmd g_ItemChangeCmd;

CItemChangeCmd::CItemChangeCmd()
{
	this->m_bSystemEnable = false;
}

CItemChangeCmd::~CItemChangeCmd()
{
}

void CItemChangeCmd::LoadFile(char* FilePath) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, FilePath);
		return;
	}

	if (lpMemScript->SetBuffer(FilePath) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_mapChangeData.clear();

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


					this->m_bSystemEnable = lpMemScript->GetNumber();

				}
				else if (section == 1)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					ITEMCHANGE_ITEM_DATA m_ChangeData;

					m_ChangeData.ItemID = SafeGetItem(GET_ITEM(lpMemScript->GetNumber(), lpMemScript->GetAsNumber()));

					if (m_ChangeData.ItemID == (WORD)-1)
					{
						this->m_bSystemEnable = false;
						return;
					}

					m_ChangeData.CoinType = lpMemScript->GetAsNumber();

					if (m_ChangeData.CoinType < 0 || m_ChangeData.CoinType > 3)
					{
						this->m_bSystemEnable = false;
						return;
					}

					m_ChangeData.CoinValue = lpMemScript->GetAsNumber();

					if (this->m_mapChangeData.find(m_ChangeData.ItemID) != this->m_mapChangeData.end())
					{
						this->m_bSystemEnable = false;
						return;
					}

					this->m_mapChangeData.insert(std::pair<int, ITEMCHANGE_ITEM_DATA>(m_ChangeData.ItemID, m_ChangeData));

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

	//LogAdd(LOG_BLUE, "[SkinModel] Enable (%d) Load Count %d Item Skin %d", this->m_Config->Enable, this->m_SkinModelData.size());
}

int CItemChangeCmd::ItemChange(int aIndex) // -1 - system off, 0 - no change made, > 0 - count of items changed
{
	if (this->m_bSystemEnable == false)
	{
		return -1;
	}

	if (!OBJMAX_RANGE(aIndex))
	{
		return -1;
	}

	if (gObj[aIndex].Type != OBJECT_USER)
	{
		return -1;
	}

	LPOBJ lpObj = &gObj[aIndex];
	lpObj->ChaosLock = TRUE; // Lock Inventory

	int iItemChangeCnt = 0;

	int MaxValue = gItemManager.GetInventoryMaxValue(lpObj);

	for (int i = INVENTORY_WEAR_SIZE; i < MaxValue; i++)
		//	for (int i = INVENTORY_WEAR_SIZE; i < INVENTORY_MAIN_SIZE; i++)
	{
		//if (PSHOP_RANGE(i) == TRUE)
		//{
		//	continue;
		//}

		if (lpObj->Inventory[i].IsItem() == false)
		{
			continue;
		}

		std::map<int, ITEMCHANGE_ITEM_DATA>::iterator It = this->m_mapChangeData.find(lpObj->Inventory[i].m_Index);

		if (It == this->m_mapChangeData.end())
		{
			continue;
		}

		if (It->second.CoinType == 0)
		{
			GDSetCoinSend(lpObj->Index, It->second.CoinValue, 0, 0,0, "ItemChange");
		}

		if (It->second.CoinType == 1)
		{
			GDSetCoinSend(lpObj->Index, 0, It->second.CoinValue, 0,0, "ItemChange");
		}

		if (It->second.CoinType == 2)
		{
			GDSetCoinSend(lpObj->Index, 0, 0, It->second.CoinValue,0, "ItemChange");
		}

		gItemManager.InventoryDelItem(aIndex, i);
		gItemManager.GCItemDeleteSend(aIndex, i, 1);

		iItemChangeCnt++;
	}

	lpObj->ChaosLock = FALSE;
	return iItemChangeCnt;
}

//////////////////////////////////////////////////////////////////////
// iDev.Games - MuOnline S9EP2 IGC9.5 - TRONG.WIN - DAO VAN TRONG     
//////////////////////////////////////////////////////////////////////