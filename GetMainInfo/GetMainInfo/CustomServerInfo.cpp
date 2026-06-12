#include "StdAfx.h"
#include "CustomServerInfo.h"
#include "MemScript.h"

CServerInfo g_ServerInfo;

CServerInfo::CServerInfo()
{
	this->Init();
}
CServerInfo::~CServerInfo()
{
}


void CServerInfo::Init()
{
	for(int n=0;n < MAX_SERVER_CLASS;n++)
	{
		this->m_data[n].SubServerNum = -1;
	};
}

bool CServerInfo::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;
	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return 0;
	}
	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}
	this->Init();
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
			SERVERINFO_DATA info;
			memset(&info,0,sizeof(info));
			static int CustomItemIndexCount = 0;
					
			info.Index = CustomItemIndexCount++;

			info.SubServerNum = lpMemScript->GetNumber();
			
			strcpy_s(info.ServerName,lpMemScript->GetAsString());
			
			strcpy_s(info.ServerText,lpMemScript->GetAsString());
		
			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}

void CServerInfo::SetInfo(SERVERINFO_DATA info)
{
	if(info.Index < 0 || info.Index >= MAX_SERVER_CLASS)
	{
		return;
	}

	this->m_data[info.Index] = info;
}