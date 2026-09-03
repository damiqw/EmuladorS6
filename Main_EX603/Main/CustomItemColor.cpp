#include "stdafx.h"
#include "CustomItemColor.h"
#include "CustomFont.h"
#include "Defines.h"
#include "Interface.h"
#include "InterfaceElemental.h"
#include "Item.h"
#include "ItemMove.h"
#include "Object.h"
#include "Protocol.h"
#include "User.h"
#include "Util.h"

CCustomItemColor gCustomItemColor;

CCustomItemColor::CCustomItemColor()
{
	this->Init();
}

CCustomItemColor::~CCustomItemColor()
{
}

void CCustomItemColor::Init()
{
	this->m_WindowOpen = false;
	this->m_CostType = 0;
	this->m_CostValue = 0;
	this->m_SelectedSlot = 255;
	this->m_SelectedItemIndex = 0xFFFF;
	this->m_ColorR = 255;
	this->m_ColorG = 255;
	this->m_ColorB = 255;
	this->m_DraggingR = false;
	this->m_DraggingG = false;
	this->m_DraggingB = false;

	this->m_EquippedList.clear();
	this->m_EquippedListIndex = 0;

	this->m_ItemColorMap.clear();
	this->m_ViewportColorMap.clear();
}

void CCustomItemColor::UpdateEquippedList()
{
	this->m_EquippedList.clear();
	this->m_EquippedListIndex = 0;

	if (!gObjUser.lpPlayer)
	{
		return;
	}

	const char* slotNames[] = {
		"Weapon (R)", "Weapon (L)", "Helm", "Armor",
		"Pants", "Gloves", "Boots", "Wings"
	};

	for (int i = 0; i <= 7; i++)
	{
		ObjectItem* item = &gObjUser.lpPlayer->pEquipment[i];
		if (item->ItemID != -1 && item->ItemID != 0xFFFF)
		{
			EQUIPPED_DYE_ITEM dyeItem;
			dyeItem.Slot = (BYTE)i;
			dyeItem.ItemIndex = item->ItemID;
			sprintf_s(dyeItem.SlotName, sizeof(dyeItem.SlotName), "%s", slotNames[i]);

			char* name = GetItemName(item->ItemID, item->Level);
			if (name && name[0] != 0)
			{
				sprintf_s(dyeItem.ItemName, sizeof(dyeItem.ItemName), "%s", name);
			}
			else
			{
				sprintf_s(dyeItem.ItemName, sizeof(dyeItem.ItemName), "Item #%d", item->ItemID);
			}

			this->m_EquippedList.push_back(dyeItem);
		}
	}

	if (!this->m_EquippedList.empty())
	{
		this->m_SelectedSlot = this->m_EquippedList[0].Slot;
		this->m_SelectedItemIndex = this->m_EquippedList[0].ItemIndex;
	}
	else
	{
		this->m_SelectedSlot = 255;
		this->m_SelectedItemIndex = 0xFFFF;
	}
}

void CCustomItemColor::OpenWindow(int costType, int costValue)
{
	this->m_WindowOpen = true;
	this->m_CostType = costType;
	this->m_CostValue = costValue;

	this->UpdateEquippedList();

	gInterface.Data[eITEMCOLOR_MAIN].OnShow = true;
}

void CCustomItemColor::CloseWindow()
{
	this->m_WindowOpen = false;
	gInterface.Data[eITEMCOLOR_MAIN].OnShow = false;
	this->m_DraggingR = false;
	this->m_DraggingG = false;
	this->m_DraggingB = false;
	pSetCursorFocus = false;
}

void CCustomItemColor::RecvNpcOpen(PMSG_CUSTOM_ITEM_COLOR_NPC_OPEN_RECV* lpMsg)
{
	this->OpenWindow(lpMsg->CostType, lpMsg->CostValue);
}

void CCustomItemColor::RecvAnswer(PMSG_CUSTOM_ITEM_COLOR_ANS_RECV* lpMsg)
{
	if (lpMsg->Result == 1)
	{
		if (gObjUser.lpViewPlayer)
		{
			CUSTOM_ITEM_COLOR_DATA_CLIENT data;
			data.ColorR = lpMsg->ColorR;
			data.ColorG = lpMsg->ColorG;
			data.ColorB = lpMsg->ColorB;
			data.Serial = 0;

			this->m_ViewportColorMap[gObjUser.lpViewPlayer->aIndex][lpMsg->Slot] = data;
		}

		gElemental.OpenMessageBox("Success", "Item color updated successfully!");
	}
	else
	{
		gElemental.OpenMessageBox("Failed", "Could not apply color to this item.");
	}
}

