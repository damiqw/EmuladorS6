#include "stdafx.h"
#include "CustomRanking.h"
#include "Defines.h"
#include "HealthBar.h"
#include "Interface.h"
#include "Util.h"
#include "Object.h"
#include "Import.h"
#include "SItemOption.h"
#include "UIController.h"
#include "ViewCharItem.h"
#include "CustomFont.h"
#include "InterfaceElemental.h"
#include "PartyBar.h"
#include "CustomMessage.h"
#include "CNewUIWindowsClient.h"
#include "ThueFlag.h"
#include "Protect.h"

CCustomRanking::CCustomRanking()
{
}

CCustomRanking gCustomRanking;


void CCustomRanking::ClearCustomRanking() // OK
{
	for (int n = 0; n < MAX_RANK; n++)
	{
		memset(gCustomRanking[n].szName, 0, sizeof(gCustomRanking[n].szName));
		memset(gCustomRanking[n].value2, 0, sizeof(gCustomRanking[n].value2));
		gCustomRanking[n].CheckOnline = 0;

	}
#if(CUSTOM_BRANKINGNEW)
	ZeroMemory(&this->CacheDataUserTop, sizeof(&this->CacheDataUserTop));
	this->CacheUserRank = false;
	this->SetItemCharTop = false;
#endif
	this->RankEnable = 0;

}

void CCustomRanking::GCReqRanking(PMSG_CUSTOM_RANKING_RECV* lpMsg) // OK
{
	memcpy(this->rankname, lpMsg->rankname, sizeof(this->rankname));
	memcpy(this->col1, lpMsg->col1, sizeof(this->col1));
	memcpy(this->col2, lpMsg->col2, sizeof(this->col2));
	this->RankEnable = 1;


	mListRanking.clear();

	this->count = lpMsg->count;

	for (int n = 0; n < lpMsg->count; n++)
	{
		CUSTOM_RANKING_DATA* lpInfo = (CUSTOM_RANKING_DATA*)(((BYTE*)lpMsg) + sizeof(PMSG_CUSTOM_RANKING_RECV) + (sizeof(CUSTOM_RANKING_DATA) * n));
		mListRanking.push_back(lpInfo->szName);
		memcpy(gCustomRanking[n].szName, lpInfo->szName, sizeof(gCustomRanking[n].szName));
		memcpy(gCustomRanking[n].value2, lpInfo->value2, sizeof(gCustomRanking[n].value2));
		gCustomRanking[n].CheckOnline = lpInfo->CheckOnline;
	}
}

void CCustomRanking::RankNameRev(PMSG_RANK_INFO* lpMsg)
{
	memset(this->m_RankInfo, 0, sizeof(this->m_RankInfo));
	for (int i = 0; i < MAX_RANK; i++)
	{

		memcpy(this->m_RankInfo[i].NameRank, lpMsg->Info[i].NameRank, 32);

	}
}

void CCustomRanking::GCReqRankingCount(PMSG_CUSTOM_RANKING_COUNT_RECV* lpMsg) // OK
{

	this->RankingCount = (lpMsg->count > 0) ? lpMsg->count : 0;
}
int NextRanking = 0;
int PrevRanking = 0;

#if(CUSTOM_BRANKINGNEW)
#include "Character.h"

char* CharacterCode(int a)
{
	switch (a)
	{
	case 0:  return pGetTextLine(pTextLineThis, 20);
	case 1:  return pGetTextLine(pTextLineThis, 25);
	case 2:  return pGetTextLine(pTextLineThis, 1669);
	case 3:  return pGetTextLine(pTextLineThis, 1669);
	case 16: return pGetTextLine(pTextLineThis, 21);
	case 17: return pGetTextLine(pTextLineThis, 26);
	case 18: return pGetTextLine(pTextLineThis, 1668);
	case 19: return pGetTextLine(pTextLineThis, 1668);
	case 32: return pGetTextLine(pTextLineThis, 22);
	case 33: return pGetTextLine(pTextLineThis, 27);
	case 34: return pGetTextLine(pTextLineThis, 1670);
	case 35: return pGetTextLine(pTextLineThis, 1670);
	case 48: return pGetTextLine(pTextLineThis, 23);
	case 50: return pGetTextLine(pTextLineThis, 1671);
	case 66: return pGetTextLine(pTextLineThis, 24);
	case 67: return pGetTextLine(pTextLineThis, 24);
	case 64: return pGetTextLine(pTextLineThis, 24);
	case 65: return pGetTextLine(pTextLineThis, 24);
	case 68: return pGetTextLine(pTextLineThis, 1672);
	case 80: return pGetTextLine(pTextLineThis, 1687);
	case 81: return pGetTextLine(pTextLineThis, 1688);
	case 82: return pGetTextLine(pTextLineThis, 1689);
	case 83: return pGetTextLine(pTextLineThis, 1689);
	case 96: return pGetTextLine(pTextLineThis, 3150);
	case 97: return pGetTextLine(pTextLineThis, 3151);
	case 98: return pGetTextLine(pTextLineThis, 3151);
	}
	return "unknown";
}

