#ifndef _Config_H
#define _Config_H
#define MAX_RANGE_TEXT 322
#define MAX_RANGE_MENU 41
class cConfig
{
public:
	void Load();
	char MenuGame_TextVN[MAX_RANGE_MENU][120];
	char TEXT_ENGINE[MAX_RANGE_TEXT][100];
	char TEXT_XSHOP[MAX_RANGE_TEXT][100];
};
extern cConfig gConfig;
#define MENU_GAME_FILE "./Data/Local/TextMuOnlineSystem.ini"
extern int Server;
#endif