#include "stdafx.h"
#include "Common.h"
#include "CustomPing.h"
#include "Interface.h"
#include "Import.h"
#include "Reconnect.h"
#include "TMemory.h"
#include "Defines.h"
#include "OffTrade.h"
#include "Protect.h"
#include "Protocol.h"
#include "PrintPlayer.h"
#include "User.h"
#include "Util.h"
#include "Controller.h"
#include "NewUIMyInventory.h"
#include "InterfaceS8AdvancedUI.h"
#include "PartySearch.h"
#include "PartySearchSettings.h"
#include "Offset.h"
#include "EventInvasion.h"
#include "InterfaceElemental.h"
#include "CustomFont.h"
#include "SEASON3B.h"
#include "Warehouse.h"
#include "Item.h"
#include "MiniMap.h"
#include "CTimCheck.h"
#include "PKNotice.h"
#include "NPCRuud.h"
#include "CustomStatsAdvance.h"
#include "CustomQuickAddStats.h"
#include "CustomInterface.h"
#include "ShowInfoItemDrop.h"
#include "CustomEventTime.h"
#include "CustomJewelBank.h"
#include "SPK_xShop.h"
#include "BuyVip.h"
#include "Antilag.h"
#include "CustomCommandInfo.h"
#include "DailyReward.h"
#include "ThueFlag.h"
#include "CustomRanking.h"

Interface	gInterface;

float TransForX(float num)
{
	return (float)(pWinWidthReal <= 1.25) ? num * pWinWidthReal : num * pWinHeightReal;
}

float TransForY(float num)
{
	return (float)num * pWinHeightReal;
}

float TransFor2X(float num)
{
	return (float)num * pWinWidthReal;
}

float ReturnX(float num)
{
	return (float)(pWinWidthReal <= 1.25) ? num / pWinWidthReal : num / pWinHeightReal;
}

float Return2X(float num)
{
	return (float)num / pWinWidthReal;
}

float ReturnY(float num)
{
	return (float)num / pWinHeightReal;
}

bool CheckButtonPressed(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && *(BYTE*)0x8793386;
}

bool CheckButtonPressedRMouse(int x, int y, int w, int h)
{
	return pCheckMouseOver(x, y, w, h) && pIsKeyRelease(VK_MBUTTON);
}

