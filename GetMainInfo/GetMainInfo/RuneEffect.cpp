#include "stdafx.h"
#include "RuneEffect.h"
#include "MemScript.h"

RuneEffect gRuneEffect;

RuneEffect::RuneEffect()
{
	this->Init();
}
RuneEffect::~RuneEffect()
{

}

void RuneEffect::Init()
{
	for (int n = 0; n < MAX_TYPE_RUNEEFFECT; n++)
	{
		this->m_RuneEffect[n].Index = -1;
	};
}

bool RuneEffect::Load(char* path)
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
			RuneEffectType info;
			memset(&info, 0, sizeof(info));
			static int CustomItemIndexCount = 0;
			info.Index = CustomItemIndexCount++;
			info.Type = lpMemScript->GetNumber();
			info.TextureIndex = lpMemScript->GetAsNumber();
			info.Speed =lpMemScript->GetAsFloatNumber();
			info.Size = lpMemScript->GetAsNumber();
			info.ColorR = lpMemScript->GetAsFloatNumber();
			info.ColorG = lpMemScript->GetAsFloatNumber();
			info.ColorB = lpMemScript->GetAsFloatNumber();
			info.FloorDistance = lpMemScript->GetAsFloatNumber();
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

void RuneEffect::SetInfo(RuneEffectType info)
{
	if (info.Index < 0 || info.Index >= MAX_TYPE_RUNEEFFECT)
	{
		return;
	}

	this->m_RuneEffect[info.Index] = info;
}