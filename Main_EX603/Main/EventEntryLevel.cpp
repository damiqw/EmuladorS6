#include "stdafx.h"
#include "EventEntryLevel.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"

void InitEventEntryLevel() // OK
{
	for(int n=0;n < 7;n++)
	{
		SetDword(0x008740FB+(0x1A*n),gProtect.m_MainInfo.m_BloodCastleEntryLevelCommon[n][0]);
		SetDword(0x00874108+(0x1A*n),gProtect.m_MainInfo.m_BloodCastleEntryLevelCommon[n][1]);
		SetDword(0x008741CB+(0x1A*n),gProtect.m_MainInfo.m_BloodCastleEntryLevelSpecial[n][0]);
		SetDword(0x008741D8+(0x1A*n),gProtect.m_MainInfo.m_BloodCastleEntryLevelSpecial[n][1]);
	}

	for(int n=0;n < 6;n++)
	{
		SetDword(0x00877C0B+(0x1A*n),gProtect.m_MainInfo.m_DevilSquareEntryLevelCommon[n][0]);
		SetDword(0x00877C18+(0x1A*n),gProtect.m_MainInfo.m_DevilSquareEntryLevelCommon[n][1]);
		SetDword(0x00877CC1+(0x1A*n),gProtect.m_MainInfo.m_DevilSquareEntryLevelSpecial[n][0]);
		SetDword(0x00877CCE+(0x1A*n),gProtect.m_MainInfo.m_DevilSquareEntryLevelSpecial[n][1]);
	}

	MemoryCpy(0x00D457C8,gProtect.m_MainInfo.m_ChaosCastleEntryLevelCommon,sizeof(gProtect.m_MainInfo.m_ChaosCastleEntryLevelCommon));

	MemoryCpy(0x00D457F8,gProtect.m_MainInfo.m_ChaosCastleEntryLevelSpecial,sizeof(gProtect.m_MainInfo.m_ChaosCastleEntryLevelSpecial));

	MemoryCpy(0x00D4DCF0,gProtect.m_MainInfo.m_KalimaEntryLevelCommon,sizeof(gProtect.m_MainInfo.m_KalimaEntryLevelCommon));

	MemoryCpy(0x00D4DD28,gProtect.m_MainInfo.m_KalimaEntryLevelSpecial,sizeof(gProtect.m_MainInfo.m_KalimaEntryLevelSpecial));

	MemoryCpy(0x00D48EAC,gProtect.m_MainInfo.m_IllusionTempleEntryLevelMin,sizeof(gProtect.m_MainInfo.m_IllusionTempleEntryLevelMin));

	MemoryCpy(0x00D48EC0,gProtect.m_MainInfo.m_IllusionTempleEntryLevelMax,sizeof(gProtect.m_MainInfo.m_IllusionTempleEntryLevelMax));

	SetDword(0x007E4BB8,0x270F); // Chaos Castle MaxLevel

	SetDword(0x008FF543,0x270F); // Kalima MaxLevel
}