#pragma once
#include "Protocol.h"

struct PMSG_QUICK_COMMAND_SEND
{
	PBMSG_HEAD2 h;
	BYTE Type;
	int  Value;
	char Name[11];
};

class cQuickCommand
{
public:
	cQuickCommand();
	~cQuickCommand();
	void Load();
	void DrawFrame(float x, float y, int target);
	bool IsWorkZone(float x, float y, float x2, float y2, bool mode = false);
	void ClearMouseBlock();
	bool GetMouseBlock();
	bool Action();
	void SendRequest(BYTE type, int value, char* name);
private:
	int m_iSelectedIndex;
	int m_target;
};
extern cQuickCommand QuickCommand;