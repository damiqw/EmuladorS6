#include "stdafx.h"
#include "Controller.h"
#include "Offset.h"
#include "Interface.h"
#include "Util.h"
#include "Protect.h"
#include "resource.h"
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
		}
	}
	
	return (LRESULT)NULL;
}
// ----------------------------------------------------------------------------------------------