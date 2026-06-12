#pragma once

#include <vector>

#include "Protocol.h"

#define MODEL_PLAYER						1163
#define Hero								*(DWORD*)0x007BC4F04
#define WorldTime							*(float*)0x005EF5A1C
#define EnableAlphaBlend					((void(__cdecl*)()) 0x636070)
#define DisableAlphaBlend					((void(__cdecl*)()) 0x00635F50)
#define sub_4DB0E0							((BOOL(__cdecl*)(int a1))0x004DB0E0)
#define cRenderCharacter					((void(__cdecl*)(ObjectPreview *a4, ObjectModel *a5, int Select)) 0x0057D260)
#define battleCastleInitEtcSetting			((void(__cdecl*)()) 0x8CF360)
#define CreateBattleCastleCharacter_Visual	((void(__cdecl*)(int a1, int a2)) 0x8CF360)
#define cSkillEffect						((void(__cdecl*)(int a1, int a2, int a3, float * a4, int a5, int a6, __int16 a7, __int16 a8, __int16 a9, __int16 a10, float a11, __int16 a12)) 0x6D9070)
#define RenderTerrainAlphaBitmap            ((void(__cdecl*)(int Texture,float xf,float yf,float SizeX,float SizeY,vec3_t Light,float Rotation,float Alpha,float Height, char a10)) 0x005DAD80)
#define sub_558630							((void(__cdecl*)(int a1, int a2, int a3)) 0x558630)
#define pCheckEffectPlayer					((bool(__thiscall*)(void * This,char a2)) 0x004C8640)

#define MAX_TYPE_RUNEEFFECT 6
//
struct RuneEffectType
{
	int Index;
	int Type;
	int	TextureIndex;
	float Speed;
	int Size;
	float ColorR;
	float ColorG;
	float ColorB;
	float FloorDistance;
};
//
struct PMSG_CUSTOM_RUNEEFFECT
{
	PSBMSG_HEAD h;
	int iIndex;
	int iLevel;
	int iReset;
	int iMReset;
	int cVip;
	int cGM;
	int cPK;
};
// ---
struct CUSTOM_RUNEEFFECT_DATA
{
	WORD m_Index;
	WORD m_Resets;
	WORD m_MResets;
	WORD m_Level;
	WORD cVip;
	WORD cGM;
	WORD cPK;
};
// ---
class RuneEffect
{
public:
	RuneEffect();
	// ---
	void GCRuneEffect(PMSG_CUSTOM_RUNEEFFECT* aRecv);
	void RenderRuneEffect(DWORD ObjectModel, int ID, float Size, float ColorR, float ColorG, float ColorB, float Speed, float FloorDistance);
	void LoadRuneEffect(RuneEffectType* info);
	void Init();
	CUSTOM_RUNEEFFECT_DATA m_RuneEffect[16000];
public:
	std::vector<RuneEffectType> m_RuneEffectInfo;
private:
	// ---
};
extern RuneEffect gRuneEffect;
// ---