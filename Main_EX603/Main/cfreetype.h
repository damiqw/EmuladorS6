#pragma once
#pragma comment(lib, "..\\..\\Util\\Lib\\freetype.lib")
#define LANGUAGE_ENG					0
#define LANGUAGE_POR					1
#define LANGUAGE_SPN					2
#define LANGUAGE_CHS					3

typedef struct
{
	GLuint BitmapIndex;
	int    m_Width;
	int    m_Height;
	int    m_uWidth;
	int    m_uHeight;
	int    m_TextureU;
	int    m_TextureV;
	int    m_TextureUWidth;
	int    m_TextureVHeight;
	unsigned char*  PakBuffer;
} FTBitmap;

typedef struct
{
	float x;
	float y;
} fPOINT;

typedef struct
{
	float cx;
	float cy;
} fBOXIN;

class __MultiLanguage
{
public:
	BYTE byLanguage;
	int iCodePage;
	int iNumByteForOneCharUTF8;
public:
	int GetCodePage()
	{
		return ((int(__thiscall*)(int)) 0x00958E20)((int)this);
	}
};

#define RT3_SORT_LEFT 1
#define RT3_SORT_LEFT_CLIP 2
#define RT3_SORT_CENTER 3
#define RT3_SORT_RIGHT 4
#define RT3_WRITE_RIGHT_TO_LEFT 7
#define RT3_WRITE_CENTER 8

#define CTRY_1252					1252
#define CTRY_CHINESE				936
#define CTRY_CHINESE_TRADITIONAL	950
#define CTRY_KOREAN					949
#define CHINESE_CP					(0x3A8)
#define NUM_UTF8_CHN				3
#define NUM_UTF8_KOR				2



#define iCharSet				0xE61144
#define WindowWidth				*(GLsizei*)0x00E61E58
#define WindowHeight			*(GLsizei*)0x00E61E5C
#define g_Fontthis				((int(__thiscall*)()) 0x0041FE10)
#define FT_bitmap_Left			((float(__cdecl*)(float X)) 0x00636420)
#define FT_bitmap_Top1			((float(__cdecl*)(float Y)) 0x00636450)
#define glClearColorBuffer		((void(__cdecl*)(int Num )) 0x00635EE0)
#define pRender_GetTextColor	((DWORD(__thiscall*)(int This)) 0x0041FFE0)
#define pRender_GetBGColor		((DWORD(__thiscall*)(int This)) 0x00420010)
#define gMultiLanguage			((__MultiLanguage*)((int(*)()) 0x00401C10)())
#define BindTexture				((bool(__cdecl*)(int uiBitmapIndex)) 0x00635CF0)
#define ExtraHDc()				(*(HDC *)((*(DWORD *)(((int(__thiscall*)()) 0x0041FE10)() + 4)) + 4))
#define textcolor()				(*(DWORD *)((*(DWORD *)(((int(__thiscall*)()) 0x0041FE10)() + 4)) + 16))
#define InsertBitmap			((int(__thiscall*)(int This, int uiBitmapIndex, BYTE* Buffer)) 0x004FE710)
#define BackColor()				(*(DWORD *)((*(DWORD *)(((int(__thiscall*)()) 0x0041FE10)() + 4)) + 20))
#define glcolor(back)			glColor4ub(__Red(back), __Green(back), __Blue(back), __Alpha(back))
#define _FindText				((bool (__cdecl*)(const char* Text,const char* Token,bool First)) 0x005A8500)

#define rendertextOriginal(This, iPos_x, iPos_y, pszText, iBoxWidth, iBoxHeight, iSort, lpTextSize)		((*(void (__thiscall **)(int, int, int, int, int, int, int, int))(**(DWORD **)(This + 4) + 44))(*(DWORD *)(This + 4), iPos_x, iPos_y, pszText, iBoxWidth, iBoxHeight, iSort, lpTextSize))

#define GlColorText()			glcolor(textcolor())
#define _alpha					__Alpha(textcolor())
#define CURRENT_COLOR1			(textcolor())
#define CURRENT_COLOR2			(BackColor())

inline unsigned char __Alpha(unsigned long rgba) { return ((rgba) >> 24); }
inline unsigned char __Red(unsigned long rgba) { return ((rgba) & 0xff); }
inline unsigned char __Green(unsigned long rgba) { return (((rgba) >> 8) & 0xff); }
inline unsigned char __Blue(unsigned long rgba) { return (((rgba) >> 16) & 0xff); }
#define SAFE_DELETE_ARRAY(p)  { if(p) { delete [] (p);     (p)=NULL; } }
#define _ConvertCharToWideStr		((int(__thiscall*)(__MultiLanguage* This, int wstrDest, LPCWSTR lpString, int iConversionType)) 0x009590E0)

class cfreetype
{
public:
	cfreetype(void);
	virtual ~cfreetype(void);
public:
	void Init();
	void Create();
	void Recreate();
	static void __thiscall CWinMain(int This);

	int ExtentPoint32(std::wstring wstrText);
	void ExtentPoint32(LPCWSTR wstrText, OUT SIZE* lpTextSize);
	void ExtentPoint32(const char* pszText, OUT SIZE* lpTextSize);

	void RenderText(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth = 0, int iBoxHeight = 0, int iSort = 1, OUT SIZE* lpTextSize = 0, BOOL color = 0, bool back = 0);
	void RenderTextReal(int iPos_x, int iPos_y, const char* pszText, int iBoxWidth = 0, int iBoxHeight = 0, int iSort = 1,OUT SIZE* lpTextSize = 0, BOOL color = 0, bool back = 0);

	static void __thiscall FT_RenderTextOriginal(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize);
	static void __thiscall RenderTextBackground(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize);

	bool OpenTga(GLuint uiBitmapIndex, const std::string& filename, GLuint uiFilter = GL_NEAREST, GLuint uiWrapMode = GL_CLAMP);
	static BOOL __thiscall _ExtentPoint32(int This, HDC hdc, LPCWSTR lpString, int cbString, LPSIZE lpSize);
	static BOOL __thiscall _GetTextExtentPoint32(int This, HDC hdc, LPCSTR lpMultiByteStr, int c, LPSIZE psizl);
	static void __thiscall RenderTextOriginal(int This, int iPos_x, int iPos_y, LPCSTR pszText, int iBoxWidth, int iBoxHeight, int iSort, OUT SIZE* lpTextSize);

	static void __thiscall GetCurrentText_basic(int This, char *pszText, int iGetLength);
	static int __thiscall ConvertWideCharToStr(__MultiLanguage* This, int wstrDest, LPCWSTR lpString, int iConversionType);
	static void __thiscall MultiLanguage_allocator(__MultiLanguage *This, int str1, int str2, int str3, int str4, int str5, int str6, int str7);

	static cfreetype* Instance()
	{
		static cfreetype tc; return &tc;
	};
};

extern int iFontHeight;
#define g_pRenderFreeType				(cfreetype::Instance())