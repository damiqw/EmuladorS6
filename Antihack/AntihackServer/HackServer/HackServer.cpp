#include "stdafx.h"
#include "resource.h"
#include "HackServer.h"
#include "MiniDump.h"
#include "ProcessManager.h"
#include "ServerDisplayer.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "ReadFiles.h"
#include "BlackList.h"
#include "HidManager.h"
#include "Util.h"
#include "HelperPlayers.h"

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
TCHAR szChildTitle[MAX_LOADSTRING];
TCHAR szChildClass[MAX_LOADSTRING];
HWND hWnd;
HWND hChildWnd;
HWND ScreenWnd;

HWND ProcessListWnd;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) // OK
{
	CMiniDump::Start();

	LoadString(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
	LoadString(hInstance,IDC_HACKSERVER,szWindowClass,MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if(InitInstance(hInstance,nCmdShow) == 0)
	{
		return 0;
	}

	gServerInfo.ReadStartupInfo("AntihackServerInfo",".\\AntihackServer.ini");

	char buff[256];

	wsprintf(buff, "[%s] %s", HACKSERVER_VERSION, HACKSERVER_CLIENT);

	SetWindowText(hWnd,buff);

	gServerDisplayer.Init(hWnd);

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		if(gSocketManager.Start(gServerInfo.m_HackServerPort) != 0)
		{
			gServerInfo.ReadInit();

			SetTimer(hWnd,TIMER_1000,1000,nullptr);

			SetTimer(hWnd,TIMER_5000,5000,nullptr);
		}
	}
	else
	{
		LogAdd(LOG_RED,"WSAStartup() failed with error: %d",WSAGetLastError());
	}


	SetTimer(hWnd,TIMER_2000,2000,nullptr);

	HACCEL h_accel_table = LoadAccelerators(hInstance,(LPCTSTR)IDC_HACKSERVER);

	MSG msg;

	while(GetMessage(&msg,nullptr,0,0) != 0)
	{
		if(TranslateAccelerator(msg.hwnd,h_accel_table,&msg) == 0)
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	CMiniDump::Clean();

	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) // OK
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)wnd_proc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance,(LPCTSTR)IDI_ICON1);
	wcex.hCursor = LoadCursor(nullptr,IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wcex.lpszMenuName = (LPCSTR)IDC_HACKSERVER;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,(LPCTSTR)IDI_ICON1);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance,int nCmdShow) // OK
{
	hInst = hInstance;

	hWnd = hWnd = CreateWindow(szWindowClass,szTitle,WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,SCREEN_X,SCREEN_Y,WINDOW_W,WINDOW_H,0,0,hInstance,0);

	if(hWnd == 0)
	{
		return 0;
	}

	HWND hWndStatusBar;
	hWndStatusBar = CreateWindowEx(0,STATUSCLASSNAME,NULL,WS_CHILD | WS_VISIBLE,0,0,0,0,hWnd,(HMENU)IDC_STATUSBAR,hInstance,NULL);
	ShowWindow(hWndStatusBar,SW_HIDE);

	int iQueueBarWidths[] = { 140,-1 };

	SendMessage(hWndStatusBar,SB_SETPARTS,2,(LPARAM)iQueueBarWidths);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	return 1;
}

LRESULT CALLBACK wnd_proc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDM_ABOUT:
					DialogBox(hInst,(LPCTSTR)IDD_ABOUTBOX,hWnd,(DLGPROC)About);
					break;
				case ID_OTHER_BANNED:
					DialogBox(hInst,(LPCTSTR)IDM_BANNED,hWnd,(DLGPROC)Banned);
					break;
				case ID_OTHER_SCREEN:
					DialogBox(hInst,(LPCTSTR)IDD_INFO_DIALOG,hWnd,(DLGPROC)PlayersList);
					break;
				case ID_OTHER_DELETETEMPBANS:
					gHidManager.DeleteAllHardwareId();
					break;
				case IDM_EXIT:
					if(MessageBox(nullptr,"Are you sure to terminate AntihackServer?","Ask terminate server",MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				case IDM_RELOAD_CONFIG:
					gServerInfo.ReadConfig();
					break;
				case IDM_RELOAD_DUMP:
					gServerInfo.ReadDumpList();
					break;
				case IDM_RELOAD_CHECKSUM:
					gServerInfo.ReadChecksumList();
					break;
				case IDM_RELOAD_WINDOW:
					gServerInfo.ReadWindowList();
					break;
				case IDM_RELOAD_BLACKLIST:
					gServerInfo.ReadBlackList();
					break;
				case IDM_UPDATE:
					gReadFiles.UpdateInternalList();
					break;
				default:
					return DefWindowProc(hWnd,message,wParam,lParam);
			}
			break;
		case WM_TIMER:
			switch(wParam)
			{
				case TIMER_1000:
					gProcessManager.CheckProcess();
					break;
				case TIMER_2000:
					gServerDisplayer.Run();
					break;
				case TIMER_5000:
					TimeoutProc();
					gProcessManager.ClearProcessCache();
					break;
				default:
					break;
			}
			break;
		case WM_DESTROY:
			{
				PostQuitMessage(0);
			}
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


LRESULT CALLBACK PlayersList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // OK
{
	switch (message)
	{
	case WM_INITDIALOG:
		{
			gHelperPlayers.init_dialog(hDlg);
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_SEARCH_IP: gHelperPlayers.search_ip(); break;
		case IDC_CLEAR_IP: gHelperPlayers.clear_ip(); break;
		case IDC_BAN_IP: gHelperPlayers.ban_ip(); break;
		case IDC_BAN_HWID: gHelperPlayers.ban_hwid(); break;
		case IDC_CLOSE_CLIENT: gHelperPlayers.close_client(); break;
		case IDC_LIST_IP: gHelperPlayers.list_ip(wParam); break;
		case IDC_LIST_HWID: gHelperPlayers.list_hwid(wParam); break;
		case ID_RELOAD: gHelperPlayers.reload(); break;
		}
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg,LOWORD(wParam));
			return 1;
		}
		break;
	}

	return 0;
}

LRESULT CALLBACK Banned(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam) // OK
{
	switch(message)
	{
		case WM_INITDIALOG:
			{
				char WindowName[100];
				int UsersCount = gHidManager.m_HardwareIdInfo.size();
				sprintf(WindowName, "Temporary Banned %d Users", UsersCount);
				SetWindowText(hDlg, WindowName);
				HWND accounts_list_box = GetDlgItem(hDlg, IDC_LIST1); 

				for(std::vector<HARDWARE_ID_INFO>::iterator it=gHidManager.m_HardwareIdInfo.begin();it != gHidManager.m_HardwareIdInfo.end();it++)
				{
					SendMessage(accounts_list_box,LB_ADDSTRING,NULL,LPARAM(it->HardwareId));
				}
			}
			break;

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