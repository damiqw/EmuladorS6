#include "stdafx.h"
#include "HackCheck.h"
#include "Offset.h"
#include "Protect.h"
#include "Util.h"

typedef int(WINAPI*WSRECV)(SOCKET,char*,int,int);
typedef int(WINAPI*WSSEND)(SOCKET,char*,int,int);

WSRECV HookRecv;
WSSEND HookSend;
BYTE EncDecKey1;
BYTE EncDecKey2;
DWORD FrameValue = 0;
DWORD SpeedValue = 0;
DWORD MainTickCount = 0;
DWORD SyncTickCount = 0;
DWORD CountModifier = 0;
DWORD DelayModifier = 0;
DWORD HasteModifier = 0;
DWORD SleepModifier = 0;
DWORD SpeedModifier1 = 0;
DWORD SpeedModifier2 = 0;
DWORD ModelModifier1 = 0;
DWORD ModelModifier2 = 0;
DWORD ModelModifier3 = 0;

DWORD g_FrameCountActive = 16;      // 60 FPS (~16.6ms)
DWORD g_FrameCountBackground = 40;  // 25 FPS (40ms)
DWORD g_FrameCountMinimized = 100;  // 10 FPS (100ms)
DWORD g_CurrentFrameCount = 16;

void __cdecl UpdateFrameCount()
{
	HWND hWnd = *(HWND*)(MAIN_WINDOW);
	if(hWnd != 0 && (IsIconic(hWnd) != 0 || IsWindowVisible(hWnd) == 0))
	{
		g_CurrentFrameCount = g_FrameCountMinimized;
	}
	else if(hWnd != 0 && GetForegroundWindow() != hWnd)
	{
		g_CurrentFrameCount = g_FrameCountBackground;
	}
	else
	{
		g_CurrentFrameCount = g_FrameCountActive;
	}
}

void LoadFpsSettings()
{
	int maxFps = GetPrivateProfileIntA("Graphics", "MaxFPS", 60, ".\\Settings.ini");
	if (maxFps <= 0) maxFps = 60;
	if (maxFps > 300) maxFps = 300;
	g_FrameCountActive = 1000 / maxFps;
	if (g_FrameCountActive == 0) g_FrameCountActive = 1;

	int bgFps = GetPrivateProfileIntA("Graphics", "BackgroundFPS", 25, ".\\Settings.ini");
	if (bgFps <= 0) bgFps = 25;
	if (bgFps > maxFps) bgFps = maxFps;
	g_FrameCountBackground = 1000 / bgFps;
	if (g_FrameCountBackground == 0) g_FrameCountBackground = 1;

	int minFps = GetPrivateProfileIntA("Graphics", "MinimizedFPS", 20, ".\\Settings.ini");
	if (minFps <= 0) minFps = 20;
	if (minFps > bgFps) minFps = bgFps;
	g_FrameCountMinimized = 1000 / minFps;
	if (g_FrameCountMinimized == 0) g_FrameCountMinimized = 1;

	g_CurrentFrameCount = g_FrameCountActive;
}

void DecryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]^EncDecKey1)-EncDecKey2;
	}
}

void EncryptData(BYTE* lpMsg,int size) // OK
{
	for(int n=0;n < size;n++)
	{
		lpMsg[n] = (lpMsg[n]+EncDecKey2)^EncDecKey1;
	}
}

bool CheckSocketPort(SOCKET s) // OK
{
	SOCKADDR_IN addr;
	int addr_len = sizeof(addr);

	if(getpeername(s,(SOCKADDR*)&addr,&addr_len) == SOCKET_ERROR)
	{
		return 0;
	}

	if(PORT_RANGE(ntohs(addr.sin_port)) == 0)
	{
		return 0;
	}

	return 1;
}

int WINAPI MyRecv(SOCKET s,char* buf,int len,int flags) // OK
{
	int result = HookRecv(s,(char*)buf,len,flags);

	if(result == SOCKET_ERROR || result == 0)
	{
		return result;
	}

	if(CheckSocketPort(s) != 0)
	{
		DecryptData((BYTE*)buf,result);
	}

	return result;
}

int WINAPI MySend(SOCKET s,char* buf,int len,int flags) // OK
{
	if(CheckSocketPort(s) != 0)
	{
		EncryptData((BYTE*)buf,len);
	}

	return HookSend(s,buf,len,flags);
}

_declspec(naked) void CheckTickCount1() // OK
{
	static DWORD CheckTickCountAddress1 = 0x004DA29B;

	_asm
	{
		Mov Dword Ptr Ss:[Ebp-0x68],0x00
		Mov Edx,MainTickCount
		Mov Dword Ptr Ss:[Ebp-0x74],Edx
		Call Dword Ptr Ds:[GetTickCount]
		Mov MainTickCount,Eax
		Mov SyncTickCount,Eax
		Jmp [CheckTickCountAddress1]
	}
}

