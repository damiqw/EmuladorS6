#include <windows.h>

// outsmart GCC's missing-declarations warning
BOOL WINAPI DllMainx(HMODULE, DWORD, LPVOID);
BOOL WINAPI DllMainx(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}
