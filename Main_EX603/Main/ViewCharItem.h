#pragma once
#include "Protocol.h"
#include "Object.h"

#define VIEWCHARITEMS TRUE
#if(VIEWCHARITEMS)

#define INVENTORY_ITEMS		12
#define vciMAX_ITEM_INFO	12

#define sub_637E80					((void(__cdecl*)(int x, float y, float w, float h, float giro, float a9, float a10, float a11, float a12, float a13))0x00637E80)
#define pSetItemOption				((void(__cdecl*)(ObjectItem * lpItem, BYTE Option, BYTE Special, BYTE Value)) 0x58B910)

struct PMSG_ANS_VIEW_CHAR_ITEMS
{
	PSWMSG_HEAD h;
	BYTE Result;
	BYTE Class;
	char Name[11];
	char Guild[9];
	BYTE Map;
	short Type[INVENTORY_ITEMS];
	BYTE Dur[INVENTORY_ITEMS];
	BYTE Item[INVENTORY_ITEMS][vciMAX_ITEM_INFO];
	int  PeriodTime[INVENTORY_ITEMS];
	BYTE mGuildMark[32];
	int GuildNumber;
};

struct CharItems
{
	BYTE Result;
	BYTE Map;
	char Guild[9];
	char Name[11];
	BYTE Class;
	ObjectItem Item[INVENTORY_ITEMS];
	BYTE mGuildMark[32];
	int GuildNumber;
};

class cViewCharItems
{
public:
	cViewCharItems();
	~cViewCharItems();
	void Init();
	void Load();
	void ClearSession();
	int CheckItemInfo(signed int a1);
	bool DrawCharInfoRanking(int X, int Y,int W,int H);
	bool IsWorkZone(WORD, WORD, WORD, WORD);
	bool IsWorkZoneDebug(WORD, WORD, WORD, WORD);
	void RecvInfo(PMSG_ANS_VIEW_CHAR_ITEMS *);
	bool getState() { return this->onView; }
	void setState(bool a1) { this->onView = a1; }
	void DrawItem3D(float sx, float sy, float Width, float Height, int Type, int Level, int ExtOption, int Ancient, bool PickUp, float Scale = 1.0f, bool Center = true);
	BOOL DrawItem3DCenterImage;
	CharItems charItem;
	bool onView;
	bool DangXem;
	DWORD ActionTime;
private:
	float Rot;
	float Zoom;
	float guiX;
	float guiY;
	short curX;
	short curY;
	
	bool  dragging;
	int Key;
};

extern cViewCharItems ViewCharItems;
#endif

char* CharacterCode2(int a);