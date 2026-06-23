#include "stdafx.h"
#include "CustomRankUser.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "User.h"
#include "Util.h"
#include "Object.h"
#include "Protect.h"
#include "Import.h"
#include "Common.h"
#include "PartyBar.h"

NEW_HEALTH_BAR gNewHealthBar[MAX_MAIN_VIEWPORT];
#if(FLAG)
BYTE MyManyFlag = 0;
#endif

void ClearNewHealthBar() // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		gNewHealthBar[n].index = 0xFFFF;
		gNewHealthBar[n].type = 0;
		gNewHealthBar[n].rate = 0;
		gNewHealthBar[n].rate2 = 0;
	}
#if(FLAG)
	MyManyFlag = 0;
#endif
}

void InsertNewHealthBar(PMSG_NEW_HEALTH_RECV* lpInfo) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index == 0xFFFF)
		{
			gNewHealthBar[n].index = lpInfo->index;
			gNewHealthBar[n].type = lpInfo->type;
			gNewHealthBar[n].rate = lpInfo->rate;
			gNewHealthBar[n].rate2 = lpInfo->rate2;
#if(FLAG)
			gNewHealthBar[n].bHasManyFlag = lpInfo->bHaeManyFlag;
#endif
			return;
		}
	}
}

NEW_HEALTH_BAR* GetNewHealthBar(WORD index,BYTE type) // OK
{
	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		if(gNewHealthBar[n].index != 0xFFFF)
		{
			if(gNewHealthBar[n].index == index && gNewHealthBar[n].type == type)
			{
				return &gNewHealthBar[n];
			}
		}
	}

	return 0;
}

