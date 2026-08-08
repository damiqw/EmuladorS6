// MonsterManager.cpp: implementation of the CMonsterManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterManager.h"
#include "pugixml.hpp"
#include "380ItemType.h"
#include "BloodCastle.h"
#include "BonusManager.h"
#include "CastleDeep.h"
#include "CastleSiege.h"
#include "ChaosCastle.h"
#include "Crywolf.h"
#include "CustomArena.h"
#include "CustomEventDrop.h"
#include "CustomOnlineLottery.h"
#include "CustomQuiz.h"
#include "DevilSquare.h"
#include "IllusionTemple.h"
#include "InvasionManager.h"
#include "ItemManager.h"
#include "EventGvG.h"
#include "EventTvT.h"
#include "Map.h"
#include "MemScript.h"
#include "Monster.h"
#include "MonsterSetBase.h"
#include "MossMerchant.h"
#include "ObjectManager.h"
#include "Raklion.h"
#include "ServerInfo.h"
#include "SocketItemType.h"
#include "User.h"
#include "Util.h"
#include "CustomLukeHelper.h"

CMonsterManager gMonsterManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterManager::CMonsterManager() // OK
{
	this->Init();
}

CMonsterManager::~CMonsterManager() // OK
{

}

void CMonsterManager::Init() // OK
{
	for(int n=0;n < MAX_MONSTER_INFO;n++)
	{
		this->m_MonsterInfo[n].Index = -1;
	}

	for(int n=0;n < MAX_MONSTER_LEVEL;n++)
	{
		memset(this->m_MonsterItemInfo[n].IndexTable,-1,sizeof(this->m_MonsterItemInfo[n].IndexTable));

		this->m_MonsterItemInfo[n].IndexCount = 0;
	}
}

void CMonsterManager::Load(char* path) // OK
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(path);

	if(res.status != pugi::status_ok)
	{
		ErrorMessageBox((char*)res.description());
		return;
	}

	this->Init();

	try
	{
		pugi::xml_node main_node = file.child("MonsterList");

		for(pugi::xml_node monster_node = main_node.child("Monster"); monster_node; monster_node = monster_node.next_sibling("Monster"))
		{
			MONSTER_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = monster_node.attribute("Index").as_int();

			info.Rate = monster_node.attribute("Rate").as_int();

			strcpy_s(info.Name, monster_node.attribute("Name").as_string());

			info.Level = monster_node.attribute("Level").as_int();

			info.Life = monster_node.attribute("Life").as_int();

			info.Mana = monster_node.attribute("Mana").as_int();

			info.DamageMin = monster_node.attribute("DamageMin").as_int();

			info.DamageMax = monster_node.attribute("DamageMax").as_int();

			info.Defense = monster_node.attribute("Defense").as_int();

			info.MagicDefense = monster_node.attribute("MagicDefense").as_int();

			info.AttackRate = monster_node.attribute("AttackRate").as_int();

			info.DefenseRate = monster_node.attribute("DefenseRate").as_int();

			info.MoveRange = monster_node.attribute("MoveRange").as_int();

			info.AttackType = monster_node.attribute("AttackType").as_int();

			info.AttackRange = monster_node.attribute("AttackRange").as_int();

			info.ViewRange = monster_node.attribute("ViewRange").as_int();

			info.MoveSpeed = monster_node.attribute("MoveSpeed").as_int();

			info.AttackSpeed = monster_node.attribute("AttackSpeed").as_int();

			info.RegenTime = monster_node.attribute("RegenTime").as_int();

			info.Attribute = monster_node.attribute("Attribute").as_int();

			info.ItemRate = monster_node.attribute("ItemRate").as_int();

			info.MoneyRate = monster_node.attribute("MoneyRate").as_int();

			info.MaxItemLevel = monster_node.attribute("MaxItemLevel").as_int();

			info.MonsterSkill = monster_node.attribute("MonsterSkill").as_int();

			info.Resistance[0] = monster_node.attribute("Resistance0").as_int();

			info.Resistance[1] = monster_node.attribute("Resistance1").as_int();

			info.Resistance[2] = monster_node.attribute("Resistance2").as_int();

			info.Resistance[3] = monster_node.attribute("Resistance3").as_int();

			#if(GAMESERVER_UPDATE>=701)

			info.ElementalAttribute = monster_node.attribute("ElementalAttribute").as_int();

			info.ElementalPattern = monster_node.attribute("ElementalPattern").as_int();

			info.ElementalDefense = monster_node.attribute("ElementalDefense").as_int();

			info.ElementalDamageMin = monster_node.attribute("ElementalDamageMin").as_int();

			info.ElementalDamageMax = monster_node.attribute("ElementalDamageMax").as_int();

			info.ElementalAttackRate = monster_node.attribute("ElementalAttackRate").as_int();

			info.ElementalDefenseRate = monster_node.attribute("ElementalDefenseRate").as_int();

			#endif

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		ErrorMessageBox((char*)"Error parsing Monster.xml");
	}

	this->InitMonsterItem();
}

void CMonsterManager::SetInfo(MONSTER_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_MONSTER_INFO)
	{
		return;
	}

	info.Life = ((__int64)info.Life*gServerInfo.m_MonsterLifeRate)/100;

	info.Defense = ((__int64)(info.Defense*gServerInfo.m_MonsterDefenseRate))/100;
	
	info.DefenseRate = ((__int64)(info.DefenseRate*gServerInfo.m_MonsterDefenseSuccessRateRate))/100;
	
	info.DamageMin = ((__int64)(info.DamageMin*gServerInfo.m_MonsterPhysiDamageRate))/100;
	
	info.DamageMax = ((__int64)(info.DamageMax*gServerInfo.m_MonsterPhysiDamageRate))/100;
	
	info.AttackRate = ((__int64)(info.AttackRate*gServerInfo.m_MonsterAttackSuccessRateRate))/100;

	info.ScriptLife = info.Life;

	this->m_MonsterInfo[info.Index] = info;
}

