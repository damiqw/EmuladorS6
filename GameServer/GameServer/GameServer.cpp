#include "stdafx.h"
#include "Resource.h"
#include "BloodCastle.h"
#include "CastleDeep.h"
#include "CastleSiege.h"
#include "ChaosCastle.h"
#include "Crywolf.h"
#include "CustomArena.h"
#include "CustomEventDrop.h"
#include "CustomOnlineLottery.h"
#include "CustomQuiz.h"
#include "DevilSquare.h"
#include "EventGvG.h"
#include "EventTvT.h"
#include "GameServer.h"

#include "BonusManager.h"
#include "GameMain.h"
#include "IllusionTemple.h"
#include "InvasionManager.h"
#include "JSProtocol.h"
#include "Message.h"
#include "MiniDump.h"
#include "Notice.h"
#include "Protect.h"
#include "QueueTimer.h"
#include "ServerDisplayer.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "SocketManagerUdp.h"
#include "ThemidaSDK.h"
#include "Util.h"
#include "CommandManager.h"
#include "CustomLukeHelper.h"
#include "FakeOnline.h"
#include "AntiCrack.h"

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HWND hWnd;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) // OK
{
	gAntiCrack.MainProtection();

	VM_START

	CMiniDump::Start();

	LoadString(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
	LoadString(hInstance,IDC_GAMESERVER,szWindowClass,MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if(InitInstance(hInstance,nCmdShow) == 0)
	{
		return 0;
	}

	SetLargeRand();

	gServerInfo.ReadStartupInfo("GameServerInfo",".\\Data\\GameServerInfo - Common.dat");

	#if(PROTECT_STATE==1)

	#if(GAMESERVER_UPDATE>=801)
	//gProtect.StartAuth(AUTH_SERVER_TYPE_S8_GAME_SERVER);
	#elif(GAMESERVER_UPDATE>=601)
	//gProtect.StartAuth(AUTH_SERVER_TYPE_S6_GAME_SERVER);
	#elif(GAMESERVER_UPDATE>=401)
	//gProtect.StartAuth(AUTH_SERVER_TYPE_S4_GAME_SERVER);
	#else
	//gProtect.StartAuth(AUTH_SERVER_TYPE_S2_GAME_SERVER);
	#endif

	#endif

	char buff[256];

	wsprintf(buff,"[%s] %s - %s",GAMESERVER_VERSION,GAMESERVER_CLIENT,gServerInfo.m_ServerName);

	SetWindowText(hWnd,buff);

	gServerDisplayer.Init(hWnd);

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		if(gSocketManager.Start((WORD)gServerInfo.m_ServerPort) == 0)
		{
			LogAdd(LOG_RED,"Could not start GameServer");
		}
		else
		{
			GameMainInit(hWnd);

			JoinServerConnect(WM_JOIN_SERVER_MSG_PROC);

			DataServerConnect(WM_DATA_SERVER_MSG_PROC);

			gSocketManagerUdp.Connect(gServerInfo.m_ConnectServerAddress,(WORD)gServerInfo.m_ConnectServerPort);

			SetTimer(hWnd,WM_TIMER_1000,1000,0);

			SetTimer(hWnd,WM_TIMER_10000,10000,0);

			gQueueTimer.CreateTimer(QUEUE_TIMER_MONSTER,100,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_MONSTER_MOVE,100,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_MONSTER_AI,100,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_MONSTER_AI_MOVE,100,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_EVENT,100,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_VIEWPORT,1000,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_FIRST,1000,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_CLOSE,1000,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_MATH_AUTHENTICATOR,10000,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_ACCOUNT_LEVEL,60000,&QueueTimerCallback);

			gQueueTimer.CreateTimer(QUEUE_TIMER_PICK_COMMAND,6000,&QueueTimerCallback);
		}
	}
	else
	{
		LogAdd(LOG_RED,"WSAStartup() failed with error: %d",WSAGetLastError());
	}

	SetTimer(hWnd,WM_TIMER_2000,2000,0);

	HACCEL hAccelTable = LoadAccelerators(hInstance,(LPCTSTR)IDC_GAMESERVER);

	MSG msg;

	while(GetMessage(&msg,0,0,0) != 0)
	{
		if(TranslateAccelerator(msg.hwnd,hAccelTable,&msg) == 0)
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	CMiniDump::Clean();

	VM_END

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) // OK
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,(LPCTSTR)IDI_GAMESERVER);
	wcex.hCursor = LoadCursor(0,IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wcex.lpszMenuName = (LPCSTR)IDC_GAMESERVER;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,(LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance,int nCmdShow) // OK
{
	hInst = hInstance;

	hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,SCREEN_X,SCREEN_Y,WINDOW_W,WINDOW_H,0,0,hInstance,0);

	if(hWnd == 0)
	{
		return 0;
	}

	HWND hWndStatusBar;
	hWndStatusBar = CreateWindowEx(0,STATUSCLASSNAME,NULL,WS_CHILD | WS_VISIBLE,0,0,0,0,hWnd,(HMENU)IDC_STATUSBAR,hInstance,NULL);
	ShowWindow(hWndStatusBar,SW_HIDE);

	int iStatusWidths[] = {140,230,330,410,560, -1};
	SendMessage(hWndStatusBar,SB_SETPARTS,6,(LPARAM)iStatusWidths);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return 1;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) // OK
{

	switch(message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_USERS:
					DialogBox(hInst,(LPCTSTR)IDD_USERS,hWnd,(DLGPROC)Users);
					break;
				case IDM_TOOL_GENERATE_ITEM:
					gServerInfo.WriteItemInfo();
					break;
				case IDM_ABOUT:
					DialogBox(hInst,(LPCTSTR)IDD_ABOUTBOX,hWnd,(DLGPROC)About);
					break;
				case IDM_EXIT:
					if(MessageBox(0,"Are you sure to terminate GameServer?","Ask terminate server",MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				case IDM_FILE_ALLUSERLOGOUT:
					gObjAllLogOut();
					break;
				case IDM_FILE_ALLUSERDISCONNECT:
					gObjAllDisconnect();
					break;
				case IDM_FILE_1MINUTESERVERCLOSE:
					if(gCloseMsg == 0)
					{
						gCloseMsg = 1;
						gCloseMsgTime = 60;
						gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(487));
					}
					break;
				case IDM_FILE_3MINUTESERVERCLOSE:
					if(gCloseMsg == 0)
					{
						gCloseMsg = 1;
						gCloseMsgTime = 180;
						gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(488));
					}
					break;
				case IDM_FILE_5MINUTESERVERCLOSE:
					if(gCloseMsg == 0)
					{
						gCloseMsg = 1;
						gCloseMsgTime = 300;
						gNotice.GCNoticeSendToAll(0,0,0,0,0,0,gMessage.GetMessage(489));
					}
					break;
				case IDM_RELOAD_RELOADCASHSHOP:
					gServerInfo.ReadCashShopInfo();
					break;
				case IDM_RELOAD_RELOADCHAOSMIX:
					gServerInfo.ReadChaosMixInfo();
					break;
				case IDM_RELOAD_RELOADCHARACTER:
					gServerInfo.ReadCharacterInfo();
					break;
				case IDM_RELOAD_RELOADCOMMAND:
					gServerInfo.ReadCommandInfo();
					break;
				case IDM_RELOAD_RELOADCOMMON:
					gServerInfo.ReadCommonInfo();
					break;
				case IDM_RELOAD_RELOADCUSTOM:
					gServerInfo.ReadCustomInfo();
					break;
				case IDM_RELOAD_RELOADEVENT:
					gServerInfo.ReadEventInfo();
					break;
				case IDM_RELOAD_RELOADEVENTITEMBAG:
					gServerInfo.ReadEventItemBagInfo();
					break;
				case IDM_RELOAD_RELOADHACK:
					gServerInfo.ReadHackInfo();
					break;
				case IDM_RELOAD_RELOADITEM:
					gServerInfo.ReadItemInfo();
					break;
				case IDM_RELOAD_RELOADMONSTER:
					gServerInfo.ReloadMonsterInfo();
					break;
				case IDM_RELOAD_RELOADMOVE:
					gServerInfo.ReadMoveInfo();
					break;
				case IDM_RELOAD_RELOADQUEST:
					gServerInfo.ReadQuestInfo();
					break;
				case IDM_RELOAD_RELOADSHOP:
					gServerInfo.ReadShopInfo();
					break;
				case IDM_RELOAD_RELOADSKILL:
					gServerInfo.ReadSkillInfo();
					break;
				case IDM_RELOAD_RELOADUTIL:
					gServerInfo.ReadUtilInfo();
					break;
				case IDM_RELOAD_RELOADBOTS: //MC bots
					gServerInfo.ReloadBotInfo(); //MC bots
					break;
				case IDM_RELOAD_RELOADALL:
					gServerInfo.ReloadAll();
					break;
				case IDM_STARTONLINELOTTERY_LORENCIA:
					gCustomOnlineLottery.StartNow(0);
					break;
				case IDM_STARTONLINELOTTERY_DEVIAS:
					gCustomOnlineLottery.StartNow(2);
					break;
				case IDM_STARTONLINELOTTERY_NORIA:
					gCustomOnlineLottery.StartNow(3);
					break;
				case IDM_STARTONLINELOTTERY_ELBELAND:
					gCustomOnlineLottery.StartNow(51);
					break;
				case IDM_STARTBC:
					gBloodCastle.StartBC();
					break;
				case IDM_STARTDS:
					gDevilSquare.StartDS();
					break;
				case IDM_STARTCC:
					gChaosCastle.StartCC();
					break;
				case IDM_STARTIT:
					gIllusionTemple.StartIT();
					break;
				case IDM_STARTQUIZ:
					gCustomQuiz.StartQuiz();
					break;
				case IDM_STARTDROP:
					gCustomEventDrop.StartDrop();
					break;
				case IDM_STARTTVT:
					gTvTEvent.StartTvT();
					break;
				case IDM_STARTGVG:
					gGvGEvent.StartGvG();
					break;
				case IDM_STARTLUKEHELPER:
					gCustomLukeHelper.StartLukeHelper();
					break;
				case IDM_FORCE_BONUS0:
					gBonusManager.ForceStart(0);
					break;
				case IDM_FORCE_BONUS1:
					gBonusManager.ForceStart(1);
					break;
				case IDM_FORCE_BONUS2:
					gBonusManager.ForceStart(2);
					break;
				case IDM_FORCE_BONUS3:
					gBonusManager.ForceStart(3);
					break;
				case IDM_FORCE_BONUS4:
					gBonusManager.ForceStart(4);
					break;
				case IDM_FORCE_BONUS5:
					gBonusManager.ForceStart(5);
					break;
				case IDM_FORCE_BONUS6:
					gBonusManager.ForceStart(6);
					break;
				case IDM_FORCE_BONUS7:
					gBonusManager.ForceStart(7);
					break;
				case IDM_FORCE_BONUS8:
					gBonusManager.ForceStart(8);
					break;
				case IDM_FORCE_BONUS9:
					gBonusManager.ForceStart(9);
					break;
				case IDM_FORCE_BONUS10:
					gBonusManager.ForceStart(10);
					break;
				case IDM_FORCE_BONUS11:
					gBonusManager.ForceStart(11);
					break;
				case IDM_FORCE_BONUS12:
					gBonusManager.ForceStart(12);
					break;
				case IDM_FORCE_BONUS13:
					gBonusManager.ForceStart(13);
					break;
				case IDM_FORCE_BONUS14:
					gBonusManager.ForceStart(14);
					break;
				case IDM_FORCE_BONUS15:
					gBonusManager.ForceStart(15);
					break;
				case IDM_FORCE_BONUS16:
					gBonusManager.ForceStart(16);
					break;
				case IDM_FORCE_BONUS17:
					gBonusManager.ForceStart(17);
					break;
				case IDM_FORCE_BONUS18:
					gBonusManager.ForceStart(18);
					break;
				case IDM_FORCE_BONUS19:
					gBonusManager.ForceStart(19);
					break;
				case IDM_INVASION0:
					gInvasionManager.ForceStart(0);
					break;
				case IDM_INVASION1:
					gInvasionManager.ForceStart(1);
					break;
				case IDM_INVASION2:
					gInvasionManager.ForceStart(2);
					break;
				case IDM_INVASION3:
					gInvasionManager.ForceStart(3);
					break;
				case IDM_INVASION4:
					gInvasionManager.ForceStart(4);
					break;
				case IDM_INVASION5:
					gInvasionManager.ForceStart(5);
					break;
				case IDM_INVASION6:
					gInvasionManager.ForceStart(6);
					break;
				case IDM_INVASION7:
					gInvasionManager.ForceStart(7);
					break;
				case IDM_INVASION8:
					gInvasionManager.ForceStart(8);
					break;
				case IDM_INVASION9:
					gInvasionManager.ForceStart(9);
					break;
				case IDM_INVASION10:
					gInvasionManager.ForceStart(10);
					break;
				case IDM_INVASION11:
					gInvasionManager.ForceStart(11);
					break;
				case IDM_INVASION12:
					gInvasionManager.ForceStart(12);
					break;
				case IDM_INVASION13:
					gInvasionManager.ForceStart(13);
					break;
				case IDM_INVASION14:
					gInvasionManager.ForceStart(14);
					break;
				case IDM_INVASION15:
					gInvasionManager.ForceStart(15);
					break;
				case IDM_INVASION16:
					gInvasionManager.ForceStart(16);
					break;
				case IDM_INVASION17:
					gInvasionManager.ForceStart(17);
					break;
				case IDM_INVASION18:
					gInvasionManager.ForceStart(18);
					break;
				case IDM_INVASION19:
					gInvasionManager.ForceStart(19);
					break;
				case IDM_INVASION20:
					gInvasionManager.ForceStart(20);
					break;
				case IDM_INVASION21:
					gInvasionManager.ForceStart(21);
					break;
				case IDM_INVASION22:
					gInvasionManager.ForceStart(22);
					break;
				case IDM_INVASION23:
					gInvasionManager.ForceStart(23);
					break;
				case IDM_INVASION24:
					gInvasionManager.ForceStart(24);
					break;
				case IDM_INVASION25:
					gInvasionManager.ForceStart(25);
					break;
				case IDM_INVASION26:
					gInvasionManager.ForceStart(26);
					break;
				case IDM_INVASION27:
					gInvasionManager.ForceStart(27);
					break;
				case IDM_INVASION28:
					gInvasionManager.ForceStart(28);
					break;
				case IDM_INVASION29:
					gInvasionManager.ForceStart(29);
					break;
				case IDM_CA0:
					gCustomArena.StartCustomArena(0);
					break;
				case IDM_CA1:
					gCustomArena.StartCustomArena(1);
					break;
				case IDM_CA2:
					gCustomArena.StartCustomArena(2);
					break;
				case IDM_CA3:
					gCustomArena.StartCustomArena(3);
					break;
				case IDM_CA4:
					gCustomArena.StartCustomArena(4);
					break;
				case IDM_CA5:
					gCustomArena.StartCustomArena(5);
					break;
				case IDM_CA6:
					gCustomArena.StartCustomArena(6);
					break;
				case IDM_CA7:
					gCustomArena.StartCustomArena(7);
					break;
				case IDM_CA8:
					gCustomArena.StartCustomArena(8);
					break;
				case IDM_CA9:
					gCustomArena.StartCustomArena(9);
					break;
				case IDM_CA10:
					gCustomArena.StartCustomArena(10);
					break;
				case IDM_CA11:
					gCustomArena.StartCustomArena(11);
					break;
				case IDM_CA12:
					gCustomArena.StartCustomArena(12);
					break;
				case IDM_CA13:
					gCustomArena.StartCustomArena(13);
					break;
				case IDM_STARTCS:
					#if(GAMESERVER_TYPE==1)
					gCastleSiege.StartCS();
					#endif
					break;
				case IDM_STARTCW:
					gCrywolf.StartCW();
					break;
				case IDM_STARTLD:
					gCastleDeep.StartLD();
					break;
				case ID_FAKEONLINE_RELOADDATA:
				{
					for (int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
					{
#if USE_FAKE_ONLINE == TRUE
						if (gObj[n].IsFakeOnline == 1)
						{
							LogAdd(LOG_RED, "[FakeOnline]  [TK: %s NV: %s] Da LogOut", gObj[n].Account, gObj[n].Name);
							gObj[n].IsFakeOnline = 0;
							gObjDel(n);
						}
#endif
					}
#if USE_FAKE_ONLINE == TRUE
					s_FakeOnline.LoadFakeData(".\\AutoTrain.xml");
#endif
				}
				break;

				case ID_FAKEONLINE_ADDFAKEONLINE:
				{
					if (gJoinServerConnection.CheckState() != 0 && gDataServerConnection.CheckState() != 0)
					{
#if USE_FAKE_ONLINE == TRUE
						s_FakeOnline.RestoreFakeOnline();
#endif
					}
				}
				break;

				case ID_FAKEONLINE_DELFAKEONLINE:
				{
					for (int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
					{
#if USE_FAKE_ONLINE == TRUE
						if (gObjIsConnectedGP(n) != 0 && gObj[n].IsFakeOnline)
						{

							s_FakeOnline.OnAttackAlreadyConnected(&gObj[n]);

						}
#endif
					}
				}
				break;

				default:
					return DefWindowProc(hWnd,message,wParam,lParam);
			}
			break;
#if(Fix_Dupe)
		case WM_CLOSE:
			if (MessageBox(0, "Close GameServer?\nSeason 6 Update 2025 \nSource Pike 1.3", "", MB_OKCANCEL) == IDOK)			
			{
				gObjAllLogOut(); 
				gObjAllDisconnect(); 
				DestroyWindow(hWnd);
			}
			break;
#else
			case WM_CLOSE:
				if (MessageBox(0, "Close GameServer?\nSeason 6 Update 2025 \nSource Pike 1.3", "", MB_OKCANCEL) == IDOK)
				{
					DestroyWindow(hWnd);
				}
				break;
#endif
		case WM_TIMER:
			switch(wParam)
			{
				case WM_TIMER_1000:
					GJServerUserInfoSend();
					ConnectServerInfoSend();
					break;
				case WM_TIMER_2000:
					gObjCountProc();
					gServerDisplayer.Run();
					break;
				case WM_TIMER_10000:
					JoinServerReconnect(hWnd,WM_JOIN_SERVER_MSG_PROC);
					DataServerReconnect(hWnd,WM_DATA_SERVER_MSG_PROC);
					break;
			}
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT hPaintStruct;
			HDC hdc = BeginPaint(hWnd, &hPaintStruct);
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP OldBmp = (HBITMAP)SelectObject(hMemDC, LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
			BitBlt(hdc, 0, 0, 663, 72, hMemDC, 0, 0, SRCCOPY);//tamando do bitmap
			SelectObject(hMemDC, OldBmp);
			DeleteDC(hMemDC);
			EndPaint(hWnd, &hPaintStruct);
		}
		break;
		case WM_JOIN_SERVER_MSG_PROC:
			JoinServerMsgProc(wParam,lParam);
			break;
		case WM_DATA_SERVER_MSG_PROC:
			DataServerMsgProc(wParam,lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd,message,wParam,lParam);
	}

	return 0;
}

LRESULT CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_INITDIALOG:
			return 1;
		case WM_COMMAND:
			if(LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg,LOWORD(wParam));
				return 1;
			}
			break;
	}

	return 0;
}

