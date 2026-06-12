#pragma once

#define glViewport2					((void(__cdecl*)(GLint x, int a2, GLsizei width, GLsizei height)) 0x006363D0)
#define CameraMatrix				*(char*)0x87933A0
#define GetOpenGLMatrix				((void(__cdecl*)(int a1)) 0x00635830)
#define gluPerspective2				((int(__cdecl*)(float a1, float a2, float a3, float a4)) 0x006358A0)
#define JCBeginOpengl				((void(__cdecl*)(GLint x, int a2, GLsizei width, GLsizei height)) 0x00636480)


#define OpenglWindowHeight				*(int*)0x87933E8
#define OpenglWindowWidth				*(int*)0x87933EC
#define OpenglWindowY					*(int*)0x87933F0
#define OpenglWindowX					*(int*)0x87933F4
#define gluPerspective					((void(__stdcall*)(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)) 0x00995FB2)
#define gluOrtho2D					((void(__stdcall*)(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top)) 0x00995FB8)
#define CameraFOV				*(float*)0xE61E40
#define CameraViewNear			*(float*)0xE61E38
#define CameraViewFar			*(float*)0xE61E3C

#define sub_860B50					((int(__thiscall*)(void * _this)) 0x00860B50)
#define sub_815F50					((int(__thiscall*)(int a1, char a5, char a6)) 0x00815F50)
#define sub_861A60					((int(__thiscall*)(int This))0x00861A60)
#define sub_7D6270					((int(__thiscall*)(int This, int a5))0x007D6270)

#define JCBaulExtShow				((void (__thiscall*)(int This)) 0x008567B0)
#define JCBaulExtMove				((BYTE *(__thiscall*)(int This, int a2, int a3)) 0x008564F0)
#define JCStoreMove					((int(__thiscall*)(int This, int a2, int a3, int a4)) 0x00840D80)
#define JCChaosMove					((int(__thiscall*)(void *This, int a2, int a3, int a4)) 0x0082C340)
#define JCShopMove					((BYTE *(__thiscall*)(int This, int a2, int a3, int a4)) 0x00846B90)
#define JCOtherStoreMove			((int (__thiscall*)(void *This, int a2, int a3, int a4)) 0x0084FA90)
#define JCBaulMove					((int (__thiscall*)(void *This, int a2, int a3, int a4)) 0x00857200)
#define JCInvExtMove				((signed int (__thiscall*)(int This, int a2, int a3)) 0x007D4E70)
#define JCTradeMove					((int (__thiscall*)(void *This, int a2, int a3, int a4)) 0x00863F10)
#define JCLuckyMove					((int (__thiscall*)(void *This, int a2, int a3, int a4)) 0x007F0460)

#define InitCashShop							((BYTE(__thiscall*)(int thisa, int a5, int x, int y)) 0x00942E80)
#define CNewUIMainFrameHelper					((BYTE(__thiscall*)(int thisa, int a5, int x, int y)) 0x007F0C80)
#define CNewUIMainFrameMaster					((int(__thiscall*)(int thisa)) 0x00819510)
#define CNewUIMainFrameTradeMove				((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x00863F10)
#define CNewUIMainFrameBaulExtMove				((BYTE*(__thiscall*)(int thisa, int PosX, int PosY)) 0x008564F0)
#define CNewUIMainFrameBaulMove					((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x00857200)
#define CNewUIMainFrameInvExtMove				((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x007D4E70)
#define CNewUIMainFrameLuckyMove				((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x007F0460)
#define CNewUIMainFrameOtherStoreMove			((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x0084FA90)
#define CNewUIMainFrameShopMove					((BYTE*(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x00846B90)
#define CNewUIMainFrameChaosMove				((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x0082C340)
#define CNewUIMainFrameStoreMove				((int(__thiscall*)(int thisa, int PosX, int PosY, int Ext)) 0x00840D80)
#define CNewUIMainFrameControl					((int(__thiscall*)(int thisa, int PosX, int PosY)) 0x007DC240)
#define RenderBitmapUV							((void(__cdecl*)(int a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11, float a12)) 0x00638E90)
#define CNewPictureFont							((int(__thiscall*)(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin)) 0x00420150)
#define GetInstanceFont							((int(*)( )) 0x0041FE10)
#define ChangeButtonInfo2						((int(__thiscall*)(char *This, int X, int Y, int Width, int Height)) 0x00779410)

