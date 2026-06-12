#include "stdafx.h"
#include "Interface.h"
#include "Defines.h"
#include <process.h>
#include <time.h>
#include "User.h"
#include "Util.h"
#include "TMemory.h"
#include "CustomBuffIcon.h"
#include "Import.h"
#include "Protect.h"

BuffIcon gIconBuff;

BuffIcon::BuffIcon()
{
	this->LoadBuffCount = 0;
	this->UserBuffCount = 0;
	this->CUSTOM_BUFFICON = true;
	ZeroMemory(&RenderInfoBuff, sizeof(RenderInfoBuff));
	ZeroMemory(&UserBuff, sizeof(UserBuff));
	BuffEffectTRSData_ENG.clear();
	this->hThread = (HANDLE)_beginthreadex(NULL, 0, this->Timer, 0, 0, NULL);
	this->Init();
}

BuffIcon::~BuffIcon()
{

	CloseHandle(this->hThread);
}

void BuffIcon::LoadEng(RenderTooltipBuff * info){
	for(int n = 0; n < 256; n++){
		if( info[n].Index < 0 || info[n].Index > 256 ){
			return;
		}
		this->BuffEffectTRSData_ENG.insert(std::pair<int, RenderTooltipBuff>(info[n].IndexBuff,info[n]));
	}
}

void sub_777FB0(int BuffIndex, int IndexTime,float RenderX, float RenderY)
{
	tooltiparray * TooltipLine = (tooltiparray*)NewAddressData3;
	int * ColorTexto = (int*)NewAddressData1;
	int * LineWeight = (int*)NewAddressData2;
	int LineW = 0;

	bool continuar = false;

	std::map<int, RenderTooltipBuff>::iterator it;

	it = gIconBuff.BuffEffectTRSData_ENG.find(BuffIndex);
	if(it != gIconBuff.BuffEffectTRSData_ENG.end()){
		continuar = true;
	}

	if(continuar)
	{
		char Buff[256] = { 0 };
		char BuffDate[256] = { 0 };
		//--
		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;
		//--
		wsprintf(TooltipLine[LineW], "%s", it->second.NameBuff);
		ColorTexto[LineW] = 1;
		LineWeight[LineW++] = 0;
		//--
		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;

		strncpy(Buff, gIconBuff.RenderInfoBuff[BuffIndex], 200);
		
		char * Line = strtok(Buff, "/");

		while( Line != NULL )
		{
			wsprintf(TooltipLine[LineW], "%s", Line);
			ColorTexto[LineW] = 0;
			LineWeight[LineW++] = 0;

			Line = strtok(NULL, "/");
		}
		// --
		if( gIconBuff.UserBuff[IndexTime].Time > 0 )
		{
			time_t t = gIconBuff.UserBuff[IndexTime].Time;
			tm* m = gmtime(&t);
			char timerCount[254];
		
			if(m->tm_yday > 0)
			{
				wsprintf(timerCount, "%d %s %d %s %d %s %d %s", m->tm_yday, pGetTextLine(pTextLineThis, 2298), m->tm_hour, pGetTextLine(pTextLineThis, 2299), m->tm_min, pGetTextLine(pTextLineThis, 2300), m->tm_sec, pGetTextLine(pTextLineThis, 2301));
			}
			else if(m->tm_hour > 0)
			{
				wsprintf(timerCount, "%d %s %d %s %d %s", m->tm_hour, pGetTextLine(pTextLineThis, 2299), m->tm_min, pGetTextLine(pTextLineThis, 2300), m->tm_sec, pGetTextLine(pTextLineThis, 2301));
			}
			else if(m->tm_min > 0)
			{
				wsprintf(timerCount, "%d %s %d %s", m->tm_min, pGetTextLine(pTextLineThis, 2300), m->tm_sec, pGetTextLine(pTextLineThis, 2301));
			}
			else if(m->tm_sec > 0)
			{
				wsprintf(timerCount, "%d %s", m->tm_sec, pGetTextLine(pTextLineThis, 2301));
			}
			wsprintf(BuffDate, pGetTextLine(pTextLineThis, 2533), timerCount);
		}

		if(gIconBuff.UserBuff[IndexTime].Time > 0 && gIconBuff.UserBuff[IndexTime].Index != 28)
		{
			//--
			wsprintf(TooltipLine[LineW], "\n");
			ColorTexto[LineW] = 0;
			LineWeight[LineW++] = 0;
			//-
			wsprintf(TooltipLine[LineW], "%s", BuffDate);
			ColorTexto[LineW] = 6;
			LineWeight[LineW++] = 0;
		}

		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;

		pMultiLineTooltip(RenderX, RenderY, LineW, 0, 3, 0, 1);
	}
}

