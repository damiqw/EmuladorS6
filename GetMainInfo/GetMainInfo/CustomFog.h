// CustomFog.h: interface for the CCustomFog class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

struct CUSTOM_FOG_INFO
{
	int Index;
	int MapIndex;
	int FogStart;
	int FogEnd;
	BYTE ColorR;
	BYTE ColorG;
	BYTE ColorB;
};

class CCustomFog
{
public:
	bool Load(char* path);
	void SetInfo(CUSTOM_FOG_INFO info);
	CUSTOM_FOG_INFO m_CustomFogInfo[MAX_FOG];
};

extern CCustomFog gCustomFog;