/*sub_779350((int)(a1 + 92), a2, a3, a4, 1, 31689, 1, 0, 0);*/
//#define FixIlusBtn ((int(__thiscall*)(int a1, int PosX, int PosY, int Width, int Height, int ImageID, int Center, int ScaleX, int ScaleY))0x00779350)
////#define sub_779410BtnIlus ((int(__thiscall*)(char *This, int X, int Y, int Width, int Height)) 0x00779410)
#define subFixbtn ((int(__thiscall*)(int a1,int a2, int a3, int a4, char a5, int a6, char a7, char a8, char a9)) 0x00779350)

//void BRenderTooltipAncestral_772EA0(int ThisR);


//void CBeginBitmap( int move );

class CNewFrame
{
public:
	static int __thiscall CNewFrame::CNewUIWindowMenuPos(DWORD* This, int a2, int a3);
	static int __thiscall CUIControlSetPosition(int This, int a2, int a3);
	static int __thiscall CNewUIMyInventory(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIGuildInfoWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUICharacterInfoWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUICommandWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUICastleWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIGuardWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIGatemanWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIGateSwitchWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIGuildMakeWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIMyQuestInfoWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIPartyInfoWindow(int thisa, int PosX, int PosY);
	static int __thiscall CNewUINPCQuest(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIEnterBloodCastle(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIEnterDevilSquare(int thisa, int PosX, int PosY);
	static int __thiscall FixEventTime(DWORD* This, int a2, int a3);
	static int __thiscall BtnIllus(char* thisa, int X, int Y, int Width, int Height);
	static int __thiscall CUILetterWriteWindow(int thisa, int a1, int PosX, int PosY, const char* a5, int a6, char a7);
	static int __thiscall CNewUIMessageBoxBaseCreate(int thisa, int x, int y, int width, int height, float fPriority);

	void InitFrameOpenGL();
	static int __thiscall CNewUIMainPaintFont(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin);
	static int __thiscall FixTextXY(int thisa, int PosX, int PosY, LPCTSTR Text, int nCount, int nTabPositions, int lpnTabStopPositions, int nTabOrigin);
	static int __thiscall CNewUIMainFrameView(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIMainFrameOpenExt(int thisa, int PosX, int PosY);
	//==

	//--
	static int __thiscall CNewUIMainInfoButtonGens(char *thisa, int X, int Y, int Width, int Height);
	static int __thiscall CNewUIMainFrameOpenTrade(int thisa, int PosX, int PosY, int Ext);
	static BYTE * __thiscall CNewUIMainFrameOpenBaultExt(int thisa, int PosX, int PosY);
	static int __thiscall CNewUIMainFrameOpenBault(int thisa, int PosX, int PosY, int Ext);
	static int __thiscall CNewUIMainFrameOpenLucky(int thisa, int PosX, int PosY, int Ext);
	static int __thiscall CNewUIMainFrameOpenOtherStore(int thisa, int PosX, int PosY, int Ext);
	static int __thiscall CNewUIMainFrameOpenStore(int thisa, int PosX, int PosY, int Ext);
	static int __thiscall CNewUIMainFrameOpenChaos(int thisa, int PosX, int PosY, int Ext);
	static BYTE * __thiscall CNewUIMainFrameOpenShop(int thisa, int PosX, int PosY, int Ext);
	//--
	static BYTE __thiscall FrameShopDisplay(int thisa, int a2, int x, int y);
	static int __thiscall GetDisplayPosX(BYTE * thisa);
	static BYTE __thiscall FrameHelperDisplay(int thisa, int a2, int x, int y);
public:
	int DisplayWin; // eax@1
	int DisplayHeight; // eax@1
	int DisplayWinMid; // eax@2
	int DisplayWinExt; // ST50_4@02
	int DisplayHeightExt; // ST50_4@02
	float DisplayWinReal; // eax@3
	int DisplayWinCDepthBox; // eax@4
};
extern CNewFrame QTFrame;
