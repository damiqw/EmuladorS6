#include "stdafx.h"
#include "Protocol.h"
#include "NPCRuud.h"
#include "Import.h"
#include "Offset.h"
#include "Util.h"
#include "Defines.h"
#include "ShowInfoItemDrop.h"
#include "InterfaceElemental.h"
#include "Interface.h"

cRenderRuud jCRenderRuud;
int TimerPush;
int cerrar = 0;

cRenderRuud::cRenderRuud( )
{
	this->JCMoveX = 1.0;
	this->JCMoveY = 0.0;
	this->OpeningRuud = false;
	this->OpenWindowConfirm = false;
	this->JCSlot = -1;
	this->JCPage = -1;
	this->Page = 1;
	this->ClearRuudInfo( );
}

cRenderRuud::~cRenderRuud()
{
}

bool cRenderRuud::isOpen( )
{
	return this->OpeningRuud;
}

void cRenderRuud::MoverWinRuud( int x, int y )
{
	if(x < 0 || y < 0 || y + 430 > 480)
	{
		return;
	}

	this->JCMoveX = x;
	this->JCMoveY = y;
}

bool cRenderRuud::CheckMouseOver( )
{
	if(pCheckMouseOver(this->JCMoveX, this->JCMoveY, 190, 430) && this->OpeningRuud || this->OpenWindowConfirm )
	{
		return true;
	}

	return false;
}

bool cRenderRuud::EventPressButton(int x, int y, int h, int w)
{
	if( pCheckMouseOver(x, y, w, h) )
	{
		if( CursorPress )
		{
			if (GetTickCount() >= this->TimerEvent + 300) 
			{
				this->TimerEvent = GetTickCount();
				return true;
			}
		}
	}
	return false;
}

void cRenderRuud::ClosedRuud()
{
	PMSG_NPC_TALK_SEND pMsg;
	pMsg.header.set(0x31,sizeof(pMsg));
	DataSend((BYTE*)&pMsg,sizeof(pMsg));
	this->JCSlot = -1;
	this->JCPage = -1;
	this->OpenWindowConfirm = false;

	if(pCheckWindow(pWindowThis(), 13))
	{
		pCloseWindow(pWindowThis(), 13);
	}
}

void cRenderRuud::ClearRuudInfo( )
{
	this->lpInfo.clear( );
	this->Page = 1;
	this->Enter = 0;
}

void cRenderRuud::InsertRuudInfo(PMSG_RUUD_ITEM_LIST * lpInfo1)
{
	RUUD_ITEM_LIST * lpInfoRuud = new RUUD_ITEM_LIST;

	lpInfoRuud->slot = lpInfo1->slot;

	lpInfoRuud->RuudSell = lpInfo1->dwRuudSell;

	lpInfoRuud->ItemInfo = *(ObjectItem*)GetInfoByteItem(*(DWORD *)(GetInstance( ) + 36), lpInfo1->ItemInfo);

	this->lpInfo.insert(std::pair<int, RUUD_ITEM_LIST >(this->Enter, *(RUUD_ITEM_LIST*)lpInfoRuud));
}

void cRenderRuud::LoadRuudShop_Recv(PMSG_RUUD_ITEM_LIST_RECV * lpMsg)
{
	this->ClearRuudInfo();

	for (int n = 0; n < lpMsg->count; n++)
	{
		PMSG_RUUD_ITEM_LIST * lpInfo = (PMSG_RUUD_ITEM_LIST*)(((BYTE*)lpMsg) + sizeof(PMSG_RUUD_ITEM_LIST_RECV) + (sizeof(PMSG_RUUD_ITEM_LIST) * n));

		this->InsertRuudInfo(lpInfo);

		this->Enter++;
	}
}

