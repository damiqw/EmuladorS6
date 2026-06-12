#pragma once

#define MAX_TYPE_RUNEEFFECT 6

struct RuneEffectType
{
	int Index;
	int Type;
	int	TextureIndex;
	float Speed;
	int Size;
	float ColorR;
	float ColorG;
	float ColorB;
	float FloorDistance;
};

class RuneEffect
{
public:
	RuneEffect();
	~RuneEffect();
	void Init();
	bool Load(char* path);
	void SetInfo(RuneEffectType info);
public:
	RuneEffectType m_RuneEffect[MAX_TYPE_RUNEEFFECT];
};
extern RuneEffect gRuneEffect;