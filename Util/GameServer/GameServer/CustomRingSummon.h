#pragma once

#define MAX_INVOKER 100

struct CUSTOM_INVOKER
{
	int ItemType;
	int ItemIndex;
	int MonsterNumb;
};

class CInvoker
{
public:
	CInvoker();
	virtual ~CInvoker();
	void Load(char* path);
    bool InvokerSummon(int aIndex);
    int m_count;
public:
	CUSTOM_INVOKER m_Invoker[MAX_INVOKER];
};
extern CInvoker gInvoker;