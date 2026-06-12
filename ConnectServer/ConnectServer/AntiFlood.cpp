#include "stdafx.h"
#include "AntiFlood.h"
#include "Log.h"
#include "Util.h"
#include "ConnectServer.h"

CAntiFlood gAntiFlood;

CAntiFlood::CAntiFlood()
{
	this->m_AntiFloodInfo.clear();
}

CAntiFlood::~CAntiFlood()
{

}

void CAntiFlood::AddIpAddress(char * IpAddress)
{
	std::map<std::string, ANTI_FLOOD_INFO>::iterator it = this->m_AntiFloodInfo.find(IpAddress);

	if (it == this->m_AntiFloodInfo.end())
	{
		ANTI_FLOOD_INFO info;

		memset(&info, 0, sizeof(ANTI_FLOOD_INFO));

		strcpy_s(info.IpAddress, IpAddress);

		info.Count = 1;

		info.TickCount = GetTickCount();

		this->m_AntiFloodInfo.insert(std::pair<std::string, ANTI_FLOOD_INFO>(IpAddress, info));
	}
	else
	{
		it->second.Count++;
		it->second.LastActivity = GetTickCount();
	}
}

bool CAntiFlood::CheckFlood(char * IpAddress)
{
	std::map<std::string, ANTI_FLOOD_INFO>::iterator it = this->m_AntiFloodInfo.find(IpAddress);

	if (it == this->m_AntiFloodInfo.end())
	{
		return 1;
	}
	else
	{
		if (it->second.Block)
		{
			if ((int)((GetTickCount() - it->second.BlockTime) / 1000) > m_AntiFloodBlockTime)
			{
				this->m_AntiFloodInfo.erase(IpAddress);

				LogAdd(LOG_RED, "[PROTECTION] FLOOD [%s] IP UNLOCK", IpAddress);
				return 1;
			}

			return 0;
		}

		if ((int)((GetTickCount() - it->second.TickCount) / 1000) < m_AntiFloodMinTimeCheck)
		{
			if (it->second.Count >= m_AntiFloodMaxCount)
			{
				if (!it->second.Block)
				{
					this->BlockIpAddress(IpAddress);
					return 0;
				}
			}
		}
		else
		{
			if ((int)((GetTickCount() - it->second.LastActivity) / 1000) > m_AntiFloodMaxTimeCheck)
			{
				this->m_AntiFloodInfo.erase(IpAddress);
			}
		}
	}

	return 1;
}

void CAntiFlood::BlockIpAddress(char * IpAddress)
{
	std::map<std::string, ANTI_FLOOD_INFO>::iterator it = this->m_AntiFloodInfo.find(IpAddress);

	if (it != this->m_AntiFloodInfo.end())
	{
		it->second.Block = 1;
		it->second.BlockTime = GetTickCount();

		LogAdd(LOG_RED, "[PROTECTION] FLOOD DETECTED [%s] IP LOCK", IpAddress);
	}
}