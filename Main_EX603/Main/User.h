#pragma once
#include "Object.h"

#define CSParts2D				((float *(__thiscall*)(float * thisa, int a4, int a5, char a6, float a7, float a8, float a9, float a10, float a11, float a12)) 0x004EFFF0)
#define Operator_new			((float *(__cdecl*)(unsigned int a4)) 0x009D00C5)

#define MAX_ACCOUNT_LEVEL 4

struct CUSTOM_LOGO
{
	int Active;
	int	X;
	int	Y;
};

class User
{
public:
	void		Load();
	void		Refresh();	
	bool		GetTarget();
	char		getName[11];
	lpCharObj	lpPlayer;
	lpViewObj	lpViewPlayer;
	lpViewObj	lpViewTarget;
	BYTE		m_TargetType;	//1 - npc, 2 - attack
	int			m_MapNumber;
	int			m_CursorX;
	int			MagickAttack;
	int			m_TodayDaily;
	int			m_CursorY;
	DWORD		m_TargetUpdateTick;
	int GetActiveSkill();
	static void	SetEventEffect(int PreviewStruct);

#if(FLAG)
	static bool CreateManyFlag(ObjectPreview* pChar);
	static void __cdecl HoolCreateManyFlay(ObjectPreview* pChar);
#endif

	//-- post item
	int				PostItemID;
	int				PostItemLV;
	int				PostItemExc;
	int				PostItemAcc;
	int				PostItemHarmony;
	int				PostItem380;
	char*			PostItemSocket;
	int				PostItemX;
	int				PostItemY;
	//Auto Sendmove
	DWORD		IsSendMove;
	DWORD		MoveToX;
	DWORD		MoveToY;
	BYTE		IsMove;
	int        AutoMoveCheckMap;

	int m_MaxStatPoint[MAX_ACCOUNT_LEVEL];
	int GetMaxStatPoint(int AccountLevel);
	int	d_Strength;
	int	d_Dexterity;
	int	d_Vitality;
	int	d_Energy;
	int	d_Leadership;
	static void ChangeCharInfo(LPVOID This);
	static char* GetMapName(signed int MapNumber);

	CUSTOM_LOGO m_Logo[400];
};
extern User gObjUser;