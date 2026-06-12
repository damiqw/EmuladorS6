#pragma once

#define OpenglWindowHeight				*(int*)0x87933E8
#define OpenglWindowWidth				*(int*)0x87933EC
#define OpenglWindowY					*(int*)0x87933F0
#define OpenglWindowX					*(int*)0x87933F4

#define sub_5DD400 ((double(__cdecl*)(float a1)) 0x005DD400)

#define sub_779410 ((int(__thiscall*)(char *This, int X, int Y, int Width, int Height)) 0x00779410)

#define sub_4DB0E0					((BOOL(__cdecl*)(int a1))0x004DB0E0)
#define sub_59A8B0					((bool(__stdcall*)())0x0059A8B0)
//-- Cursor
#define sub_4F6170					((void(__cdecl*)(float a1))0x004F6170)
#define sub_83C310					((char(__thiscall*)(DWORD * This))0x0083C310)
#define sub_861260					((int(__thiscall*)(int This))0x00861260)

#define sub_78ECE0					((int(__thiscall*)(int This))0x0078ECE0)
#define sub_8615E0					((int(__thiscall*)(int This))0x008615E0)
#define sub_861280					((int(__thiscall*)(int This))0x00861280)
#define sub_834550					((int(__thiscall*)(int This))0x00834550)
#define sub_847EF0					((int(__thiscall*)(int This))0x00847EF0)

#define CursorX					*(DWORD*)0x879340C
#define CursorY					*(DWORD*)0x8793410
#define ItemTarget					*(DWORD*)0xE61728
#define NpcTarget					*(DWORD*)0xE6172C
#define PlayerTarget				*(DWORD*)0xE61730
//--
#define sub_861A60					((int(__thiscall*)(int This))0x00861A60)
#define sub_7D6270					((int(__thiscall*)(int This, int a5))0x007D6270)
//--
//-- Offset Ventanas
#define getWindowConfig_35 ((int(__thiscall*)(int This))0x00861620)
#define sub_9CEFB0        ((int(__thiscall*)(int a1)) 0x009CF130) //1
#define pTextureBlind			((void(__cdecl*)()) 0x00637A30)	
#define GetVolumeLevel 			((int(__thiscall*)(LPVOID))0x00849E80)
#define pWindowOption			((LPVOID(__thiscall*)(LPVOID))0x00861620)(pWindowThis())
#define pDrawBarForm2			((void(__cdecl*)(float,float,float,float))0x006378A0)

//-------------------
//--ChangeResolution
//------------------
#define s_482B70							((void *(*)()) 0x482B70)
#define sub_630BC0	((int(*)()) 0x630BC0)
#define sub_596AC0	((int(__cdecl*)(int a1)) 0x596AC0) // 0x596C10  0x596AC0
#define sub_407B20	((void *(*)()) 0x407B20)
#define sub_785870	((char(__thiscall*)(DWORD This, int a2, int a3, int a4, int a5)) 0x785870)
#define sub_830B70	((char(__thiscall*)(DWORD This, int a2, int a3, int a4)) 0x830B70)
#define sub_853FA0	((char(__thiscall*)(DWORD This, int a2, int a3, int a4)) 0x853FA0)
#define sub_7792C0  ((int(__thiscall*)(char *This, int X, int Y, int Width, int Height)) 0x007792C0)
#define sub_860FC0	((void *(__cdecl*)()) 0x860FC0)
#define sub_10011A30 ((int(__cdecl*)(int a1)) 0x10011A30)

void InitOptionPanel();