void BuffIcon::sub_777EB0(float XIcon, float YIcon)
{
	int BuffIndex; // [sp+38h] [bp-44h]@3
	float x; // [sp+58h] [bp-24h]@1
	float y; // [sp+5Ch] [bp-20h]@1
	int v27; // [sp+60h] [bp-1Ch]@1
	int v28; // [sp+64h] [bp-18h]@1

	int IndexTime; // [sp+68h] [bp-8h]@5
	int v8; // ST3C_4@4
	float v9; // ST4C_4@4
	float v10; // ST50_4@4
	float v11; // ST34_4@4
	float v12; // ST30_4@4

	float Height = 21;
	float Width = 15;
	float RenderW = ( 256.0f / 100) * 75;

	x = 0.0;
	y = 0.0;
	v27 = 0;
	v28 = 0;
	IndexTime = -1;

	EnableAlphaTest(1);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	
	for( IndexTime = 0 ; IndexTime < MAX_EFFECT_LIST; ++IndexTime)
	{
		if( this->UserBuff[ IndexTime ].Index == NULL )
		{
			continue;
		}

		BuffIndex = this->UserBuff[ IndexTime ].Index;

		x = XIcon + v27 * (Width + 5.0);
		y = YIcon + v28 * (Height + 5.0);

		v8 = (BuffIndex - 1) % 80;
		v9 = (double)(v8 % 10) * Width / RenderW;
		v10 = (double)(v8 / 10) * Height / RenderW;
		v11 = Height / RenderW;
		v12 = Width / RenderW;

		RenderBitmap((BuffIndex - 1) / 80 + 31725, x, y, Width, Height,  v9, v10, v12, v11, 1, 1, 0.0);

		if( BuffIndex != 28 )
		{
			int pBuffHp = 100;
	
			if(this->UserBuff[ IndexTime ].MaxTime > 0 && this->UserBuff[ IndexTime ].Time > 0)
			{
				pBuffHp = (this->UserBuff[ IndexTime ].Time * 100) / this->UserBuff[ IndexTime ].MaxTime;
			}

			pSetBlend(1);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			pDrawBarForm(x, ( y + Height ), ( Width * pBuffHp / 100.0f ), 2.0f, 0.0f, 0);
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}

		if( pCheckMouseOver((int) x, (int) y, (int) Width, (int) Height) )
		{
			sub_777FB0( BuffIndex, IndexTime, (Width / 2.0 + x), (y + Height + 10));
		}

		if ( ++v27 >= 8 )
		{
			v27 = 0;
			++v28;
		}
	}

	pGLSwitch();
	EnableAlphaTest(0);
}

void __fastcall BuffIcon::RenderIconBuff(struct_v15* This, int a2)
{
	//if (This->RenderX == 220)
	{
		//gPartyBuffs.DrawPartyBuffs();
	}

	int JCResto; // eax@1
	int JCWinWidth; // eax@1
	JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
	JCResto = JCWinWidth / 2 - 320;

	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		This->RenderX = 220 + JCResto;
	}

	gIconBuff.sub_777EB0((float)This->RenderX+50, (float)This->RenderY+10);
}

DWORD Addr_Pointer;

__declspec(naked) void LeaBuffIndex(){
	static DWORD Addr_JMP = 0x007779C4;
	static DWORD Addr_Call = 0x004C9480;
	_asm{
		LEA ECX,DWORD PTR SS:[EBP-0x4C]
		CALL Addr_Call
		MOV EDX,DWORD PTR DS:[EAX]
		MOV DWORD PTR SS:[EBP-0x44],EDX
		MOV Addr_Pointer, EDX
		JMP[Addr_JMP]
	}
}

