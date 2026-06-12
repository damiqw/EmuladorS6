#include "stdafx.h"
#include "protocol.h"
#include "Interface.h"
#include "Defines.h"
#include "CustomStatsAdvance.h"
#include "InterfaceElemental.h"
#include "CustomFont.h"
#include "Protect.h"

CStatsAdvance g_StatsAdvance;

CStatsAdvance::CStatsAdvance()
{
	this->m_Enable = false;
	this->m_Loaded = false;

	memset(&this->m_Data, 0, sizeof(this->m_Data));
}

CStatsAdvance::~CStatsAdvance()
{
}

void CStatsAdvance::Load()
{
	this->m_Enable = true;
}

#include "SEASON3B.h"
void CStatsAdvance::DrawInfo()
{
	if (!this->m_Enable && !this->m_Loaded)
	{
		return;
	}

	if (!gInterface.CheckWindow(ObjWindow::Character))
	{
		return;
	}

	int JCResto;
#if WIDE_SCREEN
	JCResto = setPosRight(0.0);
#else
	JCResto = 0;
#endif
	pSetBlend(true);

	pLoadImage("Custom\\Interface\\StatsAdvanced.tga", 561020, 0x2601, 0x2900, 1, 0);

	DWORD dwColor = eWhite;
	float flDrawX = this->m_CharX + 583;	//450;
	float flDrawY = this->m_CharY + 85;	//18;


	gInterface.DrawGUI(eADVANCE_STAT_INFO, JCResto + flDrawX, flDrawY - 10);

	if (!gInterface.IsWorkZone(eADVANCE_STAT_INFO))
	{
		return;
	}

	flDrawX = this->m_CharX + 450;	// - 15;
	flDrawY = 0;//this->m_CharY - 52;	//18;

	float flWidth = 190;
	float flHight = 430;

	gElemental.gInfoBox(JCResto + flDrawX -190, flDrawY + 5, flWidth - 10, flHight - 15, 0x00000096, 0, 1.0);

	flDrawY += 15;

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Total Damage Reflect:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.TotalDamageReflect);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Full DamageReflect Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.FullDamageReflectRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Critical Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.CriticalDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Critical Damage (PVM):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eBlue, "%d", this->m_Data.CriticalDamagePVM);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Critical Damage (PVP)");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eBlue, "%d", this->m_Data.CriticalDamagePVP);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Exellent Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ExellentDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Exellent Damage (PVM):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eAncient, "%d", this->m_Data.ExellentDamagePVM);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Exellent Damage (PVP):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eAncient, "%d", this->m_Data.ExellentDamagePVP);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Double Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.DoubleDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Triple Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.TripleDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Damage Reduction Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.DamageReductionRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Shield Skill Damage Reduction Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ShieldSkillDamageReductionRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "SD Damage Reduction Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.SDDamageReductionRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "SD Decrease Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.SDDecreaseDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Ignore Defence Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.IgnoreDefenceRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Ignore SD Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.IgnoreSDRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Increase Damage PvP:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d", this->m_Data.IncreaseDamagePvP);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Increase Defence PvP:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d", this->m_Data.IncreaseDefencePvP);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Double Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistDoubleDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Ignore Defence Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistIgnoreDefenceRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Ignore SD Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistIgnoreSDRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Critical Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistCriticalDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Exellent Damage Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistExellentDamageRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Resist Stum Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%%", this->m_Data.ResistStumRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Ice Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseIce, this->m_Data.ResistIce);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Poison Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreasePoison, this->m_Data.ResistPoison);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Lighting Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseLighting, this->m_Data.ResistLighting);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Fire Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseFire, this->m_Data.ResistFire);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Earth Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseEarth, this->m_Data.ResistEarth);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Wind Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseWind, this->m_Data.ResistWind);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Water Increase / Resist Rate:");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d - %d%%", this->m_Data.IncreaseWater, this->m_Data.ResistWater);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Full HP Restore Rate (Def, Att):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%% - %d%%", this->m_Data.FullHPRestoreRateDef, this->m_Data.FullHPRestoreRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Full MP Restore Rate (Def, Att):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%% - %d%%", this->m_Data.FullMPRestoreRateDef, this->m_Data.FullMPRestoreRate);

	this->DrawLine(JCResto + flDrawX - 192, flDrawY, flWidth, "Full SD Restore Rate (Def, Att):");
	flDrawY = this->DrawLineR(JCResto + flDrawX - 192, flDrawY, flWidth, eGold, "%d%% - %d%%", this->m_Data.FullSDRestoreRateDef, this->m_Data.FullSDRestoreRate);

	gInterface.DrawFormat(eGold, JCResto + flDrawX - 185, 5, flWidth, 3, "ADVANCED STATUS");

}

void CStatsAdvance::DrawLine(float PosX, float PosY, int Width, LPCSTR Text, ...)
{
	float flResult = 0.0;

	char szBuff[256];
	int iBuffLen = sizeof(szBuff) - 1;
	ZeroMemory(szBuff, iBuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(szBuff, iBuffLen, Text, args);
	va_end(args);

	pDrawColorText(szBuff, PosX + 10, PosY, 150, 0, eWhite, 0, 1);
}

float CStatsAdvance::DrawLineR(float PosX, float PosY, int Width, DWORD dwColor, LPCSTR Text, ...)
{
	float flResult = 0.0;

	char szBuff[256];
	int iBuffLen = sizeof(szBuff) - 1;
	ZeroMemory(szBuff, iBuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(szBuff, iBuffLen, Text, args);
	va_end(args);

	pDrawColorText(szBuff, PosX + 140, PosY, 50, 0, dwColor, 0, 1);

	pDrawColorButton(31460, PosX + 10, PosY + 10, Width - 20, 0.25, NULL, NULL, eWhite150);

	flResult = PosY + 12;

	return flResult;
}

void CStatsAdvance::Recv(PMSG_STATS_ADVANCE* lpMsg)
{
	if (!lpMsg->Result)
	{
		return;
	}

	memcpy(&this->m_Data, &lpMsg->StatInfo, sizeof(this->m_Data));

	this->m_Loaded = true;
}