#include "stdafx.h"
#include "MiniMapBrujula.h"
#include "Import.h"
#include "Util.h"
#include "Offset.h"
#include "User.h"
#include "Interface.h"
#include "Defines.h"
#include "Common.h"
#include "MiniMapInfo.h"
#include "InterfaceS8AdvancedUI.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "InterfaceMacroUI.h"
#include "CustomFont.h"
#include "CameraMove.h"
#include "Camera.h"
#include "OptionPanel.h"

CMinimapB gRenderMapB;

#define MouseX										*(int*)0x879340C
#define MouseY										*(int*)0x8793410

POINT MaxPosition;
POINT CurPosition;
bool  DragItem;
DWORD ActionTime;

CMinimapB::CMinimapB()
{
	this->DataMap.ModelID = -1;
	this->DataMap.XSW_Minimap_Frame = 486;  //-- Minimap_FrameX
	this->DataMap.YSW_Minimap_Frame = 234;  //-- Minimap_FrameY
	this->DataMap.XSW_Minimap = 510; //-- MiniMapX
	this->DataMap.YSW_Minimap = 265; //265; //-- MiniMapY
	this->DataMap.XSW_Time_Frame = 506; //-- Time_FrameX
	this->DataMap.YSW_Time_Frame = 392; //-- Time_FrameY
	this->DataMap.This_92 = 0;
	this->DataMap.This_96 = 0;
	this->DataMap.DropMoveUserX = 0; //-- DropMoveUserX
	this->DataMap.DropMoveUserY = 0; //-- DropMoveUserY
	this->DataMap.This_108;
	this->DataMap.This_112;
	this->DataMap.CurrentMoveX = 0.0; //-- CurrentMoveX
	this->DataMap.CurrentMoveY = 0.0; //-- CurrentMoveY
	this->DataMap.Scale = 1; //-- Scale
	this->DataMap.TimerEventVK = 0; //-- Scale
	this->DataMap.Alpha = 1.0f; //-- Alpha
	this->Moving = false;
	this->ultimoX = 510;
	this->ultimoY = 265;

	MaxPosition.x = (double)gRenderMapB.DataMap.XSW_Minimap +500;
	MaxPosition.y = 800;
	CurPosition.x = MouseX;
	CurPosition.y = MouseY;
	DragItem = false;
}

CMinimapB::~CMinimapB()
{
}

void DataMapLoadB()
{
	int v4; // [sp+Ch] [bp-Ch]@5
	int v5; // [sp+10h] [bp-8h]@2
	int Type;
	int Multiplicador;
	int Scalado;

	Type = gRenderMapB.DataMap.Scale;
	Multiplicador = (( Type == 1 ) ? 1 : Type - 1 );
	Scalado = (( Type == 1 ) ? 512 : 128 );
	int JCResto;
	int JCResto2;
	#if(WIDE_SCREEN == 2)
	JCResto =  pWinWidth / pWinHeightReal  / 2-320;
	JCResto2 =  pWinWidth / pWinHeightReal-640;
#else
	JCResto = 0;
	JCResto2 =0;
#endif
	
	//gRenderMap.DataMap.XSW_Minimap = JCResto+510;
	//gRenderMap.DataMap.YSW_Minimap = 265;

	gRenderMapB.DataMap.This_92 = *(DWORD *)(*(DWORD *)0x7BC4F04 + 172) / ((Type == 1) ? 0.5 : Type - 1 ); //-- X
	gRenderMapB.DataMap.This_96 = (256 - *(DWORD *)(*(DWORD *)0x7BC4F04 + 176)) / ((Type == 1) ? 0.5 :  Type - 1  ); //-- Y

	//-- X
	if ( gRenderMapB.DataMap.This_92 - ( Multiplicador << 6 ) <= 0 )
		v5 = 0;
	else
		v5 = gRenderMapB.DataMap.This_92 - ( Multiplicador << 6 );

	gRenderMapB.DataMap.This_108 = ( v5 >= Scalado ) ? Scalado : (v5 <= 0) ? 0: gRenderMapB.DataMap.This_92 - ( Multiplicador << 6 );

	//-- Y
	if ( gRenderMapB.DataMap.This_96 - ( Multiplicador << 6 ) <= 0 )
		v4 = 0;
	else
		v4 = gRenderMapB.DataMap.This_96 - ( Multiplicador << 6 );

	gRenderMapB.DataMap.This_112 = ( v4 >= Scalado ) ? Scalado : (v4 <= 0) ? 0: gRenderMapB.DataMap.This_96 - ( Multiplicador << 6 );

	gRenderMapB.DataMap.DropMoveUserX = JCResto+gRenderMapB.ultimoX + gRenderMapB.DataMap.This_92 - gRenderMapB.DataMap.This_108; //Minimapa abajo
	gRenderMapB.DataMap.DropMoveUserY = gRenderMapB.ultimoY + gRenderMapB.DataMap.This_96 - gRenderMapB.DataMap.This_112; //Minimapa abajo
	gRenderMapB.DataMap.CurrentMoveX = (double)gRenderMapB.DataMap.This_108 / ((double) ((Type == 1) ? 512.0 : 256.0 ) / (double)Multiplicador );
	gRenderMapB.DataMap.CurrentMoveY = (double)gRenderMapB.DataMap.This_112 / ((double) ((Type == 1) ? 512.0 : 256.0 ) / (double)Multiplicador );
}

