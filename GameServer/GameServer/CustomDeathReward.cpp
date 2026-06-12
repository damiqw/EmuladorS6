#include "stdafx.h"
#include "MemScript.h"
#include "Util.h"
#include "CustomDeathReward.h"
#include "Cashshop.h"
#include "Notice.h"
#include "Message.h"

CCustomDeathReward gCustomDeathReward;

CCustomDeathReward::CCustomDeathReward()
{
	this->m_CustomDeathRewardInfo.clear();
}

CCustomDeathReward::~CCustomDeathReward()
{

}

void CCustomDeathReward::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_CustomDeathRewardInfo.clear();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			REWARD_ZONE_INFO info;

			info.map = lpMemScript->GetNumber();

			info.startX = lpMemScript->GetAsNumber();

			info.startY = lpMemScript->GetAsNumber();

			info.endX = lpMemScript->GetAsNumber();

			info.endY = lpMemScript->GetAsNumber();

			info.zen = lpMemScript->GetAsNumber();

			info.coin1 = lpMemScript->GetAsNumber();

			info.coin2 = lpMemScript->GetAsNumber();

			info.coin3 = lpMemScript->GetAsNumber();

			info.ruud = lpMemScript->GetAsNumber();

			info.pktype = lpMemScript->GetAsNumber();

			this->m_CustomDeathRewardInfo.push_back(info);
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CCustomDeathReward::CheckRewardZone(LPOBJ lpObj, LPOBJ lpTarget)
{
	for (std::vector<REWARD_ZONE_INFO>::iterator it = this->m_CustomDeathRewardInfo.begin(); it != this->m_CustomDeathRewardInfo.end(); it++)
	{
		if (it->pktype == 1)
		{
			if (lpObj->PKLevel < 6)
			{
				return;
			}
		}
		else if (it->pktype == 2)
		{
			if (lpObj->PKLevel > 6)
			{
				return;
			}
		}
		if (lpObj->Map != it->map) 
		{
			continue;
		}

		if (lpObj->X >= it->startX && lpObj->Y >= it->startY
			&& lpObj->X <= it->endX && lpObj->Y <= it->endY
			&& lpTarget->X >= it->startX && lpTarget->Y >= it->startY
			&& lpTarget->X <= it->endX && lpTarget->Y <= it->endY) 
		{
			DWORD zen_value = lpObj->Money / 100 * it->zen;

			DWORD coin1_value = lpObj->Coin1 / 100 * it->coin1;

			DWORD coin2_value = lpObj->Coin2 / 100 * it->coin2;

			DWORD coin3_value = lpObj->Coin3 / 100 * it->coin3;

			DWORD ruud_value = lpObj->Ruud / 100 * it->ruud;

			if (lpTarget->Money + zen_value > MAX_MONEY)
			{
				zen_value = MAX_MONEY - lpTarget->Money;
			}

			if (zen_value != 0)
			{
				lpObj->Money -= zen_value;
				lpTarget->Money += zen_value;

				GCMoneySend(lpObj->Index, lpObj->Money);
				GCMoneySend(lpTarget->Index, lpTarget->Money);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(498), zen_value);
				gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(499), zen_value);
			}

			else if (coin1_value != 0)
			{
				lpObj->Coin1 -= coin1_value;
				lpTarget->Coin1 += coin1_value;

				gCashShop.GDCashShopAddPointSaveSend(lpObj->Index, 0, lpObj->Coin1, 0, 0,0);
				gCashShop.GDCashShopAddPointSaveSend(lpTarget->Index, 0, lpTarget->Coin1, 0, 0,0);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(500), coin1_value);
				gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(501), coin1_value);
			}

			else if (coin2_value != 0)
			{
				lpObj->Coin2 -= coin2_value;
				lpTarget->Coin2 += coin2_value;

				gCashShop.GDCashShopAddPointSaveSend(lpObj->Index, 0, 0, lpObj->Coin2, 0,0);
				gCashShop.GDCashShopAddPointSaveSend(lpTarget->Index, 0, 0, lpTarget->Coin2, 0,0);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(502), coin2_value);
				gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(503), coin2_value);
			}

			else if (coin3_value != 0)
			{
				lpObj->Coin3 -= coin3_value;
				lpTarget->Coin3 += coin3_value;

				gCashShop.GDCashShopAddPointSaveSend(lpObj->Index, 0, 0, 0, lpObj->Coin3,0);
				gCashShop.GDCashShopAddPointSaveSend(lpTarget->Index, 0, 0, 0, lpTarget->Coin3,0);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(504), coin3_value);
				gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(505), coin3_value);
			}

			else if (ruud_value != 0)
			{
				lpObj->Ruud -= ruud_value;
				lpTarget->Ruud += ruud_value;

				gCashShop.GDCashShopAddPointSaveSend(lpObj->Index, 0, 0, 0,0, lpObj->Ruud);
				gCashShop.GDCashShopAddPointSaveSend(lpTarget->Index, 0, 0, 0,0, lpTarget->Ruud);

				gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(511), ruud_value);
				gNotice.GCNoticeSend(lpTarget->Index, 1, 0, 0, 0, 0, 0, gMessage.GetMessage(512), ruud_value);
			}
		}
	}

	return;
}

