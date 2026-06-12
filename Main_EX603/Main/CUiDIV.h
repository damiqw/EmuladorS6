#pragma once

typedef void(*PUSHEVENT_CALLBACK_LPVOID)(LPVOID);

enum IMAGE_LIST_S6//1.04e
{
	IMAGE_MENU_1 = 31292,	//newui_menu01.jpg
	IMAGE_MENU_2,			//newui_menu02.jpg
	IMAGE_MENU_3,			//newui_menu03.jpg
	IMAGE_MENU_2_1,			//newui_menu02-03.jpg
	IMAGE_GAUGE_BLUE,		//newui_menu_blue.tga
	IMAGE_GAUGE_GREEN,		//newui_menu_green.tga
	IMAGE_GAUGE_RED,		//newui_menu_red.tga
	IMAGE_GAUGE_AG,			//newui_menu_AG.tga
	IMAGE_GAUGE_SD,			//newui_menu_SD.tga
	IMAGE_GAUGE_EXBAR,		//newui_Exbar.jpg
	IMAGE_MASTER_GAUGE_BAR,	//Exbar_Master.jpg
	IMAGE_MENU_BTN_CSHOP,
	IMAGE_MENU_BTN_CHAINFO,
	IMAGE_MENU_BTN_MYINVEN,
	IMAGE_MENU_BTN_FRIEND,
	IMAGE_MENU_BTN_WINDOW,

	IMAGE_SKILL1 = 31308,
	IMAGE_SKILL2,
	IMAGE_COMMAND,
	IMAGE_SKILL3,
	IMAGE_SKILLBOX,
	IMAGE_SKILLBOX_USE,
	IMAGE_NON_SKILL1,
	IMAGE_NON_SKILL2,
	IMAGE_NON_COMMAND,
	IMAGE_NON_SKILL3,
	IMAGE_MASTER_SKILL = 31534,
	IMAGE_NON_MASTER_SKILL,
};

enum UIDIABLOIV
{
	DIV_MainUI = 51235,
	DIV_MainOrbLife,
	DIV_MainOrbMana,
	DIV_MainOrbPoison,
	DIV_MainOrbLine,
	DIV_MainBarAG,
	DIV_MainBarSD,
	DIV_RenderNumber,
	DIV_BackExpBar,
	DIV_Notification,
	DIV_BarPotion,

	DIV_SKILL1,
	DIV_SKILL2,
	DIV_COMMAND,
	DIV_SKILL3,
	DIV_SkillBox,
	DIV_HotKeySkillListUp,
	DIV_NON_SKILL1,
	DIV_NON_SKILL2,
	DIV_NON_COMMAND,
	DIV_NON_SKILL3,
	DIV_MASTER_SKILL,
	DIV_NON_MASTER_SKILL,
};

//timeGetTime
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

//OpenGL
#include <gl\GL.h>
#pragma comment(lib,"Opengl32.lib")

