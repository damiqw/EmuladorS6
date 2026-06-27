#include "stdafx.h"
#include "MuHelper.h"
#include "Protocol.h"
#include "Common.h"
#include "CustomPing.h"
#include "CustomRankUser.h"
#include "HealthBar.h"
#include "Interface.h"
#include "Offset.h"
#include "OffTrade.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Reconnect.h"
#include "Util.h"
#include "PartySearch.h"
#include "post_item.h"
#include "CustomBuffIcon.h"
#include "PetProtocol.h"
#include "EventInvasion.h"
#include "HWID.h"
#include "ChaosBox.h"
#include "Warehouse.h"
#include "PartyBuffs.h"
#include "MiniMapInfo.h"
#include "RuneEffect.h"
#include "PKNotice.h"
#if(HAISLOTRING)
#include "NewUIMyInventory.h"
#endif
#include "NPCRuud.h"
#include "CustomStatsAdvance.h"
#include "ItemMove.h"
#include "LoginMainWin.h"
#include "CustomEventTime.h"
#include "CustomJewelBank.h"
#include "CBNewUiEx.h"
#include "SPK_xShop.h"
#include "BuyVip.h"
#include "User.h"
#include "DailyReward.h"
#include "ThueFlag.h"
#include "CustomRanking.h"

#if(LuckyWheelV2)
VONGQUAYINFO_CLIENT mDataVongQuayClient;
VONGQUAY_CLIENT mDataListItemVongQuayClient;
#endif
#if(MAP_USAGE)
MAPUSAGETIM_CLIENT mMapUsageData;
extern int GetTimeGMT();
#endif

BOOL ProtocolCoreEx(BYTE head,BYTE* lpMsg,int size,int key) // OK
{
	switch(head)
	{
		case 0x0D:
		{
			PMSG_NOTICE_SEND* RecvlpMsg = (PMSG_NOTICE_SEND*)lpMsg;
			
			if (RecvlpMsg->type == (0xD3 + 1))
			{
				DATA_NOTICEPK kill = { 0 };

				kill.Delay = 0;
				kill.Time = GetTickCount() + (RecvlpMsg->delay * 1000);
				kill.Color = RecvlpMsg->color;
				memcpy(kill.Mess, RecvlpMsg->message, sizeof(kill.Mess));

				if (gPKNotice.m_DataNoticePK.size() >= 8)
				{
					gPKNotice.m_DataNoticePK.erase(gPKNotice.m_DataNoticePK.begin());
				}
				gPKNotice.m_DataNoticePK.push_back(kill);
				return 1;
			}
		}
		break;
		case 0x11:
			GCDamageRecv((PMSG_DAMAGE_RECV*)lpMsg);
			break;
		case 0xDE:
			GCCharacterCreationEnableRecv((PMSG_CHARACTER_CREATION_ENABLE_RECV*)lpMsg);
			break;
		case 0x16:
			GCMonsterDieRecv((PMSG_MONSTER_DIE_RECV*)lpMsg);
			break;
		case 0x17:
			GCUserDieRecv((PMSG_USER_DIE_RECV*)lpMsg);
			break;
		case 0x24:
			GCItemMoveRecv((PMSG_ITEM_MOVE_RECV*)lpMsg);
			break;
		case 0x26:
			GCLifeRecv((PMSG_LIFE_RECV*)lpMsg);
			break;
		case 0x27:
			GCManaRecv((PMSG_MANA_RECV*)lpMsg);
			break;
		case 0x2C:
			GCFruitResultRecv((PMSG_FRUIT_RESULT_RECV*)lpMsg);
			break;
		case 0x88:
			GCChaosMixRateRecv((PMSG_CHAOS_MIX_RATE_RECV*)lpMsg);
			break;
		case 0x9C:
			GCRewardExperienceRecv((PMSG_REWARD_EXPERIENCE_RECV*)lpMsg);
			break;
		case 0xA3:
			GCQuestRewardRecv((PMSG_QUEST_REWARD_RECV*)lpMsg);
			break;
		#if(NEW_POSTITEM)
		case 0x78:
			JCItemPublic.GCPostItem(lpMsg);
			break;
		#endif
		case 0xEA:
			jCRenderRuud.LoadRuudShop_Recv((PMSG_RUUD_ITEM_LIST_RECV*)lpMsg);
			return 1;
		case 0xEE:
			jCRenderRuud.OpenRuudShop_Recv((PMSG_NPC_TALK_RECV*)lpMsg);
			return 1;
		case 0xB1:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCMapServerMoveRecv((PMSG_MAP_SERVER_MOVE_RECV*)lpMsg);
					gIconBuff.DeleteAllBuff();
					break;
				case 0x01:
					GCMapServerMoveAuthRecv((PMSG_MAP_SERVER_MOVE_AUTH_RECV*)lpMsg);
					gIconBuff.DeleteAllBuff();
					break;
			}
			break;
		case 0x2D:
			gIconBuff.Recv((PMSG_SEND_BUFF_ICON * )lpMsg);
			break;
		case 0x2E:
			gPartyBuffs.RecvPartyBuffs((PMSG_PARTY_EFFECT_LIST_SEND*)lpMsg);
			break;
#if(HAISLOTRING)
		case 0x4E:
			switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
			{

			case 0x0A:
				g_pMyInventory.ReceiveInventory(lpMsg);
				return 1;
			case 0x0B:
				g_pMyInventory.ReceiveDurability(lpMsg);
				return 1;
			case 0x0C:
				g_pMyInventory.ReceiveDeleteInventory(lpMsg);
				return 1;
			case 0x0D:
				g_pMyInventory.ReceiveItemChange((PMSG_NEWINV_ITEM_CHANGE_RECV*)lpMsg);
				return 1;
			}
			break;
#endif
		case 0xE7:
			switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
			{
				case 0x03:
					gMiniMap.RecvMiniMapInfo((MINIMAP_INFO_RECV*)lpMsg);
					return 1;
			}
			break;
		case 0xF1:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCConnectClientRecv((PMSG_CONNECT_CLIENT_RECV*)lpMsg);
					break;
				case 0x01:
					GCConnectAccountRecv((PMSG_CONNECT_ACCOUNT_RECV*)lpMsg);
					break;
				case 0x02:
					GCCloseClientRecv((PMSG_CLOSE_CLIENT_RECV*)lpMsg);
					break;
				case 0x12:
					g_pLoginMainWin.ReciveCreateAccount(((lpMsg[0] == 0xC1) ? lpMsg[4] : lpMsg[5]));
					break;
			}
			break;
		case 0xF3:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x00:
					GCCharacterListRecv((PMSG_CHARACTER_LIST_RECV*)lpMsg);
					gIconBuff.DeleteAllBuff();
