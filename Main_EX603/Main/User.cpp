#include "stdafx.h"
#include "CustomNpcName.h"
#include "Offset.h"
#include "User.h"
#include "TMemory.h"
#include "Interface.h"
#include "Protocol.h"
#include "Object.h"
#include "Import.h"
#include "Defines.h"
#include "Item.h"
#include "HealthBar.h"
#include "CustomRankUser.h"
#include "Common.h"
#include "Util.h"


User	gObjUser;

DWORD LastTime = 0;


void User::Load()
{
	this->m_TargetUpdateTick	= 0;
	this->m_TargetType			= false;
	this->m_CursorX				= -1;
	this->m_CursorY				= -1;
	this->m_MapNumber			= -1;

	if (gProtect.m_MainInfo.ChangeCharInfo == 1)
	{
		SetCompleteHook(0xFF, 0x0077F822, &this->ChangeCharInfo);
	}

#if FLAG
	SetOp((LPVOID)0x00588511, (LPVOID)User::HoolCreateManyFlay, ASM::CALL);//melo need check
#endif

	//SetOp((LPVOID)0x00588511, (LPVOID)this->SetEventEffect, ASM::CALL);
	//Auto Move
	this->IsSendMove = 0;
	this->MoveToX = 0;
	this->MoveToY = 0;
	this->IsMove = 0;
	this->AutoMoveCheckMap = -1;

}

void User::Refresh()
{
	this->lpPlayer			= &*(ObjectCharacter*)oUserObjectStruct;
	this->lpViewPlayer		= &*(ObjectPreview*)oUserPreviewStruct;
	this->GetTarget();

	this->m_CursorX			= pCursorX;
	this->m_CursorY			= pCursorY;
	this->m_MapNumber		= pMapNumber;
	sprintf(this->getName,"%s",gObjUser.lpPlayer->Name);

	if ( gObjUser.GetActiveSkill() == 261 || 
		gObjUser.GetActiveSkill() == 552 || 
		gObjUser.GetActiveSkill() == 555 )
	{
		SetDouble(&pFrameSpeed1, 0.0004000);
		SetDouble(&pFrameSpeed2, 0.0002000);
	}
	else
	{
		SetDouble(&pFrameSpeed1, 0.0040000);
		SetDouble(&pFrameSpeed2, 0.0020000);
	}
}

bool User::GetTarget()
{
	if( pViewNPCTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewNPCTargetID);

		this->m_TargetType	= 1;
		return true;
	}
	else if( pViewAttackTargetID != -1 )
	{
		this->lpViewTarget	= &*(ObjectPreview*)pGetPreviewStruct(pPreviewThis(), pViewAttackTargetID);
		this->m_TargetType	= 2;
		return true;
	}
	
	if( this->lpViewTarget != 0 )
	{
		ZeroMemory(&this->lpViewTarget, sizeof(this->lpViewTarget));
	}
	
	this->m_TargetType = 0;
	return false;
}

int User::GetActiveSkill()
{
 lpCharObj lpPlayer  = &*(ObjectCharacter*)*(int*)(MAIN_CHARACTER_STRUCT);
 lpViewObj lpViewPlayer  = &*(ObjectPreview*)*(int*)(MAIN_VIEWPORT_STRUCT);
 return lpPlayer->pMagicList[lpViewPlayer->ActiveMagic];
}

#if(FLAG)
bool User::CreateManyFlag(ObjectPreview* pChar)
{
	if (!pChar->Unknown764)
	{
		BYTE Flag = 0;

		if (pChar == (ObjectPreview*)*(DWORD*)MAIN_VIEWPORT_STRUCT)
		{
			Flag = MyManyFlag;
		}
		else
		{
			Flag = GetPlayerManyFlag(pChar->aIndex);
		}
		if (Flag > 0)
		{
			pChar->Unknown764 = (DWORD)((void* (__thiscall*)(void* this1, int modeType, int ParentBoneIndex, bool bFllowParentRotate, float ox, float oy, float oz, float rx, float ry, float rz))(0x4EFFF0))
				(((void* (__cdecl*)(int))(0x9D00C5))(668), 6815 + Flag + ITEM_BASE_MODEL, 20, 0, -45.0, -5.0, -0.0, 0.0, 0.0, 1);
		}
	}

	return false;
}

void User::HoolCreateManyFlay(ObjectPreview* pChar)
{
	User::CreateManyFlag(pChar);
	((void(__cdecl*)(ObjectPreview*))(0x4EF9A0))(pChar);
}
#endif

