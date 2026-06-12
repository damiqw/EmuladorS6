// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomCommandInfo.h"
#include "MemScript.h"

CCustomCommandInfo gCustomCommandInfo;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomCommandInfo::CCustomCommandInfo() // OK
{
	this->Init();
}

CCustomCommandInfo::~CCustomCommandInfo() // OK
{

}

void CCustomCommandInfo::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_COMMAND;n++)
	{
		this->m_CustomCommandInfo[n].Index = -1;
	}
}

bool CCustomCommandInfo::Load(char* path) // OK
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

			CUSTOM_COMMAND_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.Color = lpMemScript->GetAsNumber();

			strcpy_s(info.Command,lpMemScript->GetAsString());

			strcpy_s(info.Description,lpMemScript->GetAsString());

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

void CCustomCommandInfo::SetInfo(CUSTOM_COMMAND_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_COMMAND)
	{
		return;
	}

	this->m_CustomCommandInfo[info.Index] = info;
}