bool pDisabledIconBuff(int x, int y, int w, int h){
	int BuffPointer; // [sp+10h] [bp-6Ch]@1
	int v27; // [sp+60h] [bp-1Ch]@1
	int v28; // [sp+64h] [bp-18h]@1
	float Height = 21;
	float Width = 15;
	BuffPointer = *(DWORD *)(GetInstance() + 200);
	v27 = 0;
	v28 = 0;
	for( int i = 0 ; i < MAX_EFFECT_LIST; ++i){
		if( gIconBuff.UserBuff[ i ].Index == NULL ){
			continue;
		}
		if( Addr_Pointer == gIconBuff.UserBuff[ i ].Index ){
			x = (double)*(signed int *)(BuffPointer + 16) + (double)v27 * (Width + 5.0);
			y = (double)*(signed int *)(BuffPointer + 20) + (double)v28 * (Height + 5.0);
			i = MAX_EFFECT_LIST;
		}
		if ( ++v27 >= 8 ){
			v27 = 0;
			++v28;
		}
	}
	return pCheckMouseOver( x, y, ( int ) Width, ( int ) Height);
}

#include "Protect.h"
void BuffIcon::Init(){
	SetCompleteHook(0xE9, 0x007779B7, &LeaBuffIndex);
	SetCompleteHook(0xE8, 0x00777A26, &pDisabledIconBuff);

    SetRange((LPVOID)0x00777C90, 5, ASM::NOP);
	SetCompleteHook(0xE8, 0x00777C9A, &this->RenderIconBuff);
}

void BuffIcon::Draw(float StartX, float StartY)
{
	float Height = ( 28.0f / 100) * 75; // ((double)(unsigned int)*(QWORD*)0x0E61E5C / 480.0); //28
	float Width = ( 20.0f / 100) * 75; // ((double)(unsigned int)*(QWORD*)0xE61E58 / 640.0); //20
	float RenderW = ( 256.0f / 100) * 75; // ((double)(unsigned int)*(QWORD*)0xE61E58 / 640.0);
	float RenderH = ( 256.0f / 100) * 75; // ((double)(unsigned int)*(QWORD*)0x0E61E5C / 480.0);

	int DataIndex = 0;
	int InfoIndex = 0;
	float InfoX = 0;
	float InfoY = 0;

	int BuffDraw = 0;

	int line = 0;

	for(int i = 0; i < MAX_EFFECT_LIST; i++)	
	{
		if(this->UserBuff[i].Index == NULL)
		{
			continue;
		}

		float X = 0;
		float Y = StartY;

		X = StartX + BuffDraw * (Width + 5.0);
		Y = StartY + line * (Height + 5.0);

		int BuffIndex = this->UserBuff[i].Index;

		int v6 = 0;

		if( BuffIndex > 0 && BuffIndex <= 80)
		{
			v6 = (BuffIndex - 1) % 80;
		}
		else if (BuffIndex > 80 && BuffIndex <= 160)
		{
			v6 = (BuffIndex - 81) % 80;
		}
		else
		{
			v6 = (BuffIndex - 161) % 80;
		}

		float CritX = (double)(v6 % 10) * (Width) / RenderW;
		float CritY = (double)(v6 / 10) * (Height) / RenderH;

		int EffectValue = (BuffIndex - 1) % 80;
		float SourceX = (double)(EffectValue % 10) * Width / RenderW;
		float SourceY = (double)(EffectValue / 10) * Height / RenderH;
		float SourceWidth = Width / RenderW;
		float SourceHeight = Height / RenderH;
		pDrawCircle((BuffIndex - 1) / 80 + 31725, X, Y, Width, Height, SourceX, SourceY, SourceWidth, SourceHeight, 1, 1, 0);

		float LineX = X; // 640 * X / pWinWidth;
		float LineY =  Y + Height;	/* 480 * (Y + High) / pWinHeight;*/

		float LineWind = Width;// 640 * Whith / pWinWidth ;

		if(this->UserBuff[i].Index != 28)
		{
			int pBuffHp = 100;
	
			if(this->UserBuff[i].MaxTime > 0 && this->UserBuff[i].Time > 0)
			{
				pBuffHp = (this->UserBuff[i].Time * 100) / this->UserBuff[i].MaxTime;
			}

			pSetBlend(1);
			glColor4f(0.0, 1.0, 0.0, 1.0);
			pDrawBarForm(LineX, LineY, LineWind * pBuffHp / 100.0f, 2.0f, 0.0f, 0);
			pGLSwitchBlend();
			pGLSwitch();
			glColor3f(1.0, 1.0, 1.0);
		}
		
		if(gInterface.IsWorkZone(X, Y, X + Width, Y + Height))
		{
			DataIndex = this->UserBuff[i].Index;
			InfoIndex = i;
			InfoX = X;
			InfoY = Y;
		}

		BuffDraw++;
		if (BuffDraw>=8)
		{
			line=1;
			BuffDraw=0;
		}
	}

	if(gInterface.IsWorkZone(InfoX, InfoY, InfoX + Width, InfoY + Height))
	{
		pSetBlend(true);

		int DrawInfoX = InfoX;
		int DrawInfoY = InfoY + 33;

		this->DrawBuffInfo(DataIndex, InfoIndex, DrawInfoX, DrawInfoY,line);
	}

	pSetBlend(false);
}

