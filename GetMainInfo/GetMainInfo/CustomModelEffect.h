// CustomWingEffect.h: interface for the CCustomWingEffect class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct CUSTOM_MODEL_EFFECT_INFO
{
	int		Index;
	int		ItemType;
	int		ItemIndex;
	int		MinLevel;
	int		MaxLevel;
	int		MinExcellent;
	int		MaxExcellent;
	float	Color[3];
	int		EffectIndex;
	int		EffectType;
	int		EffectCode;		
	float	EffectScale;
};

class CCustomModelEffect
{
public:
	CCustomModelEffect();
	virtual ~CCustomModelEffect();
	void Init();
	bool Load(char* path);
	void SetInfo(CUSTOM_MODEL_EFFECT_INFO info);
public:
	CUSTOM_MODEL_EFFECT_INFO m_CustomModelEffectInfo[MAX_MODEL_EFFECT];
};

extern CCustomModelEffect gCustomModelEffect;
