#pragma once

struct ANTI_FLOOD_INFO
{
	char IpAddress[16];
	DWORD Count;
	DWORD TickCount;
	bool Block;
	DWORD BlockTime;
	DWORD LastActivity;
};

class CAntiFlood
{
public:
	CAntiFlood();
	virtual ~CAntiFlood();

	void AddIpAddress(char * IpAddress);
	bool CheckFlood(char * IpAddress);
	void BlockIpAddress(char * IpAddress);

private:
	std::map<std::string, ANTI_FLOOD_INFO> m_AntiFloodInfo;
};

extern CAntiFlood gAntiFlood;