void BuffIcon::DrawBuffInfo(int BuffIndex, int InfoIndex, float iX, float iY, int line)
{
	tooltiparray * TooltipLine = (tooltiparray*)NewAddressData3;
	int * ColorTexto = (int*)NewAddressData1;
	int * LineWeight = (int*)NewAddressData2;
	int LineW = 0;

	bool continuar = false;

	std::map<int, RenderTooltipBuff>::iterator it;

	it = this->BuffEffectTRSData_ENG.find(BuffIndex);
	if(it != this->BuffEffectTRSData_ENG.end()){
		continuar = true;
	}

	if(continuar)
	{
		char Buff[256] = { 0 };
		char BuffDate[256] = { 0 };
		//--
		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;
		//--
		wsprintf(TooltipLine[LineW], "%s", it->second.NameBuff);
		ColorTexto[LineW] = 1;
		LineWeight[LineW++] = 0;
		//--
		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;

		strncpy(Buff, RenderInfoBuff[BuffIndex], 200);
		
		char * Line = strtok(Buff, "/");

		while( Line != NULL )
		{
			wsprintf(TooltipLine[LineW], "%s", Line);
			ColorTexto[LineW] = 0;
			LineWeight[LineW++] = 0;

			Line = strtok(NULL, "/");
		}
		// --
		if(this->UserBuff[InfoIndex].Time > 0)
		{
			time_t t = UserBuff[InfoIndex].Time;
			tm* m = gmtime(&t);
			char timerCount[254];
		
			if(m->tm_yday > 0)
			{
				wsprintf(timerCount, "%d %s %d %s %d %s %d %s", m->tm_yday, pGetTextLine(pTextThis(), 2298), m->tm_hour, pGetTextLine(pTextThis(), 2299), m->tm_min, pGetTextLine(pTextThis(), 2300), m->tm_sec, pGetTextLine(pTextThis(), 2301));
			}
			else if(m->tm_hour > 0)
			{
				wsprintf(timerCount, "%d %s %d %s %d %s", m->tm_hour, pGetTextLine(pTextThis(), 2299), m->tm_min, pGetTextLine(pTextThis(), 2300), m->tm_sec, pGetTextLine(pTextThis(), 2301));
			}
			else if(m->tm_min > 0)
			{
				wsprintf(timerCount, "%d %s %d %s", m->tm_min, pGetTextLine(pTextThis(), 2300), m->tm_sec, pGetTextLine(pTextThis(), 2301));
			}
			else if(m->tm_sec > 0)
			{
				wsprintf(timerCount, "%d %s", m->tm_sec, pGetTextLine(pTextThis(), 2301));
			}

			wsprintf(BuffDate, pGetTextLine(pTextThis(), 3039), timerCount);
		}

		// -----
		if(this->UserBuff[InfoIndex].Time > 0 && this->UserBuff[InfoIndex].Index != 28)
		{
			//--
			wsprintf(TooltipLine[LineW], "\n");
			ColorTexto[LineW] = 0;
			LineWeight[LineW++] = 0;
			//-
			wsprintf(TooltipLine[LineW], "%s", BuffDate);
			ColorTexto[LineW] = 6;
			LineWeight[LineW++] = 0;
		}

		wsprintf(TooltipLine[LineW], "\n");
		ColorTexto[LineW] = 0;
		LineWeight[LineW++] = 0;

		pMultiLineTooltip(iX + 10, iY, LineW, 0, 3, 0, 1);
	}
}