void CCustomItemColor::RecvViewportSync(PMSG_VIEWPORT_CUSTOM_ITEM_COLOR_RECV* lpMsg)
{
	WORD targetIndex = lpMsg->TargetIndex;
	BYTE count = lpMsg->Count;

	BYTE* body = ((BYTE*)lpMsg) + sizeof(PMSG_VIEWPORT_CUSTOM_ITEM_COLOR_RECV);

	for (int i = 0; i < count; i++)
	{
		VIEWPORT_ITEM_COLOR_NODE_RECV* node = (VIEWPORT_ITEM_COLOR_NODE_RECV*)(body + (i * sizeof(VIEWPORT_ITEM_COLOR_NODE_RECV)));

		CUSTOM_ITEM_COLOR_DATA_CLIENT data;
		data.Serial = node->Serial;
		data.ColorR = node->ColorR;
		data.ColorG = node->ColorG;
		data.ColorB = node->ColorB;
		data.ItemID = node->ItemID;
		data.Level = node->Level;
		data.ExcellentOption = node->ExcellentOption;
		data.AncientOption = node->AncientOption;

		if (node->Serial != 0)
		{
			this->m_ItemColorMap[node->Serial] = data;

			// Store the Serial in the client's ObjectItem directly!
			if (oUserPreviewStruct != 0 && targetIndex == *(WORD*)(oUserPreviewStruct + 0x7E))
			{
				DWORD base = *(DWORD*)0x8128AC4; // CharacterMachine
				if (base != 0)
				{
					ObjectItem* pItem = (ObjectItem*)(base + 4672 + (107 * node->Slot));
					pItem->Unknown103 = node->Serial;
				}
			}
		}

		this->m_ViewportColorMap[targetIndex][node->Slot] = data;
	}
}

bool CCustomItemColor::GetItemColorBySerial(DWORD serial, float* outColor)
{
	if (serial == 0)
	{
		return false;
	}

	std::map<DWORD, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator it = this->m_ItemColorMap.find(serial);
	if (it != this->m_ItemColorMap.end())
	{
		outColor[0] = it->second.ColorR / 255.0f;
		outColor[1] = it->second.ColorG / 255.0f;
		outColor[2] = it->second.ColorB / 255.0f;
		return true;
	}

	return false;
}

bool CCustomItemColor::GetHoveredItemColor(ObjectItem* pItem, float* outColor)
{
	if (!pItem) return false;

	// Use the directly stored Serial if available! (Perfect matching)
	if (pItem->Unknown103 != 0)
	{
		std::map<DWORD, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator it = this->m_ItemColorMap.find(pItem->Unknown103);
		if (it != this->m_ItemColorMap.end())
		{
			outColor[0] = it->second.ColorR / 255.0f;
			outColor[1] = it->second.ColorG / 255.0f;
			outColor[2] = it->second.ColorB / 255.0f;
			return true;
		}
	}

	// Fallback to property matching (just in case the item hasn't been synced via Serial yet)
	if (oUserPreviewStruct != 0)
	{
		WORD localIndex = *(WORD*)(oUserPreviewStruct + 0x7E);

		std::map<WORD, std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>>::iterator it = this->m_ViewportColorMap.find(localIndex);
		if (it != this->m_ViewportColorMap.end())
		{
			for (std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if (it2->second.ItemID == pItem->ItemID &&
					it2->second.Level == pItem->Level &&
					(it2->second.ExcellentOption & 63) == (pItem->ExcellentOption & 63) &&
					(it2->second.AncientOption & 3) == (pItem->AncientOption & 3))
				{
					outColor[0] = it2->second.ColorR / 255.0f;
					outColor[1] = it2->second.ColorG / 255.0f;
					outColor[2] = it2->second.ColorB / 255.0f;
					return true;
				}
			}
		}
	}

	return false;
}

