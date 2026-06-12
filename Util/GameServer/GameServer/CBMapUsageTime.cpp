#include "StdAfx.h"
#include "CBMapUsageTime.h"
#include "Map.h"
#include "MemScript.h"
#include "Notice.h"
#include "Util.h"
#include "DSProtocol.h"

CB_MapUsageTime gCB_MapUsageTime;

CB_MapUsageTime::CB_MapUsageTime()
{
}


CB_MapUsageTime::~CB_MapUsageTime()
{
}
char* CB_MapUsageTime::GetMessage(int index) // OK
{
	std::map<int, MESSAGE_INFO_MAPUSAGETIME>::iterator it = this->m_MessageInfoBP.find(index);

	if (it == this->m_MessageInfoBP.end())
	{
		char Error[256];
		wsprintf(Error, "Could not find message %d!", index);
		return Error;
	}
	else
	{
		return it->second.Message;
	}
}

void CB_MapUsageTime::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_MessageInfoBP.clear();

	this->m_DataMapList.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					MESSAGE_INFO_MAPUSAGETIME info;

					info.Index = lpMemScript->GetNumber();

					strcpy_s(info.Message,lpMemScript->GetAsString());

					this->m_MessageInfoBP.insert(std::pair<int, MESSAGE_INFO_MAPUSAGETIME>(info.Index, info));

				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					DATA_MAPLIST_MAPUSAGETIME info;

					info.IDMap = lpMemScript->GetNumber();

					info.UseItemIndex = lpMemScript->GetAsNumber();

					info.UseItemLevel = lpMemScript->GetAsNumber();
					
					info.UseItemCount = lpMemScript->GetAsNumber();
					
					info.UseWC = lpMemScript->GetAsNumber();
					
					info.UseWP = lpMemScript->GetAsNumber();
					
					info.UseGP = lpMemScript->GetAsNumber();

					info.UseRuud = lpMemScript->GetAsNumber();
					
					info.TimeAdd = lpMemScript->GetAsNumber();
					
					this->m_DataMapList.insert(std::pair<int, DATA_MAPLIST_MAPUSAGETIME>(info.IDMap, info));
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

DATA_MAPLIST_MAPUSAGETIME* CB_MapUsageTime::GetInfoMapUsageTime(int MapID)
{
	std::map<int, DATA_MAPLIST_MAPUSAGETIME>::iterator it = this->m_DataMapList.find(MapID);

	if (it != this->m_DataMapList.end())
	{
		return &it->second;
	}
	return 0;
}


void CB_MapUsageTime::CheckMapUsageTime(int aIndex)
{
	//if (this->Enable == 0)
	//{
	//	return;
	//}
	if (OBJECT_RANGE(aIndex) == 0)
	{
		return;
	}

	if (gObjIsConnected(aIndex) == 0)
	{
		return;
	}
	LPOBJ lpObj = &gObj[aIndex];
	int MapNumber = lpObj->Map;
	
	
	if (lpObj->Type != OBJECT_USER || lpObj->State != OBJECT_PLAYING)
	{
		return;
	}

	DATA_MAPLIST_MAPUSAGETIME* GetInfoIsMap = CB_MapUsageTime::GetInfoMapUsageTime(MapNumber);
	if (!GetInfoIsMap) return;

	if (lpObj->MapUsageTime[MapNumber] < 1)
	{
		//===CHeck Item
		if (GetInfoIsMap->UseItemIndex != -1 && GetInfoIsMap->UseItemCount > 0)
		{
			int CheckCountItem = gItemManager.GetInventoryItemCount(lpObj, GetInfoIsMap->UseItemIndex, GetInfoIsMap->UseItemLevel);
			if (CheckCountItem < GetInfoIsMap->UseItemCount)
			{
				gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(0), GetInfoIsMap->UseItemCount,gItemManager.GetItemName1(GetInfoIsMap->UseItemIndex,GetInfoIsMap->UseItemLevel));
				gObjMoveGate(aIndex, 17); //move ve lorencia
				return;
			}
		}

		//===Check Coin
		if (GetInfoIsMap->UseWC > lpObj->Coin1)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(0), GetInfoIsMap->UseWC, "WC");
			gObjMoveGate(aIndex, 17); //move ve lorencia
			return;
		}
		if (GetInfoIsMap->UseWP > lpObj->Coin2)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(0), GetInfoIsMap->UseWP, "WP");
			gObjMoveGate(aIndex, 17); //move ve lorencia
			return;
		}
		if (GetInfoIsMap->UseGP > lpObj->Coin3)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(0), GetInfoIsMap->UseGP, "GP");
			gObjMoveGate(aIndex, 17); //move ve lorencia
			return;
		}
		if (GetInfoIsMap->UseRuud > lpObj->Ruud)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(0), GetInfoIsMap->UseRuud, "Ruud");
			gObjMoveGate(aIndex, 17); //move ve lorencia
			return;
		}

		//===Tru Item va Tru Coin
		if (GetInfoIsMap->UseItemIndex != -1 && GetInfoIsMap->UseItemCount > 0)
		{
			lpObj->ChaosLock = 1;
			gItemManager.DeleteInventoryItemCount(lpObj, GetInfoIsMap->UseItemIndex, GetInfoIsMap->UseItemLevel, GetInfoIsMap->UseItemCount);
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(1), GetInfoIsMap->UseItemCount, gItemManager.GetItemName1(GetInfoIsMap->UseItemIndex,GetInfoIsMap->UseItemLevel));
			lpObj->ChaosLock = 0;
		}
		if (GetInfoIsMap->UseWC > 0 || GetInfoIsMap->UseWP > 0 || GetInfoIsMap->UseGP > 0 || GetInfoIsMap->UseRuud > 0)
		{
			GDSetCoinSend(lpObj->Index, -(GetInfoIsMap->UseWC), -(GetInfoIsMap->UseWP), -(GetInfoIsMap->UseGP), -(GetInfoIsMap->UseRuud), "MapUsage");
		}

		lpObj->MapUsageTime[MapNumber] += GetInfoIsMap->TimeAdd;
		gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(2), GetInfoIsMap->TimeAdd);
		lpObj->MapUageTimeSend = 0;
	}
	else
	{
		lpObj->MapUsageTime[MapNumber]--;
		if (lpObj->MapUsageTime[MapNumber] ==  5 || lpObj->MapUsageTime[MapNumber] == 10 || lpObj->MapUsageTime[MapNumber] == 15)
		{
			gNotice.GCNoticeSend(aIndex, 1, 0, 0, 0, 0, 0, this->GetMessageA(3));
		}
	}

	if (GetTickCount() > lpObj->MapUageTimeSend +5000)
	{
		lpObj->MapUageTimeSend = GetTickCount();
		//===Send Info Ve Client
	//===========Send Info
		MAPUSAGETIME_INFO pMsg;
		pMsg.header.set(0xD3, 0x41, sizeof(pMsg));
		pMsg.Map = MapNumber;
		pMsg.Time = (DWORD)lpObj->MapUsageTime[MapNumber];//Time
		DataSend(aIndex, (BYTE*)& pMsg, pMsg.header.size);
		//==========		

	}

}