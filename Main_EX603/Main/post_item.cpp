#include "stdafx.h"
#include "Defines.h"
#include "Import.h"
#include "Object.h"
#include "post_item.h"
#include "Interface.h"
#include "Protocol.h"
#include "Util.h"
#include <string>
#include "Protect.h"
#include "User.h"

PostItem JCItemPublic;
#if(NEW_POSTITEM)
#include "Chat.h"
#include <regex>
#include "CustomJewelBank.h"
int PostItemColor;
PostItem::PostItem()
{
	//this->Hook();
	this->ClearPostItem();
	this->FontUnderLine = CreateFontA(13, 0, 0, 0, 700, 0, 1, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	PostItemColor = GetPrivateProfileInt("Game", "PostColor", 7, ".\\Config.ini");
	if (PostItemColor < 1 || PostItemColor > 9)
	{
		PostItemColor = 9;
	}
}
PostItem::~PostItem()
{
}
DWORD g_CurrentChatType = 0xFFFFFFFF;

void __declspec (naked) HookRenderNewChat()
{
	static DWORD sub_420150 = 0x00420150;
	static DWORD sub_78C050 = 0x0078C050;
	static DWORD cntAddr = 0x007890A9;
	_asm {
		// Get chat type
		mov ecx, [ebp - 0x2C];
		call sub_78C050;
		mov g_CurrentChatType, eax;

		// Call RenderText
		lea ecx, JCItemPublic;
		call [PostItem::RenderText];

		// Reset global chat type while preserving EAX (return value)
		push eax;
		mov g_CurrentChatType, 0xFFFFFFFF;
		pop eax;

		// Continue original HookRenderNewChat logic
		push	eax;
		mov     ecx, [ebp - 0x2C];
		call	sub_78C050;
		push	eax;
		mov     edx, [ebp - 0x34];
		push    edx;
		mov     eax, [ebp - 0x38];
		push    eax;
		lea		ecx, JCItemPublic;
		call[PostItem::RenderPostItemName];
		jmp		cntAddr;
	}
}
void __declspec (naked) HookNewChatTaget()
{
	static DWORD ho = 0x00E8C588; //0x00E8C58C bold
	static DWORD sub_4200B0 = 0x004200B0;
	static DWORD sub_420040 = 0x00420040;
	static DWORD sub_78C050 = 0x0078C050;
	static DWORD sub_41FE10 = 0x0041FE10;
	static DWORD sub_420120 = 0x00420120;
	static DWORD cntAddr = 0x00788FF7;

	_asm {
		call    sub_420040;
		mov     ecx, [ebp - 0x2C];
		call	sub_78C050;
		cmp		eax, 0xA;
		jle		cancel;
		push	eax;
		lea		ecx, JCItemPublic;
		call[PostItem::ViewPostItem];
	cancel:
		jmp		cntAddr;
	}
}
void __declspec (naked) CheckGetNewChatType()
{
	static DWORD allAddr = 0x0078BAD5;
	static DWORD blkAddr = 0x0078BA95;
	_asm {
		cmp		eax, 0x0A;
		jle		check;
		mov		eax, 0x0;
	check:
		movzx   eax, byte ptr[edx + eax + 0x100];
		test    eax, eax;
		jnz     allowed;
		jmp		blkAddr;
	allowed:
		jmp		allAddr;
	}
}
void __declspec (naked) CheckRenderNewChatType()
{
	static DWORD allAddr = 0x00788C59;
	static DWORD blkAddr = 0x00788C4B;
	_asm {
		cmp		eax, 0x0A;
		jle		check;
		mov		eax, 0x0;
	check:
		movzx	edx, byte ptr[ecx + eax + 0x100];
		test    edx, edx;
		jnz     allowed;
		jmp		blkAddr;
	allowed:
		jmp		allAddr;
	}
}
void __declspec (naked) RenderNewChatType()
{
	static DWORD Addr1 = 0x41FE10;
	static DWORD Addr2 = 0x420040;
	static DWORD Addr3 = 0x4200B0;

	static DWORD alwAddr = 0x00788F29;
	static DWORD denAddr = 0x007890F2;
	_asm {
		movzx eax, al;

		cmp eax, 0x9;
		je render_gold;
		cmp eax, 0x0B;
		jae render_post_item;
		jmp deny;
	render_gold:
		push 0xC8; // Alpha (#D3B42E)
		push 0x2E; // Blue
		push 0xB4; // Green
		push 0xD3; // Red
		call Addr1;
		mov ecx, eax;
		call Addr2;
		push 0x3F; // default transparent BG
		push 0x00;
		push 0x00;
		push 0x00;
		call Addr1;
		mov ecx, eax;
		call Addr3;
		jmp alwAddr;
	render_post_item:
		push 0xC8; // Alpha
		push 0x2E; // Blue
		push 0xB4; // Green
		push 0xD3; // Red
		call Addr1;
		mov ecx, eax;
		call Addr2;
		push 0xFF; // Solid white/light-blue BG
		push 0xC8; // Blue
		push 0xC8; // Green
		push 0xFF; // Red
		call Addr1;
		mov ecx, eax;
		call Addr3;
		jmp alwAddr;
	deny:
		jmp denAddr;
	}
}
void __declspec (naked) HookNewChatSelectType()
{
	static DWORD chatType = 0x0;
	static DWORD jmpAddr = 0x0078A9D3;
	static DWORD outAddr = 0x0078AB06;
	_asm {
		mov chatType, eax
	}
	if (chatType == 9) {
		_asm {
			jmp jmpAddr
		}
	}
	else if (chatType > 10 && chatType < 0xFFFFFFFF)
	{
		_asm {
			jmp jmpAddr
		}
	}
	else {
		_asm {
			jmp outAddr
		}
	}
}
void __declspec (naked) HookAllowCreateChatType()
{
	static DWORD Addr1 = 0x0078BFF1;
	static DWORD Addr2 = 0x0078C017;
	static DWORD chatType;
	_asm {
		cmp dword ptr[ebp - 0x08], 0x0A;
		jne createChat;
		xor al, al
			jmp Addr2;
	createChat:
		jmp Addr1;
	}
	/*if (chatType == 10) {
	_asm {
	jmp Addr2
	}
	}
	else {
	_asm {
	jmp Addr1;
	}
	}*/
}
void __declspec (naked) HookFixGetBgColor() {
	_asm {
		mov     eax, [edx + 0x14];
		call    eax;
		mov     esp, ebp;
		pop		ebp;
		retn;
	}
}
void __declspec (naked) HookFixGenerateItemKey() {
	static DWORD jmpAddr = 0x007E219E;
	_asm {
		mov     dword ptr[edx + 0x24], 0x80000000;
		jmp		jmpAddr;
	}
}
void PostItem::ClearPostItem()
{
	this->IndexCount = 0;
	this->lastPostTickCount = 0;
	for (int i = 0; i < MAX_MESSAGES; i++)
	{
		this->Posts[i].item.ItemID = -1;
	}
}
void PostItem::PostItemProc(DWORD s)
{
	if (s == 0)
		return;

	if (this->lastPostTickCount + DELAY_POST_ITEM >= GetTickCount())
		return;

	if (gInterface.CheckWindow(Trade) ||
		gInterface.CheckWindow(Warehouse) ||
		gInterface.CheckWindow(Shop) ||
		gInterface.CheckWindow(Store) ||
		gInterface.CheckWindow(OtherStore) ||
		gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(ExpandWarehouse))
	{
		return;
	}

	int m_pNewUIMng = ((int(*)()) 0x861110)();
	int m_pNewChatInputBox = ((int(__thiscall*)(int)) 0x00861220)(m_pNewUIMng);
	int m_pChatInputBox = *(DWORD*)(m_pNewChatInputBox + 36);
	HWND hWndEdit = *(HWND*)(m_pChatInputBox + 120);

	const int ChatInputBoxMaxLen = 44;
	char curText[ChatInputBoxMaxLen + 1];
	char newText[ChatInputBoxMaxLen + 1] = { 0, };
	DWORD dwStart = 0, dwEnd = 0;
	DWORD nwStart = 0;
	SendMessage(hWndEdit, EM_GETSEL, (WPARAM)&dwStart, (LPARAM)&dwEnd);
	((void(__thiscall*)(int, LPSTR, int)) 0x004217D0)(m_pChatInputBox, curText, ChatInputBoxMaxLen);
	if (strlen(curText) > ChatInputBoxMaxLen - 10)
	{
		Chat.CreateMessage("", "Text chat Size Overload!", 4);
		this->lastPostTickCount = GetTickCount() + DELAY_POST_ITEM / 2; //block half time on error case;
		return;
	}
	std::string cText = curText;
	char itemcode[10];
	sprintf(itemcode, "[%08X]", s);

	std::regex const expression("\\[[0-9a-fA-F]{8}\\]");

	std::ptrdiff_t const match_pre(std::distance(
		std::sregex_iterator(cText.begin(), cText.end(), expression),
		std::sregex_iterator()));
	if (gInterface.CheckWindow(ChatWindow) && cText.length() == 10 && match_pre == 1) {
		strcat(newText, itemcode);
		nwStart = strlen(newText);
	}
	else if (gInterface.CheckWindow(ChatWindow) && cText.length() && dwStart) {
		if (dwStart != cText.length())
		{
			strcat(newText, cText.substr(0, dwStart).c_str());
			strcat(newText, itemcode);
			nwStart = strlen(newText);
			if (dwEnd != cText.length())
			{
				strcat(newText, cText.substr(dwEnd, cText.length() - dwEnd).c_str());
			}
		}
		else
		{
			strcat(newText, curText);
			strcat(newText, itemcode);
			nwStart = strlen(newText);
		}
	}
	else {
		strcat(newText, itemcode);
		nwStart = strlen(newText);
	}
	std::string const text = newText;

	std::ptrdiff_t const match_count(std::distance(
		std::sregex_iterator(text.begin(), text.end(), expression),
		std::sregex_iterator()));
	if (match_count > 1) {
		Chat.CreateMessage("", "You can't post more than 1 item per times", 4);
		this->lastPostTickCount = GetTickCount() + DELAY_POST_ITEM / 2; //block half time on error case;
		return;
	}
	gInterface.OpenWindow(ChatWindow);

	if (gInterface.CheckWindow(ChatWindow)) {
		PostMessageW(hWndEdit, EM_SETSEL, nwStart, nwStart);
		((void(__thiscall*)(int, const char* pszText)) 0x00421830)(m_pChatInputBox, newText);
		this->lastPostTickCount = GetTickCount();
	}
	return;
}

int PostItem::CheckItemInfo(int a1)
{
	if (a1 > 3092)
	{
		if (a1 > 4661)
		{
			if (a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173))
				return 0;
		}
		else if (a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)))
		{
			return 0;
		}

		return 1;
	}

	if (a1 >= 3089)
		return 1;

	if (a1 > 2071)
	{
		if (a1 != 2580 && (a1 <= 2589 || a1 > 2592))
			return 0;
		return 1;
	}

	if (a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28))
		return 1;

	return 0;
}

