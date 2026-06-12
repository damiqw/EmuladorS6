#pragma once

#define MAIN_WINDOW				0x00E8C578
#define MAIN_CONNECTION_STATUS	0x08793704
#define MAIN_SCREEN_STATE		0x00E609E8
#define MAIN_CHARACTER_STRUCT	0x08128AC8
#define MAIN_VIEWPORT_STRUCT	0x07BC4F04
#define MAIN_PACKET_SERIAL		0x08793700
#define MAIN_HELPER_STRUCT		0x00E8CB7C
#define MAIN_FONT_SIZE			0x081C0380
#define MAIN_RESOLUTION			0x00E8C240
#define MAIN_RESOLUTION_X		0x00E61E58
#define MAIN_RESOLUTION_Y		0x00E61E5C
#define MAIN_PARTY_MEMBER_COUNT	0x081F6B6C
#define MAIN_CURRENT_MAP		0x00E61E18
#define MAIN_ACTIVE_SOCKET		0x08793750
#define MAIN_PREVIEW_STRUCT		0x07BC4F04


#define MAX_MAIN_VIEWPORT 400

#define pDrawInterfaceNumBer   ((double(__stdcall*)(float X, float Y, int num, float size)) 0x854FE0)
#define ProtocolCore			((BOOL(*)(DWORD,BYTE*,DWORD,DWORD))0x00663B20)
//#define pGetPosFromAngle		((void(__cdecl*)(float*,int*,int*))0x00635B00)
#define pCursorX2				*(int*)0x0879340C
#define DrawInterfaceText ((void(*)(char*,int,int,int,int,int,int,int))0x007D04D0)
#define pCursorY2				*(int*)0x08793410
#define pTextThis				((LPVOID(*)())0x0041FE10)
#define pDrawText				((int(__thiscall*)(LPVOID This, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, LPINT lpnTabStopPositions, int nTabOrigin)) 0x00420150)
#define pSetTextColor			((void(__thiscall*)(LPVOID This, BYTE r, BYTE g, BYTE b, BYTE h)) 0x00420040)
#define pDrawBarForm			((void(__cdecl*)(float,float,float,float,float,int))0x006378A0)
#define pSetBlend				((void(__cdecl*)(BYTE))0x00635FD0)
#define pGLSwitchBlend			((void(__cdecl*)())0x00636070)
#define pGLSwitch				((void(__cdecl*)())0x00635F50)
#define pLoadImage				((int(__cdecl*)(char*,int,int,int,int,int))0x00772330)
#define pDrawToolTip			((int(__cdecl*)(int,int,LPCSTR))0x00597220)
#define pWindowThis				((LPVOID(*)())0x00861110)
#define pDrawImage              ((void(__cdecl*)(int ImageID, float PosX, float PosY, float Width, float Height, int Arg6, float Arg7, float ScaleX, float ScaleY, bool ScaleSize, bool ScalePosition, bool ScaleAlpha)) 0x637C60)
#define pDrawMessage			((int(__cdecl*)(LPCSTR,int))0x00597630)
#define pLoadItemModel			((void(*)(int,char*,char*,int))0x00614D10)
#define pLoadItemTexture		((void(*)(int,char*,int,int,int))0x00614710)
#define DrawInterface			((void(*)(DWORD,float,float,float,float))0x00790B50)
#define DrawInterfaceText		((void(*)(char*,int,int,int,int,int,int,int))0x007D04D0)
#define pCheckWindow			((bool(__thiscall*)(LPVOID,int))0x0085EC20)
#define pClosekWindow			((int(__thiscall*)(LPVOID,int))0x0085F9A0)
#define pOpenWindow				((int(__thiscall*)(LPVOID,int))0x0085EC50)
#define pGloveAssoc				((int(__thiscall*)(DWORD,DWORD,DWORD,DWORD))0x0050D810)
#define pGloveCount				((void*(__thiscall*)(DWORD))0x00512D50)(Address+0x5C)
#define pGloveSetInfo			((DWORD(__thiscall*)(DWORD,void*,DWORD))0x00513C60)
#define pGloveSaveInfo			((char*(__thiscall*)(DWORD*,DWORD,DWORD))0x005135F0)
#define pGloveRefresh			((void(*)())0x00512D60)
#define pChaosMixIndex			((DWORD(__thiscall*)(DWORD*))0x0079DEA0)(&*(DWORD*)(0x00EBB848))

#define pRenderPartObjectEffect	((void(*)(DWORD,int,float*,float,int,int,int,int,int))0x00609E70)
#define pTransformPosition      ((int(__thiscall*)(DWORD,DWORD,float*,float*,bool))0x00545030)
#define pCreateSprite	        ((int(*)(int,float*,float,float*,DWORD,float,int))0x00771310)
#define pCreateParticle			((int(__cdecl*)(DWORD,float*,DWORD,float*,DWORD,float,DWORD))(0x0074CD30))
#define pCreateEffect			((void(__cdecl*)(int,float*,DWORD,float*,int,DWORD,short,BYTE,float,BYTE,float*))0x006D9070)

