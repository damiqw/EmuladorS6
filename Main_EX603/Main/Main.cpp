#include "stdafx.h"
#include "MuHelper.h"
#include "resource.h"
#include "Main.h"
#include "..\\..\\Util\\CCRC32.H"
#include "Common.h"
#include "CustomJewel.h"
#include "CustomWing.h"
#include "StaticEffect.h"
#include "DynamicEffect.h"
#include "HackCheck.h"
#include "HealthBar.h"
#include "Item.h"
#include "ItemShopValue.h" 
#include "ItemSmoke.h"
#include "Interface.h"
#include "OffTrade.h"
#include "PacketManager.h"
#include "PrintPlayer.h"
#include "Protect.h"
#include "Protocol.h"
#include "Reconnect.h"
#include "Resolution.h"
#include "User.h"
#include "Util.h"
#include "post_item.h"
#include "SItemOption.h"
#include "Camera.h"
#include "Offset.h"
#include "TMemory.h"
#include "Font.h"
#include "cfreetype.h"
#include "CustomBow.h"
#include "CustomBuffIcon.h"
#include "CustomCloak.h"
#include "CustomEarthQuakeSkill.h"
#include "CustomGloves.h"
#include "CustomMonsterEffect.h"
#include "CustomMonsterGlow.h"
#include "CustomPet.h"
#include "CustomPetEffect.h"
#include "CustomPetEffectDynamic.h"
#include "CustomPetGlow.h"
#include "CustomRenderExcGlow.h"
#include "ItemTooltip.h"
#include "CustomModelEffect.h"
#include "ItemManager.h"
#include "ItemTRSData.h"
#include "CustomMonster.h"
#include "CustomNpcName.h"
#include "CustomCape.h"
#include "Pet.h"
#include "PetMontura.h"
#include "PetHook.h"
#include "MonsterGlow.h"
#include "MessageBox.h"
#include "PlayerSystem.h"
#include "ItemInfoEx.h"
#include "TrayMode.h"
#include "FixAttack.h"
#include "EventEntryLevel.h"
#include "CustomServerInfo.h"
#include "CustomMap.h"
#include "ChaosBox.h"
#include "Warehouse.h"
#include "ShowInfoItemDrop.h"
#include "CameraMove.h"
#include "PartyBar.h"
#include "OptionPanel.h"
#include "MiniMap.h"
#include "RuneEffect.h"
#if(HAISLOTRING)
#include "NewUIMyInventory.h"
#include "WSclient.h"
#endif
#include "AtlansAbbys.h"
#include "CUiDIV.h"
#include "NPCRuud.h"
#include "CustomStatsAdvance.h"
#include "Controller.h"
#include "CustomQuickAddStats.h"
#include "Widescreen.h"
#include "SocketManager.h"
#include "InterfaceMacroUI.h"
#include "SceneSystemS8.h"
#include "GCCharacterS13.h"
#include "ItemMove.h"
#include "discord.h"
#include "LoginMainWin.h"
#include "LoginBox.h"
#include "CustomEventTime.h"
#include "MiniMapBrujula.h"
#include "CustomJewelBank.h"
#include "Config.h"
#include "SPK_xShop.h"
#include "BuyVip.h"
#include "Antilag.h"
#include "TerrainSystem.h"
#include "CustomCommandInfo.h"
#include "DailyReward.h"
#include "EventInvasion.h"
#include "ThueFlag.h"
#include "CustomFlag.h"
#include "CustomRanking.h"

Discord* g_Discord;

HHOOK HookKB,HookMS;
HINSTANCE hins;

__declspec(naked) void PositionAncientY() 
{
	static float PositionYAncient = 67.00000000000000;
	static DWORD m_ReturnAncient = 0x0083523A;

	_asm {
		FADD DWORD PTR DS:[PositionYAncient]
		JMP[m_ReturnAncient]
	}

}

void RemoveSocket()
{
	SetRange((LPVOID)0x00D46C8C, 5, ASM::NOP);
	SetCompleteHook(0xE9, 0x00835234, &PositionAncientY);
}