#if(FLAG)
					ThueFlag.Clear();
#endif
					break;
				case 0x03:
					GCCharacterInfoRecv((PMSG_CHARACTER_INFO_RECV*)lpMsg);
					break;
				case 0x04:
					GCCharacterRegenRecv((PMSG_CHARACTER_REGEN_RECV*)lpMsg);
					break;
				case 0x05:
					GCLevelUpRecv((PMSG_LEVEL_UP_RECV*)lpMsg);
					break;
				case 0x06:
					GCLevelUpPointRecv((PMSG_LEVEL_UP_POINT_RECV*)lpMsg);
					break;
				case 0x07:
					GCMonsterDamageRecv((PMSG_MONSTER_DAMAGE_RECV*)lpMsg);
					break;
				case 0x50:
					GCMasterInfoRecv((PMSG_MASTER_INFO_RECV*)lpMsg);
					break;
				case 0x51:
					GCMasterLevelUpRecv((PMSG_MASTER_LEVEL_UP_RECV*)lpMsg);
					break;
				case 0xE0:
					GCNewCharacterInfoRecv((PMSG_NEW_CHARACTER_INFO_RECV*)lpMsg);
					return 1;
				case 0xE1:
					GCNewCharacterCalcRecv((PMSG_NEW_CHARACTER_CALC_RECV*)lpMsg);
					return 1;
				case 0xE2:
					GCNewHealthBarRecv((PMSG_NEW_HEALTH_BAR_RECV*)lpMsg);
					return 1;
				case 0xE3:
					GCNewGensBattleInfoRecv((PMSG_NEW_GENS_BATTLE_INFO_RECV*)lpMsg);
					return 1;
				case 0xE4:
					GCNewMessageRecv((PMSG_NEW_MESSAGE_RECV*)lpMsg);
					return 1;
				case 0xE5:
					gCustomRankUser.GCReqRankLevelUser((PMSG_CUSTOM_RANKUSER*)lpMsg);
					return 1;
				case 0xEA:
					GCRecvCoin((PMSG_COIN_RECV*)lpMsg);
					return 1;
				case 0xEB:
					gOffTrade.RecvPShop((PMSG_OFFTRADE_RECV*)lpMsg);
					return 1;
				case 0xEC:
					gOffTrade.PShopActiveRecv((PMSG_SHOPACTIVE_RECV*)lpMsg);
					return 1;
				case 0xED:
					GCBuyConfirmRecv((PMSG_ITEM_BUY_RECV*)lpMsg);
					break;