unsigned int BuffIcon::Timer(void *Args)
{
	while(true)
	{
		for(int i = 0; i < MAX_EFFECT_LIST; i++)
		{
			if(gIconBuff.UserBuff[i].Index != NULL)
			{
				if(gIconBuff.UserBuff[i].Time > 0)
				{
					gIconBuff.UserBuff[i].Time--;
					if(gIconBuff.UserBuff[i].Time <= 0)
					{
						gIconBuff.UserBuff[i].Index = NULL;
						gIconBuff.UserBuff[i].Time = 0;

						gIconBuff.UserBuffCount--;
					}
				}
			}

			Sleep(1);
		}

		Sleep(999);
	}	

	return 0;
}

void BuffIcon::Recv(PMSG_SEND_BUFF_ICON* DataRecv)
{
	if(DataRecv->state == 0 && DataRecv->effect > 0 )
	{
		for( int i = 0; i < MAX_EFFECT_LIST; i++ )
		{
			if(this->UserBuff[i].Index == NULL || this->UserBuff[i].Index == DataRecv->effect)
			{
				if(this->UserBuff[i].Index == NULL)
				{
					this->UserBuffCount++;
				}
				this->UserBuff[i].Index = DataRecv->effect;
				this->UserBuff[i].Time = DataRecv->time;
				this->UserBuff[i].MaxTime = DataRecv->time;
				return;
			}
		}
	}
	else
	{
		for( int i = 0; i < MAX_EFFECT_LIST; i++ )
		{
			if(this->UserBuff[i].Index == DataRecv->effect)
			{
				this->UserBuff[i].Index = NULL;
				this->UserBuff[i].Time = 0;
				this->UserBuff[i].MaxTime = 0;

				this->UserBuffCount--;
				return;
			}
		}
	}
}

void BuffIcon::DeleteAllBuff()
{
	this->UserBuffCount = 0;
	for( int i = 0; i < MAX_EFFECT_LIST; i++ )
	{
		this->UserBuff[i].Index = NULL;
		this->UserBuff[i].Time = 0;
		this->UserBuff[i].MaxTime = 0;
	}
}