void DataViewPortMapLoad()
{
	int Model;
	int Type;
	float XNPC, YNPC;
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;
	Type = gRenderMapB.DataMap.Scale;

	float InitialX = gRenderMapB.DataMap.XSW_Minimap;
	float InitialY = gRenderMapB.DataMap.YSW_Minimap;
	float This_108 = gRenderMapB.DataMap.This_108;
	float This_112 = gRenderMapB.DataMap.This_112;

	int BaseOffsetX = 0;
	if (InitialX < 0)
		BaseOffsetX = -InitialX;

	for (int i = 0; i < 400; ++i)
	{
		Model = pGetPreviewStruct(pPreviewThis(), i);
		if (Model &&
			*(BYTE*)(Model + 780) &&
			Model != *(DWORD*)0x7BC4F04 &&
			(*(BYTE*)(Model + 800) == 1 || *(BYTE*)(Model + 800) == 2 || *(BYTE*)(Model + 800) == 4))
		{
			float offsetX = *(DWORD*)(Model + 172) / ((Type == 1) ? 0.5f : (float)(Type - 1));
			float offsetY = (256 - *(DWORD*)(Model + 176)) / ((Type == 1) ? 0.5f : (float)(Type - 1));

			XNPC = BaseOffsetX + JCResto + InitialX + offsetX - This_108 - 5;
			YNPC = InitialY + offsetY - This_112 - 5;

			RenderBitMapColored(31471, XNPC, YNPC, 7.0f, 7.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));

			if (*(WORD*)(Model + 132) == 249 || *(WORD*)(Model + 132) == 247 || *(WORD*)(Model + 132) == 241)
			{
				RenderBitMapColored(31472, XNPC, YNPC, 7.0f, 7.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(0, 0, 255, 255));
			}
			else if (*(BYTE*)(Model + 800) == 4 && *(WORD*)(Model + 132) != 249)
			{
				switch (*(WORD*)(Model + 132))
				{
				case 251:
					RenderBitMapColored(31466, XNPC, YNPC, 10.0f, 10.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));
					break;
				case 255:
				case 253:
					RenderBitMapColored(31467, XNPC, YNPC, 10.0f, 10.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));
					break;
				case 240:
					RenderBitMapColored(31468, XNPC, YNPC, 10.0f, 10.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));
					break;
				case 229:
				case 233:
				case 235:
				case 237:
					RenderBitMapColored(31469, XNPC, YNPC, 10.0f, 10.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));
					break;
				default:
					RenderBitMapColored(32452, XNPC, YNPC, 10.0f, 10.0f, 0.0f, 0.0f, 0.546875f, 0.546875f, pMakeColor(255, 255, 255, 255));
					break;
				}
			}
		}
	}
}