#if(RIGHT_CLICK)
				case 0xEE:
					SetChaosBoxState((PMSG_SET_CHAOSBOX_STATE*)lpMsg);
					return 1;
#endif
				case 0xF0:
					GCPartyListRecv((PMSG_RECV_PARTYLIST*)lpMsg);
					return 1;
				case 0xEF:
					gRuneEffect.GCRuneEffect((PMSG_CUSTOM_RUNEEFFECT*)lpMsg);
					break;
				case 0xF1:
					GCPetCharSetRecv((PMSG_NEW_PET_CHARSET_RECV*)lpMsg);
					return 1;
				case 0xF2:
					GCPetCharSetSelectCharacterRecv((PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV*)lpMsg);
					return 1;
				case 0xF3:
					gCustomPing.PingRecv();
					break;
				case 0xF4:
					g_StatsAdvance.Recv((PMSG_STATS_ADVANCE*)lpMsg);
					return 1;
				case 0xF5:
					gCustomJewelBank.GCCustomJewelBankInfoRecv((PSBMSG_JEWELBANK_RECV*)lpMsg);
					break;
				case 0xF9:
					gMiniMap.RecvPartyInfo((MINIMAP_PARTY_INFO_RECV*)lpMsg);
					break;
				case 0xFB:
					GCBuyVipRecv((PMSG_BUYVIP_LIST__RECV*)lpMsg);
					break;
				case 0xE6:
					gCustomRanking.GCReqRanking((PMSG_CUSTOM_RANKING_RECV*)lpMsg);
					return 1;
				case 0xE7:
					gCustomRanking.GCReqRankingCount((PMSG_CUSTOM_RANKING_COUNT_RECV*)lpMsg);
					return 1;
				case 0xE8:
					gCustomEventTime.GCReqEventTime((PMSG_CUSTOM_EVENTTIME_RECV*)lpMsg);
					gCustomEventTime.GetItemCount();
					return 1;
			}
			break;
		case 0xD5:
			switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
			{
#if(CustomXShop)
			case 0x11: 
				gNewCashShop.SendPacketToProtocol11(lpMsg);
				break;
			case 0x12:
				gNewCashShop.SendPacketToProtocol12(lpMsg);
				break;
#endif
			}
			break;
		case 0xFB:
			switch(((lpMsg[0]==0xC1)?lpMsg[3]:lpMsg[4]))
			{
				case 0x3E:
					gMuHelper.RunningOffHelper();
					break;
#if(DAILY)
				case 0x03:
					DailyReward.GCRecvUserInfo(lpMsg);
					break;
				case 0x04:
					DailyReward.GCRecvDayInfo(lpMsg);
					break;
#endif
				case 0xD5:
					gWarehouse.GCReqWarehouseUserCountRecv((PMSG_WAREHOUSEINFO_RECV*)lpMsg);
					break;
				case 0x13:
					gIconBuff.GC_BuffInfo((PMSG_SEND_BUFF_ICON_EX*)lpMsg);
					break;
#if FLAG
				case 0x18:
					ThueFlag.RecvData(lpMsg);
					break;
#endif
				case 0x20:
					ExtraCpanelGetInfo((EXTRA_CPANEL_SENDINFO*)lpMsg);
					break;
			}
		break;
		case 0xFA:
			switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
			{
			case 0x11:
				gCustomRanking.RankNameRev((PMSG_RANK_INFO*)lpMsg);
				return 1;
#if(INFO_EVENTINVASION)
			case 0xF8:
				gEventInvasion.GCListEvent((PMSG_INVASION_INFO*)lpMsg);
				return 1;
			case 0xF9:
				gEventInvasion.GCListMonter((PMSG_INVASION_INFO_MONTER*)lpMsg);
				return 1;
			}