#define B0042CFE0									((int (__thiscall*)(int This, unsigned int  a2)) 0x0042CFE0)
//----- (005D30F0) --------------------------------------------------------
void __cdecl BCreateGuildMark(BYTE* mGuildMark, bool a2)
{
	int k; // [esp+4h] [ebp-24h]
	int j; // [esp+8h] [ebp-20h]
	int i; // [esp+Ch] [ebp-1Ch]
	_DWORD* v5; // [esp+10h] [ebp-18h]
	int* v6; // [esp+14h] [ebp-14h]
	BYTE* v7; // [esp+18h] [ebp-10h]
	int height; // [esp+1Ch] [ebp-Ch]
	int width; // [esp+20h] [ebp-8h]
	int v10; // [esp+24h] [ebp-4h]

	DWORD* dword_81C0450 = &*(DWORD*)0x81C0450;
	BYTE* byte_81CB59E = &*(BYTE*)0x81CB59E;

	v6 = (int*)B0042CFE0((int)0x9816AA0, 0x7BFCu);


	width = (int)*((float*)v6 + 65);
	height = (int)*((float*)v6 + 66);
	v5 = *(_DWORD**)((char*)v6 + 282);
	v10 = 128;
	if (a2)
	{
		v10 = 0;
	}

	for (int i = 0; i < 16; i++)
	{
		switch (i)
		{
		case 0:dword_81C0450[i] = (v10 << 24) + (0 << 16) + (0 << 8) + (0); break;
		case 1:dword_81C0450[i] = (255 << 24) + (0 << 16) + (0 << 8) + (0); break;
		case 2:dword_81C0450[i] = (255 << 24) + (128 << 16) + (128 << 8) + (128); break;
		case 3:dword_81C0450[i] = (255 << 24) + (255 << 16) + (255 << 8) + (255); break;
		case 4:dword_81C0450[i] = (255 << 24) + (0 << 16) + (0 << 8) + (255); break;
		case 5:dword_81C0450[i] = (255 << 24) + (0 << 16) + (128 << 8) + (255); break;
		case 6:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (255); break;
		case 7:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (128); break;
		case 8:dword_81C0450[i] = (255 << 24) + (0 << 16) + (255 << 8) + (0); break;
		case 9:dword_81C0450[i] = (255 << 24) + (128 << 16) + (255 << 8) + (0); break;
		case 10:dword_81C0450[i] = (255 << 24) + (255 << 16) + (255 << 8) + (0); break;
		case 11:dword_81C0450[i] = (255 << 24) + (255 << 16) + (128 << 8) + (0); break;
		case 12:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (0); break;
		case 13:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (128); break;
		case 14:dword_81C0450[i] = (255 << 24) + (255 << 16) + (0 << 8) + (255); break;
		case 15:dword_81C0450[i] = (255 << 24) + (128 << 16) + (0 << 8) + (255); break;
		}
	}

	BYTE GuildMark[64] = { 0 };
	for (int i = 0; i < 64; ++i)
	{
		if (i % 2 == 0)
			GuildMark[i] = (mGuildMark[i / 2] >> 4) & 0x0f;
		else
			GuildMark[i] = mGuildMark[i / 2] & 0x0f;
	}

	v7 = &*(BYTE*)GuildMark; //Mark
	for (j = 0; j < height; ++j)
	{
		for (k = 0; k < width; ++k)
			*v5++ = dword_81C0450[(unsigned __int8)*v7++];
	}
	glBindTexture(0xDE1u, *(_DWORD*)((char*)v6 + 277));
	glTexImage2D(0xDE1u, 0, *((char*)v6 + 276), width, height, 0, 0x1908u, 0x1401u, *(const GLvoid**)((char*)v6 + 282));
}
void GetInfoCharTop(char* Name)
{
	if (GetTickCount() < gInterface.Data[eRankPANEL_MAIN].EventTick + 300) return;
	gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();

	REQUESTINFO_CHARTOP pMsg;
	pMsg.header.set(0xD3, 0x40, sizeof(pMsg));
	pMsg.aIndex = 0;
	memcpy(pMsg.NameChar, Name, sizeof(pMsg.NameChar) - 1);
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
}
int rankmodel = 0;

