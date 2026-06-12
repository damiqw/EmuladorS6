#include "StdAfx.h"
#include "CustomPetEffectDynamic.h"
#include "MemScript.h"

cCEffectDynamicPet gCustomCEffectDynamicPet;

cCEffectDynamicPet::cCEffectDynamicPet()
{
	this->Init();
}
cCEffectDynamicPet::~cCEffectDynamicPet()
{
}


void cCEffectDynamicPet::Init() // OK
{
	for (int n = 0; n < MAX_PET_EFFECT_DYNAMIC; n++)
	{
		this->m_PetDynamicCEffect[n].Index = -1;
	};
}

bool cCEffectDynamicPet::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR, path);
		return 0;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	this->Init();

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if (strcmp("end", lpMemScript->GetString()) == 0)
			{
				break;
			}

			PET_DYNAMIC_CUSTOM info;

			memset(&info, 0, sizeof(info));

			static int CustomItemIndexCount = 0;

			info.Index = CustomItemIndexCount++;

			info.ItemIndex = lpMemScript->GetNumber();

			info.EffectCode = lpMemScript->GetAsNumber();

			info.Join = lpMemScript->GetAsNumber();

			info.TypeEffect = lpMemScript->GetAsNumber();

			info.ColorR = lpMemScript->GetAsFloatNumber();

			info.ColorG = lpMemScript->GetAsFloatNumber();

			info.ColorB = lpMemScript->GetAsFloatNumber();

			info.Effect1 = lpMemScript->GetAsFloatNumber();

			info.EffectSize = lpMemScript->GetAsFloatNumber();

			info.Effect = lpMemScript->GetAsFloatNumber();

			this->SetInfo(info);
		}
	}
	catch (...)
	{
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}

void cCEffectDynamicPet::SetInfo(PET_DYNAMIC_CUSTOM info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_PET_EFFECT_DYNAMIC)
	{
		return;
	}

	this->m_PetDynamicCEffect[info.Index] = info;
}