void PostItem::GCPostItem(BYTE* a)
{
	PMSG_POSTITEM_RECV* Data = &*(PMSG_POSTITEM_RECV*)a;
	int index = this->IndexCount % MAX_MESSAGES;
	int Color = TEXT_COLOR_WHITE;
	if (Data->Type > -1)
	{

		DWORD dwAddress;
		int a5;
		int a6;
		int a7;
		int a8;
		int a9;
		DWORD a10;
		dwAddress = (DWORD)&this->Posts[index].item;

		*(WORD*)dwAddress = Data->Type;
		a5 = Data->Dur;
		*(BYTE*)(dwAddress + 22) = a5;
		a6 = Data->Item[3];
		*(BYTE*)(dwAddress + 23) = a6;
		a7 = Data->Item[4];
		*(BYTE*)(dwAddress + 24) = a7;
		a8 = Data->Item[5];
		*(BYTE*)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
		*(BYTE*)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
		*(BYTE*)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
		a9 = Data->Item[6];
		*(WORD*)(dwAddress + 69) = (a9 & 0xF0) >> 4;
		*(WORD*)(dwAddress + 71) = a9 & 0xF;

		a10 = (DWORD)&Data->Item[7];

		if (a10)
		{
			*(BYTE*)(dwAddress + 79) = 5;

			for (int i = 0; i < 5; ++i)
				*(BYTE*)(i + dwAddress + 74) = *(BYTE*)(i + a10);

			for (int j = 0; j < 5; ++j)
			{
				if (*(BYTE*)(j + a10) == 255)
				{
					*(BYTE*)(dwAddress + 79) = j;
					break;
				}

				if (*(BYTE*)(j + a10) == 254)
				{
					*(BYTE*)(j + dwAddress + 80) = -1;
				}
				else
				{
					*(BYTE*)(j + dwAddress + 80) = *(BYTE*)(j + a10) % 50;
					*(BYTE*)(j + dwAddress + 85) = *(BYTE*)(j + a10) / 50 + 1;
				}
			}

			if (this->CheckItemInfo(*(WORD*)dwAddress))
			{
				*(BYTE*)(dwAddress + 90) = a9;
				*(WORD*)(dwAddress + 69) = 0;
				*(WORD*)(dwAddress + 71) = 0;
			}
			else
			{
				*(BYTE*)(dwAddress + 90) = -1;
			}
		}
		else
		{
			*(BYTE*)(dwAddress + 79) = 0;
		}

		*(BYTE*)(dwAddress + 96) = 0;
		*(DWORD*)(dwAddress + 103) = 1;

		if (Data->PeriodTime)
		{
			this->Posts[index].item.PeriodItem = 1;
			this->Posts[index].item.ExpireDateConvert = Data->PeriodTime;
		}

		((char(__thiscall*)(int This, ObjectItem * ip, unsigned __int8 Attribute1, unsigned __int8 Attribute2, unsigned __int8 Attribute3)) 0x007E22A0)(*(DWORD*)(GetInstance() + 308), &this->Posts[index].item, Data->Item[1], Data->Item[3], Data->Item[4]);


		lpItemObj ip = &this->Posts[index].item;

		char Text[100] = { 0, };
		//std::string TextBB;
		//pDrawMessage(Data->chatid, 2);
		//pDrawMessage(Data->pre, 1);

		if (strlen(Data->pre)) {
			strcat(Text, Data->pre);
			//TextBB += Data->pre;
		}
		else
		{
			//TextBB += " ";
			strcat(Text, " "); //atleast 1 character like " " to make the chat avaiable | it nhat la " " de chat hoat dong
		}
		if (strlen(Data->suf) && strlen(Data->suf) < 35)
		{
			ZeroMemory(this->Posts[index].suf, sizeof(this->Posts[index].suf));
			strcat(this->Posts[index].suf, Data->suf);
		}

		int Level = (ip->Level >> 3) & 15;
		((void(__cdecl*)(int iType, int iLevel, char* Text)) 0x005C2430)(ip->ItemID, Level, this->Posts[index].ItemName);

		Chat.CreateMessage(Data->chatid, Text, CHAT_TYPE_START + index);

		if (((BOOL(__stdcall*)(int)) 0x007E7820)(ip->ItemID)) //check divine weapon
		{
			Color = TEXT_COLOR_PURPLE;
		}
		else if (((BOOL(__stdcall*)(int)) 0x007E7870)(ip->ItemID)) //check wings
		{
			if (Level < 7)
				Color = TEXT_COLOR_WHITE;
			else
				Color = TEXT_COLOR_YELLOW;
		}
		else if (ip->AncientOption % 0x04 != 1 && ip->AncientOption % 0x04 != 2)
		{ //check ancient
			if (((int(__stdcall*)(lpItemObj)) 0x00968130)(ip)) //check socket
			{
				Color = TEXT_COLOR_VIOLET;
			}
			else if (ip->SpecialCount <= 0 || (ip->ExcellentOption & 0x3F) <= 0)
			{
				if (Level < 7)
				{
					if (ip->SpecialCount <= 0)
						Color = TEXT_COLOR_WHITE;
					else
						Color = TEXT_COLOR_BLUE;
				}
				else {
					Color = TEXT_COLOR_YELLOW;
				}
			}
			else {
				Color = TEXT_COLOR_GREEN;
			}
		}
		else {
			Color = TEXT_COLOR_GREEN_BLUE;
		}
		if (ip->ItemID != 6660 && ip->ItemID != 6661)
		{
			if (ip->ItemID >= ITEM_POTION + 23 && ip->ItemID <= ITEM_POTION + 26)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 15)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 14)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_POTION + 21)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 19)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 20)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 107)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_POTION + 28)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ip->ItemID == ITEM_HELPER + 37)
			{
				Color = TEXT_COLOR_BLUE;
			}
			else if (ip->ItemID == ITEM_POTION + 11)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if ((ip->ItemID >= ITEM_WING + 60 && ip->ItemID <= ITEM_WING + 65)
				|| (ip->ItemID >= ITEM_WING + 70 && ip->ItemID <= ITEM_WING + 74)
				|| (ip->ItemID >= ITEM_WING + 100 && ip->ItemID <= ITEM_WING + 129))
			{
				Color = TEXT_COLOR_VIOLET;
			}
			else if (ip->ItemID == ITEM_POTION + 111)
			{
				Color = TEXT_COLOR_YELLOW;
			}
			else if (ITEM_POTION + 101 <= ip->ItemID && ip->ItemID <= ITEM_POTION + 109)
			{
				Color = TEXT_COLOR_YELLOW;
			}
		}
		else
		{
			Color = TEXT_COLOR_BLUE;
		}

		int nGemType = ((int(__cdecl*)(int _nJewel, char _nType, bool _bModel)) 0x004E0F10)(ip->ItemID, 0, 0);
		if (nGemType != -1) {
			Color = TEXT_COLOR_YELLOW;
		}
	}

	this->Posts[index].ClrType = Color;
	this->IndexCount++;
}