void Interface::Load()
{

	if (gProtect.m_MainInfo.DisableAdvance == 0)
	{
		gInterface.BindObject(eADVANCE_STAT_INFO, 561020, 35, 30, -1, -1);	
	}

	this->BindObject(OBJECT_PARTYMENU_MAIN, 0x7A5A, 222, 140, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_BTN_PUBLICAR, 0x7A5E, 108, 29, -1, -1);
	this->BindObject(OBJECT_PARTYMENU_BTN_BUSCAR, 0x7A5E, 108, 29, -1, -1);

	this->BindObject(eFlag01, 0x7880, 78, 78, -1, -1);
	this->BindObject(eFlag02, 0x7881, 78, 78, -1, -1);
	this->BindObject(eFlag03, 0x7882, 78, 78, -1, -1);
	this->BindObject(eFlag04, 0x7883, 78, 78, -1, -1);
	this->BindObject(eFlag05, 0x7884, 78, 78, -1, -1);
	this->BindObject(eFlag06, 0x7885, 78, 78, -1, -1);
	this->BindObject(eFlag07, 0x7886, 78, 78, -1, -1);
	this->BindObject(eFlag08, 0x7887, 78, 78, -1, -1);
	this->BindObject(eFlag09, 0x7888, 78, 78, -1, -1);
	this->BindObject(eFlag10, 0x7889, 78, 78, -1, -1);
	this->BindObject(eFlag11, 0x7890, 78, 78, -1, -1);
	this->BindObject(eFlag12, 0x7891, 78, 78, -1, -1);
	this->BindObject(eFlag13, 0x7892, 78, 78, -1, -1);
	this->BindObject(eFlag14, 0x7893, 78, 78, -1, -1);
	this->BindObject(eFlag15, 0x7894, 78, 78, -1, -1);
	this->BindObject(eFlag16, 0x7895, 78, 78, -1, -1);
	this->BindObject(eFlag17, 0x7896, 78, 78, -1, -1);
	this->BindObject(eFlag18, 0x7897, 78, 78, -1, -1);
	this->BindObject(eFlag19, 0x7898, 78, 78, -1, -1);
	this->BindObject(eFlag20, 0x7899, 78, 78, -1, -1);
	this->BindObject(eFlag21, 0x7900, 78, 78, -1, -1);
	this->BindObject(eFlag22, 0x7901, 78, 78, -1, -1);
	this->BindObject(eSAMPLEBUTTON, 0x7903, 25, 40, -1, -1);
	this->BindObject(eSAMPLEBUTTON2, 0x7904, 25, 40, -1, -1);

	this->BindObject(eCONFIRM_MAIN, 0x7A5A, 222, 120, -1, -1);
	this->BindObject(eCONFIRM_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eCONFIRM_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eCONFIRM_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eCONFIRM_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(eCONFIRM_BTN_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(eCONFIRM_BTN_CANCEL, 0x7A5C, 54, 30, -1, -1);

	//Minimap
	this->BindObject(ePLAYER_POINT, 31460, 3, 3, -1, -1);
	this->BindObject(eNULL_MAP, 31461, 128, 128, -1, -1);
	this->BindObject(eLORENCIA_MAP, 31462, 128, 128, -1, -1);
	this->BindObject(eDUNGEON_MAP, 31463, 128, 128, -1, -1);
	this->BindObject(eDEVIAS_MAP, 31464, 128, 128, -1, -1);
	this->BindObject(eNORIA_MAP, 31465, 128, 128, -1, -1);
	this->BindObject(eLOSTTOWER_MAP, 31466, 128, 128, -1, -1);
	this->BindObject(eATLANS_MAP, 31467, 128, 128, -1, -1);
	this->BindObject(eTarkan_MAP, 31468, 128, 128, -1, -1);
	this->BindObject(eElbeland_MAP, 31469, 128, 128, -1, -1);
	this->BindObject(eICARUS_MAP, 31470, 128, 128, -1, -1);
	this->BindObject(eLANDOFTRIALS_MAP, 31461, 128, 128, -1, -1);
	this->BindObject(eAIDA_MAP, 31472, 128, 128, -1, -1);
	this->BindObject(eCRYWOLF_MAP, 31473, 128, 128, -1, -1);
	this->BindObject(eKANTRU_MAP, 31474, 128, 128, -1, -1);
	this->BindObject(eKANTRU3_MAP, 31475, 128, 128, -1, -1);
	this->BindObject(eBARRACKS_MAP, 31476, 128, 128, -1, -1);
	this->BindObject(eCALMNESS_MAP, 31477, 128, 128, -1, -1);
	this->BindObject(eRAKLION_MAP, 31478, 128, 128, -1, -1);
	this->BindObject(eVULCANUS_MAP, 31479, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN_MAP, 31480, 128, 128, -1, -1);
	this->BindObject(eKALRUTAN2_MAP, 31481, 128, 128, -1, -1);

	this->BindObject(eLogo, 0x7905, 150, 114, -1, -1);

	if (gProtect.m_MainInfo.CustomMenuType == 1)
	{
		this->BindObject(eMenu, 0x7906, 16, 12, -1, -1);
		this->BindObject(eMenuS8, 0x79346, 18, 18, -1, -1);
		this->BindObject(eMenuBG, 0x7907, 36, 18, 174, 0);
	}

#if(MENU_NEW)
	this->BindObject(eMENU_MAIN, 31461, 640, 419, -1, -1);  // 31461
	this->BindObject(eMENU_CLOSE, 0x7EC5, 36, 29, -1, -1);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->BindObject(eBUTTON_MENU_1, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_2, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_3, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_4, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_5, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_6, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_7, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_8, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_9, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_10, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_11, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_12, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_13, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_14, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_15, 71522, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_16, 71522, 108, 30.5, -1, -1);
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		this->BindObject(eBUTTON_MENU_1, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_2, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_3, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_4, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_5, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_6, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_7, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_8, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_9, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_10, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_11, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_12, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_13, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_14, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_15, 715277, 108, 30.5, -1, -1);
		this->BindObject(eBUTTON_MENU_16, 715277, 108, 30.5, -1, -1);
	}
#endif

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->BindObject(eOFFTRADE_JoB, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 51522, 40, 17, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 51522, 108, 30, -1, -1);
		this->BindObject(eSTORE_CLOSE, 51522, 108, 30, -1, -1);
	}
	else
	{
		//Custom Store
		this->BindObject(eOFFTRADE_JoB, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoS, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_JoC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCC, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCP, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_WCG, 0x7908, 40, 19, -1, -1);
		this->BindObject(eOFFTRADE_OPEN, 0x7BFD, 108, 30, -1, -1);
		this->BindObject(eSTORE_CLOSE, 0x7BFD, 108, 30, -1, -1);
	}

	this->BindObject(eTIME, 0x787F, 131, 70, -10, 480); //ACA SE CONTROLA ABAJO Y ARRIBA HORA LOCAL Y SERVER

	this->BindObject(eADDPOINT3_MAIN, 0x7A5A, 222, 225, -1, -1);

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->BindObject(eRanking_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(OBJECT_SKIN_SYSTEM_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(OBJECT_FLAG_SYSTEM_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(OBJECT_DAILY_SYSTEM_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(eCommand_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(eCustomShop_CLOSE_MAIN, 0x79346, 14, 16, -1, -1);

#if(LuckyWheelV2)
		this->BindObject(eWindowVongQuay_CLOSE, 0x79346, 14, 16, -1, -1);
#endif
		this->BindObject(eJewelBank_CLOSE, 0x79346, 14, 16, -1, -1);
		this->BindObject(eADDPOINT3_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(eADDPOINT_CLOSE, 0x79346, 14, 16, -1, -1);

		this->BindObject(eVip_CLOSE, 0x79346, 14, 16, -1, -1);
		this->BindObject(eVip_BRONZE, 71522, 108, 30.5, -1, -1);
		this->BindObject(eVip_SILVER, 71522, 108, 30.5, -1, -1);
		this->BindObject(eVip_GOLD, 71522, 108, 30.5, -1, -1);
		this->BindObject(eVip_PLATINUM, 71522, 108, 30.5, -1, -1);
	}	
	else
	{
		this->BindObject(eRanking_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(OBJECT_SKIN_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(OBJECT_FLAG_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(OBJECT_DAILY_SYSTEM_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eINVASION_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eVip_BRONZE, 0x7A5E, 108, 29, -1, -1);
		this->BindObject(eVip_SILVER, 0x7A5E, 108, 29, -1, -1);
		this->BindObject(eVip_GOLD, 0x7A5E, 108, 29, -1, -1);
		this->BindObject(eVip_PLATINUM, 0x7A5E, 108, 29, -1, -1);
		this->BindObject(eVip_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eCustomShop_CLOSE_MAIN, 0x7EC5, 36, 29, -1, -1);
#if(LuckyWheelV2)
		this->BindObject(eWindowVongQuay_CLOSE, 0x7EC5, 36, 29, -1, -1);
#endif

		this->BindObject(eCommand_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eJewelBank_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eADDPOINT3_CLOSE, 0x7EC5, 36, 29, -1, -1);

		this->BindObject(eADDPOINT_CLOSE, 0x7EC5, 36, 29, -1, -1);
	}

	this->BindObject(eNextEvent, 0x7903, 25, 40, -1, -1);
	this->BindObject(ePrevEvent, 0x7904, 25, 40, -1, -1);

	this->BindObject(eWAREHOUSE_LEFT, 32345, 22, 20, -1, -1);
	this->BindObject(eWAREHOUSE_RIGHT, 32346, 22, 20, -1, -1);

	this->BindObject(eSTATSADD_TEXTBOX01, 0x9307, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX01, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX02, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX03, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX04, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_STATBOX05, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(eSTATSADD_BTN_OK, 0x7A5B, 54, 30, -1, -1);

	if (gProtect.m_MainInfo.InventoryUpgrade == 1)
	{
		this->BindObject(eMoney1, 0x99090, 170, 26, -1, -1);
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		this->BindObject(eTrash, 0x9993, 43, 17, -1, -1); //909986
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		this->BindObject(eTrash, 0x9993, 24, 24, -1, -1); //909986
	}

	this->BindObject(eTrash_Expanded, 0x9993, 24, 24, -1, -1);
	this->BindObject(eTrash_MAIN, 0x7A5A, 222, 120, -1, -1);
	this->BindObject(eTrash_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eTrash_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eTrash_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eTrash_YES, 0x7B12, 54, 30, -1, -1);
	this->BindObject(eTrash_NO, 0x7B0C, 54, 30, -1, -1);

	this->BindObject(eJewelBank_MAIN, 0x7A5A, 222, 300, -1, -1);
	this->BindObject(eJewelBank_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eJewelBank_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eJewelBank_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eJewelBank_NEXT, 0x7E5A, 20, 22, -1, -1);
	this->BindObject(eJewelBank_PREV, 0x7E59, 20, 22, -1, -1);

	for (int i = 0; i < 150; i++)
	{
		this->BindObject(eJewelBank_WITHDRAW + i, 31743, 16, 16, -1, -1);
	}

	this->BindObject(eJewelBank_Count, 0x17919, 32, 16, -1, -1);

#if(LuckyWheelV2)
	this->BindObject(eWindowVongQuay, 31461, 640, 419, -1, -1);
	this->BindObject(eWindowVongQuay_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eWindowVongQuay_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eWindowVongQuay_FOOTER, 0x7A59, 230, 50, -1, -1);
#endif

	this->BindObject(eVip_MAIN, 0x7A5A, 222, 250, -1, -1);
	this->BindObject(eVip_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(eVip_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(eVip_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(eVip_DIV, 0x7A62, 223, 21, -1, -1);

	this->BindObject(eADDPOINT_MAIN, 0x7A5A, 222, 299, -1, -1);

	this->BindObject(eCommand_MAIN, 0x7A5A, 222, 299, -1, -1);

	this->BindObject(eMAIN_DailySystem, 0x7A5A, 445, 364, 205, -1);

	this->BindObject(eMAIN_ThueFlag, 0x7A5A, 445, 364, 205, -1);

	this->BindObject(OBJECT_PARTYSETTINGS_MAIN, 0x7A5A, 222, 345 + 30, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_SYSTEM_ACTIVE, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_ONLY_GUILD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_ONLY_ALLIANCE, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_ONE_CLASS, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_DARK_WIZARD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_DARK_KNIGHT, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_ELF, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_MAGIC_GLADIATOR, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_DARK_LORD, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_SUMMONER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_RAGE_FIGHTER, 0x7BAE, 15, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_LEVEL_MINUS, 0x7C0D, 16, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_LEVEL_PLUS, 0x7AA4, 16, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_PASSWORD, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(OBJECT_PARTYSETTINGS_OK, 0x7A5B, 54, 30, -1, -1);

	this->BindObject(OBJECT_PARTYSEARCH_MAIN, 0x7A5A, 222, 345, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_DIV, 0x7A62, 223, 21, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_LEFT, 0x7E56, 20, 23, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_RIGHT, 0x7E57, 20, 23, -1, -1);

	this->BindObject(OBJECT_PARTYPASSWORD_MAIN, 0x7A5A, 222, 122, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_TITLE, 0x7A63, 230, 67, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_FRAME, 0x7A58, 230, 15, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_FOOTER, 0x7A59, 230, 50, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_CLOSE, 0x7EC5, 36, 29, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_TEXTBOX, 0x7AA3, 170, 21, -1, -1);
	this->BindObject(OBJECT_PARTYPASSWORD_OK, 0x7A5B, 54, 30, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_IMAGE1, 0x7898, -1, -1, -1, -1);
	this->BindObject(OBJECT_PARTYSEARCH_IMAGE2, 0x7899, -1, -1, -1, -1);

	SetOp((LPVOID)oLoadSomeForm_Call, this->LoadImages, ASM::CALL);

	SetOp((LPVOID)oDrawInterface_Call, this->Work, ASM::CALL);

	SetCompleteHook(0xFF, 0x00633FFB, &this->LoadModels);

	SetCompleteHook(0xE8, 0x00860AF2, this->UpdateKey);
	//==========================================
	// - Remove Texts PShop
	//==========================================
	SetRange((LPVOID)0x00842086, 5, ASM::NOP);
	SetRange((LPVOID)0x0084234F, 5, ASM::NOP);
	SetRange((LPVOID)0x008423C3, 5, ASM::NOP);

	this->item_post_ = nullptr;

#if(INFO_EVENTINVASION)
	gEventInvasion.BinObeject();
#endif
}

InterfaceElement* Interface::GetInfo(short ObjectID)
{
	return &this->Data[ObjectID];
}


void Interface::LoadModels()
{
	pLoadModel(406, "Data\\Custom\\Bmd\\VIP1\\", "musign", -1);
	pLoadTexture(406, "Custom\\Bmd\\VIP1\\", 0x2901, 0x2600, 1);
	pLoadModel(407, "Data\\Custom\\Bmd\\VIP2\\", "musign", -1);
	pLoadTexture(407, "Custom\\Bmd\\VIP2\\", 0x2901, 0x2600, 1);
	pLoadModel(408, "Data\\Custom\\Bmd\\VIP3\\", "musign", -1);
	pLoadTexture(408, "Custom\\Bmd\\VIP3\\", 0x2901, 0x2600, 1);

	pInitModelData2();
}

void Interface::LoadImages()
{
	pLoadImage("Custom\\Interface\\Rank01.tga", 0x7880, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank02.tga", 0x7881, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank03.tga", 0x7882, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank04.tga", 0x7883, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank05.tga", 0x7884, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank06.tga", 0x7885, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank07.tga", 0x7886, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank08.tga", 0x7887, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank09.tga", 0x7888, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank10.tga", 0x7889, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank11.tga", 0x7890, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank12.tga", 0x7891, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank13.tga", 0x7892, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank14.tga", 0x7893, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank15.tga", 0x7894, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank16.tga", 0x7895, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank17.tga", 0x7896, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank18.tga", 0x7897, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank19.tga", 0x7898, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank20.tga", 0x7899, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank21.tga", 0x7900, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Rank22.tga", 0x7901, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Next.tga", 0x7903, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\Previous.tga", 0x7904, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\MU-logo.tga", 0x7905, 0x2601, 0x2901, 1, 0);

	pLoadImage("Custom\\Interface\\Null.tga", 0x9993, 0x2601, 0x2900, 1, 0);
	pLoadImage("Interface\\InGameShop\\ingame_Bt_Delete.tga", 99522, 0x2601, 0x2901, 1, 0);

	if (gProtect.m_MainInfo.InventoryUpgrade == 1)
	{
		pLoadImage("Custom\\Interface\\item_money.tga", 0x99090, GL_LINEAR, GL_CLAMP, 1, 0);
	}

	if (gProtect.m_MainInfo.m_CreateAccount == 1)
	{
		pLoadImage("Custom\\CreateAccount\\b_create.tga", 71620, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\CreateAccount\\Register_back.tga", 71631, GL_LINEAR, GL_CLAMP, 1, 0);
	}

	pLoadImage("Custom\\DailyReward\\closed.tga", 531020, GL_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("Custom\\DailyReward\\opened.tga", 531021, GL_LINEAR, GL_REPEAT, 1, 0);

	pLoadImage("Interface\\newui_number1.tga", 31337, 9729, 10496, 1, 0);

	pLoadImage("Custom\\Interface\\Button.tga", 0x7908, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Interface\\PartySearch_Title.tga", 0x7898, GL_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("Custom\\Interface\\Info_Block.tga", 0x7899, GL_LINEAR, GL_REPEAT, 1, 0);

	if (gProtect.m_MainInfo.CustomMenuType == 1)
	{
		pLoadImage("Custom\\Interface\\Transcur.tga", 0x79346, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\Menu2.tga", 0x7906, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Menu_BG.tga", 0x7907, 0x2601, 0x2901, 1, 0);
	}

	pLoadImage("Custom\\Interface\\MenuPlegable.tga", 500001, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);

	pLoadImage("Logo\\Mu-logo.tga", 531018, GL_LINEAR, GL_REPEAT, 1, 0);
	pLoadImage("Logo\\Mu-logo_g.jpg", 531019, GL_LINEAR, GL_REPEAT, 1, 0);

	//MiniMap
	pLoadImage("Custom\\Maps\\PlayerPoint.jpg", 31460, 0x2600, 0x2900, 1, 0);
	//--
	pLoadImage("Custom\\Maps\\edBtUcx.tga", 31463, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\edBtUcx_1.tga", 31464, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\YYB6BUk.tga", 31465, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_blacksmith.tga", 31466, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Potion.tga", 31467, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_baul.tga", 31468, 0x2601, 0x2900, 1, 0); //-- Dungeon
	pLoadImage("Custom\\Maps\\mini_map_ui_Que.tga", 31469, 0x2601, 0x2900, 1, 0); //-- Dungeon

	pLoadImage("Custom\\Maps\\mini_map_ui_monsterred.tga", 31471, 0x2601, 0x2900, 1, 0); //-- Dungeon Red
	pLoadImage("Custom\\Maps\\mini_map_ui_monsterblue.tga", 31472, 0x2601, 0x2900, 1, 0); //-- Dungeon Blue
	pLoadImage("Custom\\hudMap_I4.tga", 31473, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Maps\\mini_map_ui_party.tga", 61520, 0x2601, 0x2901, 1, 0);

	pLoadImage("Custom\\Interface\\Title.tga", 0x8916, 0x2601, 0x2900, 1, 0);
	pLoadImage("Custom\\Interface\\InfoBlock.tga", 0x8917, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Interface\\GFx\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\GFx\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\GFx\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\GFx\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\GFx\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\MiniMapBrujula.tga", 73520, GL_LINEAR, GL_REPEAT, 1, 0);

	//JewelBank
	pLoadImage("Custom\\Interface\\NumberWhite.tga", 31337, 9729, 10496, 1, 0);
	pLoadImage("Custom\\Interface\\CheckBox.tga", 0x17919, GL_LINEAR, GL_CLAMP, 1, 0);
	pLoadImage("Custom\\Interface\\Page_Porcento.tga", 0x1791A, 0x2601, 0x2901, 1, 0);

	pLoadImage("Local\\Eng\\ImgsMapName\\Frame.tga", 31607, 0x2601, 0x2900, 1, 0);

	pLoadImage("Custom\\Interface\\bg500buttom.tga", 61322, 0x2601, 0x2901, 1, 0);
	pLoadImage("Custom\\Interface\\bg500top.tga", 61323, 0x2601, 0x2901, 1, 0);

	switch (gProtect.m_MainInfo.CustomInterfaceType)
	{
	case Classic:
		pLoadImage("Custom\\Interface\\TimeBar.tga", 0x787F, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Render_buttom_1.tga", 715277, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Decor.tga", 87968, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\InterfaceBar.tga", 87969, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\Classic\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
		break;
	case Ex700:
		pLoadImage("Custom\\Interface\\TimeBar.tga", 0x787F, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\Render_buttom_2.tga", 71522, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_Skillbox.tga", 51500, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox2.jpg", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\item_pbtnbg.tga", 61547, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\skill_render.tga", 61546, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\popup_line_s.tga", 71520, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
		//--
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_IE.tga", 31293, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_IE_Exp.tga", 59000, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_I1.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_I4.jpg", 31300, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_I5.jpg", 31299, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox2.tga", 31313, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\newui_skillbox.tga", 31312, GL_LINEAR, GL_CLAMP, 1, 0);
		//-- Atributos de personaje
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\guege_mp.tga", 31296, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\guege_mp_1.tga", 51501, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\guege_hp_green.tga", 31297, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\guege_hp.tga", 31298, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\guege_hp_1.tga", 51502, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Main_IE_Buttons.tga", 0x901, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_buttom_up.tga", 51552, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_buttom_down.tga", 51551, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg03.tga", 51545, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_up.tga", 31270, 9729, 10496, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_m.tga", 31271, 9729, 10496, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_scrollbar_down.tga", 31272, 9729, 10496, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_Scrollbar_stretch.tga", 31275, 9729, 10496, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Main01.tga", 51529, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Main02.tga", 51541, GL_LINEAR, GL_CLAMP, 1, 0);
		for (int i = 51530; i < 51534; ++i) {
			pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_Button.tga", i, GL_LINEAR, GL_CLAMP, 1, 0);
		}
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonWBack.tga", 51538, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonSize.tga", 51539, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonTransparencyA.tga", 51540, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide01.tga", 51542, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide02.tga", 51543, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_ButtonHide03.tga", 51544, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg01.tga", 61550, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg02.tga", 61551, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\chat_bg03.tga", 61534, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\Chat_I5.tga", 61548, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Chat\\newui_chat_back.tga", 61549, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Render_buttom_1.tga", 71521, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\InventoryFrame_RuudShop.tga", 61560, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Menu_RuudShopFrame.tga", 61561, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\Menu_Button03.tga", 61562, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\RuudShop\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);

		//AdvancedUI
		// 
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I1.tga", 61522, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I2.tga", 61523, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I3.tga", 61524, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\Frame_I3.tga", 61526, GL_LINEAR, GL_CLAMP, 1, 0); //-- All Window
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\InventoryFrame_I4.tga", 61527, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\Draw_money.tga", 61528, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\button_close.tga", 61529, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\CharacterInfoFrame_I1.tga", 61532, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\newui_chainfo_btn_level.tga", 61533, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\ButtonCharacterInfo.tga", 61535, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\CharacterInfoFrame_I2.tga", 61538, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\BaulFrame_I1.tga", 61539, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\BaulFrame_I2.tga", 61540, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\ShopFrame_I1.tga", 61541, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\newSytemButton.tga", 61542, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\ShopFrame_I2.tga", 61543, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\StoreFrame_I1.tga", 61544, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\Render_buttom_3.tga", 71524, 0x2601, 0x2901, 1, 0); //esquina abajo derecha

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\UI\\winPet_I1.tga", 61545, GL_LINEAR, GL_CLAMP, 1, 0);

		//-- Botones del Main
		pLoadImage("Custom\\Interface\\none.tga", 31461, 0x2601, 0x2900, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31303, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31304, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31305, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31306, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31307, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\none.tga", 51522, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31294, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31295, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\none.tga", 31292, GL_LINEAR, GL_CLAMP, 1, 0);

		//-- Folder MacroUI
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Main.tga", 51550, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_BSetup.tga", 51546, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_BStart.tga", 51547, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Stop.tga", 51548, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Bar.jpg", 51549, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\MacroUI\\MacroUI_Menu.tga", 120111, GL_LINEAR, GL_CLAMP, 1, 0);

		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\PartyFrame_I3.tga", 81525, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_hpbar.tga", 81526, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_mpbar.tga", 81527, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_crown.tga", 81528, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_bg.tga", 81529, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_xbtn01_1.tga", 81530, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_bg01.tga", 81531, GL_LINEAR, GL_CLAMP, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\EX700\\Party\\party_xbtn02_1.tga", 81532, GL_LINEAR, GL_CLAMP, 1, 0);
		//--
		break;
	}

	if (gProtect.m_MainInfo.ItemTooltipUpgrade == 1)
	{
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg01.tga", 61511, 0x2601, 0x2901, 1, 0); //esquina arriba izquierda
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg02.tga", 61512, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg03.tga", 61513, 0x2601, 0x2901, 1, 0); //esquina arriba derecha
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg04.tga", 61514, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg06.tga", 61515, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg07.tga", 61516, 0x2601, 0x2901, 1, 0); //esquina abajo izquierda
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg08.tga", 61517, 0x2601, 0x2901, 1, 0);
		pLoadImage("Custom\\Interface\\CustomInterface\\tooltip_bg09.tga", 61518, 0x2601, 0x2901, 1, 0); //esquina abajo derecha
	}

	if (gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCloak.LoadTexture();
	}

	nInterface.Load();

	// ----
	pLoadSomeForm();
}

void Interface::BindObject(short MonsterID, DWORD ModelID, float Width, float Height, float X, float Y)
{
	this->Data[MonsterID].EventTick = 0;
	this->Data[MonsterID].OnClick = false;
	this->Data[MonsterID].OnShow = false;
	this->Data[MonsterID].ModelID = ModelID;
	this->Data[MonsterID].Width = Width;
	this->Data[MonsterID].Height = Height;
	this->Data[MonsterID].X = X;
	this->Data[MonsterID].Y = Y;
	this->Data[MonsterID].MaxX = X + Width;
	this->Data[MonsterID].MaxY = Y + Height;
	this->Data[MonsterID].Attribute = 0;
}

void Interface::DrawGUI(short ObjectID, float PosX, float PosY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawGUI2(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;

	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawIMG(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}

	pDrawImage(this->Data[ObjectID].ModelID, PosX, PosY, this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, ScaleX, ScaleY, 1, 1, 0);
}

void Interface::ResetDrawIMG(short ObjectID)
{
	if (this->Data[ObjectID].X != -1 || this->Data[ObjectID].Y != -1)
	{
		this->Data[ObjectID].X = -1;
		this->Data[ObjectID].Y = -1;
		this->Data[ObjectID].MaxX = -1;
		this->Data[ObjectID].MaxY = -1;
	}
}

void Interface::Work()
{
	gInterface.DrawMenuTrash();
	gInterface.DrawMenuTrash_Warning();
	gObjUser.Refresh();
	ReconnectMainProc();
	gInterface.DrawConfirmOpen();
	gWarehouse.ButtonsDraw();

	if (gProtect.m_MainInfo.EnableCommandButton == 1)
	{
		gCustomCommandInfo.DrawCommandWindow();
#if(QuickAddStats)
		gQuickAddStats.Draw();
		gQuickAddStats.DrawStatsAddWindow_STR();
		gQuickAddStats.DrawStatsAddWindow_AGI();
		gQuickAddStats.DrawStatsAddWindow_VIT();
		gQuickAddStats.DrawStatsAddWindow_ENE();
		gQuickAddStats.DrawStatsAddWindow_CMD();
#endif
	}

	//gQuickAddStats.Draw();
	//gQuickAddStats.DrawStatsAddWindow_STR();
	//gQuickAddStats.DrawStatsAddWindow_AGI();
	//gQuickAddStats.DrawStatsAddWindow_VIT();
	//gQuickAddStats.DrawStatsAddWindow_ENE();
	//gQuickAddStats.DrawStatsAddWindow_CMD();

	gRenderMap.AutoSendMove();

	if (gProtect.m_MainInfo.EnableDailyRewardButton == 1)
	{
		DailyReward.Draw();
	}

	if (MiniMapType == 1)
	{
		gInterface.DrawMiniMap();
	}

	if (MiniMapType == 2)
	{
		gInterface.DrawMiniMap();
	}

	if (gProtect.m_MainInfo.ShowInfoWindowedMode)
	{
		gInterface.WindowedModeName();
	}

	if (TimerBar == 0)
	{
		gInterface.DrawTimeUI();
	}

	if (DisablePing == 0)
	{
		gCustomPing.ShowPing();
	}

	if (pPlayerState == 5)
	{
		gCustomPing.StartPing();
	}

	if (gProtect.m_MainInfo.EnableAntilagSystemButton == 1)
	{
		gAntiLagSystem.Draw();
	}

	if (gProtect.m_MainInfo.EnableVipShopButton == 1)
	{
		gBuyVip.Draw();
		gBuyVip.DrawConfirm();
	}

#if(INFO_EVENTINVASION)
	if (gProtect.m_MainInfo.ActiveInvasion == 1)
	{
		gEventInvasion.OpenMain();
		gEventInvasion.Draw();
	}
#endif

#if(LuckyWheelV2)
	if (gProtect.m_MainInfo.EnableLuckySpinV2Button == 1)
	{
		gInterface.DrawWindowVQ();
	}
#endif

	if (gProtect.m_MainInfo.JewelBankSwitch == 1)
	{
		gCustomJewelBank.DrawJewelBankWindow();
	}

#if(MAP_USAGE)
	gInterface.DrawTimeUseMap();
#endif

	if (gProtect.m_MainInfo.EnableEventTimeButton == 1)
	{
		gCustomEventTime.DrawEventTimePanelWindow();
	}

	gPKNotice.DrawNoticePKSystem();

	gPartySearchSettings.draw_party_settings_window();
	gPartySearch.draw_party_search();
	gPartySearch.draw_party_password();
	gInterface.DrawPartyMenu();

	if (GetKeyState(VK_SNAPSHOT) < 0)
	{
		gInterface.DrawLogo(1);
	}

	if (gElemental.LockMouse != 0)
	{
		if (gElemental.LockMouse > GetTickCount())
		{
			pSetCursorFocus = true;
		}
		else
		{
			gElemental.LockMouse = 0;
			pSetCursorFocus = false;
		}
	}

	if (nInterface.ActiveLockMouse != 0)
	{
		if (nInterface.ActiveLockMouse > GetTickCount())
		{
			pSetCursorFocus = true;
		}
		else
		{
			nInterface.ActiveLockMouse = 0;
			pSetCursorFocus = false;
		}
	}

	if (gProtect.m_MainInfo.EnableEventTimeButton == 1)
	{
		if (GetKeyState('H') & 0x4000 && GetTickCount() >= gCustomEventTime.OpenTestDelay + 250)
		{
			if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				if (gCustomEventTime.CheckTestWindow())
				{
					gCustomEventTime.CloseTestWindow();
				}
				else
				{
					gCustomEventTime.ClearCustomEventTime();

					PMSG_CUSTOM_EVENTTIME_SEND pMsg;

					pMsg.header.set(0xF3, 0xE8, sizeof(pMsg));

					DataSend((BYTE*)&pMsg, pMsg.header.size);

					gCustomEventTime.OpenTestWindow();
				}
				gCustomEventTime.OpenTestDelay = GetTickCount();
			}
		}
	}

	if (gProtect.m_MainInfo.EnableAntilagSystemButton == 1)
	{
		if (GetKeyState(VK_F6) & 0x4000 && GetTickCount() >= gAntiLagSystem.OpenTestDelay + 250)
		{
			if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				if (gAntiLagSystem.CheckTestWindow())
				{
					gAntiLagSystem.Click = false;
					gAntiLagSystem.CloseTestWindow();
				}
				else
				{
					gAntiLagSystem.Click = true;
					gAntiLagSystem.OpenTestWindow();
				}
				gAntiLagSystem.OpenTestDelay = GetTickCount();
			}
		}
	}

#if(LuckyWheelV2)
	if (gProtect.m_MainInfo.EnableLuckySpinV2Button == 1)
	{
		if (GetKeyState(VK_F9) & 0x4000)
		{
			gInterface.OpenWindowVongQuay();
		}
	}
#endif

	if (gProtect.m_MainInfo.JewelBankSwitch == 1)
	{
		if (GetKeyState('J') & 0x4000 && GetTickCount() >= gCustomJewelBank.OpenTestDelay + 250)
		{
			if (GetForegroundWindow() == pGameWindow && !gInterface.CheckWindow(ObjWindow::ChatWindow))
			{
				if (gInterface.Data[eJewelBank_MAIN].OnShow)
				{
					return;
				}
				else
				{
					gCustomJewelBank.OpenWindow();
				}
			}
		}
	}

	if (gProtect.m_MainInfo.EnableCustomXShopButton == 1)
	{
		gNewCashShop.DrawShop();
		gElemental.DrawMessageBox();
	}

#if FLAG
	if (gProtect.m_MainInfo.EnableCustomFlagButton == 1)
	{
		ThueFlag.Draw();
	}
#endif

	if (gProtect.m_MainInfo.EnableCustomRanking == 1)
	{
		gCustomRanking.DrawRankPanelWindow();
	}

	jCRenderRuud.CheckOpen();

	if (gProtect.m_MainInfo.DisableAdvance == 0)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			g_StatsAdvance.DrawInfo();
		}
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{
			gInterface.DrawMenu();
		}
	}

#if(MENU_NEW)
	gInterface.DrawMenuWindow();
#endif

	gInterface.DrawLogo(0);

	pDrawInterface();
}

bool Interface::UpdateKey(DWORD Class)
{
	if (pIsKeyPress(VK_ESCAPE))
	{
		pSetCursorFocus = false;

		if (gInterface.Data[eADDPOINT3_MAIN].OnShow)
		{
			gInterface.Data[eADDPOINT3_MAIN].OnShow = false;
			return false;
		}

		if (gInterface.Data[eTrash_MAIN].OnShow)
		{
			gInterface.Data[eTrash_MAIN].OnShow = false;
			return false;
		}
		
		if (gInterface.Data[eMENU_MAIN].OnShow)
		{
			gInterface.Data[eMENU_MAIN].OnShow = false;
			return false;
		}
		
		if (gInterface.Data[eJewelBank_MAIN].OnShow)
		{
			gInterface.Data[eJewelBank_MAIN].OnShow = false;
			return false;
		}

		if (gInterface.Data[OBJECT_PARTYSETTINGS_MAIN].OnShow)
		{
			gInterface.Data[OBJECT_PARTYSETTINGS_MAIN].Close();
			return false;
		}

		if (gInterface.Data[OBJECT_PARTYMENU_MAIN].OnShow)
		{
			gInterface.Data[OBJECT_PARTYMENU_MAIN].Close();
			return false;
		}

		if (gInterface.Data[OBJECT_PARTYSEARCH_MAIN].OnShow)
		{
			gInterface.Data[OBJECT_PARTYSEARCH_MAIN].Close();
			return false;
		}

		if (gInterface.Data[OBJECT_PARTYPASSWORD_MAIN].OnShow)
		{
			gInterface.Data[OBJECT_PARTYPASSWORD_MAIN].Close();
			return false;
		}

#if(LuckyWheelV2)
		if (gInterface.Data[eWindowVongQuay].OnShow)
		{
			gInterface.Data[eWindowVongQuay].OnShow = false;
			return false;
		}
#endif

		if (gInterface.Data[eCustomShop].OnShow)
		{
			gInterface.Data[eCustomShop].OnShow = false;
			return false;
		}
		
		if (gInterface.Data[eADDPOINT_MAIN].OnShow)
		{
			gInterface.Data[eADDPOINT_MAIN].OnShow = false;
			return false;
		}

		if (gInterface.Data[eCommand_MAIN].OnShow)
		{
			gInterface.Data[eCommand_MAIN].OnShow = false;
			return false;
		}

		if (gInterface.Data[eMAIN_DailySystem].OnShow)
		{
			gInterface.Data[eMAIN_DailySystem].OnShow = false;
			return false;
		}

		if (gInterface.Data[eMAIN_ThueFlag].OnShow)
		{
			gInterface.Data[eMAIN_ThueFlag].OnShow = false;
			return false;
		}

		if (gInterface.Data[eRankPANEL_MAIN].OnShow)
		{
			gInterface.Data[eRankPANEL_MAIN].OnShow = false;
			return false;
		}

		if (gInterface.Data[eVip_MAIN].OnShow)						// Sistema de compra vip
		{
			if (gInterface.Data[eVip_MAIN].OnShow && gBuyVip.JanelaConfirmVip > 0)
			{
				gBuyVip.JanelaConfirmVip = 0;
			}
			else if (gInterface.Data[eVip_MAIN].OnShow && gBuyVip.JanelaConfirmVip == 0)
			{
				gBuyVip.JanelaConfirmVip = 0;
				gInterface.Data[eVip_MAIN].OnShow = false;
			}
			return false;
		}
	}
		if (pIsKeyPress(VK_F3) && gProtect.m_MainInfo.EnablePartySearch == 1)
		{
			gPartySearchSettings.party_search_settings_switch_state();
		}

		static DWORD HelperTickCount = 0;
		if (pIsKeyPress(VK_MBUTTON) && GetTickCount() > HelperTickCount + 300)
		{
			DWORD pHelper = *(DWORD*)MAIN_HELPER_STRUCT;
			if (pHelper != 0)
			{
				BYTE isHelperOn = *(BYTE*)(pHelper + 0x08);
				if (isHelperOn == 0)
				{
					bool inSafeZone = *(bool*)(MAIN_CHARACTER_STRUCT + 0x0E);
					if (inSafeZone)
					{
						pDrawMessage("No se puede activar el Helper en zona segura.", 1);
					}
					else
					{
						pMUHelperStart((LPVOID)pHelper);
					}
				}
				else
				{
					pMUHelperClose((LPVOID)pHelper);
				}
			}
			HelperTickCount = GetTickCount();
		}

	return ((bool(__thiscall*)(DWORD))0x815B50)(*(DWORD*)Class);
}

#include "InterfaceS8AdvancedUI.h"
#include "Defines2.h"
void Interface::InventoryUpgrade(int a1, int a2, int a3, int a4)
{
	int v10;
	int v11;
	DWORD v23;
	v10 = *(DWORD*)(a1 + 40);
	v11 = *(DWORD*)(a1 + 36);
	v23 = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);

	char MoneyBuff1[256], MoneyBuff2[256];
	ZeroMemory(MoneyBuff1, sizeof(MoneyBuff1));
	ZeroMemory(MoneyBuff2, sizeof(MoneyBuff2));

	pGetMoneyFormat(v23, MoneyBuff1, 0);
	pGetMoneyFormat(Ruud, MoneyBuff2, 0);

	DWORD Color = eWhite;
	DWORD Color2 = eWhite;;

	if (v23 >= 0 && v23 <= 99999)
	{
		Color = eWhite;
	}
	else if (v23 >= 100000 && v23 <= 999999)
	{
		Color = eShinyGreen;
	}
	else if (v23 >= 1000000 && v23 <= 9999999)
	{
		Color = eGold;
	}
	else if (v23 >= 10000000 && v23 <= 99999999)
	{
		Color = eOrange;
	}
	else if (v23 >= 100000000 && v23 <= 2000000000)
	{
		Color = eRed;
	}

	if (Ruud >= 0 && Ruud <= 99999)
	{
		Color2 = eWhite;
	}
	else if (Ruud >= 100000 && Ruud <= 999999)
	{
		Color2 = eShinyGreen;
	}
	else if (Ruud >= 1000000 && Ruud <= 9999999)
	{
		Color2 = eGold;
	}
	else if (Ruud >= 10000000 && Ruud <= 99999999)
	{
		Color2 = eOrange;
	}
	else if (Ruud >= 100000000 && Ruud <= 2000000000)
	{
		Color2 = eRed;
	}

	//--
	gInterface.DrawGUI(eMoney1, v11 + 10, v10 + 364);

	CustomFont.Draw((HFONT)pFontNormal, v11 + 48, v10 + 371, Color, 0x0, 50, 0, 1, "%s", MoneyBuff1);

	CustomFont.Draw((HFONT)pFontNormal, v11 + 120, v10 + 371, Color2, 0x0, 50, 0, 1, "%s", MoneyBuff2);


	// -- Posicionamento das janelas (X,Y)
	int This = GetInventory(GetInstance());
	int x = *(signed int*)(This + 36);
	int y = *(signed int*)(This + 40);

	// -- Texto ID 223 (Inventory)
	pSetFont(pTextThis(), (int)pFontBold);
	pSetTextColor(pTextThis(), 255, 255, 255, 255);
	pSetBackgroundTextColor(pTextThis(), 255, 255, 255, 0);
	//pDrawText(pTextThis(), x, y + 12, pGetTextLine(pTextLineThis, ((gVisualInventory.InventoryVisualOpen == 0 ? 223 : 9990))), 190, 0, (PINT)3, 0);

	// -- Texto do valor de Zen no inventário

	DWORD dwZen = *(DWORD*)(*(DWORD*)0x8128AC4 + 5956);

}

void Interface::WindowedModeName()
{
	char interaltas[600];

	DWORD elapsed2 = GetTickCount() - gCustomPing.TickCount;

	gCustomPing.m_fpscount++;

	// one second elapsed? (= 1000 milliseconds)
	if (elapsed2 > 1000)
	{
		// save the current counter value to m_fps
		gCustomPing.m_fps = gCustomPing.m_fpscount;
		// reset the counter and the interval
		gCustomPing.m_fpscount = 0;
		// set tick count
		gCustomPing.TickCount = GetTickCount();
	}

	time_t TimeServer;
	struct tm* ServerT;
	time(&TimeServer);
	ServerT = gmtime(&TimeServer);

	if (gProtect.m_MainInfo.ShowInfoWindowedModeType == 1)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s] [Ping: %d] [FPS: %d]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name, gCustomPing.PingDelayRecv, gCustomPing.m_fps);
	}
	else if (gProtect.m_MainInfo.ShowInfoWindowedModeType == 2)
	{
		sprintf_s(interaltas, sizeof(interaltas), "%s [Player: %s]", gProtect.m_MainInfo.WindowName, gObjUser.lpPlayer->Name);
	}

	SetWindowText(pGameWindow, interaltas);
	
	// Draw it on screen so it's visible in all resolutions (including borderless/fullscreen)
	pSetBlend(1);
	gInterface.DrawFormat(eWhite, 0, 0, 640, 3, interaltas);
	pGLSwitchBlend();

}


void Interface::DrawTimeUI()
{
	if (TimerBar == 1 || (this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::FullMap) || this->CheckWindow(ObjWindow::ChatWindow) || this->CheckWindow(ObjWindow::SkillTree)
		|| this->CheckWindow(ObjWindow::MoveList) || pMapNumber == 34 || pMapNumber == 30))
	{
		return;
	}
	//--

	// -----
	time_t TimeServer, TimeLocal;
	struct tm* ServerT, * LocalT;
	time(&TimeServer);
	time(&TimeLocal);
	// ----
	ServerT = gmtime(&TimeServer);
	// ----
	char ServerTimeName[25] = "Server:";
	char ServerTime[30];

	// -----
	LocalT = localtime(&TimeLocal);
	// -----
	char LocalTimeName[25] = "Local:";

	// Use standard 640x480 scaled coordinates for all resolutions
	this->DrawGUI(eTIME, this->Data[eTIME].X - 9, this->Data[eTIME].Y); 

	gInterface.DrawFormat(eGold, this->Data[eTIME].X - 77, this->Data[eTIME].Y + 54, 210, 3, "Server:");
	gInterface.DrawFormat(eWhite, this->Data[eTIME].X + 65, this->Data[eTIME].Y + 54, 100, 1, "%2d:%02d:%02d", (ServerT->tm_hour + GMT) % 24, ServerT->tm_min, ServerT->tm_sec);

	gInterface.DrawFormat(eGold, this->Data[eTIME].X - 78, this->Data[eTIME].Y + 30, 210, 3, "Local :");
	gInterface.DrawFormat(eWhite, this->Data[eTIME].X + 65, this->Data[eTIME].Y + 30, 100, 1, "%2d:%02d:%02d", LocalT->tm_hour, LocalT->tm_min, LocalT->tm_sec);
}


int Interface::DrawFormat(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	int LineCount = 0;

	char* Line = strtok(Buff, "\n");

	while (Line != NULL)
	{
		pDrawColorText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}

	return PosY;
}

bool Interface::CheckWindow(int WindowID)
{
	return pCheckWindow(pWindowThis(), WindowID);
}
int Interface::CloseWindow(int WindowID)
{
	return pCloseWindow(pWindowThis(), WindowID);
}
int Interface::OpenWindow(int WindowID)
{
	return pOpenWindow(pWindowThis(), WindowID);
}

bool Interface::IsWorkZone(short ObjectID)
{
	if ((gObjUser.m_CursorX < this->Data[ObjectID].X || gObjUser.m_CursorX > this->Data[ObjectID].MaxX) || (gObjUser.m_CursorY < this->Data[ObjectID].Y || gObjUser.m_CursorY > this->Data[ObjectID].MaxY))
		return false;

	return true;
}

bool Interface::IsWorkZone(float X, float Y, float MaxX, float MaxY, bool a5)
{
	if (a5)
	{
		if ((pCursorX < X || pCursorX > X + MaxX) || (pCursorY < Y || pCursorY > Y + MaxY))
			return false;
		return true;
	}
	if ((pCursorX < X || pCursorX > MaxX) || (pCursorY < Y || pCursorY > MaxY))
		return false;
	return true;
}

bool Interface::IsWorkZone1(WORD x, WORD y, WORD x2, WORD y2)
{
	return pCursorX >= x && pCursorX <= x2 && pCursorY >= y && pCursorY <= y2;
}

bool Interface::IsWorkZone2(short ObjectID)
{
	float PosX = this->Data[ObjectID].X;
	float MaxX = PosX + this->Data[ObjectID].Width;

	if (((float)pCursorX < PosX || (float)pCursorX > MaxX) || ((float)pCursorY < this->Data[ObjectID].Y || (float)pCursorY > this->Data[ObjectID].MaxY))
	{
		return false;
	}

	return true;
}

bool Interface::IsWorkZone4(float x, float y, float x2, float y2)
{
	bool result = GetForegroundWindow() == pGameWindow && pCursorX >= x && pCursorX <= x + x2 && pCursorY >= y && pCursorY <= y + y2;
	return result;
}

float Interface::GetResizeX(short ObjectID)
{
	if (pWinWidth == 800)
	{
		return this->Data[ObjectID].X + 16.0;
	}
	else if (pWinWidth != 1024)
	{
		return this->Data[ObjectID].X - 16.0;
	}

	return this->Data[ObjectID].X;
}

int Interface::DrawToolTip(int X, int Y, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	return pDrawToolTip(X, Y, Buff);
}

int Interface::DrawMessage(int Mode, LPCSTR Text, ...)
{
	char Buff[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----
	return pDrawMessage(Buff, Mode);
}


float Interface::DrawRepeatGUI(short MonsterID, float X, float Y, int Count)
{
	float StartY = Y;
	// ----
	for (int i = 0; i < Count; i++)
	{
		pDrawGUI(this->Data[MonsterID].ModelID, X, StartY,
			this->Data[MonsterID].Width, this->Data[MonsterID].Height);
		// ----
		StartY += this->Data[MonsterID].Height;
	}
	// ----
	return StartY;
}

void Interface::DrawButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::DrawColoredGUI(short ObjectID, float X, float Y, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = X;
		this->Data[ObjectID].Y = Y;
		this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawLogo(bool active)
{
	if (gProtect.m_MainInfo.PrintLogo != 0)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
		{
			if (active == 1)
			{
				this->Data[eLogo].EventTick = GetTickCount() + 1500;
			}

			if (gInterface.Data[eLogo].EventTick > GetTickCount())
			{
				if (gProtect.m_MainInfo.PrintLogo == 1)
				{
					this->DrawGUI(eLogo, 10, 10);
				}

				if (gProtect.m_MainInfo.PrintLogo == 2)
				{
					this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, 10);

				}

				if (gProtect.m_MainInfo.PrintLogo == 3)
				{
					this->DrawGUI(eLogo, 10, MAX_WIN_HEIGHT - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 4)
				{
					this->DrawGUI(eLogo, MAX_WIN_WIDTH - 160, MAX_WIN_HEIGHT - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 5)
				{
					this->DrawGUI(eLogo, (MAX_WIN_WIDTH / 2) - (150 / 2), (MAX_WIN_HEIGHT / 2) - (114 / 2));
				}
			}
		}
		else
		{
			if (active == 1)
			{
				this->Data[eLogo].EventTick = GetTickCount() + 1500;
			}

			if (gInterface.Data[eLogo].EventTick > GetTickCount())
			{
				if (gProtect.m_MainInfo.PrintLogo == 1)
				{
					this->DrawGUI(eLogo, 10, 10);
				}

				if (gProtect.m_MainInfo.PrintLogo == 2)
				{
					this->DrawGUI(eLogo, 640 - 160, 10);

				}

				if (gProtect.m_MainInfo.PrintLogo == 3)
				{
					this->DrawGUI(eLogo, 10, 480 - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 4)
				{
					this->DrawGUI(eLogo, 640 - 160, 480 - 144);
				}

				if (gProtect.m_MainInfo.PrintLogo == 5)
				{
					this->DrawGUI(eLogo, (640 / 2) - (150 / 2), (480 / 2) - (114 / 2));
				}
			}
		}
	}
}

void Interface::DrawAnimatedGUI(short ObjectID, float PosX, float PosY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawGUI(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height);
}

void Interface::DrawMenuWindow()
{
	if (this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Warehouse) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse))
		return;

	if (!this->Data[eMENU_MAIN].OnShow)
	{
		return;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		if (this->Data[eMENU_MAIN].ByClose == false)
		{
			if (this->Data[eMENU_MAIN].OpenedValue < 0)
			{
				this->Data[eMENU_MAIN].OpenedValue += this->Data[eMENU_MAIN].Speed;

				if (this->Data[eMENU_MAIN].OpenedValue >= -150)
				{
					this->Data[eMENU_MAIN].Speed = 5;
				}

				if (this->Data[eMENU_MAIN].OpenedValue > 0)
				{
					this->Data[eMENU_MAIN].OpenedValue = 0;
				}
			}
		}
		else
		{
			if (this->Data[eMENU_MAIN].OpenedValue > -226)
			{
				this->Data[eMENU_MAIN].OpenedValue -= this->Data[eMENU_MAIN].Speed;

				if (this->Data[eMENU_MAIN].OpenedValue <= -150)
				{
					this->Data[eMENU_MAIN].Speed = 10;
				}

				if (this->Data[eMENU_MAIN].OpenedValue <= -226)
				{
					this->Data[eMENU_MAIN].Close();
				}
			}
		}
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (this->Data[eMENU_MAIN].ByClose == false)
		{
			if (this->Data[eMENU_MAIN].OpenedValue < 0)
			{
				this->Data[eMENU_MAIN].OpenedValue += this->Data[eMENU_MAIN].Speed;

				if (this->Data[eMENU_MAIN].OpenedValue >= -150)
				{
					this->Data[eMENU_MAIN].Speed = 5;
				}

				if (this->Data[eMENU_MAIN].OpenedValue > 0)
				{
					this->Data[eMENU_MAIN].OpenedValue = 0;
				}
			}
		}
		else
		{
			if (this->Data[eMENU_MAIN].OpenedValue > -226)
			{
				this->Data[eMENU_MAIN].OpenedValue -= this->Data[eMENU_MAIN].Speed;

				if (this->Data[eMENU_MAIN].OpenedValue <= -150)
				{
					this->Data[eMENU_MAIN].Speed = 10;
				}

				if (this->Data[eMENU_MAIN].OpenedValue <= -226)
				{
					this->Data[eMENU_MAIN].Close();
				}
			}
		}
	}

	float MainWidth = 230.0;
	float StartY = 100;
	float StartX = this->Data[eMENU_MAIN].OpenedValue;

	const float buttonSpacing = 29.0f;
	const float leftColumnX = StartX + 17;
	const float rightColumnX = StartX + 140;
	const float textOffsetXLeft = StartX - 35;
	const float textOffsetXRight = StartX + 88;
	const float textOffsetY = 10;

	struct MenuButton {
		int id;
		bool enabled;
		bool isLeftColumn;
		int messageId;
		int originalPosition;
	};

	MenuButton allButtons[] = {
		{eBUTTON_MENU_1, gProtect.m_MainInfo.EnableEventTimeButton == 1, true, 25, 1},
		{eBUTTON_MENU_2, gProtect.m_MainInfo.EnableVipShopButton == 1, true, 26, 2},
		{eBUTTON_MENU_3, gProtect.m_MainInfo.EnableCommandButton == 1, true, 27, 3},
		{eBUTTON_MENU_4, gProtect.m_MainInfo.EnableCustomFlagButton == 1, true, 28, 4},
		{eBUTTON_MENU_5, gProtect.m_MainInfo.EnableCustomSkinButton == 1, true, 29, 5},
		{eBUTTON_MENU_6, gProtect.m_MainInfo.EnableCustomButton1 == 1, true, 30, 6},
		{eBUTTON_MENU_7, gProtect.m_MainInfo.EnableCustomButton2 == 1, true, 31, 7},
		{eBUTTON_MENU_8, gProtect.m_MainInfo.EnableCustomRanking == 1, true, 32, 8},
		{eBUTTON_MENU_9, gProtect.m_MainInfo.JewelBankSwitch == 1, false, 105, 9},
		{eBUTTON_MENU_10, gProtect.m_MainInfo.EnableDailyRewardButton == 0, false, 106, 10},
		{eBUTTON_MENU_11, gProtect.m_MainInfo.EnableLuckySpinV2Button == 1, false, 107, 11},
		{eBUTTON_MENU_12, gProtect.m_MainInfo.EnableCustomXShopButton == 1, false, 108, 12},
		{eBUTTON_MENU_13, gProtect.m_MainInfo.EnableAntilagSystemButton == 1, false, 109, 13}
	};

	std::vector<MenuButton> activeButtons;
	std::vector<MenuButton> leftButtons;
	std::vector<MenuButton> rightButtons;

	for (const auto& button : allButtons) {
		if (button.enabled) {
			activeButtons.push_back(button);
		}
	}

	std::sort(activeButtons.begin(), activeButtons.end(), [](const MenuButton& a, const MenuButton& b) {
		return a.originalPosition < b.originalPosition;
		});

	int totalButtons = activeButtons.size();
	int leftColumnCount = (totalButtons + 1) / 2;

	for (int i = 0; i < activeButtons.size(); ++i) {
		if (i < leftColumnCount) {
			leftButtons.push_back(activeButtons[i]);
		}
		else {
			rightButtons.push_back(activeButtons[i]);
		}
	}

	if (leftButtons.empty() && !rightButtons.empty()) {
		leftButtons = rightButtons;
		rightButtons.clear();
	}

	RenderBitmap(500001, StartX + 0, StartY + 80, 0, 330, 0, 0, 1, 1, 1, 1, 0.0);

	float currentLeftY = StartY + 20;
	for (const auto& button : leftButtons) {
		this->DrawAnimatedGUI(button.id, leftColumnX, currentLeftY);
		if (this->IsWorkZone(button.id)) {
			DWORD Color = eGray150;
			this->DrawColoredGUI(button.id, this->Data[button.id].X, this->Data[button.id].Y, Color);
		}
		this->DrawFormat(eWhite, textOffsetXLeft, currentLeftY + textOffsetY, 210, 3, gCustomMessage.GetMessage(button.messageId));
		currentLeftY += buttonSpacing;
	}

	float currentRightY = StartY + 20;
	for (const auto& button : rightButtons) {
		this->DrawAnimatedGUI(button.id, rightColumnX, currentRightY);
		if (this->IsWorkZone(button.id)) {
			DWORD Color = eGray150;
			this->DrawColoredGUI(button.id, this->Data[button.id].X, this->Data[button.id].Y, Color);
		}
		this->DrawFormat(eWhite, textOffsetXRight, currentRightY + textOffsetY, 210, 3, gCustomMessage.GetMessage(button.messageId));
		currentRightY += buttonSpacing;
	}

	if (this->Data[eMENU_MAIN].FirstLoad == true) {
		this->Data[eMENU_MAIN].FirstLoad = false;
	}
}
// ----------------------------------------------------------------------------------------------

void Interface::EventMenuWindow(DWORD Event)
{
	this->EventMenuWindow_Close(Event);

	for (int i = 1; i <= 15; ++i)
	{
		int buttonId = eBUTTON_MENU_1 + (i - 1);
		if (!gInterface.Data[eMENU_MAIN].OnShow || !gInterface.IsWorkZone(buttonId))
			continue;

		DWORD CurrentTick = GetTickCount();
		DWORD Delay = (CurrentTick - gInterface.Data[buttonId].EventTick);

		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[buttonId].OnClick = true;
			pSetCursorFocus = true;
			return;
		}

		gInterface.Data[buttonId].OnClick = false;
		pSetCursorFocus = false;

		if (Delay < 500)
			return;

		gInterface.Data[buttonId].EventTick = CurrentTick;

		//Acciones por botón
		switch (buttonId)
		{
		case eBUTTON_MENU_1:
			if (gCustomEventTime.CheckTestWindow())
				gCustomEventTime.CloseTestWindow();
			else
			{
				gCustomEventTime.ClearCustomEventTime();
				PMSG_CUSTOM_EVENTTIME_SEND pMsg;
				pMsg.header.set(0xF3, 0xE8, sizeof(pMsg));
				DataSend((BYTE*)&pMsg, pMsg.header.size);
				gCustomEventTime.OpenTestWindow();
			}
			break;

		case eBUTTON_MENU_2:
			gInterface.Data[eVip_MAIN].OnShow = true;
			gBuyVip.OpenTestWindow();
			break;

		case eBUTTON_MENU_3:
			gCustomCommandInfo.OpenCommandWindow();
			break;
		case eBUTTON_MENU_4:
			if (GetForegroundWindow() == pGameWindow)
			{
#if FLAG
				ThueFlag.OpenFlag();
				gInterface.Data[eMAIN_ThueFlag].Open();
#endif
			}
			break;
		case eBUTTON_MENU_5:
			break;
		case eBUTTON_MENU_6:
			break;
		case eBUTTON_MENU_7:
			break;
		case eBUTTON_MENU_8:
			gCustomRanking.OpenWindow();
			break;
		case eBUTTON_MENU_9:
			gCustomJewelBank.OpenWindow();
			break;
		case eBUTTON_MENU_10:
			gInterface.Data[eMAIN_DailySystem].OnShow = true;
			DailyReward.OpenWindow(true);
			break;
		case eBUTTON_MENU_11:
#if(LuckyWheelV2)
			gInterface.OpenWindowVongQuay();
#endif
			break;

		case eBUTTON_MENU_12:
#if(CustomXShop)
			gNewCashShop.OpenCustomShop();
#endif
			break;

		case eBUTTON_MENU_13:
			if (gAntiLagSystem.CheckTestWindow())
			{
				gAntiLagSystem.Click = false;
				gAntiLagSystem.CloseTestWindow();
			}
			else
			{
				gAntiLagSystem.Click = true;
				gAntiLagSystem.OpenTestWindow();
			}
			break;
		case eBUTTON_MENU_14:
		case eBUTTON_MENU_15:
			if (GetForegroundWindow() == pGameWindow)
				this->SwitchMenuWindowState();
			break;
		}

		this->CLOSE_MENU();
		Data[eMENU_MAIN].CloseAnimated(15);
	}
}
//----------------------------------------------------------------//
void Interface::EventMenuWindow_Close(DWORD Event)
{
	if (!this->Data[eMENU_MAIN].OnShow)
	{
		return;
	}
	DWORD CurrentTick = GetTickCount();

	if (IsWorkZone(eMENU_CLOSE))
	{
		DWORD Delay = (CurrentTick - this->Data[eMENU_CLOSE].EventTick);
		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eMENU_CLOSE].OnClick = true;
			return;
		}
		this->Data[eMENU_CLOSE].OnClick = false;
		if (Delay < 500)
		{
			return;
		}
		this->Data[eMENU_CLOSE].EventTick = GetTickCount();
		Data[eMENU_MAIN].CloseAnimated(15);
	}
	return;
}

void Interface::DrawMenu()
{
	if (gProtect.m_MainInfo.CustomMenuSwitch != 1)
	{
		return;
	}

	if (this->CheckWindow(ObjWindow::MoveList) || this->CheckWindow(ObjWindow::CashShop) || this->CheckWindow(ObjWindow::SkillTree) || this->CheckWindow(ObjWindow::FullMap)
			|| this->CheckWindow(Store)
			|| this->CheckWindow(ExpandWarehouse))
	{
		return;
	}

	this->Data[eMenu].OnShow = true;

	if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
	{
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{

			//float y; // ST1C_4@1
			float x; // ST18_4@1
			int JCMacroHelper; // [sp+2Ch] [bp-104h]@1
			JCMacroHelper = *(DWORD*)(GetInstance() + 152);

			//y = (double)*(signed int*)(JCMacroHelper + 24);
			x = (double)*(signed int*)(JCMacroHelper + 20);

			//this->DrawGUI(eMenuBG, x + 209, 0);

			this->DrawGUI(eMenu, x + 209, 2);

			gInterface.Data[eMenu].OnShow = true;

			gInterface.DrawGUI(eMenu, x + 209, 2);

			if (gInterface.IsWorkZone(eMenu))
			{
				//pSetCursorFocus = true; // Bloqueo de Cursor Al Señalar :)
				gInterface.DrawToolTip(x + 209 - 5, 25, "Especial Menu");
				// ----

				if (gInterface.Data[eMenu].OnClick)
				{
					gInterface.DrawColoredGUI(eMenu, x + 209, 2, pMakeColor(40, 20, 3, 130));
					return;
				}
				// ----
				gInterface.DrawColoredGUI(eMenu, x + 209, 2, pMakeColor(255, 204, 20, 200));
			}
		}
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		if (gProtect.m_MainInfo.CustomMenuType == 1)
		{

			//float y; // ST1C_4@1
			float x; // ST18_4@1
			int JCMacroHelper; // [sp+2Ch] [bp-104h]@1
			JCMacroHelper = *(DWORD*)(GetInstance() + 152);

			//y = (double)*(signed int*)(JCMacroHelper + 24);
			x = (double)*(signed int*)(JCMacroHelper + 20);

			gInterface.DrawButtonIcon(eMenuS8, 120111, x + 149, 7.0, 19.0, 19.0, "Menu");
			gInterface.Data[eMenuS8].OnShow = true;

			gInterface.DrawGUI(eMenuS8, x + 149, 11);

			if (gInterface.IsWorkZone(eMenuS8))
			{
				//pSetCursorFocus = true; // Bloqueo de Cursor Al Señalar :)
				gInterface.DrawToolTip(x + 149 + 24, 47, "Especial");
				// ----

				if (gInterface.Data[eMenuS8].OnClick)
				{
					gInterface.DrawColoredGUI(eMenuS8, x + 149, 11, pMakeColor(40, 20, 3, 130));
					return;
				}
				// ----
				gInterface.DrawColoredGUI(eMenuS8, x + 149, 11, pMakeColor(255, 204, 20, 200));
			}
		}
	}
}

bool Interface::EventDrawMenu_Open(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenu].EventTick);
	// ----
	if (!this->Data[eMenu].OnShow || !IsWorkZone(eMenu))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		//pSetCursorFocus = true;
		this->Data[eMenu].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenu].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}

	// ----
	this->Data[eMenu].EventTick = GetTickCount();

	if (GetForegroundWindow() == pGameWindow)
	{
		this->SwitchMenuWindowState();
	}

	return true;

}

bool Interface::EventDrawMenuS8_Open(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eMenuS8].EventTick);
	// ----
	if (!this->Data[eMenuS8].OnShow || !IsWorkZone(eMenuS8))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		//pSetCursorFocus = true;
		this->Data[eMenuS8].OnClick = true;
		return true;
	}
	// ----
	this->Data[eMenuS8].OnClick = false;
	// ----
	if (Delay < 500)
	{
		return false;
	}

	// ----
	this->Data[eMenuS8].EventTick = GetTickCount();

	if (GetForegroundWindow() == pGameWindow)
	{
		this->SwitchMenuWindowState();
	}

	return true;

}

