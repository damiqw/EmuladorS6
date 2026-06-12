#pragma once

#include "Protect.h"

#define WD_ATLANS   7
#define World								*(int*)0x0E61E18

#define GMT (24 + (gProtect.m_MainInfo.ServerTime))

typedef struct
{
	DWORD		m_dwPetType;
	DWORD       m_dwExp1;
	DWORD       m_dwExp2;
	WORD        m_wLevel;
	WORD        m_wLife;
	WORD        m_wDamageMin;
	WORD        m_wDamageMax;
	WORD        m_wAttackSpeed;
	WORD        m_wAttackSuccess;
} PET_INFO;

#define sub_8612C0_addr				((int(__thiscall*)(DWORD*)) 0x8612C0)
#define sub_82BF00_addr				((int(__thiscall*)(DWORD*,int)) 0x82BF00)
#define sub_824C80					((int(__thiscall*)(LPVOID This, int a2, int a3)) 0x824C80)
#define sub_79DEA0_addr				((int(__thiscall*)(char*)) 0x79DEA0)
#define sub_797E50_addr				((signed int(__cdecl*)(int)) 0x797E50)
#define sub_861A40_addr				((int(__thiscall*)(DWORD*)) 0x861A40)
#define sub_7EEC60_addr				((signed int(__thiscall*)(DWORD*,int)) 0x7EEC60)
#define sub_79DE80_addr				((int(__thiscall*)(char*)) 0x79DE80)
#define sub_824A30					((LPVOID(__cdecl*)()) 0x824A30)

struct PMSG_CHAOS_MIX_SEND
{
	PBMSG_HEAD header; // C1:86
	int type;
	BYTE info;
};

void InitCommon();
BOOL CheckIsLuckyItem(int ItemID);
BOOL CheckGensBattleMap(int map);
BOOL CheckGensMoveIndex(int idx);
void LoginTab();
void CheckMasterLevel();
void CompareGensMoveIndex();

extern BYTE GensBattleMapCount;
extern BYTE GensMoveIndexCount;
extern BYTE GensBattleMap[120];
extern BYTE GensMoveIndex[120];

extern int DisableStaticEffect;
extern int DisableDynamicEffect;
extern int DisableSkillEffect;
extern int DisableGlowEffect;
extern int DisableArmorShow;
extern int DisableWeaponShow;
extern int DisableWingShow;
extern int DisableEffect15;
extern int DisableShadows;
extern int DisablePlayerShow;
extern int Anisotropy;
extern int MaxAnisotropy;
extern int Linear;
extern int DisablePing;
extern int TimerBar;
extern int UserHpBar;
extern int MonsterHpBar;
extern int AutoMoveMap;
extern int MiniMap;
extern int MiniMapBotones;
extern int MiniMapType;
extern int DisableClickEffect;