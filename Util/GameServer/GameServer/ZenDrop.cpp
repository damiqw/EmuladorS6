#include "stdafx.h"
#include "ZenDrop.h"
#include "Util.h"
#include "MemScript.h"

cZenDrop gZenDrop;

cZenDrop::cZenDrop()
{
	this->m_ZenDrop.clear();
	this->m_ZenDropEnable = 0;
	this->m_MultiplyZenDropByMonLevel = 0;
	this->m_MultiplyZenChanceRate = 0;
}

cZenDrop::~cZenDrop()
{
	
}

void cZenDrop::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_ZenDrop.clear();

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int section = lpMemScript->GetNumber();

			while(true)
			{
				if(section == 0)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}

					this->m_ZenDropEnable = lpMemScript->GetNumber();;

					this->m_MultiplyZenDropByMonLevel = lpMemScript->GetAsNumber();

					this->m_MultiplyZenChanceRate = lpMemScript->GetAsNumber();
				}
				else if(section == 1)
				{
					if(strcmp("end",lpMemScript->GetAsString()) == 0)
					{
						break;
					}
					
					ZEN_DROP ZenDrop;

					ZenDrop.MapNumber = lpMemScript->GetNumber();

					ZenDrop.MinMoney = lpMemScript->GetAsNumber();

					ZenDrop.MaxMoney = lpMemScript->GetAsNumber();

					this->m_ZenDrop.insert(std::pair<int, ZEN_DROP>(ZenDrop.MapNumber, ZenDrop));
				}
				else
				{
					break;
				}
			}
		}
	}
	catch(...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool cZenDrop::IsZenDropActive(BYTE Map)
{
	if (this->m_ZenDropEnable == false)
	{
		return false;
	}

	if (this->m_ZenDrop.find(Map) == this->m_ZenDrop.end())
	{
		return false;
	}

	return true;
}

DWORD cZenDrop::GetZenAmount(BYTE MapNumber, WORD MonsterLevel)
{
	if (this->m_ZenDropEnable == false)
	{
		return 0;
	}

	std::map<int, ZEN_DROP>::iterator It = this->m_ZenDrop.find(MapNumber);

	if (It == this->m_ZenDrop.end())
	{
		return 0;
	}

	DWORD dwMoney = 0;
	DWORD dwSub = It->second.MaxMoney - It->second.MinMoney;

	if (dwSub < 0)
	{
		return 0;
	}

	dwMoney = It->second.MinMoney + rand()%(dwSub+1);

	if (this->m_MultiplyZenDropByMonLevel == true && (rand()%10000) < this->m_MultiplyZenChanceRate)
	{
		dwMoney *= MonsterLevel;
	}

	return dwMoney;
}
