#include "stdafx.h"
#include "Util.h"
#include "../../Util/CCRC32.H"
#include "Offset.h"
#include "Import.h"
#include "Defines.h"
#include "Protect.h"
#include "Interface.h"

BYTE NewAddressData1[240];
BYTE NewAddressData2[240];
BYTE NewAddressData3[6000];

int TextListColor[60];
int TextBold[60];
char TextList[60][100];

DWORD CharacterMaxLevel;

void SetByte(DWORD offset,BYTE value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,1,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(BYTE*)(offset) = value;

	VirtualProtect((void*)offset,1,OldProtect,&OldProtect);
}

void SetWord(DWORD offset,WORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,2,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(WORD*)(offset) = value;

	VirtualProtect((void*)offset,2,OldProtect,&OldProtect);
}

void SetDword(DWORD offset,DWORD value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(DWORD*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetFloat(DWORD offset,float value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,4,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(float*)(offset) = value;

	VirtualProtect((void*)offset,4,OldProtect,&OldProtect);
}

void SetDouble(DWORD offset,double value) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,8,PAGE_EXECUTE_READWRITE,&OldProtect);

	*(double*)(offset) = value;

	VirtualProtect((void*)offset,8,OldProtect,&OldProtect);
}

void SetCompleteHook(BYTE head,DWORD offset,...) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,5,PAGE_EXECUTE_READWRITE,&OldProtect);

	if(head != 0xFF)
	{
		*(BYTE*)(offset) = head;
	}

	DWORD* function = &offset+1;

	*(DWORD*)(offset+1) = (*function)-(offset+5);

	VirtualProtect((void*)offset,5,OldProtect,&OldProtect);
}

void MemoryCpy(DWORD offset,void* value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memcpy((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void MemorySet(DWORD offset,DWORD value,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	memset((void*)offset,value,size);

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void VirtualizeOffset(DWORD offset,DWORD size) // OK
{
	DWORD OldProtect;

	VirtualProtect((void*)offset,size,PAGE_EXECUTE_READWRITE,&OldProtect);

	DWORD HookAddr = (DWORD)malloc(size+5);

	memcpy((void*)HookAddr,(void*)offset,size);

	*(BYTE*)(HookAddr+size) = 0xE9;

	*(DWORD*)(HookAddr+size+1) = (offset+size)-((HookAddr+size)+5);

	*(BYTE*)(offset) = 0xE9;

	*(DWORD*)(offset+1) = HookAddr-(offset+5);

	memset((void*)(offset+5),0x90,(size-5));

	VirtualProtect((void*)offset,size,OldProtect,&OldProtect);
}

void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size) // OK
{
	BYTE XorTable[3] = {0xFC,0xCF,0xAB};

	for(int n=0;n < size;n++)
	{
		out_buff[n] = in_buff[n]^XorTable[n%3];
	}
}

char* ConvertModuleFileName(char* name) // OK
{
	static char buff[MAX_PATH] = {0};

	for(int n=strlen(name);n > 0;n--)
	{
		if(name[n] == '\\')
		{
			strcpy_s(buff,sizeof(buff),&name[(n+1)]);
			break;
		}
	}

	return buff;
}

void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address) // OK
{
	if(IS_INTRESOURCE(name) == 0)
	{
		return;
	}

	HRSRC resource = FindResource(mod,name,"BIN");

	if(resource == 0)
	{
		return;
	}

	if(SizeofResource(mod,resource) < sizeof(REFERENCE_INFO))
	{
		return;
	}

	HGLOBAL data = LoadResource(mod,resource);

	if(data == 0)
	{
		return;
	}

	REFERENCE_INFO* ReferenceInfo = (REFERENCE_INFO*)LockResource(data);

	if(ReferenceInfo == 0)
	{
		FreeResource(data);
		return;
	}

	if(ReferenceInfo->start == ReferenceInfo->end)
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_BASE))))
		{
			return;
		}

		REFERENCE_BASE* ReferenceBase = (REFERENCE_BASE*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceBase[n].address,address);
		}
	}
	else
	{
		if(SizeofResource(mod,resource) < (sizeof(REFERENCE_INFO)+(ReferenceInfo->count*sizeof(REFERENCE_DATA))))
		{
			return;
		}

		REFERENCE_DATA* ReferenceData = (REFERENCE_DATA*)((DWORD)ReferenceInfo+sizeof(REFERENCE_INFO));

		for(DWORD n=0;n < ReferenceInfo->count;n++)
		{
			SetDword(ReferenceData[n].address,(address+ReferenceData[n].value));
		}
	}

	FreeResource(data);
}

DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode   = 0;
    DWORD dwOldProtect  = 0;
    // ----
    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);
    // ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
    // ----
    memcpy(lpAddress, lpBuf, uSize);
    // ----
    DWORD dwBytes   = 0;
    // ----
    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);
    // ----
    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }
    // ----
    return 0x00;
};

