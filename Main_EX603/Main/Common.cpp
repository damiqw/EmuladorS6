#include "stdafx.h"
#include "Common.h"
#include "Defines.h"
#include "Import.h"
#include "Interface.h"
#include "Offset.h"
#include "Util.h"
#include "TMemory.h"
#include "ChatExpanded.h"
#include "PrintPlayer.h"
#include "HealthBar.h"
#include "WingInvisible.h"

BYTE GensBattleMapCount = 0;
BYTE GensMoveIndexCount = 0;
BYTE GensBattleMap[120];
BYTE GensMoveIndex[120];

int DisableStaticEffect;
int DisableDynamicEffect;
int DisableSkillEffect;
int DisableGlowEffect;
int DisableArmorShow;
int DisableWeaponShow;
int DisableWingShow;
int DisableEffect15;
int DisableShadows;
int DisablePlayerShow;
int Anisotropy;
int MaxAnisotropy;
int Linear;
int DisablePing;
int SeparateChat;
int TimerBar;
int UserHpBar;
int MonsterHpBar;
int AutoMoveMap;
int MiniMap;
int MiniMapBotones;
int MiniMapType;
int DisableClickEffect;

char FixHelperMouseClick(int a1);

void fix_resolution_items_size_1()
{
	return sub_6363D0_Addr(0, 0, pWinWidth, pWinHeight);
}

int fix_resolution_items_size_2()
{
	float v2 = (float)pWinWidth / (float)pWinHeight;
	return sub_6358A0_Addr(1.0, v2, 20.0, 2000.0);
}

__declspec(naked) void CheckAutoPote() 
{
	static DWORD Pointer;
	static DWORD main_addr = 0x0095E1C4;

	_asm
	{
		MOV ECX, DWORD PTR SS : [EBP - 0x1874]
		MOV Pointer, ECX
	}

	if (*(BYTE *)(Pointer + 176))
	{
		if (ViewCurHP < (ViewMaxHP * *(BYTE *)(Pointer + 177) / 100) && *(BYTE *)(*(DWORD *)(Pointer + 4) + 780) == 1 && ViewCurHP > 0)
		{
			main_addr = 0x0095E1B9;
		}
	}

	_asm
	{
		JMP[main_addr]
	}
}

__declspec(naked) void GlobalMessagem()
{
	static DWORD ADDS = 0x00597698;

	_asm
	{
		CMP DWORD PTR SS : [EBP - 8], 1200
			JMP[ADDS]
	}
}

std::string lol;

__declspec(naked) void CharacterListInfoBar()
{
	static DWORD a1 = 0x00401C60;
	static DWORD a2 = 0x009CEBF0;
	static DWORD a3 = 0x00401C40;
	static DWORD a4 = 0x0041FE10;

	static DWORD ret = 0x00401FC9;

	static DWORD X;
	static DWORD Y;
	static DWORD nCount;
	static DWORD Text;
	static DWORD Name;

	_asm
	{
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		CALL a1
		ADD EAX,0x1E
		MOV DWORD PTR SS:[EBP-0x38],EAX
		FILD DWORD PTR SS:[EBP-0x38]
		FDIV DWORD PTR DS:[0xE7C3D4]
		CALL a2
		MOv nCount,EAX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		ADD ECX,0x130
		MOV Text, ECX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		ADD ECX,0xB0
		MOV Name, ECX
		MOV ECX,DWORD PTR SS:[EBP-0x20]
		CALL a3
		ADD EAX,0x27
		MOV DWORD PTR SS:[EBP-0x3C],EAX
		FILD DWORD PTR SS:[EBP-0x3C]
		FDIV DWORD PTR DS:[0xE7C3D8]
		CALL a2
		MOV Y, EAX
		MOV EDX,DWORD PTR SS:[EBP-0x18]
		SUB EDX,0x0A
		MOV X, EDX
		CALL a4
		MOV ECX,EAX
	}

	//static char test[30];
	//static char test2[30];
	//sprintf_s(test,sizeof(test),"Master Level: %d",pMasterLevel);
	//sprintf_s(test2,sizeof(test2),"Reset: %d",ViewReset);
	lol = (char*)Text;

	pDrawText(pTextThis(),X+5,Y,lol.c_str(),nCount,0,(LPINT)3,0);
	//pDrawText(pTextThis(),X+5,Y+7,test,nCount,0,(LPINT)3,0);
	//pDrawText(pTextThis(),X+5,Y+14,test2,nCount,0,(LPINT)3,0);
	lol.clear();
	_asm{jmp ret}
}

