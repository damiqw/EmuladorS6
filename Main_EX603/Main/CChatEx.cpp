#include "stdafx.h"

#include "TMemory.h"
#include "Util.h"
#include "Offset.h"
#include "CChatEx.h"
#include "ChatExpanded.h"
#include "Common.h"
#include "WideScreen.h"

CNewUIChat gCChatEx;
int upgradeActiveChat = GetPrivateProfileIntA("Interface", "ActiveChatUpgrade", 1, "./Settings.ini");
void CNewUIChat::LoadImages()
{

	//
	((void(__cdecl*)())0x00785650)();
}

static DWORD chatReader = 0;
bool tecla;

void CNewUIChat::RenderFrame(int This) {
	gCChatEx.Hide1Teste();
	if (gInterface.CheckWindow(ChatWindow) && pCursorX > 0 && pCursorX < 19 && pCursorY > QTFrame.DisplayHeightExt + 11 + 380 && pCursorY < QTFrame.DisplayHeightExt + 11 + 400) {
		pSetCursorFocus = true;
	}
	else {
		pSetCursorFocus = false;
	}
	int Button;

	RenderBitmap(51529, 16, QTFrame.DisplayHeightExt + 11 + 371, 250, 47, 0, 0, 1.0, 0.73, 1, 1, 0.0);
	if (tecla == false) {
		RenderBitmap(51541, 16, QTFrame.DisplayHeightExt + 11 + 371, 250, 47, 0, 0, 1.0, 0.73, 1, 1, 0.0);
		Button = 51542;
	}
	else {
		RenderBitmap(51522, 16, QTFrame.DisplayHeightExt + 11 + 371, 250, 47, 0, 0, 1.0, 0.73, 1, 1, 0.0);
		Button = 51544;
	}
	gInterface.DrawButton(ButtonHideChat, 1, 382, 0.0, 0.0);
	if (pCursorX > 2 && pCursorX < 17 && pCursorY > QTFrame.DisplayHeightExt + 11 + 382 && pCursorY < QTFrame.DisplayHeightExt + 11 + 398 && tecla == false) {
		Button = 51543;
	}
	if (pCursorX > 2 && pCursorX < 17 && pCursorY > QTFrame.DisplayHeightExt + 11 + 382 && pCursorY < QTFrame.DisplayHeightExt + 11 + 398 && (GetKeyState(VK_LBUTTON) & 0x100) != 0) {
		Button = 51544;
		PlayBuffer(25, 0, 0);
		keybd_event(VK_LBUTTON, 0, KEYEVENTF_KEYUP, 0);
		if (tecla == false) {
			tecla = true;
		}
		else {
			tecla = false;
		}
	}
	RenderBitmap(Button, 1, QTFrame.DisplayHeightExt + 11 + 382, 15, 15, 0, 0, 0.92, 0.92, 1, 1, 0.0);
}

