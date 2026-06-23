#include "StdAfx.h"
#include "Util.h"
#include "SEASON3B.h"
#include "cfreetype.h"
#include "wsclientline.h"
#include <ft2build.h>
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_FREETYPE_H
#ifndef EnableAlphaTest
#define EnableAlphaTest ((void(__cdecl*)(BYTE Mode)) 0x00635FD0)
#endif

#ifndef m_Resolution
#define m_Resolution *(int*)0xE8C240
#endif

#ifndef SceneFlag
#define SceneFlag *(int*)0xE609E8
#endif

#ifndef LOG_IN_SCENE
#define LOG_IN_SCENE 2
#endif

#ifndef CHARACTER_SCENE
#define CHARACTER_SCENE 4
#endif

#ifndef m_LanguageId
#define m_LanguageId ((char*)0xE8C5C4)
#endif


int iFontHeight;
FT_Face ft_face;
FT_Library ft_library;

std::map<FT_ULong, FTBitmap*> characters;
typedef FT_Error (*FT_Init_FreeType_Proc)(FT_Library*);
typedef FT_Error (*FT_New_Face_Proc)(FT_Library, const char*, FT_Long, FT_Face*);

cfreetype::cfreetype(void)
{
}

cfreetype::~cfreetype(void)
{
}

FTBitmap* GetULongChar(FT_ULong charcode)
{
	std::map<FT_ULong, FTBitmap*>::iterator it;

	it = characters.find(charcode);

	if( it != characters.end( ) )
		return it->second;

	return NULL;
}

void offsetColor(int uiBitmapIndex, unsigned char* AlphaBuffer, int width, int height, DWORD color)
{
	unsigned char* rgbaBuffer = new unsigned char[width * height * 4];

	for (int i = 0; i < width * height; i++)
	{
		rgbaBuffer[i * 4 + 3] = AlphaBuffer[i];
		rgbaBuffer[i * 4 + 0] = __Red(color);   // canal rojo
		rgbaBuffer[i * 4 + 1] = __Green(color); // canal verde
		rgbaBuffer[i * 4 + 2] = __Blue(color);  // canal azul
	}

	glBindTexture(GL_TEXTURE_2D, uiBitmapIndex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgbaBuffer);
	delete []rgbaBuffer;
}

void Glyphface(FT_UInt uiBitmapIndex, FT_ULong charcode)
{
	int Key = (charcode - 0xE000);

	FTBitmap* pNewBitmap = new FTBitmap;

	memset(pNewBitmap, 0, sizeof(FTBitmap));

	pNewBitmap->m_Width          = 20;
	pNewBitmap->m_Height         = 20;
	pNewBitmap->m_TextureUWidth  = 26;
	pNewBitmap->m_TextureVHeight = 26;
	pNewBitmap->BitmapIndex      = uiBitmapIndex;
	pNewBitmap->m_TextureU       = (Key % 19) * 26;
	pNewBitmap->m_TextureV       = (Key / 19) * 26;

	pNewBitmap->m_uWidth         = 20;
	pNewBitmap->m_uHeight        = 20;

	characters.insert(std::pair<FT_ULong, FTBitmap*>(charcode, pNewBitmap));
}

void FT_GlyphPush(FT_UInt uiBitmapIndex, FT_ULong KeyCode, FT_GlyphSlotRec* Glyph, BYTE *PakBuffer, int width, int height)
{
	FTBitmap *pNewBitmap = new FTBitmap;

	memset(pNewBitmap, 0, sizeof(FTBitmap));

	pNewBitmap->BitmapIndex = uiBitmapIndex,

	pNewBitmap->m_TextureUWidth  = width;
	pNewBitmap->m_TextureVHeight = height;
	pNewBitmap->m_TextureU  = Glyph->bitmap_left; //-- Alineamiento-Left
	pNewBitmap->m_TextureV  = (iFontHeight-Glyph->bitmap_top);  //-- Alineamiento-Top
	pNewBitmap->m_Width     = (int)(Glyph->advance.x >> 6);
	pNewBitmap->m_Height    = (int)(Glyph->bitmap_top);
	pNewBitmap->PakBuffer   = new unsigned char[width * height];

	if (width > pNewBitmap->m_Width)
		pNewBitmap->m_uWidth = width;
	else
		pNewBitmap->m_uWidth = pNewBitmap->m_Width;

	pNewBitmap->m_uHeight = height;

	memcpy(pNewBitmap->PakBuffer, PakBuffer, width * height);

	characters.insert(std::pair<FT_ULong, FTBitmap*>(KeyCode, pNewBitmap));

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pNewBitmap->PakBuffer);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void cBindTexture(int uiBitmapIndex)
{
	if (*(DWORD*)0xE61E60 != uiBitmapIndex)
	{
		*(DWORD*)0xE61E60 = uiBitmapIndex;
		glBindTexture(GL_TEXTURE_2D, uiBitmapIndex);
	}
}

