#include "stdafx.h"
#include "CUiDIV.h"
#include "Util.h"
#include "Import.h"

//---------------------------------------------------------------------------------------------
cUiDIV gcUiDIV;
cUiDIV::cUiDIV() {}
cUiDIV::~cUiDIV() {}
//---------------------------------------------------------------------------------------------

float XMainDIV, YMainDIV, SizeMainDIV, vHeightDIVOrbs;
bool DIV_SkillMod = false, SkillList = false, m_bButtonBlink, PotionBar = true, PotionBarPress = false;

bool GameResolutionW()
{
	return *(int*)0x0E8C240 == 4 || *(int*)0x0E8C240 == 8 || *(int*)0x0E8C240 == 7 || *(int*)0x0E8C240 == 6 || *(int*)0x0E8C240 == 5;
}

float numW()
{
	return (GameResolutionW() ? 845.f : 640.f);
}

int ConvertXW(float num)
{
	return (int)(num = num / g_fScreenRate_x * ((float)WindowWidth / numW()));
}

void RenderBitmapW(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha)
{
	((void(__cdecl*)(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha))0x00637C60)(Texture, (float)ConvertXW(x), y, (float)ConvertXW(Width), Height, u, v, uWidth, vHeight, Scale, StartScale, Alpha);//RenderBitmap
}

bool CheckMouseW(int x, int y, int width, int height)
{
	return ((bool(__cdecl*)(int x, int y, int width, int height))0x00790B10)(ConvertXW((float)x), y, ConvertXW((float)width), height);//CheckMouseIn
}

void RenderCircleW(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha)
{
	//Cortesía de ChatGPT (?
	if (StartScale)
	{
		x = x * (float)WindowWidth / /*640.f*/numW();
		y = y * (float)WindowHeight / 480.f;
	}
	if (Scale)
	{
		Width = Width * (float)WindowWidth / /*640.f*/numW();
		Height = Height * (float)WindowHeight / 480.f;
	}

	BindTexture(Texture);

	const int segments = 36; // Número de segmentos para aproximar el círculo
	const float angleStep = 2.0f * 3.14159f / segments;

	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= segments; ++i)
	{
		float angle = i * angleStep;
		float px = x + Width * 0.5f * cos(angle);
		float py = y + Height * 0.5f * sin(angle);

		float texCoordU = u + uWidth * (cos(angle) + 1.0f) * 0.5f;
		float texCoordV = v + vHeight * (1.0f - (sin(angle) + 1.0f) * 0.5f); // Ajuste de la coordenada de textura en Y

		if (Alpha > 0.f)
		{
			glColor4f(1.f, 1.f, 1.f, Alpha);
		}
		glTexCoord2f(texCoordU, texCoordV);
		glVertex2f(px, py);
		if (Alpha > 0.f)
		{
			glColor4f(1.f, 1.f, 1.f, 1.f);
		}
	}
	glEnd();
}

float DIVRenderNumber(float x, float y, int iNum, float fScale)
{
	EnableAlphaTest(true);
	float width, height;

	if (fScale < 0.3f)
	{
		return x;
	}

	width = 12.f * (fScale - 0.2f);
	height = 16.f * (fScale - 0.3f);

	char strText[32];
	itoa(iNum, strText, 10);

	int iLength = (int)strlen(strText);

	x -= width * iLength / 3;

	for (int i = 0; i < iLength; ++i)
	{
		float fU = (float)(strText[i] - 48) * 12.f / 128.f;
		RenderBitmapW(DIV_RenderNumber, x, y, width, height, fU, 0.f, 12.f / 128.f, 14.f / 16.f, true, true, 0.f);
		x += width * 0.6f;
	}
	return x;
}

