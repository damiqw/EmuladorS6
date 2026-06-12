#include "stdafx.h"
#include "Util.h"
#include "ItemManager.h"
#include "Message.h"
#include "User.h"
#include "Path.h"
#include "MemScript.h"
#include "CustomGuard.h"

CCustomGuard gCustomGuard;

CCustomGuard::CCustomGuard()
{
	//FIX PYKE
	this->m_count = 0;
	memset(m_CustomGuard, -1, sizeof(m_CustomGuard));
}

CCustomGuard::~CCustomGuard()
{

}

void CCustomGuard::Load(char* path) {

	CMemScript* lpMemScript = new CMemScript;

	if (lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR, path);
		return;
	}

	if (lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_count = 0;

	for (int n = 0; n < MAX_GUARD; n++)
	{
		this->m_CustomGuard[n];
	}

	try
	{
		while (true)
		{
			if (lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while (true)
			{
				if (section == 0)
				{
					if (strcmp("end", lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_CustomGuard[this->m_count].m_MonsterClass = lpMemScript->GetNumber();

					this->m_count++;
				}
				else
				{
					break;
				}
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

CUSTOM_GUARD* CCustomGuard::GetGuard(int MonsterClass) 
{
	for (int n = 0; n < MAX_GUARD; n++)
	{
		if (this->m_CustomGuard[n].m_MonsterClass == MonsterClass)
		{
			return &this->m_CustomGuard[n];
		}
	}
	return 0;
}