void RenderGlyph(int Texture, float x,float y, int Width, int Height, float m_TextureU, float m_TextureV, float m_TextureUWidth, float m_TextureVHeight, GLfloat *m_TemColor, BOOL Active, DWORD textColor)
{
	cBindTexture(Texture);

	float p[4][2];

	y = (WindowHeight - y);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	float pos[2] = {0, 0};

	if ( !Active )
	{
		for (int i = 0; i < 3; i++)
		{
			if ( i == 2 )
			{
				pos[0] = x;
				pos[1] = y;
				if (!(__Red(textColor) == 0xFF && __Green(textColor) == 0xFF && __Blue(textColor) == 0xFF && __Alpha(textColor) == 0xFF))
					glColor4ub(__Red(textColor), __Green(textColor), __Blue(textColor), __Alpha(textColor));
				else
					glColor4fv(m_TemColor);
			}
			else if (i == 1)
			{
				pos[0] = x;
				pos[1] = y;
				if (__Alpha(textColor) > 100)
					glColor4ub(0, 0, 0, 255);
				else
					glColor4ub(0, 0, 0, __Alpha(textColor));
			}
			else
			{
				pos[0] = x + 1.0;
				pos[1] = y - 1.0;
				if (__Alpha(textColor) > 100)
					glColor4ub(0, 0, 0, 255);
				else
					glColor4ub(0, 0, 0, __Alpha(textColor));
			}
			p[0][0] = pos[0]        ; p[0][1] = pos[1];
			p[1][0] = pos[0]        ; p[1][1] = pos[1] - Height;
			p[2][0] = pos[0] + Width; p[2][1] = pos[1] - Height;
			p[3][0] = pos[0] + Width; p[3][1] = pos[1];
			//--
			float c[4][2];
			c[0][0] = m_TextureU     ; c[0][1] = m_TextureV;
			c[3][0] = m_TextureUWidth; c[3][1] = m_TextureV;
			c[2][0] = m_TextureUWidth; c[2][1] = m_TextureVHeight;
			c[1][0] = m_TextureU     ; c[1][1] = m_TextureVHeight;

			glBegin(GL_QUADS);
			for(int i=0;i<4;i++)
			{
				glTexCoord2f(c[i][0],c[i][1]);
				glVertex2f  (p[i][0],p[i][1]);
			}
			glEnd();
		}
	}
	else
	{
		if (!(__Red(textColor) == 0xFF && __Green(textColor) == 0xFF && __Blue(textColor) == 0xFF && __Alpha(textColor) == 0xFF))
			glColor4ub(__Red(textColor), __Green(textColor), __Blue(textColor), __Alpha(textColor));
		else
			glColor4fv(m_TemColor);

		p[0][0] = x        ; p[0][1] = y;
		p[1][0] = x        ; p[1][1] = y - Height;
		p[2][0] = x + Width; p[2][1] = y - Height;
		p[3][0] = x + Width; p[3][1] = y;
		//--
		float c[4][2];
		c[0][0] = m_TextureU     ; c[0][1] = m_TextureV;
		c[3][0] = m_TextureUWidth; c[3][1] = m_TextureV;
		c[2][0] = m_TextureUWidth; c[2][1] = m_TextureVHeight;
		c[1][0] = m_TextureU     ; c[1][1] = m_TextureVHeight;

		glBegin(GL_QUADS);
		for(int i=0;i<4;i++)
		{
			glTexCoord2f(c[i][0],c[i][1]);
			glVertex2f  (p[i][0],p[i][1]);
		}
		glEnd();
	}
}

