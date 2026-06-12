#include "stdafx.h"
#include "Util.h"
#include "Offset.h"
#include "Import.h"
#include "Interface.h"
#include "Defines.h"
#include "Protocol.h"
#include "Common.h"
#include "SocketManager.h"
#include "Protect.h"
#include "InterfaceMacroUI.h"
#include "CustomInterface.h"
#include "NewUISystem.h"
#include "NpcRuud.h"

JCMacroUIEx JCExMacro;
DWORD BUTTON_DELAY;

JCMacroUIEx::JCMacroUIEx()
{
	this->OpenLayer = 0;
	this->EvtKeyState = 0;
}

JCMacroUIEx::~JCMacroUIEx()
{
}

void JCMacroUIEx::ReqServerInfo(WORD subcode)
{
	PMSG_SERVER_INFO_RECV pMsg;
	pMsg.header.set(0xF4, 0x03, sizeof(pMsg));
	pMsg.ServerCode = subcode;
	JCSocketConnect.DataSend((BYTE*)& pMsg, pMsg.header.size);
}

void JCMacroUIEx::ReqServerList()
{
	PMSG_SERVER_LIST_RECV pMsg;
	pMsg.header.set(0xF4, 0x06, sizeof(pMsg));
	JCSocketConnect.DataSend((BYTE*)& pMsg, pMsg.header.size);
}

void JCMacroUIEx::ServerInfoRecv(BYTE* lpMsg, bool a2)
{
	PMSG_SERVER_INFO_SEND* Data = (PMSG_SERVER_INFO_SEND*)lpMsg;
}

void JCMacroUIEx::ServerListRecv(BYTE* lpMsg, bool a2)
{
	PMSG_SERVER_LIST_SEND* Data = (PMSG_SERVER_LIST_SEND*)lpMsg;

	this->Server_List_num = MAKE_NUMBERW(Data->count[0], Data->count[1]);

	for (char i = 0; i < this->Server_List_num; i++)
	{
		this->m_ServerList[i].ServerCode = lpMsg[7 + 4 * i];
		this->m_ServerList[i].type = lpMsg[10 + 4 * i];
		this->m_ServerList[i].UserTotal = lpMsg[9 + 4 * i];
	}
}

void JCMacroUIEx::GJMapServerMoveSend(WORD subcode)
{
	if (*(DWORD*)0x0986C128 == subcode + 1)
	{
		return;
	}
	else
	{
		*(DWORD*)0x0986C128 = subcode + 1;
	}

	JCCG_MOVESERVER_REQ pMsg;

	pMsg.header.set(0xBF, 0xFE, sizeof(pMsg));
	pMsg.subcode = subcode;

	JCExMacro.OpenLayer = !JCExMacro.OpenLayer;

	DataSend((BYTE*)& pMsg, pMsg.header.size);
}

LPCTSTR GetSrvname(int num)
{
	char* SubSrvname[] = { "[Gold]", "[Gold(PvP)]", "[NoN-PvP]", "[Normal]", "[Unknow]" };
	int SrvType;

	if (JCExMacro.m_ServerList[num].ServerCode >= 0 && JCExMacro.m_ServerList[num].ServerCode <= 3)
	{
		SrvType = 0;
	}
	else if (JCExMacro.m_ServerList[num].ServerCode == 4)
	{
		SrvType = 1;
	}
	else if (JCExMacro.m_ServerList[num].ServerCode >= 5 && JCExMacro.m_ServerList[num].ServerCode <= 8)
	{
		SrvType = 2;
	}
	else if (JCExMacro.m_ServerList[num].ServerCode >= 9 && JCExMacro.m_ServerList[num].ServerCode <= 20)
	{
		SrvType = 3;
	}
	else
	{
		SrvType = 4;
	}

	return SubSrvname[SrvType];
}