__declspec(naked) void OffButtonQuestInStats()
{
	static DWORD ButtonAddress = 0x0077EBB5;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonPetsInStats()
{
	static DWORD ButtonAddress = 0x0077EC5E;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonSkillMasterInStats()
{
	static DWORD ButtonAddress = 0x0077ECE7;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonInventoryExt()
{
	static DWORD ButtonAddress = 0x00836A28;
	_asm{jmp ButtonAddress}
}

__declspec(naked) void OffButtonOpenStore()
{
	static DWORD ButtonAddress = 0x008369B4;
	_asm{jmp ButtonAddress}
}
__declspec(naked) void OffButtonRepeirInInventory()
{
	static DWORD ButtonAddress = 0x00836941;
	_asm{jmp ButtonAddress}
}

LRESULT CALLBACK KeyboardProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		if (GetForegroundWindow() == pGameWindow)
		{
			if (GetKeyState(VK_F8) & 0x4000)
			{
#if(PREMIUM)
				gPartySearch.CGWindowOpen();
#endif
			}
			if (gProtect.m_MainInfo.CameraType == 1)
			{
				if (GetKeyState(VK_F10) & 0x4000)
				{
					gCamera.Toggle();
				}
				if (GetKeyState(VK_F11) & 0x4000)
				{
					gCamera.Restore();
				}
			}
			if (GetKeyState(VK_F12) & 0x4000)
			{
				gTrayMode.Toggle();
			}
		}
	}

	return CallNextHookEx(HookKB,nCode,wParam,lParam);
}

int MoveRuud;
int CurHookX;
int CurHookY;

LRESULT CALLBACK MouseProc(int nCode,WPARAM wParam,LPARAM lParam) // OK
{
	if(nCode == HC_ACTION)
	{
		MOUSEHOOKSTRUCTEX* HookStruct =(MOUSEHOOKSTRUCTEX*)lParam;

		if(GetForegroundWindow() == *(HWND*)(MAIN_WINDOW))
		{
			switch(wParam)
			{
				case WM_MOUSEMOVE:
					if (MoveRuud == 1)
					{
						jCRenderRuud.MoverWinRuud(*(DWORD*)0x879340C - CurHookX, *(DWORD*)0x8793410 - CurHookY);
					}
					if (gProtect.m_MainInfo.CameraType == 1)
					{
						gCamera.Move(HookStruct);
					}
					break;
				case WM_MBUTTONDOWN:
					if (gProtect.m_MainInfo.CameraType == 1)
					{
						gCamera.SetIsMove(1);
						gCamera.SetCursorX(HookStruct->pt.x);
						gCamera.SetCursorY(HookStruct->pt.y);
					}
					break;
				case WM_MBUTTONUP:
					if (gProtect.m_MainInfo.CameraType == 1)
					{
						gCamera.SetIsMove(0);
					}
					break;
				case WM_MOUSEWHEEL:
					if (gProtect.m_MainInfo.CameraType == 1)
					{
						gCamera.Zoom(HookStruct);
					}
					break;
				case WM_LBUTTONUP:
				case WM_LBUTTONDOWN:
					gInterface.EventConfirm_CANCEL(wParam);
					gInterface.EventConfirm_OK(wParam);
					gInterface.EventDrawMenuTrash_Open(wParam);
					gInterface.DrawMenuTrash_Warning_Main(wParam);
					gOffTrade.EventOffTradeWindow_Main(wParam);
					gOffTrade.EventCloseTradeWindow_Main(wParam);
					gWarehouse.ButtonEvent_Main(wParam);
#if(QuickAddStats)
					gQuickAddStats.EventStatsAddWindow_STR(wParam);
					gQuickAddStats.EventStatsAddWindow_AGI(wParam);
					gQuickAddStats.EventStatsAddWindow_VIT(wParam);
					gQuickAddStats.EventStatsAddWindow_ENE(wParam);
					gQuickAddStats.EventStatsAddWindow_CMD(wParam);
#endif
					gInterface.EventDrawMenu_Open(wParam);
					gInterface.EventDrawMenuS8_Open(wParam);
#if(MENU_NEW)
					gInterface.EventMenuWindow(wParam);
#endif
					gCustomEventTime.EventEventTimeWindow_Close(wParam);
					gCustomEventTime.EventNext(wParam); //passa pra proxima pag
					gCustomEventTime.EventPrev(wParam); //volta uma pagina
					gCustomJewelBank.CommandNext(wParam);
					gCustomJewelBank.CommandPrev(wParam);
					gCustomJewelBank.EventJewelBankWindow_Close(wParam);
					gCustomJewelBank.EventJewelBankWithDraw(wParam);
#if(LuckyWheelV2)
					gInterface.EventVongQuayWindows_Close(wParam);
#endif
#if(CustomXShop)
					gNewCashShop.EventCustomShopWindows_Close(wParam);
#endif
					gBuyVip.EventVipWindow_Main(wParam);
					gBuyVip.EventVipWindow_Close(wParam);
					gAntiLagSystem.EventUsersPanelAntiLag_CLOSE(wParam);
					gCustomCommandInfo.EventCommandWindow_Close(wParam);
					gCustomCommandInfo.CommandNext(wParam);
					gCustomCommandInfo.CommandPrev(wParam);
					DailyReward.Button(wParam);
					gEventInvasion.EventActiveInvasion_CLOSE(wParam);
#if FLAG
					ThueFlag.EventCustomFlahWindows_Close(wParam);
#endif
					gCustomRanking.EventRankingNext(wParam);
					gCustomRanking.EventRankingBack(wParam);
					gCustomRanking.EventRankingWindow_Close(wParam);
					gCustomRanking.EventVipWindow_Close(wParam);

					if (gProtect.m_MainInfo.SelectCharacterSystem = 1)
					{
						gCSCharacterS13.SelectCharButton(wParam);
					}

					if (jCRenderRuud.isOpen() && wParam == WM_LBUTTONDOWN)
					{
						if (pCheckMouseOver(jCRenderRuud.JCMoveX, jCRenderRuud.JCMoveY, 190, 70))
						{
							CurHookX = (double)*(DWORD*)0x879340C - jCRenderRuud.JCMoveX;
							CurHookY = (double)*(DWORD*)0x8793410 - jCRenderRuud.JCMoveY;
							MoveRuud = 1;
						}
						else
						{
							MoveRuud = 0;
						}
					}
					else
					{
						MoveRuud = 0;
					}

					break;
			}
		}
	}

	return CallNextHookEx(HookMS,nCode,wParam,lParam);
}

SHORT WINAPI KeysProc(int nCode) // OK
{
	if(GetForegroundWindow() != *(HWND*)(MAIN_WINDOW))
	{
		return 0;
	}

	return GetAsyncKeyState(nCode);
}

HICON WINAPI IconProc(HINSTANCE hInstance,LPCSTR lpIconName) // OK
{
	FILE* file;

	gTrayMode.m_TrayIcon = (HICON)LoadImage(hins,".\\Data\\Custom\\Main.ico",IMAGE_ICON,GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),LR_LOADFROMFILE | LR_DEFAULTCOLOR);

	return gTrayMode.m_TrayIcon;
}

void WINAPI ReduceConsumeProc() // OK
{
	while(true)
	{
		Sleep(5000);
		SetProcessWorkingSetSize(GetCurrentProcess(),0xFFFFFFFF,0xFFFFFFFF);
		SetThreadPriority(GetCurrentProcess(),THREAD_PRIORITY_LOWEST);
	}
}

void WinInventory(BYTE Mode)
{
	EnableAlphaTest(1);
	glColor3f(1.0, 1.0, 1.0);

	jCRenderRuud.OpenRuud();

	pGLSwitch();
	EnableAlphaTest(Mode);
}

