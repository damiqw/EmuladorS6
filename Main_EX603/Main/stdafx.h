#pragma once

#define WIN32_LEAN_AND_MEAN

#define _CRT_SECURE_NO_WARNINGS

#define _WINSOCK_DEPRECATED_NO_WARNINGS

//Custom
#define NEW_POSTITEM			1
#define INFO_EVENTINVASION		1
#define MAP_USAGE				1
#define FPS_60					1
#define PARTY_10				1
#define HAISLOTRING				1
#define RIGHT_CLICK				0

#define QuickAddStats			0

//ProTecno
#define MENU_NEW				1
#define LuckyWheelV2			1
#define CustomXShop				1
#define DAILY                   1
#define MOVECUSTOM              1
#define Check_WindowS           1
#define FLAG					1
#define CUSTOM_BRANKINGNEW		1
#define MODELSKINFIX			8000

#define DLL_VERSION "1.0"

// System Include
#include <windows.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <winsock2.h>
#include <Mmsystem.h>
#include <time.h>
#include <gl\GL.h>
#include <gl\GLU.h>
#include <Shellapi.h>
#include <vector>
#include <map>
#include <algorithm>
#include <winioctl.h>
#include <algorithm>
#include <stdio.h>
#include <cstdarg>
#include "..\\..\\Util\\detours\\detours.h"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Opengl32.lib")
#pragma comment(lib,"..\\..\\Util\\detours\\detours.lib")

#define MAX_CHAT_TYPE1			10
#define LODWORD(h)					((DWORD)(__int64(h) & __int64(0xffffffff)))

//Custom
#define MAX_CUSTOM_MESSAGE			200
#define MAX_CUSTOMMONSTER			500
#define MAX_BOSSCLASS				500
#define MAX_CUSTOM_NPCNAME			100
#define MAX_CUSTOM_MAP				110
#define MAX_CUSTOM_WING				100
#define MAX_DYNAMIC_WING_EFFECT		1000
#define MAX_CUSTOM_WING_EFFECT		3000
#define MAX_CUSTOM_JEWEL			50
#define MAX_CUSTOM_ITEM				2000
#define MAX_CUSTOM_BOW				50
#define MAX_CUSTOM_GLOVES			200
#define MAX_CUSTOMCLOAK				50
#define MAX_EARTH_QUAKE				100
#define MAX_EFFECT_MONSTER			500
#define MAX_CUSTOM_MONSTERGLOW		500
#define MAX_PET_ITEM				300
#define MAX_PET_EFFECT_STATIC		1000
#define MAX_PET_EFFECT_DYNAMIC		1000
#define MAX_PET_GLOW				1000
#define MAX_NOGLOW					200
#define MAX_SERVER_CLASS			20
#define MAX_ITEM2					8192
#define MaxLine						1000
#define MAX_POSITION_ITEM			1000
#define MAX_SMOKE_ITEMS				500
#define MAX_MODEL_EFFECT			500
#define MAX_FOG						100

typedef unsigned __int64 QWORD;

extern DWORD CharacterMaxLevel;

#define WIDE_SCREEN					2
#include "WideScreen.h"

#define MAX_WIN_WIDTH						QTFrame.DisplayWin
#define MAX_WIN_HEIGHT						QTFrame.DisplayHeight
#define WS_WIN_HEIGHTADD					QTFrame.DisplayHeightExt
#define WS_WIN_WIDTHADD						QTFrame.DisplayWinExt
#define WS_WIN_WIDTHREAL					QTFrame.DisplayWinReal
#define CBImgDecor							87968
#define	Fix_DisplayWinCDepthBox				QTFrame.DisplayWinCDepthBox
#define	Fix_DisplayWin						QTFrame.DisplayWin
#define	Fix_DisplayWinMid					QTFrame.DisplayWinMid
#define	Fix_DisplayWinExt					QTFrame.DisplayWinExt	
#define Fix_DisplayHeight                   QTFrame.DisplayHeight
#define Fix_DisplayHeightExt                QTFrame.DisplayHeightExt
#define THEMY			0
#define THEMX			0

enum SPK_RenderFile
{
	BTN_NEX_NEW = 0x7E59,
	BTN_PREV_NEW = 0x7E5A,

	BTN_MENU_OFFSET = 0x17A3C,
	BG_IMG_OFFSET = 0x17A3D,
	MP_IMG_OFFSET = 0x17A40,
	MP_IMG_ENDSET = 0x1C92D,
	HP_IMG_ENDSET = 0x1C92E,
	HP_IMG_GRESET = 0x17A41,
	HP_IMG_REDSET = 0x17A42,
	BG_IMG_HDLSET = 0x17A43,
	BG_IMG_HDRSET = 0x17A44,
	BG_IMG_CHARIC = 0x17A45,

	BG_IMG_PERS = 0x17AEE,
	BG_IMG_NUM2 = 0x17AEF,

	HP_FACER = 0x17AF0,
	HP_FACEB = 0x17AF1,
	HP_MANA = 0x17AF2,
	HP_SDFACE = 0x17AF3,
};
