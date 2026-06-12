#include "stdafx.h"
#include "CustomRingSummon.h"
#include "ItemManager.h"
#include "Map.h"
#include "MasterSkillTree.h"
#include "MemScript.h"
#include "Monster.h"
#include "Util.h"

CInvoker gInvoker;

CInvoker::CInvoker() // OK
{

}

CInvoker::~CInvoker() // OK
{

}

void CInvoker::Load(char* path){

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

	for (int n = 0; n < MAX_INVOKER; n++)
	{
		this->m_Invoker[n];
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

					this->m_Invoker[this->m_count].ItemType = lpMemScript->GetNumber();

					this->m_Invoker[this->m_count].ItemIndex = lpMemScript->GetAsNumber();

					this->m_Invoker[this->m_count].MonsterNumb = lpMemScript->GetAsNumber();

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

bool CInvoker::InvokerSummon(int aIndex) // OK
{
	LPOBJ lpObj = &gObj[aIndex];

	if (lpObj->Type != OBJECT_USER)
	{
		return 0;
	}

	int monster = 0;

	for (int n = 0; n < 2; n++)
	{
		CItem* Ring = &lpObj->Inventory[10 + n];

		if (Ring->IsItem() == 0 || Ring->m_Durability == 0)
		{
			continue;
		}

		for (int n = 0; n < MAX_INVOKER; n++)
		{
			if (Ring->m_Index == GET_ITEM(this->m_Invoker[n].ItemType, this->m_Invoker[n].ItemIndex))
			{
				monster = this->m_Invoker[n].MonsterNumb;
			}
		}
	}
	
	// ----

	if (OBJECT_RANGE(lpObj->SummonIndex) != 0)
	{
		gObjSummonKill(aIndex);
		GCSummonLifeSend(aIndex, 0, 1);
		return 0;
	}

	if (monster == 0)
	{
		return 0;
	}

	int index = gObjAddSummon();

	if (OBJECT_RANGE(index) == 0)
	{
		return 0;
	}

	lpObj->SummonIndex = index;

	LPOBJ lpSummon = &gObj[index];

	lpSummon->X = lpObj->X - 1;
	lpSummon->Y = lpObj->Y + 1;
	lpSummon->MTX = lpSummon->X;
	lpSummon->MTY = lpSummon->Y;
	lpSummon->Dir = 2;
	lpSummon->Map = lpObj->Map;

	gObjSetMonster(index, monster);

#if(GAMESERVER_UPDATE>=602)
	lpSummon->Life += (float)((__int64)lpSummon->Life*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_LIFE)) / 100;
	lpSummon->MaxLife += (float)((__int64)lpSummon->MaxLife*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_LIFE)) / 100;
	lpSummon->ScriptMaxLife += (float)((__int64)lpSummon->ScriptMaxLife*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_LIFE)) / 100;
	lpSummon->Defense += ((__int64)lpSummon->Defense*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_DEFENSE)) / 100;
	lpSummon->PhysiDamageMin += ((__int64)lpSummon->PhysiDamageMin*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_DAMAGE)) / 100;
	lpSummon->PhysiDamageMax += ((__int64)lpSummon->PhysiDamageMax*gMasterSkillTree.GetMasterSkillValue(lpObj, MASTER_SKILL_ADD_SUMMON_DAMAGE)) / 100;
#endif
	lpSummon->SummonIndex = lpObj->Index;
	lpSummon->Attribute = 100;
	lpSummon->TargetNumber = -1;
	lpSummon->ActionState.Attack = 0;
	lpSummon->ActionState.Emotion = 0;
	lpSummon->ActionState.EmotionCount = 0;
	lpSummon->PathCount = 0;
	lpSummon->MoveRange = 15;

	GCSummonLifeSend(lpSummon->SummonIndex, (int)lpSummon->Life, (int)lpSummon->MaxLife);
	return 1;
}