void ChargeItemConfirmRuud()
{
	float x; // ST08_4@1
	float y; // ST04_4@1
	float ItemWidth; // [sp+48h] [bp-20h]@3
	float ItemHeight; // [sp+4Ch] [bp-1Ch]@3
	float ItemX; // [sp+54h] [bp-14h]@3
	float ItemY; // [sp+58h] [bp-10h]@3
	int JCResto = pWinWidth / pWinHeightReal / 2 - 320;

	std::map<int, RUUD_ITEM_LIST>::iterator it;

	it = jCRenderRuud.lpInfo.find(((jCRenderRuud.JCPage) * 5) + jCRenderRuud.JCSlot);

	if (it != jCRenderRuud.lpInfo.end())
	{
		x = 205.0f;
		y = 100.0f;

		ItemWidth = (double)(20 * *(BYTE*)pGetItemAtt(it->second.ItemInfo.ItemID, 38));
		ItemHeight = (double)(20 * *(BYTE*)pGetItemAtt(it->second.ItemInfo.ItemID, 39));

		ItemX = (double)(x + 115 - ItemWidth / 2);
		ItemY = (double)(y + 40 - ItemHeight / 2);

		pDrawItemModel(
		ItemX,
		ItemY,
		ItemWidth,
		ItemHeight,
		it->second.ItemInfo.ItemID,
		it->second.ItemInfo.Level,
		it->second.ItemInfo.ExcellentOption,
		it->second.ItemInfo.AncientOption,
		0);
	}
}

__declspec(naked) void LeaConfirmRuud()
{
	static DWORD AddrJmp = 0x007DD4B3;

	if (jCRenderRuud.isOpen() == true && jCRenderRuud.OpenWindowConfirm)
	{
		ChargeItemConfirmRuud();
	}

	_asm
	{
		LEA EAX, DWORD PTR SS : [EBP - 0x8]
		PUSH EAX; / Arg1
		MOV ECX, DWORD PTR SS : [EBP - 0x34] ; |
		ADD ECX, 0x10; |
		JMP[AddrJmp]
	}
}

bool JCLockCursor(int x, int y, int w, int h)
{
	bool CheckRuud = false; // al@2
	bool CheckMenu = false; // al@2
	bool Check1 = false; // al@2
	bool Check2 = false; // al@2
	bool Skill = false; // al@2
	bool Interface = false; // al@2
	int JCMainSelect; // [sp+30h] [bp-2Ch]@15

	float MainWidth = 230.0;
	float MainHeight = 130.0;
	float StartBody = 30.0;
	float StartY = 30.0;
	float StartX;

	bool IsAnyInterfaceOpen();

	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		StartX = (MAX_WIN_WIDTH / 2) - (MainWidth / 2);
	}
	else
	{
		StartX = (640 / 2) - (MainWidth / 2);
	}

	float MainCenter = StartX + (MainWidth / 3);
	float ButtonX = MainCenter - (float)(29.0 / 2);

	int JCResto; // eax@1
	int JCWinWidth; // eax@1
	JCWinWidth = (double)(unsigned int)pWinWidth / pWinHeightReal;
	JCResto = JCWinWidth / 2 - 320;

	if (jCRenderRuud.isOpen())
	{
		CheckRuud = jCRenderRuud.CheckMouseOver();
	}
	if (gInterface.Data[eSTATSADD_MAIN_STR].OnShow)
	{
		CheckMenu = pCheckMouseOver(StartX, StartY + (float)2.0 + 100, 222, 120);
	}
	if (gInterface.Data[eSTATSADD_MAIN_AGI].OnShow)
	{
		CheckMenu = pCheckMouseOver(StartX, StartY + (float)2.0 + 100, 222, 120);
	}
	if (gInterface.Data[eSTATSADD_MAIN_VIT].OnShow)
	{
		CheckMenu = pCheckMouseOver(StartX, StartY + (float)2.0 + 100, 222, 120);
	}
	if (gInterface.Data[eSTATSADD_MAIN_ENE].OnShow)
	{
		CheckMenu = pCheckMouseOver(StartX, StartY + (float)2.0 + 100, 222, 120);
	}
	if (gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		CheckMenu = pCheckMouseOver(StartX, StartY + (float)2.0 + 100, 222, 120);
	}

	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		Check1 = pCheckMouseOver(x, y, 235, h);

		Interface = pCheckMouseOver(StartX, Fix_DisplayHeightExt + 429, 800, 100);

		JCMainSelect = *(DWORD*)(GetInstance() + 32);

		if ((signed int)*(BYTE*)(*(DWORD*)0x8128AC8 + 118) > 0 && *(BYTE*)(JCMainSelect + 64) == 1)
		{
			Skill = pCheckMouseOver(JCResto + 436, Fix_DisplayHeightExt + 361, 17, 42);
		}

		if (JCExMacro.OpenLayer != 0)
		{
			Check2 = pCheckMouseOver(8, 22, 120, JCExMacro.Server_List_num * 16);
		}
	}	

	if (gRenderMapB.DataMap.ModelID != 0 && MiniMap && !IsAnyInterfaceOpen())
	{
		Check2 = pCheckMouseOver(gRenderMapB.ultimoX + JCResto, gRenderMapB.ultimoY, 154, 162);
	}

	return Check1 || Check2 || CheckRuud || Skill || CheckMenu || Interface;
}

bool IsAnyInterfaceOpen()
{
	if (gInterface.Data[eSTATSADD_MAIN_STR].OnShow ||
		gInterface.Data[eSTATSADD_MAIN_AGI].OnShow ||
		gInterface.Data[eSTATSADD_MAIN_VIT].OnShow ||
		gInterface.Data[eSTATSADD_MAIN_ENE].OnShow ||
		gInterface.Data[eSTATSADD_MAIN_CMD].OnShow)
	{
		return true;
	}

	if (gInterface.CheckWindow(FullMap) ||
		gInterface.CheckWindow(FriendList) ||
		gInterface.CheckWindow(SkillTree) ||
		gInterface.CheckWindow(CashShop) ||
		gInterface.CheckWindow(FastMenu) ||
		gInterface.CheckWindow(Inventory) ||
		gInterface.CheckWindow(ObjWindow::Options) ||
		gInterface.CheckWindow(MuHelper))
	{
		return true;
	}

	if (jCRenderRuud.isOpen())
	{
		return true;
	}

	if (JCExMacro.OpenLayer != 0)
	{
		return true;
	}

	return false;
}