void cfreetype::Create()
{
	HMODULE library = LoadLibraryA("freetype.dll");

	if (!library)
	{
		MessageBox(0,"Freetype.dll could not be loaded","Error",MB_OK | MB_ICONERROR);
		return;
	}

	FT_Init_FreeType_Proc FT_Init_FreeType = (FT_Init_FreeType_Proc)GetProcAddress(library, "FT_Init_FreeType");
	FT_New_Face_Proc FT_New_Face = (FT_New_Face_Proc)GetProcAddress(library, "FT_New_Face");

	if (!FT_Init_FreeType || !FT_New_Face)
	{
		MessageBox(0,"Cannot get exported functions","Error",MB_OK | MB_ICONERROR);
		FreeLibrary(library);
		return;
	}

	FT_Error error = FT_Init_FreeType(&ft_library);
	if (error)
	{
		MessageBox(0,"Could not initialize FreeType","Error",MB_OK | MB_ICONERROR);
		FreeLibrary(library);
		return;
	}

	error = FT_New_Face(ft_library, "Data/font/NormalFont.ttf", 0, &ft_face);

	if (error == FT_Err_Unknown_File_Format)
	{
		MessageBox(0,"unknown file format","Error",MB_OK | MB_ICONERROR);
	}
	else if ( error )
	{
		MessageBox(0,"Could not load font","Error",MB_OK | MB_ICONERROR);
		return;
	}

	if (FT_Select_Charmap(ft_face, FT_ENCODING_UNICODE))
	{
		MessageBox(0,"Could not set font character map.","Error",MB_OK | MB_ICONERROR);
		return;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	extern int FontSize;
	if (FontSize >= 8 && FontSize <= 24)
	{
		iFontHeight = FontSize;
	}
	else
	{
		switch (m_Resolution)
		{
		case 0:
			iFontHeight = 10;
			break;
		case 1:
			iFontHeight = 11;
			break;
		case 2:
			iFontHeight = 12;
			break;
		case 3:
			iFontHeight = 13;
			break;
		case 4:
			iFontHeight = 14;
			break;
		default:
			iFontHeight = 14;
			break;
		}
	}

	FT_ULong Charcode;
	FT_UInt glyph_index;

	FT_Set_Pixel_Sizes(ft_face, 0, (iFontHeight));
	Charcode = FT_Get_First_Char( ft_face, &glyph_index );

	while ( glyph_index != 0 )
	{
		FT_UInt uiBitmapIndex;

		FT_Load_Glyph(ft_face, glyph_index, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL);

		FT_Render_Glyph(ft_face->glyph, FT_RENDER_MODE_MONO);

		FT_Bitmap *b = &ft_face->glyph->bitmap;

		glGenTextures(1, &uiBitmapIndex);
		glBindTexture(GL_TEXTURE_2D, uiBitmapIndex);

		FT_GlyphPush(uiBitmapIndex, Charcode, ft_face->glyph, b->buffer, b->width, b->rows);


		Charcode = FT_Get_Next_Char( ft_face, Charcode, &glyph_index );
	}

	/*for (FT_ULong Uface = 0xE000; Uface <= 0xE169; Uface++)
	{
		Glyphface(EMOJI_LIST1, Uface);
	}*/

	FT_Done_Face(ft_face);
	FT_Done_FreeType(ft_library);
	FreeLibrary(library);
}

BOOL IsCharUTF8(const char* pszText)
{
	if (pszText == NULL || strlen(pszText) <= 0)
		return TRUE;

	const char* pbyCurr = pszText;
	BOOL        bUTF8   = TRUE;

	while ( (*pbyCurr != 0x00) && bUTF8)
	{
		if ((*pbyCurr & 0x80) == 0x00)
		{
			pbyCurr++;
		}
		else if (((*pbyCurr & 0xE0) == 0xC0) && ((*(pbyCurr+1) & 0xC0) == 0x80))
		{
			pbyCurr += 2;
		}
		else if (((*pbyCurr & 0xF0) == 0xE0) && ((*(pbyCurr+1) & 0xC0) == 0x80) && ((*(pbyCurr+2) & 0xC0) == 0x80))
		{
			pbyCurr += 3;
		}
		else if (((*pbyCurr & 0xF8) == 0xF0) && 
			((*(pbyCurr+1) & 0xC0) == 0x80) && ((*(pbyCurr+2) & 0xC0) == 0x80) && ((*(pbyCurr+3) & 0xC0) == 0x80))
		{
			pbyCurr += 4;
		}
		else
		{
			bUTF8 = FALSE;
		}
	}
	return bUTF8;
}

int ConvertCharToWideStr(std::wstring& wstrDest, LPCSTR szText)
{
	wstrDest = L"";

	if (szText == NULL || strlen(szText) <= 0)
		return 0;

	int nLenOfWideCharStr;
	int iConversionType;

	if (gMultiLanguage->GetCodePage() != CHINESE_CP)
	{
		if (strcmp(szText, "¸ÖÆ¼ ·Î±ä ¹öÁ¯") == 0)
			iConversionType = (IsCharUTF8(szText)) ? CP_UTF8 : 949;
		else
			iConversionType = (IsCharUTF8(szText)) ? CP_UTF8 : gMultiLanguage->GetCodePage();
	}
	else
	{
		iConversionType = gMultiLanguage->GetCodePage();
	}
	nLenOfWideCharStr = MultiByteToWideChar(iConversionType, 0, szText, -1, NULL, 0);

	wchar_t* pwszStr = new wchar_t[nLenOfWideCharStr];

	MultiByteToWideChar(iConversionType, 0, szText, -1, pwszStr, nLenOfWideCharStr);

	wstrDest += pwszStr;

	delete[] pwszStr;
	return nLenOfWideCharStr - 1;
}

void cfreetype::RenderText(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize, BOOL color, bool back)
{
	if (pszText == NULL || (pszText[0] == '\0' && iBoxWidth == 0)) return;

	if (strlen(pszText) <= 0 && iBoxWidth == 0) return;

	std::wstring wstr = L"";

	ConvertCharToWideStr(wstr, pszText);

	int m_TextWidth = this->ExtentPoint32(wstr);

	SIZE RealTextSize;
	RealTextSize.cx = m_TextWidth;
	RealTextSize.cy = (iFontHeight + 2);

	fPOINT RealBoxPos = {iPos_x * g_fScreenRate_x, iPos_y * g_fScreenRate_y};
	fBOXIN RealBoxSize = {iBoxWidth * g_fScreenRate_x, iBoxHeight * g_fScreenRate_y};
	fBOXIN RealRenderingSize = { (long)RealTextSize.cx, (long)RealTextSize.cy };

	if(RealBoxSize.cx == 0)
		RealBoxSize.cx = RealTextSize.cx;

	if (RealBoxSize.cy == 0)
		RealBoxSize.cy = RealTextSize.cy;
	else
		RealBoxPos.y += ((RealBoxSize.cy - RealRenderingSize.cy) / 2.f);

	int iTab = 0;
	int iClipMove = 0;

	if (iSort == RT3_SORT_LEFT_CLIP)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
	}
	else if (iSort == RT3_SORT_LEFT)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
			RealRenderingSize.cx = RealBoxSize.cx;
	}
	else if(iSort == RT3_SORT_CENTER)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = (RealRenderingSize.cx - RealBoxSize.cx) / 2;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = (RealBoxSize.cx - RealRenderingSize.cx) / 2;
		}
	}
	else if (iSort == RT3_SORT_RIGHT)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = RealBoxSize.cx - RealRenderingSize.cx;
		}
	}
	else if (iSort == RT3_WRITE_RIGHT_TO_LEFT)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = RealBoxSize.cx - RealRenderingSize.cx;
		}
		RealBoxPos.x -= RealBoxSize.cx;
	}
	else if (iSort == RT3_WRITE_CENTER)
	{
		if(RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = (RealRenderingSize.cx - RealBoxSize.cx) / 2;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = (RealBoxSize.cx - RealRenderingSize.cx) / 2;
		}
		RealBoxPos.x -= (RealBoxSize.cx / 2);
	}

	GLfloat m_TemColor[4];
	glGetFloatv(GL_CURRENT_COLOR, m_TemColor);

	extern DWORD g_dwCurrentFontThis;
	DWORD m_ColoText1 = g_dwCurrentFontThis ? (*(DWORD *)((*(DWORD *)(g_dwCurrentFontThis + 4)) + 16)) : CURRENT_COLOR1;
	DWORD m_ColoText2 = g_dwCurrentFontThis ? (*(DWORD *)((*(DWORD *)(g_dwCurrentFontThis + 4)) + 20)) : CURRENT_COLOR2;
	
	if (g_dwCurrentFontThis)
	{
		HDC hdc = (HDC)*(DWORD*)(*(DWORD*)(g_dwCurrentFontThis + 4));
		if (hdc)
		{
			COLORREF hdcColor = GetTextColor(hdc);
			
			if (hdcColor == 0x00E6D28C) m_ColoText1 = 0xFFDBB012; // Party Custom
			else if (hdcColor == 0x008CFF8C) m_ColoText1 = 0xFF0ADA0A; // Guild Custom
			else if (m_ColoText1 == 0xFF000000 && hdcColor != CLR_INVALID && hdcColor != 0x00000000)
			{
				m_ColoText1 = hdcColor | 0xFF000000;
			}
		}
	}

	if (m_ColoText1 == 0xFFE6D28C) // Original Client Party Color
		m_ColoText1 = 0xFFDBB012; // Custom Party Color
	else if (m_ColoText1 == 0xFF8CFF8C) // Original Client Guild Color
		m_ColoText1 = 0xFF0ADA0A; // Custom Guild Color

	extern DWORD g_CurrentChatType;
	if (m_ColoText1 == 0xFFFFFFFF || m_ColoText1 == 0xFF000000)
	{
		if (g_CurrentChatType == 5) // Party
		{
			m_ColoText1 = 0xFFDBB012; // Light Blue (ABGR: #12b0dbff)
		}
		else if (g_CurrentChatType == 6) // Guild
		{
			m_ColoText1 = 0xFF0ADA0A; // Light Green (ABGR: #0ada0aff)
		}
		else if (g_CurrentChatType == 2) // Whisper
		{
			m_ColoText1 = 0xFFFF8CFF; // Pink/Purple (ABGR: #FFff8cff)
		}
	}

	if (m_ColoText1 == 0xFF000000)
	{
		m_ColoText1 = 0xFFFFFFFF; // Force fallback to OpenGL color (m_TemColor)
	}

	if (pszText)
	{
		if (strstr(pszText, ": [POST]:") != NULL)
		{
			m_ColoText1 = 0xFF2EB4D3; // Gold color in ABGR format (#D3B42E)
		}
		else if (strstr(pszText, ": ~") != NULL || strstr(pszText, "]~") != NULL) // Party Chat
		{
			m_ColoText1 = 0xFFDBB012; // Light Blue (ABGR: #12b0dbff)
		}
		else if (strstr(pszText, ": @@") != NULL || strstr(pszText, "]@@") != NULL) // Alliance Chat
		{
			m_ColoText1 = 0xFF00FFFF; // Yellow (ABGR: #FFFF00)
		}
		else if (strstr(pszText, ": @>") != NULL || strstr(pszText, "]@>") != NULL) // Guild Notice
		{
			m_ColoText1 = 0xFF00FFCC; // Yellowish Green
		}
		else if (strstr(pszText, ": @") != NULL || strstr(pszText, "]@") != NULL) // Guild Chat
		{
			m_ColoText1 = 0xFF0ADA0A; // Light Green (ABGR: #0ada0aff)
		}
		else if (strstr(pszText, ": $") != NULL || strstr(pszText, "]$") != NULL) // Gens Chat
		{
			m_ColoText1 = 0xFF7070FF; // Reddish
		}
	}
	// DWORD m_ColoText2 = CURRENT_COLOR2; (Ya definido arriba)

	if (back && __Alpha(m_ColoText2) > 0)
	{
		EnableAlphaTest(true);
		glColor4ub(__Red(m_ColoText2), __Green(m_ColoText2), __Blue(m_ColoText2), __Alpha(m_ColoText2));
		RenderColor((RealBoxPos.x / g_fScreenRate_x), (RealBoxPos.y  / g_fScreenRate_y), (RealBoxSize.cx / g_fScreenRate_x), (RealBoxSize.cy / g_fScreenRate_y), 0.0, 0);
		EndRenderColor();
	}

	int TextureWidth = 0;
	auto Key = wstr.begin();

	EnableAlphaTest(true);
	for (; Key != wstr.end(); Key++)
	{
		FTBitmap* b;
		if (*Key == 32)
			b = GetULongChar('|');
		else
			b = GetULongChar(*Key);

		if (!b) continue;

		float Next_y = RealBoxPos.y;
		float Next_x = RealBoxPos.x + TextureWidth + iClipMove + iTab;

		if (*Key != 32 && Next_x >= RealBoxPos.x && Next_x <= RealBoxPos.x+RealBoxSize.cx && __Alpha(m_ColoText1) > 0)
		{
			/*if (b->BitmapIndex == EMOJI_LIST1)
			{
				glColor4ub(255, 255, 255, __Alpha(m_ColoText1));
				Next_y += ((RealRenderingSize.cy - b->m_Height) / 2.f);
				RenderImage2F(b->BitmapIndex, Next_x, Next_y, b->m_Width, b->m_Height, b->m_TextureU, b->m_TextureV, b->m_TextureUWidth, b->m_TextureVHeight);
			}
			else
			{*/
				Next_y += b->m_TextureV;
				Next_x += b->m_TextureU;
				RenderGlyph(b->BitmapIndex, Next_x, Next_y, b->m_TextureUWidth, b->m_TextureVHeight, 0.0, 0.0, 1.0, 1.0, m_TemColor, color, m_ColoText1);
			//}
		}
		TextureWidth += b->m_Width;
	}
	glColor4fv(m_TemColor);

	if ( lpTextSize )
	{
		lpTextSize->cx = (RealRenderingSize.cx / g_fScreenRate_x);
		lpTextSize->cy = (RealRenderingSize.cy / g_fScreenRate_y);
	}
}