void JCSetLocationTable(int x, int y)
{
	char JCUserTotla[254];
	ZeroMemory(JCUserTotla, sizeof(JCUserTotla));
	//-- Table
	//RenderBitmap(71554, x, y, 120, 138.75, 0.0, 0.0, 0.1899999976, 0.8930000067, 1, 1, 0.0);
	pSetBlend(1);
	glColor4f(0.0, 0.0, 0.0, 0.79999998);
	pDrawBarForm(x + 3, y, 120.0f, JCExMacro.Server_List_num * 16, 0, 0);
	pGLSwitchBlend();
	pGLSwitch();
	EnableAlphaTest(1);
	glColor3f(1.0, 1.0, 1.0);


	for (char i = 0; i < JCExMacro.Server_List_num; i++)
	{
		if (pCheckMouseOver((int)x + 2, (int)y + (13 * i) + 3, (int)104, (int)13.5))
		{
			if (*(BYTE*)0x8793386 && GetTickCount() >= JCExMacro.EvtKeyState + 300)
			{
				JCExMacro.GJMapServerMoveSend(JCExMacro.m_ServerList[i].ServerCode);
				JCExMacro.EvtKeyState = GetTickCount();
			}

			pSetBlend(1);
			glColor4f(1.0, 1.0, 1.0, 0.3);
			pDrawBarForm(x + 5, y + (13 * i) + 3, 116.0f, 13.0f, 0, 0);
			pGLSwitchBlend();
			pGLSwitch();
			EnableAlphaTest(1);
			glColor3f(1.0, 1.0, 1.0);
			//	RenderBitmap(71554, x + 2, y + ( 13 * i ) + 3, 104, 13.5, 
				//	(( JCExMacro.m_ServerList[ i ].UserTotal < 100 ) ? ((*(DWORD*)0x0986C128 == JCExMacro.m_ServerList[ i ].ServerCode + 1 ) ? 0.5394999981 : 0.3750000298 ): 0.5394999981),
				//	0.1660000086, 0.1637999117, 0.09200000018, 1, 1, 0.0);
		}

		pSetFont(pTextThis(), (int)pFontNormal);
		pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
		//--
		pSetTextColor(pTextThis(), 35, 194, 29, 255);
		wsprintf(JCUserTotla, "CH %d:", JCExMacro.m_ServerList[i].ServerCode + 1);
		pDrawText(pTextThis(), x + 8, y + (13 * i) + 5, JCUserTotla, 0, 0, (LPINT)1, 0);
		//--
		pSetTextColor(pTextThis(), 200, 200, 200, 255);
		pDrawText(pTextThis(), x + 37, y + (13 * i) + 5, GetSrvname(i), 0, 0, (LPINT)1, 0);

		ZeroMemory(JCUserTotla, sizeof(JCUserTotla));
		if (JCExMacro.m_ServerList[i].UserTotal < 100)
		{
			pSetTextColor(pTextThis(), 35, 194, 29, 255);
			wsprintf(JCUserTotla, "%d%%", JCExMacro.m_ServerList[i].UserTotal);
		}
		else
		{
			pSetTextColor(pTextThis(), 255, 20, 20, 255);
			wsprintf(JCUserTotla, "Full");
		}

		pDrawText(pTextThis(), x + 2, y + (13 * i) + 5, JCUserTotla, 104, 0, (LPINT)4, 0);
	}
}

void BottonConfig(DWORD model, float X, float Y, float W, float H)
{
	int v11; // [sp+0h] [bp-B8h]@1
	float v14; // ST1C_4@1
	float v15; // ST18_4@1

	v11 = *(DWORD*)(GetInstance() + 152);

	ChangeButtonInfo2((char*)(v11 + 36), (int)X, (int)Y, (int)W, (int)H);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)H))
		{
			if (*(BYTE*)0x8793386)
			{
				v14 = 0.0;
				v15 = 0.451f;
			}
			else
			{
				v14 = 0.0;
				v15 = 0.2255f;
				pDrawToolTip(X, Y + 35, pGetTextLine(pTextLineThis, 3561));
			}
		}
		else
		{
			v14 = 0.0;
			v15 = 0.0;
		}

		pDrawPuntero(v11 + 36, 1, 51522, 0, 0, 0);
		RenderBitmap(model, X, Y, W, H, v14, v15, 0.878, 0.225, 1, 1, 0.0);
	}
	else
	{
		sub_7798F0(v11 + 36, 0);
	}
}

