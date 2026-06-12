#include "stdafx.h"
#include "resource.h"
#include "ConnectServer.h"
#include "MiniDump.h"
#include "Protect.h"
#include "ServerDisplayer.h"
#include "ServerList.h"
#include "SocketManager.h"
#include "SocketManagerUdp.h"
#include "ThemidaSDK.h"
#include "Util.h"

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];
HWND hWnd;
char CustomerName[32];
char CustomerHardwareId[36];
long MaxIpConnection;

int m_AntiFloodMaxTimeCheck = 0;
int m_AntiFloodMinTimeCheck = 0;
int m_AntiFloodMaxCount = 0;
int m_AntiFloodBlockTime = 0;

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow) // OK
{
	VM_START

	CMiniDump::Start();

	LoadString(hInstance,IDS_APP_TITLE,szTitle,MAX_LOADSTRING);
	LoadString(hInstance,IDC_CONNECTSERVER,szWindowClass,MAX_LOADSTRING);

	MyRegisterClass(hInstance);

	if(InitInstance(hInstance,nCmdShow) == 0)
	{
		return 0;
	}

	GetPrivateProfileString("ConnectServerInfo","CustomerName","",CustomerName,sizeof(CustomerName),".\\ConnectServer.ini");

	GetPrivateProfileString("ConnectServerInfo","CustomerHardwareId","",CustomerHardwareId,sizeof(CustomerHardwareId),".\\ConnectServer.ini");

	#if(PROTECT_STATE==1)

	#if(CONNECTSERVER_UPDATE>=801)
	gProtect.StartAuth(AUTH_SERVER_TYPE_S8_CONNECT_SERVER);
	#elif(CONNECTSERVER_UPDATE>=601)
	gProtect.StartAuth(AUTH_SERVER_TYPE_S6_CONNECT_SERVER);
	#elif(CONNECTSERVER_UPDATE>=401)
	gProtect.StartAuth(AUTH_SERVER_TYPE_S4_CONNECT_SERVER);
	#else
	gProtect.StartAuth(AUTH_SERVER_TYPE_S2_CONNECT_SERVER);
	#endif

	#endif

	char buff[256];

	wsprintf(buff,"[%s] %s",CONNECTSERVER_VERSION,CONNECTSERVER_CLIENT);

	SetWindowText(hWnd,buff);

	gServerDisplayer.Init(hWnd);

	WSADATA wsa;

	if(WSAStartup(MAKEWORD(2,2),&wsa) == 0)
	{
		WORD ConnectServerPortTCP = GetPrivateProfileInt("ConnectServerInfo","ConnectServerPortTCP",44405,".\\ConnectServer.ini");

		WORD ConnectServerPortUDP = GetPrivateProfileInt("ConnectServerInfo","ConnectServerPortUDP",55557,".\\ConnectServer.ini");

		MaxIpConnection = GetPrivateProfileInt("ConnectServerInfo","MaxIpConnection",0,".\\ConnectServer.ini");

		m_AntiFloodMaxTimeCheck = GetPrivateProfileInt("ConnectServerInfo", "AntiFloodMaxTimeCheck", 5, ".\\ConnectServer.ini");
		m_AntiFloodMinTimeCheck = GetPrivateProfileInt("ConnectServerInfo", "AntiFloodMinTimeCheck", 5, ".\\ConnectServer.ini");
		m_AntiFloodMaxCount = GetPrivateProfileInt("ConnectServerInfo", "AntiFloodMaxCount", 10, ".\\ConnectServer.ini");
		m_AntiFloodBlockTime = GetPrivateProfileInt("ConnectServerInfo", "AntiFloodBlockTime", 60, ".\\ConnectServer.ini");

		if(gSocketManager.Start(ConnectServerPortTCP) != 0)
		{
			if(gSocketManagerUdp.Start(ConnectServerPortUDP) != 0)
			{
				gServerList.Load("ServerList.dat");

				SetTimer(hWnd,TIMER_1000,1000,0);

				SetTimer(hWnd,TIMER_5000,5000,0);
			}
		}
	}
	else
	{
		LogAdd(LOG_RED,"WSAStartup() failed with error: %d",WSAGetLastError());
	}

	SetTimer(hWnd,TIMER_2000,2000,0);

	HACCEL hAccelTable = LoadAccelerators(hInstance,(LPCTSTR)IDC_CONNECTSERVER);

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
	wcex.hIcon = LoadIcon(hInstance,(LPCTSTR)IDI_CONNECTSERVER);
	wcex.hCursor = LoadCursor(0,IDC_ARROW);
	wcex.hbrBackground = CreateSolidBrush(RGB(0,0,0));
	wcex.lpszMenuName = (LPCSTR)IDC_CONNECTSERVER;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance,(LPCTSTR)IDI_SMALL);

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
	hWndStatusBar = CreateWindowEx(0,STATUSCLASSNAME,0,WS_CHILD | WS_VISIBLE,0,0,0,0,hWnd,(HMENU)IDC_STATUSBAR,hInstance,0);
	ShowWindow(hWndStatusBar,SW_HIDE);

	int iQueueBarWidths[] = { 110,230,-1 };

	SendMessage(hWndStatusBar,SB_SETPARTS,3,(LPARAM)iQueueBarWidths);

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
				case IDM_ABOUT:
					DialogBox(hInst,(LPCTSTR)IDD_ABOUTBOX,hWnd,(DLGPROC)About);
					break;
				case IDM_EXIT:
					if(MessageBox(0,"Are you sure to terminate ConnectServer?","Ask terminate server",MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				case IDM_RELOAD_RELOADSERVERLIST:
					gServerList.Load("ServerList.dat");
					break;
				default:
					return DefWindowProc(hWnd,message,wParam,lParam);
			}
			break;
		case WM_TIMER:
			switch(wParam)
			{
				case TIMER_1000:
					gServerList.MainProc();
					break;
				case TIMER_2000:
					gServerDisplayer.Run();
					break;
				case TIMER_5000:
					ConnectServerTimeoutProc();
					break;
				default:
					break;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT hPaintStruct;
			HDC hdc = BeginPaint(hWnd, &hPaintStruct);
			HDC hMemDC = CreateCompatibleDC(hdc);
			HBITMAP OldBmp = (HBITMAP)SelectObject(hMemDC, LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1)));
			BitBlt(hdc, 0, 0, 1920, 80, hMemDC, 0, 0, SRCCOPY);//tamando do bitmap
			SelectObject(hMemDC, OldBmp);
			DeleteDC(hMemDC);
			EndPaint(hWnd, &hPaintStruct);
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