void cfreetype::RenderTextReal(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize, BOOL color, bool back)
{
	if (pszText == NULL || (pszText[0] == '\0' && iBoxWidth == 0)) return;

	if (strlen(pszText) <= 0 && iBoxWidth == 0) return;

	std::wstring wstr = L"";

	ConvertCharToWideStr(wstr, pszText);

	int m_TextWidth = this->ExtentPoint32(wstr);

	SIZE RealTextSize;
	RealTextSize.cx = m_TextWidth;
	RealTextSize.cy = (iFontHeight + 2);

	fPOINT RealBoxPos = { iPos_x, iPos_y };
	fBOXIN RealBoxSize = { iBoxWidth, iBoxHeight };
	fBOXIN RealRenderingSize = { (long)RealTextSize.cx, (long)RealTextSize.cy };

	if (RealBoxSize.cx == 0)
		RealBoxSize.cx = RealTextSize.cx;

	if (RealBoxSize.cy == 0)
		RealBoxSize.cy = RealTextSize.cy;
	else
		RealBoxPos.y += ((RealBoxSize.cy - RealRenderingSize.cy) / 2.f);

	int iTab = 0;
	int iClipMove = 0;

	if (iSort == RT3_SORT_LEFT_CLIP)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
	}
	else if (iSort == RT3_SORT_LEFT)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
			RealRenderingSize.cx = RealBoxSize.cx;
	}
	else if (iSort == RT3_SORT_CENTER)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = (RealRenderingSize.cx - RealBoxSize.cx) / 2;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = (RealBoxSize.cx - RealRenderingSize.cx) / 2;
		}
	}
	else if (iSort == RT3_SORT_RIGHT)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = RealBoxSize.cx - RealRenderingSize.cx;
		}
	}
	else if (iSort == RT3_WRITE_RIGHT_TO_LEFT)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = RealRenderingSize.cx - RealBoxSize.cx;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = RealBoxSize.cx - RealRenderingSize.cx;
		}
		RealBoxPos.x -= RealBoxSize.cx;
	}
	else if (iSort == RT3_WRITE_CENTER)
	{
		if (RealRenderingSize.cx > RealBoxSize.cx)
		{
			iClipMove = (RealRenderingSize.cx - RealBoxSize.cx) / 2;
			RealRenderingSize.cx = RealBoxSize.cx;
		}
		else
		{
			iTab = (RealBoxSize.cx - RealRenderingSize.cx) / 2;
		}
		RealBoxPos.x -= (RealBoxSize.cx / 2);
	}

	GLfloat m_TemColor[4];
	glGetFloatv(GL_CURRENT_COLOR, m_TemColor);

	extern DWORD g_dwCurrentFontThis;
	DWORD m_ColoText1 = g_dwCurrentFontThis ? (*(DWORD *)((*(DWORD *)(g_dwCurrentFontThis + 4)) + 16)) : CURRENT_COLOR1;
	DWORD m_ColoText2 = g_dwCurrentFontThis ? (*(DWORD *)((*(DWORD *)(g_dwCurrentFontThis + 4)) + 20)) : CURRENT_COLOR2;

	if (g_dwCurrentFontThis)
	{
		HDC hdc = (HDC)*(DWORD*)(*(DWORD*)(g_dwCurrentFontThis + 4));
		if (hdc)
		{
			COLORREF hdcColor = GetTextColor(hdc);
			
			if (hdcColor == 0x00E6D28C) m_ColoText1 = 0xFFDBB012; // Party Custom
			else if (hdcColor == 0x008CFF8C) m_ColoText1 = 0xFF0ADA0A; // Guild Custom
			else if (m_ColoText1 == 0xFF000000 && hdcColor != CLR_INVALID && hdcColor != 0x00000000)
			{
				m_ColoText1 = hdcColor | 0xFF000000;
			}
		}
	}

	if (m_ColoText1 == 0xFFE6D28C) // Original Client Party Color
		m_ColoText1 = 0xFFDBB012; // Custom Party Color
	else if (m_ColoText1 == 0xFF8CFF8C) // Original Client Guild Color
		m_ColoText1 = 0xFF0ADA0A; // Custom Guild Color

	extern DWORD g_CurrentChatType;
	if (m_ColoText1 == 0xFFFFFFFF || m_ColoText1 == 0xFF000000)
	{
		if (g_CurrentChatType == 5) // Party
		{
			m_ColoText1 = 0xFFDBB012; // Light Blue (ABGR: #12b0dbff)
		}
		else if (g_CurrentChatType == 6) // Guild
		{
			m_ColoText1 = 0xFF0ADA0A; // Light Green (ABGR: #0ada0aff)
		}
		else if (g_CurrentChatType == 2) // Whisper
		{
			m_ColoText1 = 0xFFFF8CFF; // Pink/Purple (ABGR: #FFff8cff)
		}
	}

	if (m_ColoText1 == 0xFF000000)
	{
		m_ColoText1 = 0xFFFFFFFF; // Force fallback to OpenGL color (m_TemColor)
	}

	if (pszText)
	{
		if (strstr(pszText, ": [POST]:") != NULL)
		{
			m_ColoText1 = 0xFF2EB4D3; // Gold color in ABGR format (#D3B42E)
		}
		else if (strstr(pszText, ": ~") != NULL || strstr(pszText, "]~") != NULL) // Party Chat
		{
			m_ColoText1 = 0xFFDBB012; // Light Blue (ABGR: #12b0dbff)
		}
		else if (strstr(pszText, ": @@") != NULL || strstr(pszText, "]@@") != NULL) // Alliance Chat
		{
			m_ColoText1 = 0xFF00FFFF; // Yellow (ABGR: #FFFF00)
		}
		else if (strstr(pszText, ": @>") != NULL || strstr(pszText, "]@>") != NULL) // Guild Notice
		{
			m_ColoText1 = 0xFF00FFCC; // Yellowish Green
		}
		else if (strstr(pszText, ": @") != NULL || strstr(pszText, "]@") != NULL) // Guild Chat
		{
			m_ColoText1 = 0xFF0ADA0A; // Light Green (ABGR: #0ada0aff)
		}
		else if (strstr(pszText, ": $") != NULL || strstr(pszText, "]$") != NULL) // Gens Chat
		{
			m_ColoText1 = 0xFF7070FF; // Reddish
		}
	}

	int TextureWidth = 0;
	auto Key = wstr.begin();

	EnableAlphaTest(true);
	for (; Key != wstr.end(); Key++)
	{
		FTBitmap* b;
		if (*Key == 32)
			b = GetULongChar('|');
		else
			b = GetULongChar(*Key);

		if (!b) continue;

		float Next_y = RealBoxPos.y;
		float Next_x = RealBoxPos.x + TextureWidth + iClipMove + iTab;

		if (*Key != 32 && Next_x >= RealBoxPos.x && Next_x <= RealBoxPos.x + RealBoxSize.cx && __Alpha(m_ColoText1) > 0)
		{
			/*if (b->BitmapIndex == EMOJI_LIST1)
			{
				glColor4ub(255, 255, 255, __Alpha(m_ColoText1));
				Next_y += ((RealRenderingSize.cy - b->m_Height) / 2.f);
				RenderImage2F(b->BitmapIndex, Next_x, Next_y, b->m_Width, b->m_Height, b->m_TextureU, b->m_TextureV, b->m_TextureUWidth, b->m_TextureVHeight);
			}
			else
			{*/
				Next_y += b->m_TextureV;
				Next_x += b->m_TextureU;
				RenderGlyph(b->BitmapIndex, Next_x, Next_y, b->m_TextureUWidth, b->m_TextureVHeight, 0.0, 0.0, 1.0, 1.0, m_TemColor, color, m_ColoText1);
			//}
		}
		TextureWidth += b->m_Width;
	}
	glColor4fv(m_TemColor);

	if (lpTextSize)
	{
		lpTextSize->cx = RealRenderingSize.cx;
		lpTextSize->cy = RealRenderingSize.cy;
	}
}