void PostItem::CDActionItem(void* item_data)
{
	// check window, not allow for shop, inventory, warehouse, etc
	if (gInterface.CheckWindow(Trade) ||
		gInterface.CheckWindow(Warehouse) ||
		gInterface.CheckWindow(Shop) ||
		gInterface.CheckWindow(Store) ||
		gInterface.CheckWindow(OtherStore) ||
		gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(ExpandWarehouse))
	{
		return;
	}

	if (GetKeyState(VK_RBUTTON) & 0x8000 && GetKeyState(VK_CONTROL) & 0x8000)
	{
		if (GetTickCount() <= JCItemPublic.last_tickcount_post_ + 3000) { return; }

		PMSG_POSTITEM iMsg = { '\0' };
		strcpy_s(iMsg.chatmsg, (char*)pCurrentViewingItemName);
		memcpy_s(&iMsg.chatid[0], 10, (char*)oUserObjectStruct_, 10);
		memcpy_s(&iMsg.item_data[0], 107, item_data, 107);
		iMsg.h.set(0x78, sizeof(iMsg));
		DataSend((LPBYTE)&iMsg, iMsg.h.size);
		JCItemPublic.last_tickcount_post_ = GetTickCount();
	}
#if(RIGHT_CLIK)
	//Click Derecho
	else if (GetKeyState(VK_RBUTTON) & 0x8000
		&& GetTickCount() >= JCItemPublic.last_tickcount_moveitem_ + 300)
	{
		ObjectItem* lItem = (ObjectItem*)item_data;

		if (lItem->ItemID < 0) { return; }

		PMSG_ITEM_MOVE_RECV pMsg = { 0 };

		pMsg.h.set(0x79, 0x01, sizeof(pMsg));
		pMsg.Target = -1;

		if (gInterface.CheckWindow(ChaosBox) && gInterface.CheckWindow(Inventory))
		{
			if ((pCursorX > 460))
			{
				pMsg.sFlag = 0;
				pMsg.tFlag = 3;
				pMsg.Target = 0;
				pMsg.Source = lItem->PosX + lItem->PosY * 8 + 12;
			}
			else if (gInterface.CheckWindow(ExpandInventory) && pCursorX > 260)
			{
				pMsg.sFlag = 0;
				pMsg.tFlag = 3;
				pMsg.Target = 0;
				pMsg.Source = lItem->PosX + lItem->PosY * 8 + 12 + 64;
				if (pCursorY > 130)
					pMsg.Source += 32;
			}
			else
			{
				pMsg.sFlag = 3;
				pMsg.tFlag = 0;
				pMsg.Target = 0;
				pMsg.Source = lItem->PosX + lItem->PosY * 8;
			}
		}
		else
		{
			float v1 = 0;
			if (gInterface.CheckWindow(Character))
				v1 = *(float*)(0x00D24E88);
			if ((pCursorX > 460 - v1))
			{
				pMsg.sFlag = 0;
				pMsg.tFlag = 0;
				pMsg.Source = lItem->PosX + lItem->PosY * 8 + 12;

			}
			else if (gInterface.CheckWindow(ExpandInventory) && pCursorX > 260 - v1)
			{
				pMsg.sFlag = 0;
				pMsg.tFlag = 0;
				pMsg.Source = lItem->PosX + lItem->PosY * 8 + 12 + 64;
				if (pCursorY > 130)
					pMsg.Source += 32;
			}
			pMsg.Target = 0;
		}

		DataSend((BYTE*)&pMsg, pMsg.h.size);
		JCItemPublic.last_tickcount_moveitem_ = GetTickCount();
	}
#endif
}