void DrawPlayerRank(int X, int Y, int W, int H)
{

	X = X - 10;
	Y = Y + 40;
	H = H - 100;

	if (!gCustomRanking.CacheUserRank)
	{
		gInterface.DrawFormat(eGold, X + (W / 2), Y + (H / 2), 52, 1, "Loading ..");
	}
	else
	{
		gElemental.gInfoBox(X, Y, W, H, 0x00000096, 0, 0);
		//===Show 3D
		character.BDrawHeroTop(X - 10, Y, 130, 180, oHero9 + rankmodel, 1.0, gCustomRanking.CacheDataUserTop.Class);
		//==Name Char
		CustomFont.Draw((HFONT)pFontBold, X + 1, Y, 0xFFFFFFFF, 0x00FBFF69, W + 6, 0, 3, gCustomRanking.CacheDataUserTop.NameChar);//
		//==View Item 
		if (gProtect.m_MainInfo.RankingShowItems == 1)
		{
			gInterface.gDrawButtonGUI(31230, (X + W) - 15, Y + 15, 15, 15, 1);//?
			if (pCheckMouseOver((X + W) - 15, Y + 15, 15, 15) == 1)
			{
				if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[eRankPANEL_MAIN].EventTick + 300)
				{
					ViewCharItems.DangXem ^= 1;
					ViewCharItems.ActionTime = GetTickCount();
					gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();
				}
		
				pDrawToolTip(pCursorX - 60, pCursorY - 10, gCustomMessage.GetMessage(99));
			}
		}

		if (gCustomRanking.CacheDataUserTop.GuildName[0] != 0xFFFFFFFF && strlen(gCustomRanking.CacheDataUserTop.GuildName) > 1)
		{
			//=Guild
			//CustomFont.Draw((HFONT)pFontBold, X + (W / 2) - 15, Y + 145, 0xFFFFFFFF, 0x0, 0, 0, 1, gCustomMessage.GetMessage(131));//100
			CustomFont.Draw((HFONT)pFontBold, X + (W / 2) - 35, Y + 145, 0xFFFFFFFF, 0x0, 0, 0, 1, gCustomMessage.GetMessage(100));//100
			CustomFont.Draw((HFONT)pFontBold, X + (W / 2), Y + 145, 0x00FBFFFF, 0x0, 0, 0, 1, gCustomRanking.CacheDataUserTop.GuildName);//
			//==Logo Guild
			gElemental.gInfoBox((X + W) - 30, Y + 125, 27, 27, 0x00000096, 0, 0);
			//gInterface.DrawBarForm((X + W) - 27, Y + 128, 30, 30, 1.0, 0.0, 0.0, 1.0);//Test
			BCreateGuildMark(gCustomRanking.CacheDataUserTop.GuildMark, 1);
			RenderBitmap(31740, (X + W) - 27, Y + 128, 30, 30, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		}

		float TextX = X + 10;
		//==Tong Point
		gElemental.gInfoBox(TextX - 10, (Y + H) + 13, W, 42, 0x00000096, 0, 0);
		CustomFont.Draw((HFONT)pFontNormal, TextX, (Y + H) + 15, 0xEBA000FF, 0x0, (W / 4), 0, 3, gCustomMessage.GetMessage(101));//
		CustomFont.Draw((HFONT)pFontBold, TextX + (W / 4), (Y + H) + 15, 0x43F72FFF, 0x0, (W / 4), 0, 3, "%s", BNumberFormat(gCustomRanking.CacheDataUserTop.TongPoint));//
		//==Tong Reset
		CustomFont.Draw((HFONT)pFontNormal, TextX + ((W / 4) * 2), (Y + H) + 15, 0xEBA000FF, 0x0, (W / 4), 0, 3, gCustomMessage.GetMessage(102));//
		CustomFont.Draw((HFONT)pFontBold, TextX + ((W / 4) * 3), (Y + H) + 15, 0x43F72FFF, 0x0, (W / 4), 0, 3, "%s", BNumberFormat(gCustomRanking.CacheDataUserTop.Reset));//

		//==C?p ?
		CustomFont.Draw((HFONT)pFontNormal, TextX, (Y + H) + 25, 0xEBA000FF, 0x0, (W / 4), 0, 3, gCustomMessage.GetMessage(103));//
		CustomFont.Draw((HFONT)pFontBold, TextX + (W / 4), (Y + H) + 25, 0x43F72FFF, 0x0, (W / 4), 0, 3, "%s", BNumberFormat(gCustomRanking.CacheDataUserTop.Level));//
		//==C?p Master
		CustomFont.Draw((HFONT)pFontNormal, TextX + ((W / 4) * 2), (Y + H) + 25, 0xEBA000FF, 0x0, (W / 4), 0, 3, gCustomMessage.GetMessage(104));//
		CustomFont.Draw((HFONT)pFontBold, TextX + ((W / 4) * 3), (Y + H) + 25, 0x43F72FFF, 0x0, (W / 4), 0, 3, "%s", BNumberFormat(gCustomRanking.CacheDataUserTop.MasterLevel));//
		//==Luc Chien
		//CustomFont.Draw((HFONT)pFontNormal, TextX, (Y + H) + 35, 0xEBA000FF, 0x0, (W / 4), 0, 3, gOther.Text_GAME[130]);//
		//CustomFont.Draw((HFONT)pFontBold, (TextX + (W / 2)) - 40, (Y + H) + 35, 0x43F72FFF, 0x0, 0, 0, 1, "%s", CharacterCode(gCustomRanking.CacheDataUserTop.Class));//
		//CustomFont.Draw((HFONT)pFontBold, (TextX + (W / 2)) - 50, (Y + H) + 48, 0x7c509bFF, 0x0, 0, 0, 1, gOther.Text_GAME[131]);//
		//HFONT CHFontMini = CreateFontA(22, 0, 0, 0, 400, 0, 0, 0, 0x1, 0, 0, 3u, 0, "Arial");
		//CustomFont.Draw(CHFontMini, TextX + (W / 2), (Y + H) + 45, 0xff0000FF, 0x0, W, 0, 1, "%s", BNumberFormat(gCustomRanking.CacheDataUserTop.LucChien));//
		//DeleteObject(CHFontMini);
		//==Set Item Char

		if (!gCustomRanking.SetItemCharTop)
		{
			character.ClearPetCache(1);
			for (int n = 0; n < 12; n++)
			{
				if (gCustomRanking.CacheDataUserTop.Item[n][0] != 0xFF && gCustomRanking.CacheDataUserTop.Item[n][0] != 0)
				{
					//gInterface.DrawMessage(1, "(%d) %x", n, gCustomRanking.CacheDataUserTop.Item[n][0]);
					//if (gCustomRanking.CacheDataUserTop.Item[n][0] == 0xFF) continue;
					int GetInfoLoadItem = ((int(__thiscall*)(int a1, void* lp)) 0x7E1B10)(*(DWORD*)(GetInstance() + 36), gCustomRanking.CacheDataUserTop.Item[n]);
					if (GetInfoLoadItem)
					{
						character.UpdateItemChar(oHero9 + rankmodel, n, *(WORD*)GetInfoLoadItem + 1171, ((*(DWORD*)(GetInfoLoadItem + 2) >> 3) & 15), *(BYTE*)(GetInfoLoadItem + 23), *(BYTE*)(GetInfoLoadItem + 24));
						memcpy(&ViewCharItems.charItem.Item[n], (BYTE*)GetInfoLoadItem, sizeof(ViewCharItems.charItem.Item[n]));

					}
				}
			}
			gCustomRanking.SetItemCharTop = true;
		}

	}
}
int PageRank = 0;
int MaxPerPageRank = 10;
static void BPagePrevAction(LPVOID pClass)
{
	if (GetTickCount() < gInterface.Data[eRankPANEL_MAIN].EventTick + 300) return;
	gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();

	if (PageRank > 0)
	{
		PageRank--;
	}
	//pDrawMessage("-",1);
}
static void BPageNextAction(LPVOID pClass)
{
	if (GetTickCount() < gInterface.Data[eRankPANEL_MAIN].EventTick + 300) return;
	gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();

	if (PageRank < (gCustomRanking.count / MaxPerPageRank) + 10)
	{
		PageRank++;
	}
	//pDrawMessage("+", 1);
}
void CCustomRanking::GCReqInfoCharTop(DATA_VIEWTOPRANKING* lpMsg)
{
	//pDrawMessage("+", 1);
	this->CacheUserRank = true;
	this->SetItemCharTop = false;
	ZeroMemory(&this->CacheDataUserTop, sizeof(&this->CacheDataUserTop));
	memcpy(&this->CacheDataUserTop, lpMsg, sizeof(this->CacheDataUserTop));
	ViewCharItems.ClearSession();
	rankmodel = rand() % 100;

	memcpy(&ViewCharItems.charItem.Guild[0], &this->CacheDataUserTop.GuildName[0], sizeof(ViewCharItems.charItem.Guild));
	memcpy(&ViewCharItems.charItem.Name[0], &this->CacheDataUserTop.NameChar[0], 10);
	ViewCharItems.charItem.Class = this->CacheDataUserTop.Class;

}
DWORD TimeGetTop1 = 0;
bool SelectBarRanking = false;

