#include "stdafx.h"
#include "CustomPet.h"
#include "Defines.h"
#include "Import.h"
#include "Object.h"

CCustomPet g_CustomPet;

CCustomPet::CCustomPet() // OK
{
	this->Init();
}

CCustomPet::~CCustomPet() // OK
{

}

void CCustomPet::Init() // OK
{
	this->m_CustomPetInfo.clear();
}

void CCustomPet::Load(CUSTOM_PET_INFO* info) // OK
{
	for (int n = 0; n < MAX_PET_ITEM; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_PET_ITEM)
		{
			return;
		}
		this->m_CustomPetInfo.insert(std::pair<int, CUSTOM_PET_INFO>(info[n].ItemIndex,info[n]));
	}
}

int CCustomPet::GetInfoByItem(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		if(it->second.PetType == 6)
		{
			return it->second.ItemIndex + 1171;
		}
	}
	return -1;
}

int CCustomPet::GetInfoByItemInventory(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.IndexInventory + 1171;
	}
	return -1;
}

int CCustomPet::GetPetType(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.PetType;
	}
	return -1;
}

int CCustomPet::GetInfoPetType(int ItemIndex) // OK
{
	lpViewObj MuunMount = &*(ObjectPreview*)(oUserPreviewStruct);

	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.PetType;
	}
	return -1;
}

int CCustomPet::GetInfoPetEffect(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.FenrrirEffect;
	}
	return 0;
}

float CCustomPet::GetScaleInv(int ItemIndex)
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.Scale_Inve;
	}
	return -1;
}

float CCustomPet::GetScaleDrop(int ItemIndex)
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.Scale_Drop;
	}
	return -1;
}

float CCustomPet::GetScaleView(int ItemIndex)
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return it->second.Scale_View;
	}
	return -1;
}

bool CCustomPet::CheckCustomPetByItem(int ItemIndex) // OK
{
	std::map<int, CUSTOM_PET_INFO>::iterator it = this->m_CustomPetInfo.find(ItemIndex);

	if(it != this->m_CustomPetInfo.end())
	{
		return true;
	}
	return false;
}