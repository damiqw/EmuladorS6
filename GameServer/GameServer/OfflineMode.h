#pragma once

#include "StdAfx.h"
#include "Protocol.h"
// ----------------------------------------------------------------------------------------------

#define OFFMAXTIME_FOR_BUFF		20	

#define OFFLINE_MODE_RESTORE	0

struct PBMSG_HEAD2_OFFLINE
{
public:
	void set(LPBYTE lpBuf, BYTE head, BYTE sub, BYTE size)
	{
		lpBuf[0] = 0xC1;
		lpBuf[1] = size;
		lpBuf[2] = head;
		lpBuf[3] = sub;
	};
	BYTE c;
	BYTE size;
	BYTE headcode;
	BYTE subcode;
};

struct CG_OFFMODE_RESULT
{
	PBMSG_HEAD2_OFFLINE h;
	WORD HuntingRange;
	//-- Potion
	BYTE RecoveryPotionOn;
	BYTE RecoveryPotionPercent;
	BYTE RecoveryHealOn; //-> CLASS_ELF
	BYTE RecoveryHealPercent; //-> CLASS_ELF
	BYTE RecoveryDrainOn; //-> CLASS_SUMMONER
	BYTE RecoveryDrainPercent; //-> CLASS_SUMMONER
	//-- Attack
	BYTE DistanceLongOn;
	BYTE DistanceReturnOn;
	WORD DistanceMin;//-- tiempo
	WORD SkillBasicID;
	BYTE ComboOn;				//-> CLASS_KNIGHT
	BYTE PartyModeOn;
	BYTE PartyModeHealOn;		//-> CLASS_ELF
	BYTE PartyModeHealPercent;	//-> CLASS_ELF
	BYTE PartyModeBuffOn;
	BYTE BuffOn;
	WORD BuffSkill[3];
	//-- Obtaing
	WORD ObtainRange;
	BYTE ObtainRepairOn;
	BYTE ObtainPickNear;
	BYTE ObtainPickSelected;
	BYTE ObtainPickMoney;
	BYTE ObtainPickJewels;
	BYTE ObtainPickExcellent;
	BYTE ObtainPickAncient;
	BYTE ObtainPickExtra;
	int ObtainPickExtraCount;
	char ObtainPickItemList[12][16];
};

class OfflineMode
{
public:
	OfflineMode();
	~OfflineMode();
	bool m_bLoadedDB;
	int m_ConnectIndex;
	DWORD m_ConnectTick;
	int m_MUOffHelperEnabled[4];
	int m_MUOffHelperTimer[4];
	void ReadOffLine(char* section, char* path);
	void Start(CG_OFFMODE_RESULT* aRecv, int UserIndex);
	void Attack(int UserIndex);
	void RenderAttack(int UserIndex);
	void RenderAutoBuffParty(int aIndex);
	void RenderAutoPote(int aIndex);
	int PickUP(int aIndex);
	void regresar(int aIndex);
	void OnAttackSecondProcHelper(LPOBJ lpObj); // OK
	void OnHelperpAlreadyConnected(LPOBJ lpObj); // OK
};
// ----------------------------------------------------------------------------------------------
extern OfflineMode g_OfflineMode;
// ----------------------------------------------------------------------------------------------