bool Interface::MiniMapCheck()
{
	if (this->CheckWindow(Inventory) ||
		this->CheckWindow(CashShop) ||
		this->CheckWindow(ChaosBox) ||
		this->CheckWindow(Character) ||
		this->CheckWindow(CommandWindow) ||
		this->CheckWindow(ExpandInventory) ||
		this->CheckWindow(ExpandWarehouse) ||
		this->CheckWindow(FullMap) ||
		this->CheckWindow(GensInfo) ||
		this->CheckWindow(Guild) ||
		this->CheckWindow(NPC_Dialog) ||
		this->CheckWindow(NPC_Julia) ||
		this->CheckWindow(NPC_Titus) ||
		this->CheckWindow(OtherStore) ||
		this->CheckWindow(Party) ||
		this->CheckWindow(PetInfo) ||
		this->CheckWindow(Shop) ||
		this->CheckWindow(SkillTree) ||
		this->CheckWindow(Store) ||
		this->CheckWindow(Trade) ||
		this->CheckWindow(FriendList) ||
		this->CheckWindow(FastMenu) ||
		this->CheckWindow(MuHelper) ||
		this->CheckWindow(Quest) ||
		this->CheckWindow(Lugard) ||
		this->CheckWindow(Jerint) ||
		this->CheckWindow(GoldenArcher1) ||
		this->CheckWindow(GoldenArcher2) ||
		this->CheckWindow(LuckyCoin1) ||
		this->CheckWindow(LuckyCoin2) ||
		this->CheckWindow(NPC_Duel) ||
		this->CheckWindow(NPC_Devin) ||
		this->CheckWindow(GuardNPC) ||
		this->CheckWindow(SeniorNPC) ||
		this->CheckWindow(GuardNPC2) ||
		this->CheckWindow(CastleGateSwitch) ||
		this->CheckWindow(CatapultNPC) ||
		this->CheckWindow(DuelScore) ||
		this->CheckWindow(CreateGuild) ||
		this->CheckWindow(Warehouse))
	{
		return true;
	}
	return false;
}