#endif
			break;
			case 0xD3:
			switch (((lpMsg[0] == 0xC1) ? lpMsg[3] : lpMsg[4]))
			{
#if (CUSTOM_BRANKINGNEW)
			case 0x40: //
				gCustomRanking.GCReqInfoCharTop((DATA_VIEWTOPRANKING*)lpMsg);
				return 1;
#endif
#if(MAP_USAGE)
			case 0x41: //
			{
				MAPUSAGETIME_INFO* mRecv = (MAPUSAGETIME_INFO*)lpMsg;
				mMapUsageData.Map = mRecv->Map;
				mMapUsageData.Time = mRecv->Time + GetTimeGMT();
				return 1;
			}
#endif
#if(LuckyWheelV2)
			case 0x8A: //GetList Moc Nap
			{
				mDataVongQuayClient.Clear();
				PMSG_VONGQUAY_SEND* mRecv = (PMSG_VONGQUAY_SEND*)lpMsg;

				for (int i = 0; i < mRecv->count; i++)
				{
					ListVongQuaySend lpInfo = *(ListVongQuaySend*)(((BYTE*)lpMsg) + sizeof(PMSG_VONGQUAY_SEND) + (sizeof(ListVongQuaySend) * i));
					mDataVongQuayClient.DanhSachVongQuay.push_back(lpInfo);
				}
			}
			break;
			case 0x8B: //Recv List Phan Thuong
			{
				mDataListItemVongQuayClient.Clear();
				PMSG_YCVONGQUAY_SEND* mRecv = (PMSG_YCVONGQUAY_SEND*)lpMsg;
				mDataListItemVongQuayClient.IndexYC = mRecv->IndexYC;
				mDataListItemVongQuayClient.CountItem = mRecv->CountItem;
				mDataListItemVongQuayClient.WCYC = mRecv->WCYC;
				mDataListItemVongQuayClient.WPYC = mRecv->WPYC;
				mDataListItemVongQuayClient.GPYC = mRecv->GPYC;

				for (int i = 0; i < mRecv->count; i++)
				{
					LISTITEMVONGQUAY_SENDINFO lpInfo = *(LISTITEMVONGQUAY_SENDINFO*)(((BYTE*)lpMsg) + sizeof(PMSG_YCVONGQUAY_SEND) + (sizeof(LISTITEMVONGQUAY_SENDINFO) * i));
					//==SetINfoItem
					INFO_VONGQUAY_LOCAL_ITEM infoItemLocal = { 0 };
					infoItemLocal.SizeBMD = lpInfo.SizeBMD;
					infoItemLocal.Index = lpInfo.Index;
					infoItemLocal.Item = *((ObjectItem * (__thiscall*)(int, BYTE*)) 0x007E1B10)(*(DWORD*)(((int(*)()) 0x861110)() + 36), lpInfo.Item);
					infoItemLocal.Item.Durability = lpInfo.Dur;
					if (lpInfo.PeriodTime)
					{
						infoItemLocal.Item.PeriodItem = 1;
						infoItemLocal.Item.ExpireDateConvert = lpInfo.PeriodTime;
					}
					mDataListItemVongQuayClient.ListItemVongQuay.push_back(infoItemLocal);

				}
				gInterface.Data[eWindowVongQuay].OnShow = 1;
			}
			break;
			case 0x8C: //Recv List Phan Thuong
			{
				XULY_CGPACKET_VONGQUAY* mRecv = (XULY_CGPACKET_VONGQUAY*)lpMsg;
				//gInterface.DrawMessage(1, "%d ~ %d", mRecv->StartRoll, mRecv->IndexWin);
				gInterface.StartRollSau = mRecv->StartRoll;
				gInterface.IndexItemSau = mRecv->IndexWin;
			}
			break;
#endif
			}
		break;
	}

	return ProtocolCore(head,lpMsg,size,key);
}

void GCDamageRecv(PMSG_DAMAGE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = lpMsg->ViewCurHP;
		ViewCurSD = lpMsg->ViewCurSD;
	}

	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;

	if((lpMsg->type & 0x10) != 0)
	{
		if(ViewDamageCount < 3)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}

	if((lpMsg->type & 0x20) != 0)
	{
		if(ViewDamageCount < 4)
		{
			ViewDamageTable[ViewDamageCount++] = lpMsg->ViewDamageHP;
			ViewDamageValue = ViewDamageCount;
		}
	}
}

void GCCharacterCreationEnableRecv(PMSG_CHARACTER_CREATION_ENABLE_RECV* lpMsg) // OK
{
	SetExperienceTable(lpMsg->CharacterMaxLevel, lpMsg->ExperienceMultiplierConstA, lpMsg->ExperienceMultiplierConstB, lpMsg->CharacterDeleteMaxLevel);
}

void GCMonsterDieRecv(PMSG_MONSTER_DIE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCUserDieRecv(PMSG_USER_DIE_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewCurHP = 0;
	}
}

