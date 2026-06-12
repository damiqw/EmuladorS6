#pragma once
#include "Object.h"
#include "post_item.h"

#define MAX_RUUDTOKENSELL_INFO		25
#define CursorPress					*(BYTE*)0x8793386
#define MAX_ITEM_INFO				12

#define GetInfoByteItem				((int (__thiscall*)(int a1, void *lp)) 0x007E1B10)
#define EvtDrawMouse				((int(__cdecl*)(int VKBUTTON)) 0x00791090)
#define pGetItemAtt(id, offset)		(*(DWORD*)0x8128AC0 + 84 * id + offset) //1.04D || 1.04E may be -0x150
#define Convert							((double(__cdecl*)(float a1)) 0x004DB0C0)
#define sub_7E3E30 ((signed int (__thiscall*)(int a1, JCCoord a5, int a6, int a7, int a8, int a9)) 0x007E3E30)

//**********************************************//
//************ GameServer -> Client ************//
//**********************************************//

struct PMSG_RUUD_ITEM_LIST_RECV
{
	PWMSG_HEAD header; // C2:31
	BYTE type;
	BYTE count;
};

struct PMSG_RUUD_ITEM_LIST
{
	BYTE slot;
	DWORD dwRuudSell;
	BYTE ItemInfo[MAX_ITEM_INFO];
};

//**********************************************//
//************ Client -> GameServer ************//
//**********************************************//

struct PMSG_BUY_ITEMRUUD_SEND
{
	PBMSG_HEAD header; // EE:30
	BYTE PAGE;
	BYTE SLOT;
};

struct PMSG_NPC_TALK_RECV
{
	PBMSG_HEAD header; // C3:30
	BYTE result;
	BYTE level[7];
};

struct PMSG_NPC_TALK_SEND
{
	PBMSG_HEAD header; // C1:30
};
//--
struct RUUD_ITEM_LIST
{
	BYTE slot;
	DWORD RuudSell;
	ObjectItem ItemInfo;
};

class cRenderRuud
{
public:
	cRenderRuud(); 
	virtual ~cRenderRuud();
	float JCMoveX; // ST08_4@1
	float JCMoveY; // ST04_4@1
public:
	bool isOpen( );
	int CheckTimer;
	int Coordenada[3];
	bool OpeningRuud;
	bool OpenWindowConfirm;
	int JCSlot;
	int JCPage;
	void OpenRuud();
	void ClosedRuud();
	void CheckOpen();
	DWORD TimerEvent;
	bool EventPressButton(int x, int y, int w, int h);
public:
	bool CheckMouseOver( );
	void WindowConfirm( );
	void ClearRuudInfo();
	void InsertRuudInfo(PMSG_RUUD_ITEM_LIST* lpInfo1);
	void LoadRuudShop_Recv(PMSG_RUUD_ITEM_LIST_RECV * lpMsg);
	void OpenRuudShop_Recv(PMSG_NPC_TALK_RECV * lpMsg);
	void MoverWinRuud( int x, int y );
	//PMSG_RUUD_ITEM_LIST * JCGetInfoRuud(int Page, int Slot);
public:
	int Enter;
	int Page;

	std::map<int, RUUD_ITEM_LIST> lpInfo;
	PMSG_RUUD_ITEM_LIST m_RuudInfo[MAX_RUUDTOKENSELL_INFO];
};

extern cRenderRuud jCRenderRuud;