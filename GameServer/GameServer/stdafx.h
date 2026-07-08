#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

#define GAMESERVER_STATUS "STANDBY MODE"
#define GAMESERVER_STATUS_MODE "ACTIVE MODE"

#define GAMESERVER_CLIENTE_PREMIUM 1

#define GAMESERVER_VERSION "1.0"

#define UPDATE_NAME "UPDATE 1.0"

#if(GAMESERVER_TYPE==0)
#define GAMESERVER_CLIENT "GameServer"
#else
#define GAMESERVER_CLIENT "GameServer Siege"
#endif

#ifndef GAMESERVER_TYPE
#define GAMESERVER_TYPE 0
#endif

#ifndef GAMESERVER_EXTRA
#define GAMESERVER_EXTRA 1
#endif

#ifndef GAMESERVER_UPDATE
#define GAMESERVER_UPDATE 803
#endif

#ifndef GAMESERVER_LANGUAGE
#define GAMESERVER_LANGUAGE 1
#endif

#ifndef PROTECT_STATE
#define PROTECT_STATE 1
#endif

#ifndef ENCRYPT_STATE
#define ENCRYPT_STATE 1
#endif

//Custom
#define RIGHT_CLICK				0
#define INFO_EVENTINVASION		1
#define MAP_USAGE				1
#define NEW_POSTITEM			1
#define CUSTOM_PET				1
#define REGISTER_ACCOUNT		1
#define AUTO_MOVE				1
#define HAISLOTRING				1 // ON SLOTS

//Fix
#define FIX_DUPE				1
#define FIXBUGCOIN				1
#define FIX_NOTICE_KANTURU		1
#define FIX_SUMMON_PARTY		1
#define USE_FAKE_ONLINE			TRUE
#define Fix_Dupe				1
#define ANTI_CRACK				1
#define Delete_DupeItem			1
#define CUSTOM_BRANKINGNEW	    1
//LIMITED
#define USE_USERLIMIT	FALSE
#define MAX_USERCOUNT	1000
#define MAX_ITEM_SLOT		    30
#define LuckyWheelV2			1
#define DAILY					1
#define FLAG					1
//MC bot

//----------------------------
//	 ZG-Defines			     -
//	 1:ON  (CPP AND HEADER!) -
//	 2:OFF (CPP AND HEADER!) -
//----------------------------

#ifndef POINT_CUSTOM 
#define POINT_CUSTOM 1 // ShopPointEx
#endif

#define PC_POINT			 2 //Agregar algun npc o bot con PCP
#define HAPPY_HOURS			 2 //[80%]->Falta Arreglar Los Vip!
#define MASTER_HOURS		 2
#define ACHERON_GUARDIAN	 2

#define BOT_BUFFER			 1
#define BOT_STORE			 1

#define ARCA_WAR			 2	// Mix nomas!!
#define GOLDEN_ARCHER		 2	// 

//-- Need All Types
#define PG_CUSTOM			 1
#define	ALLBOTSSTRUC		 1

//MC bot

// System Include
#include <windows.h>
#include <winsock2.h>
#include <mswSock.h>
#include <commctrl.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <map>
#include <vector>
#include <queue>
#include <random>
#include <Rpc.h>
#include <algorithm>
#include <string>
#include <atltime.h>
#include <dbghelp.h>
#include <Psapi.h>
#include <thread>
#include "pugixml.hpp"

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Rpcrt4.lib")
#pragma comment(lib,"dbghelp.lib")
#pragma comment(lib,"Psapi.lib")

#if(GAMESERVER_UPDATE>=701)
#if(NDEBUG==0)
#pragma comment(lib,"..\\..\\Util\\cryptopp\\Debug\\cryptlib.lib")
#else
#pragma comment(lib,"..\\..\\Util\\cryptopp\\Release\\cryptlib.lib")
#endif
#pragma comment(lib,"..\\..\\Util\\mapm\\mapm.lib")
#endif

typedef char chr;

typedef float flt;

typedef short shrt;

typedef unsigned __int64 QWORD;
