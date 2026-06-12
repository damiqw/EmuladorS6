#include "stdafx.h"
#include "MiniMap.h"
#include "Import.h"
#include "Util.h"
#include "Offset.h"
#include "User.h"
#include "Interface.h"
#include "Defines.h"
#include "Common.h"
#include "MiniMapInfo.h"
#include "PrintPlayer.h"
#include "CustomFont.h"
#include "BAiFindPath.h"
#include "CNewUIWindowsClient.h"
#include "InterfaceElemental.h"

CMinimap gRenderMap;

#define CGlobalBitmap_GetTexture ((BITMAP_t* (__thiscall*)(void* This, int index)) 0x0042CFE0)

BITMAP_t* GetTextureInfo(int index)
{
	void* cBitmap = (void*)0x9816AA0;
	return CGlobalBitmap_GetTexture(cBitmap, index);
}

void DrawSubImage(int textureId, float x, float y, float width, float height, float x1, float x2, float y1, float y2, int color)
{
	BITMAP_t* tex = GetTextureInfo(textureId);
	float texWidth = 256.0f;
	float texHeight = 256.0f;
	if (tex != nullptr)
	{
		texWidth = tex->Width;
		texHeight = tex->Height;
	}
	float u = x1 / texWidth;
	float v = y1 / texHeight;
	float uw = (x2 - x1) / texWidth;
	float vh = (y2 - y1) / texHeight;

	RenderBitMapColored(textureId, x, y, width, height, u, v, uw, vh, color);
}

void  CMinimap::UpdateX(float X, float Y)
{
	this->DataMap.XSW_Minimap = MAX_WIN_WIDTH - (640 - 535); //-- MiniMapX (Mover Minimapa Izquierda o Derecha)
	this->DataMap.YSW_Minimap = MAX_WIN_HEIGHT - (480 - 310); //-- MiniMapX (Mover Minimapa Izquierda o Derecha)
	this->ultimoX = MAX_WIN_WIDTH - (640 - 535);//Example of initial coordinate {X}. Coordinate that will be constantly modified.
	this->ultimoY = MAX_WIN_HEIGHT - (480 - 310);//Example of initial coordinate {X}. Coordinate that will be constantly modified.

}
CMinimap::CMinimap()
{
	this->DataMap.ModelID = -1;
	this->DataMap.XSW_Minimap_Frame = 0;  //-- Minimap_FrameX
	this->DataMap.YSW_Minimap_Frame = 0;  //-- Minimap_FrameY
	this->DataMap.XSW_Minimap = 539; //-- MiniMapX (Mover Minimapa Izquierda o Derecha)
	this->DataMap.YSW_Minimap = 265; //-- MiniMapY (Minimapa Arriba) (Mover Minimapa Arriba o Abajo)
	this->DataMap.XSW_Time_Frame = 0; //-- Time_FrameX
	this->DataMap.YSW_Time_Frame = 0; //-- Time_FrameY
	this->DataMap.This_92 = 0;
	this->DataMap.This_96 = 0;
	this->DataMap.DropMoveUserX = 0; //-- DropMoveUserX
	this->DataMap.DropMoveUserY = 0; //-- DropMoveUserY
	this->DataMap.This_108;
	this->DataMap.This_112;
	this->DataMap.CurrentMoveX = 0; //-- CurrentMoveX
	this->DataMap.CurrentMoveY = 0; //-- CurrentMoveY
	this->DataMap.Scale = 1; //-- Scale
	this->DataMap.TimerEventVK = 0; //-- Scale
	this->DataMap.Alpha = 1.0f; //-- Alpha
	this->Moving = false;
	this->ultimoX = 539;//Example of initial coordinate {X}. Coordinate that will be constantly modified.
	this->ultimoY = 265;//Example of initial coordinate {Y}. Coordinate that will be constantly modified.
}

CMinimap::~CMinimap()
{
}