bool Interface::CombinedChecks()
{
	if ((this->CheckWindow(Inventory)
		&& this->CheckWindow(ExpandInventory)
		&& this->CheckWindow(Store)) ||
		(this->CheckWindow(Inventory)
			&& this->CheckWindow(Warehouse)
			&& this->CheckWindow(ExpandWarehouse)) ||
		(this->CheckWindow(Inventory)
			&& this->CheckWindow(Character)
			&& this->CheckWindow(Store)))
		return true;
	return false;
}

bool Interface::CheckMap()
{
	switch (gObjUser.m_MapNumber)
	{
	case eMapNumber::Lorencia:
		return false;
		break;
	case eMapNumber::Dungeon:
		return false;
		break;
	case eMapNumber::Devias:
		return false;
		break;
	case eMapNumber::Noria:
		return false;
		break;
	case eMapNumber::LostTower:
		return false;
		break;
	case eMapNumber::Atlans:
		return false;
		break;
	case eMapNumber::Tarkan:
		return false;
		break;
	case eMapNumber::Elbeland:
		return false;
		break;
	case eMapNumber::Icarus:
		return false;
		break;
	case eMapNumber::Trials:
		return false;
		break;
	case eMapNumber::Aida:
		return false;
		break;
	case eMapNumber::Crywolf:
		return false;
		break;
	case eMapNumber::Kanturu1:
		return false;
		break;
	case eMapNumber::Kanturu3:
		return false;
		break;
	case eMapNumber::Barracks:
		return false;
		break;
	case eMapNumber::Calmness:
		return false;
		break;
	case eMapNumber::Raklion:
		return false;
		break;
	case eMapNumber::Vulcanus:
		return false;
		break;
	case eMapNumber::Karutan1:
		return false;
		break;
	case eMapNumber::Karutan2:
		return false;
		break;
	case eMapNumber::Stadium:
		return false;
		break;
	case eMapNumber::Mundioca:
		return false;
		break;
	default:
		return true;
		break;
	}
}