void BottonStart(DWORD model1, DWORD model2, float X, float Y, float W, float H)
{
	int v11; // [sp+0h] [bp-B8h]@1
	float v14; // ST1C_4@1
	float v15; // ST18_4@1
	DWORD model;

	v11 = *(DWORD*)(GetInstance() + 152);

	ChangeButtonInfo2((char*)(v11 + 208), (int)X, (int)Y, (int)W, (int)H);
	ChangeButtonInfo2((char*)(v11 + 380), (int)X, (int)Y, (int)W, (int)H);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (!*(BYTE*)(*(DWORD*)0xE8CB7C + 8))
		{
			model = model1;

			//-- Boton Play
			if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)H))
			{
				if (*(BYTE*)0x8793386)
				{
					v14 = 0.0;
					v15 = 0.451f;
				}
				else
				{
					v14 = 0.0;
					v15 = 0.2255f;
					pDrawToolTip(X, Y + 35, pGetTextLine(pTextLineThis, 3562));
				}
			}
			else
			{
				v14 = 0.0;
				v15 = 0.0;
			}
		}
		else
		{
			model = model2;

			//if(offhelper == 1)
			//{
			//	gMuHelper.RunningOffHelper();
			//}

			if (pCheckMouseOver((int)X, (int)Y, (int)W, (int)H))
			{
				if (*(BYTE*)0x8793386)
				{
					v14 = 0.0;
					v15 = 0.451f;
				}
				else
				{
					v14 = 0.0;
					v15 = 0.2255f;
					pDrawToolTip(X, Y + 35, pGetTextLine(pTextLineThis, 3563));
				}
			}
			else
			{
				v14 = 0.0;
				v15 = 0.0;
			}
		}

		pDrawPuntero(v11 + 208, 1, 51522, 0, 0, 0);
		pDrawPuntero(v11 + 380, 1, 51522, 0, 0, 0);
		RenderBitmap(model, X, Y, W, H, v14, v15, 0.878, 0.225, 1, 1, 0.0);
	}
	else
	{
		if (!*(BYTE*)(*(DWORD*)0xE8CB7C + 8))
		{
			sub_7798F0(v11 + 208, 0);
		}
		else
		{
			//if(offhelper == 1)
			//{
			//	gMuHelper.RunningOffHelper();
			//}

			sub_7798F0(v11 + 380, 0);
		}
	}
}

DWORD EvkMenu;

