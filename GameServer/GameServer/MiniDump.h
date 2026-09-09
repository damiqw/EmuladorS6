// MiniDump.h: interface for the CMiniDump class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

class CMiniDump
{
public:
	static void Start();
	static void Clean();
	static void CreateDump(EXCEPTION_POINTERS* info, const char* customReason = 0);
};
