#include "stdafx.h"
#include "CustomItemColor.h"
#include "CashShop.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "MemScript.h"
#include "Notice.h"
#include "Util.h"
#include "Viewport.h"

CCustomItemColor gCustomItemColor;

CCustomItemColor::CCustomItemColor()
{
	memset(&this->m_NpcInfo, 0, sizeof(this->m_NpcInfo));
	this->m_AllowItems.clear();
	this->m_ItemColorMap.clear();
}

CCustomItemColor::~CCustomItemColor()
{
}

void CCustomItemColor::LoadFile(char* path)
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

	this->m_AllowItems.clear();

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

					this->m_NpcInfo.Enable = lpMemScript->GetNumber();
					this->m_NpcInfo.NPCClass = lpMemScript->GetAsNumber();
					this->m_NpcInfo.Map = lpMemScript->GetAsNumber();
					this->m_NpcInfo.PosX = lpMemScript->GetAsNumber();
					this->m_NpcInfo.PosY = lpMemScript->GetAsNumber();
					this->m_NpcInfo.CostType = lpMemScript->GetAsNumber();
					this->m_NpcInfo.CostValue = lpMemScript->GetAsNumber();
				}
				else if (section == 1)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					int itemType = lpMemScript->GetNumber();
					int itemIndex = lpMemScript->GetAsNumber();

					int fullIndex = SafeGetItem(GET_ITEM(itemType, itemIndex));

					if (fullIndex != (WORD)-1)
					{
						CUSTOM_ITEM_COLOR_ALLOW_INFO info;
						info.ItemIndex = fullIndex;
						this->m_AllowItems.push_back(info);
					}
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

bool CCustomItemColor::NpcTalk(LPOBJ lpNpc, LPOBJ lpObj)
{
	if (this->m_NpcInfo.Enable == 0)
	{
		return false;
	}

	if (lpNpc->Class == this->m_NpcInfo.NPCClass)
	{
		if (this->m_NpcInfo.Map == -1 || (lpNpc->Map == this->m_NpcInfo.Map && lpNpc->X == this->m_NpcInfo.PosX && lpNpc->Y == this->m_NpcInfo.PosY))
		{
			PMSG_CUSTOM_ITEM_COLOR_NPC_OPEN pMsg;
			pMsg.header.set(0xEF, 0x10, sizeof(pMsg));
			pMsg.CostType = this->m_NpcInfo.CostType;
			pMsg.CostValue = this->m_NpcInfo.CostValue;

			DataSend(lpObj->Index, (BYTE*)&pMsg, pMsg.header.size);
			this->DGItemColorLoadSend(lpObj->Index);
			return true;
		}
	}

	return false;
}

bool CCustomItemColor::IsAllowedItem(int itemIndex)
{
	if (this->m_AllowItems.empty())
	{
		// If allow list is empty, allow all armor/weapons by default
		int cat = itemIndex / 512;
		if (cat >= 0 && cat <= 11) // Swords, Axes, Maces, Spears, Bows, Staffs, Shields, Helmets, Armors, Pants, Gloves, Boots
		{
			return true;
		}
		return false;
	}

	for (std::vector<CUSTOM_ITEM_COLOR_ALLOW_INFO>::iterator it = this->m_AllowItems.begin(); it != this->m_AllowItems.end(); ++it)
	{
		if (it->ItemIndex == itemIndex)
		{
			return true;
		}
	}

	return false;
}

void CCustomItemColor::SetItemColor(DWORD serial, BYTE r, BYTE g, BYTE b)
{
	CUSTOM_ITEM_COLOR_DATA data;
	data.Serial = serial;
	data.ColorR = r;
	data.ColorG = g;
	data.ColorB = b;
	this->m_ItemColorMap[serial] = data;
}

