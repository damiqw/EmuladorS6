#include "stdafx.h"
#include "Util.h"
#include "PlayerSystem.h"
#include "Protect.h"
#include "User.h"
#include "CustomRankUser.h"
#include "InterfaceElemental.h"

__declspec(naked) void PlayerInfoCheckDelect()
{
	static DWORD Addr_JMP = 0x00842869;
	_asm
	{
		JMP[Addr_JMP]
	}
}

void PlayerLoad()
{
	if (gProtect.m_MainInfo.PlayerShowGuildLogo == 1)
	{
		SetCompleteHook(0xE8, 0x005BAFAB, &PlayerGuildLogo);

		SetCompleteHook(0xE8, 0x007C5DB0, &GensLogoPlayer);
				
	}

	if (gProtect.m_MainInfo.AlwaysPlayerShowName == 1)
	{
		SetCompleteHook(0xE9, 0x00842859, &PlayerInfoCheckDelect);
		SetByte(0x81C03FA, 0x01);
	}
}

int valor = 0;

void GensLogoPlayer(int a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, char a10, char a11, float a12)
{
	gObjUser.Refresh();
	//RenderBitmap(a1, a2 - valor + 28, a3 + 30, 32.0, 34.3, a6, a7, a8, a9, a10, a11, a12);  //logo abajo del guild
	//RenderBitmap(a1, a2 - valor + 112, a3 + 10, 32.0, 34.3, a6, a7, a8, a9, a10, a11, a12); //logo al otro costado derecho
	//RenderBitmap(a1, a2 - valor + 28, a3 + -10, 32.0, 34.3, a6, a7, a8, a9, a10, a11, a12); //logo ariba del logo guild
	RenderBitmap(a1, a2 - valor + 4, a3 + 10, 32.0, 34.3, a6, a7, a8, a9, a10, a11, a12);   //logo al lado del guild 
}

void PlayerGuildLogo(int a1, int a2, char *a3)
{
	//gObjUser.Refresh();

	int result = *(DWORD *)(a3 + 668);
	int WChat = *(DWORD*)(a3 + 680); //W


	if ( (*(WORD *)(result + 124) == 0))
	{
		valor = 15;
		CreateGuildMark(*(WORD *)(result + 124), 1);
		RenderBitmap(31740, a1 - 18, a2 + 2, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	}
	
	if ( !(*(WORD *)(result + 124) == 0))
	{
		valor = 0;
		CreateGuildMark(*(WORD *)(result + 124), 1999);
		RenderBitmap(31740, a1 - 8000, a2 + 2, 16.0, 16.0, 0.0, 0.0, 1.0, 1.0, 1, 1, 0.0);
	}
	
	if (gCustomRankUser.m_Data[*(WORD*)(result + 0x7E)].m_MarryName != NULL /*&& ShowVIP > 0*/)
	{
		gElemental.DrawText((HFONT)pFontBigBold, a1-25, a2-15.0f, 0xFF5CC0FF, 0x0, WChat+50, 0, 3, gCustomRankUser.m_Data[*(WORD*)(result + 0x7E)].m_MarryName);//
		//gElemental.DrawText((HFONT)pFontBigBold, a1-25, a2-10.0f, 0xFFDD00FF, 0xFF009DFF, WChat+50, 0, 3, gCustomRankUser.m_Data[*(WORD*)(result + 0x7E)].m_MarryName);//
	}

	RenderBoolean(a1,a2,a3);
}