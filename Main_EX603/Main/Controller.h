#pragma once
// ----------------------------------------------------------------------------------------------

#define VK_0 	0x30 //	0 key
#define VK_1 	0x31 //	1 key
#define VK_2 	0x32 //	2 key
#define VK_3 	0x33 // 3 key
#define VK_4 	0x34 //	4 key
#define VK_5 	0x35 //	5 key
#define VK_6 	0x36 //	6 key
#define VK_7 	0x37 //	7 key
#define VK_8 	0x38 //	8 key
#define VK_9 	0x39 //	9 key 

#define eKEYS_COUNT 9;

enum eKEYS
{
	eF9 = 0,
	eF10 = 1,
	eF11 = 2,
	eF12 = 3,
	eF7 = 4,
	eF8 = 5,
	eEND = 6,
	eESCAPE = 7,
	eItemMoveRBTN = 8,
	eF1 = 9,
};

class Controller
{
public:
	~Controller();
	bool	Load();
	// ----
	static	LRESULT WINAPI Keyboard(int Code, WPARAM wParam, LPARAM lParam);
	// ----
	HINSTANCE	Instance;
	BOOL VKF9_State;
	std::map<int,DWORD> m_KeyDelay;
private:
	HHOOK		KeyboardHook;
	
	// ----
}; extern Controller gController;
// ----------------------------------------------------------------------------------------------