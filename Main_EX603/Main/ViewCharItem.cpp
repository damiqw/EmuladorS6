#include "stdafx.h"
#include "Object.h"
#include "Protocol.h"
#include "ViewCharItem.h"
#include "Defines.h"
#include "Import.h"
#include "TMemory.h"
#include "Util.h"
#include "Interface.h"
#include "Character.h"
#include "InterfaceElemental.h"
#include "PartyBar.h"

#if(VIEWCHARITEMS)

cViewCharItems ViewCharItems;


int equipmentI[INVENTORY_ITEMS] = { 0x7A82, 0x7A83, 0x7A7F, 0x7A84, 0x7A86, 0x7A85, 0x7A7E, 0x7A81, 0x7A80, 0x7a88, 0x7a87, 0x7a87 };
int equipmentX[INVENTORY_ITEMS] = { 15, 135, 75, 75, 75, 15, 135, 120, 15, 54, 54, 114 };
int equipmentY[INVENTORY_ITEMS] = { 87, 87, 44, 87, 150, 150, 150, 44, 44, 87, 150, 150 };
int equipmentW[INVENTORY_ITEMS] = { 46, 46, 46, 46, 46, 46, 46, 61, 46, 28, 28, 28 };
int equipmentH[INVENTORY_ITEMS] = { 66, 66, 46, 66, 46, 46, 46, 46, 46, 28, 28, 28 };

char* CharacterCode2(int a)
{
	switch (a)
	{
	case 0:  return pGetTextLine(pTextLineThis, 20);
	case 1:  return pGetTextLine(pTextLineThis, 25);
	case 2:  return pGetTextLine(pTextLineThis, 1669);
	case 3:  return pGetTextLine(pTextLineThis, 1669);
	case 16: return pGetTextLine(pTextLineThis, 21);
	case 17: return pGetTextLine(pTextLineThis, 26);
	case 18: return pGetTextLine(pTextLineThis, 1668);
	case 19: return pGetTextLine(pTextLineThis, 1668);
	case 32: return pGetTextLine(pTextLineThis, 22);
	case 33: return pGetTextLine(pTextLineThis, 27);
	case 34: return pGetTextLine(pTextLineThis, 1670);
	case 35: return pGetTextLine(pTextLineThis, 1670);
	case 48: return pGetTextLine(pTextLineThis, 23);
	case 50: return pGetTextLine(pTextLineThis, 1671);
	case 66: return pGetTextLine(pTextLineThis, 24);
	case 67: return pGetTextLine(pTextLineThis, 24);
	case 64: return pGetTextLine(pTextLineThis, 24);
	case 65: return pGetTextLine(pTextLineThis, 24);
	case 68: return pGetTextLine(pTextLineThis, 1672);
	case 80: return pGetTextLine(pTextLineThis, 1687);
	case 81: return pGetTextLine(pTextLineThis, 1688);
	case 82: return pGetTextLine(pTextLineThis, 1689);
	case 83: return pGetTextLine(pTextLineThis, 1689);
	case 96: return pGetTextLine(pTextLineThis, 3150);
	case 97: return pGetTextLine(pTextLineThis, 3151);
	case 98: return pGetTextLine(pTextLineThis, 3151);
	}
	return "unknown";
}
cViewCharItems::cViewCharItems()
{
	int i = 0;
	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		this->charItem.Item[i].ItemID = i * 512 + 1;
		this->charItem.Item[i].Level = i << 3;
		this->charItem.Item[i].ExcellentOption = i;
	}

	this->onView = false;
	this->DangXem = false;
	this->Init();
}

cViewCharItems::~cViewCharItems()
{
}

bool nInGameShopIsInGameShopRect(float _x, float _y)
{
	if (ViewCharItems.DrawItem3DCenterImage)
		return true;
	if (pCheckWindow(pWindowThis(), ObjWindow::CashShop)) //ObjWindow::CashShop = 65
		return _x >= 0 && _x < 640 && _y < 429 && _y >= 0;
	return false;
}

void cViewCharItems::Init()
{
	this->guiX = 300;
	this->guiY = 20;
	this->curX = pCursorX;
	this->curY = pCursorY;
	this->dragging = false;

	SetCompleteHook(0xE8, 0x005CF3AC, &nInGameShopIsInGameShopRect);
	ClearSession();
}

