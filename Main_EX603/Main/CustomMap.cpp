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
	if (iMap == 75 || iMap >= 82)
	{
		return g_pUIMapName.GetNameMap(iMap);
	}
	else
	{
		return pGetMapName_Original(iMap);
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