__declspec(naked) void GuildAssistEx()
{
	static DWORD GuildAssistEx_Buff;

	_asm
	{
		mov GuildAssistEx_Buff, ecx
	}

	if( GuildAssistEx_Buff == 128 || GuildAssistEx_Buff == 64 )
	{
		_asm
		{
			mov GuildAssistEx_Buff, 0x0078F5FD
			jmp GuildAssistEx_Buff
		}
	}
	else
	{
		_asm
		{
			mov GuildAssistEx_Buff, 0x0078F57A
			jmp GuildAssistEx_Buff
		}
	}
}

PET_INFO* GetPetInfo(int pItem)
{
	PET_INFO* pPetInfo = ((PET_INFO * (__cdecl*)(int)) 0x004F9930)(pItem);
	if (pPetInfo->m_dwPetType == -1) {
		PET_INFO Petinfo;
		ZeroMemory(&Petinfo, sizeof(PET_INFO));

		Petinfo.m_dwPetType = *(WORD*)pItem == 6661;
		Petinfo.m_wLevel = 1;
		Petinfo.m_wLife = 255;
		Petinfo.m_dwExp1 = 0;
		((void(__cdecl*)(BYTE, BYTE, PET_INFO*)) 0x004F97C0)(0, 0, &Petinfo);

	}
	return pPetInfo;
}

int sub_790B10(int v13, int v12, int v11, int v10)
{
	glColor4f(1.0, 1.0, 1.0, 1.0);

	return pCheckMouseOver(v13, v12, v11, v10);
}

signed int __cdecl chaos_box_send_mix(int a1)
{
	//return sub_797E50_addr(a1);
	DWORD* v2; // eax
	DWORD* v5; // eax

	v2 = (DWORD*)sub_8612C0_addr((DWORD*)pWindowThis());
	sub_82BF00_addr(v2, 1);

	int headCode = sub_79DEA0_addr((char*)0xEBB848);
	PMSG_CHAOS_MIX_SEND pMsg;
	pMsg.header.set(0x86, sizeof(pMsg));
	pMsg.type = headCode;
	pMsg.info = sub_79DE80_addr((char*)0xEBB848);
	DataSend((BYTE*)&pMsg, sizeof(pMsg));

	((void(*)())0x00404B60)();
	sub_6D6C20(25, 0, 0);
	//v5 = (DWORD*)sub_824A30();
	sub_824C80(sub_824A30(), a1, 1);
	return 1;
}

signed int __cdecl lucky_item_mix_send(int a1)
{
	DWORD* v2 = (DWORD*)sub_861A40_addr((DWORD*)pWindowThis());
	int headCode = sub_7EEC60_addr(v2, 2);
	PMSG_CHAOS_MIX_SEND pMsg;
	pMsg.header.set(0x86, sizeof(pMsg));
	pMsg.type = headCode;
	pMsg.info = 0;
	DataSend((BYTE*)&pMsg, sizeof(pMsg));
	((void(*)())0x00404B60)();
	sub_6D6C20(25, 0, 0);
	// v4 = sub_824A30();
	sub_824C80(sub_824A30(), a1, 1);
	return 1;
}

