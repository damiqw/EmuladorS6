// MonsterMove.cpp: implementation of the CMonsterMove class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MonsterMove.h"
#include "MapManager.h"
#include "MemScript.h"
#include "Monster.h"
#include "RandomManager.h"
#include "Util.h"

CMonsterMove gMonsterMove;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMonsterMove::CMonsterMove() // OK
{
	this->m_MonsterMoveInfo.clear();
}

CMonsterMove::~CMonsterMove() // OK
{

}

void CMonsterMove::Load(char* path) // OK
{
	CMemScript* lpMemScript = new CMemScript;

	if(lpMemScript == 0)
	{
		ErrorMessageBox(MEM_SCRIPT_ALLOC_ERROR,path);
		return;
	}

	if(lpMemScript->SetBuffer(path) == 0)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
		delete lpMemScript;
		return;
	}

	this->m_MonsterMoveInfo.clear(); 

	try
	{
		while (true)
		{
			if(lpMemScript->GetToken() == TOKEN_END)
			{
				break;
			}

			int MonsterClass = lpMemScript->GetNumber();

			this->SetInfo(MonsterClass);

			while (true)
			{
				if(strcmp("end",lpMemScript->GetAsString()) == 0)
				{
					break;
				}

				MONSTER_MOVE_SPAWN info;

				info.MonsterClass = MonsterClass;

				info.Map = lpMemScript->GetNumber();

				info.X = lpMemScript->GetAsNumber();

				info.Y = lpMemScript->GetAsNumber();

				info.Dir = lpMemScript->GetAsNumber();

				info.MoveTime = lpMemScript->GetAsNumber();

				this->SetSpawnInfo(info);
			}
		}
	}
	catch (...)
	{
		ErrorMessageBox(lpMemScript->GetLastError());
	}

	delete lpMemScript;
}

void CMonsterMove::SetInfo(int MonsterClass) // OK
{
	std::map<int,MONSTER_MOVE_INFO>::iterator it = this->m_MonsterMoveInfo.find(MonsterClass);

	if(it == this->m_MonsterMoveInfo.end())
	{
		MONSTER_MOVE_INFO info;
		
		info.Index = MonsterClass;
		
		info.MonsterIndex = -1;

		info.CreateTime = 0;

		info.MoveTime = 0;

		this->m_MonsterMoveInfo.insert(std::pair<int,MONSTER_MOVE_INFO>(info.Index,info));
	}
}

void CMonsterMove::SetSpawnInfo(MONSTER_MOVE_SPAWN info) // OK
{
	std::map<int,MONSTER_MOVE_INFO>::iterator it = this->m_MonsterMoveInfo.find(info.MonsterClass);

	if(it == this->m_MonsterMoveInfo.end())
	{
		return;
	}

	it->second.SpawnInfo.push_back(info);
}

void CMonsterMove::MainProc() // OK
{
	for(std::map<int,MONSTER_MOVE_INFO>::iterator ir=this->m_MonsterMoveInfo.begin(); ir != this->m_MonsterMoveInfo.end();ir++)
	{
		if((GetTickCount()-ir->second.CreateTime) >= (ir->second.MoveTime*1000))
		{
			ir->second.CreateTime = GetTickCount();

			gObjDel(ir->second.MonsterIndex);

			CRandomManager RandomManager;

			for(std::vector<MONSTER_MOVE_SPAWN>::iterator it = ir->second.SpawnInfo.begin(); it != ir->second.SpawnInfo.end(); it++)
			{
				RandomManager.AddElement((int)(&(*it)),1);
			}

			MONSTER_MOVE_SPAWN* info = 0;

			if(RandomManager.GetRandomElement((int*)&info) == 0)
			{
				continue;
			}

			int index = gObjAddMonster(info->Map);

			if(OBJECT_RANGE(index) == 0)
			{
				continue;
			}

			LPOBJ lpObj = &gObj[index];

			lpObj->PosNum = -1;
			lpObj->X = info->X;
			lpObj->Y = info->Y;
			lpObj->TX = lpObj->X;
			lpObj->TY = lpObj->Y;
			lpObj->OldX = lpObj->X;
			lpObj->OldY = lpObj->Y;
			lpObj->StartX = (BYTE)lpObj->X;
			lpObj->StartY = (BYTE)lpObj->Y;
			lpObj->Dir = info->Dir;
			lpObj->Map = info->Map;

			if(gObjSetMonster(index,ir->second.Index) == 0)
			{
				gObjDel(index);
				continue;
			}

			ir->second.MonsterIndex = index;

			ir->second.MoveTime = info->MoveTime;

			LogAdd(LOG_BLACK,"[Monster Move] SpawnMonster [%d] [%s][%d][%d]",ir->second.Index,gMapManager.GetMapName(lpObj->Map),lpObj->X,lpObj->Y);
		}
	}
}