DWORD SetOp(const DWORD dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
    BYTE btBuf[5];
    DWORD dwShift    = (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;
    // ----
    btBuf[0]        = cmd;
    memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));
    // ----
    return WriteMemory2((PVOID)dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
};

DWORD SetRange2(const DWORD dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf	= new BYTE[wCount];
	// ----
	memset(lpBuf, btValue, wCount);
	// ----
	return WriteMemory2( (PVOID)dwAddress, (LPVOID) lpBuf, wCount);
}

void SetJmp2(DWORD offset,DWORD size,LPVOID function)
{
	MemorySet(offset,0x90,size);
	SetCompleteHook(0xE9,offset,function);
}

DWORD GetFileCRC(const char* szFileName)
{
	CCRC32 CRC32;

	DWORD Buffer;

	if(CRC32.FileCRC(szFileName,&Buffer,1024) == 0)
	{
		return 0;
	}

	return Buffer;
}

void SetExperienceTable(int MaxLevel, int ConstA, int ConstB, int DeleteLevel) // OK
{
	SetWord(0x00405B7C, DeleteLevel); // Delete Level
	SetWord(0x0040CC40, DeleteLevel); // Delete Level Msg

	SetByte(0x00595273 + 2, (BYTE)ConstA); // CalcNextExperience 10
	SetByte(0x0081105A + 2, (BYTE)ConstA); // CalcNextExperience 10

	SetWord(0x005952A8 + 2, (WORD)ConstB); // CalcNextExperience 1000
	SetWord(0x0081109B + 2, (WORD)ConstB); // CalcNextExperience 1000

	CharacterMaxLevel = MaxLevel;
}

DWORD WriteMemoryT(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	DWORD dwErrorCode = 0;
	DWORD dwOldProtect = 0;

	int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, &dwOldProtect);

	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}

	memcpy(lpAddress, lpBuf, uSize);

	DWORD dwBytes = 0;

	iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, &dwBytes);

	if (iRes == 0)
	{
		dwErrorCode = GetLastError();
		return dwErrorCode;
	}

	return 0x00;
}

DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	btBuf[0] = cmd;
	memcpy((LPVOID)&btBuf[1], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemoryT(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2)
{
	BYTE btBuf[6];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	memcpy((LPVOID)&btBuf[2], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemoryT(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}

DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3)
{
	BYTE btBuf[7];
	// ----
	btBuf[0] = cmd;
	btBuf[1] = cmd2;
	btBuf[2] = cmd3;
	memcpy((LPVOID)&btBuf[3], (LPVOID)dwJMPAddress, sizeof(ULONG_PTR));
	// ----
	return WriteMemoryT(dwEnterFunction, (LPVOID)btBuf, sizeof(btBuf));
}


#define pGetItemName					((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)

char* GetItemName(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	//return (char*)(oUserTextObject + 84 * ItemType);
	return strdup(a.c_str());
}

short GetSymbolFromVK(WPARAM wParam)
{
	BYTE btKeyState[256];
	HKL hklLayout = GetKeyboardLayout(0);
	WORD Symbol;
	GetKeyboardState(btKeyState);
	if ((ToAsciiEx(wParam, MapVirtualKey(wParam, 0), btKeyState, &Symbol, 0, hklLayout) == 1))
	{
		return Symbol;
	}
	return 0;
}

float full_x_in_game_wide(float x)
{
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		return (float)(pWinWidthReal <= 1.25) ? x / pWinWidthReal : x / pWinHeightReal;

	return (float)FULL_X_IN_GAME_X((int)x);
}

float GetTextWidth(char* text, HGDIOBJ font)
{
	HDC hDC = GetDC(*(HWND*)(MAIN_WINDOW));
	SIZE psizl;

	SelectObject(hDC, font);
	GetTextExtentPoint32(hDC, text, strlen(text), &psizl);

	return full_x_in_game_wide(psizl.cx);
}

float GetTextHeight(char* Text, HGDIOBJ Font)
{
	HDC hDC = GetDC(*(HWND*)(MAIN_WINDOW));

	SIZE psizl;

	SelectObject(hDC, Font);
	GetTextExtentPoint32(hDC, Text, strlen(Text), &psizl);

	return FULL_Y_IN_GAME_Y(psizl.cy);
}

#include "Defines.h"
#define pBGetItemName					((const char(__cdecl*)(int ItemID, const char * Level, char * Buffer)) 0x005C2430)
char* BGetItemName(int ItemType, int Level)
{
	char ItemNameGet[100];
	memset(ItemNameGet, 0, sizeof(ItemNameGet));
	pBGetItemName(ItemType, (const char*)(GET_ITEMOPT_LEVEL(Level)), (char*)ItemNameGet);
	std::string a(ItemNameGet);
	return strdup(a.c_str());
}