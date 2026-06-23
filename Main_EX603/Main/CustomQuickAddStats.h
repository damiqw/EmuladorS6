#pragma once

#include "Protocol.h"
#include "Interface.h"
#if(QuickAddStats)

class QuickAddStats
{
public:
	QuickAddStats();
	~QuickAddStats();
	void Draw();
	void OpenStatsSTRWindow();
	void OpenStatsAGIWindow();
	void OpenStatsVITWindow();
	void OpenStatsENEWindow();
	void OpenStatsCMDWindow();
	void DrawStatsAddWindow_STR();
	void DrawStatsAddWindow_AGI();
	void DrawStatsAddWindow_VIT();
	void DrawStatsAddWindow_ENE();
	void DrawStatsAddWindow_CMD();
	void EventStatsAddWindow_STR(DWORD Event);
	void EventStatsAddWindow_AGI(DWORD Event);
	void EventStatsAddWindow_VIT(DWORD Event);
	void EventStatsAddWindow_ENE(DWORD Event);
	void EventStatsAddWindow_CMD(DWORD Event);
	// ----
	void		CloseStatsAddWindow_STR() { gInterface.Data[eSTATSADD_MAIN_STR].OnShow = false; };
	void		CloseStatsAddWindow_AGI() { gInterface.Data[eSTATSADD_MAIN_AGI].OnShow = false; };
	void		CloseStatsAddWindow_VIT() { gInterface.Data[eSTATSADD_MAIN_VIT].OnShow = false; };
	void		CloseStatsAddWindow_ENE() { gInterface.Data[eSTATSADD_MAIN_ENE].OnShow = false; };
	void		CloseStatsAddWindow_CMD() { gInterface.Data[eSTATSADD_MAIN_CMD].OnShow = false; };


private:

}; 
extern QuickAddStats gQuickAddStats;
#endif