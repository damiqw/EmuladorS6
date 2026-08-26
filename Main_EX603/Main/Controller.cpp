#include "stdafx.h"
#include "Controller.h"
#include "Offset.h"
#include "Interface.h"
#include "Util.h"
#include "Protect.h"
#include "resource.h"
#include "ControllerTextBox.h"
#include "Defines.h"
// ----------------------------------------------------------------------------------------------
Controller	gController;
// ----------------------------------------------------------------------------------------------

Controller::~Controller()
{
}

bool Controller::Load()
{
	// ----
	if( !this->KeyboardHook )
	{
		this->KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, this->Keyboard, gController.Instance, NULL);
		// ----
		if( !this->KeyboardHook )
		{
			return false;
		}
	}
	return true;
}
// ----------------------------------------------------------------------------------------------

LRESULT Controller::Keyboard(int Code, WPARAM wParam, LPARAM lParam)
{
	if( (Code == HC_ACTION) && (wParam == WM_KEYDOWN))
	{
		KBDLLHOOKSTRUCT Hook = *((KBDLLHOOKSTRUCT*)lParam);
		
		if( GetForegroundWindow() == *(HWND*)(MAIN_WINDOW) )
		{
			if (gInterface.ControlTextBox(Hook))
			{
				return 1;
			}
			if (gTextBoxController.ControlTextBox(Hook))
			{
				return 1;
			}

			if (Hook.vkCode == 0x4E) // VK_N
			{
				if (SceneFlag == MAIN_SCENE 
					&& !gInterface.CheckWindow(ObjWindow::ChatWindow)
					&& !gInterface.CheckWindow(ObjWindow::MuHelper)
					&& !gInterface.CheckWindow(ObjWindow::Store)
					&& !gInterface.CheckWindow(ObjWindow::CreateGuild)
					&& !gInterface.CheckWindow(ObjWindow::FastDial)
					&& !gInterface.CheckWindow(ObjWindow::FriendList))
				{
					if (gInterface.Data[OBJECT_PARTYMENU_MAIN].OnShow)
					{
						gInterface.Data[OBJECT_PARTYMENU_MAIN].Close();
					}
					else
					{
						gInterface.Data[OBJECT_PARTYMENU_MAIN].Open();
					}
					return 1;
				}
			}

			if (Hook.vkCode == 0x48) // VK_H
			{
				if (SceneFlag != MAIN_SCENE 
					|| gInterface.CheckWindow(ObjWindow::MuHelper)
					|| gInterface.CheckWindow(ObjWindow::Store)
					|| gInterface.CheckWindow(ObjWindow::CreateGuild)
					|| gInterface.CheckWindow(ObjWindow::FastDial)
					|| gInterface.CheckWindow(ObjWindow::FriendList))
				{
					short symbol = gTextBoxController.GetSymbolFromVK(Hook.vkCode);
					if (symbol != 0)
					{
						PostMessage(*(HWND*)(MAIN_WINDOW), WM_CHAR, symbol, 1);
					}
					return 1;
				}
			}
		}
	}
	
	return CallNextHookEx(gController.KeyboardHook, Code, wParam, lParam);
}
// ----------------------------------------------------------------------------------------------