void Interface::DrawMiniMap()
{
	if(gRenderMapB.DataMap.ModelID == -1)
	{
		return;
	}

	if (this->MiniMapCheck() || this->CheckMap() 
		|| !MiniMap || this->CheckWindow(FullMap) 
		|| this->CheckWindow(FriendList) || gInterface.CheckWindow(SkillTree) 
		|| gInterface.CheckWindow(CashShop) || gInterface.CheckWindow(FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options))
	{
		return;
	}

	float DIRPointer;
	lpViewObj ObjectPointer;
	char Cord[256];
	float v8; // ST34_4@1
	float v9; // ST30_4@1
	float v10; // ST08_4@1
	float v11; // ST04_4@1
	int Type;
	int Multiplicador;
	int Scalado;

	ObjectPointer = &*(ObjectPreview*)(*(DWORD *)0x7BC4F04);
	DIRPointer =  180 + ( 45 * abs((signed int)(ObjectPointer->m_Model.WorldPos.Z / 45.0)));

	Type = gRenderMapB.DataMap.Scale;

	DataMapLoadB(); //mover a los lados

	int JCResto;
	int JCResto2;
	#if(WIDE_SCREEN == 2)
	JCResto =  pWinWidth / pWinHeightReal/ 2-320;
	JCResto2 =  pWinWidth / pWinHeightReal-640;
	
#else
	JCResto = 0;
	JCResto2 =0;
#endif


	v8 = (double) (( Type == 1 ) ? 0.25f : (( Type == 2 ) ? 0.5f : 1.0));
	v9 = (double) (( Type == 1 ) ? 0.25f : (( Type == 2 ) ? 0.5f : 1.0));

	v10 = (double) gRenderMapB.DataMap.YSW_Minimap;
	v11 = (double) gRenderMapB.DataMap.XSW_Minimap;

	int InitialX = v11;
	float InitialY = v10;
	float cursorX = pCursorX >= JCResto+MAX_WIN_WIDTH ? 0 : pCursorX;
	float cursorY = pCursorY >= MAX_WIN_HEIGHT ? 0 : pCursorY;

	if (GetKeyState(VK_RBUTTON) & 0x8000 && GetTickCount() > ActionTime + 100)
	{
		if (gInterface.IsWorkZone(JCResto + MaxPosition.x, MaxPosition.y, 95, 100, true))
		{
			if (!DragItem)
			{
				DragItem = true;
				CurPosition.x = MouseX;
				CurPosition.y = MouseY;
			}
		}
		if (DragItem)
		{
			MaxPosition.x += MouseX - CurPosition.x;
			MaxPosition.y += MouseY - CurPosition.y;
			CurPosition.x = MouseX;
			CurPosition.y = MouseY;
		}		
	}
	else
	{
		if (DragItem)
		{
			DragItem = false;
		}
	}

	if (MiniMapType == 1)
	{
		switch (pGameResolutionMode)
		{
		case 0:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 410)	  //mover el mapa abajo o arriba
				MaxPosition.y = 410;	  //mover el mapa abajo o arriba
			break;//listo
		case 1:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 410)	//mover el mapa abajo o arriba
				MaxPosition.y = 410;	//mover el mapa abajo o arriba
			break;//listo
		case 2:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 405)
				MaxPosition.y = 405;
			break;//listo
		case 3:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 405)
				MaxPosition.y = 405;
			break;//listo
		case 4:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 510)
				MaxPosition.y = 510;
			break;//listo
		case 5:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 480)
				MaxPosition.y = 480;
			break;//listo
		case 6:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 520)
				MaxPosition.y = 520;
			break;//listo
		case 7:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 490)
				MaxPosition.y = 490;
			break;//listo
		case 8:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < -85)
				MaxPosition.y = -85;
			if (MaxPosition.x > JCResto + 529)
				MaxPosition.x = JCResto + 529;
			if (MaxPosition.y > 500)
				MaxPosition.y = 500;
			break;//listo
		}
	}

	if (MiniMapType == 2)
	{
		switch (pGameResolutionMode)
		{
		case 0:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 300)
				MaxPosition.y = 300;
			break;//listo
		case 1:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 300)
				MaxPosition.y = 300;
			break;//listo
		case 2:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 395)
				MaxPosition.y = 395;
			break;//listo
		case 3:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 395)
				MaxPosition.y = 395;
			break;//listo
		case 4:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 500)
				MaxPosition.y = 500;
			break;//listo
		case 5:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 470)
				MaxPosition.y = 470;
			break;//listo
		case 6:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 510)
				MaxPosition.y = 510;
			break;//listo
		case 7:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < 0)
				MaxPosition.y = 0;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 480)
				MaxPosition.y = 480;
			break;//listo
		case 8:
			if (MaxPosition.x < -JCResto)
				MaxPosition.x = -JCResto;
			if (MaxPosition.y < -85)
				MaxPosition.y = -85;
			if (MaxPosition.x > JCResto + 505)
				MaxPosition.x = JCResto + 505;
			if (MaxPosition.y > 490)
				MaxPosition.y = 490;
			break;//listo
		}
	}

	InitialX = MaxPosition.x;
	InitialY = MaxPosition.y;

	gRenderMapB.ultimoX = InitialX;
	gRenderMapB.ultimoY = InitialY;
	gRenderMapB.DataMap.XSW_Minimap = MaxPosition.x;
	gRenderMapB.DataMap.YSW_Minimap = MaxPosition.y;

	if (MiniMapType == 2)
	{
		float usercurrenty; // ST74_4@3
		float usercurrentx; // ST20_4@12

		usercurrentx = (double)(*(signed int*)(dword_7BC4F04 + 172) + 2.5) / 256.0;
		usercurrenty = (double)(253.5 - *(signed int*)(dword_7BC4F04 + 176)) / 256.0;

		//CustomFont.Draw((HFONT)pFontNormal,100, 100, 0xFFFFFFFF, 0x0, 255, 0, 1, "Debug Pos: %d / %d - MiX: %d/%d", MouseX, MouseY, InitialX, InitialY);

		//GetDrawCircle(550000, x, y, 256, usercurrentx, usercurrenty, 0.5, 1, 1, 0.0);	
		GetDrawCircle(31462, JCResto+InitialX + 14, InitialY + 18, 100,usercurrentx, usercurrenty, v9, 1, 1, gRenderMapB.DataMap.Alpha); //Minimapa abajo
		//RenderBitmap(31462, v11 + 14, v10 + 18, 95, 100, gRenderMap.DataMap.CurrentMoveX, gRenderMap.DataMap.CurrentMoveY, v9, v8, 1, 1, 0.0); //Minimapa abajo
	}

	if (MiniMapType == 1)
	{
		//-- Fondo
		//RenderBitmap(31464, JCResto+InitialX - 1, InitialY + 6, 125, 125, 0.3699999452, 0.0625, 0.5779999495, 0.2889999151, 1, 1, 0.0); //Minimapa abajo
		RenderBitmap(31462, JCResto+InitialX + 14, InitialY + 18, 93, 100, gRenderMapB.DataMap.CurrentMoveX, gRenderMapB.DataMap.CurrentMoveY, v9, v8, 1, 1, gRenderMapB.DataMap.Alpha); //Minimapa abajo
		RenderBitmap(31607, JCResto + InitialX + 11, InitialY + 15, 100, 105, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		//-- Cabezera
		RenderBitmap(31463, JCResto+InitialX + 11, InitialY - 3, 100, 18, 0.3259999454, 0.00249999878, 0.6679999232, 0.04399995133, 1, 1, 0.0); //Minimapa abajo           

		//-- Titulo
		pSetFont(pTextThis(), (int)pFontBold);
		wsprintf(Cord, "%s ( %d , %d )", ((World >= 82 && World <= 120) ? pGetTextLine(pTextLineThis, (3160 + World - 82)) : pMapName(World)), ObjectPointer->MapPosX, ObjectPointer->MapPosY);
		pSetBackgroundTextColor(pTextThis(), 0, 0, 0, 0);
		pSetTextColor(pTextThis(), 240, 240, 240, 255);
		pDrawText(pTextThis(), JCResto + InitialX, InitialY + 1, Cord, 124.0, 0, (LPINT)3, 0); //Minimapa abajo
	}
	sub_637E80( 32450,
	(double)gRenderMapB.DataMap.DropMoveUserX,
	(double)gRenderMapB.DataMap.DropMoveUserY,
	10.0,
	10.0, 
	DIRPointer,
	0.0,
	0.0,
	0.546875,
	0.546875);

	float JCPartyCoordX;
	float JCPartyCoordY;

	for(int i = 0; i < pPartyMemberCount ; i++)
	{
		if( !strcmp(pGetStrutParty( i ).Name, pGetUserName) )
		{
			continue;
		}
		JCPartyCoordX = (double) InitialX + gMiniMap.gPartyInfo[ i ].x / ((Type == 1) ? 0.5 : Type - 1 );
		JCPartyCoordY = (double) InitialY + (256 - gMiniMap.gPartyInfo[ i ].y ) / ((Type == 1) ? 0.5 : Type - 1 );
		
		JCPartyCoordX = JCPartyCoordX - gRenderMapB.DataMap.This_108 - 5;
		JCPartyCoordY = JCPartyCoordY - gRenderMapB.DataMap.This_112 - 5;

		RenderBitMapColored(61520, JCPartyCoordX, JCPartyCoordY, 10.0, 10.0, 0.0, 0.0, 0.546875, 0.546875, pMakeColor(255, 255, 255, gRenderMapB.DataMap.Alpha * 255));
	}

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, gRenderMapB.DataMap.Alpha);

	DataViewPortMapLoad();
	int textAlpha;

	pGLSwitch();
	EnableAlphaTest(0);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	if ( gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
	//-- Carcasa Mapa
	//RenderBitmap(31465, v11 + 0, v10 + 6, 120, 120, 0.01299999747, 0.02999999747, 0.3105553985, 0.6109998822, 1, 1, 0.0); //Minimapa abajo  
	if (MiniMapType == 2)
	{
		if(MiniMapBotones==1)
		{
			RenderBitmap(73520, JCResto+InitialX +8, InitialY + 6, 124, 124 , 0, 0, 0.2399999495, 0.4989999151, 1, 1, 0.0); //Minimapa carcasa
			int x12, y12, w12, h12;
			//-- Boton Alejar
			x12 = JCResto+InitialX + 58; //Minimapa abajo
			y12 = InitialY + 109; //Minimapa abajo
			w12 = 23;
			h12 = 23;
			if(pCheckMouseOver( x12, y12, w12, h12 ))
			{
				if( *(BYTE*)0x8793386 )
				{	
					//RenderBitmap(73520, x12 , y12+0.5 , 23, 23, 0.41260000253, 0.0744997975, 0.035999919, 0.073999919, 1, 1, 0.0);
					PlayBuffer(25, 0, 0);
					if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
					{
						
						MiniMapBotones=2;
						gRenderMap.DataMap.TimerEventVK = GetTickCount();
					}
				}
				else
				{
					//RenderBitmap(73520, x12, y12, 23, 23, 0.28260000253, 0.1754999595, 0.043859919, 0.084999919, 1, 1, 0.0);
					//RenderBitmap(73520, x12 , y12 +0.5, 23, 23, 0.41260000253, 0.1534999595, 0.035999919, 0.073999919, 1, 1, 0.0);
				}
			
			}
			else
			{
				//RenderBitmap(73520, x12, y12, 23, 23, 0.28260000253, 0.0, 0.043859919, 0.084999919, 1, 1, 0.0);
				//RenderBitmap(73520, x12 , y12, 23, 23, 0.41260000253, 0.0, 0.035999919, 0.073999919, 1, 1, 0.0);
			}
		}
		if(MiniMapBotones==2)
		{
			RenderBitmap(73520, JCResto+InitialX +8, InitialY + 6, 124, 124 , 0, 0, 0.2399999495, 0.4989999151, 1, 1, 0.0); //Minimapa carcasa
			RenderBitmap(73520, JCResto+InitialX +2, InitialY + 2, 120, 136 , 0.5889999151, 0, 0.2399999495, 0.5709999151, 1, 1, 0.0); //Minimapa  botones

			int x1, y1, w1, h1;
			//-- Boton Alejar
			x1 = JCResto+InitialX + 52; //Minimapa abajo
			y1 = InitialY + 109; //Minimapa abajo
			w1 = 23;
			h1 = 23;
		
			if(pCheckMouseOver( x1, y1, w1, h1 ))
			{
				if( *(BYTE*)0x8793386 )
				{
					
					RenderBitmap(73520, x1 , y1+0.5 , 23, 23, 0.41260000253, 0.0744997975, 0.035999919, 0.073999919, 1, 1, 0.0);
					PlayBuffer(25, 0, 0);
					if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
					{
						if ( gRenderMapB.DataMap.Scale == 3 )
						{ 
							gRenderMapB.DataMap.Scale = 2;
						}
						else if ( gRenderMapB.DataMap.Scale == 2 )
						{ 
							gRenderMapB.DataMap.Scale = 1;
						}

						gRenderMapB.DataMap.TimerEventVK = GetTickCount();
					}
				}
				else
				{
				 RenderBitmap(73520, x1 , y1 +0.5, 23, 23, 0.41260000253, 0.1534999595, 0.035999919, 0.073999919, 1, 1, 0.0);
				}
			
			}
			else
			{
			  RenderBitmap(73520, x1 , y1 , 23, 23, 0.41260000253, 0.0, 0.035999919, 0.073999919, 1, 1, 0.0);
			}

			//-- Boton Acercar
			x1 = JCResto+InitialX + 80; //Minimapa abajo
			y1 = InitialY + 102; //Minimapa abajo
			if(pCheckMouseOver( x1, y1, w1, h1 ))
			{
				if( *(BYTE*)0x8793386 )
				{
					//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.3689999878, 0.1219998896, 0.06599189341, 1, 1, 0.0);
					RenderBitmap(73520, x1 , y1 , 23, 23, 0.24060000253, 0.0884997975, 0.043859919, 0.084999919, 1, 1, 0.0);
					PlayBuffer(25, 0, 0);

					if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
					{
						if ( gRenderMapB.DataMap.Scale == 1 )
						{ 
							gRenderMapB.DataMap.Scale = 2;
						}
						else if ( gRenderMapB.DataMap.Scale == 2 )
						{ 
							gRenderMapB.DataMap.Scale = 3;
						}

						gRenderMapB.DataMap.TimerEventVK = GetTickCount();
					}
				}
				else
				{
					//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.3689999878, 0.1219998896, 0.06599189341, 1, 1, 0.0);
					
					RenderBitmap(73520, x1 , y1 , 23, 23, 0.24060000253, 0.1754999595, 0.043859919, 0.084999919, 1, 1, 0.0);
				}
			
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.3689999878, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.24060000253, 0.0, 0.043859919, 0.084999919, 1, 1, 0.0);
			}

			//-- Boton Config
			x1 = JCResto+InitialX + 24; //Minimapa abajo
			y1 = InitialY + 102; //Minimapa abajo
			//-- Carcaza Boton
			//RenderBitmap(31463, x1 - 5, y1 - 3, 26, 26, 0.8360000253, 0.4990000129, 0.1519999206, 0.073999919, 1, 1, 0.0);

		if(pCheckMouseOver( x1, y1, w1, h1 ))
		{
			this->DrawToolTip(JCResto+v11 + 26, v10 - 20, "Especial Menu");
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.682000539, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.28260000253, 0.0884997975, 0.043859919, 0.084999919, 1, 1, 0.0);
				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					if (GetForegroundWindow() == pGameWindow)
					{
						this->SwitchMenuWindowState();
					}
					gRenderMapB.DataMap.TimerEventVK = GetTickCount();
				}
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.682000539, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.28260000253, 0.1754999595, 0.043859919, 0.084999919, 1, 1, 0.0);
			}
		}
		else
		{
			//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.682000539, 0.1219998896, 0.06599189341, 1, 1, 0.0);
			RenderBitmap(73520, x1 , y1 , 23, 23, 0.28260000253, 0.0, 0.043859919, 0.084999919, 1, 1, 0.0);
		}
		//-- Boton Camara
		x1 = JCResto+InitialX + 26; //Minimapa abajo
		y1 = InitialY + 12; //Minimapa abajo
		//-- Carcaza Boton
		//RenderBitmap(73520, x1, y1 , 23, 23, 0, 0.5059999151, 0.043859919, 0.084999919, 1, 1, 0.0);

		if(pCheckMouseOver( x1, y1, w1, h1 ))
		{
			this->DrawToolTip(JCResto+v11 + 26, v10 - 20, "Camera 3D Restore");
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.74460064924, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0, 0.5944997126, 0.043859919, 0.084999919, 1, 1, 0.0);
				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					gCamera.Restore();
				}
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.74460064924, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0, 0.6814998746, 0.043859919, 0.084999919, 1, 1, 0.0);
			}
		}
		else
		{
			//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.74460064924, 0.1219998896, 0.06599189341, 1, 1, 0.0);
			RenderBitmap(73520, x1, y1 , 23, 23, 0, 0.5059999151, 0.043859919, 0.084999919, 1, 1, 0.0);
		}

		//-- Boton 3D
		x1 = JCResto+InitialX + 53; //Minimapa abajo
		y1 = InitialY + 5; //Minimapa abajo
		//-- Carcaza Boton
		//RenderBitmap(31463, x1 - 5, y1 - 3, 26, 26, 0.8360000253, 0.4990000129, 0.1519999206, 0.073999919, 1, 1, 0.0);

		if(pCheckMouseOver( x1, y1, w1, h1 ))
		{
			this->DrawToolTip(JCResto+v11 + 26, v10 - 20, "Camera 3D");
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.61940042876, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.084999919, 0.5944997126, 0.043859919, 0.084999919, 1, 1, 0.0);
				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					gCamera.Toggle();
					gRenderMapB.DataMap.TimerEventVK = GetTickCount();
				}
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.61940042876, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.084999919, 0.6814998746, 0.043859919, 0.084999919, 1, 1, 0.0);
			}
		}
		else
		{
			//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.61940042876, 0.1219998896, 0.06599189341, 1, 1, 0.0);
			RenderBitmap(73520, x1, y1 , 23, 23, 0.084999919, 0.5059999151, 0.043859919, 0.084999919, 1, 1, 0.0);
		}
		
		//-- Boton Armadura
		x1 =JCResto+ InitialX +5; //Minimapa abajo
		y1 = InitialY + 30; //Minimapa abajo
		//-- Carcaza Boton
		//RenderBitmap(31463, x1 - 5, y1 - 3, 26, 26, 0.8360000253, 0.4990000129, 0.1519999206, 0.073999919, 1, 1, 0.0);

		if(pCheckMouseOver( x1, y1, w1, h1 ))
		{
			this->DrawToolTip(JCResto+v11 + 26, v10 - 20, "Config Helper");
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.80720075948, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.43060000253, 0.5737498948, 0.032999919, 0.070999919, 1, 1, 0.0);

				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					gInterface.OpenWindow(MuHelper);
					gRenderMapB.DataMap.TimerEventVK = GetTickCount();
				}	
			
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.80720075948, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.43060000253, 0.6424998746, 0.032999919, 0.070999919, 1, 1, 0.0);
			}
		}
		else
		{
			//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.80720075948, 0.1219998896, 0.06599189341, 1, 1, 0.0);
			RenderBitmap(73520, x1 , y1 , 23, 23, 0.43060000253, 0.5049999151, 0.032999919, 0.070999919, 1, 1, 0.0);
		}
		
		//-- Boton Batalla
		x1 = JCResto+InitialX + 5; //Minimapa abajo
		y1 = InitialY + 83; //Minimapa abajo
		//-- Carcaza Boton
		//RenderBitmap(31463, x1 - 5, y1 - 3, 26, 26, 0.8360000253, 0.4990000129, 0.1519999206, 0.073999919, 1, 1, 0.0);

		if(pCheckMouseOver( x1, y1, w1, h1 ))
		{
			this->DrawToolTip(JCResto+v11 + 26, v10 - 20, "System Option");
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.2499999553, 0.93240097996, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.32560000253, 0.0884997975, 0.043859919, 0.084999919, 1, 1, 0.0);
				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					//colocar
					gRenderMapB.DataMap.TimerEventVK = GetTickCount();
				}		
			}
			else
			{
				//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.1239999682, 0.93240097996, 0.1219998896, 0.06599189341, 1, 1, 0.0);
				RenderBitmap(73520, x1 , y1 , 23, 23, 0.32560000253, 0.1754999595, 0.043859919, 0.084999919, 1, 1, 0.0);
			}
		}
		else
		{
			//RenderBitmap(31463, x1, y1, 18.29999924, 18.29999924, 0.0, 0.93240097996, 0.1219998896, 0.06599189341, 1, 1, 0.0);
			RenderBitmap(73520, x1 , y1 , 23, 23, 0.32560000253, 0.0, 0.043859919, 0.084999919, 1, 1, 0.0);	                                      

		
		}
		//-- Boton mimap return
		x1 = JCResto+InitialX + 10; //Minimapa abajo
		y1 = InitialY + 61; //Minimapa abajo
		//-- 

		if(pCheckMouseOver( x1, y1, 14, 18 ))
		{
			
			RenderBitmap(73520, x1 , y1, 14, 18, 0.45660000253, 0.0554997975, 0.018999919, 0.048999919, 1, 1, 0.0);  
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);

				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					MiniMapBotones=1;
				}		
			}
			else
			{

				RenderBitmap(73520, x1 , y1, 14, 18, 0.45660000253, 0.1104997975, 0.018999919, 0.048999919, 1, 1, 0.0); 
			}
		}
		else
		{
			RenderBitmap(73520, x1 , y1, 14, 18, 0.45660000253, 0.0, 0.018999919, 0.048999919, 1, 1, 0.0); 

		}
		//-- Boton mimap return
		x1 = JCResto+InitialX + 102; //Minimapa abajo
		y1 = InitialY + 61; //Minimapa abajo
		//-- 
		
		if(pCheckMouseOver( x1, y1, 14, 18 ))
		{
			
			RenderBitmap(73520, x1 , y1, 14, 18, 0.47660000253, 0.0554997975, 0.018999919, 0.048999919, 1, 1, 0.0);  
			if( *(BYTE*)0x8793386 )
			{
				PlayBuffer(25, 0, 0);

				if( GetTickCount() >= gRenderMapB.DataMap.TimerEventVK + 200 )
				{
					MiniMapBotones=1;
				}		
			}
			else
			{

				RenderBitmap(73520, x1 , y1, 14, 18, 0.47660000253, 0.1104997975, 0.018999919, 0.048999919, 1, 1, 0.0); 
			}
		}
		else
		{
			RenderBitmap(73520, x1 , y1, 14, 18, 0.47660000253, 0.0, 0.018999919, 0.048999919, 1, 1, 0.0); 

		}

	}	
}
}
}

