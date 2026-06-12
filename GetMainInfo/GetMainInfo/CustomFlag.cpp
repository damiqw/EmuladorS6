#include "stdafx.h"
#include "CustomFlag.h"
#include "MemScript.h"

cCustomFlag gCustomFlag;

cCustomFlag::cCustomFlag()
{
	this->Init();
}

cCustomFlag::~cCustomFlag()
{

}

void cCustomFlag::Init()
{
	for(int n=0;n < MAX_CUSTOM_FLAG;n++)
	{
		this->m_CustomFlagInfo[n].Index = -1;
	}
}

void cCustomFlag::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
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

			CUSTOM_FLAG_INFO info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			strcpy_s(info.ModelName,lpMemScript->GetAsString());

			info.ColorR = lpMemScript->GetAsNumber();

			info.ColorG = lpMemScript->GetAsNumber();

			info.ColorB = lpMemScript->GetAsNumber();

			this->SetInfo(info);
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void cCustomFlag::SetInfo(CUSTOM_FLAG_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_FLAG)
	{
		return;
	}

	this->m_CustomFlagInfo[info.Index] = info;
}