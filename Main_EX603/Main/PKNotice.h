#pragma once

#include "Protocol.h"

struct DATA_NOTICEPK
{
	int Delay;
	DWORD	Color;
	DWORD	Time;
	char	Mess[90];
};

struct PMSG_NOTICE_SEND
{
	PBMSG_HEAD header; // C1:0D
	BYTE type;
	BYTE count;
	BYTE opacity;
	WORD delay;
	DWORD color;
	BYTE speed;
	char message[256];
};


class PKNotice
{
public:
	PKNotice();

	
	void DrawNoticePKSystem();
	
	std::vector<DATA_NOTICEPK> m_DataNoticePK;
private:
}; extern PKNotice gPKNotice;