int cfreetype::ExtentPoint32(std::wstring wstr)
{
	int TextureWidth = 0;
	auto Key = wstr.begin();

	for (; Key != wstr.end(); Key++)
	{
		FTBitmap* pNewBitmap = NULL;

		if (*Key == 32 || *Key == 0x0A || *Key == 0x0)
			pNewBitmap = GetULongChar('|');
		else
			pNewBitmap = GetULongChar(*Key);

		if ( !pNewBitmap ) continue;

		TextureWidth += pNewBitmap->m_uWidth;
	}
	return TextureWidth;
}

void cfreetype::ExtentPoint32(LPCWSTR wstrText, OUT SIZE* lpTextSize)
{
	std::wstring wstr = wstrText;

	int TextureWidth = 0;
	auto Key = wstr.begin();

	for (; Key != wstr.end(); Key++)
	{
		FTBitmap* pNewBitmap = NULL;

		if (*Key == 32 || *Key == 0x0A || *Key == 0x0)
			pNewBitmap = GetULongChar('|');
		else
			pNewBitmap = GetULongChar(*Key);

		if ( !pNewBitmap ) continue;

		TextureWidth += pNewBitmap->m_uWidth;
	}

	lpTextSize->cx = TextureWidth;
	lpTextSize->cy = (iFontHeight + 2);
}