void hmmm(int a1, float a2, float a3, float a4, float a5)
{
	if (a1 != 0x7a87 && a1 != 0x7a88)
	{

		//gInterface.DrawFormat(-1, a2, a3, 100, 0, "%04X", a1);
		gInterface.DrawFormat(-1, a2, a3, 100, 0, "%.1f %.1f ", a2, a3, a4, a5);
		gInterface.DrawFormat(-1, a2 - 150, a3, 100, 0, "%.1f %.1f ", a4, a5);
	}
	//gInterface.DrawFormat(-1, a2, a3, 100, 0, "%04X ", a1, a2 - 150, a3, a4, a5);
	//pDrawGUI(a1, a2, a3, a4, a5);
}

void cViewCharItems::Load()
{
	//SetCompleteHook(0xE8, 0x008370EE, &hmmm);
}

bool cViewCharItems::IsWorkZone(WORD x, WORD y, WORD w, WORD h){
	return pCursorX >= x && pCursorX <= (x + w) && pCursorY >= y && pCursorY <= (y + h);
}

bool cViewCharItems::IsWorkZoneDebug(WORD x, WORD y, WORD w, WORD h){

	return this->IsWorkZone(x, y, w, h);
}

void cViewCharItems::DrawItem3D(float sx, float sy, float Width, float Height, int Type, int Level, int ExtOption, int Ancient, bool PickUp, float Scale, bool Center)
{
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	sub_6363D0_Addr(0, 0, *(GLsizei*)0x00E61E58, *(GLsizei*)0x00E61E5C);
	float v2 = *(float*)0x00E61E58 / *(float*)0x00E61E5C;
	sub_6358A0_Addr(Scale, v2, *(float*)0xE61E38, *(float*)0xE61E3C);
	glMatrixMode(0x1700);
	glPushMatrix();
	glLoadIdentity();
	sub_635830_Addr((LPVOID)0x87933A0);
	sub_635DE0_Addr();
	sub_635E40_Addr();

	ViewCharItems.DrawItem3DCenterImage = Center;

	pDrawItemModel(sx, sy, Width, Height, Type, Level, ExtOption, Ancient, PickUp);
	ViewCharItems.DrawItem3DCenterImage = false;

	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();

	glColor3f(1, 1, 1);
	pSetBlend(false);
	return;
}
void cViewCharItems::ClearSession()
{
	this->charItem.Result = 0;
	this->charItem.Map = 0;
	this->charItem.GuildNumber = -1;
	ZeroMemory(this->charItem.Name, sizeof(this->charItem.Name));
	memset(&this->charItem.Item,0xFF,sizeof(this->charItem.Item));
	
	ZeroMemory(this->charItem.Guild, sizeof(this->charItem.Guild));

}

bool cViewCharItems::DrawCharInfoRanking(int X, int Y,int W,int H)
{
	if (!strlen(this->charItem.Name))
	{
		return false;
	}

	//---
	bool ret = false;
	if (!this->DangXem ||
		gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(CashShop))
	{
		this->DangXem = false;
		return ret;
	}


	int Back2 = 0;

	if (pGameResolutionMode == 1)
	{
		Back2 = 0;
	}
	else if (pGameResolutionMode == 2)
	{
		Back2 = 50;
	}
	else if (pGameResolutionMode == 3)
	{
		Back2 = 100.0;
	}
	else if (pGameResolutionMode == 4)
	{
		Back2 = 100.0;
	}

	float MainWidth = W;
	float MainHeight = H;
	float StartBody = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);
	float StartY = Y;
	float StartX = X;
	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	float startX = StartX + 250;
	float startY = StartY;

	if (this->IsWorkZone(startX + 167.5, startY + 5, 15, 15) && GetKeyState(VK_LBUTTON) & 0x8000)
	{
		this->onView = false;
		this->DangXem = false;
		return true;
	}
	

	/*int c = ((int(__cdecl*)(int)) 0x57D9A0)(9999);
	if (c) {
	RenderBitmap(0x7A5A, startX, startY + 35, 190, 429.0 - 64, 0.0, 0.0, 222.f / 256.0, 250 / 256.0, 1, 1, 0.0);
	}*/
	//pDrawGUI(31322, startX, startY, 190.0, 429.0 - 220);
	//pDrawGUI(31354, startX, startY, 190.0, 64.0);
	//pDrawGUI(31355, startX, startY + 64, 21.0, 320.0 - 220);
	//pDrawGUI(31356, startX + 169, startY + 64, 21.0, 320.0 - 220);
	//pDrawGUI(31357, startX, startY + 384 - 220, 190.0, 45.0);
	//---

	//gInterface.DrawFormat(0xffffffff, startX, startY + 12, 190, 3, this->charItem.Name);

	//---
	int i = 0;
	pSetBlend(1);
	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (!((this->charItem.Class/16) == 3 && i == 2)
			&& !((this->charItem.Class/16) == 6 && i == 5)) {
			pDrawGUI(equipmentI[i], equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i]);
		}
	}
	pGLSwitch();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pSetBlend(1);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1)
		{
			//gInterface.DrawItem3D(KhungInfoX + 5, KhungInfoY - 5, ListItemWH1, ListItemWH, CTItemIndex, CTItem->Level, CTItem->ExcOption, CTItem->AncOption, 0, 1.4);//BMD MOdel
			gInterface.DrawItem3D(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i],
				this->charItem.Item[i].ItemID, this->charItem.Item[i].Level, this->charItem.Item[i].ExcellentOption, this->charItem.Item[i].AncientOption, 0,1.4,1);
		}
	}
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1 && this->IsWorkZone(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i])){
			gInterface.DrawItemToolTipText((void*)&this->charItem.Item[i], pCursorX + 25, pCursorY);
			break;
		}
	}

	//character.DrawTarget(150, 150, 150, 150);
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
	return ret || this->IsWorkZone(startX, startY, 190, 429.0 - 30);
}

