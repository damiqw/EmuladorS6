// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CashShop.h"
#include "CustomBuyVip.h"
#include "DSProtocol.h"
#include "JSProtocol.h"
#include "Util.h"
#include "MemScript.h"
#include "Message.h"
#include "Notice.h"

CCustomBuyVip gCustomBuyVip;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomBuyVip::CCustomBuyVip() // OK
{
	this->m_CustomBuyVipInfo.clear();
}

CCustomBuyVip::~CCustomBuyVip() // OK
{

}

void CCustomBuyVip::Init() // OK
{
	this->m_CustomBuyVipInfo.clear();
}

void CCustomBuyVip::Load(char* path) // OK
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

	this->Init();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			CUSTOM_BUYVIP_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.Exp = lpMemScript->GetAsNumber();

			info.Drop = lpMemScript->GetAsNumber();

			info.Days = lpMemScript->GetAsNumber();

			info.Coin1 = lpMemScript->GetAsNumber();

			info.Coin2 = lpMemScript->GetAsNumber();

			info.Coin3 = lpMemScript->GetAsNumber();

			strcpy_s(info.VipName,lpMemScript->GetAsString());

			this->m_CustomBuyVipInfo.insert(std::pair<int, CUSTOM_BUYVIP_INFO>(info.Index, info));
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomBuyVip::BuyVip(int aIndex,BUYPREMIUM_REQ* lpMsg)
{
	LPOBJ lpObj = &gObj[aIndex];

	if(gObjIsConnectedGP(aIndex) == 0)
	{
		return;
	}

	if(lpObj->PShopOpen != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(43));
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gNewMessage.GetTextMessage(43, lpObj->Language));
		return;
	}

	if (lpMsg->VipType < 1 || lpMsg->VipType > 3)
	{
		return;
	}

	if (lpMsg->VipType < lpObj->AccountLevel)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(759));
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gNewMessage.GetTextMessage(759, lpObj->Language));
		return;
	}

	lpObj->BuyVip = lpMsg->VipType;
	gCashShop.CGCashShopPointRecv(lpObj->Index);
}

void CCustomBuyVip::BuyVipDone(LPOBJ lpObj)
{
	if(gObjIsConnectedGP(lpObj->Index) == 0)
	{
		return;
	}

	if(lpObj->PShopOpen != 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(43));
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gNewMessage.GetTextMessage(43, lpObj->Language));
		return;
	}

	if (lpObj->BuyVip < 1 || lpObj->BuyVip > 3)
	{
		return;
	}

	if (lpObj->BuyVip < lpObj->AccountLevel)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(759));
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gNewMessage.GetTextMessage(759, lpObj->Language));
		return;
	}

	std::map<int, CUSTOM_BUYVIP_INFO>::iterator VipInfo = this->m_CustomBuyVipInfo.find(lpObj->BuyVip - 1);

	if (lpObj->Coin1 < VipInfo->second.Coin1 || lpObj->Coin2 < VipInfo->second.Coin2 || lpObj->Coin3 < VipInfo->second.Coin3)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(757));
		//gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gNewMessage.GetTextMessage(757, lpObj->Language));
		return;
	}

	LogAdd(LOG_EVENT,"[%s][%s] BuyVip (Level: %d)",lpObj->Account,lpObj->Name,lpObj->BuyVip);

	GDSetCoinSend(lpObj->Index, -(VipInfo->second.Coin1), -(VipInfo->second.Coin2), -(VipInfo->second.Coin3), 0,"BuyVip");

	GJAccountLevelSaveSend(lpObj->Index,lpObj->BuyVip,VipInfo->second.Days*86400);
	GJAccountLevelSend(lpObj->Index);

	gCashShop.CGCashShopPointRecv(lpObj->Index);

	gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(758),VipInfo->second.VipName);

	lpObj->BuyVip = 0;
}

void CCustomBuyVip::ReloadBuyVipInterface() // OK
{
	for (int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
	{
		if (gObjIsConnectedGP(n) != 0)
		{
			this->GCBuyVipSend(n);
		}
	}
}

bool CCustomBuyVip::GCBuyVipSend(int aIndex) // OK
{
	BYTE send[2048];

	PMSG_BUYVIP_LIST_SEND pMsg;

	pMsg.header.set(0xF3, 0xFB, 0);

	int size = sizeof(pMsg);

	pMsg.count = 0;

	PMSG_BUYVIP_LIST info;

	for (std::map<int, CUSTOM_BUYVIP_INFO>::iterator it = this->m_CustomBuyVipInfo.begin(); it != this->m_CustomBuyVipInfo.end(); it++)
	{
		info.Index = it->second.Index;

		info.Exp = it->second.Exp;

		info.Drop = it->second.Drop;

		info.Days = it->second.Days;

		info.Coin1 = it->second.Coin1;

		info.Coin2 = it->second.Coin2;

		info.Coin3 = it->second.Coin3;

		memcpy(info.VipName, it->second.VipName, sizeof(info.VipName));

		memcpy(&send[size], &info, sizeof(info));
		size += sizeof(info);

		pMsg.count++;
	}

	pMsg.header.size[0] = SET_NUMBERHB(size);
	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send, &pMsg, sizeof(pMsg));

	DataSend(aIndex, send, size);

	return 1;
}