void BuffIcon::GC_BuffInfo(PMSG_SEND_BUFF_ICON_EX* aRecv)
{
	int BuffIndex = aRecv->btEffectIndex;

	bool continuar = false;

	std::map<int, RenderTooltipBuff>::iterator it;

	it = this->BuffEffectTRSData_ENG.find(BuffIndex);
	if(it != this->BuffEffectTRSData_ENG.end()){
		continuar = true;
	}

	if(continuar == true)
	{
		switch(BuffIndex)
		{
		case EFFECT_GREATER_DAMAGE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_DEFENSE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELF_BUFFER:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff,
					aRecv->iValue[0],aRecv->iValue[0],aRecv->iValue[0],aRecv->iValue[1]);
			}
			break;
		case EFFECT_MANA_SHIELD:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_INFINITY_ARROW:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BP_RECOVERY:
			break;
		case EFFECT_GREATER_LIFE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_MANA:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLESS_POTION:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SOUL_POTION:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff
					, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[1]);

			}
			break;
		case EFFECT_DISABLE_MAGIC:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CASTLE_GATE_STATE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GUILD_STATE1:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GUILD_STATE2:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GUILD_STATE3:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GUILD_STATE4:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_INVISIBILITY:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GUILD_STATE5:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CASTLE_CROWN_STATE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE1:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE2:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE3:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE4:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE5:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE6:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE7:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GAME_MASTER:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SEAL_OF_ASCENSION1:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_WEALTH1:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_SEAL_OF_SUSTENANCE1:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ORDER_OF_SPEED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ORDER_OF_SUBLIMATION:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ORDER_OF_PROTECTION:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN1:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN2:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN3:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN4:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_HALLOWEEN5:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_ASCENSION2:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SEAL_OF_WEALTH2:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_SEAL_OF_SUSTENANCE2:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SEAL_OF_MOVEMENT:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SCROLL_OF_QUICK:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_DEFENSE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_DAMAGE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_MAGIC_DAMAGE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_LIFE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SCROLL_OF_MANA:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_STRENGTH:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_DEXTERITY:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_VITALITY:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_ENERGY:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_ELIXIR_OF_LEADERSHIP:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_POISON:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ICE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ICE_ARROW:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_FIRE_SLASH:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_PHYSI_DAMAGE_IMMUNITY:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MAGIC_DAMAGE_IMMUNITY:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_STERN:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MAGIC_DEFENSE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MONSTER_PHYSI_DAMAGE_IMMUNITY:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MONSTER_MAGIC_DAMAGE_IMMUNITY:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ORDER_OF_RESTRAINT:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE8:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE9:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE10:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE11:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CRYWOLF_STATE12:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_DAMAGE_REFLECT:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SLEEP:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BLIND:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_NEIL:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SAHAMUTT:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_LESSER_DAMAGE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DEFENSE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM1:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM2:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHERRY_BLOSSOM3:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SWORD_POWER:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff
					, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2], aRecv->iValue[3]);
			}
			break;
		case EFFECT_MAGIC_CIRCLE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_SWORD_SLASH:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_LIGHTNING_STORM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_RED_STORM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_FROZEN_STAB:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_SEAL_OF_LIFE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_SEAL_OF_MANA:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_SCROLL_OF_BATTLE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_STRENGTH:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS1:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff
					, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_CHRISTMAS2:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS3:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS4:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff
					, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS5:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS6:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_CHRISTMAS7:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_DUEL_ARENA_WATCH:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_TALISMAN_OF_GUARDIAN:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_TALISMAN_OF_PROTECTION:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MASTER_SEAL_OF_ASCENSION:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_MASTER_SEAL_OF_WEALTH:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0],aRecv->iValue[1]);
			}
			break;
		case EFFECT_GLADIATORS_GLORY:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_PARTY_EXPERIENCE_BONUS:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0],aRecv->iValue[1],aRecv->iValue[2]);
			}
			break;
		case EFFECT_MAX_AG_BOOST_AURA:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_MAX_SD_BOOST_AURA:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_SCROLL_OF_HEALING:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddHPRecoveryRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[1];
			break;
		case EFFECT_HAWK_FIGURINE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddCriticalDamageRate += lpEffect->m_value[0];
			break;
		case EFFECT_GOAT_FIGURINE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExcellentDamageRate += lpEffect->m_value[0];
			break;
		case EFFECT_OAK_CHARM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[0];
			break;
		case EFFECT_MAPLE_CHARM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxMP += lpEffect->m_value[0];
			break;
		case EFFECT_GOLDEN_OAK_CHARM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMaxSD += lpEffect->m_value[1];
			break;
		case EFFECT_GOLDEN_MAPLE_CHARM:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxMP += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMaxBP += lpEffect->m_value[1];
			break;
		case EFFECT_WORN_HORSESHOE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddItemDropRate += lpEffect->m_value[0];
			break;
		case EFFECT_GREATER_IGNORE_DEFENSE_RATE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			//lpObj->EffectOption.AddIgnoreDefenseRate += lpEffect->m_value[0];
			break;
		case EFFECT_FITNESS:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			//lpObj->EffectOption.AddVitality += lpEffect->m_value[0];
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			//lpObj->EffectOption.AddDefenseSuccessRate += lpEffect->m_value[0];
			break;
		case EFFECT_IRON_DEFENSE:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[0];
			//lpObj->EffectOption.AddDefense += lpEffect->m_value[1];
			break;
		case EFFECT_GREATER_LIFE_ENHANCED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			//lpObj->EffectOption.MulMaxHP += lpEffect->m_value[0];
			//lpObj->EffectOption.MulMaxMP += lpEffect->m_value[1];
			break;
		case EFFECT_GREATER_LIFE_MASTERED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2]);
			}
			//lpObj->EffectOption.MulMaxHP += lpEffect->m_value[0];
			//lpObj->EffectOption.MulMaxMP += lpEffect->m_value[1];
			//lpObj->EffectOption.MulMaxBP += lpEffect->m_value[2];
			break;
		case EFFECT_DEATH_STAB_ENHANCED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_MAGIC_CIRCLE_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_MAGIC_CIRCLE_ENHANCED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2]);
			}
			break;
		case EFFECT_MANA_SHIELD_MASTERED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_FROZEN_STAB_MASTERED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BLESS:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_INFINITY_ARROW_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_BLIND_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_DRAIN_LIFE_ENHANCED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_ICE_STORM_ENHANCED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_EARTH_PRISON:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE_MASTERED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_GREATER_CRITICAL_DAMAGE_EXTENDED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2]);
			}
			break;
		case EFFECT_SWORD_POWER_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2], aRecv->iValue[3]);
			}
			break;
		case EFFECT_SWORD_POWER_ENHANCED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2], aRecv->iValue[3]);
			}
			break;
		case EFFECT_SWORD_POWER_MASTERED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1], aRecv->iValue[2], aRecv->iValue[3]);
			}
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_GREATER_DEFENSE_SUCCESS_RATE_ENHANCED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[1]);
			}
			break;
		case EFFECT_FITNESS_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_DRAGON_ROAR_ENHANCED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_CHAIN_DRIVER_ENHANCED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_POISON_ARROW:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_POISON_ARROW_IMPROVED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BLESS_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0], aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DAMAGE_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_LESSER_DEFENSE_IMPROVED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_FIRE_SLASH_ENHANCED:
			{
				wsprintf(RenderInfoBuff[BuffIndex], it->second.InfoBuff, aRecv->iValue[0]);
			}
			break;
		case EFFECT_IRON_DEFENSE_IMPROVED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BLOOD_HOWLING:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_BLOOD_HOWLING_IMPROVED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_PENTAGRAM_JEWEL_HALF_SD:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.DivMaxSD += lpEffect->m_value[0];
			break;
		case EFFECT_PENTAGRAM_JEWEL_HALF_MP:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.DivMaxMP += lpEffect->m_value[0];
			break;
		case EFFECT_PENTAGRAM_JEWEL_HALF_SPEED:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.DivPhysiSpeed += lpEffect->m_value[0];
			//lpObj->EffectOption.DivMagicSpeed += lpEffect->m_value[0];
			break;
		case EFFECT_PENTAGRAM_JEWEL_HALF_HP:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.DivMaxHP += lpEffect->m_value[0];
			break;
		case EFFECT_PENTAGRAM_JEWEL_STUN:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_PENTAGRAM_JEWEL_SLOW:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			break;
		case EFFECT_TALISMAN_OF_ASCENSION1:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExperienceRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMasterExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_TALISMAN_OF_ASCENSION2:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExperienceRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMasterExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_TALISMAN_OF_ASCENSION3:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExperienceRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMasterExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_SEAL_OF_ASCENSION3:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SEAL_OF_ASCENSION2:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMasterExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_BLESSING_OF_LIGHT:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExperienceRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMasterExperienceRate += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_DEFENSE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddDefense += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_MAGIC_DAMAGE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMagicDamage += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_LIFE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_MANA:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddMaxMP += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_DAMAGE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddPhysiDamage += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_HEALING:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddHPRecoveryRate += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMaxHP += lpEffect->m_value[1];
			break;
		case EFFECT_MASTER_SCROLL_OF_BATTLE:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddCriticalDamageRate += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_STRENGTH:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddExcellentDamageRate += lpEffect->m_value[0];
			break;
		case EFFECT_MASTER_SCROLL_OF_QUICK:
			{
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			}
			//lpObj->EffectOption.AddPhysiSpeed += lpEffect->m_value[0];
			//lpObj->EffectOption.AddMagicSpeed += lpEffect->m_value[0];
			break;
		default:
				memcpy(RenderInfoBuff[BuffIndex], it->second.InfoBuff, 100);
			break;
		}	
	}
}