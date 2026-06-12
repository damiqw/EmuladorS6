#pragma once

#include "Protocol.h"

extern int BauID;
extern int BauQtd;
extern BYTE BauLock;

void BauLoad();

struct PMSG_WAREHOUSEINFO_RECV
{
	PSBMSG_HEAD	header;
	int BauID;
	int BauQtd;
	BYTE BauLock;
};

struct PMSG_WAREHOUSE_CHANGE_SEND
{
	PSBMSG_HEAD header;
	int BauID;
};

class CWarehouse
{
public:
	void StorageLoad();
	static void StorageBauTitle(char* a, char* b, char* c, int d);
	void ButtonsDraw();
	bool ButtonClick_Event(DWORD Event, int ObjectId);
	bool ButtonEvent_Main(DWORD Event);
	void CGWarehouseIDSend(int BauID);
	void GCReqWarehouseUserCountRecv(PMSG_WAREHOUSEINFO_RECV* lpMsg);
};
extern CWarehouse gWarehouse;