bool CCustomItemColor::GetItemColor(DWORD serial, BYTE& r, BYTE& g, BYTE& b)
{
	if (serial == 0)
	{
		return false;
	}

	std::map<DWORD, CUSTOM_ITEM_COLOR_DATA>::iterator it = this->m_ItemColorMap.find(serial);
	if (it != this->m_ItemColorMap.end())
	{
		r = it->second.ColorR;
		g = it->second.ColorG;
		b = it->second.ColorB;
		return true;
	}

	return false;
}

void CCustomItemColor::DGItemColorSaveSend(DWORD serial, BYTE r, BYTE g, BYTE b)
{
	if (serial == 0)
	{
		return;
	}

	SDHP_CUSTOM_ITEM_COLOR_SAVE_SEND pMsg;
	pMsg.header.set(0xED, 0x01, sizeof(pMsg));
	pMsg.Serial = serial;
	pMsg.ColorR = r;
	pMsg.ColorG = g;
	pMsg.ColorB = b;

	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
}

void CCustomItemColor::DGItemColorLoadSend(int aIndex)
{
	if (!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	SDHP_CUSTOM_ITEM_COLOR_LOAD_SEND pMsg;
	pMsg.header.set(0xED, 0x00, sizeof(pMsg));
	pMsg.AccountIndex = aIndex;

	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
}

void CCustomItemColor::GDItemColorLoadRecv(SDHP_CUSTOM_ITEM_COLOR_LOAD_RECV* lpMsg)
{
	int aIndex = lpMsg->AccountIndex;
	WORD count = lpMsg->Count;

	BYTE* body = ((BYTE*)lpMsg) + sizeof(SDHP_CUSTOM_ITEM_COLOR_LOAD_RECV);

	for (int i = 0; i < count; i++)
	{
		SDHP_CUSTOM_ITEM_COLOR_NODE* node = (SDHP_CUSTOM_ITEM_COLOR_NODE*)(body + (i * sizeof(SDHP_CUSTOM_ITEM_COLOR_NODE)));
		if (node->Serial != 0)
		{
			this->SetItemColor(node->Serial, node->ColorR, node->ColorG, node->ColorB);
		}
	}

	if (OBJMAX_RANGE(aIndex))
	{
		LPOBJ lpObj = &gObj[aIndex];
		if (lpObj->Connected == OBJECT_ONLINE)
		{
			this->SendViewportList(lpObj);
		}
	}
}

void CCustomItemColor::CGItemColorRecv(PMSG_CUSTOM_ITEM_COLOR_REQ* lpMsg, int aIndex)
{
	if (!OBJMAX_RANGE(aIndex))
	{
		return;
	}

	LPOBJ lpObj = &gObj[aIndex];
	if (lpObj->Connected != OBJECT_ONLINE)
	{
		return;
	}

	BYTE slot = lpMsg->Slot;
	if (slot > 7) // Equipped slots only (0 to 7)
	{
		return;
	}

	CItem* lpItem = &lpObj->Inventory[slot];
	if (!lpItem->IsItem())
	{
		return;
	}

	if (!this->IsAllowedItem(lpItem->m_Index))
	{
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "This item cannot be colored.");
		return;
	}

	// Cost Check
	if (this->m_NpcInfo.CostValue > 0)
	{
		int cost = this->m_NpcInfo.CostValue;

		if (this->m_NpcInfo.CostType == 1) // WCoinC (Coin2)
		{
			if (lpObj->Coin2 < cost)
			{
				gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "Insufficient WCoinC");
				return;
			}
			GDSetCoinSend(lpObj->Index, 0, -cost, 0, 0, "CustomItemColor");
		}
		else if (this->m_NpcInfo.CostType == 2) // GoblinPoint (Coin3)
		{
			if (lpObj->Coin3 < cost)
			{
				gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "Insufficient GoblinPoints");
				return;
			}
			GDSetCoinSend(lpObj->Index, 0, 0, -cost, 0, "CustomItemColor");
		}
		else if (this->m_NpcInfo.CostType == 3) // Money
		{
			if (lpObj->Money < (DWORD)cost)
			{
				gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, "Insufficient Zen");
				return;
			}
			lpObj->Money -= cost;
			GCMoneySend(aIndex, lpObj->Money);
		}
	}

	DWORD serial = lpItem->m_Serial;
	if (serial == 0)
	{
		// Fallback serial if 0
		serial = (DWORD)(aIndex * 1000 + slot + 1);
		lpItem->m_Serial = serial;
	}

	this->SetItemColor(serial, lpMsg->ColorR, lpMsg->ColorG, lpMsg->ColorB);
	this->DGItemColorSaveSend(serial, lpMsg->ColorR, lpMsg->ColorG, lpMsg->ColorB);

	PMSG_CUSTOM_ITEM_COLOR_ANS pAns;
	pAns.header.set(0xEF, 0x12, sizeof(pAns));
	pAns.Result = 1;
	pAns.Slot = slot;
	pAns.ColorR = lpMsg->ColorR;
	pAns.ColorG = lpMsg->ColorG;
	pAns.ColorB = lpMsg->ColorB;
	DataSend(aIndex, (BYTE*)&pAns, pAns.header.size);

	// Send Viewport sync
	this->SendViewportItemColor(lpObj, aIndex);
}

