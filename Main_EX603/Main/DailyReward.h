#pragma once
#if (DAILY)
#include "InterfaceBase.h"
#include "Protocol.h"
#include "Object.h"
#include "Import.h"
#include "Interface.h"
#include "NewInterface.h"

#define cDR_SPLIT_DAY	7

struct PMSG_DAILY_REWARD_SEND
{
	PBMSG_HEAD2 h;
	BYTE Type;
	int  Value;
};

struct PMSG_DAILY_REWARD_USER_INFO_RECV
{
	PBMSG_HEAD2 h;
	BYTE MaxDay;
	BYTE CurDay;
	BYTE FWday;
	BYTE State[31];
	DWORD Timer;
};

struct PMSG_DAILY_REWARD_DAY_INFO_RECV
{
	PBMSG_HEAD2 h;
	short Type;
	BYTE Dur;
	BYTE Item[12];
	int  PeriodTime;
	int Wcoin;
	int Zen;
	char Text[100];
};

class cDailyReward : public cInterfaceBase
{
public:
	cDailyReward();
	~cDailyReward();
	void ToggleWindow(bool mode = false);
	void OpenWindow(bool mode = false);
	void CloseWindow(bool mode = false);
	void SetWindow(bool state, bool mode = false);
	void Init();
	void Draw();
	void OnOpen();
	void OnClose();
	bool AllowedGift();
	void ClearDayGift();
	void SendRequest(BYTE type, int value);
	void GCRecvUserInfo(BYTE* a);
	void GCRecvDayInfo(BYTE* a);
	int  CheckItemInfo(signed int a1);
	void DrawIcon();
	static void RecvGiftAction(LPVOID pClass);
	int Button(DWORD Event);

	bool	CheckJewelWindow()

	{
		return gInterface.Data[eMAIN_DailySystem].OnShow;
	};

	void	OpenJewelWindow()
	{
		gInterface.Data[eMAIN_DailySystem].OnShow = true;
	};

	void    CloseJewelWindow()
	{
		gInterface.Data[eMAIN_DailySystem].OnShow = false;
		pSetCursorFocus = false;
	};

	DWORD OpenDailyDelay;

	BYTE SelectedDay;
	BOOL Blink;
	BOOL Loaded;
	BOOL Checked;
	BOOL DayInfo;
	BYTE MaxDay;
	BYTE CurDay;
	BYTE FWday;
	BYTE State[31];
	DWORD Timer;
	ObjectItem Item;
	short Type;
	BYTE Level;
	BYTE Ex;
	int Wcoin;
	int Zen;
	char Text[100];
	DWORD TickCount;

	//
	bool  Moving;
	float ultimoX;
	float ultimoY;
	short mX;
	short mY;
	//

};

extern cDailyReward DailyReward;
#endif