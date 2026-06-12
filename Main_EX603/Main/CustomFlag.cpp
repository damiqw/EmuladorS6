#include "stdafx.h"
#include "CustomFlag.h"

CCustomFlag gCustomFlag;

CCustomFlag::CCustomFlag() // OK
{
	this->Init();
}

CCustomFlag::~CCustomFlag() // OK
{

}

void CCustomFlag::Init() // OK
{
	for(int n=0;n < MAX_CUSTOM_FLAG;n++)
	{
		this->m_CustomFlagInfo[n].Index = -1;
	}
}

void CCustomFlag::Load(CUSTOM_FLAG_INFO* info) // OK
{
	for(int n=0;n < MAX_CUSTOM_FLAG;n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomFlag::SetInfo(CUSTOM_FLAG_INFO info) // OK
{
	if(info.Index < 0 || info.Index >= MAX_CUSTOM_FLAG)
	{
		return;
	}

	this->m_CustomFlagInfo[info.Index] = info;
}

CUSTOM_FLAG_INFO* CCustomFlag::GetInfo(int index) // OK
{
	if(index < 0 || index >= MAX_CUSTOM_FLAG)
	{
		return 0;
	}

	if(this->m_CustomFlagInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomFlagInfo[index];
}

CUSTOM_FLAG_INFO* CCustomFlag::GetInfoByItem(int ItemIndex) // OK
{
	for(int n=0;n < MAX_CUSTOM_FLAG;n++)
	{
		CUSTOM_FLAG_INFO* lpInfo = this->GetInfo(n);

		if(lpInfo == 0)
		{
			continue;
		}

		if(lpInfo->ItemIndex == ItemIndex)
		{
			return lpInfo;
		}
	}

	return 0;
}
