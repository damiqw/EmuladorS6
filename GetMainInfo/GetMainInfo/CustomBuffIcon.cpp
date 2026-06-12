#include "StdAfx.h"
#include "CustomBuffIcon.h"
#include "MemScript.h"

CBuffIcon gCBuffIcon;

CBuffIcon::CBuffIcon(){
	this->Init();
}
CBuffIcon::~CBuffIcon()
{
}


void CBuffIcon::Init(){
	for(int n=0;n< 256;n++){
		this->m_TooltipENG [n].IndexBuff = -1;
	}
}

bool CBuffIcon::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR,path);
		return 0;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	int CustomItemIndexCount = 0;

	try
	{
		while(true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			if(strcmp("end",lpMemScript->GetString()) == 0)
			{
				break;
			}

			RenderTooltipBuff info;

			memset(&info,0,sizeof(info));

			info.Index = CustomItemIndexCount++;

			info.IndexBuff = lpMemScript->GetNumber();

			info.Arg1 = lpMemScript->GetAsNumber();

			info.Arg2 = lpMemScript->GetAsNumber();

			info.Arg3 = lpMemScript->GetAsNumber();

			strcpy_s(info.NameBuff,lpMemScript->GetAsString());

			info.Arg4 = lpMemScript->GetAsNumber();

			info.Arg5 = lpMemScript->GetAsNumber();

			info.Arg6 = lpMemScript->GetAsNumber();

			strcpy_s(info.InfoBuff, lpMemScript->GetAsString());

			this->m_TooltipENG[CustomItemIndexCount-1] = info;
		}
	}
	catch(...)
	{
		printf(lpMemScript->GetLastError());
		return 0;
	}

	delete lpMemScript;

	return 1;
}