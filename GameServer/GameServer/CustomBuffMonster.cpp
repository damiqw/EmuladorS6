#include "StdAfx.h"
#include "user.h"
#include "MemScript.h"
#include "Util.h"
#include "Monster.h"
#include "Notice.h"
#include "Message.h"
#include "CustomBuffMonster.h"
#include "EffectManager.h"
// -------------------------------------------------------------------------------
CustomBuffMonster gCustomBuffMonster;
// -------------------------------------------------------------------------------

CustomBuffMonster::CustomBuffMonster()
{
	this->Init();
}
// -------------------------------------------------------------------------------

CustomBuffMonster::~CustomBuffMonster()
{
	// ----
}
// -------------------------------------------------------------------------------

void CustomBuffMonster::Init()
{
	this->m_IsLoaded			= false;
	this->m_MonsterLoaded		= 0;
	// ----
	this->m_MobsData.clear();
}
// -------------------------------------------------------------------------------

void CustomBuffMonster::Load(char* path)
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

	this->Init();

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

					CUSTOMBUFF_MONSTER info;

					info.MonsterID = lpMemScript->GetNumber();

					info.MapNumber = lpMemScript->GetAsNumber();

					info.Effect = lpMemScript->GetAsNumber();

					info.Type = lpMemScript->GetAsNumber();

					info.Power[0] = lpMemScript->GetAsNumber();

					info.Power[1] = lpMemScript->GetAsNumber();

					info.Power[2] = lpMemScript->GetAsNumber();

					info.Power[3] = lpMemScript->GetAsNumber();

					info.Duration = lpMemScript->GetAsNumber();

					this->m_MobsData.push_back(info);
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
	this->m_IsLoaded = true;
}
// -------------------------------------------------------------------------------

int CustomBuffMonster::GetMonsterSlot(int Class, int Map)
{
	for( int i = 0; i < this->m_MobsData.size(); i++ )
	{
		if( this->m_MobsData[i].MonsterID != Class )
		{
			continue;
		}
		// ----
		if( this->m_MobsData[i].MapNumber != Map && this->m_MobsData[i].MapNumber != -1 )
		{
			continue;
		}
		// ----
		return i;
	}
	// ----
	return -1;
}

// -------------------------------------------------------------------------------

void CustomBuffMonster::AddMonsterBonus(LPOBJ lpMonster, LPOBJ lpObj)
{
	if( !this->m_IsLoaded )
	{
		return;
	}
	// ----
	int MonsterSlot = this->GetMonsterSlot(gObj[lpMonster->Index].Class, gObj[lpMonster->Index].Map);
	// ----
	if( MonsterSlot == -1 )
	{
		return;
	}

	int aIndex = gObjMonsterGetTopHitDamageUser(lpObj);

	if(OBJECT_RANGE(aIndex) != 0)
	{
		lpObj = &gObj[aIndex];
	}
	// ----

	gEffectManager.AddEffect(lpObj,(this->m_MobsData[MonsterSlot].Type == 0) ? 0 : 1,this->m_MobsData[MonsterSlot].Effect,(this->m_MobsData[MonsterSlot].Type == 0) ? this->m_MobsData[MonsterSlot].Duration : (int)(time(0)+this->m_MobsData[MonsterSlot].Duration),this->m_MobsData[MonsterSlot].Power[0],this->m_MobsData[MonsterSlot].Power[1],this->m_MobsData[MonsterSlot].Power[2],this->m_MobsData[MonsterSlot].Power[3]);
	// ----
	gNotice.GCNoticeSend(lpObj->Index,1,0,0,0,0,0,gMessage.GetMessage(881));
}
// -------------------------------------------------------------------------------