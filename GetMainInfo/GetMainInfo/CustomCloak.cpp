#include "stdafx.h"
#include "CustomCloak.h"
#include "MemScript.h"

cCustomCloak gCloak;

cCustomCloak::cCustomCloak() // OK
{
	this->Init();
}

cCustomCloak::~cCustomCloak() // OK
{

}

void cCustomCloak::Init() // OK
{
	for(int n=0;n < MAX_CUSTOMCLOAK;n++)
	{
		this->m_Cloak[n].Index = -1;
		
		this->m_Cloak[n].IndexCloak = -1;

		this->m_Cloak[n].IndexStrip = -1;
	}
}

bool cCustomCloak::Load(char* path) // OK
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

			CUSTOMCLOAK_DATA info;

			memset(&info,0,sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Mode = lpMemScript->GetAsNumber();

			info.IndexCloak = 129500 + CustomItemIndexCount;

			strcpy_s(info.CloakName,lpMemScript->GetAsString());

			info.IndexStrip = 129600 + CustomItemIndexCount;

			strcpy_s(info.StripName,lpMemScript->GetAsString());

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

void cCustomCloak::SetInfo(CUSTOMCLOAK_DATA info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOMCLOAK)
	{
		return;
	}

	this->m_Cloak[info.Index] = info;
}
