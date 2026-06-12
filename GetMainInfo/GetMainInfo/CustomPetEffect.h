#pragma once

struct PET_EFFECT_CUSTOM
{
	int Index;				//int Index
	int ItemIndex;			//int ItemIndex
	int EffectCode;			//int EffectIndex;
	int Join;				//int EffectValue
	int TypeEffect;			// -descartável
//	int LargeRand;			// -descartável
	float ColorR;			//float ColorR;
	float ColorG;			//float ColorG;
	float ColorB;			//float ColorB;
	float EffectSize;		//float ColorSize;
	float ColorMain;
	float ColorSide;
};

class cCEffectPet
{
public:
	cCEffectPet();
	virtual ~cCEffectPet();
	void Init();
	bool Load(char* path);
	void SetInfo(PET_EFFECT_CUSTOM info);

public:
	PET_EFFECT_CUSTOM m_PetCEffect [MAX_PET_EFFECT_STATIC];

}; extern cCEffectPet gCustomCEffectPet;