void GCLifeRecv(PMSG_LIFE_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxHP = lpMsg->ViewHP;
		ViewMaxSD = lpMsg->ViewSD;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurHP = ((ViewCurHP==0)?ViewCurHP:lpMsg->ViewHP);
		ViewCurSD = lpMsg->ViewSD;
	}
}

void GCManaRecv(PMSG_MANA_RECV* lpMsg) // OK
{
	if(lpMsg->type == 0xFE)
	{
		ViewMaxMP = lpMsg->ViewMP;
		ViewMaxBP = lpMsg->ViewBP;
	}

	if(lpMsg->type == 0xFF)
	{
		ViewCurMP = lpMsg->ViewMP;
		ViewCurBP = lpMsg->ViewBP;
	}
}

void GCFruitResultRecv(PMSG_FRUIT_RESULT_RECV* lpMsg) // OK
{
	if(lpMsg->result == 0 || lpMsg->result == 3 || lpMsg->result == 6 || lpMsg->result == 17)
	{
		ViewValue = lpMsg->ViewValue;
		ViewPoint = lpMsg->ViewPoint;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCRewardExperienceRecv(PMSG_REWARD_EXPERIENCE_RECV* lpMsg) // OK
{
	ViewDamageHP = lpMsg->ViewDamageHP;
}

void GCQuestRewardRecv(PMSG_QUEST_REWARD_RECV* lpMsg) // OK
{
	int aIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]) & 0x7FFF;

	if(ViewIndex == aIndex)
	{
		ViewPoint = lpMsg->ViewPoint;
	}
}

void GCMapServerMoveRecv(PMSG_MAP_SERVER_MOVE_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMove(lpMsg->IpAddress,lpMsg->ServerPort);
}

void GCMapServerMoveAuthRecv(PMSG_MAP_SERVER_MOVE_AUTH_RECV* lpMsg) // OK
{
	ReconnectOnMapServerMoveAuth(lpMsg->result);
}

void GCConnectClientRecv(PMSG_CONNECT_CLIENT_RECV* lpMsg) // OK
{
	gHwid.SendHwid();
	ViewIndex = MAKE_NUMBERW(lpMsg->index[0],lpMsg->index[1]);
}

void GCConnectAccountRecv(PMSG_CONNECT_ACCOUNT_RECV* lpMsg) // OK
{
	ReconnectOnConnectAccount(lpMsg->result);
}

void GCCloseClientRecv(PMSG_CLOSE_CLIENT_RECV* lpMsg) // OK
{
	ReconnectOnCloseClient(lpMsg->result);
}

void GCCharacterListRecv(PMSG_CHARACTER_LIST_RECV* lpMsg) // OK
{
	ReconnectOnCharacterList();
}

