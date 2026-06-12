// CustomPet.cpp: implementation of the CCustomPet class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CustomPet.h"
#include "MemScript.h"
#include "Util.h"
#include "ItemManager.h"

CCustomPet gCustomPet;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCustomPet::CCustomPet() // OK
{
	this->m_CustomPetInfo.clear();
}

CCustomPet::~CCustomPet() // OK
{

}

void CCustomPet::Load(char* path) // OK
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

	this->m_CustomPetInfo.clear();

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

			CUSTOM_PET_INFO info;

			memset(&info, 0, sizeof(info));

			info.Index = lpMemScript->GetNumber();

			info.ItemIndex = lpMemScript->GetAsNumber();

			info.IncLife = lpMemScript->GetAsNumber();

			info.IncMana = lpMemScript->GetAsNumber();

			info.IncDamageRate = lpMemScript->GetAsNumber();

			info.IncAttackSpeed = lpMemScript->GetAsNumber();

			info.IncDoubleDamageRate = lpMemScript->GetAsNumber();

			info.IncTripleDamageRate = lpMemScript->GetAsNumber();
			
			info.IncExperience = lpMemScript->GetAsNumber();
			
			info.IncResistDoubleDamage = lpMemScript->GetAsNumber();
			
			info.IncResistIgnoreDefense = lpMemScript->GetAsNumber();
			
			info.IncResistIgnoreSD = lpMemScript->GetAsNumber();
			
			info.IncResistCriticalDamage = lpMemScript->GetAsNumber();
			
			info.IncResisteExcellentDamage = lpMemScript->GetAsNumber();
			
			info.IncBlockStuck = lpMemScript->GetAsNumber();
			
			info.IncReflectRate = lpMemScript->GetAsNumber();
			
			info.Recovery = lpMemScript->GetAsNumber();

			this->m_CustomPetInfo.insert(std::pair<int,CUSTOM_PET_INFO>(info.ItemIndex, info));
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}



bool CCustomPet::CheckCustomPetByItem(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return 1;
	}

	return 0;
}


bool CCustomPet::PetIsInmortal(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if( it != this->m_CustomPetInfo.end() )
	{
		if( it->second.Recovery != 0 )
		{
			return 1;
		}
	}

	return 0;
}

int CCustomPet::GetCustomPetDamageRate(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.IncDamageRate;
	}

	return 0;
}

void CCustomPet::CalcCustomPetOption(LPOBJ lpObj, bool flag)
{
	if (flag != 0)
	{
		return;
	}

#if(HAISLOTRING)
	CItem* pEquipetNew = &lpObj->EquipInventory[12];

	std::map<int, CUSTOM_PET_INFO>::iterator itb = this->m_CustomPetInfo.find(pEquipetNew->m_Index);

	if (itb != this->m_CustomPetInfo.end())
	{
		if (pEquipetNew->m_Durability > 0)
		{
			lpObj->AddLife += itb->second.IncLife;
			//--
			lpObj->AddMana += itb->second.IncMana;
			//--
			lpObj->PhysiSpeed += itb->second.IncAttackSpeed;
			lpObj->MagicSpeed += itb->second.IncAttackSpeed;
			//--
			lpObj->DoubleDamageRate += itb->second.IncDoubleDamageRate;
			//--
			lpObj->TripleDamageRate += itb->second.IncTripleDamageRate;
			//--
			lpObj->ExperienceRate += itb->second.IncExperience;
			lpObj->MasterExperienceRate += itb->second.IncExperience;
			//--
			lpObj->ResistDoubleDamageRate += itb->second.IncDoubleDamageRate;
			//--
			lpObj->ResistIgnoreDefenseRate += itb->second.IncResistIgnoreDefense;
			//--
			lpObj->ResistIgnoreShieldGaugeRate += itb->second.IncResistIgnoreSD;
			//--
			lpObj->ResistCriticalDamageRate += itb->second.IncResistCriticalDamage;
			//--
			lpObj->ResistExcellentDamageRate += itb->second.IncResisteExcellentDamage;
			//--
			lpObj->ResistStunRate += itb->second.IncBlockStuck;
			//--
			lpObj->DamageReflect += itb->second.IncReflectRate;
		}
	}
#endif
}