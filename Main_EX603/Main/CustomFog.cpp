#include "stdafx.h"
#include "Common.h"
#include "CustomFog.h"
#include "Offset.h"
#include "Util.h"

CCustomFog gCustomFog;

CCustomFog::CCustomFog() // OK
{
	this->Init();
}

CCustomFog::~CCustomFog() // OK
{

}

void CCustomFog::Init() // OK
{
	for (int n = 0; n < MAX_FOG; n++)
	{
		this->m_CustomFogInfo[n].Index = -1;
	}
}

void CCustomFog::Load(CUSTOM_FOG_INFO* info) // OK
{
	for (int n = 0; n < MAX_FOG; n++)
	{
		this->SetInfo(info[n]);
	}
}

void CCustomFog::SetInfo(CUSTOM_FOG_INFO info) // OK
{
	if (info.Index < 0 || info.Index >= MAX_FOG)
	{
		return;
	}

	this->m_CustomFogInfo[info.Index] = info;
}

CUSTOM_FOG_INFO* CCustomFog::GetInfo(int index) // OK
{
	if (index < 0 || index >= MAX_FOG)
	{
		return 0;
	}

	if (this->m_CustomFogInfo[index].Index != index)
	{
		return 0;
	}

	return &this->m_CustomFogInfo[index];
}

CUSTOM_FOG_INFO* CCustomFog::GetInfoByNumber(int MapNumber) // OK
{
	for (int n = 0; n < MAX_FOG; n++)
	{
		CUSTOM_FOG_INFO* lpInfo = this->GetInfo(n);

		if (lpInfo == 0)
		{
			continue;
		}

		if (lpInfo->MapIndex == MapNumber)
		{
			return lpInfo;
		}
	}

	return 0;
}

void InitFog() // OK
{
	SetDword(0x00D22578, (DWORD)&glEnableFog);
}

void APIENTRY glEnableFog(GLenum cap) // OK
{
	CUSTOM_FOG_INFO* lpInfo = gCustomFog.GetInfoByNumber(*(DWORD*)MAIN_CURRENT_MAP);

	if (Anisotropy != 0)
	{
		glGetIntegerv(0x84FF, &MaxAnisotropy);
		glTexParameteri(GL_TEXTURE_2D, 0x84FE, MaxAnisotropy - 0.1);
	}
	if (Linear != 0)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if (lpInfo != 0)
	{
		GLfloat rgba[4] = { (float)(lpInfo->ColorR / 255.0f),(float)(lpInfo->ColorG / 255.0f),(float)(lpInfo->ColorB / 255.0f),1.0f };
		GLfloat fstart = (float)lpInfo->FogStart;
		GLfloat fend = (float)lpInfo->FogEnd;

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (*(DWORD*)(MAIN_SCREEN_STATE) == 5 && cap != GL_BLEND && cap != GL_TEXTURE_2D && cap != GL_DEPTH_TEST)
		{
			glEnable(GL_FOG);
			glFogi(GL_FOG_MODE, GL_LINEAR);
			glHint(GL_FOG_HINT, GL_NICEST);
			glFogf(GL_FOG_START, fstart);
			glFogf(GL_FOG_END, fend);
			glFogfv(GL_FOG_COLOR, rgba);
			glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
			glShadeModel(GL_SMOOTH);
		}
		else
		{
			glDisable(GL_FOG);
		}
	}

	return glEnable(cap);
}