bool CCustomItemColor::GetEquippedItemColor(int itemIndex, float* outColor)
{
	WORD localIndex = (oUserPreviewStruct != 0) ? *(WORD*)(oUserPreviewStruct + 0x7E) : 0xFFFF;
	std::map<WORD, std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>>::iterator itLocal = this->m_ViewportColorMap.find(localIndex);

	if (itLocal != this->m_ViewportColorMap.end())
	{
		for (std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator it = itLocal->second.begin(); it != itLocal->second.end(); ++it)
		{
			BYTE slot = it->first;
			int slotItem = -1;
			if (gObjUser.lpPlayer && slot < INVENTORY_WEAR_SIZE)
			{
				slotItem = gObjUser.lpPlayer->pEquipment[slot].ItemID;
			}
			else if (oUserPreviewStruct != 0)
			{
				static const int offsets[8] = { 448, 484, 268, 304, 340, 376, 412, 520 };
				if (slot < 8)
				{
					slotItem = *(short*)(oUserPreviewStruct + offsets[slot]);
				}
			}

			if (slotItem == itemIndex || (slotItem - ITEM_BASE_MODEL) == itemIndex || slotItem == (itemIndex + ITEM_BASE_MODEL) || (slotItem - ITEM_INTER) == itemIndex || slotItem == (itemIndex + ITEM_INTER))
			{
				outColor[0] = (float)(it->second.ColorR / 255.0f);
				outColor[1] = (float)(it->second.ColorG / 255.0f);
				outColor[2] = (float)(it->second.ColorB / 255.0f);
				return true;
			}
		}
	}

	for (std::map<WORD, std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>>::iterator itPlayer = this->m_ViewportColorMap.begin(); itPlayer != this->m_ViewportColorMap.end(); ++itPlayer)
	{
		if (itPlayer->first == localIndex)
		{
			continue;
		}

		for (int n = 0; n < 400; n++)
		{
			DWORD preview = pGetPreviewStruct(pPreviewThis(), n);
			if (preview != 0 && *(WORD*)(preview + 0x7E) == itPlayer->first)
			{
				static const int offsets[8] = { 448, 484, 268, 304, 340, 376, 412, 520 };
				for (std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator it = itPlayer->second.begin(); it != itPlayer->second.end(); ++it)
				{
					BYTE slot = it->first;
					if (slot < 8)
					{
						short slotModel = *(short*)(preview + offsets[slot]);
						if (slotModel == itemIndex || (slotModel - ITEM_BASE_MODEL) == itemIndex || slotModel == (itemIndex + ITEM_BASE_MODEL) || (slotModel - ITEM_INTER) == itemIndex || slotModel == (itemIndex + ITEM_INTER))
						{
							outColor[0] = (float)(it->second.ColorR / 255.0f);
							outColor[1] = (float)(it->second.ColorG / 255.0f);
							outColor[2] = (float)(it->second.ColorB / 255.0f);
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

ObjectPreview* g_pCurrentRenderingPreview = NULL;

int __cdecl HookDrawViewPort(DWORD ObjectPointer, DWORD ModelPointer, int a3)
{
	g_pCurrentRenderingPreview = (ObjectPreview*)ObjectPointer;
	int result = ((int(__cdecl*)(DWORD, DWORD, int))0x0056F210)(ObjectPointer, ModelPointer, a3);
	g_pCurrentRenderingPreview = NULL;
	return result;
}

void __cdecl HookRenderLinkObject(float x, float y, float z, DWORD preview, DWORD itemAddress, int ItemIndex, int ItemLevel, int NewOption, char a9, char a10, int RenderType, char a12)
{
	if (preview == 0)
	{
		((void(__cdecl*)(float, float, float, DWORD, DWORD, int, int, int, char, char, int, char))0x005655C0)(x, y, z, preview, itemAddress, ItemIndex, ItemLevel, NewOption, a9, a10, RenderType, a12);
		return;
	}

	float* light = (float*)(preview + 0xDC);
	float oldLight[3] = { light[0], light[1], light[2] };

	float customColor[3];
	if (gCustomItemColor.GetCharacterSlotColor((ObjectPreview*)preview, ItemIndex, customColor))
	{
		light[0] = customColor[0];
		light[1] = customColor[1];
		light[2] = customColor[2];
		RenderType |= 0x40;
	}

	((void(__cdecl*)(float, float, float, DWORD, DWORD, int, int, int, char, char, int, char))0x005655C0)(x, y, z, preview, itemAddress, ItemIndex, ItemLevel, NewOption, a9, a10, RenderType, a12);

	light[0] = oldLight[0];
	light[1] = oldLight[1];
	light[2] = oldLight[2];
}

void __cdecl HookRenderPartObjectBody(int Model, int Object, int ItemIndex, float Alpha, int a5)
{
	if (Model == 0 || Object == 0)
	{
		((void(__cdecl*)(int, int, int, float, int))0x005FA710)(Model, Object, ItemIndex, Alpha, a5);
		return;
	}

	DWORD preview = 0;
	if (oUserPreviewStruct != 0 && Object == (oUserPreviewStruct + 776))
	{
		preview = (DWORD)oUserPreviewStruct;
	}
	else
	{
		for (int n = 0; n < 400; n++)
		{
			DWORD p = pGetPreviewStruct(pPreviewThis(), n);
			if (p != 0 && Object == (int)(p + 776))
			{
				preview = p;
				break;
			}
		}
	}

	float oldBody[3] = { *(float*)(Model + 72), *(float*)(Model + 76), *(float*)(Model + 80) };
	float oldLight[3] = { *(float*)(Model + 100), *(float*)(Model + 104), *(float*)(Model + 108) };

	float customColor[3];
	bool hasColor = false;

	if (preview != 0)
	{
		hasColor = gCustomItemColor.GetCharacterSlotColor((ObjectPreview*)preview, ItemIndex, customColor);
	}
	else if (gCustomItemColor.IsWindowOpen() && gCustomItemColor.m_SelectedSlot != 255)
	{
		int selectedModel = gCustomItemColor.m_SelectedItemIndex;
		if (ItemIndex == selectedModel || ItemIndex == (selectedModel + ITEM_BASE_MODEL) || (ItemIndex - ITEM_BASE_MODEL) == selectedModel || (ItemIndex - ITEM_INTER) == selectedModel || ItemIndex == (selectedModel + ITEM_INTER))
		{
			customColor[0] = (float)(gCustomItemColor.m_ColorR / 255.0f);
			customColor[1] = (float)(gCustomItemColor.m_ColorG / 255.0f);
			customColor[2] = (float)(gCustomItemColor.m_ColorB / 255.0f);
			hasColor = true;
		}
	}

	if (hasColor)
	{
		*(float*)(Model + 72) = customColor[0];
		*(float*)(Model + 76) = customColor[1];
		*(float*)(Model + 80) = customColor[2];
		*(float*)(Model + 100) = customColor[0];
		*(float*)(Model + 104) = customColor[1];
		*(float*)(Model + 108) = customColor[2];
	}

	((void(__cdecl*)(int, int, int, float, int))0x005FA710)(Model, Object, ItemIndex, Alpha, a5);

	if (hasColor)
	{
		*(float*)(Model + 72) = oldBody[0];
		*(float*)(Model + 76) = oldBody[1];
		*(float*)(Model + 80) = oldBody[2];
		*(float*)(Model + 100) = oldLight[0];
		*(float*)(Model + 104) = oldLight[1];
		*(float*)(Model + 108) = oldLight[2];
	}
}

void CCustomItemColor::InstallRenderHooks()
{
	// Hooks for Attached / Linked Objects (Weapons and Wings)
	SetCompleteHook(0xE8, 0x005711AB, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x0057126F, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x005713D6, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00576DDB, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00588357, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x005883F4, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00588505, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00588617, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00588661, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x0058876E, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x005887AD, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00609D1E, &HookRenderLinkObject);
	SetCompleteHook(0xE8, 0x00610691, &HookRenderLinkObject);

	// Hooks for Mesh Body Parts (Helm, Armor, Pants, Gloves, Boots)
	SetCompleteHook(0xE8, 0x0060D9C9, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DB79, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DBEA, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DC5B, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DD1D, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DD8E, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DDFF, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DE70, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DEBA, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060DF78, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E045, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E124, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E211, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E2E6, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E394, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E408, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E47C, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E516, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E5BC, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E662, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E745, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E828, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060E93C, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060EA50, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060EB63, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060EC77, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060ED50, &HookRenderPartObjectBody);
	SetCompleteHook(0xE8, 0x0060ED94, &HookRenderPartObjectBody);
}

bool CCustomItemColor::GetCharacterSlotColor(ObjectPreview* pChar, int modelIndex, float* outColor)
{
	if (!pChar)
	{
		return false;
	}

	DWORD preview = (DWORD)pChar;
	WORD charIndex = *(WORD*)(preview + 0x7E);
	bool isLocalHero = (preview == (DWORD)oUserPreviewStruct || (gObjUser.lpViewPlayer && preview == (DWORD)gObjUser.lpViewPlayer));

	// Check if Master Color Studio is open and live previewing for local hero
	if (isLocalHero && this->IsWindowOpen() && this->m_SelectedSlot != 255)
	{
		int selectedModel = this->m_SelectedItemIndex + ITEM_BASE_MODEL;
		if (modelIndex == selectedModel || modelIndex == this->m_SelectedItemIndex || (modelIndex - ITEM_BASE_MODEL) == this->m_SelectedItemIndex || (modelIndex - ITEM_INTER) == this->m_SelectedItemIndex)
		{
			outColor[0] = (float)(this->m_ColorR / 255.0f);
			outColor[1] = (float)(this->m_ColorG / 255.0f);
			outColor[2] = (float)(this->m_ColorB / 255.0f);
			return true;
		}
	}

	std::map<WORD, std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>>::iterator itPlayer = this->m_ViewportColorMap.find(charIndex);
	if (itPlayer == this->m_ViewportColorMap.end())
	{
		return false;
	}

	int slot = -1;
	static const int offsets[8] = { 448, 484, 268, 304, 340, 376, 412, 520 };
	for (int n = 0; n < 8; n++)
	{
		short slotModel = *(short*)(preview + offsets[n]);
		if (slotModel == modelIndex || (slotModel - ITEM_BASE_MODEL) == modelIndex || slotModel == (modelIndex + ITEM_BASE_MODEL) || (slotModel - ITEM_INTER) == modelIndex || slotModel == (modelIndex + ITEM_INTER))
		{
			slot = n;
			break;
		}
	}

	if (slot != -1)
	{
		std::map<BYTE, CUSTOM_ITEM_COLOR_DATA_CLIENT>::iterator itSlot = itPlayer->second.find((BYTE)slot);
		if (itSlot != itPlayer->second.end())
		{
			outColor[0] = (float)(itSlot->second.ColorR / 255.0f);
			outColor[1] = (float)(itSlot->second.ColorG / 255.0f);
			outColor[2] = (float)(itSlot->second.ColorB / 255.0f);
			return true;
		}
	}

	return false;
}

void CCustomItemColor::SendApplyRequest()
{
	if (this->m_SelectedSlot == 255)
	{
		gElemental.OpenMessageBox("Notice", "Please select an item from your inventory first!");
		return;
	}

	PMSG_CUSTOM_ITEM_COLOR_REQ_SEND pMsg;
	pMsg.header.set(0xEF, 0x10, sizeof(pMsg));
	pMsg.Slot = this->m_SelectedSlot;
	pMsg.ColorR = this->m_ColorR;
	pMsg.ColorG = this->m_ColorG;
	pMsg.ColorB = this->m_ColorB;

	DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void CCustomItemColor::DrawWindow()
{
	if (!this->m_WindowOpen)
	{
		return;
	}

	if (gInterface.CheckWindow(SkillTree) 
	|| gInterface.CheckWindow(Character) 
	|| gInterface.CheckWindow(Shop)
	|| gInterface.CheckWindow(CreateGuild)
	|| gInterface.CheckWindow(ChatWindow)
	|| gInterface.CheckWindow(FriendList)
	|| gInterface.CheckWindow(MuHelper)
	|| gInterface.CheckWindow(Store)
	|| gInterface.CheckWindow(Warehouse)
	|| gInterface.CheckWindow(Trade)
	|| gInterface.CheckWindow(CashShop)
	|| gInterface.CheckWindow(MoveList)
	|| gInterface.CheckWindow(ChaosBox))
	{
		this->CloseWindow();
		return;
	}

	pSetCursorFocus = true;
	gInterface.Data[eITEMCOLOR_MAIN].OnShow = true;

	float startX = 210.0f;
	float startY = 60.0f;
	float width = 220.0f;
	float height = 260.0f;

	gElemental.gDrawWindowCustom(startX, startY, width, height, eITEMCOLOR_MAIN, "Master Color Studio");

	// Equipped Item Selector
	float selX = startX + 15.0f;
	float selY = startY + 42.0f;

	if (!this->m_EquippedList.empty())
	{
		if (this->m_EquippedListIndex < 0) this->m_EquippedListIndex = 0;
		if (this->m_EquippedListIndex >= (int)this->m_EquippedList.size()) this->m_EquippedListIndex = (int)this->m_EquippedList.size() - 1;

		EQUIPPED_DYE_ITEM* curItem = &this->m_EquippedList[this->m_EquippedListIndex];
		this->m_SelectedSlot = curItem->Slot;
		this->m_SelectedItemIndex = curItem->ItemIndex;

		char dispText[128];
		sprintf_s(dispText, sizeof(dispText), "[%s] %s", curItem->SlotName, curItem->ItemName);
		CustomFont.Draw(CustomFont.FontBold, (int)(selX + 22), (int)(selY + 2), 0xFFFFFFFF, 0, 145, 0, 3, dispText);

		// Left Arrow Button '<'
		if (gElemental.gDrawButtonProTecno(selX, selY, 18.0f, 11, "<", 18.0f))
		{
			if (this->m_EquippedListIndex > 0)
			{
				this->m_EquippedListIndex--;
			}
		}

		// Right Arrow Button '>'
		if (gElemental.gDrawButtonProTecno(selX + 172.0f, selY, 18.0f, 11, ">", 18.0f))
		{
			if (this->m_EquippedListIndex < (int)this->m_EquippedList.size() - 1)
			{
				this->m_EquippedListIndex++;
			}
		}
	}
	else
	{
		CustomFont.Draw(CustomFont.FontBold, (int)(selX), (int)(selY + 2), 0xFF8888FF, 0, 190, 0, 3, "No equipped dyeable items!");
	}

	// Red Slider (R)
	float sliderTrackW = 120.0f;
	float sliderRX = startX + 75.0f;
	float sliderRY = startY + 75.0f;
	
	char textR[32];
	sprintf_s(textR, "Red: %d", this->m_ColorR);
	CustomFont.Draw(CustomFont.FontNormal, (int)(startX + 15), (int)(sliderRY - 2), 0xFF5555FF, 0, 55, 0, 1, textR);

	// Render Red Slider Track & Fill & Knob
	gElemental.gInfoBox(sliderRX, sliderRY, sliderTrackW, 8.0f, 0x000000FF, 0, 0);
	gElemental.gInfoBox(sliderRX, sliderRY, (this->m_ColorR / 255.0f * sliderTrackW), 8.0f, 0xFF3333FF, 0, 0);
	gElemental.gInfoBox(sliderRX + (this->m_ColorR / 255.0f * sliderTrackW) - 2.0f, sliderRY - 2.0f, 5.0f, 12.0f, 0xFFFFFFFF, 0, 0);

	// Green Slider (G)
	float sliderGY = startY + 105.0f;
	char textG[32];
	sprintf_s(textG, "Green: %d", this->m_ColorG);
	CustomFont.Draw(CustomFont.FontNormal, (int)(startX + 15), (int)(sliderGY - 2), 0x55FF55FF, 0, 55, 0, 1, textG);

	// Render Green Slider Track & Fill & Knob
	gElemental.gInfoBox(sliderRX, sliderGY, sliderTrackW, 8.0f, 0x000000FF, 0, 0);
	gElemental.gInfoBox(sliderRX, sliderGY, (this->m_ColorG / 255.0f * sliderTrackW), 8.0f, 0x33FF33FF, 0, 0);
	gElemental.gInfoBox(sliderRX + (this->m_ColorG / 255.0f * sliderTrackW) - 2.0f, sliderGY - 2.0f, 5.0f, 12.0f, 0xFFFFFFFF, 0, 0);

	// Blue Slider (B)
	float sliderBY = startY + 135.0f;
	char textB[32];
	sprintf_s(textB, "Blue: %d", this->m_ColorB);
	CustomFont.Draw(CustomFont.FontNormal, (int)(startX + 15), (int)(sliderBY - 2), 0x5555FFFF, 0, 55, 0, 1, textB);

	// Render Blue Slider Track & Fill & Knob
	gElemental.gInfoBox(sliderRX, sliderBY, sliderTrackW, 8.0f, 0x000000FF, 0, 0);
	gElemental.gInfoBox(sliderRX, sliderBY, (this->m_ColorB / 255.0f * sliderTrackW), 8.0f, 0x3333FFFF, 0, 0);
	gElemental.gInfoBox(sliderRX + (this->m_ColorB / 255.0f * sliderTrackW) - 2.0f, sliderBY - 2.0f, 5.0f, 12.0f, 0xFFFFFFFF, 0, 0);

	// Color Preview Box
	float previewBoxY = startY + 168.0f;
	char rgbValText[64];
	sprintf_s(rgbValText, "Preview RGB: (%d, %d, %d)", this->m_ColorR, this->m_ColorG, this->m_ColorB);
	CustomFont.Draw(CustomFont.FontBold, (int)(startX + 15), (int)(previewBoxY), 0xFFFFFFFF, 0, 130, 0, 1, rgbValText);

	DWORD previewColor = (this->m_ColorR << 24) | (this->m_ColorG << 16) | (this->m_ColorB << 8) | 0xFF;
	gElemental.gInfoBox(startX + 145.0f, previewBoxY - 2.0f, 50.0f, 16.0f, previewColor, 0, 0);

	// Cost Display
	char costText[64];
	const char* coinNames[] = { "WCoinC", "WCoinP", "GoblinPoints", "Zen" };
	const char* coinName = (this->m_CostType >= 0 && this->m_CostType <= 3) ? coinNames[this->m_CostType] : "Coins";
	sprintf_s(costText, "Cost: %d %s", this->m_CostValue, coinName);
	CustomFont.Draw(CustomFont.FontBold, (int)(startX + 20), (int)(startY + 195), 0xFFFF00FF, 0, 180, 0, 3, costText);

	// Apply & Close Buttons
	float btnX = startX + 35.0f;
	float btnY = startY + 225.0f;
	if (gElemental.gDrawButtonProTecno(btnX, btnY, 65.0f, 13, "Apply", 65.0f))
	{
		this->SendApplyRequest();
	}

	float closeBtnX = startX + 120.0f;
	if (gElemental.gDrawButtonProTecno(closeBtnX, btnY, 65.0f, 13, "Close", 65.0f))
	{
		this->CloseWindow();
	}

	this->UpdateMouse();
}

void CCustomItemColor::UpdateMouse()
{
	if (!this->m_WindowOpen)
	{
		return;
	}

	float startX = 210.0f;
	float startY = 60.0f;
	float sliderRX = startX + 75.0f;
	float sliderTrackW = 120.0f;

	int mouseX = pCursorX;
	bool isMouseDown = (GetKeyState(VK_LBUTTON) & 0x8000) != 0;

	if (isMouseDown)
	{
		// Red Slider (R)
		if (pCheckMouseOver(sliderRX - 5, startY + 68.0f, sliderTrackW + 10, 20.0f))
		{
			float pos = (float)(mouseX - sliderRX) / sliderTrackW;
			if (pos < 0.0f) pos = 0.0f;
			if (pos > 1.0f) pos = 1.0f;
			this->m_ColorR = (BYTE)(pos * 255.0f);
		}
		// Green Slider (G)
		else if (pCheckMouseOver(sliderRX - 5, startY + 98.0f, sliderTrackW + 10, 20.0f))
		{
			float pos = (float)(mouseX - sliderRX) / sliderTrackW;
			if (pos < 0.0f) pos = 0.0f;
			if (pos > 1.0f) pos = 1.0f;
			this->m_ColorG = (BYTE)(pos * 255.0f);
		}
		// Blue Slider (B)
		else if (pCheckMouseOver(sliderRX - 5, startY + 128.0f, sliderTrackW + 10, 20.0f))
		{
			float pos = (float)(mouseX - sliderRX) / sliderTrackW;
			if (pos < 0.0f) pos = 0.0f;
			if (pos > 1.0f) pos = 1.0f;
			this->m_ColorB = (BYTE)(pos * 255.0f);
		}
	}
}