void GCCharacterInfoRecv(PMSG_CHARACTER_INFO_RECV* lpMsg) // OK
{
	ReconnectOnCharacterInfo();

	ViewReset = lpMsg->ViewReset;
	ViewMasterReset = lpMsg->ViewMasterReset;
	ViewAccountLevel = lpMsg->ViewAccountLevel;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;

	*(WORD*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x07E) = 0;

	*(BYTE*)(*(DWORD*)(MAIN_VIEWPORT_STRUCT)+0x30C) = 0;

	switch(((*(BYTE*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0B)) & 7))
	{
		case 0:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DKMaxAttackSpeed>=0xFFFF)?0x0F:0x0F));
			break;
		case 1:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DKMaxAttackSpeed>=0xFFFF)?0x0F:0x0F));
			break;
		case 2:
			SetByte(0x00556C38,((gProtect.m_MainInfo.FEMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 3:
			SetByte(0x00556C38,((gProtect.m_MainInfo.MGMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 4:
			SetByte(0x00556C38,((gProtect.m_MainInfo.DLMaxAttackSpeed>=0xFFFF)?0x02:0x0F));
			break;
		case 5:
			SetByte(0x00556C38,((gProtect.m_MainInfo.SUMaxAttackSpeed>=0xFFFF)?0x02:0x0F)); 
			break;
		case 6:
			SetByte(0x00556C38,((gProtect.m_MainInfo.RFMaxAttackSpeed>=0xFFFF)?0x0F:0x0F));
			break;
	}
}

void GCCharacterRegenRecv(PMSG_CHARACTER_REGEN_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewCurSD = lpMsg->ViewCurSD;
}

void GCLevelUpRecv(PMSG_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewPoint = lpMsg->ViewPoint;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewExperience = lpMsg->ViewExperience;
	ViewNextExperience = lpMsg->ViewNextExperience;
}

void GCLevelUpPointRecv(PMSG_LEVEL_UP_POINT_RECV* lpMsg) // OK
{
	if(lpMsg->result >= 16 && lpMsg->result <= 20)
	{
		ViewPoint = lpMsg->ViewPoint;
		ViewMaxHP = lpMsg->ViewMaxHP;
		ViewMaxMP = lpMsg->ViewMaxMP;
		ViewMaxBP = lpMsg->ViewMaxBP;
		ViewMaxSD = lpMsg->ViewMaxSD;
		ViewStrength = lpMsg->ViewStrength;
		ViewDexterity = lpMsg->ViewDexterity;
		ViewVitality = lpMsg->ViewVitality;
		ViewEnergy = lpMsg->ViewEnergy;
		ViewLeadership = lpMsg->ViewLeadership;
	}
}

void GCMonsterDamageRecv(PMSG_MONSTER_DAMAGE_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewDamageHP = lpMsg->ViewDamageHP;
	ViewDamageSD = lpMsg->ViewDamageSD;
}

void GCMasterInfoRecv(PMSG_MASTER_INFO_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
}

void GCMasterLevelUpRecv(PMSG_MASTER_LEVEL_UP_RECV* lpMsg) // OK
{
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewMasterExperience = lpMsg->ViewMasterExperience;
	ViewMasterNextExperience = lpMsg->ViewMasterNextExperience;
}

void GCNewCharacterInfoRecv(PMSG_NEW_CHARACTER_INFO_RECV* lpMsg) // OK
{
	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x0E) = lpMsg->Level;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x74) = lpMsg->LevelUpPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x18) = lpMsg->Strength;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1A) = lpMsg->Dexterity;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1C) = lpMsg->Vitality;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x1E) = lpMsg->Energy;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x20) = lpMsg->Leadership;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x22) = lpMsg->Life;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x26) = lpMsg->MaxLife;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x24) = lpMsg->Mana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x28) = lpMsg->MaxMana;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x40) = lpMsg->BP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x42) = lpMsg->MaxBP;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2A) = lpMsg->Shield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x2C) = lpMsg->MaxShield;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4C) = lpMsg->FruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x4E) = lpMsg->MaxFruitAddPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x50) = lpMsg->FruitSubPoint;

	*(WORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x52) = lpMsg->MaxFruitSubPoint;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x10) = lpMsg->Experience;

	*(DWORD*)(*(DWORD*)(MAIN_CHARACTER_STRUCT)+0x14) = lpMsg->NextExperience;

	//EXTRA
	ViewReset = lpMsg->ViewReset;
	ViewMasterReset = lpMsg->ViewMasterReset;
	ViewAccountLevel = lpMsg->ViewAccountLevel;
	ViewPoint = lpMsg->ViewPoint;
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewStrength = lpMsg->ViewStrength;
	ViewDexterity = lpMsg->ViewDexterity;
	ViewVitality = lpMsg->ViewVitality;
	ViewEnergy = lpMsg->ViewEnergy;
	ViewLeadership = lpMsg->ViewLeadership;
}

