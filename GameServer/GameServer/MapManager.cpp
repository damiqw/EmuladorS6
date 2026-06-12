// MapManager.cpp: implementation of the CMapManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapManager.h"
#include "MemScript.h"
#include "ServerInfo.h"
#include "Util.h"

CMapManager gMapManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapManager::CMapManager() // OK
{
	this->m_MapManagerInfo.clear();
}

CMapManager::~CMapManager() // OK
{

}

void CMapManager::Load(char* path) // OK
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

	this->m_MapManagerInfo.clear();

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

			MAP_MANAGER_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.NonPK = lpMemScript->GetAsNumber();

			info.ViewRange = lpMemScript->GetAsNumber();

			info.ExperienceRate = lpMemScript->GetAsNumber();

			info.MasterExperienceRate = lpMemScript->GetAsNumber();

			info.ItemDropRate = lpMemScript->GetAsNumber();

			info.ExcItemDropRate = lpMemScript->GetAsNumber();

			info.SetItemDropRate = lpMemScript->GetAsNumber();

			info.SocketItemDrop = lpMemScript->GetAsNumber();

			#if(GAMESERVER_UPDATE>=603)

			info.HelperEnable = lpMemScript->GetAsNumber();

			#else

			info.HelperEnable = 0;

			#endif

			#if(GAMESERVER_UPDATE>=501)

			info.GensBattle = lpMemScript->GetAsNumber();

			#else

			info.GensBattle = 0;

			#endif

			info.PkDropItem = lpMemScript->GetAsNumber();

			info.MonsterHPBar = lpMemScript->GetAsNumber();

			info.TradeEnable = lpMemScript->GetAsNumber();

			info.CustomStore = lpMemScript->GetAsNumber();

			info.CustomAttack = lpMemScript->GetAsNumber();

			info.CustomPick = lpMemScript->GetAsNumber();

			info.ChatEnable = lpMemScript->GetAsNumber();

			info.PartyEnable = lpMemScript->GetAsNumber();

			info.DuelEnable = lpMemScript->GetAsNumber();

			info.SpawnGate = lpMemScript->GetAsNumber();

			info.RespawnGate = lpMemScript->GetAsNumber();

			strcpy_s(info.Name,lpMemScript->GetAsString());

			this->m_MapManagerInfo.insert(std::pair<int,MAP_MANAGER_INFO>(info.Index,info));
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

int CMapManager::IsValidMap(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return 1;
	}

	return 0;
}

int CMapManager::GetMapNonPK(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return gServerInfo.m_NonPK;
	}
	else
	{
		return ((it->second.NonPK==-1)?gServerInfo.m_NonPK:((it->second.NonPK==1)?1:0));
	}
}

int CMapManager::GetMapNonOutlaw(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.NonPK==-1)?0:((it->second.NonPK==2)?1:0));
	}
}

int CMapManager::GetMapViewRange(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 15;
	}
	else
	{
		return ((it->second.ViewRange==-1)?15:it->second.ViewRange);
	}
}

int CMapManager::GetMapExperienceRate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 100;
	}
	else
	{
		return ((it->second.ExperienceRate==-1)?100:it->second.ExperienceRate);
	}
}

int CMapManager::GetMapMasterExperienceRate(int index) // OK
{
	#if(GAMESERVER_UPDATE>=401)

	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return it->second.MasterExperienceRate;
	}

	#endif

	return 100;
}

int CMapManager::GetMapItemDropRate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 100;
	}
	else
	{
		return ((it->second.ItemDropRate==-1)?100:it->second.ItemDropRate);
	}
}

int CMapManager::GetMapExcItemDropRate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.ExcItemDropRate==-1)?0:it->second.ExcItemDropRate);
	}
}

int CMapManager::GetMapSetItemDropRate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.SetItemDropRate==-1)?0:it->second.SetItemDropRate);
	}
}

int CMapManager::GetMapSocketItemDrop(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.SocketItemDrop==-1)?0:it->second.SocketItemDrop);
	}
}

int CMapManager::GetMapHelperEnable(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.HelperEnable==-1)?0:it->second.HelperEnable);
	}
}

int CMapManager::GetMapGensBattle(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.GensBattle==-1)?0:it->second.GensBattle);
	}
}

int CMapManager::GetMapPkDropItem(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.PkDropItem==-1)?0:it->second.PkDropItem);
	}
}

int CMapManager::GetMapMonsterHPBar(int index) // OK
{
	#if(GAMESERVER_UPDATE<=603)

	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return ((it->second.MonsterHPBar == -1) ? gServerInfo.m_MonsterHealthBarSwitch : ((it->second.MonsterHPBar == 1) ? 1 : 0));
	}

	return gServerInfo.m_MonsterHealthBarSwitch;

	#else

	return 0;

	#endif
}

int CMapManager::GetMapTradeEnable(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return ((it->second.TradeEnable == -1) ? gServerInfo.m_TradeSwitch : ((it->second.TradeEnable == 1) ? 1 : 0));
	}

	return gServerInfo.m_TradeSwitch;
}

int CMapManager::GetMapCustomStore(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.CustomStore==-1)?0:it->second.CustomStore);
	}
}

int CMapManager::GetMapCustomAttack(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.CustomAttack==-1)?0:it->second.CustomAttack);
	}
}



int CMapManager::GetMapCustomPick(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return 0;
	}
	else
	{
		return ((it->second.CustomPick==-1)?0:it->second.CustomPick);
	}
}

int CMapManager::GetMapChatEnable(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return it->second.ChatEnable;
	}

	return 0;
}

int CMapManager::GetMapPartyEnable(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return it->second.PartyEnable;
	}

	return 0;
}

int CMapManager::GetMapDuelEnable(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return ((it->second.DuelEnable == -1) ? gServerInfo.m_DuelSwitch : ((it->second.DuelEnable == 1) ? 1 : 0));
	}

	return gServerInfo.m_DuelSwitch;
}

int CMapManager::GetSpawnGate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return it->second.SpawnGate;
	}

	return -1;
}

int CMapManager::GetRespawnGate(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it != this->m_MapManagerInfo.end())
	{
		return it->second.RespawnGate;
	}

	return -1;
}

char* CMapManager::GetMapName(int index) // OK
{
	std::map<int,MAP_MANAGER_INFO>::iterator it = this->m_MapManagerInfo.find(index);

	if(it == this->m_MapManagerInfo.end())
	{
		return "NoName";
	}
	else
	{
		return it->second.Name;
	}
}
