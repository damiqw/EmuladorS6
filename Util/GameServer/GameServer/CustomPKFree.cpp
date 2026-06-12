#include "stdafx.h"
#include "MemScript.h"
#include "Util.h"
#include "CustomPKFree.h"

CPKZone gPKZone;

CPKZone::CPKZone()
{
}

CPKZone::~CPKZone()
{
}

void CPKZone::Load(char* path)
{
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

	this->m_PkZoneInfo.clear();

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

			PK_ZONE_INFO info;

			info.map = lpMemScript->GetNumber();

			info.startX = lpMemScript->GetAsNumber();

			info.startY = lpMemScript->GetAsNumber();

			info.endX = lpMemScript->GetAsNumber();

			info.endY = lpMemScript->GetAsNumber();

			info.type = lpMemScript->GetAsNumber();

			this->m_PkZoneInfo.push_back(info);
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

bool CPKZone::CheckAttackZone(LPOBJ lpObj, LPOBJ lpTarget)
{
	for(std::vector<PK_ZONE_INFO>::iterator it=this->m_PkZoneInfo.begin();it != this->m_PkZoneInfo.end();it++) 
	{
		if (lpObj->Map != it->map) {
			continue;
		}

		if (lpObj->X >= it->startX && lpObj->Y >= it->startY
			&& lpObj->X <= it->endX && lpObj->Y <= it->endY
			&& lpTarget->X >= it->startX && lpTarget->Y >= it->startY
			&& lpTarget->X <= it->endX && lpTarget->Y <= it->endY) {
			if (it->type == 1) {
				return false;
			}
		}
	}

	return true;
}

bool CPKZone::CheckZoneMurderLevel(LPOBJ lpObj, LPOBJ lpTarget)
{
	for(std::vector<PK_ZONE_INFO>::iterator it=this->m_PkZoneInfo.begin();it != this->m_PkZoneInfo.end();it++) 
	{
		if (lpObj->Map != it->map) {
			continue;
		}

		if (lpObj->X >= it->startX && lpObj->Y >= it->startY
			&& lpObj->X <= it->endX && lpObj->Y <= it->endY
			&& lpTarget->X >= it->startX && lpTarget->Y >= it->startY
			&& lpTarget->X <= it->endX && lpTarget->Y <= it->endY) {
			if (it->type == 2) {
				return false;
			}
		}
	}

	return true;
}