#include "CustomFont.h"
/*bool cViewCharItems::DrawCharInfo()
{
	bool ret = false;
	if (!this->onView ||
		gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(CashShop))
	{
		this->onView = false;
		return ret;
	}

	if (!gInterface.Data[eMainViewChar].OnShow)
	{
		return 0;
	}

	
	
	
	float MainWidth = 315;
	float MainHeight = 220;
	float startX = 100;
	float startY = ((MAX_WIN_HEIGHT - 51) / 2) - (MainHeight / 2);

	if (!gElemental.GiaoDienCash(eMainViewChar, &startX, &startY, MainWidth, MainHeight, "Char Info"))
	{
	gElemental.gInfoBox(startX+190, startY+45, 105, 140, 0xD4966396, 0, 0);
	CustomFont.Draw(CustomFont.FontBold, startX, startY+12, 0xffffffff, 0x0, MainWidth, 0, 3, this->charItem.Name);
	if (this->charItem.GuildNumber != -1)
	{
		CustomFont.Draw(CustomFont.FontBold, startX, startY+25,0xffffffff, 0x0 , MainWidth, 0, 3, "Guild [%s]",this->charItem.Guild);
	}
	character.ViewItems(startX+150, startY, 200, 200,this->charItem.Class);
	//---
	int i = 0;
	pSetBlend(1);
	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (!((this->charItem.Class/16) == 3 && i == 2)
			&& !((this->charItem.Class/16) == 6 && i == 5)) {
			pDrawGUI(equipmentI[i], equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i]);
		}
	}
	pGLSwitch();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	pSetBlend(1);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1){
			gInterface.DrawItem3D(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i],
				this->charItem.Item[i].ItemID, this->charItem.Item[i].Level, this->charItem.Item[i].ExcellentOption, this->charItem.Item[i].AncientOption, 0, 1.3);
		}
	}
	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);

	for (i = 0; i < INVENTORY_ITEMS; ++i)
	{
		if (this->charItem.Item[i].ItemID != -1 && this->IsWorkZone(equipmentX[i] + startX, equipmentY[i] + startY, equipmentW[i], equipmentH[i])){
			gInterface.DrawItemToolTipText((void*)&this->charItem.Item[i], pCursorX + 25, pCursorY);
			break;
		}
	}

	glColor3f(1.0, 1.0, 1.0);
	pSetBlend(false);
	}


	return ret || this->IsWorkZone(startX, startY, 190, 429.0 - 30);
}*/

int cViewCharItems::CheckItemInfo(signed int a1)
{
	if (a1 > 3092)
	{
		if (a1 > 4661)
		{
			if (a1 > 5685 || a1 < 5676 && (a1 < 5164 || a1 > 5173))
				return 0;
		}
		else if (a1 < 4652 && (a1 > 4149 || a1 < 4140 && (a1 < 3628 || a1 > 3637)))
		{
			return 0;
		}

		return 1;
	}

	if (a1 >= 3089)
		return 1;

	if (a1 > 2071)
	{
		if (a1 != 2580 && (a1 <= 2589 || a1 > 2592))
			return 0;
		return 1;
	}

	if (a1 == 2071 || a1 <= 1041 && (a1 >= 1040 || a1 >= 26 && a1 <= 28))
		return 1;

	return 0;
}