POINT Coord;
//----- (0082ABA0)
char CMinimap::MapRender(int a1)
{
	static bool lastMapState = false;
	static int lastMapNumber = -1;
	bool currentMapState = (*(BYTE*)(a1 + 13500) != 0);

	if (pMapNumber != lastMapNumber)
	{
		lastMapState = false;
		lastMapNumber = pMapNumber;
	}

	if (currentMapState && !lastMapState)
	{
		gMiniMap.m_MiniMapSpotInfo.clear();
		BYTE send[4];
		send[0] = 0xC1;
		send[1] = 4;
		send[2] = 0xE7;
		send[3] = 0x01;
		DataSend(send, 4);
	}
	else if (!currentMapState && lastMapState)
	{
		BYTE send[4];
		send[0] = 0xC1;
		send[1] = 4;
		send[2] = 0xE7;
		send[3] = 0x02;
		DataSend(send, 4);
	}
	lastMapState = currentMapState;

	float DIRPointer;
	lpViewObj ObjectPointer;

	char result; // al@2
	float blue; // ST30_4@3
	float green; // ST2C_4@3
	float v7; // ST78_4@3
	float v8; // ST74_4@3
	float v9; // ST20_4@12
	float v10; // ST1C_4@12
	float v11; // ST70_4@12
	float v12; // ST6C_4@12
	float v13; // ST10_4@12
	float v14; // ST0C_4@12
	float v15; // ST20_4@15
	float v16; // ST1C_4@15
	float v17; // ST68_4@15
	float v18; // ST64_4@15
	float v19; // ST10_4@15
	float v20; // ST0C_4@15
	int v21; // eax@17
	int v22; // eax@19
	float v23; // ST30_4@19
	float v24; // ST60_4@19
	int v25; // eax@19
	float v26; // ST5C_4@19
	float v27; // ST58_4@19
	float v28; // ST54_4@22
	float v29; // ST50_4@22
	float v30; // ST4C_4@22
	float v31; // ST48_4@22
	int v32; // eax@23
	int v33; // eax@23
	float v34; // ST2C_4@23
	float v35; // ST44_4@23
	int v36; // eax@23
	float v37; // ST30_4@23
	float v38; // ST40_4@23
	int v39; // eax@23
	float v40; // ST30_4@23
	float v41; // ST2C_4@23
	float v42; // ST3C_4@23
	float v43; // ST38_4@23
	int v44; // [sp+78h] [bp-3Ch]@1
	float v45; // [sp+7Ch] [bp-38h]@3
	float v46; // [sp+88h] [bp-2Ch]@6
	float v47; // [sp+8Ch] [bp-28h]@1
	float v48; // [sp+90h] [bp-24h]@3
	float v49; // [sp+94h] [bp-20h]@6
	float v50; // [sp+98h] [bp-1Ch]@6
	float v51; // [sp+9Ch] [bp-18h]@3
	float v52; // [sp+A4h] [bp-10h]@3
	float v53; // [sp+A8h] [bp-Ch]@3
	signed int i; // [sp+ACh] [bp-8h]@3
	int j; // [sp+ACh] [bp-8h]@17
	int k; // [sp+ACh] [bp-8h]@20
	float v57; // [sp+B0h] [bp-4h]@3

	v44 = a1;
	v47 = 45.0;

	ObjectPointer = &*(ObjectPreview*)(*(DWORD*)0x7BC4F04);
	//DIRPointer = (double) 135.0f + ( 45 * abs((signed int)(ObjectPointer->m_Model.Angle.Z / 45.0)));
	DIRPointer = 180;

	if (*(BYTE*)(a1 + 13500))
	{
		pSetBlend(1);
		//pDrawBarForm(0.0, 0.0, MAX_WIN_WIDTH, MAX_WIN_HEIGHT, 0.45000002, 1);
		pGLSwitch();

		pSetBlend(1);
		glColor4f(1.0, 1.0, 1.0, 1.0);

		pSetCursorFocus = true; //Khoa khong cho click di chuyen
		gElemental.LockMouse = GetTickCount() + 500;
		float MainWidth = 480.0;
		float MainHeight = 480.0;

		float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
		float StartY = (MAX_WIN_HEIGHT / 2) - (MainHeight / 2);
		float XNPC = 0;
		float YNPC = 0;

		int Bx = (pCursorX - StartX) + 1;
		int By = (pCursorY - StartY) + 1;

		Coord.x = Bx / 1.8700005;
		Coord.y = 256.0 - (By / 1.85);
		WORD* TerrainWall = (WORD*)0x82C6AA0;
		int iTerrainIndex = TERRAIN_INDEX(Coord.x, Coord.y);
		RenderBitmap(550000, StartX, StartY + 20.0f, MainWidth, 472.0f, 0, 0, 1.0, 1.0, 1, 1, 0.0);


		for (int n = 0; n < 400; n++)
		{
			lpViewObj lpObj = &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), n);


			if (!lpObj)
			{
				continue;
			}

			if (lpObj->m_Model.Unknown4 == 0)
			{
				continue;
			}
			XNPC = (float)(StartX + (lpObj->MapPosX * 1.8700005));
			YNPC = (float)(StartY + ((255 - lpObj->MapPosY) * 1.85));

			if (lpObj->m_Model.ObjectType == emPlayer)
			{
				sub_637E80(32450, XNPC + 5.0, YNPC - 5.0, 10.0, 10.0, DIRPointer, 0.0, 0.0, 0.546875, 0.546875);

			}
		}

		//-- CICLO PARA PINTAR LOS NPC DESDE SERVIDOR
		CustomFont.Draw(CustomFont.FontNormal, StartX + 20, StartY + 40, 0xFFFFFFFF, 0x00000000, 0, 0, 1, "SPOTS TOTAL: %d", gMiniMap.m_MiniMapSpotInfo.size());

		for (i = 0; i < (signed int)gMiniMap.m_MiniMapSpotInfo.size(); ++i)
		{
			MINIMAP_SPOT_INFO* spot = &gMiniMap.m_MiniMapSpotInfo[i];

			XNPC = (float)(StartX + (spot->x * 1.8700005));
			YNPC = (float)(StartY + ((255.0 - spot->y) * 1.85));

			float drawW = 22.0f;
			float drawH = 22.0f;
			float size = 22.0f;

			if (spot->group == 0) // Portales
			{
				drawW = 16.0f;
				drawH = 24.0f;
				size = 24.0f;
			}

			float drawX = XNPC - (drawW / 2.0f);
			float drawY = YNPC - (drawH / 2.0f);

			//=== Show Name Info 
			if (pCheckMouseOver((int)(XNPC - size / 2.0f), (int)(YNPC - size / 2.0f), (int)size, (int)size)) //Nombre Monsters
			{
				CustomFont.Draw(CustomFont.FontNormal, XNPC + 5, YNPC - 15, 0xFFFFFFFF, 0x0000005D, 0, 0, 8, "%s", spot->text);
			}

			if (spot->group == 0) // Portales
			{
				DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 638.0f, 658.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
			}
			else if (spot->group == 1) // Safezone NPCs
			{
				switch (spot->type)
				{
				case 0:
				case 1: // Shield / Guard / Soldier
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 606.0f, 636.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				case 2: // NPC General / Dialog Bubble / Quest
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 574.0f, 604.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				case 3: // Herrero / Blacksmith / Repair
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 446.0f, 476.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				case 4: // Pociones / Potion
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 510.0f, 540.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				case 5: // Almacén / Storage / Lock
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 478.0f, 508.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				default:
					DrawSubImage(BITMAP_EHUDMAP, drawX, drawY, drawW, drawH, 574.0f, 604.0f, 0.0f, 30.0f, pMakeColor(255, 255, 255, 255));
					break;
				}
			}
		}

		//===Tim Duong Di
		if (!gBAiFindPath.pathTimDuongDi.empty())
		{

			glColor4f(0.0, 0.91, 0.0, 0.75); //Char
			// in ra danh sách các điểm di chuyển trong đường đi
			double phamvi = 0;
			for (int n = 0; n < gBAiFindPath.pathTimDuongDi.size(); n++)
			{

				float BplayerX = gBAiFindPath.pathTimDuongDi[n].x;
				float BplayerY = 256 - gBAiFindPath.pathTimDuongDi[n].y;
				GetDrawCircle(550001, (StartX - 1) + (BplayerX * 1.8700005), ((StartY - 2) + (BplayerY * 1.85)) - 5.0, 5.0, 0, 0, 0, 1, 1, 0.0);
			}
			pGLSwitch();

			pSetBlend(1);
			glColor4f(1.0, 1.0, 1.0, 1.0);
			//==Icon Vi Tri
			XNPC = (float)(StartX + (gBAiFindPath.ViTriCanDenX * 1.8700005));
			YNPC = (float)(StartY + ((255 - gBAiFindPath.ViTriCanDenY) * 1.85));
			RenderBitMapColored(31553, XNPC-5, YNPC - 15.0, 10.0, 10.0, 0.0, 0.0, 0.546875, 0.546875, pMakeColor(255, 115, 0, 255)); //Icono NPC
		}

		//====
		if (pCheckMouseOver(StartX, StartY, MainWidth, MainHeight) == 1)
		{
			gInterface.DrawToolTip(gObjUser.m_CursorX + 20, gObjUser.m_CursorY, "%d ~ %d", Coord.x, Coord.y);
			RenderBitMapColored(31553, gObjUser.m_CursorX-5, gObjUser.m_CursorY-15, 10.0, 10.0, 0.0, 0.0, 0.546875, 0.546875, pMakeColor(255, 115, 0, 255)); //Icono NPC
			if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick > 3000)
			{
				gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();

				//if ((TerrainWall[BTERRAIN_INDEX((int)Coord.x, (int)Coord.y)] & 0x0004) != 0x0004)
				{
					gBAiFindPath.TimDuongDi(*(DWORD*)(Hero + 172), *(DWORD*)(Hero + 176), (int)Coord.x, (int)Coord.y);

				}
			}
		}

		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		result = 1;
	}
	else
	{
		result = *(BYTE*)(a1 + 13500);
	}

	return result;
}