#endif
#include "Common.h"
void CCustomRanking::DrawRankPanelWindow()
{
	if (!gInterface.Data[eRankPANEL_MAIN].OnShow)
	{
		return;
	}

	if (gInterface.CheckWindow(Inventory)
		|| gInterface.CheckWindow(Character) //-- 13 & 16
		|| gInterface.CheckWindow(Warehouse) //-- 8
		|| gInterface.CheckWindow(Shop) //-- 12
		|| gInterface.CheckWindow(ChaosBox) //-- 9
		|| gInterface.CheckWindow(Trade) //-- 7
		|| gInterface.CheckWindow(Store) //-- 14
		|| gInterface.CheckWindow(OtherStore) //-- 15
		|| gInterface.CheckWindow(LuckyCoin1) //-- 60
		|| gInterface.CheckWindow(NPC_ChaosMix)
		|| gInterface.CheckWindow(MoveList)

		)
	{
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;
		return;
	}

	gInterface.CheckWindowSProTecno(9);

	pSetCursorFocus = true;
	float MainWidth = 310.0;
#if(CUSTOM_BRANKINGNEW)
	MainWidth += 160;
#endif

	if (ViewCharItems.DangXem == 1)
	{
		MainWidth += 160;
	}

	float MainHeight = 255.0;
	float StartBody;
	StartBody = ((480 - 51) / 2) - (MainHeight / 2);
	float StartY = 60;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2) - 3;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);
	float PosX = 50;

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX - 49 + PosX, StartY - 8, MainWidth + 6, MainHeight + 27, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + MainWidth -336, StartBody -14, 210, 3, gCustomMessage.GetMessage(32));
		gInterface.DrawGUI2(eRanking_CLOSE, StartX + MainWidth - gInterface.Data[eRanking_CLOSE].Width - 7, StartBody - 17);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + MainWidth - gInterface.Data[eRanking_CLOSE].Width - 7, StartBody - 16, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eRanking_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eRanking_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eRanking_CLOSE, gInterface.Data[eRanking_CLOSE].X, StartY, Color);
		}
	}
	else
	{
		RenderBitmap(61322, StartX - 46 + PosX, StartY -8, MainWidth -5, MainHeight + 95, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX - 46 + PosX, StartY -8, MainWidth -5, MainHeight - 210, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + MainWidth - 337, StartBody - 14, 210, 3, gCustomMessage.GetMessage(32));
		gInterface.DrawGUI2(eRanking_CLOSE, StartX + MainWidth - gInterface.Data[eRanking_CLOSE].Width + 1, StartBody - 34);
		if (gInterface.IsWorkZone(eRanking_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eRanking_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eRanking_CLOSE, gInterface.Data[eRanking_CLOSE].X, gInterface.Data[eRanking_CLOSE].Y, Color);
		}
	}
	{
		DWORD Color = eGray100;

		float SizeButtonW = 80.0;

		if (this->RankEnable == 1)
		{
			gInterface.DrawFormat(eWhite, StartX + 30, StartY + 35, 52, 1, "TOP:");

			gInterface.DrawFormat(eWhite, StartX + 80, StartY + 35, 52, 1, "%s", this->col1);

			gInterface.DrawFormat(eWhite, StartX + 145, StartY + 35, 52, 1, "%s", this->col2);

			char* name = (char*)(oUserPreviewStruct + 0x38);

			//for (int i = 0; i < this->count; i++)
#if(CUSTOM_BRANKINGNEW)
			for (int n = 0, i = (PageRank * MaxPerPageRank); n < MaxPerPageRank && i < this->count; i++)
#else
			for (int i = 0; i < this->count; i++)
#endif
			{
				Color = eGold;

				if (strcmp(name, this->gCustomRanking[i].szName) == 0)
				{
					Color = eExcellent;
				}
#if(CUSTOM_BRANKINGNEW)
				if (pCheckMouseOver(StartX + 20, StartY + 50 + (18 * n), 255, 15) == 1 && !ViewCharItems.getState())
				{
					if (pIsKeyPress(VK_LBUTTON) && GetTickCount() > gInterface.Data[eRankPANEL_MAIN].EventTick + 300)
					{
						GetInfoCharTop(this->gCustomRanking[i].szName);
						gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();
					}

					gElemental.gInfoBox(StartX + 20, StartY + 51 + (18 * n), 255, 6, 0x26E0A596, 0, 0);
				}
				else
				{
					gElemental.gInfoBox(StartX + 20, StartY + 51 + (18 * n), 255, 6, 0x00000096, 0, 0);
				}
#else
				gCItemSetOption.ItemTooltipS15(StartX + 20, StartY + 50 + (18 * n), 245, 15, 0.0, 0);
#endif

				gInterface.DrawFormat(Color, StartX + 30, StartY + 53 + (18 * n), 52, 1, "%d?", (i + 1));
#if(CUSTOM_BRANKINGNEW)

				if (this->gCustomRanking[i].CheckOnline)
				{
					gInterface.DrawBarForm(StartX + 70, StartY + 55 + (18 * n), 5.0, 5.0, 0.0, 1.0, 0.0, 0.75);
				}
				else
				{
					gInterface.DrawBarForm(StartX + 70, StartY + 55 + (18 * n), 5.0, 5.0, 1.0, 0.0, 0.0, 0.75);
				}

				if (!this->CacheUserRank)
				{
					GetInfoCharTop(this->gCustomRanking[0].szName);
				}
#endif
				gInterface.DrawFormat(Color, StartX + 80, StartY + 53 + (18 * n), 52, 1, "%s", this->gCustomRanking[i].szName);

				gInterface.DrawFormat(Color, StartX + 145, StartY + 53 + (18 * n), 120, 1, "%s", this->gCustomRanking[i].value2);
#if(CUSTOM_BRANKINGNEW)
				n++;
#endif
			}

#if(CUSTOM_BRANKINGNEW)
			//Next Page
			float CenterX = StartX + (290 / 2);
			float CenterY = (StartY + 270);
			const BYTE state[3] = { 0, 1, 2 };
			RenderBitmap(32344, CenterX - (60 / 2), CenterY - 40, 60.f, 22.f, 0, 0, 80.f / 128.f, 30.f / 34.f, 1, 1, 0.0);

			CustomFont.Draw((HFONT)pFontBold, CenterX - (60 / 2), CenterY - 40 + 5, 0xffffffff, 0x0, 60, 0, 3, "%d / %d", PageRank + 1, (this->count / MaxPerPageRank + 10));
			//
			if (gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				UIController.Button(32345, CenterX - (60 / 2) - 26, CenterY - 40, 20, 22, 20, 22, 3, state, BPagePrevAction);
				UIController.Button(32346, CenterX + (60 / 2) + 6, CenterY - 40, 20, 22, 20, 22, 3, state, BPageNextAction);
			}
			else
			{
				UIController.Button(32342, CenterX - (60 / 2) - 26, CenterY - 40, 20, 22, 20, 22, 3, state, BPagePrevAction);
				UIController.Button(32343, CenterX + (60 / 2) + 6, CenterY - 40, 20, 22, 20, 22, 3, state, BPageNextAction);
			}

			DrawPlayerRank(StartX + 300, StartY, 150, MainHeight);
			//ViewCharItems.DrawCharInfo();
			ViewCharItems.DrawCharInfoRanking(StartX + 190, StartY, 150, MainHeight);
			float ListItemX = StartX + 30;
			DWORD SelectBarHoverBG = 0x0;
			float SelectBarY = StartY - 30;
			int SelectBarHover = 0;
			RenderBitmap(31424, ListItemX - 2, SelectBarY + 37, 110, 20, 0.0, 0.0, 0.82, 0.71, 1, 1, 0.0);
			if (pCheckMouseOver(ListItemX - 2, SelectBarY + 37, 110, 20))
			{

				SelectBarHover = 1;
				SelectBarHoverBG = 0x66646450;
				if (GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500) //Click
				{
					if (GetKeyState(VK_LBUTTON) & 0x8000)
					{
						SelectBarHover = 2;
						gInterface.Data[eWindowClick].EventTick = GetTickCount();
						PlayBuffer(25, 0, 0);
						SelectBarRanking ^= 1;
					}
				}
			}
			RenderBitmap(31422, ListItemX + 2, SelectBarY + 39.5, 13.5, 13.5, 0.0, 0.21 * SelectBarHover, 0.91, 0.21, 1, 1, 0.0);
			CustomFont.Draw((HFONT)pFontBold, ListItemX + 15, SelectBarY + 41, 0xFFFFFFFF, SelectBarHoverBG, 85, 0, 3, "%s", this->m_RankInfo[this->SelectBarRankingNumber].NameRank);// 
			if (SelectBarRanking)
			{
				int CountSelectBar = 1;
				gInterface.DrawBarForm(ListItemX + 15, SelectBarY + 41 + (15), 85, 15 * 12, 0.0, 0.0, 0.0, 0.8);
				for (int i = 0; i < this->RankingCount; i++)
				{
					if (SelectBarRankingNumber == i) continue;
					DWORD SelectHover = 0x0;
					if (pCheckMouseOver(ListItemX + 15, SelectBarY + 41 + (15 * CountSelectBar), 130, 15))
					{
						SelectHover = 0x66646450;
						if (GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500) //Click
						{
							if (GetKeyState(VK_LBUTTON) & 0x8000)
							{
								//gInterface.DrawMessage(1,"%d ~ %d", this->RankingType,this->RankingCount);
								SelectBarRankingNumber = i;
								gInterface.Data[eWindowClick].EventTick = GetTickCount();
								PlayBuffer(25, 0, 0);
								SelectBarRanking ^= 1;
								this->ClearCustomRanking();
								PageRank = 0;
								PMSG_CUSTOM_RANKING_SEND pMsg;

								pMsg.header.set(0xF3, 0xE6, sizeof(pMsg));


								pMsg.type = i;

								DataSend((BYTE*)&pMsg, pMsg.header.size);

							}
						}
					}
					CustomFont.Draw((HFONT)pFontBold, ListItemX + 15, SelectBarY + 41 + (15 * CountSelectBar), 0xFFFFFFFF, SelectHover, 85, 0, 3, "%s", this->m_RankInfo[i].NameRank);// 
					CountSelectBar++;
				}
			}

#endif
		}
		else
		{
			if (this->RankLoad == 1)
			{
				gInterface.DrawFormat(eGold, MainCenter - (sizeof(this->rankname) / 2) + 30, StartY + 120, 52, 1, "Loading ..");
				this->RankLoad = 2;
			}
			else if (this->RankLoad == 2)
			{
				gInterface.DrawFormat(eGold, MainCenter - (sizeof(this->rankname) / 2) + 30, StartY + 120, 52, 1, "Loading ...");
				this->RankLoad = 3;
			}
			else if (this->RankLoad == 3)
			{
				gInterface.DrawFormat(eGold, MainCenter - (sizeof(this->rankname) / 2) + 30, StartY + 120, 52, 1, "Loading ....");
				this->RankLoad = 4;
			}
			else if (this->RankLoad == 4)
			{
				gInterface.DrawFormat(eGold, MainCenter - (sizeof(this->rankname) / 2) + 30, StartY + 120, 52, 1, "Loading .....");
				this->RankLoad = 0;
			}
			else
			{
				gInterface.DrawFormat(eGold, MainCenter - (sizeof(this->rankname) / 2) + 30, StartY + 120, 52, 1, "Loading .");
				this->RankLoad = 1;
			}
		}
	}
}

