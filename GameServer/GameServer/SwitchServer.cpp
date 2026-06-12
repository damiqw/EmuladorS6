#include "stdafx.h"
#include "Protocol.h"
#include "SwitchServer.h"
#include "JSProtocol.h"

gSwitchServer JCSwitchServer;

gSwitchServer::gSwitchServer()
{
}

gSwitchServer::~gSwitchServer()
{
}

void gSwitchServer::SwitchServerReq(JCCG_MOVESERVER_REQ* lpMsg, int aIndex)
{
	LPOBJ lpObj = &gObj[aIndex];

	if (gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	GJMapServerMoveSend(lpObj->Index, lpMsg->subcode, lpObj->Map, (BYTE)lpObj->X, (BYTE)lpObj->Y);
}