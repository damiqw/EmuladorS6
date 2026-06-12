#pragma once

struct ITEM_INFO2
{
	char Name[30];
	BYTE TwoHand;
	WORD Level;
	BYTE Slot;
	WORD Skill;
	BYTE Width;
	BYTE Height;
	BYTE DamageMin;
	BYTE DamageMax;
	BYTE DefenseSuccessRate;
	BYTE Defense;
	BYTE MagicDefense;
	BYTE AttackSpeed;
	BYTE WalkSpeed;
	BYTE Durability;
	BYTE MagicDurability;
	BYTE MagicDamageRate;
	WORD RequireStrength;
	WORD RequireDexterity;
	WORD RequireEnergy;
	WORD RequireVitality;
	WORD RequireLeadership;
	WORD RequireLevel;
	BYTE Value;
	DWORD BuyMoney;
	BYTE SetAttr;
	BYTE RequireClass[7];
	BYTE Resistance[7];
};

#define GetItemInfo(x) (ITEM_INFO2*)(*(DWORD*)(0x08128AC0) + x * sizeof(ITEM_INFO2))

#define INVENTORY_WEAR_SIZE 12
#define INVENTORY_EXT1_SIZE 76
#define INVENTORY_EXT2_SIZE 108

#define GetChangeUp(x) (((x>>4)&0x01)?3:(((x>>3)&0x01)?2:1))

void InitItemMove();
bool EquipmentWindowProcess(LPVOID WindowThis);
bool UpdateMouseEvent(DWORD* WindowThis);
void RightClickMoveItem();
void RightClickDeleteItem(BYTE result);
BYTE GetInventoryWearSlot(int ItemIndex);