void Interface::CloseCustomWindow()
{
	pSetCursorFocus = false;
}

void testfunc()
{
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
}

void Interface::DrawItem(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse)
{
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;
	sub_6358A0_Addr(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, Excl, Anc, OnMouse);
	testfunc();
	glColor3f(1, 1, 1);
	pSetBlend(false);
}

void Interface::DrawConfirmOpen()
{
	if (!this->CheckWindow(Shop) && this->Data[eCONFIRM_MAIN].OnShow == true)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_OK].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if ((GetTickCount() - this->Data[eCONFIRM_BTN_CANCEL].EventTick) < 100)
	{
		this->Data[eCONFIRM_MAIN].OnShow = false;
		pSetCursorFocus = false;
	}

	if (!this->Data[eCONFIRM_MAIN].OnShow)
	{
		return;
	}

	//this->Data[eCONFIRM_MAIN].EventTick = GetTickCount();

	float MainWidth = 230.0;
	float MainHeight = 130.0;
	float StartBody = 90.0;
	float StartY = 90.0;
	float StartX = 25;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	pSetCursorFocus = true;

	gInterface.DrawGUI(eCONFIRM_MAIN, StartX, StartY + (float)2.0);
	gInterface.DrawGUI(eCONFIRM_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(eCONFIRM_FRAME, StartX, StartY + (float)5.0, 5);
	gInterface.DrawGUI(eCONFIRM_FOOTER, StartX, StartY);

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 10, 210, 3, gCustomMessage.GetMessage(66));

	this->DrawFormat(eGold, (int)StartX + 10, (int)StartBody + 40, 210, 3, gCustomMessage.GetMessage(67));

	this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, 0);

	if (this->IsWorkZone(eCONFIRM_BTN_OK))
	{
		int ScaleY = 30;
		// ----
		if (this->Data[eCONFIRM_BTN_OK].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		this->DrawButton(eCONFIRM_BTN_OK, (int)StartX + 40, (int)StartBody + 70, 0, ScaleY);
	}

	this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, 0);

	if (this->IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		int ScaleY = 30;
		// ----
		if (this->Data[eCONFIRM_BTN_CANCEL].OnClick)
		{
			ScaleY = 60;
		}
		// ----
		this->DrawButton(eCONFIRM_BTN_CANCEL, (int)StartX + 140, (int)StartBody + 70, 0, ScaleY);
	}

}

bool Interface::EventConfirm_OK(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_OK].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_OK))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_OK].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_OK].EventTick = GetTickCount();

	PMSG_ITEM_BUY_RECV pMsg;

	pMsg.header.set(0xF3, 0xED, sizeof(pMsg));

	pMsg.slot = this->ConfirmSlot;

	DataSend((BYTE*)&pMsg, pMsg.header.size);

	this->Data[eCONFIRM_MAIN].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}

bool Interface::EventConfirm_CANCEL(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eCONFIRM_BTN_CANCEL].EventTick);
	// ----
	if (!this->Data[eCONFIRM_MAIN].OnShow || !IsWorkZone(eCONFIRM_BTN_CANCEL))
	{
		return false;
	}
	// ----
	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eCONFIRM_BTN_CANCEL].OnClick = true;
		return true;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].OnClick = false;;
	// ----
	if (Delay < 500)
	{
		return false;
	}
	// ----
	this->Data[eCONFIRM_BTN_CANCEL].EventTick = GetTickCount();

	this->Data[eCONFIRM_MAIN].OnShow = false;
	pSetCursorFocus = false;
	// ----
	return false;
}

void Interface::DrawItemIMG(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
	float x = PosX;
	float y = PosY;

	if (ItemID >= ITEM(0, 0) && ItemID < ITEM(1, 0))
	{
		x = PosX - 5;
		if (ItemID == ITEM(0, 16) || ItemID == ITEM(0, 19)) { y = PosY + 30; }
		else if ((ItemID >= ITEM(0, 32) && ItemID <= ITEM(0, 35)) || gCustomBattleGloves.CheckGloves(ItemID) == true) { y = PosY + 15; }
		else if (ItemID >= ITEM(0, 15) && ItemID < ITEM(0, 32)) { y = PosY + 25; }
		else if (ItemID > ITEM(0, 35)) { y = PosY + 20; }
		else if (ItemID == ITEM(0, 0)) { y = PosY + 30; }
		else { y = PosY + 20; }
	}
	else if (ItemID >= ITEM(3, 0) && ItemID < ITEM(4, 0))
	{
		y = PosY + 30;
	}
	else if (ItemID >= ITEM(7, 0) && ItemID < ITEM(8, 0)) { y = PosY + 25; }
	else if (ItemID >= ITEM(8, 0) && ItemID < ITEM(9, 0))
	{
		if ((ItemID >= ITEM(8, 2) && ItemID <= ITEM(8, 4))
			|| ItemID == ITEM(8, 7) || ItemID == ITEM(8, 8)
			|| ItemID == ITEM(8, 15))
		{
			y = PosY + 20;
		}
		else if (ItemID == ITEM(8, 34) || ItemID == ITEM(8, 35)) { y = PosY + 25; }
		else if (ItemID <= ITEM(8, 73)) { y = PosY + 25; }
		else if (ItemID > ITEM(8, 73)) { y = PosY + 35; }
	}
	else if (ItemID >= ITEM(9, 0) && ItemID < ITEM(12, 0)) { y = PosY + 25; }
	else if (ItemID >= 2048)
	{
		y = PosY + 25;

		if (ItemID == ITEM(12, 40)) { y = PosY + 10; }
	}
	else { y = PosY + 20; }

	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	sub_6363D0_Addr(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	sub_6358A0_Addr(1.6, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	pDrawItemModel(x, y, Width, Height, ItemID, Level, Excl, Anc, OnMouse);
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glColor4f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0);
	pSetBlend(false);
}

void Interface::DrawItemToolTipText(void* item, int x, int y)
{
	static DWORD mem = 0;
	_asm
	{
		PUSH 0
		PUSH 0
		PUSH 0
		PUSH item
		PUSH y
		PUSH x
		MOV mem, 0x00861110
		CALL mem
		MOV ECX, EAX
		MOV mem, 0x00861AA0
		CALL mem
		MOV ECX, EAX
		MOV mem, 0x007E3E30
		CALL mem
	}
}

void Interface::DrawButtonRender(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

#if(MAP_USAGE)
int GetTimeGMT()
{
	time_t rawTime;
	struct tm* timeInfo;

	time(&rawTime);
	timeInfo = gmtime(&rawTime);

	timeInfo->tm_hour += (gProtect.m_MainInfo.ServerTime);
	//timeInfo->tm_hour += +1;
	return mktime(timeInfo);


}
float fAlpha = 0.1f;
void BRenderTimeCountDown(float x, float y, float w, int MatchTime)
{
	char lpszStr[256];
	char lpszStrS[10];
	int iMinute = MatchTime / 60;
	DWORD ColorText = 0xE6FCF7FF;
	wsprintf(lpszStr, " %.2d :", iMinute);

	int iSecondTime = MatchTime - (iMinute * 60);
	if (iSecondTime >= 0)
	{
		wsprintf(lpszStrS, " %.2d", iSecondTime);
		strcat(lpszStr, lpszStrS);
	}

	if (iMinute < 5)
	{
		ColorText = 0xFF2121FF;
	}
	if (iMinute < 15)
	{
		wsprintf(lpszStrS, ": %.2d", ((int)WorldTime % 60));
		strcat(lpszStr, lpszStrS);
	}
	//HFONT FontTextTime = CreateFontA(14, 700, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	CustomFont.Draw((HFONT)pFontNormal, x, y, 0xE6FCF7FF, 0x0, w, 0, 3, lpszStr); //Buoc Vao
	//DeleteObject(FontTextTime);

}


void Interface::DrawTimeUseMap()
{
	if ((gInterface.CheckWindow(ObjWindow::CashShop) || gInterface.CheckWindow(ObjWindow::FullMap) || gInterface.CheckWindow(ObjWindow::ChatWindow) || gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::MoveList)))
	{
		return;
	}
	if (mMapUsageData.Map != pMapNumber)
	{
		return;
	}
	if ((mMapUsageData.Time - GetTimeGMT() < 1))
	{
		mMapUsageData.Time = 0;
		mMapUsageData.Map = 255;
		return;
	}
	float InfoW = 120;
	float InfoH = 40;
	float InfoX = 5;
	float InfoY = MAX_WIN_HEIGHT - (InfoH + 115);
	gElemental.gInfoBox(InfoX, InfoY, InfoW, InfoH, 0x00000096, 0, 0); //1vs3
	//HFONT FontTextTime = CreateFontA(16, 700, 0, 0, 700, 0, 0, 0, 0x1, 0, 0, 3, 0, "Tahoma");
	CustomFont.Draw((HFONT)pFontNormal, InfoX, InfoY + 5, 0xFFAA00FF, 0x0, InfoW + 10, 0, 3, "Proceso Regresivo"); //Buoc Vao
	CustomFont.Draw((HFONT)pFontNormal, InfoX, InfoY + 22, 0xFFAA00FF, 0x0, InfoW + 10, 0, 3, "Al Finalizar Te Saca Del Mapa"); //Buoc Vao
	//DeleteObject(FontTextTime);
	BRenderTimeCountDown(InfoX, (InfoY + InfoH) - 7, InfoW + 10, mMapUsageData.Time - GetTimeGMT());
}

#endif

void Interface::DrawItem3D(float PosX, float PosY, float Width, float Height, int ItemID, int Level, int ExtOption, int Ancient, bool PickUp, float Scale, bool Center)
{
	float x = PosX;
	float y = PosY;

	if (ItemID >= ITEM(0, 0) && ItemID < ITEM(1, 0))
	{
		x = PosX - 10;
		if (ItemID == ITEM(0, 16) || ItemID == ITEM(0, 19)) {
			y = PosY + 30;
			//g_Console.AddMessage(1, "DrawItem3D %d", ItemID);
		}
		else if ((ItemID >= ITEM(0, 32) && ItemID <= ITEM(0, 35)) /*|| gCustomBattleGloves.CheckGloves(ItemID) == true*/) { y = PosY + 15; }
		else if (ItemID >= ITEM(0, 15) && ItemID < ITEM(0, 32)) { y = PosY + 25; }
		else if (ItemID > ITEM(0, 35)) { y = PosY + 20; }
		else if (ItemID == ITEM(0, 0)) { y = PosY + 30; }
		else { y = PosY + 20; }
	}
	else if (ItemID >= ITEM(3, 0) && ItemID < ITEM(4, 0))
	{
		y = PosY + 30;
	}
	else if (ItemID >= ITEM(7, 0) && ItemID < ITEM(8, 0)) { y = PosY + 25; }
	else if (ItemID >= ITEM(8, 0) && ItemID < ITEM(9, 0))
	{
		if ((ItemID >= ITEM(8, 2) && ItemID <= ITEM(8, 4))
			|| ItemID == ITEM(8, 7) || ItemID == ITEM(8, 8)
			|| ItemID == ITEM(8, 15))
		{
			y = PosY + 20;
		}
		else if (ItemID == ITEM(8, 34) || ItemID == ITEM(8, 35)) { y = PosY + 25; }
		else if (ItemID <= ITEM(8, 73)) { y = PosY + 25; }
		else if (ItemID > ITEM(8, 73)) { y = PosY + 35; }
	}
	else if (ItemID >= ITEM(9, 0) && ItemID < ITEM(12, 0)) { y = PosY + 25; }
	else if (ItemID >= 2048)
	{
		y = PosY + 25;

		if (ItemID == ITEM(12, 40)) { y = PosY + 10; }
	}
	else { y = PosY + 20; }
	PosX = x;
	PosY = y - 25;
	pSetBlend(true);
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)0x00E61E58, *(GLsizei*)0x00E61E5C);
	float v2 = *(float*)0x00E61E58 / *(float*)0x00E61E5C;
	sub_6358A0_Addr(Scale, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();
	glClear(0x100);


	pDrawItemModel(PosX, PosY, Width, Height, ItemID, Level, ExtOption, Ancient, PickUp);

	sub_636720_Addr();
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glColor3f(1, 1, 1);
	pSetBlend(false);
	return;
}


bool Interface::RenderCheckBox(float PosX, float PosY, DWORD TextColor, bool Checkis, LPCSTR Text, ...)
{
	bool mreturn = false;
	char Buff[2048];
	int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	if (Checkis)
	{
		pDrawButton(31593, PosX, PosY, 15.0, 15.0, 0.0, 0.0);
	}
	else
	{
		pDrawButton(31593, PosX, PosY, 15.0, 15.0, 0.0, 15.0);
	}
	gElemental.DrawText((HFONT)pFontBold, PosX + 22, PosY + 3, TextColor, 0x0, 0, 0, 1, Text);

	if (pCheckMouseOver(PosX, PosY, 15, 15) == 1)
	{
		if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500)
		{
			gInterface.Data[eWindowClick].EventTick = GetTickCount();
			PlayBuffer(25, 0, 0);
			gElemental.LockMouse = GetTickCount() + 500;
			mreturn = true;
			//gInterface.DrawMessage(1, "CCC");
		}
	}
	return mreturn;
}

void Interface::DrawFrame(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp)
{
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.0);
}

void Interface::DrawFrameAlpha(DWORD ModelID, float X, float Y, float W, float H, float SourceX, float SourceY, float SourceW, float SourceH, float ScaleW, float ScaleH, bool ScaleUp)
{
	float v1, v2;

	if (W) {
		W /= ScaleW;
		v1 = ScaleW / (SourceW / W);
	}
	else {
		v1 = ScaleW;
	}

	if (H) {
		H /= ScaleH;
		v2 = ScaleH / (SourceH / H);
	}
	else {
		v2 = ScaleH;
	}
	RenderBitmap(ModelID, X, Y, W, H, SourceX / SourceW, SourceY / SourceH, v1, v2, ScaleUp, 1, 0.8);
}

void Interface::NewModelRender3D(float x, float y, float Width, float Height, int ItemID, int Level, int Excl, int Anc, bool OnMouse) // code hien thi item
{
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();

	glViewport2(0, 0, *(GLsizei*)MAIN_RESOLUTION_X, *(GLsizei*)MAIN_RESOLUTION_Y);
	float v2 = *(float*)MAIN_RESOLUTION_X / *(float*)MAIN_RESOLUTION_Y;

	gluPerspective2(1.0, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700u);
	glPushMatrix();
	glLoadIdentity();
	GetOpenGLMatrix(0x87933A0);
	EnableDepthTest();
	EnableDepthMask();

	RenderItem3D(x, y, Width, Height, ItemID, Level, Excl, Anc, OnMouse);

	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();

	glColor4f((GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0, (GLfloat)1.0);
	pSetBlend(false);
}

bool Interface::IsWorkZone5(float X, float Y, float MaxX, float MaxY)
{
	if ((gObjUser.m_CursorX < X || gObjUser.m_CursorX > MaxX)
		|| (gObjUser.m_CursorY < Y || gObjUser.m_CursorY > MaxY))
	{
		return false;
	}
	// ----
	return true;
}

int Interface::DrawToolTipEx(DWORD Color, int PosX, int PosY, int Width, int Height, int Align, LPCSTR Text, ...)
{
	char Buff[2048];
	char Buff2[2048];
	int BuffLen = sizeof(Buff);
	ZeroMemory(Buff, BuffLen);
	// ----
	va_list args;
	va_start(args, Text);
	int Len = vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);
	// ----

	int LineCount = 0;

	strcpy(Buff2, Buff);

	char* Line = strtok(Buff2, "\n");
	// ----
	while (Line != NULL)
	{
		LineCount++;
		Line = strtok(NULL, "\n");
	}

	pSetBlend(1);
	glColor4f(0.0, 0.0, 0.0, 1.0);
	pDrawBarForm(PosX, PosY, Width, LineCount * 10, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();

	glColor3f(1.0, 1.0, 1.0);

	this->DrawFormat(eWhite, PosX, PosY, Width, Align, Buff);

	pSetBlend(0);
	return 0;
}

void Interface::DrawText(DWORD Color, int PosX, int PosY, int Width, int Align, LPCSTR Text, ...) // OK
{
	char Buff[2048];
	const int BuffLen = sizeof(Buff) - 1;
	ZeroMemory(Buff, BuffLen);

	va_list args;
	va_start(args, Text);
	vsprintf_s(Buff, BuffLen, Text, args);
	va_end(args);

	char * Line = strtok(Buff, "\n");

	while (Line != nullptr)
	{
		DrawInterfaceText(Line, PosX, PosY, Width, 0, Color, 0, Align);
		PosY += 10;
		Line = strtok(NULL, "\n");
	}
}

void Interface::DrawColoredButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY, DWORD Color)
{
	if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	{
		this->Data[ObjectID].X = PosX;
		this->Data[ObjectID].Y = PosY;
		this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
		this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY, Color);
}