void cViewCharItems::RecvInfo(PMSG_ANS_VIEW_CHAR_ITEMS * data)
{
	this->charItem.Result = data->Result;
	if (data->Result)
	{
		this->charItem.Map = data->Map;

		memcpy(&this->charItem.Guild[0], &data->Guild[0], sizeof(this->charItem.Guild));

		memcpy(&this->charItem.Name[0], &data->Name[0], 10);
		this->charItem.Class = data->Class;

		character.CreateHero(CustomObjectID::oViewCharItems, (this->charItem.Class)/16, true);
		this->Key = ((int(__cdecl*)(int)) 0x57D9A0)(CustomObjectID::oViewCharItems);
		int c = ((int(__thiscall*)(int a1, int a2)) 0x0096A4C0)(((int(*)()) 0x402BC0)(), this->Key);

		this->Rot = 45.f;
		this->Zoom = 1.f;
		DWORD dwAddress;
		int a5;
		int a6;
		int a7;
		int a8;
		int a9;
		DWORD a10;
		int i;
		for (i = 0; i < INVENTORY_ITEMS; ++i)
		{
			dwAddress = (DWORD)&this->charItem.Item[i];

			*(WORD *)dwAddress = data->Type[i];
			a5 = data->Dur[i];
			*(BYTE *)(dwAddress + 22) = a5;
			a6 = data->Item[i][3];
			*(BYTE *)(dwAddress + 23) = a6;
			a7 = data->Item[i][4];
			*(BYTE *)(dwAddress + 24) = a7;
			a8 = data->Item[i][5];
			*(BYTE *)(dwAddress + 97) = (a8 & 2) >> 1 > 0;
			*(BYTE *)(dwAddress + 98) = (a8 & 4) >> 2 > 0;
			*(BYTE *)(dwAddress + 73) = 16 * (a8 & 8) >> 7 > 0;
			a9 = data->Item[i][6];
			*(WORD *)(dwAddress + 69) = (a9 & 0xF0) >> 4;
			*(WORD *)(dwAddress + 71) = a9 & 0xF;

			a10 = (DWORD)&data->Item[i][7];

			if (a10)
			{
				*(BYTE *)(dwAddress + 79) = 5;

				for (int i = 0; i < 5; ++i)
					*(BYTE *)(i + dwAddress + 74) = *(BYTE *)(i + a10);

				for (int j = 0; j < 5; ++j)
				{
					if (*(BYTE *)(j + a10) == 255)
					{
						*(BYTE *)(dwAddress + 79) = j;
						break;
					}

					if (*(BYTE *)(j + a10) == 254)
					{
						*(BYTE *)(j + dwAddress + 80) = -1;
					}
					else
					{
						*(BYTE *)(j + dwAddress + 80) = *(BYTE *)(j + a10) % 50;
						*(BYTE *)(j + dwAddress + 85) = *(BYTE *)(j + a10) / 50 + 1;
					}
				}

				if (this->CheckItemInfo(*(WORD *)dwAddress))
				{
					*(BYTE *)(dwAddress + 90) = a9;
					*(WORD *)(dwAddress + 69) = 0;
					*(WORD *)(dwAddress + 71) = 0;
				}
				else
				{
					*(BYTE *)(dwAddress + 90) = -1;
				}
			}
			else
			{
				*(BYTE *)(dwAddress + 79) = 0;
			}

			*(BYTE *)(dwAddress + 96) = 0;
			*(DWORD *)(dwAddress + 103) = 1;

			if (data->PeriodTime[i])
			{
				this->charItem.Item[i].PeriodItem = 1;
				this->charItem.Item[i].ExpireDateConvert = data->PeriodTime[i];
			}

			//pSetItemOption(&this->charItem.Item[i], data->Item[i][1], data->Item[i][3], data->Item[i][4]);
			((char(__thiscall*)(int This, ObjectItem * ip, unsigned __int8 Attribute1, unsigned __int8 Attribute2, unsigned __int8 Attribute3)) 0x007E22A0)(*(DWORD*)(GetInstance() + 308) ,&this->charItem.Item[i],data->Item[i][1], data->Item[i][3], data->Item[i][4]);
			this->charItem.GuildNumber = data->GuildNumber;
			if (data->Type[i] >= 0 && c)
				character.CharSetSlotItem(c, i, data->Type[i] + 1171, (data->Item[i][1] >> 3) & 0xF, data->Item[i][3] & 0x3F, data->Item[i][4]);
		}
		this->onView = true;
		gInterface.Data[eMainViewChar].OnShow ^= 1;
		return;
	}

	this->onView = false;
}
#endif