void cfreetype::ExtentPoint32(const char* pszText, OUT SIZE* lpTextSize)
{
	std::wstring wstr = L"";
	ConvertCharToWideStr(wstr, pszText);

	int TextureWidth = 0;
	auto Key = wstr.begin();

	for (; Key != wstr.end(); Key++)
	{
		FTBitmap* pNewBitmap = NULL;

		if (*Key == 32 || *Key == 0x0A || *Key == 0x0)
			pNewBitmap = GetULongChar('|');
		else
			pNewBitmap = GetULongChar(*Key);

		if ( !pNewBitmap ) continue;

		TextureWidth += pNewBitmap->m_uWidth;
	}

	lpTextSize->cx = TextureWidth;
	lpTextSize->cy = (iFontHeight + 2);
}

//--
void cfreetype::CWinMain(int This)
{
	cfreetype::Instance()->Create();

	((void(__thiscall*)(int)) 0x00859F90)(This);
}

DWORD g_dwCurrentFontThis = 0;

void cfreetype::FT_RenderTextOriginal(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize)
{
	if ( *(DWORD *)(This + 4) )
	{
		g_dwCurrentFontThis = This;
		cfreetype::Instance()->RenderText(iPos_x, iPos_y, pszText, iBoxWidth, iBoxHeight, iSort, lpTextSize, TRUE);
	}
}