#if(FPS_60 == 1)
_declspec(naked) void CheckTickCount2() // OK
{
	static DWORD CheckTickCountAddress1 = 0x004DA3F0;

	_asm
	{
		Pushad
		Pushfd
		Call UpdateFrameCount
		Popfd
		Popad
		Mov Ecx, Dword Ptr Ss : [Ebp - 0x6C]
		Mov CountModifier, Ecx
		Mov Edx, Dword Ptr Ss : [Ebp - 0x74]
		Mov DelayModifier, Edx
		Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
		Mov HasteModifier, Ecx
		Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
		Mov Ecx, Dword Ptr Ds : [Edx + 0x214]
		Mov SpeedModifier1, Ecx
		Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
		Mov Ecx, Dword Ptr Ds : [Edx + 0x218]
		Mov SpeedModifier2, Ecx
		Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
		Mov Ecx, Dword Ptr Ds : [Edx + 0x31A]
		Mov ModelModifier1, Ecx
		Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
		Mov Ecx, Dword Ptr Ds : [Edx + 0x394]
		Mov ModelModifier2, Ecx
		Mov Edx, Dword Ptr Ds : [MAIN_VIEWPORT_STRUCT]
		Mov Ecx, Dword Ptr Ds : [Edx + 0x398]
		Mov ModelModifier3, Ecx
		Mov Eax, MainTickCount
		Sub Eax, Dword Ptr Ss : [Ebp - 0x74]
		Mov Dword Ptr Ss : [Ebp - 0x68] , Eax
		Mov Eax, g_CurrentFrameCount //-- fps
		Cmp Dword Ptr Ss : [Ebp - 0x68] , Eax
		Jge CONTINUE
		Mov Ecx, g_CurrentFrameCount
		Sub Ecx, Dword Ptr Ss : [Ebp - 0x68]
		Mov Dword Ptr Ss : [Ebp - 0x18C] , Ecx
		Mov Edx, Dword Ptr Ss : [Ebp - 0x18C]
		Mov SleepModifier, Edx
		NEXT :
		Push 1
			Call Dword Ptr Ds : [Sleep]
			Call Dword Ptr Ds : [GetTickCount]
			Sub Eax, Dword Ptr Ss : [Ebp - 0x074]
			Cmp Eax, Dword Ptr Ss : [Ebp - 0x18C]
			Jl NEXT
			Mov Eax, MainTickCount
			Cmp SyncTickCount, Eax
			Jnz HACK
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x6C]
			Cmp CountModifier, Ecx
			Jnz HACK
			Mov Edx, Dword Ptr Ss : [Ebp - 0x74]
			Cmp DelayModifier, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
			Cmp HasteModifier, Ecx
			Jnz HACK
			Mov Edx, Dword Ptr Ss : [Ebp - 0x18C]
			Cmp SleepModifier, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [0x07BC4F04]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x214]
			Cmp SpeedModifier1, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [0x07BC4F04]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x218]
			Cmp SpeedModifier2, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [0x07BC4F04]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x31A]
			Cmp ModelModifier1, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [0x07BC4F04]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x394]
			Cmp ModelModifier2, Edx
			Jnz HACK
			Mov Ecx, Dword Ptr Ds : [0x07BC4F04]
			Mov Edx, Dword Ptr Ds : [Ecx + 0x398]
			Cmp ModelModifier3, Edx
			Jnz HACK
			Add Eax, Dword Ptr Ss : [Ebp - 0x18C]
			Mov MainTickCount, Eax
			Mov Eax, g_CurrentFrameCount //-- fps
			Mov Dword Ptr Ss : [Ebp - 0x68] , Eax
			CONTINUE :
		Mov Ecx, Dword Ptr Ss : [Ebp - 0x178]
			Add Ecx, Dword Ptr Ss : [Ebp - 0x68]
			Mov Dword Ptr Ss : [Ebp - 0x6C] , Ecx
			Jmp[CheckTickCountAddress1]
			HACK :
			Push 0
			Call Dword Ptr Ds : [ExitProcess] }
}
#endif

void InitHackCheck() // OK
{
	LoadFpsSettings();

	WORD EncDecKey = 0;

	for(int n=0;n < sizeof(gProtect.m_MainInfo.CustomerName);n++)
	{
		EncDecKey += (BYTE)(gProtect.m_MainInfo.CustomerName[n]^gProtect.m_MainInfo.ClientSerial[(n%sizeof(gProtect.m_MainInfo.ClientSerial))]);
	}

	EncDecKey1 = (BYTE)0xEE;
	EncDecKey2 = (BYTE)0xFF; // Default is 0x76

	EncDecKey1 += LOBYTE(EncDecKey);
	EncDecKey2 += HIBYTE(EncDecKey);

	HookRecv = *(WSRECV*)(0x00D227B0);

	HookSend = *(WSSEND*)(0x00D227F8);

	SetDword(0x00D227B0,(DWORD)&MyRecv);

	SetDword(0x00D227F8,(DWORD)&MySend);
}
