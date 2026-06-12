#pragma once

#define SCREEN_D					2
#define WINDOW_W					600
#define WINDOW_H					600
#define SCREEN_X					(CONST INT)((GetSystemMetrics(SM_CXSCREEN)-WINDOW_W)/SCREEN_D)
#define SCREEN_Y					(CONST INT)((GetSystemMetrics(SM_CYSCREEN)-WINDOW_H)/SCREEN_D)

#define MAX_LOADSTRING 100

#define TIMER_1000 100
#define TIMER_2000 101

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance,int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
LRESULT CALLBACK About(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam);