void JCMacroUIEx::JCFrameBar(int a1)
{
	if (gInterface.CheckWindow(ObjWindow::MoveList) 
		|| gInterface.CheckWindow(ObjWindow::CashShop) 
		|| gInterface.CheckWindow(ObjWindow::SkillTree) 
		|| gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)
		|| gInterface.CheckWindow(ObjWindow::FullMap))
	{
		return;
	}

	char Cord[256]; // [sp+31h] [bp-FFh]@1
	float y; // ST1C_4@1
	float x; // ST18_4@1
	int JCMacroHelper; // [sp+2Ch] [bp-104h]@1
	float RenderX;
	JCMacroHelper = *(DWORD*)(GetInstance() + 152);

	y = (double) * (signed int*)(JCMacroHelper + 24);
	x = (double) * (signed int*)(JCMacroHelper + 20);

	float X = (double) * ((DWORD*)a1 + 5);
	float Y = (double) * ((signed int*)a1 + 6);

	float renderMenu = 15.0f;

	renderMenu = 50.0f;

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(51550, X + 85.0 + renderMenu, Y, 122.0, 24.0, 0.0, 0.285, 0.724, 0.27, 1, 1, 0.0);
		RenderBitmap(51550, X, Y, 164.0, 24.0, 0.0, 0.0, 0.725, 0.28, 1, 1, 0.0);
	}
	else
	{
		pDrawGUI(31602, X, Y, 22.0, 25.0);

		for (int i = 0; i < 6; i++)
		{
			RenderX = (double)X + 22.0 + (i * 26.0);
			pDrawGUI(31603, RenderX, Y, 26.0, 25.0);
		}

		pDrawGUI(31604, RenderX, Y, 73.0, 20.0);
		gInterface.DrawGUI(eMenuBG, RenderX + 56, Y);
		//RenderImage(31604, RenderX +80, Y, 50, 20.0);
		/*pDrawGUI(31602, x, y, 22.0, 25.0);

		RenderBitMapColored(31603,
			(double)(*(DWORD*)(JCMacroHelper + 20) + 22),
			(double) * (signed int*)(JCMacroHelper + 24),
			(double) * (signed int*)(JCMacroHelper + 12),
			25.0, 0.1, 0.0, 0.69999999, 0.78125,
			pMakeColor(0xFFu, 0xFFu, 0xFFu, 0xFFu));

		pDrawGUI(31604, (double)(*(DWORD*)(JCMacroHelper + 20) + *(DWORD*)(JCMacroHelper + 12) + 22),
			(double) * (signed int*)(JCMacroHelper + 24), 73.0, 20.0);*/

	}

	if (pCheckMouseOver((int)x +17, (int)y+0, (int)35, (int)22))
	{
		if (*(BYTE*)0x8793386 && GetTickCount() >= BUTTON_DELAY + 300)
		{
			if (JCExMacro.OpenLayer == 1)
			{
				JCExMacro.OpenLayer = 0;
			}
			else
			{
				JCExMacro.OpenLayer = 1;
			}

			if (JCExMacro.OpenLayer != 0)
			{
				JCExMacro.ReqServerList();
			}
			BUTTON_DELAY = GetTickCount();
		}

		//	RenderBitmap(31460, x + 17.0, y + 3, 10, 10, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);

		/*	RenderBitmap(71554, x + 10.0, y, 35.625, 24.0,
			( JCExMacro.OpenLayer != 0 ) ? 0.3090001385 : 0.7610001564,
			( JCExMacro.OpenLayer != 0 ) ? 0.2740000784 : 0.153000012, 0.05700046197, 0.1315008551, 1, 1, 0.0);*/
	}
	else
	{
		//	RenderBitmap(31460, x + 17.0, y + 3, 10, 10, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);

			//-- Si esta abierto
		/*	RenderBitmap(71554, x + 10.0, y, 35.625, 24.0,
				( JCExMacro.OpenLayer != 0 ) ? 0.3090001385 : 0.7610001564,
				( JCExMacro.OpenLayer != 0 ) ? 0.2740000784 : 0.153000012, 0.05700046197, 0.1315008551, 1, 1, 0.0);*/
	}

	if (JCExMacro.OpenLayer != 0)
	{
		JCSetLocationTable(x+8, y+22);
	}

	pSetFont(pTextThis(), (int)pFontBold);
	pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
	pSetTextColor(pTextThis(), 240, 240, 240, 255);

	ZeroMemory(Cord, sizeof(Cord));
	wsprintf(Cord, "CH %d", *(DWORD*)0x0986C128);
	pDrawText(pTextThis(), (int)x + 10, (int)y + 4, Cord, 35.625, 0, (LPINT)3, 0);

	pSetFont(pTextThis(), (int)pFontNormal);

	ZeroMemory(Cord, sizeof(Cord));

	if (World >= 82 && World <= 100)
	{
		wsprintf(Cord, "%s  %d,%d", pGetTextLine(pTextLineThis, (3810 + World - 82)), pGetUserCoorX, pGetUserCoorY);
	}
	else
	{
		wsprintf(Cord, "%s  %d,%d", pGetMapName(World), pGetUserCoorX, pGetUserCoorY);
	}
	
	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		pDrawText(pTextThis(), (int)x - 15, (int)y + 4, Cord, 190, 0, (LPINT)3, 0);
	}
	else
	{
		pDrawText(pTextThis(), (int)x - 0, (int)y + 4, Cord, 190, 0, (LPINT)3, 0);
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		//Extra
		DWORD Color = Color4f(255, 189, 25, 255);
		if (!*(BYTE*)(*(DWORD*)(MUHELPER_STRUC)+0x08))
		{
			gInterface.DrawFormat(Color, X + 153.5 + renderMenu, Y + 2, 27.5, 3, "0");
		}
		else
		{
			gInterface.DrawFormat(Color, X + 153.5 + renderMenu, Y + 2, 27.5, 3, "1");
		}

		//-- Boton Config
		BottonConfig(51546, X + 119 + renderMenu, y + 7.0, 19.0, 19.0);

		//-- Boton start
		BottonStart(51547, 51548, X + 138 + renderMenu, y + 7.0, 19.0, 19.0);

		//gInterface.DrawButtonIcon(Color, 120111, X + 100 + renderMenu, y + 7.0, 19.0, 19.0, "Menu");

	}
	else
	{
		//-- Boton Config
		BottonConfig(31761, 171.5,*(DWORD*)(JCMacroHelper + 24), 18, 13);

		//-- Boton start
		BottonStart(31762, 31763, 171.5+18,*(DWORD*)(JCMacroHelper + 24), 18, 13);
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

/*void OffHelper(DWORD id, float x, float y, float w, float h)
{
	pDrawGUI(id, x, y, w, h);

	if( gInterface.IsWorkZone(ButtonStartAttack) )
	{
		if( gInterface.Data[ButtonStartAttack].OnClick )
		{
			if(offhelper == 0)
			{
				offhelper = 1;
			}
			else
			{
				offhelper = 0;
			}
			gInterface.Data[ButtonStartAttack].OnClick = false;
		}
	}
	if(offhelper == 1)
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 0);
	}
	else
	{
		gInterface.DrawButtonRender(ButtonStartAttack, x + 50, y + 8, 0, 15);
	}
	gInterface.DrawFormat(eGold, x + 50 + 16, y + 12, 60, 1, "MuOffHelper");
}*/

char BarTime(int This)
{
	float v1; // ST10_4@2
	float v2; // ST0C_4@2
	float v3; // ST30_4@3
	float v4; // ST08_4@3
	float v5; // ST04_4@3
	int v13; // [sp+30h] [bp-4h]@1

	v13 = This;

	if (*(BYTE*)(v13 + 72) == 1)
	{
		v1 = (double) * (signed int*)(This + 20);
		v2 = (double) * (signed int*)(This + 16);
		RenderImage2(51522, v5, v4);

		if (*(DWORD*)(v13 + 88) == 1)
		{
			v3 = *(float*)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD*)(v13 + 20) + 2);
			v5 = (double)(*(DWORD*)(v13 + 16) + 2);
			pDrawGUI(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
		else if (*(DWORD*)(v13 + 88) > 1)
		{
			RenderImage2(51522, v5, v4);
			v3 = *(float*)(v13 + 92) * 50.0;
			v4 = (double)(*(DWORD*)(v13 + 20) + 2);
			v5 = (double)(*(DWORD*)(v13 + 16) + 2);
			pDrawGUI(51549, v5 + 108.0, v4 - 16.0, v3, 3.0);
		}
	}

	return 1;
}

signed int JCGetMoveMapWidth()
{
	signed int v52; // [sp+0h] [bp-4h]@11

	v52 = CGetScreenWidth2();

	return (int)(pWinWidth / pWinHeightReal) - (640 - v52);
}



int CalDistance(int x, int y, int x1, int y1)
{
	if (x == x1 && y == y1)
	{
		return 0;
	}

	float tx = x - x1;
	float ty = y - y1;

	return sqrt(tx * tx + ty * ty);
}

LPCTSTR GetnameMap()
{
	if (World >= 82 && World <= 100)
	{
		return  pGetTextLine(pTextLineThis, (3810 + World - 82));
	}
	else
	{
		return pGetMapName(World);
	}
}


int JCMacroUIEx::CameraGuiReset()
{
	int v49; // eax@55
	signed int v52; // [sp+0h] [bp-4h]@11

	pSetCursorFocus = false;

	if (pCheckWindow(pWindowThis(), 13) && pCheckWindow(pWindowThis(), 16) //-- 13 & 16
		|| pCheckWindow(pWindowThis(), 8) //-- 8
		|| pCheckWindow(pWindowThis(), 12) //-- 12
		|| pCheckWindow(pWindowThis(), 9) //-- 9
		|| pCheckWindow(pWindowThis(), 7) //-- 7
		|| pCheckWindow(pWindowThis(), 14) //-- 14
		|| pCheckWindow(pWindowThis(), 15) //-- 15
		|| pCheckWindow(pWindowThis(), 60) //-- 60
		|| pCheckWindow(pWindowThis(), 76)) //-- 76
	{
#if(WIDE_SCREEN)
		v52 = 190 + 190;
#else
		v52 = 260;
#endif
	}
	else
	{
		if (pCheckWindow(pWindowThis(), 16)
			&& pCheckWindow(pWindowThis(), 4)
			|| pCheckWindow(pWindowThis(), 69))
		{
#if(WIDE_SCREEN)
			v52 = 190 + 190;
#else
			v52 = 260;
#endif
		}
		else
		{
			if (pCheckWindow(pWindowThis(), 16) && pCheckWindow(pWindowThis(), 11))
			{
#if(WIDE_SCREEN)
				v52 = 190 + 190;
#else
				v52 = 260;
#endif
			}
			else
			{
				if (pCheckWindow(pWindowThis(), 27))
				{
#if(WIDE_SCREEN)
					v52 = 190 + 190;
#else
					v52 = 260;
#endif
				}
				else
				{
					if (pCheckWindow(pWindowThis(), 13)
						|| (pCheckWindow(pWindowThis(), 16))
						|| (pCheckWindow(pWindowThis(), 3))
						|| (pCheckWindow(pWindowThis(), 21))
						|| (pCheckWindow(pWindowThis(), 6))
						|| (pCheckWindow(pWindowThis(), 22))
						|| (pCheckWindow(pWindowThis(), 23))
						|| (pCheckWindow(pWindowThis(), 24))
						|| (pCheckWindow(pWindowThis(), 4))
						|| (pCheckWindow(pWindowThis(), 18))
						|| (pCheckWindow(pWindowThis(), 10))
						|| (pCheckWindow(pWindowThis(), 5))
						|| (pCheckWindow(pWindowThis(), 25))
						|| (pCheckWindow(pWindowThis(), 26))
						|| (pCheckWindow(pWindowThis(), 19))
						|| (pCheckWindow(pWindowThis(), 20))
						|| (pCheckWindow(pWindowThis(), 58))
						|| (pCheckWindow(pWindowThis(), 59))
						|| (pCheckWindow(pWindowThis(), 62))
						|| (pCheckWindow(pWindowThis(), 73))
						|| (pCheckWindow(pWindowThis(), 68))
						|| (pCheckWindow(pWindowThis(), 69))
						|| (pCheckWindow(pWindowThis(), 70))
						|| (pCheckWindow(pWindowThis(), 66))
						|| (pCheckWindow(pWindowThis(), 75))
						|| (pCheckWindow(pWindowThis(), 74)))
					{
#if(WIDE_SCREEN)
						v52 = 190;
#else
						v52 = 450;
#endif
					}
					else
					{
						if (pCheckWindow(pWindowThis(), 79))
						{
#if(WIDE_SCREEN)

							if (pCheckWindow(pWindowThis(), 80))
								v52 = 190 + 190;
							else
								v52 = 190;
#else

							if (pCheckWindow(pWindowThis(), 80))
								v52 = 260;
							else
								v52 = 450;
#endif
						}
						else
						{
#if(WIDE_SCREEN)
							v52 = 0;
#else
							v52 = 640;
#endif
						}
					}
				}
			}
		}
	}
	if (pCheckWindow(pWindowThis(), 77))
	{
#if(WIDE_SCREEN)
		v49 = sub_861A60((int)pWindowThis());
		if (sub_7D6270(v49, 0))
			v52 = 190 + 190 + 190;
		else
			v52 = 190 + 190;
#else
		v49 = sub_861A60((int)pWindowThis());
		if (sub_7D6270(v49, 0))
			v52 = 70;
		else
			v52 = 260;
#endif
	}
	else
	{
		if (pCheckWindow(pWindowThis(), 78))
#if(WIDE_SCREEN)
			v52 = 190 + 190 + 190;
		//pSetCursorFocus = true;
#else
			v52 = 70;

#endif
	}

	int Width = TransForX(190);

	if (jCRenderRuud.OpeningRuud && pCheckWindow(pWindowThis(), 13))
	{
		if (pCheckMouseOver(1, 0, Return2X(Width), 429))
		{
			pSetCursorFocus = true;
		}
	}

	if (jCRenderRuud.OpeningRuud && jCRenderRuud.OpenWindowConfirm && pCheckWindow(pWindowThis(), 13))
	{
		pSetCursorFocus = true;
	}

#if(WIDE_SCREEN)
	return MAX_WIN_WIDTH - v52;

#else
	return v52;
#endif
}

void JCMacroUIEx::Load()
{
	//SetCompleteHook(0xE8, 0x007F76CD, &OffHelper);

	//--
	//-- Muhelper + MoverServer

	SetCompleteHook(0xE9, 0x007D2BC0, this->JCFrameBar);
	
	//SetCompleteHook(0xE9, 0x0080B8E0, &BarTime);
	
}