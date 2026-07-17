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
	switch (MapNumber)
	{
		case 0: return "Lorencia";
		case 1: return "Dungeon";
		case 2: return "Devias";
		case 3: return "Noria";
		case 4: return "Lost Tower";
		case 6: return "Arena";
		case 7: return "Atlans";
		case 8: return "Tarkan";
		case 9: return "Devil Square 1";
		case 10: return "Icarus";
		case 11: return "Blood Castle 1";
		case 12: return "Blood Castle 2";
		case 13: return "Blood Castle 3";
		case 14: return "Blood Castle 4";
		case 15: return "Blood Castle 5";
		case 16: return "Blood Castle 6";
		case 17: return "Blood Castle 7";
		case 18: return "Chaos Castle 1";
		case 19: return "Chaos Castle 2";
		case 20: return "Chaos Castle 3";
		case 21: return "Chaos Castle 4";
		case 22: return "Chaos Castle 5";
		case 23: return "Chaos Castle 6";
		case 24: return "Kalima 1";
		case 25: return "Kalima 2";
		case 26: return "Kalima 3";
		case 27: return "Kalima 4";
		case 28: return "Kalima 5";
		case 29: return "Kalima 6";
		case 30: return "Castle Siege";
		case 31: return "Land of Trials";
		case 32: return "Devil Square 2";
		case 33: return "Aida";
		case 34: return "Crywolf";
		case 36: return "Kalima 7";
		case 37: return "Kanturu 1";
		case 38: return "Kanturu 2";
		case 39: return "Kanturu 3";
		case 40: return "Custom Arena";
		case 41: return "Barracks";
		case 42: return "Refuge";
		case 45: return "Illusion Temple 1";
		case 46: return "Illusion Temple 2";
		case 47: return "Illusion Temple 3";
		case 48: return "Illusion Temple 4";
		case 49: return "Illusion Temple 5";
		case 50: return "Illusion Temple 6";
		case 51: return "Elbeland";
		case 52: return "Blood Castle 8";
		case 53: return "Chaos Castle 7";
		case 56: return "Swamp of Calmness";
		case 57: return "Raklion 1";
		case 58: return "Raklion 2";
		case 62: return "Santa Town";
		case 63: return "Vulcanus";
		case 64: return "Duel Arena";
		case 65: return "Double Goer 1";
		case 66: return "Double Goer 2";
		case 67: return "Double Goer 3";
		case 68: return "Double Goer 4";
		case 69: return "Imperial Guardian 1";
		case 70: return "Imperial Guardian 2";
		case 71: return "Imperial Guardian 3";
		case 72: return "Imperial Guardian 4";
		case 75: return "Mundioca";
		case 76: return "GM Map";
		case 79: return "Loren Market";
		case 80: return "Karutan 1";
		case 81: return "Karutan 2";
		case 82: return "Double Goer Renew 1";
		case 83: return "Double Goer Renew 2";
		case 84: return "Double Goer Renew 3";
		case 85: return "Double Goer Renew 4";
		case 86: return "Double Goer Renew 5";
		case 87: return "Double Goer Renew 6";
		case 88: return "Double Goer Renew 7";
		case 89: return "Double Goer Renew 8";
		case 90: return "Double Goer Renew 9";
		case 91: return "Acheron 1";
		case 92: return "Acheron 2";
		case 95: return "Deventer 1";
		case 96: return "Deventer 2";
		case 97: return "Chaos Castle Final";
		case 98: return "Illusion Temple Final 1";
		case 99: return "Illusion Temple Final 2";
		case 100: return "Urk Mountain 1";
		case 101: return "Urk Mountain 2";
		case 102: return "Devil Square Final";
		case 110: return "Nars";
		case 112: return "Ferea";
		case 113: return "Nixies Lake";
		case 114: return "Instance Zone";
		case 115: return "Labyrinth of Dimensions";
		case 116: return "Deep Dungeon 1";
		case 117: return "Deep Dungeon 2";
		case 118: return "Deep Dungeon 3";
		case 119: return "Deep Dungeon 4";
		case 120: return "Deep Dungeon 5";
		case 121: return "Trial Area";
		case 122: return "Swamp of Darkness";
		case 123: return "Kubera Mine 1";
		case 124: return "Kubera Mine 2";
		case 125: return "Kubera Mine 3";
		case 126: return "Kubera Mine 4";
		case 127: return "Kubera Mine 5";
		case 128: return "Atlans Abyss 1";
		case 129: return "Atlans Abyss 2";
		case 130: return "Atlans Abyss 3";
		case 131: return "Scorched Canyon";
		case 132: return "Crimson Icarus";
		case 133: return "Arenil Temple";
		case 134: return "Ashen Aida";
		case 135: return "Old Kethotum";
		case 136: return "Blaze Kethhotum";
		case 137: return "Kanturu Under Area";
		case 138: return "Ignis Vulcanus";
		case 139: return "Boss Battle Zone";
		case 140: return "Blood Tarkan";
		case 141: return "Tormenta Island";
		case 142: return "Twister Karutan";
		case 143: return "Kardamahal UnderGround Temple";
		case 144: return "Swamp of Doom";
		default:
			static char szUnknown[32];
			wsprintf(szUnknown, "Unknown(%d)", MapNumber);
			return szUnknown;
	}
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