int MoveAutoLoad = 0;

void CMinimap::AutoSendMove()
{

	/*char TDebugTExt[65] = {0};
	sprintf(TDebugTExt, "81F6BD8 [%d]",*(DWORD *)0x81F6BD8);
	pDrawMessage(TDebugTExt, 1); */
	if (!gObjUser.MoveToX && !gObjUser.MoveToY)
	{
		if (gBAiFindPath.ViTriCanDenX != -1 && gBAiFindPath.ViTriCanDenY != -1 && gObjUser.IsSendMove == 0)
		{
			if (*(DWORD*)(Hero + 172) == gBAiFindPath.ViTriCanDenX && *(DWORD*)(Hero + 176) == gBAiFindPath.ViTriCanDenY)
			{
				gBAiFindPath.Clear();
			}
			else
			{
				gBAiFindPath.TimDuongDi(*(DWORD*)(Hero + 172), *(DWORD*)(Hero + 176), gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			}
		}
		return;
	}
	//if (gProtect.m_MainInfo.MoveTabMap == 0)
	//{
	//	return;
	//}

	if (GetKeyState(VK_ESCAPE) < 0 && gObjUser.MoveToX && gObjUser.MoveToY || *(DWORD*)0x81C038C != gObjUser.MoveToX && *(DWORD*)0x81C0388 != gObjUser.MoveToY || gObjUser.AutoMoveCheckMap != pMapNumber)
	{
		if ((GetTickCount() - gInterface.Data[ePLAYER_POINT].EventTick) < 1000) {
			return;
		}
		gInterface.Data[ePLAYER_POINT].EventTick = GetTickCount();
		gObjUser.MoveToX = 0;
		gObjUser.MoveToY = 0;
		*(DWORD*)0x81C038C = 0;
		*(DWORD*)0x81C0388 = 0;
		gObjUser.IsSendMove = 0;
		pDrawMessage("Move Cancel", 1); // Huy Lenh Di Chuyen
		gObjUser.AutoMoveCheckMap = -1;
		this->CGAutoMove(0);
		gBAiFindPath.Clear();
		return;
	}

	if (gObjUser.MoveToX && gObjUser.MoveToY) {
		HFONT FontTextMiniMap = CreateFontA(16, 0, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
		//CustomFont.Draw(FontTextMiniMap, (int)(MAX_WIN_WIDTH / 2)-(300/2), (int)30, 0xBBFF00FF, 0x0000008D, 300, 25, 3, gCustomMessage.GetMessage(93),*(DWORD *)0x81C038C,*(DWORD *)0x81C0388);
		//CustomFont.Draw(FontTextMiniMap, (int)(MAX_WIN_WIDTH / 2)-(300/2), (int)30, 0xBBFF00FF, 0x0000008D, 300, 25, 3,"Test %d/%d %d",*(DWORD *)0x81C038C,*(DWORD *)0x81C0388,gObjUser.lpViewPlayer->Unknown120);
		int chieurong = 200;
		if (MoveAutoLoad == 1)
		{
			gInterface.DrawToolTip((int)(MAX_WIN_WIDTH / 2) - (chieurong / 2), (int)(MAX_WIN_HEIGHT / 2) - (50 / 2), "EnMovimiento", gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			MoveAutoLoad = 2;
		}
		else if (MoveAutoLoad == 2)
		{
			gInterface.DrawToolTip((int)(MAX_WIN_WIDTH / 2) - (chieurong / 2), (int)(MAX_WIN_HEIGHT / 2) - (50 / 2), "EnMovimiento", gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			MoveAutoLoad = 3;
		}
		else if (MoveAutoLoad == 3)
		{
			gInterface.DrawToolTip((int)(MAX_WIN_WIDTH / 2) - (chieurong / 2), (int)(MAX_WIN_HEIGHT / 2) - (50 / 2), "EnMovimiento", gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			MoveAutoLoad = 4;
		}
		else if (MoveAutoLoad == 4)
		{
			gInterface.DrawToolTip((int)(MAX_WIN_WIDTH / 2) - (chieurong / 2), (int)(MAX_WIN_HEIGHT / 2) - (50 / 2), "EnMovimiento", gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			MoveAutoLoad = 0;
		}
		else
		{
			gInterface.DrawToolTip((int)(MAX_WIN_WIDTH / 2) - (chieurong / 2), (int)(MAX_WIN_HEIGHT / 2) - (50 / 2), "EnMovimiento", gBAiFindPath.ViTriCanDenX, gBAiFindPath.ViTriCanDenY);
			MoveAutoLoad = 1;
		}
		DeleteObject(FontTextMiniMap);
	}
	//if ( *(DWORD *)0x81C03B4 >= *(DWORD *)0xE616D0 && !*(BYTE *)0x81C042C )
	if ((GetTickCount() - gObjUser.IsSendMove) < 2000 && gObjUser.lpViewPlayer->Unknown120 > 0) {
		return;
	}
	if (*(DWORD*)0x81C038C == gObjUser.MoveToX && *(DWORD*)0x81C0388 == gObjUser.MoveToY)
	{
		gObjUser.Refresh();
		if (PathFinding2(gObjUser.lpViewPlayer->MapPosX,
			gObjUser.lpViewPlayer->MapPosY,
			*(DWORD*)0x81C038C,
			*(DWORD*)0x81C0388,
			oUserPreviewStruct + 628,
			0.0,
			2))
		{
			gObjUser.IsSendMove = GetTickCount();
			SendMove(oUserPreviewStruct, oUserPreviewStruct + 776);
			if (gObjUser.IsMove >= 1) {
				gObjUser.IsMove--;
			}
		}
		else if (gObjUser.IsMove > 3) {
			gObjUser.MoveToX = 0;
			gObjUser.MoveToY = 0;
			*(DWORD*)0x81C038C = 0;
			*(DWORD*)0x81C0388 = 0;
			gObjUser.IsSendMove = 0;
			gObjUser.IsMove = 0;
			//pDrawMessage(gCustomMessage.GetMessage(96), 1); // Không Cho Hiện Thông Báo Trên Màn Hình*/
			gBAiFindPath.Clear();
			SendAction(oUserPreviewStruct, oUserPreviewStruct + 776);
			return;
		}
		else {
			gObjUser.IsMove++;
		}

		if (gObjUser.lpViewPlayer->MapPosX == *(DWORD*)0x81C038C && gObjUser.lpViewPlayer->MapPosY == *(DWORD*)0x81C0388)
		{
			gObjUser.MoveToX = 0;
			gObjUser.MoveToY = 0;
			*(DWORD*)0x81C038C = 0;
			*(DWORD*)0x81C0388 = 0;
			gObjUser.IsSendMove = 0;
			//pDrawMessage(gCustomMessage.GetMessage(95), 1); // Không Cho Hiện Thông Báo Trên Màn Hình*/
			this->CGAutoMove(0);
			return;
		}

	}

}
void CMinimap::CGAutoMove(int Type)
{
	AUTOMOVE_REQ pRequest;
	pRequest.h.set(0xF3, 0x37, sizeof(pRequest));
	pRequest.TYPE = Type;
	DataSend((LPBYTE)&pRequest, pRequest.h.size);
}

int TimerEvent;

bool MiniMapFileCheck1(int Map) // OK
{
	if (Map - 1 == 30) { return 0; }

	char Path[64];

	wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozj", Map);

	int File = rFileOpen(Path, "rb");

	if (File)
	{
		rFileClose(File);
		return 1;
	}
	else
	{
		return 0;
	}
}

bool JCFileMapCheck(int map) // OK
{
	if (map - 1 == 30) { return 1; }

	char Path[64];

	wsprintf(Path, "Data\\Custom\\Maps\\World%d.ozt", map);

	FILE* file;

	if (fopen_s(&file, Path, "r") != 0)
	{
		return 0;
	}
	else
	{
		fclose(file);
		return 1;
	}
}

void MiniMapLoad() // OK
{
	if (pMapNumber < 100 && pMapNumber != 30)
	{
		char buff1[32];

		wsprintf(buff1, "Custom\\Maps\\World%d.tga", (pMapNumber + 1));

		if (JCFileMapCheck((pMapNumber + 1)) != 0)
		{
			pLoadImage(buff1, 550000, 0x2601, 0x2900, 1, 0);
		}
	}
}

__declspec(naked) void LoadTexture()
{
	static DWORD Addr2_JMP = 0x0062F8A6;
	static DWORD Addr1_JMP = 0x0062F87C;
	static DWORD Map = 0x007AA331;

	_asm
	{
		MOV EAX, DWORD PTR SS : [EBP - 0x78]
		MOV Map, EAX
	}
	if (Map == 74 || Map == 75)
	{
		_asm
		{
			JMP[Addr2_JMP]
		}
	}
	else
	{
		MiniMapLoad();
		_asm
		{
			JMP[Addr1_JMP]
		}
	}
}

bool pDisabledMouseMAP(int x, int y, int w, int h)
{
	return 0;
}

void LoadObjectMapCore() // OK
{
	((void(*)())0x00629180)();

	MiniMapLoad();
}

void LoadImages(char* a1, int a2, int a3, int a4, int a5, int a6)
{

	pLoadImage(a1, a2, a3, a4, a5, a6);
}


void CMinimap::MiniMapload()
{
	SetCompleteHook(0xFF, 0x0062EB26, &LoadObjectMapCore); //ok

	SetCompleteHook(0xE8, 0x0082B772, &pDisabledMouseMAP); //ok

	//SetCompleteHook(0xE9, 0x0062F870, &LoadTexture); //ok
	SetCompleteHook(0xE9, 0x0082ABA0, &CMinimap::MapRender);
}