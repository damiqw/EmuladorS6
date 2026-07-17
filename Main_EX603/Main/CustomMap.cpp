#include "stdafx.h"
#include "Util.h"
#include "CustomMap.h"
#include "Import.h"
#include "SEASON3B.h"
#include <string>

CUIMapName g_pUIMapName;
ImgPathMap m_mapImgPath;

void CUIMapName::OpenScritp(PathMap* thisa)
{
	this->MapPath.clear();

	for (int m = 0; m < MAX_CUSTOM_MAP; m++)
	{
		if (thisa[m].world != 75 && (thisa[m].world <= WD_81KARUTAN2 || thisa[m].world > WD_ENDMAP))
		{
			continue;
		}
		this->MapPath.insert(std::pair<int, PathMap>(thisa[m].world, thisa[m]));
	}
}

PathMap* CUIMapName::GetMapInfo(int world)
{
	listMap::iterator li = this->MapPath.find(world);

	if (li != this->MapPath.end())
	{
		return (PathMap*)&li->second;
	}
	return NULL;
}

char* CUIMapName::GetNameMap(int world)
{
	listMap::iterator li = this->MapPath.find(world);

	if (li != this->MapPath.end())
	{
		return GlobalText(GlobalLine, li->second.LineText);
	}
	return "No Found";
}

char* GetMapName(int iMap)
{
	switch (MapNumber)
	{
		case 0: return "Lorencia";
		case 1: return "Dungeon";
		case 2: return "Devias";
		case 3: return "Noria";
		case 4: return "Lost Tower";
		case 6: return "Arena";
		case 7: return "Atlans";
		case 8: return "Tarkan";
		case 9: return "Devil Square 1";
		case 10: return "Icarus";
		case 11: return "Blood Castle 1";
		case 12: return "Blood Castle 2";
		case 13: return "Blood Castle 3";
		case 14: return "Blood Castle 4";
		case 15: return "Blood Castle 5";
		case 16: return "Blood Castle 6";
		case 17: return "Blood Castle 7";
		case 18: return "Chaos Castle 1";
		case 19: return "Chaos Castle 2";
		case 20: return "Chaos Castle 3";
		case 21: return "Chaos Castle 4";
		case 22: return "Chaos Castle 5";
		case 23: return "Chaos Castle 6";
		case 24: return "Kalima 1";
		case 25: return "Kalima 2";
		case 26: return "Kalima 3";
		case 27: return "Kalima 4";
		case 28: return "Kalima 5";
		case 29: return "Kalima 6";
		case 30: return "Castle Siege";
		case 31: return "Land of Trials";
		case 32: return "Devil Square 2";
		case 33: return "Aida";
		case 34: return "Crywolf";
		case 36: return "Kalima 7";
		case 37: return "Kanturu 1";
		case 38: return "Kanturu 2";
		case 39: return "Kanturu 3";
		case 40: return "Custom Arena";
		case 41: return "Barracks";
		case 42: return "Refuge";
		case 45: return "Illusion Temple 1";
		case 46: return "Illusion Temple 2";
		case 47: return "Illusion Temple 3";
		case 48: return "Illusion Temple 4";
		case 49: return "Illusion Temple 5";
		case 50: return "Illusion Temple 6";
		case 51: return "Elbeland";
		case 52: return "Blood Castle 8";
		case 53: return "Chaos Castle 7";
		case 56: return "Swamp of Calmness";
		case 57: return "Raklion 1";
		case 58: return "Raklion 2";
		case 62: return "Santa Town";
		case 63: return "Vulcanus";
		case 64: return "Duel Arena";
		case 65: return "Double Goer 1";
		case 66: return "Double Goer 2";
		case 67: return "Double Goer 3";
		case 68: return "Double Goer 4";
		case 69: return "Imperial Guardian 1";
		case 70: return "Imperial Guardian 2";
		case 71: return "Imperial Guardian 3";
		case 72: return "Imperial Guardian 4";
		case 75: return "Mundioca";
		case 76: return "GM Map";
		case 79: return "Loren Market";
		case 80: return "Karutan 1";
		case 81: return "Karutan 2";
		case 82: return "Double Goer Renew 1";
		case 83: return "Double Goer Renew 2";
		case 84: return "Double Goer Renew 3";
		case 85: return "Double Goer Renew 4";
		case 86: return "Double Goer Renew 5";
		case 87: return "Double Goer Renew 6";
		case 88: return "Double Goer Renew 7";
		case 89: return "Double Goer Renew 8";
		case 90: return "Double Goer Renew 9";
		case 91: return "Acheron 1";
		case 92: return "Acheron 2";
		case 95: return "Deventer 1";
		case 96: return "Deventer 2";
		case 97: return "Chaos Castle Final";
		case 98: return "Illusion Temple Final 1";
		case 99: return "Illusion Temple Final 2";
		case 100: return "Urk Mountain 1";
		case 101: return "Urk Mountain 2";
		case 102: return "Devil Square Final";
		case 110: return "Nars";
		case 112: return "Ferea";
		case 113: return "Nixies Lake";
		case 114: return "Instance Zone";
		case 115: return "Labyrinth of Dimensions";
		case 116: return "Deep Dungeon 1";
		case 117: return "Deep Dungeon 2";
		case 118: return "Deep Dungeon 3";
		case 119: return "Deep Dungeon 4";
		case 120: return "Deep Dungeon 5";
		case 121: return "Trial Area";
		case 122: return "Swamp of Darkness";
		case 123: return "Kubera Mine 1";
		case 124: return "Kubera Mine 2";
		case 125: return "Kubera Mine 3";
		case 126: return "Kubera Mine 4";
		case 127: return "Kubera Mine 5";
		case 128: return "Atlans Abyss 1";
		case 129: return "Atlans Abyss 2";
		case 130: return "Atlans Abyss 3";
		case 131: return "Scorched Canyon";
		case 132: return "Crimson Icarus";
		case 133: return "Arenil Temple";
		case 134: return "Ashen Aida";
		case 135: return "Old Kethotum";
		case 136: return "Blaze Kethhotum";
		case 137: return "Kanturu Under Area";
		case 138: return "Ignis Vulcanus";
		case 139: return "Boss Battle Zone";
		case 140: return "Blood Tarkan";
		case 141: return "Tormenta Island";
		case 142: return "Twister Karutan";
		case 143: return "Kardamahal UnderGround Temple";
		case 144: return "Swamp of Doom";
		default:
			static char szUnknown[32];
			wsprintf(szUnknown, "Unknown(%d)", MapNumber);
			return szUnknown;
	}
}

