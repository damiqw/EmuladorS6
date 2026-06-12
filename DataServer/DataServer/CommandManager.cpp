// CommandManager.cpp: implementation of the CCommandManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommandManager.h"
#include "QueryManager.h"
#include "SocketManager.h"
#include "Util.h"

CCommandManager gCommandManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommandManager::CCommandManager() // OK
{

}

CCommandManager::~CCommandManager() // OK
{

}

void CCommandManager::GDCommandResetRecv(SDHP_COMMAND_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x00,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.ResetDay = gQueryManager.GetAsInteger("ResetDay");

	pMsg.ResetWek = gQueryManager.GetAsInteger("ResetWek");

	pMsg.ResetMon = gQueryManager.GetAsInteger("ResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandMasterResetRecv(SDHP_COMMAND_MASTER_RESET_RECV* lpMsg,int index) // OK
{
	SDHP_COMMAND_MASTER_RESET_SEND pMsg;

	pMsg.header.set(0x0F,0x01,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	gQueryManager.ExecQuery("EXEC WZ_GetMasterResetInfo '%s','%s'",lpMsg->account,lpMsg->name);

	gQueryManager.Fetch();

	pMsg.MasterResetDay = gQueryManager.GetAsInteger("MasterResetDay");

	pMsg.MasterResetWek = gQueryManager.GetAsInteger("MasterResetWek");

	pMsg.MasterResetMon = gQueryManager.GetAsInteger("MasterResetMon");

	gQueryManager.Close();

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandDivorceRecv(SDHP_COMMAND_DIVORCE_RECV* lpMsg, int index) // OK
{
	gQueryManager.ExecQuery("UPDATE Character SET Married=0, MarryCouple=NULL WHERE Name='%s'", lpMsg->name);

	gQueryManager.Close();
}

void CCommandManager::GDCommandRewardRecv(SDHP_COMMAND_REWARD_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("EXEC WZ_SetReward '%s','%s','%s','%s','%d','%d'",lpMsg->account,lpMsg->name,lpMsg->accountGM,lpMsg->nameGM,lpMsg->Type,lpMsg->Value);
	gQueryManager.Close();
}

void CCommandManager::GDCommandRewardAllRecv(SDHP_COMMAND_REWARDALL_RECV* lpMsg,int index) // OK
{
	gQueryManager.ExecQuery("EXEC WZ_SetRewardAll '%s','%s','%d','%d'",lpMsg->accountGM,lpMsg->nameGM,lpMsg->Type,lpMsg->Value);
	gQueryManager.Close();
}

void CCommandManager::GDCommandRenameRecv(SDHP_COMMAND_RENAME_RECV* lpMsg, int index) // OK
{

			SDHP_COMMAND_RENAME_SEND pMsg;

			pMsg.header.set(0x0F,0x05,sizeof(pMsg));

			pMsg.index = lpMsg->index;

			memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

			memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

			memcpy(pMsg.newname,lpMsg->newname,sizeof(pMsg.newname));

			if(gQueryManager.ExecQuery("EXEC WZ_RenameCharacter '%s','%s','%s'",lpMsg->account,lpMsg->name,lpMsg->newname) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
			{
				gQueryManager.Close();

				pMsg.result = 2;
			}
			else
			{
				pMsg.result = gQueryManager.GetResult(0);

				gQueryManager.Close();
			}
			
			gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandBanAccountRecv(SDHP_COMMAND_BAN_ACCOUNT_RECV* lpMsg, int index) // OK
{
	SDHP_COMMAND_BAN_ACCOUNT_SEND pMsg;

	pMsg.header.set(0x0F,0x06,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.account,lpMsg->account,sizeof(pMsg.account));

	pMsg.BlocCode = lpMsg->BlocCode;

	if(gQueryManager.ExecQuery("EXEC WZ_BanAccount '%s','%d'",lpMsg->account,lpMsg->BlocCode) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		pMsg.result = 0;

		gQueryManager.Close();
	}
	else
	{
		pMsg.result = gQueryManager.GetResult(0);

		gQueryManager.Close();
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandBanCharacterRecv(SDHP_COMMAND_BAN_CHARACTER_RECV* lpMsg, int index) // OK
{
	SDHP_COMMAND_BAN_CHARACTER_SEND pMsg;

	pMsg.header.set(0x0F,0x07,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	memcpy(pMsg.name,lpMsg->name,sizeof(pMsg.name));

	pMsg.CtlCode = lpMsg->CtlCode;

	if(gQueryManager.ExecQuery("EXEC WZ_BanCharacter '%s','%d'",lpMsg->name,lpMsg->CtlCode) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		pMsg.result = 0;

		gQueryManager.Close();
	}
	else
	{
		pMsg.result = gQueryManager.GetResult(0);

		gQueryManager.Close();
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,pMsg.header.size);
}

void CCommandManager::GDCommandGiftRecv(SDHP_GIFT_RECV* lpMsg,int index) // OK
{

	SDHP_GIFT_SEND pMsg;

	pMsg.header.set(0x0F,0x08,sizeof(pMsg));

	pMsg.index = lpMsg->index;

	pMsg.result = 0;

	if(gQueryManager.ExecQuery("SELECT * FROM CustomGift WHERE AccountID='%s'",lpMsg->account) == 0 || gQueryManager.Fetch() == SQL_NO_DATA)
	{
		gQueryManager.Close();

		if(gQueryManager.ExecQuery("INSERT INTO CustomGift (AccountID,Quantity) VALUES ('%s',1)",lpMsg->account) == 0)
		{
			gQueryManager.Close();

			pMsg.result = 0;
		}
		else
		{
			gQueryManager.Close();

			pMsg.result = 1;
		}
	}
	else
	{
		pMsg.result = gQueryManager.GetAsInteger("Quantity")+1;
		gQueryManager.Close();
		gQueryManager.ExecQuery("UPDATE CustomGift SET Quantity=Quantity+1 WHERE AccountID='%s'",lpMsg->account);
		gQueryManager.Close();
	}

	gSocketManager.DataSend(index,(BYTE*)&pMsg,sizeof(pMsg));

}


void CCommandManager::GDCommandTopRecv(SDHP_TOP_RECV* lpMsg,int index) // OK
{
	BYTE send[4096];

	SDHP_TOP_SEND pMsg;

	pMsg.header.set(0x0F,0x09,0);

	int size = sizeof(pMsg);

	pMsg.index = lpMsg->index;

	pMsg.type = lpMsg->type;

	pMsg.classe = lpMsg->classe;

	pMsg.count = 0;

	SDHP_TOP_INFO info;

	int WZclasse = (lpMsg->classe == 999) ? -1: lpMsg->classe;

	if(gQueryManager.ExecQuery("EXEC WZ_CustomTop %d,%d",lpMsg->type,WZclasse) != 0)
	{
		while(gQueryManager.Fetch() != SQL_NO_DATA)
		{
			gQueryManager.GetAsString("VALUE1",info.name,sizeof(info.name));
			info.value = gQueryManager.GetAsInteger("VALUE2");

			memcpy(&send[size],&info,sizeof(info));
			size += sizeof(info);

			pMsg.count++;
		}
	}

	gQueryManager.Close();

	pMsg.header.size[0] = SET_NUMBERHB(size);
	pMsg.header.size[1] = SET_NUMBERLB(size);

	memcpy(send,&pMsg,sizeof(pMsg));

	//LogAdd(LOG_BLACK,"valor %d",pMsg.count);

	gSocketManager.DataSend(index,send,size);

}