void cRenderRuud::CheckOpen( )
{
	if( this->OpeningRuud )
	{
		if( !pCheckWindow(pWindowThis(), 13) )
		{
			this->OpeningRuud = false;
			this->ClosedRuud();
		}

		if( this->OpeningRuud &&
			(this->Coordenada[1] != pGetUserCoorX
			|| this->Coordenada[2] != pGetUserCoorY
			|| this->Coordenada[0] != pMapNumber))
		{
			this->OpeningRuud = false;
			this->ClosedRuud();
		}
	}
	else
	{
		this->Coordenada[0] = pMapNumber;
		this->Coordenada[1] = pGetUserCoorX;
		this->Coordenada[2] = pGetUserCoorY;
	}
}

void cRenderRuud::OpenRuudShop_Recv(PMSG_NPC_TALK_RECV * lpMsg)
{
	if(lpMsg->result == 100)
	{
		this->OpeningRuud = true;

		if(!pCheckWindow(pWindowThis(), 13))
		{
			pOpenWindow(pWindowThis(), 13);
		}
	}
}

void JPrintfItemName(int ItemID, int x, int y, int Width, int Type)
{
	pSetFont(pTextThis(), (int) pFontBold);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);

	pDrawText(pTextThis(), x, y, (const char*)pGetItemAtt(ItemID, 0), Width, 0, (LPINT)Type, 0);
}