void CUIMapName::InitImgPathMap(int* thisa)
{
	((void(__thiscall*)(int*)) 0x0047E1A0)(thisa);

	std::string  strFolderName;

	strFolderName.append("Local\\");

	strFolderName.append((char*)0xE8C5C4);
	strFolderName.append("\\ImgsMapName\\");

	listMap::iterator li = g_pUIMapName.MapPath.begin();

	for (; li != g_pUIMapName.MapPath.end(); li++)
	{
		std::string  strMapName;
		strMapName.append(strFolderName.c_str());

		if (li->second.MapName[0] != '\0')
		{
			strMapName.append(li->second.MapName);
		}
		else
		{
			strMapName.append("none.tga");
		}
		m_mapImgPath[li->second.world] = strMapName;
	}
}

void CUIMapName::ShowMapName(int thisa)
{
	if (World == 75 || World >= 82)
	{
		*(DWORD*)(thisa + 40) = FADEIN;
		*(float*)(thisa + 52) = 0.2f;
		*(DWORD*)(thisa + 48) = 0;

		if (World != 40)
		{
			if (*(WORD*)(thisa + 36) != World)
			{
				DeleteBitmap(31255, 0);

				if (m_mapImgPath.find(World) != m_mapImgPath.end())
				{
					pLoadImage((char*)m_mapImgPath[World].c_str(), 31255, 9728, 10496, 1, 0);
				}
				
				*(WORD*)(thisa + 36) = World;
				*(BYTE*)(thisa + 56) = IsStrifeMap(World);
			}
		}
		else
		{
			*(DWORD*)(thisa + 40) = HIDE;
		}
	}
	else
	{
		((void(__thiscall*)(int)) 0x0047FD60)(thisa);
	}
}

void PlayMp3Map(HDC hDC)
{
	MainScene(hDC);
	if (World == 75 || (World > WD_81KARUTAN2 && World <= WD_ENDMAP))
	{
		if (SceneFlag == MAIN_SCENE)
		{
			PathMap* t = g_pUIMapName.GetMapInfo(World);
			if (t)
			{
				std::string  strFolderName = "Data\\Music\\";
				if (*(bool*)(Hero + 14))
				{
					strFolderName += t->lpszMp3;
					PlayMp3(strFolderName.data(), 0);
				}
			}
		}
	}
}

void CUIMapName::Load()
{
	//Increase terrains amount
	SetByte(0x0062EBF7, 0x69);
	SetByte(0x0062EE41, 0x69);
	SetByte(0x0062EEE4, 0x69);
	//Bypass in terrains files
	SetByte(0x0062EBF8, 0xEB);
	SetByte(0x0062EBFE, 0xEB);
	SetByte(0x0062EE42, 0xEB);
	SetByte(0x0062EE48, 0xEB);
	SetByte(0x0062EEE5, 0xEB);
	SetByte(0x0062EEEB, 0xEB);
	//-- Gate.bmd + 1024 Lineas
	SetDword(0x005B57EA + 3, 0x400); //-- MaxData GateBMD
	SetDword(0x00589DBB + 3, 0x400); //-- MaxData GateBMD
	SetDword(0x004D2CB1 + 1, 0x3800); //-- MaxData GateBMD
	SetDword(0x004D2D9B + 1, 0x3800); //-- MaxData GateBMD
	SetCompleteHook(0xE8, 0x00520ECF, &GetMapName);
	SetCompleteHook(0xE8, 0x00520F1F, &GetMapName);
	SetCompleteHook(0xE8, 0x0063E743, &GetMapName);
	SetCompleteHook(0xE8, 0x00640EB2, &GetMapName);
	SetCompleteHook(0xE8, 0x007D2DD9, &GetMapName);
	SetCompleteHook(0xE8, 0x007E6C0F, &GetMapName);
	SetCompleteHook(0xE8, 0x0084AEF7, &GetMapName);
	SetCompleteHook(0xE8, 0x004DADA4, &PlayMp3Map);
	SetCompleteHook(0xE8, 0x0063E71B, &CUIMapName::ShowMapName);
	SetCompleteHook(0xE8, 0x0063EEB6, &CUIMapName::ShowMapName);
	SetCompleteHook(0xE8, 0x006410EE, &CUIMapName::ShowMapName);
	SetCompleteHook(0xE8, 0x0047E15A, &CUIMapName::InitImgPathMap);
}

