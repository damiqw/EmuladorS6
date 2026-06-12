#include "StdAfx.h"
#include "CustomPing.h"
#include "Common.h"
#include "Defines.h"
#include "Interface.h"
#include "Protect.h"
#include "Protocol.h"
#include "Util.h"
#include "ShowInfoItemDrop.h"
#include "CustomFont.h"
// -------------------------------------------------------------------------------

CCustomPing gCustomPing;
// -------------------------------------------------------------------------------

CCustomPing::CCustomPing()
{
	this->PingDelaySend = GetTickCount();
	this->PingDelaySend = 0;
	this->PingDelayRecv = -1;
	this->RealPingDelaySend = 0;
	this->RealPingDelayRecv = -1;
	this->m_fpscount = 0;
	this->m_fps = 0;
	this->TickCount = GetTickCount();
	this->m_fpscount2 = 0;
	this->m_fps2 = 0;
	this->TickCount2 = GetTickCount();
	this->PingStart = 0;
}
// -------------------------------------------------------------------------------

CCustomPing::~CCustomPing()
{
	// ----
}

void CCustomPing::ShowPing()
{

	if (gInterface.MiniMapCheck() || gInterface.CombinedChecks())
	{
		return;
	}

	if ((int)this->RealPingDelayRecv >= 0)
	{
		pSetBlend(1);
		glColor4f(0.0, 0.0, 0.0, 0.8);
		//pDrawBarForm((float)490, (float)0, 150.0f, 15.0f, 0.0f, 0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor4f(1.0, 1.0, 1.0, 1.0);

		pSetBlend(1);

		DWORD elapsed = GetTickCount() - this->TickCount;

		this->m_fpscount++;

		// one second elapsed? (= 1000 milliseconds)
		if (elapsed > 1000)
		{
			// save the current counter value to m_fps
			this->m_fps = m_fpscount;
			// reset the counter and the interval
			this->m_fpscount = 0;
			// set tick count
			this->TickCount = GetTickCount();
		}

		char result; // al@2
		float y; // ST08_4@5
		float x; // ST04_4@5
		signed int v13; // ST18_4@7
		float v39; // ST64_4@25
		signed int v42; // [sp+20h] [bp-50h]@23
		int v43; // [sp+54h] [bp-1Ch]@1
		int v44; // [sp+5Ch] [bp-14h]@7
		int v45; // [sp+68h] [bp-8h]@5
		int i; // [sp+6Ch] [bp-4h]@3

		v43 = *(DWORD*)(GetInstance() + 104);
		if (gProtect.m_MainInfo.CustomInterfaceType == 0)
		{
			x = (double)(*(DWORD*)(v43 + 16) + *(DWORD*)(v43 + 24));
		}
		else if (gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			x = (double)(*(DWORD*)(v43 + 16) + *(DWORD*)(v43 + 24));
		}
		else if (gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			x = (double)(*(DWORD*)(v43 + 16) + *(DWORD*)(v43 + 24));
		}

		/*CustomFont.Draw(CustomFont.FontNormal, x - 63, 1, 0, 200, 140, 15, 1, " ");*/

		//gInterface.DrawFormat(eGold, x - 60, 4, 100, 1, "RTT: %d ms", this->RealPingDelayRecv);

		//gInterface.DrawFormat(eGold, x - 10, 4, 100, 1, "PING: %d ms", this->PingDelayRecv);

		//gInterface.DrawFormat(eGold, x + 40, 4, 100, 1, "FPS: %d", this->m_fps);


	}
}

void CCustomPing::PingRecv()
{
	this->RealPingDelayRecv = (GetTickCount() - this->RealPingDelaySend) + 1;
}

void CCustomPing::PingSend()
{

	this->RealPingDelaySend = GetTickCount();

	PMSG_PING_SEND lpMsg;

	lpMsg.header.set(0xF3, 0xF1, sizeof(lpMsg));

	DataSend((LPBYTE)&lpMsg, lpMsg.header.size);

}

void PingTest(LPVOID lpThreadParameter)
{
	while (TRUE)
	{
		gCustomPing.PingSend();

		SOCKET m_socket;

		m_socket = socket(PF_INET, SOCK_STREAM, 0);

		if (m_socket == INVALID_SOCKET)
		{
			return;
		}

		SOCKADDR_IN target;

		target.sin_family = AF_INET;
		target.sin_port = htons(gProtect.m_MainInfo.IpAddressPort);
		target.sin_addr.s_addr = inet_addr(gProtect.m_MainInfo.IpAddress);

		if (target.sin_addr.s_addr == INADDR_NONE)
		{
			HOSTENT* host = gethostbyname(gProtect.m_MainInfo.IpAddress);

			if (host != 0)
			{
				memcpy(&target.sin_addr.s_addr, (*host->h_addr_list), host->h_length);
			}
		}

		gCustomPing.PingDelaySend = GetTickCount();

		if (connect(m_socket, (SOCKADDR*)&target, sizeof(target)) != SOCKET_ERROR)
		{
			gCustomPing.PingDelayRecv = GetTickCount() - gCustomPing.PingDelaySend + 1;

			Sleep(100);

			closesocket(m_socket);
			m_socket == INVALID_SOCKET;
		}

		Sleep(5000);
		//char* msg = "C1";
		//int result = send(m_socket, msg, strlen(msg), 0);
	}
}

void CCustomPing::StartPing()
{
	if (this->PingStart == 1)
		return;

	//if(gProtect.m_MainInfo.PingTest == 1)
	//{
		//if(DisablePing != 1)
		//{
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PingTest, 0, 0, 0);
	//}
//}
	this->PingStart = 1;
}