bool CCustomRanking::EventRankingNext(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eNextEvent].EventTick);
	DWORD Delay2 = (CurrentTick - gInterface.Data[ePrevEvent].EventTick);

	if (!gInterface.Data[eRankPANEL_MAIN].OnShow || NextRanking == -1)
	{
		return false;
	}

	if (!gInterface.IsWorkZone(eNextEvent))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eNextEvent].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}

	if (Delay < 200 || Delay2 < 200)
	{
		return false;
	}

	this->ClearCustomRanking();

	gInterface.Data[eNextEvent].OnClick = false;
	pSetCursorFocus = false;

	gInterface.Data[eNextEvent].EventTick = GetTickCount();

	PMSG_CUSTOM_RANKING_SEND pMsg;

	pMsg.header.set(0xF3, 0xE6, sizeof(pMsg));

	RankingType++;
	pMsg.type = RankingType;

	DataSend((BYTE*)&pMsg, pMsg.header.size);

	return true;
}

bool CCustomRanking::EventRankingBack(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eNextEvent].EventTick);
	DWORD Delay2 = (CurrentTick - gInterface.Data[ePrevEvent].EventTick);

	if (!gInterface.Data[eRankPANEL_MAIN].OnShow || PrevRanking == -1)
	{
		return false;
	}

	if (!gInterface.IsWorkZone(ePrevEvent))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[ePrevEvent].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}

	if (Delay < 200 || Delay2 < 200)
	{
		return false;
	}

	this->ClearCustomRanking();

	gInterface.Data[ePrevEvent].OnClick = false;
	pSetCursorFocus = false;

	gInterface.Data[ePrevEvent].EventTick = GetTickCount();

	PMSG_CUSTOM_RANKING_SEND pMsg;

	pMsg.header.set(0xF3, 0xE6, sizeof(pMsg));

	RankingType--;
	pMsg.type = RankingType;

	DataSend((BYTE*)&pMsg, pMsg.header.size);
	return true;
}

