#pragma once

#include "stdafx.h"
#include "Protocol.h"
#include "Interface.h"
#include "Import.h"

extern int ButtonReset;
extern int ButtonMasterReset;
extern int ButtonActive;
extern int ButtonDaily;

class cAntiLagSystem
{
public:
	cAntiLagSystem();
	~cAntiLagSystem();

	void Init();
	void Load();
	void Draw();

	int ActivePage;
	int ActiveSend;
	int FreePoint;
	bool Click;
	int PointX;
	bool m_Loaded;

	bool CheckTestWindow()
	{
		return gInterface.Data[eADDPOINT_MAIN].OnShow;
	};

	void	OpenTestWindow()
	{
		gInterface.Data[eADDPOINT_MAIN].OnShow = true; pSetCursorFocus = true;
	};

	void    CloseTestWindow()
	{
		gInterface.Data[eADDPOINT_MAIN].OnShow = false; pSetCursorFocus = false;
	};
	DWORD OpenTestDelay;
	//

	bool		EventUsersPanelAntiLag_CLOSE(DWORD Event);

	int         testFunctionInvItem;
	int			testFunctionInvItem2;
	int			testFunctionInvItem3;
	int			testFunctionInvItem4;
	int			testFunctionInvItem5;
	int			testFunctionInvItem6;
	int			testFunctionInvItem7;
	int			testFunctionInvItem8;
	int			testFunctionInvItem9;
	int			testFunctionInvItem10;
	int			testFunctionInvItem11;
	int			testFunctionInvItem12;
	int			testFunctionInvItem13;

};
extern cAntiLagSystem gAntiLagSystem;