extern "C" _declspec(dllexport) void EntryProc() // OK
{

	if(gProtect.ReadMainFile("Data/Local/Main.bmd") == 0)
	{
		MessageBox(0,"Data\Local\Main.bmd not found or invalid!","Error",MB_OK | MB_ICONERROR);
		ExitProcess(0);
	}

	gController.Load();
	gMuHelper.Load();

	SetByte(0x00E61144,0xA0); // Accent
	SetByte(0x004D1E69,0xEB); // Crack (mu.exe)
	SetByte(0x004D228D,0xE9); // Crack (GameGuard)
	SetByte(0x004D228E,0x8B); // Crack (GameGuard)
	SetByte(0x004D228F,0x00); // Crack (GameGuard)
	SetByte(0x004D2290,0x00); // Crack (GameGuard)
	SetByte(0x004D2291,0x00); // Crack (GameGuard)
	SetByte(0x004D559C,0xEB); // Crack (ResourceGuard)
	SetByte(0x00633F7A,0xEB); // Crack (ResourceGuard)
	SetByte(0x00634403,0xEB); // Crack (ResourceGuard)
	SetByte(0x0063E6C4,0xEB); // Crack (ResourceGuard)
	SetByte(0x004D2246,0xEB); // Crack (ResourceGuard)
	SetByte(0x00501163,0xEB); // Crack (ResourceGuard)
	SetByte(0x0040AF0A,0x00); // Crack (ResourceGuard)
	SetByte(0x0040B4BC,0x50); // Login Screen
	SetByte(0x0040B4C5,0x50); // Login Screen
	SetByte(0x0040B4CF,0x18); // Login Screen
	SetByte(0x0040AF0A,0x00); // Login Screen
	SetByte(0x0040AFD5,0xEB); // Login Screen
	SetByte(0x005C8F86,0x00); // Lucky Move To Vault
	SetByte(0x005C8DAC,0x00); // Lucky Move To Trade
	SetByte(0x00777FD6,0x70); // Item Text Limit
	SetByte(0x00777FD7,0x17); // Item Text Limit
	SetByte(0x004EBEC7,0x3C); // Item Text Limit
	SetByte(0x005C4004,0x3C); // Item Text Limit
	SetByte(0x007E40BB,0x3C); // Item Text Limit
	SetByte(0x0081B546,0x3C); // Item Text Limit
	SetByte(0x0081B58D,0x3C); // Item Text Limit
	SetByte(0x0086E284,0x3C); // Item Text Limit
	SetByte(0x0086E44C,0x3C); // Item Text Limit
	SetByte(0x0086E573,0x3C); // Item Text Limit
	SetByte(0x0086F8FC,0x3C); // Item Text Limit
	SetByte(0x007DA373,0xB7); // Item Type Limit
	SetByte(0x007E1C44,0xB7); // Item Type Limit
	SetByte(0x0052100D,0xEB); // Ctrl Fix
	SetByte(0x0052101B,0x02); // Ctrl Fix
	SetByte(0x009543C4,0x00); // Move Vulcanu
	SetCompleteHook(0xE9, 0x005DB322, 0x5DB408);    //Fix Map 62 camera 3D (santa town)
	SetCompleteHook(0xE8, 0x005DB3BE, 0x005DB490);  //fix map vucanus 
	SetByte(0x0064CBD1,((gProtect.m_MainInfo.HelperActiveAlert==0)?0xEB:0x75)); // Helper Message Box
	SetByte(0x0064CBD0,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x0095CEEF,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x0095CF14,(BYTE)gProtect.m_MainInfo.HelperActiveLevel); // Helper Active Level
	SetByte(0x00E61F68,(gProtect.m_MainInfo.ClientVersion[0]+1)); // Version
	SetByte(0x00E61F69,(gProtect.m_MainInfo.ClientVersion[2]+2)); // Version
	SetByte(0x00E61F6A,(gProtect.m_MainInfo.ClientVersion[3]+3)); // Version
	SetByte(0x00E61F6B,(gProtect.m_MainInfo.ClientVersion[5]+4)); // Version
	SetByte(0x00E61F6C,(gProtect.m_MainInfo.ClientVersion[6]+5)); // Version
	SetWord(0x00E609E4,(gProtect.m_MainInfo.IpAddressPort)); // IpAddressPort
	SetDword(0x004D0E09,(DWORD)gProtect.m_MainInfo.WindowName);
	SetDword(0x004D9F55,(DWORD)gProtect.m_MainInfo.ScreenShotPath);
	SetByte(0x004030D4, (BYTE)gProtect.m_MainInfo.RemoveClass); // Create character max chars (default: 7)
	SetDword(0x00D226C8,(DWORD)KeysProc);
	SetDword(0x00D2265C,(DWORD)IconProc);

	SetCompleteHook(0xE8, 0x008350E9, &WinInventory);
	SetCompleteHook(0xE9, 0x007DD4A9, &LeaConfirmRuud);
	SetCompleteHook(0xE8, 0x007D2B3D, &JCLockCursor);

	if (gProtect.m_MainInfo.DiscordRPCSwitch == 1)
	{
		g_Discord->Initialize();
		g_Discord->Update();
	}

	if (gProtect.m_MainInfo.Language == 1)
	{
		SetByte((0x00958D4C + 3), 0xA8);	//1 Codepage utf China lang
		SetByte((0x00958D4C + 4), 0x03);	//2	Codepage utf China lang

		SetByte((0x00958D85 + 3), 0xA8);	//1 Codepage utf China lang
		SetByte((0x00958D85 + 4), 0x03);	//2	Codepage utf China lang

		SetByte((0x00958DBB + 3), 0xA8);	//1 Codepage utf China lang
		SetByte((0x00958DBB + 4), 0x03);	//2	Codepage utf China lang

		SetByte((0x00958DD7 + 3), 0xA8);	//1 Codepage utf China lang
		SetByte((0x00958DD7 + 4), 0x03);	//2	Codepage utf China lang

		SetByte(0x004215A7, 0xEB); //[0-9A-Za-z] Name
		SetByte(0x00507AFD, 0xEB); //[0-9A-Za-z] Guild
		SetByte((0x00507AEA + 1), 0x72); //[0-9A-Za-z] Name
		SetByte(0x004D6B49, 0xEB);

		SetByte(0x004D6A84, 0xE9);
		SetByte(0x004D6A84 + 1, 0x8D);
		SetByte(0x004D6A84 + 2, 0x00);
		SetByte(0x004D6A89, 0x90);
	}
	else if (gProtect.m_MainInfo.Language == 2)
	{
		SetDword(0x00958D4F, 0xCAED); // Korean CodePage
		SetDword(0x00958D88, 0xCAED); // Korean CodePage
		SetDword(0x00958DBE, 0xCAED); // Korean CodePage
		SetDword(0x00958DDA, 0xCAED); // Korean CodePage

		SetByte(0x004215A7, 0xEB); // Create Character Name
		SetByte(0x00507AEA, 0xEB); // Create Character Name
		SetByte(0x00507AEB, 0x72); // Create Character Name
	}

	if(gProtect.m_MainInfo.SystemFPS == 1)
	{
		SetDword(0x004D9D3B, (DWORD)&FrameValue);
		SetDword(0x004DAC60, (DWORD)&FrameValue);
		SetDword(0x7B55338, (DWORD)10);
		SetDword(0x004D597B, (DWORD)&MainTickCount);
		SetDword(0x004DA289, (DWORD)&MainTickCount);
		SetDword(0x004DA297, (DWORD)&MainTickCount);
		SetDword(0x004DA3A2, (DWORD)&MainTickCount);
		SetDword(0x004DA3CE, (DWORD)&MainTickCount);
		SetDword(0x004DA3D9, (DWORD)&MainTickCount);
		SetDword(0x0063D326, (DWORD)&MainTickCount);
		SetDword(0x00642112, (DWORD)&MainTickCount);

		SetCompleteHook(0xE9, 0x004DA280, &CheckTickCount1);

		SetCompleteHook(0xE9, 0x004DA3A1, &CheckTickCount2);

		g_CameraWalkInstance.Init();
	}

	SetByte(0x005C914B+3,0x00); // LuckItemmove

	//SetCompleteHook(0xE9, 0x004D1CF0, 0x004D1DC2); //-- Remoce MuError.DMP

	MemorySet(0x00D20170,0x90,0x1B); // Remove MuError.log

	MemorySet(0x0063E908,0x90,20); // C1:F3:04

	MemorySet(0x0064452A,0x90,0x0D); // Fix Dark horse look around

	MemorySet(0x00792B7F,0x90,0x05); // Crywolf Gatekeeper
			
	SetCompleteHook(0xE9, 0x0095DFBE, 0x0095DFD3); // Helper + Inventory
	
	SetCompleteHook(0xE9,0x0064452A,0x00644537); //-- Fix montura

	MemoryCpy(0x00E611B2,gProtect.m_MainInfo.IpAddress,sizeof(gProtect.m_MainInfo.IpAddress)); // IpAddress

	MemoryCpy(0x00E61F70,gProtect.m_MainInfo.ClientSerial,sizeof(gProtect.m_MainInfo.ClientSerial)); // ClientSerial

	SetCompleteHook(0xFF,0x0065FD79,&ProtocolCoreEx);

	SetCompleteHook(0xE8,0x005B96E8,&DrawNewHealthBar);

	VirtualizeOffset(0x004D9D39,12);

	VirtualizeOffset(0x004D9D45,7);

	VirtualizeOffset(0x004D9EFC,15);

	VirtualizeOffset(0x004DAC5C,8);

	VirtualizeOffset(0x005451F7,5);

	VirtualizeOffset(0x00545230,8);

	VirtualizeOffset(0x005A52E9,8);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN1),(DWORD)&NewAddressData1);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN2),(DWORD)&NewAddressData2);

	LoadReferenceAddressTable((HMODULE)hins,MAKEINTRESOURCE(IDR_BIN3),(DWORD)&NewAddressData3);

	gCustomMessage.LoadEng(gProtect.m_MainInfo.EngCustomMessageInfo);

	gCustomMessage.LoadPor(gProtect.m_MainInfo.PorCustomMessageInfo);

	gCustomMessage.LoadSpn(gProtect.m_MainInfo.SpnCustomMessageInfo);

	gCustomBow.Load(gProtect.m_MainInfo.CustomBowInfo);

	gIconBuff.LoadEng(gProtect.m_MainInfo.m_TooltipTRSDataEng);

	gCloak.Load(gProtect.m_MainInfo.m_CustomCloak);

	gCustomEarthQuake.Load(gProtect.m_MainInfo.m_EarthQuakeLoad);

	gCustomBattleGloves.Load(gProtect.m_MainInfo.CustomGloves);

	JCEffectMonster.Load(gProtect.m_MainInfo.m_CustomMonsterEffect);

	gCustomMonsterGlow.LoadGlow(gProtect.m_MainInfo.m_CustomMonsterGlow);

	gCustomMonsterGlow.LoadBrightness(gProtect.m_MainInfo.m_CustomMonsterbrightness);

	g_CustomPet.Load(gProtect.m_MainInfo.CustomPetInfo);

	gCustomCEffectPet.Load(gProtect.m_MainInfo.m_CustomPetCEffect);

	gCustomCEffectDynamicPet.Load(gProtect.m_MainInfo.m_DynamicPetEffect);

	cRender.Load(gProtect.m_MainInfo.RenderMeshPet);

	JCRemoveGlow.Load(gProtect.m_MainInfo.m_JCWRemoveGlow);

	gItemManager.Load(gProtect.m_MainInfo.m_ItemInfoEx);

	GInfo.loadnInformation( gProtect.m_MainInfo.m_TRSTooltipData);

	GInfo.loadnText( gProtect.m_MainInfo.m_TRSTooltipText);

	ItemTRSData.Load(gProtect.m_MainInfo.CustomPosition);

	gCustomModelEffect.Load(gProtect.m_MainInfo.m_CustomModelInfo);

	gCustomMonster.Load(gProtect.m_MainInfo.CustomMonsters);

	gCustomMonster.LoadBossClass(gProtect.m_MainInfo.CustomBossClass);

	gNPCName.Load(gProtect.m_MainInfo.CustomNPCName);

	gCustomItem.Load(gProtect.m_MainInfo.CustomItemInfo);

	gCustomJewel.Load(gProtect.m_MainInfo.CustomJewelInfo);

	gCustomWing.Load(gProtect.m_MainInfo.CustomWingInfo);

	gCustomWingEffect.Load(gProtect.m_MainInfo.CustomWingEffectInfo);

	gDynamicWingEffect.Load(gProtect.m_MainInfo.DynamicWingEffectInfo);

	gCustomFog.Load(gProtect.m_MainInfo.CustomFogInfo);

	gSmokeEffect.Load(gProtect.m_MainInfo.CustomSmokeEffect);

	g_ServerInfo.Init(gProtect.m_MainInfo.m_ServerInfo);

	g_pUIMapName.OpenScritp(gProtect.m_MainInfo.m_MapInfo);

	gRuneEffect.LoadRuneEffect(gProtect.m_MainInfo.m_RuneEffect);

	gItemPrice.Load(gProtect.m_MainInfo.CustomItemPrice);

	gCustomEventTime.Load(gProtect.m_MainInfo.CustomEventInfo);

	gCustomCommandInfo.Load(gProtect.m_MainInfo.CustomCommandInfo);

	gCustomFlag.Load(gProtect.m_MainInfo.CustomFlagInfo);

	gPacketManager.LoadEncryptionKey("Data\\Enc1.dat");

	gPacketManager.LoadDecryptionKey("Data\\Dec2.dat");

	if(gProtect.m_MainInfo.DisableCustomBow == 0)
	{
		gCustomBow.Init();
	}
		
	if(gProtect.m_MainInfo.DisableCustomCloack == 0)
	{
		gCapeAnimation.Load();
	}	
		
	if(gProtect.m_MainInfo.DisableCustomClaws == 0)
	{
		gCustomBattleGloves.Init();
	}	
			
	if(gProtect.m_MainInfo.DisableCustomPosition== 0)
	{
		ItemTRSData.Init(); // FIX IT
	}
			
	if(gProtect.m_MainInfo.DisableCustomPet == 0)
	{
		gCustomPet.Load();

		initmontura();
		
		gObjCreatePetExHook();

		gCustomCEffectPet.Init();
	}

	if (gProtect.m_MainInfo.RuneEffect == 1)
	{
		gRuneEffect.Init();
	}

	if (gProtect.m_MainInfo.m_SaveLoginBox == 1)
	{
		AutoLogin.Load();
	}

	if (gProtect.m_MainInfo.m_CreateAccount == 1)
	{
		g_pLoginMainWin.Init();
	}



	InvisibleItemX();

	InitTerrain();

	InitCommon();

	InitHackCheck();

	InitEventEntryLevel();

	InitItem();

	InitJewel();

	InitPrintPlayer();

	InitReconnect();

	InitResolution();

	InitWing();

	InitFont();

	InitChaosBox();

	InitItemMove();

	gObjUser.Load();

	gInterface.Load();

	gCItemSetOption.Load();

	JCItemPublic.Hook();

	gOffTrade.Init();

	InitFog();

	InitloadGlow();

	JCRemoveGlow.Init();

	gCustomEarthQuake.LoadRenderSkill();

	gCustomMonster.InitMonster();

	gProtect.CheckLauncher();

	gProtect.CheckInstance();

	gProtect.CheckClientFile();

	gProtect.CheckPluginFile();

	gProtect.CheckPluginFile2();
	
	gProtect.CheckPluginFile3();

	gProtect.CheckPluginFile4();

	gProtect.CheckPluginFile5();

	gProtect.CheckLauncherCommandLine();

	gMessageBoxPopUp.InitPopUp();

	PlayerLoad();

	gItemInfoEx.Load();

	FixVisualSpeedAttack();

	g_ServerInfo.Load();

	g_pUIMapName.Load();

	gWarehouse.StorageLoad();

	#if(PARTY_10)
	QTPary.Load();
	#endif

	gConfig.Load();

	gCustomJewelBank.Load();

	gRenderMap.MiniMapload();
	gRenderMapB.MiniMaploadB();