void HookRenderItemToolTip(int a1)
{
	((void(__cdecl*)()) 0x007DCF20)();
	lpItemObj item = (lpItemObj) * (DWORD*)(a1 + 84);
	//===Fix Move Item

	//===
	if (gInterface.CheckWindow(8))
	{
		return;
	}
	DWORD uniqId = 0;
	if (item) {
		int pos = -1;
		if (a1 == *(DWORD*)(*(DWORD*)0x098670B8 + 0x18))
		{
			uniqId = item->UniqueID;
		}
		else if (a1 == *(DWORD*)(*(DWORD*)0x098670B8 + 0x1C))
		{
			uniqId = item->UniqueID + 0x10000000;
		}
		else if (a1 == *(DWORD*)(*(DWORD*)0x098670B8 + 0x20))
		{
			uniqId = item->UniqueID + 0x20000000;
		}
		//
		// CTRL + Right Click (block equip / block move)
		if ((GetKeyState(VK_RBUTTON) & 0x8000) && (GetKeyState(VK_CONTROL) & 0x8000))
		{
			JCItemPublic.PostItemProc(uniqId); // your link item function
			return; // IMPORTANT: block default MU behavior
		}

		else
		{
			// === Right click = Jewel Bank ===
			if (GetKeyState(VK_RBUTTON) & 0x8000 && GetKeyState(VK_SHIFT) & 0x8000)
			{
				// panel: normal / expanded / 2nd inventory
				int panel = *(DWORD*)(a1 + 44);


				if (panel == 200 || panel == 44 || panel == 131)
				{
					int start = (panel == 200) ? 12 : (panel == 44) ? 76 : 108;
					int Slot = item->PosX + (item->PosY * 8) + start;

					gCustomJewelBank.JewelBankSend(Slot);
					return;
				}
			}
			// === Default Right click = move / equip etc ===
			if (!pIsKeyRepeat(VK_CONTROL))
			{
				JCItemPublic.CDActionItem(item);
				return;
			}
		}
	}
}