bool CCustomRanking::EventRankingWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eRanking_CLOSE].EventTick);
	if (!gInterface.Data[eRankPANEL_MAIN].OnShow || !gInterface.IsWorkZone(eRanking_CLOSE))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eRanking_CLOSE].OnClick = true;
		return true;
	}
	gInterface.Data[eRanking_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	gInterface.Data[eRanking_CLOSE].EventTick = GetTickCount();
	this->CloseTestWindow();
	return false;
}

void CCustomRanking::OpenWindow()
{
	if ((GetTickCount() - gInterface.Data[eRankPANEL_MAIN].EventTick) < 1500)
	{
		return;
	}

	gInterface.Data[eRankPANEL_MAIN].EventTick = GetTickCount();

	if (gInterface.Data[eRankPANEL_MAIN].OnShow == true)
	{
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;
		return;
	}

	gInterface.CloseCustomWindow();

	this->ClearCustomRanking();

	this->RankingCount = 0;

	this->SelectBarRankingNumber = 0;

	PMSG_CUSTOM_RANKING_COUNT_SEND pMsg1;

	pMsg1.header.set(0xF3, 0xE7, sizeof(pMsg1));

	DataSend((BYTE*)&pMsg1, pMsg1.header.size);

	PMSG_CUSTOM_RANKING_SEND pMsg;

	pMsg.header.set(0xF3, 0xE6, sizeof(pMsg));

	this->RankingType = 0;

	pMsg.type = 0;

	DataSend((BYTE*)&pMsg, pMsg.header.size);

	gInterface.Data[eRankPANEL_MAIN].OnShow = true;
}

bool CCustomRanking::EventVipWindow_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eRanking_CLOSE].EventTick);
	if (!gInterface.Data[eRankPANEL_MAIN].OnShow || !gInterface.IsWorkZone(eRanking_CLOSE))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eRanking_CLOSE].OnClick = true;
		return true;
	}
	gInterface.Data[eRanking_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	gInterface.Data[eRanking_CLOSE].EventTick = GetTickCount();
	this->CloseTestWindow();
	return false;
}