void GCNewCharacterCalcRecv(PMSG_NEW_CHARACTER_CALC_RECV* lpMsg) // OK
{
	ViewCurHP = lpMsg->ViewCurHP;
	ViewMaxHP = lpMsg->ViewMaxHP;
	ViewCurMP = lpMsg->ViewCurMP;
	ViewMaxMP = lpMsg->ViewMaxMP;
	ViewCurBP = lpMsg->ViewCurBP;
	ViewMaxBP = lpMsg->ViewMaxBP;
	ViewCurSD = lpMsg->ViewCurSD;
	ViewMaxSD = lpMsg->ViewMaxSD;
	ViewAddStrength = lpMsg->ViewAddStrength;
	ViewAddDexterity = lpMsg->ViewAddDexterity;
	ViewAddVitality = lpMsg->ViewAddVitality;
	ViewAddEnergy = lpMsg->ViewAddEnergy;
	ViewAddLeadership = lpMsg->ViewAddLeadership;
	ViewPhysiDamageMin = lpMsg->ViewPhysiDamageMin;
	ViewPhysiDamageMax = lpMsg->ViewPhysiDamageMax;
	ViewMagicDamageMin = lpMsg->ViewMagicDamageMin;
	ViewMagicDamageMax = lpMsg->ViewMagicDamageMax;
	ViewCurseDamageMin = lpMsg->ViewCurseDamageMin;
	ViewCurseDamageMax = lpMsg->ViewCurseDamageMax;
	ViewMulPhysiDamage = lpMsg->ViewMulPhysiDamage;
	ViewDivPhysiDamage = lpMsg->ViewDivPhysiDamage;
	ViewMulMagicDamage = lpMsg->ViewMulMagicDamage;
	ViewDivMagicDamage = lpMsg->ViewDivMagicDamage;
	ViewMulCurseDamage = lpMsg->ViewMulCurseDamage;
	ViewDivCurseDamage = lpMsg->ViewDivCurseDamage;
	ViewMagicDamageRate = lpMsg->ViewMagicDamageRate;
	ViewCurseDamageRate = lpMsg->ViewCurseDamageRate;
	ViewPhysiSpeed = lpMsg->ViewPhysiSpeed;
	ViewMagicSpeed = lpMsg->ViewMagicSpeed;
	ViewAttackSuccessRate = lpMsg->ViewAttackSuccessRate;
	ViewAttackSuccessRatePvP = lpMsg->ViewAttackSuccessRatePvP;
	ViewDefense = lpMsg->ViewDefense;
	ViewDefenseSuccessRate = lpMsg->ViewDefenseSuccessRate;
	ViewDefenseSuccessRatePvP = lpMsg->ViewDefenseSuccessRatePvP;
	ViewDamageMultiplier = lpMsg->ViewDamageMultiplier;
	ViewRFDamageMultiplierA = lpMsg->ViewRFDamageMultiplierA;
	ViewRFDamageMultiplierB = lpMsg->ViewRFDamageMultiplierB;
	ViewRFDamageMultiplierC = lpMsg->ViewRFDamageMultiplierC;
	ViewDarkSpiritAttackDamageMin = lpMsg->ViewDarkSpiritAttackDamageMin;
	ViewDarkSpiritAttackDamageMax = lpMsg->ViewDarkSpiritAttackDamageMax;
	ViewDarkSpiritAttackSpeed = lpMsg->ViewDarkSpiritAttackSpeed;
	ViewDarkSpiritAttackSuccessRate = lpMsg->ViewDarkSpiritAttackSuccessRate;
}

void GCNewHealthBarRecv(PMSG_NEW_HEALTH_BAR_RECV* lpMsg) // OK
{
	ClearNewHealthBar();
#if(FLAG)
	MyManyFlag = lpMsg->bHaeManyFlag;
#endif
	for(int n=0;n < lpMsg->count;n++)
	{
		PMSG_NEW_HEALTH_RECV* lpInfo = (PMSG_NEW_HEALTH_RECV*)(((BYTE*)lpMsg)+sizeof(PMSG_NEW_HEALTH_BAR_RECV)+(sizeof(PMSG_NEW_HEALTH_RECV)*n));

		InsertNewHealthBar(lpInfo);
		//InsertNewHealthBar(lpInfo->index,lpInfo->type,lpInfo->rate,lpInfo->rate2);
	}
}

void GCNewGensBattleInfoRecv(PMSG_NEW_GENS_BATTLE_INFO_RECV* lpMsg) // OK
{
	GensBattleMapCount = lpMsg->GensBattleMapCount;

	GensMoveIndexCount = lpMsg->GensMoveIndexCount;

	memcpy(GensBattleMap,lpMsg->GensBattleMap,sizeof(GensBattleMap));

	memcpy(GensMoveIndex,lpMsg->GensMoveIndex,sizeof(GensMoveIndex));
}

void GCNewMessageRecv(PMSG_NEW_MESSAGE_RECV* lpMsg) // OK
{

}

void DataSend(BYTE* lpMsg,DWORD size) // OK
{
	BYTE EncBuff[2048];

	if(gPacketManager.AddData(lpMsg,size) != 0 && gPacketManager.ExtractPacket(EncBuff) != 0)
	{
		BYTE send[2048];

		memcpy(send,EncBuff,size);

		if(EncBuff[0] == 0xC3 || EncBuff[0] == 0xC4)
		{
			if(EncBuff[0] == 0xC3)
			{
				BYTE save = EncBuff[1];

				EncBuff[1] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[2],&EncBuff[1],(size-1))+2;

				EncBuff[1] = save;

				send[0] = 0xC3;
				send[1] = LOBYTE(size);
			}
			else
			{
				BYTE save = EncBuff[2];

				EncBuff[2] = (*(BYTE*)(MAIN_PACKET_SERIAL))++;

				size = gPacketManager.Encrypt(&send[3],&EncBuff[2],(size-2))+3;

				EncBuff[2] = save;

				send[0] = 0xC4;
				send[1] = HIBYTE(size);
				send[2] = LOBYTE(size);
			}
		}

		((void(__thiscall*)(void*,BYTE*,DWORD))0x00405110)((void*)0x08793750,send,size);
	}
}