void InitCommon() // OK
{
	SetCompleteHook(0xE9,0x0040B154,&LoginTab);

	SetCompleteHook(0xFF, 0x0064A79A, &CheckMasterLevel); // C1:16

	SetCompleteHook(0xFF, 0x0064A85F, &CheckMasterLevel); // C1:16

	SetCompleteHook(0xFF, 0x00656E03, &CheckMasterLevel); // C1:48

	SetCompleteHook(0xFF, 0x0064AB3D, &CheckMasterLevel); // C1:9C

	SetCompleteHook(0xFF, 0x0064AC02, &CheckMasterLevel); // C1:9C

	SetCompleteHook(0xFF, 0x0063DDF2, &CheckMasterLevel); // C1:F3:03

	SetCompleteHook(0xFF, 0x0063DF89, &CheckMasterLevel); // C1:F3:03

	SetCompleteHook(0xFF, 0x0063EA4C, &CheckMasterLevel); // C1:F3:04

	SetCompleteHook(0xFF, 0x0064CA0C, &CheckMasterLevel); // LevelUp

	SetCompleteHook(0xFF, 0x0077FAF9, &CheckMasterLevel); // Print Level

	SetCompleteHook(0xFF, 0x0081071B, &CheckMasterLevel); // Experience Bar

	SetCompleteHook(0xFF, 0x0081079B, &CheckMasterLevel); // Experience Bar

	SetCompleteHook(0xFF,0x0047FE31,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059890D,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059A399,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059A93C,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0059B13B,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005A4261,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005A4D52,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x005B6117,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x0065A6CE,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x00727987,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x007861F1,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x007D32FA,&CheckGensBattleMap);

	SetCompleteHook(0xFF,0x007D3B0D,&CheckGensBattleMap);

	SetCompleteHook(0xE9,0x008317BD,&CompareGensMoveIndex);

	SetCompleteHook(0xE9, 0x00597691, &GlobalMessagem); // Global Message More Letters

	SetCompleteHook(0xE9,0x0078F56E,&GuildAssistEx);

	SetCompleteHook(0xE9, 0x0082A983, 0x0082A9F3); //ok DUPE FIX

	SetCompleteHook(0xE9, 0x0059AFFA, 0x0059B00E); //Fix Kill Monsters

	SetCompleteHook(0xE9,0x0071AE92,0x00720894); //Fix RF Skill

	SetCompleteHook(0xE9,0x0071B1A3,0x00720894); //Fix RF Skill

	SetCompleteHook(0xE9, 0x005880F0, 0x0058811F); //Fix gm wing on Blood castle

	SetDword(0x00588444 + 3, 4095);

	SetCompleteHook(0xE8,0x007D2B0C,&FixHelperMouseClick);

	SetCompleteHook(0xE8, 0x00772960, &fix_resolution_items_size_1);
	SetCompleteHook(0xE8, 0x007729B3, &fix_resolution_items_size_2);

	SetCompleteHook(0xE9, 0x0095E1AB, &CheckAutoPote); //Fix AutoPot en Helper

	SetDword(0x00797E1D + 1, (DWORD)&chaos_box_send_mix); // increase mix.bmd limits (ChaosBox)
	SetDword(0x00797A92 + 1, (DWORD)&lucky_item_mix_send); // increase mix.bmd limits (LuckyItem)

	SetRange(0x008429CB, 0x59, 0x90); // Remove MonsterName in top of window when hover

	//Fix Evolution White Boots
	SetDword(0x0057F9FA + 3, 304); //-- slot armor
	SetDword(0x0057FA3D + 3, 340); //-- slot pants
	SetDword(0x0057FA7F + 3, 376); //-- slot glove
	SetDword(0x0057FAC1 + 3, 412); //-- slot boot

	SetByte(0x005C9A8D + 2, 0x05); //Fix MuHelper. Item Repair if DarkRaven HP=0
	SetCompleteHook(0xE8, 0x004F9CBD, GetPetInfo); //Fix Show Tooltip Dark Horse + Dark Raven in Shop

	if (gProtect.m_MainInfo.SkillTreeType == 1)
	{
		SetDword(0x0063424F + 1, (DWORD)"Data\\Custom\\Local\\MasterSkillTreeData.bmd");
	}

	//-> Custom Master Skill Tree Type (S13)
	if (gProtect.m_MainInfo.SkillTreeType == 2)
	{
		SetDword(0x0063424F + 1, (DWORD)"Data\\Custom\\Local\\MasterSkillTreeDataEx.bmd");
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		//RenderEditGuildMark position X y Text (NAME) fix season 6
		SetByte((PVOID)(0x007D14E5 + 2), 25);// NAME guild create
		SetByte((PVOID)(0x007D157D + 2), 30); // textura marco del los colores del guild
		SetByte((PVOID)(0x007CFEB8 + 3), 35);//MouseX
		//SetCompleteHook(0xE9, 0x007D00B9, &PositionGuildMakeCreate);

		SetCompleteHook(0xE8, 0x0080FF56, &sub_790B10); //Fix Mouse Interface
	}

	MemorySet(0x0040A7EF, 0x90, 0x5); //RETIRA BOTÃO MENU TELA PRINCIPAL
	MemorySet(0x0040A87E, 0x90, 0x5); //RETIRA BOTÃO CREDIT TELA PRINCIPAL

	//SelectCharacter Info Bar
	MemorySet(0x00401F6C,0x90,0x5C);
	SetCompleteHook(0xE9,0x00401F6C,&CharacterListInfoBar);
	//SetByte(0x00401D36+1,0x7F);
	//SetByte(0x00401D34+1,70); //90 = Y size character_ex.tga


	gInterface.MenuButtonClick.Red = RGBTOGLFLOAT(GetPrivateProfileInt("Menu", "MenuBtnMouse_Red", FLOATTORGB(0.8), ".\\Settings.ini"));
	gInterface.MenuButtonClick.Green = RGBTOGLFLOAT(GetPrivateProfileInt("Menu", "MenuBtnMouse_Green", FLOATTORGB(0.0), ".\\Settings.ini"));
	gInterface.MenuButtonClick.Blue = RGBTOGLFLOAT(GetPrivateProfileInt("Menu", "MenuBtnMouse_Blue", FLOATTORGB(0.0), ".\\Settings.ini"));
	gInterface.MenuButtonClick.Alpha = RGBTOGLFLOAT(GetPrivateProfileInt("Menu", "MenuBtnMouse_Alpha", FLOATTORGB(1.0), ".\\Settings.ini"));

	Anisotropy				= GetPrivateProfileIntA("Graphics","Anisotropy",1,"./Settings.ini");
	MaxAnisotropy			= GetPrivateProfileIntA("Graphics","MaxAnisotropy",1,"./Settings.ini");
	Linear					= GetPrivateProfileIntA("Graphics","Linear",1,"./Settings.ini");
	UserHpBar				= GetPrivateProfileIntA("Other","UserHpBar",0,"./Settings.ini");
	MonsterHpBar			= GetPrivateProfileIntA("Other","MonsterHpBar",0,"./Settings.ini");

	MiniMap					= GetPrivateProfileIntA("Setting", "MiniMap", 0, "./Settings.ini");
	MiniMapType				= GetPrivateProfileIntA("Setting", "MiniMapType", 0, "./Settings.ini");

	SeparateChat			= GetPrivateProfileIntA("Setting", "SeparateChat", 0, "./Settings.ini");

	AutoMoveMap				= GetPrivateProfileIntA("Other", "AutoMoveMap", 0, "./Settings.ini");

	gChatExpanded.m_separate = SeparateChat;

	MiniMapBotones = 1;

	if(SeparateChat == 1)
	{
		gChatExpanded.Load();
	}	
}

