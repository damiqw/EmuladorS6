#pragma once

#define pAngleMatrix2			((int(__cdecl*)(vec3_t a1, vec34_t a2)) 0x959CE0)
#define pVectorRotate2			((int(__cdecl*)(vec3_t a1, vec34_t a2, vec3_t a3)) 0x95A1E0)
#define pMoveSceneFrame			*(int*)0x00E8CB20
#define pEarthQuake				*(float*)0x08787D48
#define pCreateEffect2			((int(__cdecl*)(int a4, vec3_t Bone1, float* a6, vec3_t color, int a8, int a9, __int16 a10, __int16 a11, __int16 a12, __int16 a13, float a14, __int16 a1)) 0x006D9070)

struct HORSE_EARTH_QUAKE{
	int Index;
	int ItemIndex;
	int EffectCode;
	int UseRGB;
	int ColorR;
	int ColorG;
	int ColorB;
	int EffectSize;
	int SkillEarthQuake1;
	int SkillEarthQuake2;
};

class cCEarthQuake
{
public:
	cCEarthQuake();
	virtual ~cCEarthQuake();
	void Load(HORSE_EARTH_QUAKE* info);
	void LoadRenderSkill();
public:
	std::vector<HORSE_EARTH_QUAKE> m_EarthQuake;
}; extern cCEarthQuake gCustomEarthQuake;