bool Interface::gDrawButtonGUI(int IDGUID, float PosX, float PosY, float SizeW, float SizeH, int TypeButton)
{
	bool mreturn = false;
	//=====================Button 1

	if (TypeButton == 3)
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;

			if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover)
			{
				gInterface.Data[eWindowClick].EventTick = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 2);
			}
			else {
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 1);
			}

		}
		else {
			pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
		}
	}
	else if (TypeButton == 2)
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;

			if ((GetKeyState(VK_LBUTTON) & 0x8000) && GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover)
			{
				gInterface.Data[eWindowClick].EventTick = GetTickCount();
				PlayBuffer(25, 0, 0);
				mreturn = true;
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, SizeH * 1);
			}
			else {
				pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
			}

		}
		else {
			pDrawButton(IDGUID, PosX, PosY, SizeW, SizeH, 0.0, 0.0);
		}
	}

	else
	{
		if (pCheckMouseOver(PosX, PosY, SizeW, SizeH) == 1)
		{
			gElemental.LockMouse = GetTickCount() + 500;
			if (GetTickCount() - gInterface.Data[eWindowClick].EventTick > 500 && !gElemental.LockButtonHover) //Click
			{
				if ((GetKeyState(VK_LBUTTON) & 0x8000))
				{
					gInterface.Data[eWindowClick].EventTick = GetTickCount();
					PlayBuffer(25, 0, 0);
					mreturn = true;
				}
			}
			pDrawColorButton(IDGUID, PosX, PosY, SizeW, SizeH, 0, 0, pMakeColor(255, 204, 20, 130));
		}
		else
		{
			pDrawGUI(IDGUID, PosX, PosY, SizeW, SizeH);
		}
	}

	return mreturn;
}

void Interface::DrawBarForm(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f((GLfloat)red, (GLfloat)green, (GLfloat)blue, (GLfloat)alpha);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

void Interface::DrawBarForm2(float PosX, float PosY, float Width, float Height, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	pSetBlend(true);
	glColor4f(red, green, blue, alpha);
	pDrawBarForm(PosX, PosY, Width, Height, 0.0f, 0);
	//DrawTest(PosX,PosY,Width,Height,0.0f, 0);
	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}

bool Interface::ControlTextBox(KBDLLHOOKSTRUCT Hook)
{
	if (gInterface.Data[eSTATSADD_MAIN_STR].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX01,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_AGI].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX02,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_VIT].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX03,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_ENE].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX04,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else if (gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		char Value[20];
		int IsBackspace = false;
		int IsDelete = false;
		int IsTab = false;

		int ObjectCount = 1;

		if ((gObjUser.lpPlayer->Class & 7) == 4)
		{
			ObjectCount = 1;
		}

		int SelectedIndex = 0;

		if (Hook.vkCode == VK_BACK)
		{
			IsBackspace = true;
		}
		else if (Hook.vkCode == VK_DELETE)
		{
			IsDelete = true;
		}
		else if (Hook.vkCode == VK_TAB)
		{
			IsTab = true;
		}
		else if ((Hook.vkCode >= 0x30 && Hook.vkCode <= 0x39) || (Hook.vkCode >= 0x60 && Hook.vkCode <= 0x69))
		{
			int Symbol = GetSymbolFromVK(Hook.vkCode);
			if (Symbol == 0)
			{
				return true;
			}
			char buff[10];
			sprintf(buff, "%c", Symbol);
			strcpy_s(Value, buff);
			////console.Log("", buff);
			//int Value = atoi(buff);
		}
		else
		{
			return true;
		}
		int ObjectIDs[1] =
		{
			eSTATSADD_STATBOX05,
		};

		for (int i = 0; i < ObjectCount; i++)
		{
			if (gInterface.Data[ObjectIDs[i]].Attribute == 1)
			{
				SelectedIndex = i;
				if (IsBackspace == true)
				{
					gInterface.Data[ObjectIDs[i]].StatValue[strlen(gInterface.Data[ObjectIDs[i]].StatValue) - 1] = '\0';

					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) == 0)
					{
						strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
					}
					break;
				}
				else if (IsDelete == true)
				{
					strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, "0");
				}
				else if (IsTab == true)
				{
					gInterface.Data[ObjectIDs[i]].Attribute = 0;

					if (i == ObjectCount - 1)
					{
						gInterface.Data[ObjectIDs[0]].Attribute = 1;
					}
					else
					{
						gInterface.Data[ObjectIDs[i + 1]].Attribute = 1;
					}
					break;
				}
				else
				{
					if (strlen(gInterface.Data[ObjectIDs[i]].StatValue) < 8)
					{
						if (!strcmp(gInterface.Data[ObjectIDs[i]].StatValue, "0"))
						{
							strcpy_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
						else
						{
							strcat_s(gInterface.Data[ObjectIDs[i]].StatValue, Value);
						}
					}
				}
			}
		}

		int StatPoints = 0;

		for (int i = 0; i < ObjectCount; i++)
		{
			if (i == SelectedIndex)
			{
				continue;
			}
			StatPoints += atoi(gInterface.Data[ObjectIDs[i]].StatValue);
		}

		if (StatPoints + atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > ViewPoint)
		{
			char buff[20];
			sprintf(buff, "%d", ViewPoint - StatPoints);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}

		if (atoi(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue) > gObjUser.GetMaxStatPoint(ViewAccountLevel))
		{
			char buff[20];
			sprintf(buff, "%d", gObjUser.GetMaxStatPoint(ViewAccountLevel));
			//strcat_s(this->Data[ObjectIDs[SelectedIndex]].StatValue, buff);
			strcpy_s(gInterface.Data[ObjectIDs[SelectedIndex]].StatValue, buff);
		}
	}
	else
	{
		return false;
	}

	return false;
}

void Interface::DrawColoredAnimatedGUI(short ObjectID, float X, float Y, DWORD Color)
{
	//if( this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1 )
	//{
	this->Data[ObjectID].X = X;
	this->Data[ObjectID].Y = Y;
	this->Data[ObjectID].MaxX = X + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = Y + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawColorButton(this->Data[ObjectID].ModelID, X, Y,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, 0, 0, Color);
}

void Interface::DrawAnimatedButton(short ObjectID, float PosX, float PosY, float ScaleX, float ScaleY)
{
	//if (this->Data[ObjectID].X == -1 || this->Data[ObjectID].Y == -1)
	//{
	this->Data[ObjectID].X = PosX;
	this->Data[ObjectID].Y = PosY;
	this->Data[ObjectID].MaxX = PosX + this->Data[ObjectID].Width;
	this->Data[ObjectID].MaxY = PosY + this->Data[ObjectID].Height;
	//}
	// ----
	pDrawButton(this->Data[ObjectID].ModelID, PosX, PosY,
		this->Data[ObjectID].Width, this->Data[ObjectID].Height, ScaleX, ScaleY);
}

void Interface::draw_chat_message(int mode, char* name, char* text)
{
	CharTest char_text;
	CharTest char_name;
	sub_409A50_addr(&char_text, (int)text);
	sub_409A50_addr(&char_name, (int)name);
	char* this_ = (char*)pChatBoxThis((DWORD*)pWindowThis());
	sub_7894E0_Addr(this_, (int)&char_name, (int)&char_text, mode, 0);
	sub_409AD0_Addr((void*)&char_name);
	sub_409AD0_Addr((void*)&char_text);
}

bool Interface::IsWorkZone7(int Index, int add_points)
{
	if (pCursorX < this->m_Data[Index].X - add_points || pCursorX > this->m_Data[Index].MaxX + add_points ||
		pCursorY < this->m_Data[Index].Y - add_points || pCursorY > this->m_Data[Index].MaxY + add_points)
	{
		return false;
	}
	return true;
}

void Interface::TextDraw(int PosX, int PosY, int box_width, int Arg5, int Color, int Arg7, int Align, HGDIOBJ Font, LPCTSTR Format, ...)
{
	char TextBuff[1024] = { 0 };
	va_list va;
	va_start(va, Format);
	vsprintf_s(TextBuff, Format, va);
	va_end(va);

	pSetFont(pTextThis(), (int)Font);
	int v13 = sub_41FFE0_Addr(pTextThis());
	int v15 = sub_420010_Addr(pTextThis());
	pSetTextColor2(pTextThis(), Color);
	pSetBgColor(pTextThis(), Arg7);
	pSetBkColor(pTextThis(), 255, 255, 255, 0);

	char* line = strtok(TextBuff, "\n");
	// ----

	int rect[4];
	bool on = glIsEnabled(GL_SCISSOR_TEST);
	glGetIntegerv(GL_SCISSOR_BOX, rect);

	while (line != nullptr)
	{
		int line_height = GetTextHeight(line, Font);
		int line_width = GetTextWidth(line, Font);

		if (box_width > 0)
		{
			int start_x_real = pGetRealX(PosX);
			int start_y_real = pGetRealY(MAX_WIN_HEIGHT - PosY - line_height);
			int width_real = pGetRealX(box_width);
			int height_real = pGetRealY(line_height);

			if (on)
			{
				if (start_y_real < rect[1])
					start_y_real = rect[1];

				if (start_y_real + height_real > rect[1] + rect[3])
					height_real = rect[1] + rect[3] - start_y_real;
			}

			glEnable(GL_SCISSOR_TEST);
			glScissor(start_x_real, start_y_real, width_real, height_real);
		}

		//if (Interface::IsWorkZone(PosX, PosY, PosX + box_width, PosY + line_height + 6))
		if (pCheckMouseOver(PosX, PosY, box_width, line_height + 2))
		{
			if (box_width > 0 && line_width > box_width)
			{
				pDrawText(pTextThis(), PosX - this->scrollable_counter, PosY, line, 0, Arg5, (int*)Align, 0);

				int x = line_width - box_width / 2;

				if (this->scrollable_counter >= x)
				{
					pDrawText(pTextThis(), PosX + box_width - (this->scrollable_counter - x), PosY, line, 0, Arg5, (int*)Align, 0);

					if (PosX + box_width - (this->scrollable_counter - x) == PosX)
						this->scrollable_counter = 0;
				}

				if (strcmp(this->scrollable_buffer, line) != 0)
				{
					strcpy_s(this->scrollable_buffer, line/*, strlen(line)*/);
					this->scrollable_counter = 0;
				}

				this->scrollable_counter++;
			}
			else
			{
				//this->scrollable_counter = 0;
				pDrawText(pTextThis(), PosX, PosY, line, box_width, Arg5, (int*)Align, 0);
			}

			PosY += 10;
			line = strtok(nullptr, "\n");
		}
		else
		{
			if (!strcmp(this->scrollable_buffer, line))
				this->scrollable_counter = 0;

			pDrawText(pTextThis(), PosX, PosY, line, box_width, Arg5, (int*)Align, 0);
			PosY += 10;
			line = strtok(nullptr, "\n");
		}

		if (box_width > 0)
			glDisable(GL_SCISSOR_TEST);
	}

	glScissor(rect[0], rect[1], rect[2], rect[3]);

	if (on)
		glEnable(GL_SCISSOR_TEST);

	pSetTextColor2(pTextThis(), v13);
	pSetBgColor(pTextThis(), v15);
}

void Interface::DrawButton7(int Index, float PosX, float PosY, float Width, float Height, MU_4float* Base, MU_4float* OnClick, MU_4float* Hover, LPCTSTR Text/*, ...*/)
{
	if (Index != -1)
	{
		m_Data[Index].Width = Width;
		m_Data[Index].Height = Height;
		m_Data[Index].X = PosX;
		m_Data[Index].Y = PosY;
		m_Data[Index].MaxX = PosX + Width;
		m_Data[Index].MaxY = PosY + Height;
		m_Data[Index].Type = objButton;

		/*if (pIsKeyRepeat(VK_LBUTTON))
		{
			DrawBarForm(PosX,PosY,Width,Height,OnClick->Red,OnClick->Green,OnClick->Blue,OnClick->Alpha);
		}
		else */
		if (this->IsWorkZone7(Index))
		{
			DrawBarForm2(PosX - 0.4, PosY - 0.4, Width + 0.8, Height + 0.8, 1.0, 1.0, 1.0, 0.8);

			if (IsRepeatKey(VK_LBUTTON))
				DrawBarForm2(PosX, PosY, Width, Height, OnClick->Red, OnClick->Green, OnClick->Blue, OnClick->Alpha);
			else
			{
				DrawBarForm2(PosX, PosY, Width, Height, Hover->Red, Hover->Green, Hover->Blue, Hover->Alpha);
			}
		}
		else
		{
			DrawBarForm2(PosX, PosY, Width, Height, Base->Red, Base->Green, Base->Blue, Base->Alpha);
		}
	}
	else
	{
		DrawBarForm2(PosX, PosY, Width, Height, Base->Red, Base->Green, Base->Blue, Base->Alpha);
	}


	if (Text != nullptr)
	{
		int text_width = GetTextWidth(const_cast<char*>(Text), pFontNormal);
		int text_height = GetTextHeight(const_cast<char*>(Text), pFontNormal);

		if (text_width > Width - 10)
			this->TextDraw(PosX + 5, PosY + (Height - text_height) / 2, Width - 10, 1, eGold, 0, eLeftToRightBoxSize, pFontNormal, Text);
		else
			this->TextDraw(PosX + Width / 2, PosY + (Height - text_height) / 2, 0, 1, eGold, 0, 8, pFontNormal, Text);
	}
}

GLvoid GetDrawCircle(int ID, float X, float Y, float W, float CurrenX, float CurrenY, float SetScale, int ScaleSize, int ScalePosicion, float Alpha)
{
	float v14; // ST1C_4@1
	float v15; // ST18_4@1
	GLuint vertexcount; // ST1C_4@5
	float v33; // ST1C_4@5
	GLfloat angle; // ST1C_4@5
	GLfloat texturecoord[2]; // [sp+2Ch] [bp-40h]@5
	GLfloat VertexCoord[4]; // [sp+4Ch] [bp-20h]@5

	SetScale = SetScale / 2;
	//--
	W = W / 2;
	X = X + W;
	Y = Y + W;

	if (ScalePosicion)
	{
		X = ((double(__cdecl*)(float a1)) 0x00636420)(X);
		Y = ((double(__cdecl*)(float a1)) 0x00636450)(Y);
	}

	if (ScaleSize)
	{
		W = ((double(__cdecl*)(float a1)) 0x00636420)(W);
	}

	v33 = (double)pWinHeight - Y;

	vertexcount = 30;

	((bool(__cdecl*)(int a1)) 0x00635CF0)(ID);

	glBegin(GL_TRIANGLE_FAN);

	angle = 2.0 * 3.1415926 / vertexcount;
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, Alpha);
	texturecoord[0] = CurrenX;
	texturecoord[1] = CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = X;
	VertexCoord[1] = v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);

	for (int i = 0; i < vertexcount; i++)
	{
		texturecoord[0] = (std::cos(angle * i) * SetScale) + CurrenX;
		texturecoord[1] = (std::sin(angle * i) * SetScale) + CurrenY;
		glTexCoord2fv(texturecoord);
		VertexCoord[0] = (std::cos(angle * i) * W) + X;
		VertexCoord[1] = (std::sin(angle * i) * -W) + v33;
		VertexCoord[2] = 0.0;
		VertexCoord[3] = 1.0;
		glVertex4fv(VertexCoord);
	}
	//--
	texturecoord[0] = (1.0 * SetScale) + CurrenX;
	texturecoord[1] = (0.0 * SetScale) + CurrenY;
	glTexCoord2fv(texturecoord);
	//--
	VertexCoord[0] = (1.0 * W) + X;
	VertexCoord[1] = (0.0 * -W) + v33;
	VertexCoord[2] = 0.0;
	VertexCoord[3] = 1.0;
	glVertex4fv(VertexCoord);
	//--
	if (Alpha > 0.0)
		glColor4f(1.0, 1.0, 1.0, 1.0);
	//--
	glEnd();
}

void Interface::DrawButtonIcon(int Enum, int ImgID, float X, float Y, float W, float H, LPCSTR Text)
{
	gInterface.DrawButtonRender(Enum, X + 1.5f, Y + 0.5f, 0, 0.0f);
	if (gInterface.IsWorkZone(Enum))
	{
		gInterface.DrawToolTip(X, Y + 40, Text);
		if (gInterface.Data[Enum].OnClick) {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.451f, 0.878, 0.225, 1, 1, 0.0);
		}
		else {
			RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.2255f, 0.878, 0.225, 1, 1, 0.0);
		}
	}
	else {
		RenderBitmap(ImgID, X, Y, W, H, 0.0, 0.0, 0.878, 0.225, 1, 1, 0.0);
	}
}