void DrawNewHealthBar() // OK
{

	int PosX, PosY, LifeProgress, ShieldProgress;
	float LifeBarWidth = 40.0f;
	char LifeDisplay[25];
	VAngle Angle;

	if (gProtect.m_MainInfo.DisablePartyHpBar == 1)
	{
		if (QTPary.PartyMemberCount > 0)
		{
			for (int j = 0; j < QTPary.PartyMemberCount; j++)
			{
				signed int PartyNummber =  QTPary.JCPartyDB[j].ViewportID;

				//signed int PartyNummber = *((DWORD*)&pPartyListStruct + 8 * j + 7);

				//lpViewObj lpObj	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(),PartyNummber);

				DWORD ViewportAddress = ((DWORD(__thiscall*)(void*,DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(),PartyNummber);

				if (ViewportAddress)
				{
					Angle.X = *(float*)(ViewportAddress+0x404);

					Angle.Y = *(float*)(ViewportAddress+0x408);

					Angle.Z = *(float*)(ViewportAddress+0x40C) + *(float*)(ViewportAddress+0x3E8) + 100.0f;

					pGetPosFromAngle(&Angle, &PosX, &PosY);

					pDrawImage(30019, (float)(PosX - 8), (float)(PosY - 32), 24.0, 24.0,0.0, 0.40000001, 1.4, 1.4, 1, 1, 0.0);

				}
			}
		}
	}
	else if (gProtect.m_MainInfo.DisablePartyHpBar == 2)
	{

	}
	else
	{
		((void(*)())0x005BA770)();
	}
	

	for(int n=0;n < MAX_MAIN_VIEWPORT;n++)
	{
		DWORD ViewportAddress = ((DWORD(__thiscall*)(void*,DWORD))0x0096A4C0)(((void*(*)())0x00402BC0)(),n);

		lpViewObj lpObj		= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);
		lpViewObj lpTarget	= gObjUser.lpViewTarget;

		gObjUser.m_Logo[n].Active = 0;

		bool istarget = 1;

		if( !lpTarget || (lpTarget->m_Model.ObjectType != emMonster && lpTarget->m_Model.ObjectType != emPlayer) || !lpTarget->m_Model.Unknown4 || lpTarget->aIndex != lpObj->aIndex )
		{
			istarget = 0;
		}

		if(!ViewportAddress)
		{
			continue;
		}

		if(*(BYTE*)(ViewportAddress+0x30C) == 0)
		{
			continue;
		}

		Angle.X = *(float*)(ViewportAddress+0x404);

		Angle.Y = *(float*)(ViewportAddress+0x408);

		Angle.Z = *(float*)(ViewportAddress+0x40C) + *(float*)(ViewportAddress+0x3E8) + 100.0f;

		pGetPosFromAngle(&Angle, &PosX, &PosY);

		if (*(BYTE*)(ViewportAddress+0x320) == 1) //Check User Type
        {
           	gObjUser.m_Logo[n].Active = 1;
			gObjUser.m_Logo[n].X = PosX;
			gObjUser.m_Logo[n].Y = PosY;
        }

		PosX -= (int)floor(LifeBarWidth / (double)2.0);

		NEW_HEALTH_BAR* lpNewHealthBar = GetNewHealthBar(*(WORD*)(ViewportAddress+0x7E),*(BYTE*)(ViewportAddress+0x320));

		if(lpNewHealthBar == 0)
		{
			continue;
		}

		char* name = (char*)(ViewportAddress+0x38);

		float BarWidth;
		float SDBarWidth;
		float Height1;
		float Height2;
		float Height3;
		float LifeBackground;
		float PosXName;
		float PosXBar;
		float PosYBar;
		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			BarWidth = (((69.95 - 1) / 100.0f) * lpNewHealthBar->rate) - 1;
			LifeBackground = 70;
			SDBarWidth = (((69.95 - 1) / 100.0f) * lpNewHealthBar->rate2) - 1;
			Height1 = 4;
			Height2 = 3.5;
			Height3 = 6;
			PosXName = +17;
			PosXBar -=17;
			PosYBar = +2;
		}
		else
		{
			BarWidth = (((39.95 - 1) / 100.0f) * lpNewHealthBar->rate) - 1;
			LifeBackground = 40;
			SDBarWidth = (((39.95 - 1) / 100.0f) * lpNewHealthBar->rate2) - 1;
			Height1 = 3;
			Height2 = 2.5;
			Height3 = 4;
		}
		//int PercentLifeMonster = lpNewHealthBar->rate / 1;
		//int PercentLifeUser = lpNewHealthBar->rate / 1;
		//int PercentShieldUser = lpNewHealthBar->rate2 / 1;

		if (lpNewHealthBar->type == emPlayer)
		{	
			if(UserHpBar == 1)
			{
				if (istarget == 1)
		        {

					pSetBlend(true);

					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); 
					pDrawBarForm((float)(PosX - 1)+PosXBar, (float)(PosY - 5.5), LifeBackground, Height3, 0.0, 0);
					glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6); 
					pDrawBarForm((float)(PosX - 1) + PosXBar, (float)(PosY - 1 + PosYBar), LifeBackground, Height3, 0.0, 0);
						
					if (QTPary.PartyMemberCount > 0)
					{
						glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(255), 0.8);
					}
					else
					{
						glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(255), RGBTOGLFLOAT(0), 0.8);
					}

					pDrawBarForm((float)(PosX)+PosXBar, (float)(PosY-4), BarWidth, Height1, 0.0, 0);
					
					glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(255), RGBTOGLFLOAT(0), 0.8);
						
					pDrawBarForm((float)(PosX)+PosXBar, (float)(PosY-0.5 + PosYBar), SDBarWidth, Height2, 0.0, 0);

					//gCustomRankUser.DrawFormat(eWhite, PosX+1, PosY-24.05, 40, 3, "%d%%", PercentLifeUser);

					//gCustomRankUser.DrawFormat(eWhite, PosX+1, PosY-20, 40, 3, "%d%%", PercentShieldUser);

					pSetBlend(false);
					
				}

			}
		}
		else if (lpNewHealthBar->type == emMonster)
		{
			if (MonsterHpBar == 1)
			{
				pSetBlend(true);

				glColor4f(RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.6);
				pDrawBarForm((float)(PosX - 1), (float)(PosY - 1.5), LifeBackground, Height3, 0.0, 0);

				glColor4f(RGBTOGLFLOAT(255), RGBTOGLFLOAT(0), RGBTOGLFLOAT(0), 0.8);

				pDrawBarForm((float)(PosX), (float)(PosY), BarWidth, Height2, 0.0, 0);

				glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset color to white for the text
				gCustomRankUser.DrawFormat(eWhite, PosX-41+PosXName, PosY-10.0, 120, 3, "%s", name);

				//gCustomRankUser.DrawFormat(eWhite, PosX, PosY-0.05, 41, 3, "%d%%", PercentLifeMonster);
				
				pSetBlend(false);
			}
		}

		pGLSwitch();
	}

	gCustomRankUser.DrawInfo();

	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);
}

#if(FLAG)
BYTE GetPlayerManyFlag(WORD index)
{
	for (int n = 0; n < MAX_MAIN_VIEWPORT; n++)
	{
		if (gNewHealthBar[n].index != 0xFFFF)
		{
			if (gNewHealthBar[n].index == index)
			{
				return gNewHealthBar[n].bHasManyFlag;
			}
		}
	}
	return 0;
}
#endif