#include "StdAfx.h"
#include "CustomPetEffectDynamic.h"

cCEffectDynamicPet gCustomCEffectDynamicPet;

cCEffectDynamicPet::cCEffectDynamicPet()
{
	this->m_PetDynamicCEffect.clear();
}

cCEffectDynamicPet::~cCEffectDynamicPet()
{

}

void cCEffectDynamicPet::Load(PET_DYNAMIC_CUSTOM * info)
{
	for (int n = 0; n < MAX_PET_EFFECT_DYNAMIC; n++)
	{
		if (info[n].Index < 0 || info[n].Index >= MAX_PET_EFFECT_DYNAMIC)
		{
			return;
		}
		this->m_PetDynamicCEffect.push_back(info[n]);
	}
}