//-> Clear Inventory
void Interface::DrawMenuTrash()
{
	if (this->CheckWindow(ObjWindow::Warehouse))
	{
		return;
	}

	if (this->CheckWindow(ObjWindow::Inventory) && this->CheckWindow(ObjWindow::Character))
	{
		this->Data[eTrash_Expanded].OnShow = true;

		float MainWidth = 230.0;

		float MainHeight = 130.0;

		float PosX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);

		this->DrawGUI(eTrash_Expanded, PosX + 212, 365);

		if (IsWorkZone(eTrash_Expanded))
		{
			//this->DrawToolTip(PosX + 164, 350, "Limpar Inventário");
		}
	}

	if (this->CheckWindow(ObjWindow::Inventory))
	{
		if (this->CheckWindow(ObjWindow::Character))
		{
			return;
		}

		else
		{

			int JCResto;
			if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
			{
				JCResto = pWinWidth / pWinHeightReal - 640;
			}
			else
			{
				JCResto = 0;
			}

			float PosX = JCResto + 125;
			float PosY = +40;

			this->Data[eTrash].OnShow = true;

			float MainWidth = 230.0;

			float MainHeight = 130.0;

			//float PosX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
			if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
			{
				this->DrawGUI(eTrash, PosX + 486, PosY + 353); //aca se ajusta el boton

				if (pCheckMouseOver(PosX + 486, PosY + 353, 25, 25))
				{
					if (*(BYTE*)0x8793386)
					{
						pDrawButton(99522, PosX + 486, PosY + 353, 25, 25, 0, 50);
					}
					else
					{
						pDrawButton(99522, PosX + 486, PosY + 353, 25, 25, 0, 0);
					}
				}
				else
				{
					pDrawButton(99522, PosX + 486, PosY + 353, 25, 25, 0, 25);
				}

				if (IsWorkZone(eTrash))
				{
					//gInterface.DrawToolTip(PosX + 476, PosY + 343, "Clearinv");
				}
			}

		}
	}
}

bool Interface::EventDrawMenuTrash_Open(DWORD Event)
{
	if (this->CheckWindow(ObjWindow::Warehouse))
	{
		return false;
	}

	if (this->CheckWindow(ObjWindow::Inventory) && this->CheckWindow(ObjWindow::Character))
	{
		DWORD CurrentTick = GetTickCount();
		DWORD Delay = (CurrentTick - this->Data[eTrash_Expanded].EventTick);

		if (!this->CheckWindow(ObjWindow::Inventory) && this->CheckWindow(ObjWindow::Character) || !IsWorkZone(eTrash_Expanded))
		{
			return false;
		}

		if (Event == WM_LBUTTONDOWN)
		{
			this->Data[eTrash_Expanded].OnClick = true;
			pSetCursorFocus = true;
			return true;
		}

		this->Data[eTrash_Expanded].OnClick = false;
		pSetCursorFocus = false;

		if (Delay < 500)
		{
			return false;
		}

		this->Data[eTrash_Expanded].EventTick = GetTickCount();

		gInterface.OpenTrashWindow();
	}

	if (this->CheckWindow(ObjWindow::Inventory))
	{
		if (this->CheckWindow(ObjWindow::Character))
		{
			return false;
		}

		else
		{
			DWORD CurrentTick = GetTickCount();
			DWORD Delay = (CurrentTick - this->Data[eTrash].EventTick);

			if (!this->CheckWindow(ObjWindow::Inventory) || !IsWorkZone(eTrash))
			{
				return false;
			}

			if (Event == WM_LBUTTONDOWN)
			{
				this->Data[eTrash].OnClick = true;
				pSetCursorFocus = true;
				return true;
			}

			this->Data[eTrash].OnClick = false;
			pSetCursorFocus = false;

			if (Delay < 500)
			{
				return false;
			}

			this->Data[eTrash].EventTick = GetTickCount();

			gInterface.OpenTrashWindow();
		}
	}

	return true;
}

void Interface::DrawMenuTrash_Warning()
{
	if (this->Data[eTrash_MAIN].OnShow)
	{
		pSetCursorFocus = true;
	}

	if (!this->Data[eTrash_MAIN].OnShow)
	{
		return;
	}

	float MainWidth = 230.0;
	float MainHeight = 313.0;
	float StartY = 80.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (29.0 / 2);

	this->DrawGUI(eTrash_MAIN, StartX, StartY + 2);
	this->DrawGUI(eTrash_MAIN, StartX, StartY + 17);
	this->DrawGUI(eTrash_TITLE, StartX, StartY);
	this->DrawGUI(eTrash_FRAME, StartX, StartY + 67);
	this->DrawGUI(eTrash_FRAME, StartX, StartY + 80);
	this->DrawGUI(eTrash_FOOTER, StartX, StartY + 95);

	this->DrawFormat(eExcellent, StartX + 10, 90, 210, 3, "Limpiar tu Inventario");

	this->DrawFormat(eGold, StartX + 10, 115, 210, 3, "Guarda tus items de valor en el Bault");

	this->DrawFormat(eGold, StartX + 10, 130, 210, 3, "Tus items de tu Inventario Seran Borrados");
	this->DrawFormat(eGold, StartX + 10, 141, 210, 3, "Excepto los que estan Equipado.");

	this->DrawFormat(eExcellent, StartX + 10, 156, 210, 3, "Estas seguro de limpiar el Inventario?");

	this->DrawGUI(eTrash_YES, StartX + 30, StartY + 95);

	this->DrawGUI(eTrash_NO, StartX + 140, StartY + 95);
}

bool Interface::DrawMenuTrash_Warning_Main(DWORD Event)
{
	this->DrawMenuTrash_Warning_Yes(Event);
	this->DrawMenuTrash_Warning_No(Event);
	return true;
}

bool Interface::DrawMenuTrash_Warning_Yes(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eTrash_YES].EventTick);

	if (!this->Data[eTrash_MAIN].OnShow || !IsWorkZone(eTrash_YES))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		this->Data[eTrash_YES].OnClick = true;
		pSetCursorFocus = true;
		return true;
	}

	this->Data[eTrash_YES].OnClick = false;
	pSetCursorFocus = false;

	if (Delay < 500)
	{
		return false;
	}

	pChatSend("/clearinv"); //Here you change command syntax

	this->CloseTrashWindow();

	return false;
}

bool Interface::DrawMenuTrash_Warning_No(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - this->Data[eTrash_NO].EventTick);

	if (!this->Data[eTrash_MAIN].OnShow || !IsWorkZone(eTrash_NO))
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		pSetCursorFocus = true;
		this->Data[eTrash_NO].OnClick = true;
		return true;
	}

	this->Data[eTrash_NO].OnClick = false;

	pSetCursorFocus = false;

	if (Delay < 500)
	{
		return false;
	}

	this->Data[eTrash_NO].EventTick = GetTickCount();

	this->CloseTrashWindow();

	return false;
}

#if(LuckyWheelV2)
#include <cmath>
#include "CBNewUiEx.h"
CNewUIScrollBar* ListVongQuay = nullptr;
int MaxListVQInPage = 5;
int MaxListItemVQInPage = 5;
int SelectTypeVQ = 1;
int Chay = -1;
float CountVong = 0.5;
int solan = 1;

bool Interface::EventVongQuayWindows_Close(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	DWORD Delay = (CurrentTick - gInterface.Data[eWindowVongQuay_CLOSE].EventTick);
	if (!gInterface.Data[eWindowVongQuay].OnShow || !gInterface.IsWorkZone(eWindowVongQuay_CLOSE))
	{
		return false;
	}
	if (Event == WM_LBUTTONDOWN)
	{
		gInterface.Data[eWindowVongQuay_CLOSE].OnClick = true;
		return true;
	}
	gInterface.Data[eWindowVongQuay_CLOSE].OnClick = false;
	if (Delay < 500)
	{
		return false;
	}
	gInterface.Data[eWindowVongQuay_CLOSE].EventTick = GetTickCount();
	this->CloseTestWindow();
	return false;
}

void Interface::OpenWindowVongQuay()
{

	if ((GetTickCount() - gInterface.Data[eWindowVongQuay].EventTick) < 1500)
	{
		//gInterface.Data[eRankPANEL_MAIN].OnShow = false;
		return;
	}

	gInterface.Data[eWindowVongQuay].EventTick = GetTickCount();

	if (gInterface.Data[eWindowVongQuay].OnShow == true)
	{
		gInterface.Data[eWindowVongQuay].OnShow = false;

		return;
	}

	gInterface.CloseCustomWindow();
	XULY_CGPACKET pMsg;
	pMsg.header.set(0xD3, 0x8C, sizeof(pMsg));
	pMsg.ThaoTac = 1;
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
	pMsg.header.set(0xD3, 0x8B, sizeof(pMsg));
	pMsg.ThaoTac = 1; //
	DataSend((LPBYTE)&pMsg, pMsg.header.size);
	gInterface.Data[eWindowVongQuay].OnShow = true;
}

void Interface::DrawWindowVQ()
{
	if (!gInterface.Data[eWindowVongQuay].OnShow)
	{
		return;
	}

	if (gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::FriendList)
		|| gInterface.CheckWindow(ObjWindow::MoveList)
		|| gInterface.CheckWindow(ObjWindow::Party)
		|| gInterface.CheckWindow(ObjWindow::Quest)
		|| gInterface.CheckWindow(ObjWindow::NPC_Devin)
		|| gInterface.CheckWindow(ObjWindow::Guild)
		|| gInterface.CheckWindow(ObjWindow::Trade)
		|| gInterface.CheckWindow(ObjWindow::Warehouse)
		|| gInterface.CheckWindow(ObjWindow::ChaosBox)
		|| gInterface.CheckWindow(ObjWindow::CommandWindow)
		|| gInterface.CheckWindow(ObjWindow::PetInfo)
		|| gInterface.CheckWindow(ObjWindow::Shop)
		//|| gInterface.CheckWindow(ObjWindow::Inventory)
		|| gInterface.CheckWindow(ObjWindow::Store)
		|| gInterface.CheckWindow(ObjWindow::OtherStore)
		|| gInterface.CheckWindow(ObjWindow::Character)
		|| gInterface.CheckWindow(ObjWindow::DevilSquare)
		|| gInterface.CheckWindow(ObjWindow::BloodCastle)
		|| gInterface.CheckWindow(ObjWindow::CreateGuild)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC)
		|| gInterface.CheckWindow(ObjWindow::SeniorNPC)
		|| gInterface.CheckWindow(ObjWindow::GuardNPC2)
		|| gInterface.CheckWindow(ObjWindow::CastleGateSwitch)
		|| gInterface.CheckWindow(ObjWindow::CatapultNPC)
		|| gInterface.CheckWindow(ObjWindow::CrywolfGate)
		|| gInterface.CheckWindow(ObjWindow::IllusionTemple)
		|| gInterface.CheckWindow(ObjWindow::HeroList)
		|| gInterface.CheckWindow(ObjWindow::ChatWindow)
		|| gInterface.CheckWindow(ObjWindow::FastMenu)
		|| gInterface.CheckWindow(ObjWindow::Options)
		|| gInterface.CheckWindow(ObjWindow::Help)
		|| gInterface.CheckWindow(ObjWindow::FastDial)
		|| gInterface.CheckWindow(ObjWindow::SkillTree)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher1)
		|| gInterface.CheckWindow(ObjWindow::GoldenArcher2)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin1)
		|| gInterface.CheckWindow(ObjWindow::LuckyCoin2)
		|| gInterface.CheckWindow(ObjWindow::NPC_Duel)
		|| gInterface.CheckWindow(ObjWindow::NPC_Titus)
		|| gInterface.CheckWindow(ObjWindow::CashShop)
		|| gInterface.CheckWindow(ObjWindow::Lugard)
		|| gInterface.CheckWindow(ObjWindow::QuestList1)
		|| gInterface.CheckWindow(ObjWindow::QuestList2)
		|| gInterface.CheckWindow(ObjWindow::Jerint)
		|| gInterface.CheckWindow(ObjWindow::FullMap)
		|| gInterface.CheckWindow(ObjWindow::NPC_Dialog)
		|| gInterface.CheckWindow(ObjWindow::GensInfo)
		|| gInterface.CheckWindow(ObjWindow::NPC_Julia)
		|| gInterface.CheckWindow(ObjWindow::NPC_ChaosMix)
		|| gInterface.CheckWindow(ObjWindow::ExpandInventory)
		|| gInterface.CheckWindow(ObjWindow::ExpandWarehouse)
		|| gInterface.CheckWindow(ObjWindow::MuHelper))
	{

		this->CloseWindow(true);
	}
	if (!gInterface.Data[eWindowVongQuay].OnShow)
	{
		return;
	}

	if (gInterface.CheckWindow(ObjWindow::Warehouse))
	{
		return;
	}


	float WindowW = 420;
	float WindowH = 300;
	float MainWidth = 230.0;
	float MainHeight = 290.0;
	float StartBody = 80.0;
	float StartY = 60;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2) - 90;
	float MainCenter = StartX + (MainWidth / 3);
	float PosX = 50;
	float InfoMocNapX = (StartX + 10) + 3;
	float InfoMocNapY = (StartY + 15);

	gInterface.CheckWindowSProTecno(5);

	if (gInterface.IsWorkZone(eWindowVongQuay))
	{
		pSetCursorFocus = true;
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		RenderBitmap(0xF1007, StartX + 7, StartY + - 21, 425, 325, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
		gInterface.DrawFormat(eGold, StartX + 115, StartY + 3, 210, 3, gCustomMessage.GetMessage(107));
		gInterface.DrawGUI(eWindowVongQuay_CLOSE, StartX + 405, StartY - 1);
		(nInterface.Drawbutton(nInterface.CloseWindowsUP, StartX + 405, StartY + 1, "") || GetKeyState(VK_ESCAPE) & 0x4000);
		if (gInterface.IsWorkZone(eWindowVongQuay_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eWindowVongQuay_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eWindowVongQuay_CLOSE, gInterface.Data[eWindowVongQuay_CLOSE].X, StartY, Color);
		}
	}
	else
	{
		RenderBitmap(61322, StartX + 13, StartY - 15, 410, 375.f, 0, 0, 0.97, 1.0, 1, 1, 0.0);
		RenderBitmap(61323, StartX + 13, StartY - 15, 410, 41.f, 0, 0, 0.97, 0.57, 1, 1, 0.0);
		gInterface.DrawGUI(eWindowVongQuay_CLOSE, StartX + 389, StartY - 14);
		gInterface.DrawFormat(eGold, StartX + 113, StartY + 3, 210, 3, gCustomMessage.GetMessage(107));
		if (gInterface.IsWorkZone(eWindowVongQuay_CLOSE))
		{
			DWORD Color = eGray100;
			// ----
			if (gInterface.Data[eWindowVongQuay_CLOSE].OnClick)
			{
				Color = eGray150;
			}
			// ----
			gInterface.DrawColoredGUI(eWindowVongQuay_CLOSE, gInterface.Data[eWindowVongQuay_CLOSE].X, gInterface.Data[eWindowVongQuay_CLOSE].Y, Color);
			//gInterface.DrawToolTip(gInterface.Data[eWindowVongQuay_CLOSE].X + 5, gInterface.Data[eWindowVongQuay_CLOSE].Y + 25, "Close");
		}
	}

	pSetCursorFocus = true;

	pSetBlend(true);
	glColor3f(1.0, 1.0, 1.0);

	//===Info Yeu Cau Moc Nap
	float TyleInfoYeuCau = 7.5f;
	float WInfo = (WindowW - 20) / 10;
	float WProcess = (WInfo * (TyleInfoYeuCau - 2.7));
	float WButton = 88;
	float HInfo = WindowH - 160;
	gElemental.gInfoBox((StartX + WindowW) - 110, InfoMocNapY + 15, 85, 125, 0x00000096, 0, 0);
	gElemental.gInfoBox((StartX + WindowW) - 110, InfoMocNapY + 160, 85, 105, 0x00000096, 0, 0);

	int DataListVQ = mDataVongQuayClient.DanhSachVongQuay.size();
	if (!ListVongQuay)
	{
		ListVongQuay = new CNewUIScrollBar();
		ListVongQuay->Create((StartX + WindowW) - 15, InfoMocNapY + 10, HInfo);
		if (ListVongQuay)
		{
			ListVongQuay->SetMaxPos((DataListVQ <= MaxListVQInPage) ? 0 : (DataListVQ / MaxListVQInPage));
			ListVongQuay->SetPos((StartX + WindowW) - 15, InfoMocNapY + 10);
		}
	}
	if (ListVongQuay)
	{
		if (gInterface.Data[eWindowVongQuay].OnClick)
		{
			ListVongQuay->SetPos((StartX + WindowW) - 15, InfoMocNapY + 10);
			ListVongQuay->SetCurPos(0);
		}
		ListVongQuay->MouseWheelWindow = pCheckMouseOver(InfoMocNapX, InfoMocNapY, WindowW, WindowH);
		ListVongQuay->Render();
		ListVongQuay->UpdateMouseEvent();
		ListVongQuay->Update();
	}

	float KhoangCachYMocNap = 24;
	int MixItemListPage = ListVongQuay->GetCurPos();
	int MaxList = 0;
	for (int n = (MixItemListPage * MaxListVQInPage); n < DataListVQ; n++)
	{
		if (gElemental.gDrawButton((StartX + WindowW) - 108, InfoMocNapY + 15, 110, 11, mDataVongQuayClient.DanhSachVongQuay[n].Name, WButton) && (GetTickCount() - gInterface.Data[eWindowVongQuay].EventTick) > 300 && gInterface.StartRollSau < 1) //"Xem"
		{

			SelectTypeVQ = mDataVongQuayClient.DanhSachVongQuay[n].IndexVongQuay;
			Chay = -1;
			gInterface.Data[eWindowVongQuay].OnShow = true;
			gInterface.Data[eWindowVongQuay].EventTick = GetTickCount();
			XULY_CGPACKET pMsg;
			pMsg.header.set(0xD3, 0x8B, sizeof(pMsg));
			pMsg.ThaoTac = SelectTypeVQ; //
			DataSend((LPBYTE)&pMsg, pMsg.header.size);
			gInterface.IndexItemSau = -1;
		}

		InfoMocNapY = InfoMocNapY + (KhoangCachYMocNap);
		MaxList++;
		if (MaxList >= MaxListItemVQInPage) break;
	}
	if ((GetTickCount() - gInterface.Data[eTIME].EventTick) > 6000)
	{

		if (gElemental.gDrawButton(StartX + 115, StartY + 200, 100, 11, "Girar", 60) && (GetTickCount() - gInterface.Data[eTIME].EventTick) > 6000)
		{
			XULY_CGPACKET_SOLAN pMsg;
			pMsg.header.set(0xD3, 0x8A, sizeof(pMsg));
			pMsg.ThaoTac = SelectTypeVQ; //
			pMsg.SoLan = 1;
			DataSend((LPBYTE)&pMsg, pMsg.header.size);
			gInterface.Data[eTIME].EventTick = GetTickCount();
		}
	}
	float PosYCoinNhan = StartY + 185;
	CustomFont.Draw(CustomFont.FontBold, (StartX + WindowW) - 105, PosYCoinNhan - 5, 0xFFDE26FF, 0x3a4b3978, 90, 0, 3, "Requisitos");
	CustomFont.Draw(CustomFont.FontNormal, (StartX + WindowW) - 105, PosYCoinNhan + (10 * 1), 0xFF8214FF, 0x0, WindowW, 0, 1, "- WCoin : %s", BNumberFormat(mDataListItemVongQuayClient.WCYC));			//Text3 = "+ WCoin : %s
	CustomFont.Draw(CustomFont.FontNormal, (StartX + WindowW) - 105, PosYCoinNhan + (10 * 2), 0xFF8214FF, 0x0, WindowW, 0, 1, "- WCoinP :%s", BNumberFormat(mDataListItemVongQuayClient.WPYC));		  //Text4 = "+ WCoinP : %
	CustomFont.Draw(CustomFont.FontNormal, (StartX + WindowW) - 105, PosYCoinNhan + (10 * 3), 0xFF8214FF, 0x0, WindowW, 0, 1, "- GobinP :%s", BNumberFormat(mDataListItemVongQuayClient.GPYC));		  //Text5 = "+ GobinP : %
	if (mDataListItemVongQuayClient.CountItem > 0)
	{
		CustomFont.Draw(CustomFont.FontNormal, (StartX + WindowW) - 105, PosYCoinNhan + (10 * 4), 0xFF8214FF, 0x0, WindowW, 0, 1, "+ Rud : %s", BNumberFormat(mDataListItemVongQuayClient.CountItem));		  //Text6 = " + Ruud : % s"
		CustomFont.Draw(CustomFont.FontNormal, (StartX + WindowW) - 105, PosYCoinNhan + (10 * 5) + 5, 0x26FFD7A4, 0x0, WindowW, 0, 1, "%s", BGetItemName(mDataListItemVongQuayClient.IndexYC, 0));//
	}
	int DataListItem = mDataListItemVongQuayClient.ListItemVongQuay.size();
	float Radius = 100.0f; // Set the radius of the circular layout
	float AngleStep = 2 * 3.14159265358979323846 / 12.0f; // Divide the circle into 12 equal angles
	float WBox = 30;
	int BBShowInfoItem = -1;
	DWORD boxColor = 0x00000096;
	unsigned int timeInterval2 = 10; // 5 seconds
	unsigned int currentTime2 = GetTickCount();
	unsigned int colorIndex2 = (currentTime2 / timeInterval2) % 2;
	if (gInterface.StartRollSau >= 1)
	{
		if (Chay >= 12)
		{
			Chay = 0;
			CountVong += 0.1;

		}

		if (colorIndex2 == 0 && CountVong <= 2.3)
		{
			Chay += CountVong;
		}
		if (CountVong >= 2.3)
		{
			Chay += CountVong;
		}

	}
	else
	{
		CountVong = 1;
	}
	for (int n = 0; n < DataListItem; n++)
	{
		ItemBmdStruct* is = pGetItemBmdStruct(mDataListItemVongQuayClient.ListItemVongQuay[n].Index);
		int size = max(is->ItemWidth, is->ItemHeight);

		float itemScale = 1.0;
		float addY = 0;
		switch (size)
		{
		case 4:
			addY = -5;
			break;
		case 3:
			addY = -3;
			break;
		case 2:
			addY = -1;
			break;
		}

		// Calculate polar coordinates for circular layout
		float angle = n * AngleStep;
		float PosXBoxItem = StartX + 125 + Radius * cos(angle);
		float PosYBoxItem = StartY + 140 + Radius * sin(angle);

		if (n == Chay)  // Replace yourNewVariable with the variable you want to compare with
		{
			boxColor = 0xD4966396;
		}
		else
		{
			boxColor = 0x00000096;
		}
		if (solan != 1)
		{
			int roll = rand() % 2;
			switch (roll)
			{
			case 0:
				gElemental.gInfoBox(PosXBoxItem, PosYBoxItem, WBox, WBox, 0x00000096, 0, 0);
				break;
			case 1:
				gElemental.gInfoBox(PosXBoxItem, PosYBoxItem, WBox, WBox, 0xD4966396, 0, 0);
				break;
			case 2:
				gElemental.gInfoBox(PosXBoxItem, PosYBoxItem, WBox, WBox, 0x26E0A596, 0, 0);
				break;
			}
		}
		gElemental.gInfoBox(PosXBoxItem, PosYBoxItem, WBox, WBox, boxColor, 0, 0);
		gInterface.DrawItem3D(PosXBoxItem + 5, PosYBoxItem + addY + 5, WBox, WBox, mDataListItemVongQuayClient.ListItemVongQuay[n].Index, mDataListItemVongQuayClient.ListItemVongQuay[n].Item.Level, mDataListItemVongQuayClient.ListItemVongQuay[n].Item.ExcellentOption, mDataListItemVongQuayClient.ListItemVongQuay[n].Item.AncientOption, 0, 1.0 / mDataListItemVongQuayClient.ListItemVongQuay[n].SizeBMD);
		if (gInterface.IndexItemSau != -1)
		{
			if (solan == 1)
			{
				Chay = gInterface.IndexItemSau;
			}
			else
			{
				Chay = -1;
			}
			gElemental.gInfoBox(InfoMocNapX + 112, StartY + 140, WBox, WBox, 0xD4966396, 0, 0);
			gInterface.DrawItem3D(InfoMocNapX + 117, StartY + 145, WBox, WBox, mDataListItemVongQuayClient.ListItemVongQuay[gInterface.IndexItemSau].Index, mDataListItemVongQuayClient.ListItemVongQuay[gInterface.IndexItemSau].Item.Level, mDataListItemVongQuayClient.ListItemVongQuay[gInterface.IndexItemSau].Item.ExcellentOption, mDataListItemVongQuayClient.ListItemVongQuay[gInterface.IndexItemSau].Item.AncientOption, 0, 1.0 / mDataListItemVongQuayClient.ListItemVongQuay[gInterface.IndexItemSau].SizeBMD);
			if (pCheckMouseOver(InfoMocNapX + 112, StartY + 140, WBox, WBox))
			{
				BBShowInfoItem = gInterface.IndexItemSau;
			}
		}
		if (pCheckMouseOver(PosXBoxItem, PosYBoxItem, WBox, WBox))
		{
			BBShowInfoItem = n;
		}
	}
	//===Coin
	if (BBShowInfoItem != -1)
	{
		gInterface.DrawItemToolTipText((void*)&mDataListItemVongQuayClient.ListItemVongQuay[BBShowInfoItem].Item, *(int*)0x879340C, *(int*)0x8793410 + 25);
		glColor3f(1, 1, 1);
		pSetBlend(false);
	}

	pGLSwitchBlend();
	pGLSwitch();
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
}
#endif

