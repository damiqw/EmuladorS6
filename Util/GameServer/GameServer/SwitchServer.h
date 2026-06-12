#pragma once

struct JCCG_MOVESERVER_REQ
{
	PSBMSG_HEAD header; // C1:29:06
	WORD subcode;
};


class gSwitchServer
{
public:
	gSwitchServer();
	~gSwitchServer();
	void SwitchServerReq(JCCG_MOVESERVER_REQ*, int);
};

extern gSwitchServer JCSwitchServer;