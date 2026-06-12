#pragma once


#if(NEW_POSTITEM)
#include "Object.h"
#include "Protocol.h"

#define		DELAY_POST_ITEM		3000
#define		MAX_MESSAGES		200
#define		CHAT_TYPE_START		11

#define MAX_ITEM_INDEX     512

//item index
#define ITEM_SWORD		 (0)
#define ITEM_AXE		 (1*MAX_ITEM_INDEX)
#define ITEM_MACE		 (2*MAX_ITEM_INDEX)
#define ITEM_SPEAR		 (3*MAX_ITEM_INDEX)
#define ITEM_BOW		 (4*MAX_ITEM_INDEX)
#define ITEM_STAFF		 (5*MAX_ITEM_INDEX)
#define ITEM_SHIELD		 (6*MAX_ITEM_INDEX) 
#define ITEM_HELM		 (7*MAX_ITEM_INDEX)
#define ITEM_ARMOR		 (8*MAX_ITEM_INDEX)
#define ITEM_PANTS		 (9*MAX_ITEM_INDEX)
#define ITEM_GLOVES		 (10*MAX_ITEM_INDEX)
#define ITEM_BOOTS		 (11*MAX_ITEM_INDEX)
#define ITEM_WING		 (12*MAX_ITEM_INDEX)
#define ITEM_HELPER		 (13*MAX_ITEM_INDEX)
#define ITEM_POTION  	 (14*MAX_ITEM_INDEX)
#define ITEM_ETC 		 (15*MAX_ITEM_INDEX)

struct JCCoord
{
	int X;
	int Y;
};

#define sub_7E3E30 ((signed int (__thiscall*)(int a1, JCCoord a5, int a6, int a7, int a8, int a9)) 0x007E3E30)

enum ItemNameColor {
	TEXT_COLOR_WHITE = 0,
	TEXT_COLOR_BLUE = 1,
	TEXT_COLOR_RED = 2,
	TEXT_COLOR_YELLOW = 3,
	TEXT_COLOR_GREEN = 4,
	TEXT_COLOR_DARKRED = 5,
	TEXT_COLOR_PURPLE = 6,
	TEXT_COLOR_DARKBLUE = 7,
	TEXT_COLOR_DARKYELLOW = 8,
	TEXT_COLOR_GREEN_BLUE = 9,
	TEXT_COLOR_GRAY = 10,
	TEXT_COLOR_REDPURPLE = 11,
	TEXT_COLOR_VIOLET = 12,
	TEXT_COLOR_ORANGE = 13
};

struct PostItem_struct
{
	ObjectItem item;
	short ClrType;
	char Author[11];
	char ItemName[64];
	char suf[35];
	//smt else
};

struct PMSG_POSTITEM_SEND {
	PBMSG_HEAD h;
	int  pos;
	char pre[35];
	char suf[35];
};

struct PMSG_POSTITEM_RECV
{
	PBMSG_HEAD header;
	char chatid[11];
	char pre[35];
	char suf[35];
	short Type;
	BYTE Dur;
	BYTE Item[12];
	int  PeriodTime;
};

struct PMSG_POSTITEM
{
	PBMSG_HEAD h;
	char chatid[11];    //  3
	char chatmsg[60];   //  D
	char item_data[107];
};

#if(RIGHT_CLICK)
struct PMSG_ITEM_MOVE_RECV
{
	PSBMSG_HEAD h;
	BYTE sFlag;
	BYTE tFlag;
	BYTE Source;
	BYTE Target;
};
#endif

class PostItem
{
public:
	PostItem();
	virtual ~PostItem();

	void Hook();
	void PostItemProc(DWORD);
	void CGPostItem(DWORD, const char*, const char*);
	void GCPostItem(BYTE* a);
	void ClearPostItem();
	void SetColor(int type);
	void RenderItem();
	int CheckItemInfo(int);
	static void HookSendChat(const char*);
	static bool HookRenderFrame(int);
	static bool ViewPostItem(int type);
	static void RenderPostItemName(int x, int y, int type, int width);
	static int 	RenderText(int PosX, int PosY, LPCTSTR Text, int Width, int Height, LPINT Align, OUT SIZE* lpTextSize);
	PostItem_struct Posts[MAX_MESSAGES];
	HFONT	FontUnderLine;
	int		viewing;
	int		minX;
	int		maxX;
	DWORD last_tickcount_post_;
	DWORD last_tickcount_moveitem_;
	void CDActionItem(void* item_data);

	static void Equipments();
	static void RemoveEquipment(void* item_data);

private:
	int	  IndexCount;
	DWORD lastPostTickCount;

};

#endif

extern PostItem JCItemPublic;