BOOL CheckIsLuckyItem(int ItemID) // OK
{
  bool result;

  if ( ItemID < 4158 || ItemID > 4168 )
  {
    if ( ItemID < 3646 || ItemID > 3656 )
    {
      if ( ItemID < 5694 || ItemID > 5704 )
      {
        if ( ItemID < 5182 || ItemID > 5192 )
          result = ItemID >= 4670 && ItemID <= 4680;
        else
          result = 1;
      }
      else
      {
        result = 1;
      }
    }
    else
    {
      result = 1;
    }
  }
  else
  {
    result = 1;
  }
  return result;
}

BOOL CheckGensBattleMap(int map) // OK
{
	for(int n=0;n < GensBattleMapCount;n++)
	{
		if(GensBattleMap[n] == map)
		{
			return 1;
		}
	}

	return 0;
}

BOOL CheckGensMoveIndex(int idx) // OK
{
	for(int n=0;n < GensMoveIndexCount;n++)
	{
		if(GensMoveIndex[n] == idx)
		{
			return 1;
		}
	}

	return 0;
}

__declspec(naked) void LoginTab() // OK
{
	static DWORD LoginTabAddress1 = 0x0040B16F;

	__asm
	{
		Push 0
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x350]
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Eax,Dword Ptr Ds:[Edx+0x350]
		Mov Edx,Dword Ptr Ds:[Eax]
		Call Dword Ptr Ds:[Edx+0x30]
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x354]
		Push Ecx
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Edx+0x350]
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Edx,Dword Ptr Ds:[Eax+0x350]
		Mov Eax,Dword Ptr Ds:[Edx]
		Call Dword Ptr Ds:[Eax+0x58]
		Mov Ecx,Dword Ptr Ss:[Ebp-0x38]
		Mov Edx,Dword Ptr Ds:[Ecx+0x350]
		Push Edx
		Mov Eax,Dword Ptr Ss:[Ebp-0x38]
		Mov Ecx,Dword Ptr Ds:[Eax+0x354]
		Mov Edx,Dword Ptr Ss:[Ebp-0x38]
		Mov Eax,Dword Ptr Ds:[Edx+0x354]
		Mov Edx,Dword Ptr Ds:[Eax]
		Call Dword Ptr Ds:[Edx+0x58]
		Jmp [LoginTabAddress1]
	}
}