void CNewUIChat::RenderButtons01(DWORD a1, float a2, float a3, float a4, float a5) {
	if (tecla == false) {
		if (pWinWidth <= 800) {
			RenderBitmap(a1 + 20250, a2 + 1.5, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 17, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "All");
			gInterface.DrawFormat(CGris, 44, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Party");
			gInterface.DrawFormat(CGris, 71, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Guild");
			gInterface.DrawFormat(CGris, 98, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Gens");
			gInterface.DrawFormat(CGris, 126.5, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Whisp");
			gInterface.DrawFormat(CGris, 154, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Sys");
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chat");
		}
		if (pWinWidth > 800) {
			RenderBitmap(a1 + 20250, a2 + 1.5, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 17, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "General");
			gInterface.DrawFormat(CGris, 44, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Party");
			gInterface.DrawFormat(CGris, 71, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Guild");
			gInterface.DrawFormat(CGris, 98, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Gens");
			gInterface.DrawFormat(CGris, 126.5, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Whisper");
			gInterface.DrawFormat(CGris, 154, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "System");
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chatting");
		}
	}
	else {
		//None
	}
}

void CNewUIChat::RenderButtons02(DWORD a1, float a2, float a3, float a4, float a5) {
	if (tecla == false) {
		if (pWinWidth <= 800) {
			RenderBitmap(a1 + 20246, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 126.5, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Whisp");
		}
		if (pWinWidth > 800) {
			RenderBitmap(a1 + 20246, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 126.5, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Whisper");
		}
	}
	else {
		//None
	}
}

void CNewUIChat::RenderButtons03(DWORD a1, float a2, float a3, float a4, float a5) {
	if (tecla == false) {
		if (pWinWidth <= 800) {
			RenderBitmap(a1 + 20244, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chat");
		}
		if (pWinWidth > 800) {
			RenderBitmap(a1 + 20244, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chatting");
		}
	}
	else {
		//None
	}
}

void CNewUIChat::RenderButtons04(DWORD a1, float a2, float a3, float a4, float a5) {
	if (tecla == false) {
		if (pWinWidth <= 800) {
			RenderBitmap(a1 + 20245, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 154, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Sys");
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chat");
		}
		if (pWinWidth > 800) {
			RenderBitmap(a1 + 20245, a2 - 3.0, a3 + 12.0, 27.5, 14.0, 0, 0, 0.8700000048, 0.9, 1, 1, 0.0);
			gInterface.DrawFormat(CGris, 154, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "System");
			gInterface.DrawFormat(CGris, 180, QTFrame.DisplayHeightExt + 11 + 385, 27.5, 3, "Chatting");
		}
	}
	else {
		//None
	}
}

void CNewUIChat::RenderButtons05(DWORD a1, float a2, float a3, float a4, float a5) {
	if (tecla == false) {
		RenderBitmap(a1 + 20251, a2 - 1.5, a3 + 12.0, 16.0, 14.0, 0, 0, 1.0, 0.9, 1, 1, 0.0);
		//RenderBitmap(51900, 16, 371, 250, 47, 0, 0, 1.0, 0.73, 1, 1, 0.0);
	}
	else {
		//None
	}
}

__declspec(naked) void RenderButtons06()
{
	static DWORD RenderButtons06_buff = 0x00785CD2;
	static DWORD CALL01 = 0x00779350;
	static DWORD CALL02 = 0x00779410;
	_asm
	{
		PUSH EBP
		MOV EBP, ESP
		PUSH ECX
		MOV DWORD PTR SS : [EBP - 0x4] , ECX
		PUSH 0
		PUSH 0
		PUSH 0
		PUSH 51539//<<ID Textura
		PUSH 1
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		ADD ECX, 0x78
		CALL CALL01
		PUSH 15//<<Alto Textura
		PUSH 16//<<Ancho Textura
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV ECX, DWORD PTR DS : [EAX + 0x18]
		ADD ECX, 12//<<Y
		PUSH ECX
		MOV EDX, DWORD PTR SS : [EBP - 0x4]
		MOV EAX, DWORD PTR DS : [EDX + 0x14]
		ADD EAX, 214//<<X
		PUSH EAX
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		ADD ECX, 0x78
		CALL CALL02
		PUSH 0
		PUSH 0
		PUSH 0
		PUSH 51540//<<ID Textura
		PUSH 1
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		ADD ECX, 0x124
		CALL CALL01
		PUSH 15//<<Alto Textura
		PUSH 16//<<Ancho Textura
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		MOV EDX, DWORD PTR DS : [ECX + 0x18]
		ADD EDX, 12//<<Y
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x4]
		MOV ECX, DWORD PTR DS : [EAX + 0x14]
		ADD ECX, 230//<<X
		PUSH ECX
		MOV ECX, DWORD PTR SS : [EBP - 0x4]
		ADD ECX, 0x124
		CALL CALL02
		jmp[RenderButtons06_buff]
	}
}

//////////////////////////////Prueba del boton HIDE(No tiene ninguna funcion.. solamente estetico en este codigo xD)//////////////////////////////
					//////////////////////////////En la version original esconde los botones//////////////////////////////

void CNewUIChat::ButtonHide01()
{
	int Button;
	gInterface.DrawButton(ButtonHideChat, 1, 382, 0.0, 0.0);
	Button = 51542;
	if (gInterface.IsWorkZone(ButtonHideChat))
	{
		Button = 51543;
	}
	if (gInterface.Data[ButtonHideChat].OnClick)
	{
		Button = 51544;
		PlayBuffer(25, 0, 0);
	}
	RenderBitmap(Button, 1, QTFrame.DisplayHeightExt + 11382, 15, 15, 0, 0, 0.92, 0.92, 1, 1, 0.0);
}

bool CNewUIChat::ButtonHide02(DWORD Event)
{
	DWORD CurrentTick = GetTickCount();
	// ----
	if (*(DWORD*)(MAIN_SCREEN_STATE) != ObjState::GameProcess)
	{
		return false;
	}
	// ----
	if (gInterface.IsWorkZone(ButtonHideChat))
	{
		DWORD Delay = (CurrentTick - gInterface.Data[ButtonHideChat].EventTick);
		// ----
		if (Event == WM_LBUTTONDOWN)
		{
			gInterface.Data[ButtonHideChat].OnClick = true;
			return true;
		}
		// ----
		gInterface.Data[ButtonHideChat].OnClick = false;
		// ----
		if (Delay < 500)
		{
			return false;
		}
		// ----
		gInterface.Data[ButtonHideChat].EventTick = GetTickCount();
		// ----
	}
}

void CNewUIChat::Hide1Teste() {
	if (tecla == false) {
		SetByte(0x00786150, 0x55);
	}
	else {
		SetByte(0x00786150, 0xC3);
	}
}

//----- (007889B0) --------------------------------------------------------
char ChatWindowsDraw(MUChat* This) {

	This->WindowPosY = QTFrame.DisplayHeightExt + 11 + 378;
	static int BWindowPosY = 323 + QTFrame.DisplayHeightExt;
	static int BWindowPosY1 = 278 + QTFrame.DisplayHeightExt;
	static int BWindowPosY2 = 233 + QTFrame.DisplayHeightExt;
	static int BWindowPosY3 = 188 + QTFrame.DisplayHeightExt;
	static int BWindowPosY4 = 143 + QTFrame.DisplayHeightExt;
	if (This->WindowsActivo) {
		chatReader = 10;
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, This->AlphaColor);
		if (This->WindowHeight_ == 55) {
			pDrawButton(51545, This->WindowPosX, BWindowPosY, (float)This->WindowWidth_, 55.0f, 0, 0);
		}
		if (This->WindowHeight_ == 100) {
			pDrawButton(51545, This->WindowPosX, BWindowPosY1, (float)This->WindowWidth_, 100.0f, 0, 0);
		}
		if (This->WindowHeight_ == 145) {
			pDrawButton(51545, This->WindowPosX, BWindowPosY2, (float)This->WindowWidth_, 145.0f, 0, 0);
		}
		if (This->WindowHeight_ == 190) {
			pDrawButton(51545, This->WindowPosX, BWindowPosY3, (float)This->WindowWidth_, 190.0f, 0, 0);
		}
		if (This->WindowHeight_ == 235) {
			pDrawButton(51545, This->WindowPosX, BWindowPosY4, (float)This->WindowWidth_, 255.0f, 0, 0);
		}
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
	}
	else {
		if (upgradeActiveChat == 1) {
			chatReader = 10;
			pSetBlend(true);
			glColor4f(1.0, 1.0, 1.0, 0.5);
			pDrawButton(51545, This->WindowPosX, BWindowPosY1, 260.0f, 100.0f, 0, 0);
			pGLSwitchBlend();
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
			pSetBlend(false);
		}
		else {
			chatReader = 0;
		}
	}
	return 1;
}

//----- (00789110) --------------------------------------------------------
char RenderFrameChat(MUChat* This) {
	float v4; // ST30_4@5
	float v5; // ST2C_4@5
	float v6; // ST28_4@5
	float v7; // ST20_4@7
	int i; // [sp+38h] [bp-Ch]@5
	float v16; // [sp+3Ch] [bp-8h]@2
	if (This->WindowsActivo) {
		v16 = (double)(This->WindowPosY - This->WindowHeight_);
		v4 = v16 - 19.0;
		//
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, 0.8);
		pDrawGUI(31275, (float)This->WindowPosX, v4, (float)This->WindowWidth_, 19.0f);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		//
		v5 = v16 + 7.0;
		//-- boton flecha arriba
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		pDrawGUI(51552, 2.0f, v5 - 8.0f, 7.0f, 7.0f);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		//-- scroll flecha arriba
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		pDrawGUI(31270, 2.0f, v5, 7.0f, 3.0f);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		//
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		for (int i = 0; i < This->WindowLineCount; ++i) {
			v7 = v16 + 9.0 + (double)(15 * i + 3);
			pDrawGUI(31271, 2.0f, v7 - 2.0f, 7.0, 15.0f);
		}
		//
		v6 = This->WindowPosY - 7;
		//-- scroll flecha abajo
		pDrawGUI(31272, 2.0f, v6 - 4, 7.0, 3.0);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
		//-- boton flecha abajo
		pSetBlend(true);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		pDrawGUI(51551, 2.0f, v6, 7.0f, 7.0f);
		pGLSwitchBlend();
		pGLSwitch();
		glColor3f(1.0, 1.0, 1.0);
		pSetBlend(false);
	}
	return 1;
}
bool IsActive = true;
__declspec(naked) void DrawMessageSystem()
{
	static DWORD ChangeMove = 4;
	static DWORD Buffer_warp = 0x007890ED;
	static DWORD CALL_MAIN1 = 0x0078C030;
	static DWORD CALL_MAIN2 = 0x00402880;
	static DWORD CALL_MAIN3 = 0x0041FE10;

	ChangeMove = chatReader;

	if (IsActive == false)
	{
		_asm
		{
			PUSH 0
			PUSH 1
			PUSH 0
			PUSH 0
			MOV ECX, DWORD PTR SS : [EBP - 0x2C]
			CALL CALL_MAIN1
			MOV ECX, EAX
			CALL CALL_MAIN2
			PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 0x34]
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x38]
			ADD EDX, ChangeMove
			PUSH EDX
			CALL CALL_MAIN3
			MOV ECX, EAX; |
			JMP[Buffer_warp]
		}
	}
	else
	{
		_asm
		{
			PUSH 0
			PUSH 1
			PUSH 0
			PUSH 0
			MOV ECX, DWORD PTR SS : [EBP - 0x2C]
			CALL CALL_MAIN1
			MOV ECX, EAX
			CALL CALL_MAIN2
			PUSH EAX
			MOV ECX, DWORD PTR SS : [EBP - 0x34]
			PUSH ECX
			MOV EDX, DWORD PTR SS : [EBP - 0x38]
			MOV EDX, 0x5
			PUSH EDX
			CALL CALL_MAIN3
			MOV ECX, EAX; |
			JMP[Buffer_warp]
		}
	}
}

__declspec(naked) void DrawMessageChat()
{
	static DWORD ChangeMove = 4;
	static DWORD Buffer_warp = 0x007890A4;
	static DWORD CALL_MAIN1 = 0x00402880;
	static DWORD CALL_MAIN2 = 0x0041FE10;

	ChangeMove = chatReader;

	_asm
	{
		PUSH 0
		PUSH 1
		PUSH 0
		PUSH 0
		LEA ECX, DWORD PTR SS : [EBP - 0x54]
		CALL CALL_MAIN1
		PUSH EAX
		MOV EDX, DWORD PTR SS : [EBP - 0x34]
		PUSH EDX
		MOV EAX, DWORD PTR SS : [EBP - 0x38]
		ADD EAX, ChangeMove
		PUSH EAX
		CALL CALL_MAIN2
		MOV ECX, EAX; |
		JMP[Buffer_warp]
	}
}

_declspec(naked) void WisperBarSizeMove()
{
	static float D2B828 = 17.00000;
	static float D4383C = 47.00000;
	static DWORD WhisperTxt_buf2f = 0x00787744;

	_asm
	{
		FLD DWORD PTR DS : [D2B828]
		FSTP DWORD PTR SS : [ESP]
		PUSH ECX
		FLD DWORD PTR DS : [D4383C]
		FSTP DWORD PTR SS : [ESP]
		MOV ECX, DWORD PTR SS : [EBP - 0x24]
		MOV EDX, DWORD PTR DS : [ECX + 0x18]
		ADD EDX, 0x1C
		MOV DWORD PTR SS : [EBP - 0x28] , EDX
		FILD DWORD PTR SS : [EBP - 0x28]
		PUSH ECX
		FSTP DWORD PTR SS : [ESP]
		MOV EAX, DWORD PTR SS : [EBP - 0x24]
		MOV ECX, DWORD PTR DS : [EAX + 0x14]
		ADD ECX, 2
		MOV DWORD PTR SS : [EBP - 0x2C] , ECX
		FILD DWORD PTR SS : [EBP - 0x2C]
		JMP[WhisperTxt_buf2f]
	}
}
//-- (00787BA0) //-- ChatInput
double sub_787BA0()
{
	return 15.199999809;
}

void CNewUIChat::Load()
{
	//SetCompleteHook(0xE9, 0x00789084, &DrawMessageChat);
	//SetCompleteHook(0xE9, 0x007890C6, &DrawMessageSystem);
	//SetCompleteHook(0xE8, 0x0078B0CF, &RenderFrameChat);
	SetCompleteHook(0xE9, 0x0078770E, &WisperBarSizeMove);
	SetCompleteHook(0xE8, 0x0078B09A, &ChatWindowsDraw);

	gInterface.BindObject(ButtonHideChat, 51522, 15, 15, -1, -1);

	SetDword((PVOID)(0x0085A426), WS_WIN_HEIGHTADD + 370);//<-PosicionY del Chat_Back
	SetByte((PVOID)(0x0085A42B), 15);//<-PosicionX del Chat_Back
	SetByte((PVOID)(0x00785965), 52);//<-PosicionX del Texto Chat

	SetCompleteHook(0xE8, 0x00785B32, this->LoadImages);
	SetCompleteHook(0xE8, 0x00787620, this->RenderFrame);
	SetCompleteHook(0xE8, 0x007877FE, this->RenderButtons01);
	SetCompleteHook(0xE8, 0x00787847, this->RenderButtons02);
	SetCompleteHook(0xE8, 0x00787893, this->RenderButtons03);
	SetCompleteHook(0xE8, 0x007878DE, this->RenderButtons04);
	SetCompleteHook(0xE8, 0x00787931, this->RenderButtons05);
	SetByte((PVOID)(0x0078649D + 1), 16);//<-AnchoBotonChat_ButtonWBack
	SetOp((LPVOID)0x00785C50, (LPVOID)RenderButtons06, ASM::JMP);
	//MemorySet(0x007877B0, 0x90, 0x1A9);//Elimina lso botones
	MemorySet(0x00787630, 0x90, 0x5);//Elimina el Texto arriba de lso botones
	SetCompleteHook(0xE9, 0x00787BA0, &sub_787BA0); //-- ChatInput
}
