#include "stdafx.h"
#include "HwidManager.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "Util.h"

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

bool CHwidManager::CheckHwid(char* HardwarewId) // OK
{
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

	if (this->CheckHwid(lpMsg->HardwareId) == 0)
	{
		gObjDel(lpObj->Index);
		return;
	}

	strcpy_s(lpObj->HardwareId,lpMsg->HardwareId);
	this->InsertHwid(lpMsg->HardwareId, lpObj->Index);
}