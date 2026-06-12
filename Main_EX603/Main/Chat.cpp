#include "stdafx.h"
#include "Chat.h"
#include "Object.h"

cChat Chat;

cChat::cChat()
{
}

cChat::~cChat()
{
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