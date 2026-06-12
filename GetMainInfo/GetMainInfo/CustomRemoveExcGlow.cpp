#include "stdafx.h"
#include "CustomRemoveExcGlow.h"
#include "MemScript.h"

JCRemoveGLow JCRemoveGlow;

JCRemoveGLow::JCRemoveGLow()
{
	for ( int k = 0 ; k < MAX_NOGLOW ; ++k )
	{
		this->m_JCRemoveGlow[k].ItemIndex = -1;
	}
}

JCRemoveGLow::~JCRemoveGLow()
{

}

bool JCRemoveGLow::Load( char* Path )
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		printf(MEM_SCRIPT_ALLOC_ERROR, Path);
		return 0;
	}

	if(lpMemScript->SetBuffer( Path ) == 0)
	{
		printf(lpMemScript->GetLastError());
		delete lpMemScript;
		return 0;
	}

	static int CustomItemIndexCount = 0;

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

			JCItemnoGlow info;

			memset(&info, 0, sizeof( info ));

			

			info.ItemIndex = GET_ITEM(lpMemScript->GetNumber(),lpMemScript->GetAsNumber());
			
			info.IndexTexture = lpMemScript->GetAsNumber();

			if( CustomItemIndexCount < MAX_NOGLOW )
			{
				this->m_JCRemoveGlow[CustomItemIndexCount] = info;
			}
			CustomItemIndexCount++;
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