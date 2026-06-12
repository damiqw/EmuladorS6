#pragma once

struct SERVERINFO_DATA
{
	int Index;
	int SubServerNum;
	char ServerName[20];
	char ServerText[50];
};

class CServerInfo
{
public:
	CServerInfo();
	virtual ~CServerInfo();
	void Init();
	bool Load(char* path);
	void SetInfo(SERVERINFO_DATA info);
public:
	SERVERINFO_DATA m_data[MAX_SERVER_CLASS];

}; 
extern CServerInfo g_ServerInfo;