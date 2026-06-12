#include "stdafx.h"
#include "QuickCommand.h"
#include "Util.h"
#include "Interface.h"
#include "CustomFont.h"
#include "Object.h"
#include "SEASON3B.h"
#include "TMemory.h"
#include "Defines.h"

cQuickCommand QuickCommand;
cQuickCommand::cQuickCommand()
{
	this->Load();
	this->m_iSelectedIndex = -1;
	this->m_target = -1;
}

cQuickCommand::~cQuickCommand()
{
}

#define sub_853770			((void(__thiscall*)(DWORD a1)) 0x00853770)
#define MoveHero			((void(__cdecl*)()) 0x005B5FC0)

void fake_853770(DWORD a1)
{
	sub_853770(a1);
	float x = (double)*(DWORD *)(a1 + 16);
	float y = (double)*(DWORD *)(a1 + 20);
	int   target = *(DWORD *)(a1 + 60);
	QuickCommand.DrawFrame(x, y, target);
}
void fake_5B5FC0()
{
	*(bool*)0x0813DDCE = QuickCommand.GetMouseBlock();
	MoveHero();
	QuickCommand.ClearMouseBlock();
}

void NullFunction()
{
	static DWORD address = 0x004DA3E4;
	_asm {
		jmp address;
	}
}

void cQuickCommand::Load()
{
	SetCompleteHook(0xE8, 0x004D9577, fake_5B5FC0);
	SetCompleteHook(0xE8, 0x0085374B, fake_853770);
	SetFloat(0x00D24E60, 155);
	SetByte(0x0085381F + 3, 4);
	SetByte(0x008538F6 + 3, 5);
}

void cQuickCommand::ClearMouseBlock()
{
	this->m_iSelectedIndex = -1;
}
bool cQuickCommand::GetMouseBlock()
{
	bool block = *(bool*)0x0813DDCE;

	if (block)
		return block;

	block |= this->Action();

	return block;
}
#include "ViewCharItem.h"
#include "Character.h"
bool cQuickCommand::Action()
{
	if (this->m_iSelectedIndex != -1 && pIsKeyRelease(VK_LBUTTON))
	{
		ObjectPreview *lpViewTarget = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), this->m_target);
		if (lpViewTarget) 
		{

			this->SendRequest(0, 0, lpViewTarget->Name);
			//character.ClearPetCache(1);
			ViewCharItems.ClearSession();
			
		}
	}

	return this->m_iSelectedIndex != -1;
}
bool cQuickCommand::IsWorkZone(float x, float y, float x2, float y2, bool mode)
{
	if (mode)
		return GetForegroundWindow() == pGameWindow && pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;

	return pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
}

void cQuickCommand::DrawFrame(float x, float y, int target)
{
	m_iSelectedIndex = -1;
	int i;
	for (i = 0; i < 1; i++)
	{
		if (m_iSelectedIndex == -1 && this->IsWorkZone(x, y + 40.f + 20.f * (i + 5), 112, 19)) {
			m_iSelectedIndex = i;
			pDrawGUI(31583, x + 16, y + 44.f + 19.f * (i + 5), 6.0, 9.0); //>
			pDrawGUI(31584, x + 90, y + 44.f + 19.f * (i + 5), 6.0, 9.0); //<
		}
		CustomFont.Draw(CustomFont.FontNormal, x, y + 42.f + 19.f * (i + 5), m_iSelectedIndex == i ? 0xffff00ff : 0xffffffff, 0x0, 112, 0, 3, "View Items");
		
	}
	this->m_target = target;
}

void cQuickCommand::SendRequest(BYTE type, int value, char* name)
{

	PMSG_QUICK_COMMAND_SEND pRequest;
	pRequest.h.set((LPBYTE)&pRequest, 0xFB, 0x34, sizeof(pRequest));
	pRequest.Type = type;
	pRequest.Value = value;

	memcpy_s(&pRequest.Name[0], 10, name, 10);
	
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}