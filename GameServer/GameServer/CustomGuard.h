#pragma once

#define MAX_GUARD 100

struct CUSTOM_GUARD
{
	int  m_MonsterClass;
};

class CCustomGuard
{
public:
	int m_count;
	CCustomGuard();
	~CCustomGuard();
	void Load(char* path);
	CUSTOM_GUARD* GetGuard(int MonsterClass);
	CUSTOM_GUARD m_CustomGuard[MAX_GUARD];
private:

};
extern CCustomGuard gCustomGuard;