void User::SetEventEffect(int PreviewStruct)
{

	lpViewObj lpPreview = &*(ObjectPreview*)PreviewStruct;

	if(lpPreview)
	{
		if(*(DWORD*)(MAIN_SCREEN_STATE) == GameProcess)
		{
			if (lpPreview->m_Model.ObjectType == emPlayer)
			{
					VAngle Angle;
					int PosX;
					int PosY;

					Angle.X = *(float*)(PreviewStruct+0x404);

					Angle.Y = *(float*)(PreviewStruct+0x408);

					Angle.Z = *(float*)(PreviewStruct+0x40C) + *(float*)(PreviewStruct+0x3E8) + 100.0f;

					pGetPosFromAngle(&Angle, &PosX, &PosY);

				//gInterface.DrawItem(PosX,PosY-30,4,4,0,SET_ITEMOPT_LEVEL(0),0,0,0);

			}
		}
	}

	// ----
	if( lpPreview->CtlCode == 32 )
	{
		if( *(DWORD*)(PreviewStruct + 672) && lpPreview->Unknown23 != 5 )
		{
			pInitEventStatus(PreviewStruct);
		}
		// ----
		lpPreview->Unknown23 = 5;
	}
	// ----
	if( *(DWORD*)(PreviewStruct + 672) != 0 || !lpPreview->Unknown23 )
	{
		return;
	}
	// ----
	switch(lpPreview->Unknown23)
	{
	case 5:	//-> GM
		{
			if( pEventEffectThis(668) )
			{
				DWORD ModelID = 349;
				// ----
				if( !strncmp(lpPreview->Name, "[GM]", 4) )
				{
					ModelID = 406;
				}
				else if( !strncmp(lpPreview->Name, "[EM]", 4) )
				{
					ModelID = 407;
				}
				else if( !strcmp(lpPreview->Name, "Admin") )
				{
					ModelID = 408;
				}

				// ----
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect(pEventEffectThis(668), ModelID, 20, 1, 70.0, -5.0, 0.0, 0.0, 0.0, 45.0);
			}
		}
		break;
		// --
	case 6:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 0, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 7:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 1, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 8:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 2, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 9:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 3, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 10:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 4, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 11:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 5, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 12:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 6, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
		// --
	case 13:
		{
			if( pEventEffectThis(668) )
			{
				*(LPVOID*)(PreviewStruct + 672) = pAddEventEffect2(pEventEffectThis(668), 32241, 7, 20, 120.0, 0.0, 0.0);
			}
		}
		break;
	default:
		{
			lpPreview->Unknown23 = 0;
		}
		break;
	}
}

char* User::GetMapName(signed int MapNumber)
{
	if (MapNumber >= 83 && MapNumber <= 100)
	{
		return pGetTextLine(pTextLineThis, (3160 + MapNumber - 83));
	}
	return pGetMapName(MapNumber);
}

int User::GetMaxStatPoint(int AccountLevel)
{
	return this->m_MaxStatPoint[AccountLevel];
}

#include "PrintPlayer.h"
#include "InterfaceElemental.h"
void User::ChangeCharInfo(LPVOID This)
{
	if (!gInterface.CheckWindow(Character))
	{
		return;
	}

	int JCResto;
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		JCResto = pWinWidth / pWinHeightReal - 640;
	}
	else
	{
		JCResto = 0;
	}

	float PosX = JCResto + 125;
	float PosY = +40;

	gInterface.DrawFormat(eGold, PosX + 345, PosY + 19, 100, 1, "Level:%d", gObjUser.lpPlayer->Level);

	gInterface.DrawFormat(eGold, PosX + 395, PosY + 19, 100, 1, "Point:%d", ViewPoint);

	gInterface.DrawFormat(eGold, PosX + 450, PosY + 19, 100, 1, "GR: %d", ViewMasterReset);

	gElemental.gInfoBox(PosX + 339, PosY + 53, 102, -9, 0x00000096, 0, 0);

	gElemental.gInfoBox(PosX + 450, PosY + 30, -8, 37, 0x00000096, 0, 0);

	gInterface.DrawFormat(eGold, PosX + 344, PosY + 40, 100, 1, "Resets: %d", ViewReset);

	gInterface.DrawFormat(eGold, PosX + 344, PosY + 63, 100, 1, "MasterLevel: %d", pMasterLevel);
}