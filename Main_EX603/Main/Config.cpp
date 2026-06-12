#include "StdAfx.h"
#include "Config.h"
#include "Util.h"
#include <stdlib.h>
#include "windows.h"
#include "Protect.h"

cConfig gConfig;

void cConfig::Load()
{
	for (int Lang = 0; Lang < MAX_RANGE_TEXT; Lang++)
	{
		char section[MAX_RANGE_TEXT], key[MAX_RANGE_TEXT];
		sprintf_s(section, "JewelBankText");
		sprintf_s(key, "TEXT_%d", Lang);
		GetPrivateProfileStringA(section, key, "Null", TEXT_ENGINE[Lang], sizeof(TEXT_ENGINE[Lang]), MENU_GAME_FILE);
	}

	for (int Lang = 0; Lang < MAX_RANGE_TEXT; Lang++)
	{
		char section[MAX_RANGE_TEXT], key[MAX_RANGE_TEXT];
		sprintf_s(section, "CustomXShopText");
		sprintf_s(key, "TEXT_%d", Lang);
		GetPrivateProfileStringA(section, key, "Null", TEXT_XSHOP[Lang], sizeof(TEXT_XSHOP[Lang]), MENU_GAME_FILE);
	}

	for (int Menu = 0; Menu < MAX_RANGE_MENU; Menu++)
	{
		char section[50], key[50];
		sprintf_s(section, "MenuGame");
		sprintf_s(key, "MenuGame%0d", Menu);
		GetPrivateProfileStringA(section, key, "Null", MenuGame_TextVN[Menu], sizeof(MenuGame_TextVN[Menu]), MENU_GAME_FILE);
	}
}