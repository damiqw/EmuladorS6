#include "stdafx.h"
#include "SmokeEffect.h"
#include "MemScript.h"

cSmokeEffect gSmokeEffect;

cSmokeEffect::cSmokeEffect()
{
	this->Init();
}

cSmokeEffect::~cSmokeEffect()
{
	
}

void cSmokeEffect::Init()
{
	for (int i=0; i<MAX_SMOKE_ITEMS; i++)
	{
		this->m_CustomSmokeEffect[i].Index = -1;
	}
}

bool cSmokeEffect::Load(char* path)
{
	CMemScript* lpMemScript = new CMemScript;

	int Index = 0;

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

			CUSTOM_SMOKEEFFECT info;

			info.Index = Index;

			info.ItemIndex = lpMemScript->GetNumber();

			info.Red = lpMemScript->GetAsFloatNumber();

			info.Green = lpMemScript->GetAsFloatNumber();

			info.Blue = lpMemScript->GetAsFloatNumber();

			Index++;

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

void cSmokeEffect::SetInfo(CUSTOM_SMOKEEFFECT info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_SMOKE_ITEMS)
	{
		return;
	}
	this->m_CustomSmokeEffect[info.Index] = info;
}