void cRenderRuud::WindowConfirm( )
{
	float x; // ST08_4@1
	float y; // ST04_4@1
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	std::map<int, RUUD_ITEM_LIST>::iterator it;

	if ( this->OpenWindowConfirm && this->JCPage != -1 && this->JCSlot != -1 )
	{
		x = 205.0f;
		y = 100.0f;

		it = this->lpInfo.find(((this->JCPage) * 5) + this->JCSlot);

		if(it != this->lpInfo.end())
		{
			gElemental.gInfoBox(x, y, 230, 150,0x00000096, 0, 0);

			pSetFont(pTextThis(), (int) pFontBold);
			pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
			pDrawText(pTextThis(), (int)x, (int)(y + 75), "Mastery", 230, 0, (LPINT)3, 0);

			JPrintfItemName(it->second.ItemInfo.ItemID, (int)x, (int)(y + 90), 230, 3);

			//-- 0.4359999299 push
			if( pCheckMouseOver((int)x + 35, (int)y + 119, 43, 17) )
			{
				if( *(BYTE*)0x8793386 && cerrar == 0 )
				{
					RenderBitmap(71521, (int)x + 35, (int)y + 119, 43, 17, 0.0013, 0.4359999299, 0.8805001974, 0.3845001459, 1, 1, 0.0);
					if( GetTickCount( ) >= TimerPush + 300)
					{
						PMSG_BUY_ITEMRUUD_SEND pMsg;
						pMsg.header.set(0xEE,sizeof(pMsg));
						pMsg.PAGE = this->JCPage + 1;
						pMsg.SLOT = this->JCSlot + 1;
						DataSend((BYTE*)&pMsg,sizeof(pMsg));
						cerrar = 1;

						this->JCSlot = -1;
						this->JCPage = -1;
						TimerPush = GetTickCount( );
					}
				}
				else
				{
					RenderBitmap(71521, x + 35, y + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
				}
			}
			else
			{
				RenderBitmap(71521, x + 35, y + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
			}
		}
		//--
		if( pCheckMouseOver((int)x + 151, (int)y + 119, 43, 17) )
		{
			
			if( *(BYTE*)0x8793386 && cerrar == 0 )
			{
				RenderBitmap(71521, (int)x + 151, (int)y + 119, 43, 17, 0.0013, 0.4359999299, 0.8805001974, 0.3845001459, 1, 1, 0.0);
				if( GetTickCount( ) >= TimerPush + 300)
				{
					this->JCSlot = -1;
					this->JCPage = -1;
					cerrar = 1;
					TimerPush = GetTickCount( );
				}
			}
			else
			{
				RenderBitmap(71521, (int)x + 151, (int)y + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
			}
		}
		else
		{
			RenderBitmap(71521, (int)x + 151, (int)y + 119, 43, 17, 0.0013, 0.013, 0.8805001974, 0.3845001459, 1, 1, 0.0);
		}

		pDrawText(pTextThis(), (int)x + 35, (int)y + 122, pGetTextLine_(pTextLineThis, 228), 43, 0, (LPINT)3, 0);
		pDrawText(pTextThis(), (int)x + 151, (int)y + 122, pGetTextLine_(pTextLineThis, 229), 43, 0, (LPINT)3, 0);
	}

	if( cerrar == 1 && !*(BYTE*)0x8793386 )
	{
		cerrar = 0;
		this->OpenWindowConfirm = false;
	}
}

void JCRuudShopText(int x, int y, int Width)
{
	float v16; // ST34_4@1
	unsigned __int8 v17; // ST18_1@1
	unsigned __int8 v22; // ST18_1@1
	float v35; // [sp+338h] [bp-4h]@1

	v16 = *(float*)0x5EF5A1C * 0.001000000047497451;
	v35 = Convert( v16 ) + 1.0;

	v17 = (signed int)((2.0 - v35) * 127.0);
	pSetFont(pTextThis(), (int) pFontBold);
	//-- TitleName 1
	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, v17);
	pDrawText(pTextThis(), x, y + 29, "NPC Ruud", Width, 0, (LPINT)3, 0);
	//-- TitleName 2
	v22 = (signed int)(v35 * 127.0);
	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, v22);
	pDrawText(pTextThis(), x, y + 29, "Priest James", Width, 0, (LPINT)3, 0);

	pSetFont(pTextThis(), (int) pFontNormal);
	pSetTextColor(pTextThis(), 0xFFu, 0xFFu, 0xFFu, 0xFFu);
	pDrawText(pTextThis(), x + 15, y + 58, "You can use Ruud to purchase Selaed Mastery", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 68, "Set Items.", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 78, "You can unseal Sealed Sets by combining", 166, 0, (LPINT)1, 0);
	pDrawText(pTextThis(), x + 15, y + 88, "Ancient Hero's souls via Chaos Goblin.", 166, 0, (LPINT)1, 0);
}

void cRenderRuud::OpenRuud( )
{
	if( this->OpeningRuud == false )
	{
		return;
	}

	std::map<int, RUUD_ITEM_LIST>::iterator it;
	float x; // ST08_4@1
	float y; // ST04_4@1
	float RuudY; // ST04_4@1
	float ItemWidth; // [sp+48h] [bp-20h]@3
	float ItemHeight; // [sp+4Ch] [bp-1Ch]@3
	float ItemX; // [sp+54h] [bp-14h]@3
	float ItemY; // [sp+58h] [bp-10h]@3

	float RuudH = 55.0f;
	char Precio[50];

	x = (double)this->JCMoveX;
	y = (double)this->JCMoveY;

	RuudY = y + 109.5f;

	RenderBitmap(61560, x, y, 190.0f, 429.0f, 0.0, 0.0, 0.6319999695, 0.6218001246, 1, 1, 0.0);
	JCRuudShopText((int) x, (int) y, (int) 190.0f);

	if( EventPressButton( (int)(x + 65), (int)y + 400, 10, 10) && !this->OpenWindowConfirm )
	{
		if( this->Page > 1 ) { this->Page--; }
		RenderBitmap(61562, x + 65, y + 400, 10, 10, 0.02999999747, ( this->Page == 1 ) ?0.4549999833 : 0.3069999814, 0.2610003054, 0.1405000836, 0, 0, 0);
	}
	else
	{
		RenderBitmap(61562, x + 65, y + 400, 10, 10, 0.02999999747, ( this->Page == 1 ) ?0.4549999833 : 0.00800000038, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}

	if( EventPressButton( (int)x + 115, (int)y + 400, 10, 10) && !this->OpenWindowConfirm)
	{
		if( this->Page < 5 ) { this->Page++; }
		RenderBitmap(61562, x + 115, y + 400, 10, 10, 0.319999963, ( this->Page == 5 ) ? 0.4549999833 : 0.3069999814, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}
	else
	{
		RenderBitmap(61562, x + 115, y + 400, 10, 10, 0.319999963, ( this->Page == 5 ) ? 0.4549999833 : 0.00800000038, 0.2610003054, 0.1405000836, 1, 1, 0.0);
	}

	char nPage[10];
	ZeroMemory(nPage,sizeof(nPage));
	wsprintf(nPage, pGetTextLine_(pTextLineThis, 1181), this->Page, 5);

	pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
	pSetFont(pTextThis(), (int) pFontNormal);

	pDrawText(pTextThis(), (int)x + 85, (int)y + 403, nPage, 20, 0, (LPINT)3, 0);

	for ( int i = 0 ; i < 5 ; i++ )
	{
		it = this->lpInfo.find(((this->Page - 1) * 5) + i);

		if(it != this->lpInfo.end())
		{
			y = RuudY + ( RuudH * i );

			RenderBitmap(61561, x + 10, y + 1.0f, 166, RuudH, 0.0, 0.0, 0.5450001955, 0.6800000072, 1, 1, 0.0);

			JPrintfItemName(it->second.ItemInfo.ItemID, (int)(x + 68), (int)(y + 8), 105, 1);

			//-- evento comprar
			if( CheckButtonPressed((int)(x + 135), (int)(y + 5.0f), 38, 17) && !this->OpenWindowConfirm )
			{
				RenderBitmap(61542, (int) x + 135, y + 5.0f, 38, 17, 0.0, 0.268338412, 0.7135385275, 0.2283384204, 1, 1, 0);
				this->OpenWindowConfirm = true;
				this->JCSlot = i;
				this->JCPage = this->Page - 1;
			}
			else
			{
				RenderBitmap(61542,(int) x + 135, y + 5.0f, 38, 17, 0.0, 0.02, 0.7135385275, 0.2283384204, 1, 1, 0);
			}
			//-- Buy Boton
			pSetTextColor(pTextThis(), 0xFFu, 0xBDu, 0x19u, 0xFFu);
			pDrawText(pTextThis(),(int)(x + 135), (int)(y + 8.0f), pGetTextLine_(pTextLineThis, 1124), 38, 0, (LPINT)3, 0);
			//-- Precio del Item
			pGetMoneyFormat(it->second.RuudSell, Precio, 0);
			pDrawText(pTextThis(),(int)(x + 90), (int)(y + 43.0f), Precio, 100, 0, (LPINT)3, 0);
		}
	}

	for ( int i = 0 ; i < 5 ; i++ )
	{
		it = this->lpInfo.find(((this->Page - 1) * 5) + i);
		y = RuudY + ( RuudH * i );

		if(it != this->lpInfo.end())
		{
			ItemWidth = (double)(20 * *(BYTE *)pGetItemAtt(it->second.ItemInfo.ItemID, 38));
			ItemHeight = (double)(20 * *(BYTE *)pGetItemAtt(it->second.ItemInfo.ItemID, 39));

			ItemX = (double)(x + 38 - ItemWidth / 2);
			ItemY = (double)(y + 6.0f - ItemHeight / 2);

			gInterface.DrawItemIMG(
				ItemX,
				ItemY,
				ItemWidth,
				ItemHeight,
				it->second.ItemInfo.ItemID,
				it->second.ItemInfo.Level,
				it->second.ItemInfo.ExcellentOption,
				it->second.ItemInfo.AncientOption,
				0);

			if( pCheckMouseOver((int)(x + 13), (int)(y + 1.0f), 50, 50))
			{
				JCCoord B;
				B.X = (int)x + 10;
				B.Y = (int)(y + 1.0f);

				sub_7E3E30(*(DWORD *)(GetInstance( ) + 308), B, (int)&it->second.ItemInfo, 0, 0, 0);
			}
		}
	}

	this->WindowConfirm( );
}