int CheckIpAddress(HWND hDlg,char* text)
{
	HWND hWndIP = GetDlgItem(hDlg,IDC_USERIPLIST);

	int count = SendMessage(hWndIP,LB_GETCOUNT,0,0);

	for(int n=0;n < count;n++)
	{
		int aIndex = (int)SendMessage(hWndIP,LB_GETITEMDATA,(LPARAM)n,0);

		if(strcmp(gObj[aIndex].IpAddr,text) == 0)
		{
			return 1;
		}
	}

	return 0;
}

LRESULT CALLBACK Users(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	HWND hWndAcc = GetDlgItem(hDlg,IDC_ACCNAME);

	HWND hWndChar = GetDlgItem(hDlg,IDC_CHARNAME);

	HWND hWndIP = GetDlgItem(hDlg,IDC_USERIPLIST);

	HWND hWndHID = GetDlgItem(hDlg,IDC_USERHIDLIST);

	HWND hWndUL = GetDlgItem(hDlg,IDC_ACCOUNTLIST);

	if(message == WM_INITDIALOG)
	{
		SendMessage(hWndAcc,WM_SETTEXT,0,(LPARAM)"Account:");

		SendMessage(hWndChar,WM_SETTEXT,0,(LPARAM)"Character:");

		SendMessage(hWndIP,LB_RESETCONTENT,0,0);

		SendMessage(hWndHID,LB_RESETCONTENT,0,0);

		SendMessage(hWndUL,LB_RESETCONTENT,0,0);

		for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
		{
			if(gObj[n].Connected >= OBJECT_CONNECTED && gObj[n].Type == OBJECT_USER)
			{
				if(CheckIpAddress(hDlg,gObj[n].IpAddr) == 0)
				{
					int aItem = SendMessage(hWndIP,LB_ADDSTRING,0,(LPARAM)gObj[n].IpAddr);

					SendMessage(hWndIP,LB_SETITEMDATA,aItem,n);	
				}

				char buff[256];

				wsprintf(buff,"[%s][%s]",gObj[n].Account,gObj[n].Name);

				int bItem = SendMessage(hWndUL,LB_ADDSTRING,0,(LPARAM)buff);

				SendMessage(hWndUL,LB_SETITEMDATA,bItem,n);
			}
		}

		SetFocus(hWndIP);

		return 1;
	}
	else if(message == WM_COMMAND)
	{
		if(LOWORD(wParam) == IDC_USERIPLIST && HIWORD(wParam) == LBN_SELCHANGE)
		{
			int aItem = SendMessage(hWndIP,LB_GETCURSEL,0,0);

			int aIndex = SendMessage(hWndIP,LB_GETITEMDATA,aItem,0);

			SendMessage(hWndHID,LB_RESETCONTENT,0,0);

			if(gObj[aIndex].Connected < OBJECT_CONNECTED || gObj[aIndex].Type < OBJECT_USER)
			{
				return 0;
			}

			for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
			{
				if(gObj[n].Connected >= OBJECT_CONNECTED && gObj[n].Type == OBJECT_USER && strcmp(gObj[aIndex].IpAddr,gObj[n].IpAddr) == 0)
				{
					int bItem = SendMessage(hWndHID,LB_ADDSTRING,0,(LPARAM)gObj[n].HardwareId);

					SendMessage(hWndHID,LB_SETITEMDATA,bItem,n);
				}
			}

			return 1;
		}
		else if(LOWORD(wParam) == IDC_USERHIDLIST && HIWORD(wParam) == LBN_SELCHANGE)
		{
			int aItem = SendMessage(hWndHID,LB_GETCURSEL,0,0);

			int aIndex = SendMessage(hWndHID,LB_GETITEMDATA,aItem,0);

			char buff[256];

			wsprintf(buff,"Account: %s",gObj[aIndex].Account);

			SendMessage(hWndAcc,WM_SETTEXT,0,(LPARAM)buff);

			wsprintf(buff,"Character: %s",gObj[aIndex].Name);

			SendMessage(hWndChar,WM_SETTEXT,0,(LPARAM)buff);

			return 1;
		}
		else if(LOWORD(wParam) == IDC_REFRESH)
		{
			SendMessage(hWndAcc,WM_SETTEXT,0,(LPARAM)"Account:");

			SendMessage(hWndChar,WM_SETTEXT,0,(LPARAM)"Character:");

			SendMessage(hWndIP,LB_RESETCONTENT,0,0);

			SendMessage(hWndHID,LB_RESETCONTENT,0,0);

			SendMessage(hWndUL,LB_RESETCONTENT,0,0);

			for(int n=OBJECT_START_USER;n < MAX_OBJECT;n++)
			{
				if(gObj[n].Connected >= OBJECT_CONNECTED && gObj[n].Type == OBJECT_USER)
				{
					if(CheckIpAddress(hDlg,gObj[n].IpAddr) == 0)
					{
						int aItem = SendMessage(hWndIP,LB_ADDSTRING,0,(LPARAM)gObj[n].IpAddr);

						SendMessage(hWndIP,LB_SETITEMDATA,aItem,n);	
					}

					char buff[256];

					wsprintf(buff,"[%s][%s]",gObj[n].Account,gObj[n].Name);

					int bItem = SendMessage(hWndUL,LB_ADDSTRING,0,(LPARAM)buff);

					SendMessage(hWndUL,LB_SETITEMDATA,bItem,n);
				}
			}

			SetFocus(hWndIP);

			return 1;
		}
		else if(LOWORD(wParam) == IDC_DISCONNECT)
		{
			SendMessage(hWndAcc,WM_SETTEXT,0,(LPARAM)"Account:");

			SendMessage(hWndChar,WM_SETTEXT,0,(LPARAM)"Character:");

			int aItem = SendMessage(hWndHID,LB_GETCURSEL,0,0);

			int aIndex = SendMessage(hWndHID,LB_GETITEMDATA,aItem,0);

			gObjUserKill(aIndex);

			SendMessage(hWndHID,LB_DELETESTRING,aItem,0);

			if(SendMessage(hWndHID,LB_GETCOUNT,0,0) == 0)
			{
				int bItem = SendMessage(hWndIP,LB_GETCURSEL,0,0);

				SendMessage(hWndIP,LB_DELETESTRING,bItem,0);
			}

			return 1;
		}
		else if(LOWORD(wParam) == IDC_BANACC)
		{
			int aItem = SendMessage(hWndHID,LB_GETCURSEL,0,0);

			int aIndex = SendMessage(hWndHID,LB_GETITEMDATA,aItem,0);

			SDHP_COMMAND_BAN_ACCOUNT_SEND pMsg;

			pMsg.header.set(0x0F,0x06,sizeof(pMsg));

			memcpy(pMsg.account,gObj[aIndex].Account,sizeof(pMsg.account));

			pMsg.BlocCode = 1;

			gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

			gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(628));

			gObjUserKill(aIndex);

			SendMessage(hWndHID,LB_DELETESTRING,aItem,0);

			if(SendMessage(hWndHID,LB_GETCOUNT,0,0) == 0)
			{
				int bItem = SendMessage(hWndIP,LB_GETCURSEL,0,0);

				SendMessage(hWndIP,LB_DELETESTRING,bItem,0);
			}

			return 1;
		}
		else if(LOWORD(wParam) == IDC_BANCHAR)
		{
			int aItem = SendMessage(hWndHID,LB_GETCURSEL,0,0);

			int aIndex = SendMessage(hWndHID,LB_GETITEMDATA,aItem,0);

			SDHP_COMMAND_BAN_CHARACTER_SEND pMsg;

			pMsg.header.set(0x0F,0x07,sizeof(pMsg));

			memcpy(pMsg.name,gObj[aIndex].Name,sizeof(pMsg.name));

			pMsg.CtlCode = 1;

			gDataServerConnection.DataSend((BYTE*)&pMsg,pMsg.header.size);

			gNotice.GCNoticeSend(aIndex,1,0,0,0,0,0,gMessage.GetMessage(628));

			gObjUserKill(aIndex);

			SendMessage(hWndHID,LB_DELETESTRING,aItem,0);

			if(SendMessage(hWndHID,LB_GETCOUNT,0,0) == 0)
			{
				int bItem = SendMessage(hWndIP,LB_GETCURSEL,0,0);

				SendMessage(hWndIP,LB_DELETESTRING,bItem,0);
			}

			return 1;
		}
		else if(LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg,LOWORD(wParam));
			return 1;
		}
	}

	return 0;
}