MONSTER_INFO* CMonsterManager::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_MONSTER_INFO)
	{
		return 0;
	}

	if(this->m_MonsterInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_MonsterInfo[index];
}

char* CMonsterManager::GetMonsterName(int index) // OK
{
	MONSTER_INFO* MonsterInfo = this->GetInfo(index);

	if(MonsterInfo == NULL)
	{
		return "No Name";
	}
	else
	{
		return MonsterInfo->Name;
	}
}

void CMonsterManager::InitMonsterItem() // OK
{
	for(int n=0;n < MAX_MONSTER_LEVEL;n++)
	{
		this->InsertMonsterItem(n);
	}
}

void CMonsterManager::InsertMonsterItem(int level) // OK
{
	for(int n=0;n < MAX_ITEM;n++)
	{
		ITEM_INFO ItemInfo;

		if(gItemManager.GetInfo(n,&ItemInfo) == 0)
		{
			continue;
		}

		if(ItemInfo.Level < 0 || ItemInfo.DropItem == 0)
		{
			continue;
		}

		if((ItemInfo.Level+4) >= level && (ItemInfo.Level-2) <= level)
		{
			MONSTER_ITEM_INFO* lpItem = &this->m_MonsterItemInfo[level];

			if(lpItem->IndexCount >= 0 && lpItem->IndexCount < MAX_MONSTER_ITEM)
			{
				lpItem->IndexTable[lpItem->IndexCount++] = n;
			}
		}
	}
}

long CMonsterManager::GetMonsterItem(int level,int excellent,int socket) // OK
{
	if(level < 0 || level >= MAX_MONSTER_LEVEL)
	{
		return -1;
	}

	if(this->m_MonsterItemInfo[level].IndexCount == 0)
	{
		return -1;
	}

	int IndexTable[MAX_MONSTER_ITEM];
	int IndexCount = 0;

	for(int n=0;n < this->m_MonsterItemInfo[level].IndexCount;n++)
	{
		if(excellent != 0 && this->m_MonsterItemInfo[level].IndexTable[n] >= GET_ITEM(12,0))
		{
			continue;
		}

		if(excellent != 0 && g380ItemType.Check380ItemType(this->m_MonsterItemInfo[level].IndexTable[n]) != 0)
		{
			continue;
		}

		if((excellent != 0 || socket == 0) && gSocketItemType.CheckSocketItemType(this->m_MonsterItemInfo[level].IndexTable[n]) != 0)
		{
			continue;
		}

		IndexTable[IndexCount++] = this->m_MonsterItemInfo[level].IndexTable[n];
	}

	return ((IndexCount==0)?-1:IndexTable[GetLargeRand()%IndexCount]);
}

void CMonsterManager::SetMonsterData() // OK
{
	for(int n=0;n < gMonsterSetBase.m_count;n++)
	{
		MONSTER_SET_BASE_INFO* lpInfo = &gMonsterSetBase.m_MonsterSetBaseInfo[n];

		if(lpInfo->Type == 3 || lpInfo->Type == 4)
		{
			continue;
		}

		int index = gObjAddMonster(lpInfo->Map);

		if(OBJECT_RANGE(index) == 0)
		{
			continue;
		}

		if(gObjSetPosMonster(index,n) == 0)
		{
			gObjDel(index);
			continue;
		}

		if(gObjSetMonster(index,lpInfo->MonsterClass) == 0)
		{
			gObjDel(index);
			continue;
		}

		#if(GAMESERVER_TYPE==1)

		LPOBJ lpObj = &gObj[index];

		if(lpObj->Map == MAP_CASTLE_SIEGE)
		{
			if(lpObj->Class == 216)
			{
				gCastleSiege.SetCrownIndex(index);
			}
		}

		if(lpObj->Map == MAP_CRYWOLF)
		{
			if(lpObj->Type == OBJECT_MONSTER)
			{
				if(gCrywolf.m_ObjCommonMonster.AddObj(index) == 0)
				{
					gObjDel(index);
					continue;
				}
			}

			if(lpObj->Type == OBJECT_NPC)
			{
				if(lpObj->Class >= 204 && lpObj->Class <= 209)
				{
					if(gCrywolf.m_ObjSpecialNPC.AddObj(index) == 0)
					{
						gObjDel(index);
						continue;
					}
				}
				else
				{
					if(lpObj->Class != 406 && lpObj->Class != 407)
					{
						if(gCrywolf.m_ObjCommonNPC.AddObj(index) == 0)
						{
							gObjDel(index);
							continue;
						}
					}
				}
			}
		}

		#endif
	}

	gBloodCastle.Init();

	gBonusManager.Init();

	gCastleDeep.Init();

	gChaosCastle.Init();

	gCustomArena.Init();

	gCustomEventDrop.Init();

	gCustomOnlineLottery.Init();

	gCustomQuiz.Init();

	gTvTEvent.Init();

	gGvGEvent.Init();

	gCustomLukeHelper.Init();

	gDevilSquare.Init();

	gIllusionTemple.Init();

	gInvasionManager.Init();

	gMossMerchant.Init();

	gRaklion.SetState(RAKLION_STATE_END);
}