void PostItem::Hook()
{
	//MemorySet(0x0070725C, 0x90, 5);
	//MemorySet(0x00707CB0, 0x90, 5);
	//MemorySet(0x007071D8, 0x90, 5);

	SetCompleteHook(0xE8, 0x007DD0D9, &HookRenderItemToolTip);
	SetCompleteHook(0xE9, 0x0078BFE7, &HookAllowCreateChatType);
	SetCompleteHook(0xE9, 0x0078BFE7, &HookAllowCreateChatType);
	SetCompleteHook(0xE9, 0x0078A9CA, &HookNewChatSelectType);
	SetCompleteHook(0xE9, 0x00788EE7, &RenderNewChatType);
	SetCompleteHook(0xE9, 0x00788C3F, &CheckRenderNewChatType);
	SetCompleteHook(0xE9, 0x0078BA89, &CheckGetNewChatType);
	SetCompleteHook(0xE9, 0x00788FF2, &HookNewChatTaget);
	SetCompleteHook(0xE9, 0x007890A4, &HookRenderNewChat);
	SetCompleteHook(0xE8, 0x0078B0CF, &HookRenderFrame);
	SetCompleteHook(0xE8, 0x0078707F, &HookSendChat);
	//fix core
	SetCompleteHook(0xE9, 0x007E2197, &HookFixGenerateItemKey);
	SetCompleteHook(0xE9, 0x0042002E, &HookFixGetBgColor);
#if(RIGHT_CLICK)
	SetCompleteHook(0xE9, 0x0083B7E4 + 0x150, &Equipments);//1.04D->0x0083B7E4
#endif
}
bool PostItem::ViewPostItem(int type)
{
	if (type < CHAT_TYPE_START || type >= (CHAT_TYPE_START + MAX_MESSAGES))
	{
		return false;
	}

	int index = type - CHAT_TYPE_START;
	JCItemPublic.viewing = index;
	return true;
}
void PostItem::RenderItem()
{
	if (JCItemPublic.viewing < 0 || JCItemPublic.viewing > MAX_MESSAGES)
	{
		return;
	}

	if (*(int*)0x879340C <= JCItemPublic.maxX)
	{
		if (*(int*)0x879340C >= JCItemPublic.minX) //check min
		{
			lpItemObj item = &JCItemPublic.Posts[JCItemPublic.viewing].item;

			if (item && item->ItemID == -1)
			{
				return;
			}
			//JCCoord JCShowSellItem;
			//
			//JCShowSellItem.X = 320;
			//JCShowSellItem.Y = (int)150;

			//sub_7E3E30(*(DWORD*)(GetInstance() + 308), JCShowSellItem, (int)item, 0, 0, 0);
			gInterface.DrawItemToolTipText(item, 340, 120); //vi tri

			gInterface.item_post_ = item;
			gObjUser.PostItemID = item->ItemID;
			gObjUser.PostItemLV = item->Level;
			gObjUser.PostItemExc = item->ExcellentOption;
			gObjUser.PostItemAcc = item->AncientOption;
			gObjUser.PostItem380 = item->Is380Item;
			gObjUser.PostItemHarmony = item->HarmonyValue;
			gObjUser.PostItemSocket = item->SocketOption;
			gObjUser.PostItemX = item->PosX;
			gObjUser.PostItemY = item->PosY;

		}
	}
}
bool PostItem::HookRenderFrame(int a1)
{
	bool result = ((bool(__thiscall*)(int)) 0x00789110)(a1);

	JCItemPublic.RenderItem();
	JCItemPublic.viewing = -1;
	return result;
}
int	PostItem::RenderText(int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, OUT SIZE* lpTextSize)
{
	SIZE textSize;
	((int(__thiscall*)(int This, int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, OUT SIZE * lpTextSize)) 0x00420150)
		(((int(*)()) 0x0041FE10)(), PosX, PosY, Text, Width, Height, Align, &textSize); //String 1
	return textSize.cx;
}
void PostItem::RenderPostItemName(int x, int y, int type, int width)
{
	if (type < CHAT_TYPE_START || type >= (CHAT_TYPE_START + MAX_MESSAGES))
	{
		return;
	}

	int index = type - CHAT_TYPE_START;

	if (JCItemPublic.Posts[index].item.ItemID == -1)
	{
		return;
	}

	DWORD clrB = ((DWORD(__thiscall*)(DWORD)) 0x0041FFE0)(((int(*)()) 0x0041FE10)());// ok
	DWORD bgcB = 0;
	bool isSuf = strlen(JCItemPublic.Posts[index].suf);
	if (isSuf)
	{
		bgcB = ((DWORD(__thiscall*)(DWORD)) 0x00420010)(((int(*)()) 0x0041FE10)());
	}


	SIZE textSize;
	((int(__thiscall*)(int, HFONT)) 0x00420120)(((int(*)()) 0x0041FE10)(), JCItemPublic.FontUnderLine); //Set Font Name Item
	JCItemPublic.SetColor(JCItemPublic.Posts[index].ClrType);
	//=Item Name
	char ItemName[120] = { 0 };
	wsprintf(ItemName, "[%s]", JCItemPublic.Posts[index].ItemName);

	((int(__thiscall*)(int This, int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, OUT SIZE * lpTextSize)) 0x00420150)
		(((int(*)()) 0x0041FE10)(), x + width, y, ItemName, 0, 0, (LPINT)0, &textSize);
	((int(__thiscall*)(int, HFONT)) 0x00420120)(((int(*)()) 0x0041FE10)(), *(HFONT*)0x00E8C588);
	if (isSuf)
	{
		((DWORD(__thiscall*)(DWORD, DWORD)) 0x00420080)(((int(*)()) 0x0041FE10)(), clrB);
		((DWORD(__thiscall*)(DWORD, DWORD)) 0x004200F0)(((int(*)()) 0x0041FE10)(), bgcB);
		((int(__thiscall*)(int This, int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, OUT SIZE * lpTextSize)) 0x00420150)
			(((int(*)()) 0x0041FE10)(), x + width + textSize.cx, y, JCItemPublic.Posts[index].suf, 0, 0, (LPINT)0, 0);
	}

	if (JCItemPublic.viewing == index) {
		JCItemPublic.maxX = x + width + textSize.cx;
		JCItemPublic.minX = x + width;
	}
}
void PostItem::SetColor(int type)
{

	switch (type)
	{
	case TEXT_COLOR_WHITE:
	case TEXT_COLOR_DARKRED:
	case TEXT_COLOR_DARKBLUE:
	case TEXT_COLOR_DARKYELLOW:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 0xff, 0xff, 0xff, 0xff);
		break;
	case TEXT_COLOR_BLUE:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 0x7F, 0xB2, 0xFF, 0xff);
		break;
	case TEXT_COLOR_GRAY:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 102, 102, 102, 0xff);
		break;
	case TEXT_COLOR_GREEN_BLUE:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 255, 255, 255, 0xff);
		break;
	case TEXT_COLOR_RED:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 255, 50, 25, 0xff);
		break;
	case TEXT_COLOR_YELLOW:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 255, 204, 25, 0xff);
		break;
	case TEXT_COLOR_GREEN:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 25, 255, 128, 0xff);
		break;
	case TEXT_COLOR_PURPLE:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 255, 25, 255, 0xff);
		break;
	case TEXT_COLOR_REDPURPLE:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 204, 128, 204, 0xff);
		break;
	case TEXT_COLOR_VIOLET:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 179, 102, 255, 0xff);
		break;
	case TEXT_COLOR_ORANGE:
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 230, 107, 10, 0xff);
		break;
	}

	if (TEXT_COLOR_DARKRED == type)
	{
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x004200B0)(((int(*)()) 0x0041FE10)(), 160, 0, 0, 255);
	}
	else if (TEXT_COLOR_DARKBLUE == type)
	{
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x004200B0)(((int(*)()) 0x0041FE10)(), 0, 0, 160, 255);
	}
	else if (TEXT_COLOR_DARKYELLOW == type)
	{
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x004200B0)(((int(*)()) 0x0041FE10)(), 160, 102, 0, 255);
	}
	else if (TEXT_COLOR_GREEN_BLUE == type)
	{
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x004200B0)(((int(*)()) 0x0041FE10)(), 60, 60, 200, 255);
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x00420040)(((int(*)()) 0x0041FE10)(), 0, 255, 0, 255);
	}
	else
	{
		((int(__thiscall*)(int This, DWORD, DWORD, DWORD, DWORD)) 0x004200B0)(((int(*)()) 0x0041FE10)(), 0, 0, 0, 0x3F);
	}
}
bool isPostItemChat(std::string s, DWORD* u, int* p)
{
	std::smatch m;
	std::regex e("\\[[0-9a-fA-F]{8}\\]");
	std::regex_search(s, m, e);

	if (m.size() < 1) {
		return false;
	}
	*p = m.position(0);
	*u = std::stoul(s.substr(m.position(0) + 1, 10 - 2), 0, 16);
	return true;
}
void PostItem::HookSendChat(const char* Text)
{
	char pretext[35] = { 0, };
	char suftext[35] = { 0, };
	DWORD uniqID = 0;
	short pos = -1;
	int  sP = 0;
	std::string s = Text;

	char lspzCommand[5] = { '/', '!', '~', '@', '$' };

	if (strlen(Text) < 10) {
		return ((void(__cdecl*)(const char*)) 0x005BDE40)(Text);
	}
	for (int i = 0; i < sizeof(lspzCommand); i++) {
		if (Text[0] == lspzCommand[i]) {
			return ((void(__cdecl*)(const char*)) 0x005BDE40)(Text);
		}
	}
	if (!isPostItemChat(s, &uniqID, &sP) || sP == -1) {
		return ((void(__cdecl*)(const char*)) 0x005BDE40)(Text);
	}
	if (uniqID - 0x20000000 > 0x80000000) {
		uniqID -= 0x20000000;
		pos = 12 + 64 + 32;
	}
	else if (uniqID - 0x10000000 > 0x80000000) {
		uniqID -= 0x10000000;
		pos = 12 + 64;
	}
	else if (uniqID > 0x80000000) {
		pos = 12;
	}
	if (pos == -1) {
		return ((void(__cdecl*)(const char*)) 0x005BDE40)(Text);
	}

	int m_pNewUIMng = ((int(*)()) 0x861110)();
	int m_pNewMyInventory = ((int(__thiscall*)(int)) 0x00861260)(m_pNewUIMng);
	lpItemObj item = ((lpItemObj(__thiscall*)(DWORD, DWORD, int)) 0x008357D0)(m_pNewMyInventory, uniqID, 0);
	if (item == 0)
	{
		Chat.CreateMessage("", "Item data has been changed, please try it again.", 4);
		return;
	}
	pos += item->PosX + item->PosY * 8;
	JCItemPublic.CGPostItem(pos, s.substr(0, min(sP, 34)).c_str(), s.substr(sP + 10, s.length() - (sP + 10)).c_str());
}