void cfreetype::RenderTextBackground(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize)
{
	if ( *(DWORD *)(This + 4) )
	{
		g_dwCurrentFontThis = This;
		cfreetype::Instance()->RenderText(iPos_x, iPos_y, pszText, iBoxWidth, iBoxHeight, iSort, lpTextSize, false, true);
	}
}

void cfreetype::RenderTextOriginal(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize)
{
	if ( *(DWORD *)(This + 4) )
	{
		g_dwCurrentFontThis = This;
		if ( SceneFlag == LOG_IN_SCENE || SceneFlag == CHARACTER_SCENE)
		{
			rendertextOriginal(This, iPos_x, iPos_y, (int)pszText, iBoxWidth, iBoxHeight, iSort, (int)lpTextSize);
		}
		else
		{
			cfreetype::Instance()->RenderText(iPos_x, iPos_y, pszText, iBoxWidth, iBoxHeight, iSort, lpTextSize);
		}
	}
}

BOOL cfreetype::_GetTextExtentPoint32(int This, HDC hdc, LPCSTR lpString, int cbString, LPSIZE lpSize)
{
	if ( SceneFlag == LOG_IN_SCENE || SceneFlag == CHARACTER_SCENE)
	{
		std::wstring wstrText = L"";
		ConvertCharToWideStr(wstrText, lpString);
	
		return GetTextExtentPoint32W(hdc, wstrText.c_str(), wstrText.length(), lpSize);
	}
	else
	{
		cfreetype::Instance()->ExtentPoint32(lpString, lpSize);
		return TRUE;
	}
}

BOOL cfreetype::_ExtentPoint32(int This, HDC hdc, LPCWSTR lpString, int cbString, LPSIZE lpSize)
{
	cfreetype::Instance()->ExtentPoint32(lpString, lpSize);
	return TRUE;
}

bool CheckSpecialText(char *Text)
{
	return false;
}

void cfreetype::MultiLanguage_allocator(__MultiLanguage* This, int str1, int str2, int str3, int str4, int str5, int str6, int str7)
{
	((void(__thiscall*)(__MultiLanguage*, int, int, int, int, int, int, int)) 0x00958CF0)(This, str1, str2, str3, str4, str5, str6, str7);

	if (strcmp(m_LanguageId, "Chs") == 0)
	{
		This->iCodePage = CHINESE_CP;
		This->byLanguage = LANGUAGE_CHS;
		This->iNumByteForOneCharUTF8 = 3;
		SetDword(0x00786D30 + 1, This->iCodePage);
		SetDword(0x00787040 + 1, This->iCodePage);
		SetDword(0x0078B40F + 1, This->iCodePage);
		SetDword(0x0078B46A + 1, This->iCodePage);
		SetDword(0x00840E75 + 1, This->iCodePage);
		//--
		SetDword(0x00958D4C + 3, This->iCodePage);
		SetDword(0x00958D4C + 3, This->iCodePage);
		SetDword(0x00958D85 + 3, This->iCodePage);
		SetDword(0x00958DBB + 3, This->iCodePage);
		SetDword(0x00958DD7 + 3, This->iCodePage);
		SetDword(0x00959037 + 3, This->iCodePage);
		SetDword(0x00958D56 + 3, This->iNumByteForOneCharUTF8);
		SetDword(0x00958D8F + 3, This->iNumByteForOneCharUTF8);
		SetDword(0x00958DC5 + 3, This->iNumByteForOneCharUTF8);
		SetDword(0x00958DE1 + 3, This->iNumByteForOneCharUTF8);
	}
	else if (strcmp(m_LanguageId, "Kor") == 0)
	{
		This->byLanguage = 4;
		This->iCodePage = CTRY_KOREAN;
		This->iNumByteForOneCharUTF8 = 2;
	}
}

