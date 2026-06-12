#pragma once
#include "stdafx.h"
#include "Protocol.h"
#include "Import.h"
#include "Interface.h"

#define MAX_RANK 50

struct PMSG_CUSTOM_RANKING_RECV
{
	PSWMSG_HEAD h;
	int index;
	char rankname[20];
	char col1[20];
	char col2[20];
	int count;
};

struct PMSG_CUSTOM_RANKING_COUNT_RECV
{
	PSBMSG_HEAD header; // C1:BF:51
	int count;
};

struct PMSG_CUSTOM_RANKING_COUNT_SEND
{
	PSBMSG_HEAD header; // C1:BF:51
};

struct PMSG_CUSTOM_RANKING_SEND
{
	PSBMSG_HEAD header; // C1:BF:51
	BYTE type;
};

struct CUSTOM_RANKING_DATA
{
	char szName[20];
	char value2[60];
#if(CUSTOM_BRANKINGNEW)
	bool CheckOnline;
#endif
};
#if(CUSTOM_BRANKINGNEW)
struct DATA_VIEWTOPRANKING
{
	PSWMSG_HEAD header;
	char NameChar[11];
	char GuildName[11];
	BYTE GuildMark[32];
	DWORD TongPoint;
	DWORD Reset;
	DWORD Level;
	DWORD MasterLevel;
	//DWORD LucChien;
	BYTE Item[12][16];
	int aIndex;
	BYTE Class;
};
struct REQUESTINFO_CHARTOP
{
	PSBMSG_HEAD header; // C3:F3:03
	char NameChar[11];
	int aIndex;
};
#endif

struct RANK_INFO_SEND
{
	char NameRank[128];
};

struct PMSG_RANK_INFO
{
	PWMSG_HEAD2 h;
	RANK_INFO_SEND Info[MAX_RANK];
};

class CCustomRanking
{
public:
	CCustomRanking();

	void		OPEN_WINDOW_RANKING() { gInterface.Data[eRankPANEL_MAIN].OnShow ^= true; pSetCursorFocus ^= true; gInterface.Data[eRankPANEL_MAIN].FirstLoad = true; *(BYTE*)0xE8C5AC ^= 1; };
	void		CLOSE_WINDOW_RANKING() { gInterface.Data[eRankPANEL_MAIN].OnShow = false; pSetCursorFocus = false; };
	bool		CHECK_WINDOW_RANKING() { return gInterface.Data[eRankPANEL_MAIN].OnShow; };
	void RankNameRev(PMSG_RANK_INFO* lpMsg);
	RANK_INFO_SEND m_RankInfo[MAX_RANK];
	void ClearCustomRanking();
	void GCReqRanking(PMSG_CUSTOM_RANKING_RECV* lpMsg);
	void GCReqRankingCount(PMSG_CUSTOM_RANKING_COUNT_RECV* lpMsg);
	void DrawRankPanelWindow();
	bool EventRankingNext(DWORD Event);
	bool EventRankingBack(DWORD Event);
	int RankingType;
	int RankEnable;
	int RankingCount;
	bool EventRankingWindow_Close(DWORD Event);
	bool EventVipWindow_Close(DWORD Event);
	void OpenWindow();
	int count;
	std::vector<std::string> mListRanking;
#if(CUSTOM_BRANKINGNEW)
	DATA_VIEWTOPRANKING CacheDataUserTop;
	void GCReqInfoCharTop(DATA_VIEWTOPRANKING* lpMsg);
	bool CacheUserRank;
	bool SetItemCharTop;
#endif

	bool CheckTestWindow()
	{
		return gInterface.Data[eRankPANEL_MAIN].OnShow;
	};

	void	OpenTestWindow()
	{
		gInterface.Data[eRankPANEL_MAIN].OnShow = true; *(DWORD*)0xE8CB3C = true;
	};

	void    CloseTestWindow()
	{
		gInterface.Data[eRankPANEL_MAIN].OnShow = false; *(DWORD*)0xE8CB3C = false;
	};

	DWORD OpenTestDelay;

	int SelectBarRankingNumber;
private:
	char rankname[20];
	char col1[20];
	char col2[20];
	CUSTOM_RANKING_DATA gCustomRanking[MAX_RANK];
	int RankLoad;

};
extern CCustomRanking gCustomRanking;



