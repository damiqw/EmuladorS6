#include "stdafx.h"
#include "ItemMove.h"
#include "Offset.h"
#include "Protect.h"
#include "Item.h"
#include "Util.h"
#include "Import.h"

bool ItemMove = false;
int SourceFlag = -1;
int SourceSlot = -1;
int TargetSlot = -1;

void InitItemMove() // OK
{
	SetCompleteHook(0xE8,0x00834682,&EquipmentWindowProcess);

	SetCompleteHook(0xE8,0x00860AE8,&UpdateMouseEvent);
}

bool EquipmentWindowProcess(LPVOID WindowThis) // OK
{
	if(ItemMove)
	{
		return true;
	}

	return ((bool(__thiscall*)(LPVOID))0x00837A30)(WindowThis);
}

bool UpdateMouseEvent(DWORD* WindowThis) // OK
{
	RightClickMoveItem();

	return ((bool(__thiscall*)(DWORD))0x008159D0)(*(DWORD*)WindowThis);
}

void RightClickMoveItem()
{
	// ============================================================
	// ✅ FIX: Block auto-wear if CTRL is pressed (PK mode)
	// ============================================================
	if (GetKeyState(VK_CONTROL) & 0x8000)
	{
		return; // Do NOT auto-equip the item
	}

	// ============================================================
	// ✅ ORIGINAL RIGHT-CLICK LOGIC
	// ============================================================

	if (!ppMousePress(VK_RBUTTON) || PickedItem || ItemMove)
	{
		return;
	}

	if (pCheckWindow(pWindowThis(), 9) == 0 && pCheckWindow(pWindowThis(), 13) == 0) // ChaosBox ~ Inventory
	{
		return;
	}

	ItemMove = false;
	SourceFlag = -1;

	SourceSlot = *(DWORD*)((DWORD)InventoryThis(pWindowThis()) + 284);
	TargetSlot = -1;

	if (SourceSlot >= 0 && SourceSlot < INVENTORY_WEAR_SIZE)
	{
		if (*(DWORD*)MAIN_CURRENT_MAP == 10 || *(DWORD*)MAIN_CURRENT_MAP == 39)
		{
			if (SourceSlot == 7 &&
				GetItemEquipedIndex(8) != GET_ITEM(13, 3) &&
				GetItemEquipedIndex(8) != GET_ITEM(13, 4) &&
				GetItemEquipedIndex(8) != GET_ITEM(13, 37))
			{
				return;
			}

			if (SourceSlot == 8 &&
				(GetItemEquipedIndex(8) == GET_ITEM(13, 3) ||
					GetItemEquipedIndex(8) == GET_ITEM(13, 4) ||
					GetItemEquipedIndex(8) == GET_ITEM(13, 37)) &&
				GetItemEquipedIndex(7) == 0xFFFF)
			{
				return;
			}
		}

		DWORD ItemStruct = GetItemEquiped(SourceSlot);

		if (ItemStruct && GetItemEquipedIndex(SourceSlot) != 0xFFFF)
		{
			ITEM_INFO2* lpItemInfo = GetItemInfo(*(WORD*)ItemStruct);

			TargetSlot = InventoryFindEmptySlot(InventoryThis(pWindowThis()), lpItemInfo->Width, lpItemInfo->Height);

			if (TargetSlot != -1)
			{
				SendRequestEquipmentItem(0, SourceSlot, ItemStruct, 0, INVENTORY_WEAR_SIZE + TargetSlot);
				ResetMouseRButton();
				ItemMove = true;
				SourceFlag = 0;
			}
		}
	}
	else
	{
		int InventoryMain = InventoryFindItemSlot(GetMyInventoryCtrl(InventoryThis(pWindowThis()), 0), pCursorX, pCursorY);
		int InventoryExpand1 = InventoryFindItemSlot(GetMyInventoryCtrl(InventoryThis(pWindowThis()), 1), pCursorX, pCursorY);
		int InventoryExpand2 = InventoryFindItemSlot(GetMyInventoryCtrl(InventoryThis(pWindowThis()), 2), pCursorX, pCursorY);

		if (pCheckWindow(pWindowThis(), 9) != 0)
		{
			DWORD MixItemStruct = (DWORD)InventoryFindItem(MixGetMyInventoryCtrl(MixInventoryThis(pWindowThis())), pCursorX, pCursorY);

			if (MixItemStruct)
			{
				ITEM_INFO2* lpItemInfo = GetItemInfo(*(WORD*)MixItemStruct);

				SourceSlot = InventoryFindItemSlot(MixGetMyInventoryCtrl(MixInventoryThis(pWindowThis())), pCursorX, pCursorY);
				TargetSlot = InventoryFindEmptySlot(InventoryThis(pWindowThis()), lpItemInfo->Width, lpItemInfo->Height);

				if (SourceSlot != -1 && TargetSlot != -1)
				{
					SendRequestEquipmentItem(3, SourceSlot, MixItemStruct, 0, INVENTORY_WEAR_SIZE + TargetSlot);
					ResetMouseRButton();
					ItemMove = true;
					SourceFlag = 1;
				}
			}
			else
			{
				DWORD InventoryCtrl = -1;

				DWORD ItemStruct = (DWORD)InventoryFindItemAtPt(InventoryThis(pWindowThis()), pCursorX, pCursorY, &InventoryCtrl);

				if (ItemStruct)
				{
					ITEM_INFO2* lpItemInfo = GetItemInfo(*(WORD*)ItemStruct);

					if (InventoryMain != -1)
						SourceSlot = INVENTORY_WEAR_SIZE + InventoryMain;
					else if (InventoryExpand1 != -1)
						SourceSlot = INVENTORY_EXT1_SIZE + InventoryExpand1;
					else if (InventoryExpand2 != -1)
						SourceSlot = INVENTORY_EXT2_SIZE + InventoryExpand2;

					TargetSlot = InventoryMixFindEmptySlot(MixGetMyInventoryCtrl(MixInventoryThis(pWindowThis())), lpItemInfo->Width, lpItemInfo->Height);

					if (SourceSlot != -1 && TargetSlot != -1)
					{
						SendRequestEquipmentItem(0, SourceSlot, ItemStruct, 3, TargetSlot);
						ResetMouseRButton();
						ItemMove = true;
						SourceFlag = 0;
					}
				}
			}
		}
		else
		{
			if (pCheckWindow(pWindowThis(), 7) != 0 || pCheckWindow(pWindowThis(), 8) != 0) // Trade ~ Warehouse
			{
				return;
			}

			DWORD InventoryCtrl = -1;

			DWORD ItemStruct = (DWORD)InventoryFindItemAtPt(InventoryThis(pWindowThis()), pCursorX, pCursorY, &InventoryCtrl);

			if (ItemStruct)
			{
				if (InventoryMain != -1)
					SourceSlot = INVENTORY_WEAR_SIZE + InventoryMain;
				else if (InventoryExpand1 != -1)
					SourceSlot = INVENTORY_EXT1_SIZE + InventoryExpand1;
				else if (InventoryExpand2 != -1)
					SourceSlot = INVENTORY_EXT2_SIZE + InventoryExpand2;

				TargetSlot = GetInventoryWearSlot(*(WORD*)ItemStruct);

				if (SourceSlot != -1 && TargetSlot != 0xFF)
				{
					SendRequestEquipmentItem(0, SourceSlot, ItemStruct, 0, TargetSlot);
					ResetMouseRButton();
					ItemMove = true;
					SourceFlag = 0;
				}
			}
		}
	}
}