__declspec(naked) void CheckMasterLevel() // OK
{
	static DWORD CheckMasterLevelAddress1 = 0x005875A0;

	_asm
	{
		Push Ebp
		Mov Ebp, Esp
		Mov Eax, Dword Ptr Ds : [MAIN_CHARACTER_STRUCT]
		Xor Ecx, Ecx
		Mov Cx, Word Ptr Ds : [Eax + 0x0E]
		Cmp Ecx, CharacterMaxLevel
		Je NEXT
		Xor Eax, Eax
		Jmp EXIT
		NEXT :
		Xor Edx, Edx
			Mov Dl, Byte Ptr Ss : [Ebp + 0x08]
			Push Edx
			Call[CheckMasterLevelAddress1]
			Add Esp, 0x04
			EXIT :
			Pop Ebp
			Retn
	}
}

__declspec(naked) void CompareGensMoveIndex() // OK
{
	static DWORD CheckGensMoveIndexAddress1 = 0x0051B090;
	static DWORD CheckGensMoveIndexAddress2 = 0x008317FC;
	static DWORD CheckGensMoveIndexAddress3 = 0x008317EA;

	__asm
	{
		Lea Ecx,Dword Ptr Ss:[Ebp-0x08]
		Call [CheckGensMoveIndexAddress1]
		Mov Ecx,Dword Ptr Ds:[Eax]
		Mov Edx,Dword Ptr Ds:[Ecx]
		Push Edx
		Call [CheckGensMoveIndex]
		Add Esp,0x04
		Test Eax,Eax
		Jnz EXIT
		Jmp [CheckGensMoveIndexAddress2]
		EXIT:
		Jmp [CheckGensMoveIndexAddress3]
	}
}

char FixHelperMouseClick(int a1) // Agregar al final del archivo
{
	if (gInterface.CheckWindow(ChaosBox) || gInterface.CheckWindow(Warehouse))
		return 0;

	return pHelperMouseClick(a1);
}