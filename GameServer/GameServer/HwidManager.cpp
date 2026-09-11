#include "stdafx.h"
#include "HwidManager.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "Util.h"
#include "MemScript.h"

CHwidManager gHwidManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHwidManager::CHwidManager()
{

}

CHwidManager::~CHwidManager()
{

}

void CHwidManager::Load(char* path) // OK
{
	if(GetFileAttributes(path) == INVALID_FILE_ATTRIBUTES)
	{
		LogAdd(LOG_BLUE, "[HwidManager] HardwareIdExceptionList not found (%s)", path);
		return;
	}

	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		delete lpMemScript;
		return;
	}

	this->m_HwidExceptionInfo.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					std::string hwid = lpMemScript->GetString();
					if(!hwid.empty())
					{
						this->m_HwidExceptionInfo.insert(hwid);
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CHwidManager::CheckHwidException(char* HardwarewId) // OK
{
	if(HardwarewId == 0 || HardwarewId[0] == '\0')
	{
		return 0;
	}

	if(this->m_HwidExceptionInfo.find(std::string(HardwarewId)) != this->m_HwidExceptionInfo.end())
	{
		return 1;
	}

	return 0;
}

bool CHwidManager::CheckHwid(char* HardwarewId) // OK
{
	if(this->CheckHwidException(HardwarewId) != 0)
	{
		return 1;
	}

	std::map<std::string,HardwareId_INFO>::iterator it = this->m_HwidInfo.find(std::string(HardwarewId));

	if(it == this->m_HwidInfo.end())
	{
		return ((gServerInfo.m_MaxHwidConnection==0)?0:1);
	}
	else
	{
		return ((it->second.HardwareIdCount>=gServerInfo.m_MaxHwidConnection[it->second.MaxAccountLevel])?0:1);
	}
}

int CHwidManager::GetOfflineCountByHwid(char* HardwarewId)
{
	if(HardwarewId == 0 || HardwarewId[0] == '\0')
	{
		return 0;
	}

	int count = 0;

	for(int n = OBJECT_START_USER; n < MAX_OBJECT; n++)
	{
		if(gObj[n].Connected >= OBJECT_CONNECTED)
		{
			if(strcmp(gObj[n].HardwareId, HardwarewId) == 0)
			{
				if(gObj[n].m_OfflineMode != 0 || gObj[n].AttackCustomOffline != 0 || gObj[n].PShopCustomOffline != 0)
				{
					count++;
				}
			}
		}
	}

	return count;
}

void CHwidManager::InsertHwid(char* HardwarewId, int aIndex) // OK
{
	HardwareId_INFO info;

	strcpy_s(info.HardwareId,HardwarewId);

	info.HardwareIdCount = 1;

	info.aIndex = aIndex;

	info.MaxAccountLevel = gObj[aIndex].AccountLevel;

	std::map<std::string,HardwareId_INFO>::iterator it = this->m_HwidInfo.find(std::string(HardwarewId));

	if(it == this->m_HwidInfo.end())
	{
		this->m_HwidInfo.insert(std::pair<std::string,HardwareId_INFO>(std::string(HardwarewId),info));
	}
	else
	{
		if (gObj[aIndex].AccountLevel > info.MaxAccountLevel)
		{
			info.MaxAccountLevel = gObj[aIndex].AccountLevel;
		}

		it->second.HardwareIdCount++;
	}
}

void CHwidManager::RemoveHwid(char* HardwarewId) // OK
{
	std::map<std::string,HardwareId_INFO>::iterator it = this->m_HwidInfo.find(std::string(HardwarewId));

	if(it != this->m_HwidInfo.end())
	{
		if((--it->second.HardwareIdCount) == 0)
		{
			this->m_HwidInfo.erase(it);
		}
	}
}

void CHwidManager::ConnectHwid(CG_HWID_SEND *lpMsg, LPOBJ lpObj)
{
	if (strcmp(lpMsg->DLLVersion,GAMESERVER_VERSION) != 0)
	{
		LogAdd(LOG_RED,"Invalid DLL Version! Current [%s] DLL [%s]", GAMESERVER_VERSION, lpMsg->DLLVersion);
		lpObj->Socket = INVALID_SOCKET;
		closesocket(lpObj->PerSocketContext->Socket);
		gObjDel(lpObj->Index);
		return;
	}

	if (gServerInfo.m_AntihackDllCRC != 0)
	{
		if (gServerInfo.m_AntihackDllCRC != lpMsg->AntihackDllCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	if (gServerInfo.m_MainDllCRC != 0)
	{
		if (gServerInfo.m_MainDllCRC != lpMsg->MainDllCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	if (gServerInfo.m_MainExeCRC != 0)
	{
		if (gServerInfo.m_MainExeCRC != lpMsg->MainExeCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	if (gServerInfo.m_PlayerBmdCRC != 0)
	{
		if (gServerInfo.m_PlayerBmdCRC != lpMsg->PlayerBmdCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	if (gServerInfo.m_SkillBmdCRC != 0)
	{
		if (gServerInfo.m_SkillBmdCRC != lpMsg->SkillBmdCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	if (gServerInfo.m_ItemBmdCRC != 0)
	{
		if (gServerInfo.m_ItemBmdCRC != lpMsg->ItemBmdCRC)
		{
			lpObj->Socket = INVALID_SOCKET;
			closesocket(lpObj->PerSocketContext->Socket);
			gObjDel(lpObj->Index);
			return;
		}
	}

	bool AllowConnection = (this->CheckHwid(lpMsg->HardwareId) != 0);

	if (AllowConnection == 0)
	{
		int OfflineCount = this->GetOfflineCountByHwid(lpMsg->HardwareId);
		if (OfflineCount > 0)
		{
			lpObj->m_OfflineHwidGrace = true;
			AllowConnection = 1;
		}
	}

	if (AllowConnection == 0)
	{
		gObjDel(lpObj->Index);
		return;
	}

	strcpy_s(lpObj->HardwareId,lpMsg->HardwareId);
	this->InsertHwid(lpMsg->HardwareId, lpObj->Index);
}