double Interface::CRenderNumberExBank(float a1, float a2, int a3, float a4, DWORD ModelID)
{
	double result; // st7@2
	float v5; // ST44_4@5
	float v6; // ST38_4@5
	signed int i; // [sp+38h] [bp-30h]@3
	float v8; // [sp+3Ch] [bp-2Ch]@3
	signed int v9; // [sp+44h] [bp-24h]@3
	char v10[32]; // [sp+48h] [bp-20h]@3
	float v11; // [sp+70h] [bp+8h]@3

	EnableAlphaTest(1);
	glColor4f(1.0f, 0.7f, 0.0f, 1.0f);

	if (a4 >= 0.300000011920929)
	{
		v8 = (a4 - 0.4800000119209290) * 12.0;
		itoa(a3, v10, 10);
		v9 = strlen(v10);
		v11 = a1 - (double)v9 * v8 / 2.0;
		for (i = 0; i < v9; ++i)
		{
			v6 = (double)(v10[i] - 48) * 12.0 / 128.0;
			v5 = (a4 - 0.400000011920929) * 16.0;
			RenderBitmap(ModelID, v11, a2, v8, v5, v6, 0.0, 0.09375, 0.875, 1, 1, 0.0);
			v11 = v8 * 0.800000011920929 + v11;
		}
		result = v11;
	}
	else
	{
		result = a1;
	}
	pGLSupremo();
	return result;
}

float Interface::CRenderNumberClassic(BYTE Color, float x, float y, int iNum, float fScale)
{
	EnableAlphaTest(1);
	if (fScale < 0.3f)
	{
		return x;
	}

	char strText[32];
	itoa(iNum, strText, 10);
	int iLength = (int)strlen(strText);

	if (Color == 1) // 
	{
		float width = 11.f * (fScale - 0.3f);
		float height = 17.3f * (fScale - 0.3f);
		x -= width * iLength / 2;
		for (int i = 0; i < iLength; ++i)
		{
			float fU = (float)(strText[i] - 48) * 12.f / 128.f;
			RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
			x += width * 0.8f;
		}
	}
	if (Color == 2) //
	{
		float width = 11.f * (fScale - 0.3f);
		float height = 17.3f * (fScale - 0.3f);
		x -= width * iLength / 2;
		for (int i = 0; i < iLength; ++i)
		{
			float fU = (float)(strText[i] - 48) * 12.f / 128.f;
			RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
			x += width * 0.8f;
		}
		RenderBitmap(41004, x, y, width + 3, height, 0.f, 0.f, 9.f / 16.f, 14.f / 16.f, 1, 1, 0.0);
	}
	return x;
}

float Interface::RenderExNumberLevel2(float x, float y, int iNum, int iNum1, float fScale)
{
	EnableAlphaTest(1);
	if (fScale < 0.3f)
	{
		return x;
	}

	char strText[32];
	char strText1[32];
	itoa(iNum, strText, 10);
	itoa(iNum1, strText1, 10);
	int iLength = (int)strlen(strText);
	int iLength1 = (int)strlen(strText1);
	float width = 11.f * (fScale - 0.3f);
	float height = 17.3f * (fScale - 0.3f);

	x -= width * iLength / 2;
	for (int i = 0; i < iLength; ++i)
	{
		float fU = (float)(strText[i] - 48) * 12.f / 128.f;
		RenderBitmap(31337, x + 0.5, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
		x += width * 0.8f;
	}
	RenderBitmap(0x1791A, x, y, width + 3, height, 0.f, 0.f, 9.f / 16.f, 14.f / 16.f, 1, 1, 0.0);
	x += width * 1.8f;
	x -= width * iLength1 / 2;
	for (int i = 0; i < iLength1; ++i)
	{
		float fU = (float)(strText1[i] - 48) * 12.f / 128.f;
		RenderBitmap(31337, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, 1, 1, 0.0);
	}
	return x;
}

#if(Check_WindowS)
void Interface::CheckWindowSProTecno(int type)
{
	switch (type)
	{
	case 0: //Event Time
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 1: //VIP
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 2: //Comando
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 3: //Jewel Bank
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 4: //Daily
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 5: //Lucky Wheel
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 6: //XShop
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eADDPOINT_MAIN].OnShow = false;				//	Antilag
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 7: //Antilag
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 8: //CustomFlag
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eRankPANEL_MAIN].OnShow = false;			//	CustomRanking
	}
	break;
	case 9: //CustomRanking
	{
		gInterface.Data[eMENU_MAIN].OnShow = false;					//	MENU
		gInterface.Data[eADDPOINT3_MAIN].OnShow = false;			//	EventTime
		gInterface.Data[eVip_MAIN].OnShow = false;					//	VIP
		gInterface.Data[eCommand_MAIN].OnShow = false;				//	comandos
		gInterface.Data[eJewelBank_MAIN].OnShow = false;			//	JewelBank
		gInterface.Data[eMAIN_DailySystem].OnShow = false;			//	DAILYREWARD
		gInterface.Data[eWindowVongQuay].OnShow = false;			//	LuckyWheel
		gInterface.Data[eINVASION_MAIN].OnShow = false;				//	INVASION
		gInterface.Data[eCustomShop].OnShow = false;				//	CustomXShop
		gInterface.Data[eMAIN_ThueFlag].OnShow = false;				//	CustomFlag
	}
	break;
	case 10: //
	{
	}
	break;
	case 11: //
	{
	}
	break;
	case 12: //
	{

	}
	break;
	}
}
#endif

void Interface::DrawPartyMenu()
{
	if (!gInterface.Data[OBJECT_PARTYMENU_MAIN].OnShow)
	{
		return;
	}

	float MainWidth = 230.0;
	float StartY = 100.0;
	float StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	float ButtonX = StartX + (MainWidth / 2) - 54.0;

	pSetCursorFocus = true;

	// Draw the base object to maintain state/MaxX/MaxY
	gInterface.DrawGUI(OBJECT_PARTYMENU_MAIN, StartX, StartY + 2);

	// Overdraw with stretched background to fill the smaller frame
	pDrawGUI(0x7A5A, StartX + 4, StartY + 2, 222.0f, 145.0f);

	gInterface.DrawGUI(OBJECT_PARTYMENU_TITLE, StartX, StartY);
	StartY = gInterface.DrawRepeatGUI(OBJECT_PARTYMENU_FRAME, StartX, StartY + 67.0, 2);
	gInterface.DrawGUI(OBJECT_PARTYMENU_FOOTER, StartX, StartY);

	// StartY is now offset. Restore it to original for drawing components
	StartY = 100.0;

	gInterface.DrawFormat(eGold, StartX + 10, StartY + 12, 210, 3, "Party Search");

	gInterface.DrawButton(OBJECT_PARTYMENU_BTN_PUBLICAR, ButtonX, StartY + 50, 0, 0);
	if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_PUBLICAR))
	{
		gInterface.DrawButton(OBJECT_PARTYMENU_BTN_PUBLICAR, ButtonX, StartY + 50, 0, 29);
	}
	gInterface.DrawFormat(eWhite, ButtonX, StartY + 59, 108, 3, "Publicar Party");

	gInterface.DrawButton(OBJECT_PARTYMENU_BTN_BUSCAR, ButtonX, StartY + 90, 0, 0);
	if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_BUSCAR))
	{
		gInterface.DrawButton(OBJECT_PARTYMENU_BTN_BUSCAR, ButtonX, StartY + 90, 0, 29);
	}
	gInterface.DrawFormat(eWhite, ButtonX, StartY + 99, 108, 3, "Buscar Party");
}

bool Interface::EventPartyMenu(DWORD Event)
{
	if (!gInterface.Data[OBJECT_PARTYMENU_MAIN].OnShow)
	{
		return false;
	}

	if (Event == WM_LBUTTONDOWN)
	{
		if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_PUBLICAR))
		{
			gInterface.Data[OBJECT_PARTYMENU_BTN_PUBLICAR].OnClick = true;
			return true;
		}

		if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_BUSCAR))
		{
			gInterface.Data[OBJECT_PARTYMENU_BTN_BUSCAR].OnClick = true;
			return true;
		}
	}

	if (Event == WM_LBUTTONUP)
	{
		if (gInterface.Data[OBJECT_PARTYMENU_BTN_PUBLICAR].OnClick)
		{
			gInterface.Data[OBJECT_PARTYMENU_BTN_PUBLICAR].OnClick = false;
			if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_PUBLICAR))
			{
				BYTE pMsg[4] = {0xC1, 0x04, 0xFF, 0x06};
				DataSend(pMsg, 4);

				gInterface.Data[OBJECT_PARTYMENU_MAIN].Close();
				gInterface.Data[OBJECT_PARTYSETTINGS_MAIN].Open();
			}
			return true;
		}

		if (gInterface.Data[OBJECT_PARTYMENU_BTN_BUSCAR].OnClick)
		{
			gInterface.Data[OBJECT_PARTYMENU_BTN_BUSCAR].OnClick = false;
			if (gInterface.IsWorkZone(OBJECT_PARTYMENU_BTN_BUSCAR))
			{
				BYTE pMsg[4] = {0xC1, 0x04, 0xFF, 0x07};
				DataSend(pMsg, 4);

				gInterface.Data[OBJECT_PARTYMENU_MAIN].Close();
				gPartySearch.ClearPartyList();
				gInterface.Data[OBJECT_PARTYSEARCH_MAIN].Open();
			}
			return true;
		}
	}

	if (gInterface.IsWorkZone(OBJECT_PARTYMENU_MAIN))
	{
		return true;
	}

	return false;
}
