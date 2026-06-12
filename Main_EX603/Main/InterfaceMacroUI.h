#pragma once
#include "Protocol.h"

#define MUHELPER_STRUC		0x00E8CB7C
#define PlayBuffer			((signed int(__cdecl*)(int a1, int a2, int a3)) 0x006D6C20)
#define RenderImage2		((int(__cdecl*)(int a1, float a2, float a3)) 0x00790C20)
#define pHelperMouseClick	((char(__thiscall*)(int a1)) 0x007D2920)

//**********************************************//
//********** Client -> ConnectServer ***********//
//**********************************************//

struct PMSG_SERVER_INFO_RECV
{
	PSBMSG_HEAD header; // C1:F4:03
	BYTE ServerCode;
};

struct PMSG_SERVER_LIST_RECV
{
	PSBMSG_HEAD header; // C1:F4:06
};

//**********************************************//
//********** ConnectServer -> Client ***********//
//**********************************************//

struct PMSG_SERVER_INFO_SEND
{
	PSBMSG_HEAD header; // C1:F4:03
	char ServerAddress[16];
	WORD ServerPort;
};

struct PMSG_SERVER_LIST_SEND
{
	PSWMSG_HEAD header; // C1:F4:06
	BYTE count[2];
};

struct PMSG_SERVER_LIST
{
	WORD ServerCode;
	BYTE UserTotal;
	BYTE type;
};

//**********************************************//
//********** Client -> GameServer **************//
//**********************************************//

struct JCCG_MOVESERVER_REQ
{
	PSBMSG_HEAD header; // C1:29:06
	WORD subcode;
};

class JCMacroUIEx
{
public:
	JCMacroUIEx();
	virtual ~JCMacroUIEx();
	void Load();
	static void JCFrameBar(int _this);
	void ServerInfoRecv(BYTE* a1, bool a2 = false);
	void ServerListRecv(BYTE* a1, bool a2 = false);
	void GJMapServerMoveSend(WORD subcode);
	static signed int CameraGuiReset();
public:
	DWORD EvtKeyState;
	int OpenLayer;
	int Server_List_num;
	PMSG_SERVER_LIST m_ServerList[50];
public:
	void ReqServerInfo(WORD subcode);
	void ReqServerList();
};

extern JCMacroUIEx JCExMacro;