void RightClickDeleteItem(BYTE result) // OK
{
	if(ItemMove)
	{
		if(result != 0xFF)
		{
			if(SourceFlag == 0)
			{
				if(SourceSlot >= 0 && SourceSlot < INVENTORY_WEAR_SIZE)
				{
					InventoryUnequipItem(InventoryThis(pWindowThis()),SourceSlot);
				}
				else if(SourceSlot >= INVENTORY_WEAR_SIZE)
				{
					InventoryDeleteItem(InventoryThis(pWindowThis()),SourceSlot-INVENTORY_WEAR_SIZE);
				}
			}
			else
			{
				InventoryMixDeleteItem(MixInventoryThis(pWindowThis()),SourceSlot);
			}
		}

		ItemMove = false;
	}
}

BYTE GetInventoryWearSlot(int ItemIndex) // OK
{
	int slot = 0xFF;

	ITEM_INFO2* lpItemInfo = GetItemInfo(ItemIndex);

	BYTE Class = ((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7);

	BYTE ChangeUp = GetChangeUp(*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B));

	WORD ItemR = GetItemEquipedIndex(0);
	WORD ItemL = GetItemEquipedIndex(1);
	WORD RingR = GetItemEquipedIndex(10);
	WORD RingL = GetItemEquipedIndex(11);
	WORD EarringR = GetItemEquipedIndex(13);
	WORD EarringL = GetItemEquipedIndex(14);

	if(lpItemInfo->Slot >= 0 && lpItemInfo->Slot < INVENTORY_WEAR_SIZE)
	{
		if(lpItemInfo->TwoHand == 0)
		{
			if(lpItemInfo->Slot == 0 && ItemR != 0xFFFF && ItemL == 0xFFFF)
			{
				ITEM_INFO2* lpItemRight = GetItemInfo(ItemR);

				if(lpItemRight->TwoHand == 0)
				{
					slot = 1;
				}
			}
			else if(lpItemInfo->Slot == 1 && ItemL != 0xFFFF && ItemR == 0xFFFF)
			{
				ITEM_INFO2* lpItemLeft = GetItemInfo(ItemL);

				if(lpItemLeft->TwoHand == 0)
				{
					slot = 1;
				}
			}
			else if(lpItemInfo->Slot == 10 && RingR != 0xFFFF && RingL == 0xFFFF)
			{
				slot = 11;
			}
			else if (lpItemInfo->Slot == 13 && EarringR != 0xFFFF && EarringL == 0xFFFF)
			{
				slot = 14;
			}
		}

		if(GetItemEquipedIndex(lpItemInfo->Slot) == 0xFFFF)
		{
			slot = lpItemInfo->Slot;
		}
	}

	bool bEquipable = false;

	if(lpItemInfo->RequireClass[Class])
	{
		bEquipable = true;
	}
	else if(Class == 3 && lpItemInfo->RequireClass[0] && lpItemInfo->RequireClass[1])
	{
		bEquipable = true;
	}

	if(lpItemInfo->RequireClass[Class] > ChangeUp)
	{
		bEquipable = false;
	}

	if(bEquipable == true)
	{
		bEquipable = false;

		if(lpItemInfo->Slot == slot)
		{
			bEquipable = true;
		}
		else if(lpItemInfo->Slot == 0 && slot == 1)
		{
			if((Class == 1 || Class == 3) && lpItemInfo->TwoHand == 0)
			{
				bEquipable = true;
			}
			else if(Class == 5 && !(ItemIndex >= GET_ITEM(5,0) && ItemIndex < GET_ITEM(6,0)))
			{
				bEquipable = true;
			}
		}
		else if(lpItemInfo->Slot == 10 && slot == 11)
		{
			bEquipable = true;
		}
		else if (lpItemInfo->Slot == 13 && slot == 14)
		{
			bEquipable = true;
		}

		if(Class == 2)
		{
			if(lpItemInfo->Slot == 0 && ItemL != GET_ITEM(4,7) && (ItemL >= GET_ITEM(4,0) && ItemL < GET_ITEM(5,0)) && ItemIndex != GET_ITEM(4,15))
			{
				bEquipable = false;
			}
		}
	
		if(Class == 3 && lpItemInfo->Slot == 2)
		{
			bEquipable = false;
		}

		if(Class == 6 && lpItemInfo->Slot == 5)
		{
			bEquipable = false;
		}
	}

	return ((bEquipable) ? slot : 0xFF);
}