#if(HAISLOTRING)
	g_pMyInventory.Init();
	g_pWSclient.Init();
#endif

	InitAtlansAbbys();

	//gcUiDIV.Load();
	if (gProtect.m_MainInfo.CustomInterfaceType == 1 || gProtect.m_MainInfo.CustomInterfaceType == 2)
	{
		QTFrame.InitFrameOpenGL();

		JCSocketConnect.InitProperity();

		JCExMacro.Load();
	}
	if(gProtect.m_MainInfo.CustomOptionPanel == 1)
	{
		InitOptionPanel();
	}

	if(gProtect.m_MainInfo.ItemTooltipDrop == 1)
	{
		g_ShowInventoryGX.Init();
	}


	if (gProtect.m_MainInfo.DisableAdvance == 0)
	{
		if (gProtect.m_MainInfo.CustomInterfaceType == 0 || gProtect.m_MainInfo.CustomInterfaceType == 1)
		{
			g_StatsAdvance.Load();	//<-- Advanced
		}
	}

	if(gProtect.m_MainInfo.CsSkill == 1)
	{
		//Liberar CS Skills
		SetByte((0x005B89C3+3), 0x00);
		SetByte((0x005B89C9+3), 0x00);
		SetByte((0x005B89CF+3), 0x00);
		SetByte((0x005B89D5+3), 0x00);
		SetByte((0x005B89DB+3), 0x00);
		SetByte((0x005B89E1+3), 0x00);
		SetWord((0x005B89E7+3), 0x00);

		SetByte((0x005C6314+2), 0x00);
		SetByte((0x005C6327+2), 0x00);
		SetByte((0x005C633A+2), 0x00);
		SetByte((0x005C634D+2), 0x00);
		SetByte((0x005C6360+2), 0x00);
		SetByte((0x005C6373+2), 0x00);
		SetWord((0x005C6386+2), 0x00);


	}

	if(gProtect.m_MainInfo.ReduceMemory == 1)
	{
		CreateThread(0,0,(LPTHREAD_START_ROUTINE)ReduceConsumeProc,0,0,0);
	}

	if (gProtect.m_MainInfo.SelectCharacterSystem == 1)
	{
		gCSCharacterS13.Load();
	}

	if (gProtect.m_MainInfo.SelectServerType == 3) //select server season 8
	{
		CScene803();
	}

	if (gProtect.m_MainInfo.SelectCharacterType == 3) //select char season 8
	{
		SScene803();
	}

		if (gProtect.m_MainInfo.DisableTree == 1)
		{
			MemorySet(0x008193F0, 0x90, 0xC8); //Remove Master Skill Tree Window(A Buttom)
		}

		if(gProtect.m_MainInfo.DisableReflectEffect == 1)
		{
			SetByte(0x005528A0,0xC3);
		}

		if(gProtect.m_MainInfo.DisableEffectPlus15 == 1)
		{
			MemorySet(0x006097B0,0x90,0x69D);
		}
		
		if(gProtect.m_MainInfo.DisableGens == 1)
		{
			MemorySet(0x007C5A68, 0x90, 0x25);
			MemorySet(0x007C4430, 0x90, 0x159);			// Disable Gens
			MemorySet(0x007C5AD2, 0x90, 0x05);			//-> Disable Gens (Key B)
		}

		if(gProtect.m_MainInfo.DisableTabMap == 1)
		{
			MemorySet(0x0062F876, 0x90, 0x30);			//-> Disable ViewMap (Key TAB)
		}

		if (gProtect.m_MainInfo.DisableBattleZoneWindow == 1)
		{
			SetCompleteHook(0xE9, 0x00832862, 0x00832897);
		}

		if (gProtect.m_MainInfo.DisableMoveWindow == 1)
		{
			MemorySet(0x00830BA6, 0x90, 0x05);
			MemorySet(0x00832ED8, 0x90, 0x05);
			MemorySet(0x0083279C, 0x90, 0x05);
			MemorySet(0x008329A2, 0x90, 0x05);
		}

		if (gProtect.m_MainInfo.DisableBCDSCCMaster == 1)
		{
			SetCompleteHook(0xE9, 0x007E4CA4, 0x007E4D16);
			MemorySet(0x00878B5F, 0x90, 0x5);
			MemorySet(0x0087500F, 0x90, 0x5);
			SetByte((PVOID)(0x008743FC + 3), 7);
			SetByte((PVOID)(0x00874D54 + 6), 7);
			SetByte((PVOID)(0x007E4CB9 + 1), 0);
			SetByte((PVOID)(0x00877EDC + 3), 6);
		}

		if (gProtect.m_MainInfo.Disable380MixChaosMachine == 1)
		{
			MemorySet(0x007AA3BA, 0x90, 0x5);
			MemorySet(0x007AA39C, 0x90, 0x5);
			MemorySet(0x007AA9B3, 0x90, 0x5);
		}

		if(gProtect.m_MainInfo.DisableHelper == 1)
		{
			MemorySet(0x0085B6AC, 0x90, 0x05);			//-> Remove Helper Top Screen
			MemorySet(0x0085CC50, 0x90, 0x05);			//-> Disable Helper (Key Z)
			MemorySet(0x007D40A2, 0x90, 0x05);			//-> Disable Helper (Key Home)
		}

		if(gProtect.m_MainInfo.DisableClickEffect == 1)
		{
		    SetRange((LPVOID)0x006E899D, 5, ASM::NOP);
		    SetRange((LPVOID)0x007126FA, 5, ASM::NOP);
		    SetRange((LPVOID)0x005B768F, 5, ASM::NOP);
		    SetRange((LPVOID)0x005B770C, 5, ASM::NOP);
		}

		if(gProtect.m_MainInfo.DisableCashShopKeyX == 1)
		{
			//MemorySet(0x00661700, 0x90, 0x43);			//-> Disable CashShop (Key X) SafeZone
			//MemorySet(0x007D3D7A, 0x90, 0x05);			//-> Disable CashShop (Key X) MonsterZone
			SetByte((PVOID)(0x007D3D56+1),0xFF); // Remover XShop
		}
		BYTE WCoinPValue = 0;
		BYTE WCoinGValue = 0;

		if (gProtect.m_MainInfo.DisableWCoinCCashShop != 0)
		{
			SetRange(0x0094346B, 0x3A, ASM::NOP); // Disable WCoin Text in CashShop
			SetRange(0x009434A5, 0x38, ASM::NOP); // Disable WCoin Value in CashShop
			WCoinPValue += 15;
			WCoinGValue += 15;
		}

		if (gProtect.m_MainInfo.DisableWCoinPCashShop != 0)
		{
			SetRange(0x00943524, 0x3A, ASM::NOP); // Disable WCoinP Text in CashShop
			SetRange(0x0094355E, 0x38, ASM::NOP); // Disable WCoinP Value in CashShop
			WCoinGValue += 15;
		}
		else
		{
			SetByte(0x00943541, *(BYTE*)0x00943541 - WCoinPValue);// WcoinP Text X position. Default 65
			SetByte(0x00943578, *(BYTE*)0x00943578 - WCoinPValue);// WCoinP Value X position. Default 65
		}

		if (gProtect.m_MainInfo.DisableWCoinGCashShop != 0)
		{
			SetRange(0x009435DD, 0x3A, ASM::NOP); // Disable GoblinPoint Text in CashShop
			SetRange(0x00943617, 0x38, ASM::NOP); // Disable GoblinPoint Value in CashShop
		}
		else
		{
			SetByte(0x009435FA, *(BYTE*)0x009435FA - WCoinGValue);// GoblinPoint Text X position. Default 80
			SetByte(0x00943631, *(BYTE*)0x00943631 - WCoinGValue);// GoblinPoint Value X position. Default 80
		}

		if(gProtect.m_MainInfo.DisableSocketInvetory == 1)
		{
			RemoveSocket();
		}

		if (gProtect.m_MainInfo.DisableAncientInventory == 1)
		{
			SetRange((LPVOID)0x00D46C84, 5, ASM::NOP);      //-> Remove Interface [Set Option]
		}

		if(gProtect.m_MainInfo.DisableRepeirInInventory == 1)
		{
			SetCompleteHook(0xE9, 0x0083693C, &OffButtonRepeirInInventory);
		}

		if(gProtect.m_MainInfo.DisableButtonOpenStore == 1)
		{
			SetCompleteHook(0xE9, 0x008369AF, &OffButtonOpenStore);
		}

		if(gProtect.m_MainInfo.DisableButtonInventoryExt == 1)
		{
			SetCompleteHook(0xE9, 0x00836A23, &OffButtonInventoryExt);
		}

		if(gProtect.m_MainInfo.DisableButtonQuestInStats == 1)
		{
			SetCompleteHook(0xE9, 0x0077EBB0, &OffButtonQuestInStats);
		}

		if(gProtect.m_MainInfo.DisableButtonPetsInStats == 1)
		{
			SetCompleteHook(0xE9, 0x0077EC59, &OffButtonPetsInStats);
		}

		if(gProtect.m_MainInfo.DisableButtonSkillMaster == 1)
		{
			SetCompleteHook(0xE9, 0x0077ECE2, &OffButtonSkillMasterInStats);
		}

		if(gProtect.m_MainInfo.DisableButtonVaultExt == 1)
		{
	   		SetCompleteHook(0xE9, 0x00856FAA, 0x00856FD2); // Remove (H) Ba� Aberto
		    SetCompleteHook(0xE9, 0x007D371E, 0x007D3725); // Remove bot�o (H)
		}

		if (gProtect.m_MainInfo.DisableBlueEyeEffect == 1)
		{
			MemorySet(0x0057BF78, 0x90, 0x05); // pin_lights eyes
			MemorySet(0x0057C125, 0x90, 0x05); // pin_lights eyes
			MemorySet(0x0057BE80, 0x90, 0x05); // JointLaser01 eyes
			MemorySet(0x0057C057, 0x90, 0x05); // JointLaser01 eyes

		}

		if (gProtect.m_MainInfo.DisableFlareGlovesEffect == 1)
		{
			MemorySet(0x0057ABA9, 0x90, 0x05); // flare01 Gloves
			MemorySet(0x0057ACBF, 0x90, 0x05); // flare01 Gloves
			MemorySet(0x0057AD03, 0x90, 0x05); // flare01 Gloves
			MemorySet(0x0057AD47, 0x90, 0x05); // flare01 Gloves
		}

		if (gProtect.m_MainInfo.DisableGlowMuSignEffect == 1)
		{
			//glow gmsign
			SetCompleteHook(0xE9, 0x005E496C, 0x005E4A3F); // glow gmsign
		}
		
		if (gProtect.m_MainInfo.DisableWebzenChatCommand == 1)
		{
			SetByte(0x005A4070, 0xC3);
		}
		//Fenrir SafeZone (Struct +14)
		/*SetByte(0x00501955 + 2, 0);
		MemorySet(0x0054EAE1, 0x90, 0x06);//SetPlayerStop
		MemorySet(0x0054FC92, 0x90, 0x06);//SetPlayerWalk
		
		//Horse SafeZone (Struct +14)
		SetByte(0x00502269+2,0);
		MemorySet(0x0054ECA3,0x90,0x6);
		MemorySet(0x0054FCEC,0x90,0x6);
		
		//Dinorant e Uniria (Struct +14)
		SetByte(0x00502C4B+2,0);
		MemorySet(0x0054ED6D,0x90,0x6);
		MemorySet(0x0054FD5F,0x90,0x6);
		MemorySet(0x0054FE3E,0x90,0x6);
		
		//Raven (Struct +14)
		MemorySet(0x0054FD23,0x90,0x6);
		//kayito
		SetByte(0x0054ED11, 0xEB); // Ignore animation standing Pet on Arm
		SetByte(0x0054FD1E, 0xEB); // Ignore animation walking Pet on Arm
		SetCompleteHook(0xE9, 0x004F18E1, 0x004F19CD); // Pet always flying*/

	//==============================================================================
	// [Fix] AntiLag
	//==============================================================================
	if(DisableStaticEffect)
	{
		//Remove Effect Static
		MemorySet(0x00771310,0x90,0x11E);
	}
	if(DisableDynamicEffect)
	{
		//Remove Effect Dynamic
		MemorySet(0x0074CD30,0x90,0x10C50);
	}
	if(DisableSkillEffect)
	{
		//Remove Effect Skill
		MemorySet(0x00626190,0x90,0x2FE2);
		//Remove Efeect Skill 2
		MemorySet(0x0072D1B0,0x90,0x87A2);
	}

	HookKB = SetWindowsHookEx(WH_KEYBOARD,KeyboardProc,hins,GetCurrentThreadId());

	HookMS = SetWindowsHookEx(WH_MOUSE,MouseProc,hins,GetCurrentThreadId());

	cfreetype::Instance()->Init();
}


BOOL APIENTRY DllMain(HANDLE hModule,DWORD ul_reason_for_call,LPVOID lpReserved) // OK
{
	switch(ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hins = (HINSTANCE)hModule;
			gController.Instance = static_cast<HMODULE>(hModule);
			break;
		case DLL_PROCESS_DETACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		default:
			break;
	}

	return 1;
}