int cfreetype::ConvertWideCharToStr(__MultiLanguage* This, int wstrDest, LPCWSTR lpString, int iConversionType)
{
	if (This->byLanguage == LANGUAGE_CHS)
	{
		iConversionType = This->iCodePage;
	}
	return _ConvertCharToWideStr(This, wstrDest, lpString, iConversionType);
}

void cfreetype::GetCurrentText_basic(int This, char *pszText, int iGetLength)
{
	if (!pszText) return;

	HWND hwnd = *(HWND*)(This + 120);

	wchar_t* wstrText = new wchar_t[iGetLength];

	GetWindowTextW(hwnd, wstrText, iGetLength);

	if (wstrText == NULL || wcslen(wstrText) <= 0)
		return;

	int nLenOfWideCharStr;

	nLenOfWideCharStr = WideCharToMultiByte(gMultiLanguage->GetCodePage(), 0, wstrText, -1, NULL, 0, 0, 0);

	if (nLenOfWideCharStr > 0 && nLenOfWideCharStr < iGetLength)
	{
		char* pszStr = new char[nLenOfWideCharStr];
		WideCharToMultiByte(gMultiLanguage->GetCodePage(), 0, wstrText, -1, pszStr, nLenOfWideCharStr, 0, 0);

		strncpy_s(pszText, iGetLength, pszStr, iGetLength - 1);

		delete[] pszStr;
	}

	delete[] wstrText;
}

void WideToChar(std::wstring unicode_char, char *pszText, int iGetLength)
{
	if (unicode_char.length() <= 0)
		return;

	int nLenOfWideCharStr;

	nLenOfWideCharStr = WideCharToMultiByte(gMultiLanguage->GetCodePage(), 0, unicode_char.c_str(), -1, NULL, 0, 0, 0);

	if (nLenOfWideCharStr > 0 && nLenOfWideCharStr < iGetLength)
	{
		char* pszStr = new char[nLenOfWideCharStr];
		WideCharToMultiByte(gMultiLanguage->GetCodePage(), 0, unicode_char.c_str(), -1, pszStr, nLenOfWideCharStr, 0, 0);
		strncpy_s(pszText, iGetLength, pszStr, iGetLength - 1);
		delete[] pszStr;
	}
}

void cfreetype::Init()
{
	//--005A967A
	//SetDword(0x004D27FB + 6, 16);
	SetDword(0x004D2870 + 1, FW_BOLD);
	SetDword(0x004D29AF + 1, FW_BOLD);
	SetCompleteHook(0xE8, 0x00959203, &ConvertWideCharToStr); //--
	SetCompleteHook(0xE9, 0x004217D0, &GetCurrentText_basic); //--
	SetCompleteHook(0xE8, 0x0078B284, &cfreetype::_ExtentPoint32); //-- CHECK CHAT
	SetCompleteHook(0xE8, 0x0078B30F, &cfreetype::_ExtentPoint32); //-- CHECK CHAT
	SetCompleteHook(0xE8, 0x0078B3F9, &cfreetype::_ExtentPoint32); //-- CHECK CHAT
	SetCompleteHook(0xE9, 0x00420150, &cfreetype::RenderTextOriginal);
	SetCompleteHook(0xE8, 0x00778F05, &cfreetype::RenderTextBackground); //-- ToolTip
	SetCompleteHook(0xE8, 0x007FBA67, &cfreetype::RenderTextBackground); //-- ToolTip
	SetCompleteHook(0xE9, 0x009593B0, &cfreetype::_GetTextExtentPoint32);
	SetCompleteHook(0xE8, 0x004D21EF, &cfreetype::MultiLanguage_allocator);
	SetCompleteHook(0xE8, 0x004D2A04, &cfreetype::CWinMain);
	//SetCompleteHook(0xE8, 0x005C0083, &cfreetype::FT_RenderTextOriginal); //-- ToolTip back
}

void cfreetype::Recreate()
{
	for (std::map<FT_ULong, FTBitmap*>::iterator it = characters.begin(); it != characters.end(); ++it)
	{
		if (it->second)
		{
			if (it->second->BitmapIndex != 0)
			{
				glDeleteTextures(1, &it->second->BitmapIndex);
			}
			if (it->second->PakBuffer)
			{
				delete[] it->second->PakBuffer;
			}
			delete it->second;
		}
	}
	characters.clear();

	this->Create();
}