#define pCreateMonster			((DWORD(*)(int,int,int,int))0x00901460)
#define pCreateCharacter		((DWORD(*)(int,int,int,int,float))0x0057EEC0)
#define pSettingMonster			((DWORD(*)(int,int))0x00580BB0)

#define sub_7798F0_Addr			((char(__thiscall*)(char *This, char a2)) 0x7798F0)
#define sub_7909D0_addr			((DWORD*(__thiscall*)(DWORD *this_, int a2)) 0x7909D0)
#define pGetKeyState			((bool(__cdecl*)(int)) 0x791070)
#define sub_779860_addr			((char(__thiscall*)(void *)) 0x779860) // 1.04D -> 0x779710
#define sub_78EB50_Addr			((int(__thiscall*)(char *this_, int a2, char a3)) 0x78EB50)
#define sub_91C9D0_Addr			((void*(*)()) 0x91C9D0)
#define sub_91CC20_Addr			((int(__thiscall*)(BYTE *this_, int a2, int a3)) 0x91CC20)
#define sub_78E0E0_Addr			((DWORD*(__thiscall*)(DWORD* this_)) 0x78E0E0)
#define sub_41FFE0_Addr			((int(__thiscall*)(LPVOID a1)) 0x41FFE0)
#define sub_420010_Addr			((int(__thiscall*)(LPVOID a1)) 0x420010)
#define pSetTextColor2			((int(__thiscall*)(LPVOID a1, int color)) 0x420080)
#define pSetBgColor				((int(__thiscall*)(LPVOID a1, int a2)) 0x4200F0)
#define sub_409A50_addr			((DWORD *(__thiscall*)(void *This, int a2)) 0x409A50)
#define sub_7894E0_Addr			((char(__thiscall*)(char* This, int Name, int Message, DWORD Type, DWORD Arg4)) 0x007894E0)
#define sub_409AD0_Addr			((int(__thiscall*)(LPVOID a1)) 0x00409AD0)

#define pMouseWheelValue	*(int*)0x879337C
#define pKeyIsPressed		((int(__cdecl*)(int a1)) 0x791090)
#define sub_4D5B70_Addr		((int(__cdecl*)(int)) 0x4D5B70)
#define	pGetRealX			((double(__cdecl*)(float a1)) 0x636420)
#define	pGetRealY			((double(__cdecl*)(float a1)) 0x636450)
#define g_bWndActive		*reinterpret_cast<BYTE*>(0x00E8C5AC)

#define pIsWindowMode			*(DWORD*)0xE60974
#define sub_596AC0_Addr			((int(__cdecl*)(int a1)) 0x596AC0)
#define sub_482B70_Addr			((BYTE*(__cdecl*)()) 0x482B70)
#define sub_785870_Addr			((char(__thiscall*)(int this_, int a2, int a3, int a4, int a5)) 0x785870)
#define sub_830B70_Addr			((char(__thiscall*)(DWORD This, int a2, int a3, int a4)) 0x830B70)

#define GetItemEquiped(x)			(*(DWORD*)(0x08128AC4)+(4672+(107*x)))
#define GetItemEquipedIndex(x)		(*(WORD*)(GetItemEquiped(x)))
#define GetMyInventoryCtrl			((LPVOID(__thiscall*)(LPVOID,int))0x00835720)
#define InventoryDeleteItem			((DWORD*(__thiscall*)(LPVOID,int))0x00834320)
#define InventoryFindEmptySlot		((int(__thiscall*)(LPVOID,int,int))0x00835940)
#define InventoryFindItem			((DWORD*(__thiscall*)(LPVOID,int,int))0x007DAC10)
#define InventoryFindItemAtPt		((DWORD*(__thiscall*)(LPVOID,int,int,DWORD*))0x0083CAB0)
#define InventoryFindItemSlot		((int(__thiscall*)(LPVOID,int,int))0x007DAC40)
#define InventoryMixDeleteItem		((DWORD*(__thiscall*)(LPVOID,int))0x0084EFD0)
#define InventoryMixFindEmptySlot	((int(__thiscall*)(LPVOID,int,int))0x007DACA0)
#define InventoryThis				((LPVOID(__thiscall*)(LPVOID))0x00861260)
#define InventoryUnequipItem		((DWORD*(__thiscall*)(LPVOID,int))0x00833B20)
#define PSInventoryThis				((LPVOID(__thiscall*)(LPVOID))0x00861400)
#define MixGetMyInventoryCtrl		((LPVOID(__thiscall*)(LPVOID))0x0082C780)
#define MixInventoryThis			((LPVOID(__thiscall*)(LPVOID))0x008612C0)
#define PickedItem					(*(DWORD*)0x09816F7C)
#define CreatePickedItem			((bool(__cdecl*)(DWORD,DWORD))0x007DD100)
#define ResetMouseRButton			((void(*)())0x007D51E0)
#define SendRequestEquipmentItem	((bool(_cdecl*)(int,int,DWORD,int,int))0x005BD850)

#define pCursorX				*(int*)0x879340C
#define pCursorY				*(int*)0x8793410


static signed int sub_9CEBF0(double a1)
{
	return (signed int)a1;
}