void cUiDIV::CLoadBitmap(char* Folder, int Code, int Arg3, int Arg4, int Arg5, int Arg6)
{
	pLoadImage(Folder, Code, Arg3, Arg4, Arg5, Arg6);//return

	pLoadImage("Interface\\DIV\\DIV_MainUI.tga", DIV_MainUI, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainOrbLife.tga", DIV_MainOrbLife, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainOrbMana.tga", DIV_MainOrbMana, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainOrbPoison.tga", DIV_MainOrbPoison, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainOrbLine.jpg", DIV_MainOrbLine, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainBarAG.tga", DIV_MainBarAG, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_MainBarSD.tga", DIV_MainBarSD, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_RenderNumber.tga", DIV_RenderNumber, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_BackExpBar.tga", DIV_BackExpBar, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_Notification.tga", DIV_Notification, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_BarPotion.tga", DIV_BarPotion, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_Skill01.jpg", DIV_SKILL1, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_Skill02.jpg", DIV_SKILL2, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_SkillCommand.jpg", DIV_COMMAND, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_Skill03.jpg", DIV_SKILL3, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_SkillBox.tga", DIV_SkillBox, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_HotKeySkillListUp.tga", DIV_HotKeySkillListUp, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_non_Skill01.jpg", DIV_NON_SKILL1, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_non_Skill02.jpg", DIV_NON_SKILL2, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_non_SkillCommand.jpg", DIV_NON_COMMAND, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_non_Skill03.jpg", DIV_NON_SKILL3, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_SkillMaster.jpg", DIV_MASTER_SKILL, GL_NEAREST, GL_REPEAT, true, false);
	pLoadImage("Interface\\DIV\\DIV_non_SkillMaster.jpg", DIV_NON_MASTER_SKILL, GL_NEAREST, GL_REPEAT, true, false);
}

void cUiDIV::RenderFrameWindow(GLuint uiImageType, float x, float y, float width, float height)
{
	glAlphaFunc(GL_GREATER, 0.0f);
	XMainDIV = /*117.f*/(numW() - 408.f) / 2.f;
	YMainDIV = 396.f;

	if(PotionBar == true)
	{
		RenderBitmapW(DIV_BarPotion, XMainDIV - 78.f, YMainDIV + 44.f, 104.f, 30, 0.f, 0.f, 1.f, 0.5f, true, true, 0.f);
	}

	RenderBitmapW(DIV_MainUI, XMainDIV, YMainDIV, 204.f, 82.f, 0.f, 0.f, 0.986f, 0.5f, true, true, 0.f);
	RenderBitmapW(DIV_MainUI, XMainDIV + (GameResolutionW() ? 203.f : 204.f), YMainDIV, 204.f, 82.f, 0.014f, 0.494f, 0.986f, 0.5f, true, true, 0.f);

	if(CheckMouseW((int)(XMainDIV - 2.f), (int)(YMainDIV + 44.f), 28, 30))
	{
		if (IsPress(1))
		{
			if (PotionBarPress)
			{
				PotionBar = !PotionBar;
				PotionBarPress = false;	
			}
			else
			{
				PotionBarPress = true;
			}
			PlayBuffer(25, 0, 0);
		}
		RenderBitmapW(DIV_BarPotion, XMainDIV - 78.f, YMainDIV + 44.f, 104.f, 30, 0.f, 0.5f, 1.f, 0.5f, true, true, 0.f);
	}

	if (GetTimeCheck(CTimeCheck_GetSingleton(), 5, 500))
		m_bButtonBlink = !m_bButtonBlink;

	if (!IsQuestIndexByEtcListEmpty(&*(int*)0xEBCF60))
	{
		if (!IsVisible(GetInstance(), 69)//INTERFACE_QUEST_PROGRESS_ETC
			|| !IsVisible(GetInstance(), 16))//INTERFACE_CHARACTER
			if (m_bButtonBlink)
				RenderBitmapW(DIV_Notification, XMainDIV + 317.f, YMainDIV + 11.f, 17.f, 17.f, 0.5f, 0.f, 0.5f, 1.f, true, true, 0.f);	
		{
			if (CheckMouseW((int)(XMainDIV + 317.f), (int)(YMainDIV + 11.f), 17, 17) && IsPress(1))
			{
				Show(GetInstance(), 16);
				Show(GetInstance(), 4);		
			}
		}
	}
	if(CheckNoReadLetter(GetLetterList()))
	{
		if (CheckMouseW((int)(XMainDIV + 332.f), (int)(YMainDIV + 5.f), 17, 17) && IsPress(1))
		{
			keybd_event('F', 0, KEYEVENTF_EXTENDEDKEY, 0);
		}
		if (m_bButtonBlink)
			RenderBitmapW(DIV_Notification, XMainDIV + 332.f, YMainDIV - 5.f, 17.f, 17.f, 0.f, 0.f, 0.5f, 1.f, true, true, 0.f);
	}

	DIV_SkillMod = true;
	int CNewUISkillList = GetUI_NewSkillList(GetInstance());
	RenderSkillIcon(CNewUISkillList, *(BYTE*)(*(int*)0x7BC4F04 + 50), XMainDIV + 266.5f, YMainDIV + 39.5f, 20.f, 28.f);
	if (*(BYTE*)(*(int*)0x8128AC8 + 118) > 0)//bySkillNumber
	{
		RenderBitmapW(DIV_SkillBox, (XMainDIV + 266.5f) - 1.5f, (YMainDIV + 39.5f) - 1.5f, 26.f, 26.f, 0.25f, 0.f, 0.25f, 1.f, true, true, 0.f);
		RenderBitmapW(DIV_HotKeySkillListUp, XMainDIV + 122.f, YMainDIV + 68.f, 134.f, 14.f, 0.f, 0.f, 1.f, 0.33f, true, true, 0.f);
		RenderBitmapW(DIV_HotKeySkillListUp, XMainDIV + 122.f, YMainDIV + 68.f, 134.f, 14.f, 0.f, (*(BYTE*)(CNewUISkillList + 20) ? 0.66f : 0.33f), 1.f, 0.33f, true, true, 0.f);

		int iStartSkillIndex = 1;
		if (*(BYTE*)(CNewUISkillList + 20))//m_bHotKeySkillListUp
		{
			iStartSkillIndex = 6;
			SkillList = true;
		}

		//for (int i = 0; i < (*(BYTE*)(CNewUISkillList + 20) ? 4 : 5); ++i)
		for (int i = 0; i < 5; ++i)
		{
			int iIndex = iStartSkillIndex + i;
			if (iIndex == 10)
				iIndex = 0;

			if (*((DWORD*)CNewUISkillList + iIndex + 6) == -1)
			{
				continue;
			}

			RenderSkillIcon(CNewUISkillList, *((DWORD*)CNewUISkillList + iIndex + 6), /*XMainDIV + 120.f*/29.5f * i + (XMainDIV + 119.f), YMainDIV + 40.f, 20.f, 28.f);
			
			float CurrentSkill_u = (*((BYTE*)Hero + 50) == *((DWORD*)CNewUISkillList + iIndex + 6) ? 0.5f : 0.f);
			RenderBitmapW(DIV_SkillBox, (29.5f * i + (XMainDIV + 119.f)) - 1.5f, (YMainDIV + 40.f) - 1.5f, 26.f, 26.f, CurrentSkill_u, 0.f, 0.25f, 1.f, true, true, 0.f);
		}
	}
	DIV_SkillMod = false;
}

void cUiDIV::LifeManaOrbs(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha)
{
	glColor4f(1.f, 1.f, 1.f, 1.f);
	int Cal = (int)(timeGetTime() * 0.75f) % 3150 / 50;
	float CoordU = (float)(Cal % 8) * 0.125f;
	float CoordV = (float)(Cal / 8) * 0.125f;

	float HeightDIVOrbs = /*64.f*/Height * 1.6f;
	if (Texture == IMAGE_GAUGE_GREEN || Texture == IMAGE_GAUGE_RED)
	{
		RenderBitmapW((Texture == IMAGE_GAUGE_RED ? DIV_MainOrbLife : DIV_MainOrbPoison), XMainDIV + 8.25f, YMainDIV + 72.5f, 64.f, -HeightDIVOrbs, CoordU, CoordV, 0.125f, -HeightDIVOrbs / 512.f, true, true, 0.f);
		vHeightDIVOrbs = HeightDIVOrbs / 62.5f;
		if (vHeightDIVOrbs >= 0.03f && vHeightDIVOrbs <= 0.98f)
		{
			EnableAlphaBlend();
			RenderCircleW(DIV_MainOrbLine, XMainDIV + 40.f, YMainDIV +/*157.f*/ -353.f, 64.f, 64.f, (Texture == IMAGE_GAUGE_RED ? 0.f : 0.5f), vHeightDIVOrbs, 0.25f, 1.f, true, true, 0.f);
			EnableAlphaTest(true);
		}
	}
	else if (Texture == IMAGE_GAUGE_BLUE)//Mana
	{
		RenderBitmapW(DIV_MainOrbMana, XMainDIV + 336.f, YMainDIV + 72.5f, 64.f, -HeightDIVOrbs, CoordU, CoordV, 0.125f, -HeightDIVOrbs / 512.f, true, true, 0.f);
		vHeightDIVOrbs = HeightDIVOrbs / 62.5f;
		if (vHeightDIVOrbs >= 0.03f && vHeightDIVOrbs <= 0.98f)
		{
			EnableAlphaBlend();
			RenderCircleW(DIV_MainOrbLine, XMainDIV + 368.f, YMainDIV +/*157.f*/ -353.f, 64.f, 64.f, 0.25f, vHeightDIVOrbs, 0.25f, 1.f, true, true, 0.f);
			EnableAlphaTest(true);
		}
	}
	HeightDIVOrbs = /*55.f*/Height * 1.4f;
	if (Texture == IMAGE_GAUGE_AG)//AG
	{
		RenderBitmapW(DIV_MainBarAG, XMainDIV + 349.f, YMainDIV + 65.f, -HeightDIVOrbs, 7.f, -CoordU, -CoordV, -HeightDIVOrbs / 440.f, 0.125f, true, true, 0.f);
	}
	else if (Texture == IMAGE_GAUGE_SD)//SD
	{
		RenderBitmapW(DIV_MainBarSD, XMainDIV + 60.f, YMainDIV + 65.f, HeightDIVOrbs, 7.f, CoordU, CoordV, HeightDIVOrbs / 440.f, 0.125f, true, true, 0.f);
	}
	float WidthExp = /*171.f*/Width * 0.27f;
	if (Texture == IMAGE_GAUGE_EXBAR || Texture == IMAGE_MASTER_GAUGE_BAR)//Experience
	{
		RenderBitmapW(Texture, XMainDIV + 120.f, YMainDIV + 27.f, WidthExp, 3.f, 0.f, 0.f, WidthExp / 228.f, 1.f, true, true, 0.f);
	}

	glAlphaFunc(GL_GREATER, 0.25f);
}

void cUiDIV::RenderIconSkill(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha)
{
	if (DIV_SkillMod == true)
	{
		SetDword(0x00814BF6 + 3, DIV_COMMAND);
		SetDword(0x00814C06 + 3, DIV_NON_COMMAND);
		SetDword(0x00814C0F + 3, DIV_SKILL1);
		SetDword(0x00814C1F + 3, DIV_NON_SKILL1);
		SetDword(0x00814C28 + 3, DIV_SKILL2);
		SetDword(0x00814C38 + 3, DIV_NON_SKILL2);
		SetDword(0x00814C41 + 3, DIV_SKILL3);
		SetDword(0x00814C51 + 3, DIV_NON_SKILL3);
		SetDword(0x00814C5A + 3, DIV_MASTER_SKILL);
		SetDword(0x00814C6A + 3, DIV_NON_MASTER_SKILL);

		RenderBitmapW(Texture, x, y, 23.f, 23.f, u, v, uWidth, vHeight, Scale, StartScale, Alpha);
	}
	else
	{
		SetDword(0x00814BF6 + 3, IMAGE_COMMAND);
		SetDword(0x00814C06 + 3, IMAGE_NON_COMMAND);
		SetDword(0x00814C0F + 3, IMAGE_SKILL1);
		SetDword(0x00814C1F + 3, IMAGE_NON_SKILL1);
		SetDword(0x00814C28 + 3, IMAGE_SKILL2);
		SetDword(0x00814C38 + 3, IMAGE_NON_SKILL2);
		SetDword(0x00814C41 + 3, IMAGE_SKILL3);
		SetDword(0x00814C51 + 3, IMAGE_NON_SKILL3);
		SetDword(0x00814C5A + 3, IMAGE_MASTER_SKILL);
		SetDword(0x00814C6A + 3, IMAGE_NON_MASTER_SKILL);

		((void(__cdecl*)(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha))0x00637C60)(Texture, x, y, Width, Height, u, v, uWidth, vHeight, Scale, StartScale, Alpha);//RenderBitmap
	}
}

void cUiDIV::CurrentSkill_CheckMouse(int x, int y, int width, int height)
{
	CheckMouseW((int)XMainDIV + 267, (int)YMainDIV + 40, 23, 23);
}

void cUiDIV::SkillBar_CheckMouse(int x, int y, int width, int height)
{
	CheckMouseW((int)(x - 222.f + (29.5f * 0 + (XMainDIV + 119.f))), (int)(YMainDIV + 40.f), width, height);
}

void cUiDIV::Exp_CheckMouse(int x, int y, int width, int height)
{
	CheckMouseW((int)(XMainDIV + 120.f), (int)(YMainDIV + 27.f), 171, 3);
}

void cUiDIV::Skill_RenderNumber(float x, float y, int iNum, float fScale)
{
	((void(__cdecl*)(float x, float y, int iNum, float fScale))0x00791000)(x, y, iNum, (DIV_SkillMod == false ? fScale : 0.f));//RenderNumber
}

void cUiDIV::Exp_RenderNumber(float x, float y, int iNum, float fScale)
{
	RenderBitmapW(DIV_BackExpBar, XMainDIV + (GameResolutionW() ? 117.f : 117.5f), YMainDIV + 26.f, (GameResolutionW() ? 174.5f : 175.f), 6.f, 0.f, 0.f, 1.f, 1.f, true, true, 0.f);
	DIVRenderNumber(XMainDIV + 113.5f, YMainDIV + 22.f, iNum, 0.75f);
}

void cUiDIV::Life_RenderNumber(float x, float y, int iNum, float fScale)
{
	DIVRenderNumber(XMainDIV + 40.5f, YMainDIV + 38.f, iNum, 0.75f);
}

void cUiDIV::Mana_RenderNumber(float x, float y, int iNum, float fScale)
{
	DIVRenderNumber(XMainDIV + 368.5f, YMainDIV + 38.f, iNum, 0.75f);
}

void cUiDIV::AG_RenderNumber(float x, float y, int iNum, float fScale)
{
	DIVRenderNumber(XMainDIV + 323.f, YMainDIV + 65.f, iNum, 0.75f);
}

void cUiDIV::SD_RenderNumber(float x, float y, int iNum, float fScale)
{
	DIVRenderNumber(XMainDIV + 89.f, YMainDIV + 65.f, iNum, 0.75f);
}

void cUiDIV::Potion_RenderNumber(float x, float y, int iNum/*, float fScale*/)
{
	DIVRenderNumber(/*x*/ x, (PotionBar == true ? y : 640.f), iNum, 0.75f);
}

void cUiDIV::Potion_RenderItem3D(float sx, float sy, float Width, float Height, int Type, int Level, int Option1, int ExtOption, bool PickUp)
{	
	((void(__cdecl*)(float sx, float sy, float Width, float Height, int Type, int Level, int Option1, int ExtOption, bool PickUp))0x005CF310)(sx, (PotionBar == true ? sy : 640.f), Width, Height, Type, Level, Option1, ExtOption, PickUp);
}

void cUiDIV::CHotKeyQStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y)
{
	XMainDIV = /*117.f*/(numW() - 408.f) / 2.f;
	YMainDIV = 396.f;
	//float x = 130.f, y = 10.f;
	float x = -70.f, y = 60.f;
	((void(__thiscall*)(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y))0x008977D0)(This, (float)ConvertXW(XMainDIV + x), YMainDIV + y, XMainDIV + (x + 2.f), YMainDIV + (y + 5.f));
}

