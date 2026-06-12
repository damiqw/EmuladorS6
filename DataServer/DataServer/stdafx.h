#pragma once

#define WIN32_LEAN_AND_MEAN

#define _WIN32_WINNT _WIN32_WINNT_WINXP

#define DATASERVER_CLIENT "DataServer"
#define DATASERVER_VERSION "1.0"
#define UPDATE_NAME "UPDATE 1.0"

#ifndef DATASERVER_UPDATE
#define DATASERVER_UPDATE 803
#endif

#ifndef PROTECT_STATE
#define PROTECT_STATE 1
#endif

//Custom
#define NEW_POSTITEM	1
#define HAISLOTRING		1
#define DAILY			1
#define CUSTOM_BRANKINGNEW 1

// System Include
#include <windows.h>
#include <winsock2.h>
#include <commctrl.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <process.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <Rpc.h>
#include <dbghelp.h>
#include <Psapi.h>

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"comctl32.lib")
#pragma comment(lib,"Rpcrt4.lib")
#pragma comment(lib,"dbghelp.lib")
#pragma comment(lib,"Psapi.lib")

extern char CustomerName[32];
extern char CustomerHardwareId[36];

typedef unsigned __int64 QWORD;