void PostItem::CGPostItem(DWORD pos, const char* pre, const char* suf) {

	PMSG_POSTITEM_SEND iMsg = { '\0' };

	iMsg.pos = pos;
	ZeroMemory(iMsg.pre, sizeof(iMsg.pre));
	ZeroMemory(iMsg.suf, sizeof(iMsg.suf));
	strcat(iMsg.pre, pre);
	strcat(iMsg.suf, suf);

	iMsg.h.set(0x78, sizeof(iMsg));
	DataSend((LPBYTE)&iMsg, iMsg.h.size);
}

#if(RIGHT_CLICK)
// -----------------------------------------------------------------------------
//clic right
void __declspec (naked) PostItem::Equipments()
{
	static DWORD mem = 0;
	_asm {
		mov eax, dword ptr ds : [ebp - 04]
		mov mem, eax
	}
	RemoveEquipment((void*)mem);
	_asm {
		mov esp, ebp
		pop ebp
		ret 0004
	}
}

void PostItem::RemoveEquipment(void* item_data)
{
	// check window, not allow for shop, inventory, warehouse, etc
	if (gInterface.CheckWindow(Trade) ||
		gInterface.CheckWindow(Warehouse) ||
		gInterface.CheckWindow(Shop) ||
		gInterface.CheckWindow(Store) ||
		gInterface.CheckWindow(OtherStore) ||
		gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(ExpandWarehouse))
	{
		return;
	}
	if (GetKeyState(VK_RBUTTON) & 0x8000 && GetTickCount() >= JCItemPublic.last_tickcount_moveitem_ + 250) {

		ObjectItem* lItem = (ObjectItem*)item_data;

		if (lItem->ItemID < 0) { return; }

		PMSG_ITEM_MOVE_RECV pMsg = { 0 };

		pMsg.h.set(0x79, 0x01, sizeof(pMsg));

		pMsg.sFlag = 0;
		pMsg.tFlag = 0;
		pMsg.Source = lItem->PosX;
		pMsg.Target = 0;

		DataSend((BYTE*)&pMsg, pMsg.h.size);

		JCItemPublic.last_tickcount_moveitem_ = GetTickCount();
	}
}
#endif

#endif