void cUiDIV::CHotKeyWStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y)
{	
	//float x = 150.f, y = 10.f;
	float x = -50.f, y = 60.f;
	((void(__thiscall*)(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y))0x00897BD0)(This, (float)ConvertXW(XMainDIV + x), YMainDIV + y, XMainDIV + (x + 3.f), YMainDIV + (y + 5.f));
}

void cUiDIV::CHotKeyEStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y)
{	
	//float x = 170.f, y = 10.f;
	float x = -30.f, y = 60.f;
	((void(__thiscall*)(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y))0x00895760)(This, (float)ConvertXW(XMainDIV + x), YMainDIV + y, XMainDIV + (x + 3.f), YMainDIV + (y + 5.f));
}

void cUiDIV::CHotKeyRStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y)
{	
	//float x = 190.f, y = 10.f;
	float x = -10.f, y = 60.f;
	((void(__thiscall*)(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y))0x008979C0)(This, (float)ConvertXW(XMainDIV + x), YMainDIV + y, XMainDIV + (x + 3.f), YMainDIV + (y + 5.f));
}

void none_RenderBitmap(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha)
{
}

void none_CheckMouse(int x, int y, int width, int height)
{
}

void CBeginOpengl(int x, int y, int Width, int Height)
{
	x = x * WindowWidth / 640;
	y = y * WindowHeight / 480;
	Width = Width * WindowWidth / 640;
	Height = Height * WindowHeight / 480;

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glViewport2(x, y, Width, Height);
	gluPerspective2(CameraFOV + 4.f, (float)Width / (float)Height, CameraViewNear, CameraViewFar * 1.4f);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(CameraAngle[1], 0.f, 1.f, 0.f);
	if (CameraTopViewEnable == false)
		glRotatef(CameraAngle[0] - -2.f, 1.f, 0.f, 0.f);
	glRotatef(CameraAngle[2], 0.f, 0.f, 1.f);
	glTranslatef(-CameraPosition[0], -CameraPosition[1], -CameraPosition[2]);
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthMask(true);
	AlphaTestEnable = false;
	TextureEnable = true;
	DepthTestEnable = true;
	CullFaceEnable = true;
	DepthMaskEnable = true;
	glDepthFunc(GL_LEQUAL);
	glAlphaFunc(GL_GREATER, 0.25f);
	if (FogEnable)
	{
		glEnable(GL_FOG);
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogf(GL_FOG_DENSITY, FogDensity);
		glFogfv(GL_FOG_COLOR, &FogColor);
	}
	else
	{
		glDisable(GL_FOG);
	}
	GetOpenGLMatrix((int)&CameraMatrix);
}