#define RenderSkillIcon							((void(__thiscall*)(int This, int iIndex, float x, float y, float width, float height)) 0x00813DC0)
#define GetUI_NewSkillList						((int(__thiscall*)(int)) 0x00861200)
#define WindowWidth								*(GLsizei*)0x0E61E58
#define WindowHeight							*(GLsizei*)0x0E61E5C
#define BindTexture								((bool(__cdecl*)(int tex)) 0x00635CF0)
#define EnableAlphaBlend						((void(__cdecl*)()) 0x00636070)
#define EnableAlphaTest							((void(__cdecl*)(bool DepthMask)) 0x00635FD0)
#define Hero									*(int*)0x007BC4F04
#define IsPress									((int(__cdecl*)(int VKBUTTON)) 0x00791070)
#define g_fScreenRate_x							*(float*)0xE7C3D4
#define g_fScreenRate_y							*(float*)0xE7C3D8
#define IsQuestIndexByEtcListEmpty				((bool(__thiscall*)(void *This)) 0x005235E0)
#define GetTimeCheck							((bool(__thiscall*)(int This, int index, int DelayTime)) 0x0095ABE0)
#define CTimeCheck_GetSingleton					((int(__cdecl*)()) 0x00815610)
#define CheckNoReadLetter						((bool(__thiscall*)(int This)) 0x00496880)
#define GetLetterList							((int(__cdecl*)()) 0x007C3390)
#define CameraViewFar							*(float*)0xE61E3C
#define CameraFOV								*(float*)0xE61E40
#define CameraViewNear							*(float*)0xE61E38
#define CameraTopViewEnable						*(BYTE*)0xE61E3C
#define AlphaTestEnable							*(BYTE*)0x879325C
#define TextureEnable							*(BYTE*)0x8793260
#define DepthTestEnable							*(BYTE*)0x879325F
#define CullFaceEnable							*(BYTE*)0x879325E
#define DepthMaskEnable							*(BYTE*)0x879325D
#define FogEnable								*(BYTE*)0x87933F9
#define FogDensity								*(float*)0xE61E44
#define FogColor								*(float*)0xE61E48
#define glViewport2								((void(__cdecl*)(int x,int y,int Width,int Height)) 0x006363D0)
#define CameraMatrix							*(char*)0x87933A0
#define GetOpenGLMatrix							((void(__cdecl*)(int a1)) 0x00635830)
#define gluPerspective2							((int(__cdecl*)(float Fov,float Aspect,float ZNear,float ZFar)) 0x006358A0)
#define CameraAngle								((float*)0x87933D0)
#define CameraPosition							((float*)0x87933DC)
#define PlayBuffer								((signed int(__cdecl*)(int a1, int a2, int a3)) 0x006D6C20)
#define SceneFlag								*(int*)0x0E609E8
#define Toggle2									((void(__thiscall*)(int This, DWORD dwKey)) 0x0078B130)
#define IsVisible								((bool(__thiscall*)(int This, DWORD dwKey)) 0x0085EC20)
#define Hide									((bool(__thiscall*)(int This, DWORD dwKey)) 0x0085F9A0)
#define Show									((bool(__thiscall*)(int This, DWORD dwKey)) 0x0085EC50)

class cUiDIV
{
public:
	cUiDIV();
	virtual ~cUiDIV();

	void CLoadBitmap(char* Folder, int Code, int Arg3, int Arg4, int Arg5, int Arg6);
	void RenderFrameWindow(GLuint uiImageType, float x, float y, float width, float height);
	static void LifeManaOrbs(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha);
	void RenderIconSkill(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale, float Alpha);

	static void CurrentSkill_CheckMouse(int x, int y, int width, int height);
	static void SkillBar_CheckMouse(int x, int y, int width, int height);

	static void Exp_CheckMouse(int x, int y, int width, int height);

	static void Skill_RenderNumber(float x, float y, int iNum, float fScale);

	static void Exp_RenderNumber(float x, float y, int iNum, float fScale);

	static void Life_RenderNumber(float x, float y, int iNum, float fScale);
	static void Mana_RenderNumber(float x, float y, int iNum, float fScale);
	static void AG_RenderNumber(float x, float y, int iNum, float fScale);
	static void SD_RenderNumber(float x, float y, int iNum, float fScale);

	static void Potion_RenderNumber(float x, float y, int iNum/*, float fScale*/);

	static void Potion_RenderItem3D(float sx, float sy, float Width, float Height, int Type, int Level, int Option1, int ExtOption, bool PickUp);

	static void __thiscall CHotKeyQStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y);
	static void __thiscall CHotKeyWStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y);
	static void __thiscall CHotKeyEStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y);
	static void __thiscall CHotKeyRStateItem(int This, float RenderItem3D_x, float RenderItem3D_y, float RenderNumber_x, float RenderNumber_y);
	void Load();

private:
};
extern cUiDIV gcUiDIV;