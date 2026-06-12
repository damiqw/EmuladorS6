#pragma once

enum JInterfaceType
{
	Classic = 1,
	Ex700 = 2,
	Legends = 3,
	Diablo = 4,
	Season1 = 5,
	Season2 = 6,
};
#define sub_5B9260		((void(__cdecl*)(float a1, float a2, float a3, float a4, float a5, char a6, char a7)) 0x005B9260)

#define JCGetAttribute			((void(__thiscall*)( )) 0x0080FA10)
#define JCGetAttributeSD			((void(__thiscall*)( )) 0x00810420)
#define JCGetAttributeAG			((void(__thiscall*)( )) 0x00810150)

#define JCLoadSkill				((void(__thiscall*)(int a1, int a5, float a6, float a7, float a8, float a9)) 0x00813DC0)
#define JCPSkill				((void(__cdecl*)(int a1, int a5, float a6, float a7, float a8, float a9)) 0x00813DC0)
#define JCTimerSkillBar 		((void(__stdcall*)(int a1, float a2, float a3, float a4, float a5)) 0x00814F30)
#define dword_81C039C						*(DWORD*)0x81C039C
#define byte_81C0398						*(BYTE*)0x81C0398
#define dword_8128AC8						*(DWORD*)0x8128AC8
#define byte_8793384						*(BYTE*)0x8793384
#define byte_8793380						*(BYTE*)0x8793380
#define dword_8128ABC						*(DWORD*)0x8128ABC
#define dword_81C03A0						*(DWORD*)0x81C03A0
#define dword_8793708						*(DWORD*)0x8793708
#define sub_779860							((char(__thiscall*)(int a1)) 0x00779860)
#define sub_791090							((int(__cdecl*)(int VKBUTTON)) 0x00791090)
#define sub_791070							((int(__cdecl*)(int VKBUTTON)) 0x00791070)
#define sub_4D5B70							((char(__cdecl*)(signed int a1)) 0x004D5B70)
#define sub_482B70							((int(*)()) 0x00482B70)
#define JCMultiSkillLine					((void(__thiscall*)(int a1, float a5, int a6, int a7, int a8, int a9)) 0x00772EA0)
#define pDrawBar ((double(__cdecl*)(float a1, float a2, int a3, float a4)) 0x791000)

#define pDrawImage              ((void(__cdecl*)(int ImageID, float PosX, float PosY, float Width, float Height, int Arg6, int Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)) 0x637C60)
#define pSetBackgroundTextColor		((void(__thiscall*)(LPVOID This, int r, int g, int b, int h)) 0x004200B0)

class CInterface
{
public:
	void Load();
	int MasterPoint_1;
	int MasterPoint_2;
	int MasterPoint_3;
};

extern CInterface gInterfaceBar;

#define pGetTextLine			((char*(__thiscall*)(LPVOID This, int LineNumber)) 0x402320)