float CNewUIMainFrameWindow_GetLayerDepth()
{
	return (IsVisible(GetInstance(), 33) || IsVisible(GetInstance(), 1) ? 5.9f : 10.6f);//INTERFACE_CHATINPUTBOX || INTERFACE_FRIEND;
}

void cUiDIV::Load()
{
	SetCompleteHook(0xE9, 0x00812120, &CNewUIMainFrameWindow_GetLayerDepth);
	SetCompleteHook(0xE8, 0x0089580C, &cUiDIV::Potion_RenderItem3D);
	SetCompleteHook(0xE8, 0x0089787C, &cUiDIV::Potion_RenderItem3D);
	SetCompleteHook(0xE8, 0x00897A6C, &cUiDIV::Potion_RenderItem3D);
	SetCompleteHook(0xE8, 0x00897C7C, &cUiDIV::Potion_RenderItem3D);

	SetCompleteHook(0xE8, 0x004D98DB, &CBeginOpengl);
	SetDword(0x004D9746 + 3, 480);

	static float size3dpotion = 5.f;
	SetDword(0x00894B53 + 2, (DWORD)&size3dpotion);
	SetDword(0x00894B5F + 2, (DWORD)&size3dpotion);

	SetCompleteHook(0xE9, 0x00895600, &cUiDIV::Potion_RenderNumber);

	SetCompleteHook(0xE8, 0x00895A73, &cUiDIV::CHotKeyQStateItem);
	SetCompleteHook(0xE8, 0x00895AE8, &cUiDIV::CHotKeyWStateItem);
	SetCompleteHook(0xE8, 0x00895B5D, &cUiDIV::CHotKeyEStateItem);
	SetCompleteHook(0xE8, 0x00895BD2, &cUiDIV::CHotKeyRStateItem);

	SetCompleteHook(0xE8, 0x0080FF28, &cUiDIV::Life_RenderNumber);
	SetCompleteHook(0xE8, 0x008100BB, &cUiDIV::Mana_RenderNumber);
	SetCompleteHook(0xE8, 0x00810389, &cUiDIV::AG_RenderNumber);
	SetCompleteHook(0xE8, 0x00810659, &cUiDIV::SD_RenderNumber);

	SetCompleteHook(0xE8, 0x00810F45, &cUiDIV::Exp_RenderNumber);
	SetCompleteHook(0xE8, 0x008117EE, &cUiDIV::Exp_RenderNumber);

	SetCompleteHook(0xE8, 0x00810F97, &cUiDIV::Exp_CheckMouse);//exp
	SetCompleteHook(0xE8, 0x00811840, &cUiDIV::Exp_CheckMouse);//exp

	SetCompleteHook(0xE8, 0x00814E63, &cUiDIV::Skill_RenderNumber);

	SetCompleteHook(0xE8, 0x008129A3, &cUiDIV::SkillBar_CheckMouse);
	SetCompleteHook(0xE8, 0x008129FC, &cUiDIV::SkillBar_CheckMouse);
	SetCompleteHook(0xE8, 0x00812A55, &cUiDIV::SkillBar_CheckMouse);
	SetCompleteHook(0xE8, 0x00812B16, &cUiDIV::SkillBar_CheckMouse);

	static float width = 30.f;//SkillIcon
	static float widthbar = 150.f;//SkillIcon
	SetDword(0x00812A88 + 2, (DWORD)&width);
	SetDword(0x00812959 + 2, (DWORD)&widthbar);

	SetCompleteHook(0xE8, 0x0080F0EF, &cUiDIV::CLoadBitmap);

	SetCompleteHook(0xE8, 0x0080F9A3, &cUiDIV::RenderFrameWindow);

	SetCompleteHook(0xE8, 0x0080FE56, &cUiDIV::LifeManaOrbs);//Poison
	SetCompleteHook(0xE8, 0x0080FEEF, &cUiDIV::LifeManaOrbs);//Life
	SetCompleteHook(0xE8, 0x00810083, &cUiDIV::LifeManaOrbs);//Mana

	SetCompleteHook(0xE8, 0x00810354, &cUiDIV::LifeManaOrbs);//AG
	SetCompleteHook(0xE8, 0x00810624, &cUiDIV::LifeManaOrbs);//SD

	SetCompleteHook(0xE8, 0x008112A6, &cUiDIV::LifeManaOrbs);//Exp
	SetCompleteHook(0xE8, 0x0081147F, &cUiDIV::LifeManaOrbs);//Exp
	SetCompleteHook(0xE8, 0x008115C9, &cUiDIV::LifeManaOrbs);//Exp
	SetCompleteHook(0xE8, 0x00811660, &cUiDIV::LifeManaOrbs);//Exp
	SetCompleteHook(0xE8, 0x00811790, &cUiDIV::LifeManaOrbs);//Exp

	SetCompleteHook(0xE8, 0x00810A1A, &cUiDIV::LifeManaOrbs);//Exp Master
	SetCompleteHook(0xE8, 0x00810BE5, &cUiDIV::LifeManaOrbs);//Exp Master
	SetCompleteHook(0xE8, 0x00810D2C, &cUiDIV::LifeManaOrbs);//Exp Master
	SetCompleteHook(0xE8, 0x00810DC3, &cUiDIV::LifeManaOrbs);//Exp Master
	SetCompleteHook(0xE8, 0x00810EF0, &cUiDIV::LifeManaOrbs);//Exp Master
	
	SetCompleteHook(0xE8, 0x00814D4D, &cUiDIV::RenderIconSkill);
	SetCompleteHook(0xE8, 0x00814DC1, &cUiDIV::RenderIconSkill);	

	SetCompleteHook(0xE8, 0x0081276F, &cUiDIV::CurrentSkill_CheckMouse);
	SetCompleteHook(0xE8, 0x008127C8, &cUiDIV::CurrentSkill_CheckMouse);
	SetCompleteHook(0xE8, 0x0081282D, &cUiDIV::CurrentSkill_CheckMouse);
	SetCompleteHook(0xE8, 0x00812899, &cUiDIV::CurrentSkill_CheckMouse);

	static float ytooltipskill1 = 400.f;
	SetDword(0x0081271C + 2, (DWORD)&ytooltipskill1);
	SetDword(0x00812950 + 2, (DWORD)&ytooltipskill1);
	SetDword(0x00812A7F + 2, (DWORD)&ytooltipskill1);

	static float ytooltipskill2 = 350.f;
	SetDword(0x00812D48 + 2, (DWORD)&ytooltipskill2);
	SetDword(0x008139A9 + 2, (DWORD)&ytooltipskill2);

	//Remove Interface
	MemorySet(0x0080F270, 0x90 ,0x4D1);//Botones
	SetCompleteHook(0xE8, 0x0080F92D, &none_RenderBitmap);//RenderFrame
	SetCompleteHook(0xE8, 0x0080F968, &none_RenderBitmap);
	//SetCompleteHook(0xE8, 0x0080F9A3, &none_RenderBitmap);
	SetCompleteHook(0xE8, 0x0080FA02, &none_RenderBitmap);
	
	SetCompleteHook(0xE8, 0x00811B61, &none_RenderBitmap);

	SetCompleteHook(0xE8, 0x008119E6, &none_RenderBitmap);//newui_menu_Bt01
	SetCompleteHook(0xE8, 0x00811B1A, &none_RenderBitmap);//newui_menu_Bt03
	SetCompleteHook(0xE8, 0x00811B61, &none_RenderBitmap);//newui_menu_Bt03

	static float noney = -600.f;
	SetDword(0x00813782 + 2, (DWORD)&noney);//Skillbar
	SetDword(0x008138E8 + 2, (DWORD)&noney);//Skill
	SetCompleteHook(0xE8, 0x0080FF56, &none_CheckMouse);
	SetCompleteHook(0xE8, 0x008100E9, &none_CheckMouse);
	SetCompleteHook(0xE8, 0x008103B7, &none_CheckMouse);
	SetCompleteHook(0xE8, 0x00810699, &none_CheckMouse);
}