#include "stdafx.h"
#include "Chat.h"
#include "Object.h"
#include "Util.h"
#include "Defines.h"
#include "Defines2.h"
#include "SEASON3B.h"
#include "cfreetype.h"
#include "Import.h"

cChat Chat;

cChat::cChat()
{
}

cChat::~cChat()
{
}

void cChat::Init()
{
	// Elimina el llamado incondicional a ShowBackground(false) en CNewUIChatInputBox::Hide (hace el fondo persistente)
	MemorySet(0x00787C77, 0x90, 11);
}

void cChat::CycleBackgroundAlpha()
{
	int pChatLog = GetUINewChatLogWindow();
	if (!pChatLog)
	{
		return;
	}

	BYTE* pShowBackground = (BYTE*)(pChatLog + 0x158);
	float* pBackgroundAlpha = (float*)(pChatLog + 0x150);

	if (*pShowBackground == 0)
	{
		*pShowBackground = 1;
		*pBackgroundAlpha = 0.2f;
	}
	else
	{
		if (*pBackgroundAlpha < 0.35f)
		{
			*pBackgroundAlpha = 0.4f;
		}
		else if (*pBackgroundAlpha < 0.55f)
		{
			*pBackgroundAlpha = 0.6f;
		}
		else if (*pBackgroundAlpha < 0.75f)
		{
			*pBackgroundAlpha = 0.8f;
		}
		else
		{
			*pShowBackground = 0;
			*pBackgroundAlpha = 0.2f;
		}
	}

	PlayBuffer(25, 0, 0);
}

void cChat::CreateMessage(char* strID, char* strText, int MsgType)
{
	//ChatTextObj v1, v2;
	//
	////((int(__thiscall*)(void* a1, int a2)) 0x409A50)(&v1, (int)n);
	//((int(__thiscall*)(void* a1, int a2)) 0x409A50)(&v2, (int)m);
	//
	//signed int slot = ((signed int(__thiscall*)(DWORD This, LPVOID Name, LPVOID Message, DWORD Type, DWORD Arg4)) 0x007894E0) (((DWORD(__thiscall*)(LPVOID This)) 0x861180)(((LPVOID(*)()) 0x861110)()), (LPVOID)& v1, (LPVOID)& v2, c, 0);
	//
	//((int(__thiscall*)(LPVOID a1)) 0x00409AD0)((LPVOID)& v1);
	//((int(__thiscall*)(LPVOID a1)) 0x00409AD0)((LPVOID)& v2);


	BYTE str_ID[28];
	BYTE str_Text[28];

	((void* (__thiscall*)(void* thisa, char* a4))0x00409A50)(&str_ID, strID);
	((void* (__thiscall*)(void* thisa, char* a4))0x00409A50)(&str_Text, strText);
	((void(__thiscall*)(int thisa, void* strID, void* strText, int MsgType, int ErrMsgType))0x007894E0)(((int(__thiscall*)(int))0x00861180)(((int(*)()) 0x00861110)()), str_ID, str_Text, MsgType, 0);
}

void cChat::CreatePlayerHeadMessage(char* m, int i)
{
	int key = ((int(__cdecl*)(int)) 0x57D9A0)(i);
	lpViewObj lpObj;
	if (key != 400)
	{
		lpObj = ((lpViewObj(__thiscall*)(int a1, int a2)) 0x0096A4C0)(((int(*)()) 0x402BC0)(), key);
		if (lpObj && lpObj->m_Model.Unknown4 && lpObj->m_Model.ObjectType == 1)
		{
			((char(__cdecl*)(char* PlayerName, const CHAR * Message, lpViewObj lpObj, int a4, int a5)) 0x005996A0)(lpObj->Name, m, lpObj, 0, -1);
		}
	}
}