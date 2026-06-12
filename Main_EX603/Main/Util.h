#pragma once

struct REFERENCE_INFO
{
	DWORD count;
	DWORD start;
	DWORD end;
};

struct REFERENCE_BASE
{
	DWORD address;
};

struct REFERENCE_DATA
{
	DWORD address;
	DWORD value;
};

void SetByte(DWORD offset,BYTE value);
void SetWord(DWORD offset,WORD value);
void SetDword(DWORD offset,DWORD value);
void SetFloat(DWORD offset,float value);
void SetDouble(DWORD offset,double value);
void SetCompleteHook(BYTE head,DWORD offset,...);
void MemoryCpy(DWORD offset,void* value,DWORD size);
void MemorySet(DWORD offset,DWORD value,DWORD size);
void VirtualizeOffset(DWORD offset,DWORD size);
void PacketArgumentEncrypt(char* out_buff,char* in_buff,int size);
char* ConvertModuleFileName(char* name);
void LoadReferenceAddressTable(HMODULE mod,char* name,DWORD address);
DWORD WriteMemory2(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SetOp(const DWORD dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SetRange2(const DWORD dwAddress, const USHORT wCount, const BYTE btValue);
void SetJmp2(DWORD offset,DWORD size,LPVOID function);
DWORD GetFileCRC(const char* szFileName);

void SetExperienceTable(int MaxLevel, int ConstA, int ConstB, int DeleteLevel);
extern char* GetItemName(int ItemType, int Level);
short GetSymbolFromVK(WPARAM wParam);

float full_x_in_game_wide(float x);


float GetTextWidth(char* text, HGDIOBJ font);
float GetTextHeight(char* Text, HGDIOBJ Font);

DWORD WriteMemoryT(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2);
DWORD SendPacked(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd, const BYTE cmd2, const BYTE cmd3);

char* BGetItemName(int ItemType, int Level);

extern DWORD FrameValue;
extern DWORD MainTickCount;
extern int TextListColor[60];
extern int TextBold[60];
extern char TextList[60][100];
extern BYTE NewAddressData1[240];
extern BYTE NewAddressData2[240];
extern BYTE NewAddressData3[6000];