void CCustomItemColor::SendViewportItemColor(LPOBJ lpObj, int aTargetIndex)
{
	BYTE buffer[1024];
	PMSG_VIEWPORT_CUSTOM_ITEM_COLOR* lpMsg = (PMSG_VIEWPORT_CUSTOM_ITEM_COLOR*)buffer;
	
	int count = 0;
	BYTE* body = buffer + sizeof(PMSG_VIEWPORT_CUSTOM_ITEM_COLOR);

	for (int i = 0; i < INVENTORY_WEAR_SIZE; i++)
	{
		if (lpObj->Inventory[i].IsItem())
		{
			BYTE r, g, b;
			if (this->GetItemColor(lpObj->Inventory[i].m_Serial, r, g, b))
			{
				VIEWPORT_ITEM_COLOR_NODE node;
				node.Slot = (BYTE)i;
				node.ColorR = r;
				node.ColorG = g;
				node.ColorB = b;
				node.Serial = lpObj->Inventory[i].m_Serial;

				memcpy(body + (count * sizeof(VIEWPORT_ITEM_COLOR_NODE)), &node, sizeof(VIEWPORT_ITEM_COLOR_NODE));
				count++;
			}
		}
	}

	if (count == 0)
	{
		return;
	}

	int size = sizeof(PMSG_VIEWPORT_CUSTOM_ITEM_COLOR) + (count * sizeof(VIEWPORT_ITEM_COLOR_NODE));
	lpMsg->header.set(0xEF, 0x13, size);
	lpMsg->TargetIndex = lpObj->Index;
	lpMsg->Count = (BYTE)count;

	if (aTargetIndex != -1 && aTargetIndex != lpObj->Index)
	{
		DataSend(aTargetIndex, buffer, size);
	}
	else
	{
		DataSend(lpObj->Index, buffer, size);
		MsgSendV2(lpObj, buffer, size);
	}
}

void CCustomItemColor::SendViewportList(LPOBJ lpObj)
{
	this->SendViewportItemColor(lpObj, lpObj->Index);

	for (int n = 0; n < MAX_VIEWPORT; n++)
	{
		if (lpObj->VpPlayer[n].state != VIEWPORT_SEND && lpObj->VpPlayer[n].state != VIEWPORT_WAIT)
		{
			continue;
		}

		if (lpObj->VpPlayer[n].type != OBJECT_USER)
		{
			continue;
		}

		int target = lpObj->VpPlayer[n].index;
		if (OBJECT_RANGE(target) != 0 && gObj[target].Connected == OBJECT_ONLINE)
		{
			this->SendViewportItemColor(&gObj[target], lpObj->Index);
		}
	}
}
