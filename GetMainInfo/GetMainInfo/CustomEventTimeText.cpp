// CustomItem.cpp: implementation of the CCustomItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CustomEventTimeText.h"
#include "MemScript.h"

CCustomEventTimeText gCustomEventTimeText;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomEventTimeText::CCustomEventTimeText() // OK
{
	this->Init();
}

CCustomEventTimeText::~CCustomEventTimeText() // OK
{

}

void CCustomEventTimeText::Init() // OK
{
	for(int n=0;n < MAX_EVENTTIME;n++)
	{
		this->m_CustomEventInfo[n].Index = -1;
	}
}

bool CCustomEventTimeText::Load(char* path) // OK
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

			CUSTOM_EVENT_INFO info;

			memset(&info,0,sizeof(info));

			info.Index = lpMemScript->GetNumber();

			strcpy_s(info.Name,lpMemScript->GetAsString());

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

void CCustomEventTimeText::SetInfo(CUSTOM_EVENT_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_EVENTTIME)
	{
		return;
	}

	this->m_CustomEventInfo[info.Index] = info;
}
