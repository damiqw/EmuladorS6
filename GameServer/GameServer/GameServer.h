#pragma once

#define SCREEN_D					2
#define WINDOW_W					1220
#define WINDOW_H					750
#define SCREEN_X					(CONST INT)((GetSystemMetrics(SM_CXSCREEN)-WINDOW_W)/SCREEN_D)
#define SCREEN_Y					(CONST INT)((GetSystemMetrics(SM_CYSCREEN)-WINDOW_H)/SCREEN_D)

#define MAX_LOADSTRING 100

#define WM_TIMER_1000 100
#define WM_TIMER_2000 101
#define WM_TIMER_10000 102

#define WM_JOIN_SERVER_MSG_PROC (WM_USER+1)
#define WM_DATA_SERVER_MSG_PROC (WM_USER+2)

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance,int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK Users(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
HWND hWndComboBox;