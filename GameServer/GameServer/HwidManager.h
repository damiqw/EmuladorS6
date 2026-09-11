#pragma once

#include "User.h"
#include "Protocol.h"

struct HardwareId_INFO
{
	char HardwareId[36];
	WORD HardwareIdCount;
	int aIndex;
	int MaxAccountLevel;
};

struct CG_HWID_SEND
{
	PSBMSG_HEAD	Head;
	char HardwareId[36];
	char DLLVersion[20];
	DWORD AntihackDllCRC;
	DWORD MainDllCRC;
	DWORD MainExeCRC;
	DWORD PlayerBmdCRC;
	DWORD SkillBmdCRC;
	DWORD ItemBmdCRC;
};

#include <set>

class CHwidManager
{
public:
	CHwidManager();
	virtual ~CHwidManager();
	void Load(char* path);
	bool CheckHwid(char* HardwarewId);
	bool CheckHwidException(char* HardwarewId);
	int GetOfflineCountByHwid(char* HardwarewId);
	void InsertHwid(char* HardwarewId, int aIndex);
	void RemoveHwid(char* HardwarewId);
	void ConnectHwid(CG_HWID_SEND *lpMsg, LPOBJ lpObj);
private:
	std::map<std::string,HardwareId_INFO> m_HwidInfo;
	std::set<std::string> m_HwidExceptionInfo;

}; extern CHwidManager gHwidManager;