bool MiniMapFileCheck1ProTecno(int Map) // OK
{
	if(Map - 1 == 30){return 0;}

	char Path[64];

	wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozj", Map);
	int File = rFileOpen(Path, "rb");
	if ( File )
	{
		rFileClose(File);
		return 1;
	}

	wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozt", Map);
	File = rFileOpen(Path, "rb");
	if ( File )
	{
		rFileClose(File);
		return 1;
	}

	return 0;
}

void LogToFile(const char* format, ...)
{
	char buff[1024];
	va_list args;
	va_start(args, format);
	vsprintf_s(buff, format, args);
	va_end(args);

	FILE* f;
	if (fopen_s(&f, "custom_map_debug.log", "a") == 0)
	{
		fprintf(f, "%s\n", buff);
		fclose(f);
	}
}

void MiniMaploadB() // OK
{
	LogToFile("[MiniMaploadB] pMapNumber: %d", pMapNumber);
	if (pMapNumber < 100 && pMapNumber != 30)
	{
		char buff[64];
		char Path[64];
		int Map = pMapNumber + 1;

		wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozj", Map);
		int File = rFileOpen(Path, "rb");
		LogToFile("  Trying %s -> rFileOpen returns: %d", Path, File);
		if (File)
		{
			rFileClose(File);
			wsprintf(buff, "Custom\\Maps\\World%d.jpg", Map);
			gRenderMapB.DataMap.ModelID = 31462;
			LogToFile("  pLoadImage(%s, 31462)", buff);
			pLoadImage(buff, 31462, 0x2601, 0x2900, 1, 0);
			return;
		}

		wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozt", Map);
		File = rFileOpen(Path, "rb");
		LogToFile("  Trying %s -> rFileOpen returns: %d", Path, File);
		if (File)
		{
			rFileClose(File);
			wsprintf(buff, "Custom\\Maps\\World%d.tga", Map);
			gRenderMapB.DataMap.ModelID = 31462;
			LogToFile("  pLoadImage(%s, 31462)", buff);
			pLoadImage(buff, 31462, 0x2601, 0x2900, 1, 0);
			return;
		}

		gRenderMapB.DataMap.ModelID = -1;
		LogToFile("  No map texture found. ModelID set to -1");
	}
}

__declspec(naked) void LoadTextureProTecno()
{
	static DWORD Addr2_JMP = 0x0062F8A6;
	static DWORD Addr1_JMP = 0x0062F87C;
	static DWORD Map = 0x007AA331;

	_asm
	{
		MOV EAX, DWORD PTR SS:[EBP-0x78]
		MOV Map, EAX
	}
	if ( Map == 74 || Map == 75 )
	{
		_asm
		{
			JMP[Addr2_JMP]
		}
	}
	else
	{
		MiniMaploadB();
		_asm
		{
			JMP[Addr1_JMP]
		}
	}
}

void CMinimapB::MiniMaploadB()
{
	SetCompleteHook(0xE9, 0x0062F870, &LoadTextureProTecno); //ok
}