void GCRecvCoin(PMSG_COIN_RECV* lpMsg) // OK
{
	Coin1 = lpMsg->Coin1;
	Coin2 = lpMsg->Coin2;
	Coin3 = lpMsg->Coin3;
	Ruud = lpMsg->Ruud;
}

void GCBuyConfirmRecv(PMSG_ITEM_BUY_RECV* lpMsg) // OK
{
	gInterface.Data[eCONFIRM_MAIN].OnShow = true;
	pSetCursorFocus = true;
	gInterface.ConfirmSlot = lpMsg->slot;
}

void GCBuyVipRecv(PMSG_BUYVIP_LIST__RECV* lpMsg) // OK
{
	gBuyVip.ClearBuyVipList();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_BUYVIP_LIST* lpInfo = (PMSG_BUYVIP_LIST*)(((BYTE*)lpMsg) + sizeof(PMSG_BUYVIP_LIST__RECV) + (sizeof(PMSG_BUYVIP_LIST) * n));

		gBuyVip.InsertBuyVip(lpInfo);
	}
}

//--- pet
void GCPetCharSetRecv(PMSG_NEW_PET_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSet();

	for (int n = 0; n < lpMsg->count; n++)
	{
		NEW_PET_STRUCT* lpInfo = (NEW_PET_STRUCT*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_PET_CHARSET_RECV)+(sizeof(NEW_PET_STRUCT)*n));

		InsertNewPetCharSet(lpInfo->index, lpInfo->PetCharSet);
	}
}

void GCPetCharSetSelectCharacterRecv(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV* lpMsg)
{
	ClearNewPetCharSetSelectCharacter();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_NEW_CHARACTER_CHARSET_RECV* lpInfo = (PMSG_NEW_CHARACTER_CHARSET_RECV*)(((BYTE*)lpMsg) + sizeof(PMSG_NEW_SELECT_CHARACTER_CHARSET_RECV)+(sizeof(PMSG_NEW_CHARACTER_CHARSET_RECV)*n));

		InsertNewPetCharSetSelectCharacter(lpInfo->Name, lpInfo->PetCharSet);
	}
}

#if(RIGHT_CLICK)
void SetChaosBoxState(PMSG_SET_CHAOSBOX_STATE* Data)
{
	pChaosBoxState = Data->state;
	return;
}
#endif

void ExtraCpanelGetInfo(EXTRA_CPANEL_SENDINFO* lpMsg)
{
	gInterface.m_QuickAdd = lpMsg->QuickAdd;
	//
	gObjUser.d_Strength = lpMsg->dStrength;
	gObjUser.d_Dexterity = lpMsg->dDexterity;
	gObjUser.d_Vitality = lpMsg->dVitality;
	gObjUser.d_Energy = lpMsg->dEnergy;
	gObjUser.d_Leadership = lpMsg->dLeadership;

	for (int i = 0; i < MAX_ACCOUNT_LEVEL; i++)
	{

		gObjUser.m_MaxStatPoint[i] = lpMsg->MaxStatPoint[i];
	}
}

void CGSendStatsAdd(PMSG_UPDATE_STATS_SEND pMsg)
{
	pMsg.header.set(0xFF, 0x0C, sizeof(pMsg));
	DataSend((BYTE*)&pMsg, pMsg.header.size);
}

void GCItemMoveRecv(PMSG_ITEM_MOVE_RECV* lpMsg) // OK
{
	LastMixCode = -1;

	RightClickDeleteItem(lpMsg->result);
}

void GCPartyListRecv(PMSG_RECV_PARTYLIST* lpMsg)
{
	gPartySearch.ClearPartyList();

	for (int n = 0; n < lpMsg->Count; n++)
	{
		PMSG_PARTYSEARCH_PARTYLIST* lpInfo = (PMSG_PARTYSEARCH_PARTYLIST*)(((BYTE*)lpMsg) + sizeof(PMSG_RECV_PARTYLIST) + (sizeof(PMSG_PARTYSEARCH_PARTYLIST) * n));

		gPartySearch.InsertPartyList(lpInfo);
	}

	gPartySearch.party_search_switch_state();
}