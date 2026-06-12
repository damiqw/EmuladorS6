#include "stdafx.h"
#include "CustomJewelBank.h"
#include "CommandManager.h"
#include "DSProtocol.h"
#include "GameMain.h"
#include "ItemManager.h"
#include "Message.h"
#include "Notice.h"
#include "Util.h"

CCustomJewelBank gCustomJewelBank;

void CCustomJewelBank::LoadConfig(char* FilePath)
{
	pugi::xml_document file;
	pugi::xml_parse_result res = file.load_file(FilePath);
	if (res.status != pugi::status_ok) 
	{
		ErrorMessageBox("File %s load fail. Error: %s", FilePath, res.description());
		return;
	}
	pugi::xml_node IsBankConfig = file.child("SPK");

	this->Enable		= IsBankConfig.attribute("Enable").as_int();
	this->MaxPage		= IsBankConfig.attribute("MaxPages").as_int();
	this->JewelMaxCount = IsBankConfig.attribute("MaxCount").as_int();

	pugi::xml_node Message = IsBankConfig.child("Message");
	for (pugi::xml_node msg = Message.child("Msg"); msg; msg = msg.next_sibling())
	{
		MESSAGE_INFO_JWBANK info;
		info.Index = msg.attribute("Index").as_int();
		strcpy_s(info.Message, msg.attribute("Text").as_string());
		this->m_MessageInfoBP.insert(std::pair<int, MESSAGE_INFO_JWBANK>(info.Index, info));
	}
}
char* CCustomJewelBank::GetMessage(int index)
{
	std::map<int, MESSAGE_INFO_JWBANK>::iterator it = this->m_MessageInfoBP.find(index);
	if (it == this->m_MessageInfoBP.end())
	{
		char Error[256];
		wsprintf(Error, "Could not find message %d!", index);
		return Error;
	}
	else
	{
		return it->second.Message;
	}
}
void CCustomJewelBank::GCCustomJewelBankInfoSend(LPOBJ lpObj)
{
	if (gObjIsConnectedGP(lpObj->Index) == 0)
	{
		return;
	}
	PSBMSG_JEWELBANK_SEND pMsg = { 0 };
	pMsg.h.set(0xF3, 0xF5, sizeof(pMsg));

	for (int M = 0; M < MAX_ITEM_SLOT; M++)
	{
		pMsg.ItemBank[M] = lpObj->ItemBank[M];
	}

	pMsg.Enable = this->Enable;
	pMsg.JewelMaxCount = this->JewelMaxCount;
	pMsg.MaxPage = this->MaxPage;

	DataSend(lpObj->Index, (BYTE*)&pMsg, pMsg.h.size);
}
int CCustomJewelBank::GetJewelSimpleType(int ItemIndex) // OK
{ 
	switch (ItemIndex)
	{
		case GET_ITEM(14, 13):	return 0;	//"Ngọc Ước Nguyện"
		case GET_ITEM(14, 14):	return 1;	//"Ngọc Tâm Linh"
		case GET_ITEM(14, 16):	return 2;	//"Ngọc Sinh Mệnh"
		case GET_ITEM(14, 22):	return 3;	//"Ngọc Sáng Tạo"
		case GET_ITEM(14, 31):	return 4;	//"Đá Hộ Mệnh"
		case GET_ITEM(14, 41):	return 5;	//"Đá Tạo Hóa"
		case GET_ITEM(14, 42):	return 6;	//"Đá Nguyên Thủy"
		case GET_ITEM(12, 15):	return 7;	//"Ngọc Hỗn Nguyên"
		case GET_ITEM(14, 43):	return 8;	//"Đá Cấp Thấp"
		case GET_ITEM(14, 44):	return 9;	//"Đá Cấp Cao"

		case GET_ITEM(12, 30):	return 10;	//"Cụm Ngọc Ước Nguyện"
		case GET_ITEM(12, 31):	return 11;	//"Cụm Ngọc Tâm Linh"	
		case GET_ITEM(12, 136):	return 12;	//"Cụm Ngọc Sinh Mệnh"
		case GET_ITEM(12, 137):	return 13;	//"Cụm Ngọc Sáng Tạo"	
		case GET_ITEM(12, 138):	return 14;	//"Cụm Đá Hộ Mệnh"	
		case GET_ITEM(12, 139):	return 15;	//"Cụm Đá Nguyên Thủy"
		case GET_ITEM(12, 140):	return 16;	//"Cụm Đá Tạo Hóa"
		case GET_ITEM(12, 141):	return 17;	//"Cụm Ngọc Hỗn Nguyên"
		case GET_ITEM(12, 142):	return 18;	//"Cụm Đá Tinh Luyện 1"
		case GET_ITEM(12, 143):	return 19;	//"Cụm Đá Tinh Luyện 2"
		
		case GET_ITEM(14, 244):	return 20;	//"Ngọc Cấp Độ"
		case GET_ITEM(14, 245):	return 21;	//"Ngọc Tuyệt Chiêu"
		case GET_ITEM(14, 246):	return 22;	//"Ngọc May Mắn"
		case GET_ITEM(14, 247):	return 23;	//"Ngọc Tính Năng"
		case GET_ITEM(14, 248):	return 24;	//"Ngọc Hoàn Hảo"
		case GET_ITEM(14, 249):	return 25;	//"Ngọc Socket"	
		case GET_ITEM(14, 250):	return 26;	//"Ngọc Thần Loại 1"
		case GET_ITEM(14, 251):	return 27;	//"Ngọc Thần Loại 2"
		case GET_ITEM(14, 252):	return 28;	//"Ngọc Full"
		case GET_ITEM(14, 260):	return 29;	//"Ngọc Nâng Cấp"

		case GET_ITEM(12, 32):	return 30;	//"Hộp Quà Đỏ",			
		case GET_ITEM(12, 33):	return 31;	//"Hộp Quà Xanh Lá",		
		case GET_ITEM(12, 34):	return 32;	//"Hộp Quà Xanh Dương",	
		case GET_ITEM(14, 52):	return 33;	//"Box GM",				
		case GET_ITEM(14, 55):	return 34;	//"Box Trang Bị 380",	
		case GET_ITEM(14, 56):	return 35;	//"Box Vũ Khí Cấp 4",	
		case GET_ITEM(14, 57):	return 36;	//"Box Khiên Cấp 4",		
		case GET_ITEM(14, 51):	return 37;	//"Pháo Hoa Ngôi Sao",	
		case GET_ITEM(14, 121):	return 38;	//"Hộp Quà Vàng",		
		case GET_ITEM(14, 122):	return 39;	//"Hộp Quà Bạc",			
	}
	return -1;
}

int CCustomJewelBank::GetJewelSimpleIndex(int type) // OK
{ 
	switch (type)
	{
		case 0:		return GET_ITEM(14, 13); //"Ngọc Ước Nguyện"
		case 1:		return GET_ITEM(14, 14); //"Ngọc Tâm Linh"
		case 2:		return GET_ITEM(14, 16); //"Ngọc Sinh Mệnh"
		case 3:		return GET_ITEM(14, 22); //"Ngọc Sáng Tạo"
		case 4:		return GET_ITEM(14, 31); //"Đá Hộ Mệnh"
		case 5:		return GET_ITEM(14, 41); //"Đá Tạo Hóa"
		case 6:		return GET_ITEM(14, 42); //"Đá Nguyên Thủy"
		case 7:		return GET_ITEM(12, 15); //"Ngọc Hỗn Nguyên"
		case 8:		return GET_ITEM(14, 43); //"Đá Cấp Thấp"
		case 9:		return GET_ITEM(14, 44); //"Đá Cấp Cao"

		case 20:	return GET_ITEM(14, 244); //"Ngọc Cấp Độ"
		case 21:	return GET_ITEM(14, 245); //"Ngọc Tuyệt Chiêu"
		case 22:	return GET_ITEM(14, 246); //"Ngọc May Mắn"
		case 23:	return GET_ITEM(14, 247); //"Ngọc Tính Năng"
		case 24:	return GET_ITEM(14, 248); //"Ngọc Hoàn Hảo"
		case 25:	return GET_ITEM(14, 249); //"Ngọc Socket"	
		case 26:	return GET_ITEM(14, 250); //"Ngọc Thần Loại 1"
		case 27:	return GET_ITEM(14, 251); //"Ngọc Thần Loại 2"
		case 28:	return GET_ITEM(14, 252); //"Ngọc Full"
		case 29:	return GET_ITEM(14, 260); //"Ngọc Nâng Cấp"

		case 30:	return GET_ITEM(12, 32);	//"Hộp Quà Đỏ",			
		case 31:	return GET_ITEM(12, 33);	//"Hộp Quà Xanh Lá",		
		case 32:	return GET_ITEM(12, 34);	//"Hộp Quà Xanh Dương",	
		case 33:	return GET_ITEM(14, 52);	//"Box GM",				
		case 34:	return GET_ITEM(14, 55);	//"Box Trang Bị 380",	
		case 35:	return GET_ITEM(14, 56);	//"Box Vũ Khí Cấp 4",	
		case 36:	return GET_ITEM(14, 57);	//"Box Khiên Cấp 4",		
		case 37:	return GET_ITEM(14, 51);	//"Pháo Hoa Ngôi Sao",	
		case 38:	return GET_ITEM(14, 121);	//"Hộp Quà Vàng",		
		case 39:	return GET_ITEM(14, 122);	//"Hộp Quà Bạc",			
	}
	return -1;
}

int CCustomJewelBank::GetJewelBundleIndex(int type) // OK
{
	switch (type)
	{
		case 0:		return GET_ITEM(12, 30);	//"Cụm Ngọc Ước Nguyện"
		case 1:		return GET_ITEM(12, 31);	//"Cụm Ngọc Tâm Linh"	
		case 2:		return GET_ITEM(12, 136);	//"Cụm Ngọc Sinh Mệnh"
		case 3:		return GET_ITEM(12, 137);	//"Cụm Ngọc Sáng Tạo"	
		case 4:		return GET_ITEM(12, 138);	//"Cụm Đá Hộ Mệnh"	
		case 5:		return GET_ITEM(12, 139);	//"Cụm Đá Nguyên Thủy"
		case 6:		return GET_ITEM(12, 140);	//"Cụm Đá Tạo Hóa"
		case 7:		return GET_ITEM(12, 141);	//"Cụm Ngọc Hỗn Nguyên"
		case 8:		return GET_ITEM(12, 142);	//"Cụm Đá Tinh Luyện 1"
		case 9:		return GET_ITEM(12, 143);	//"Cụm Đá Tinh Luyện 2"
	}
	return -1;
}

void CCustomJewelBank::JewelBankRecv(PSBMSG_JEWELBANK_RECV* lpMsg, int aIndex)
{
	if (!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];

	int Slot = lpMsg->slot;

	if (gObjIsConnectedGP(aIndex) == 0 || lpObj->TradeDuel == 1 || lpObj->Interface.use != 0 || lpObj->ChaosLock != 0 || INVENTORY_FULL_RANGE(Slot) == 0 || lpObj->Inventory[Slot].IsItem() == 0)
	{
		return;
	}

	int JewelIndex = this->GetJewelSimpleType(lpObj->Inventory[Slot].m_Index);

	if (JewelIndex >= 0)
	{
		int JewelType;
		int JewelCount;

		if (JewelIndex >= 10 && JewelIndex < 20)
		{
			JewelType = JewelIndex - 10;
			JewelCount = 10 * (lpObj->Inventory[Slot].m_Level + 1);
		}
		else
		{
			JewelType = JewelIndex;
			JewelCount = gItemManager.GetInventoryItemCount(lpObj,lpObj->Inventory[Slot].m_Index,lpObj->Inventory[Slot].m_Level);
		}
		#if(BUNDLE_ITEM)
		if (JewelCount < 0 || JewelCount > 32640)
		#else
		if (JewelCount < 0 || JewelCount > 160)
		#endif
		{
			return;
		}

		switch (JewelType)
		{
			case 0:		lpObj->ItemBank[0]	+= JewelCount;	break;
			case 1:		lpObj->ItemBank[1]	+= JewelCount;	break;
			case 2:		lpObj->ItemBank[2]	+= JewelCount;	break;
			case 3:		lpObj->ItemBank[3]	+= JewelCount;	break;
			case 4:		lpObj->ItemBank[4]	+= JewelCount;	break;
			case 5:		lpObj->ItemBank[5]	+= JewelCount;	break;
			case 6:		lpObj->ItemBank[6]	+= JewelCount;	break;
			case 7:		lpObj->ItemBank[7]	+= JewelCount;	break;
			case 8:		lpObj->ItemBank[8]	+= JewelCount;	break;
			case 9:		lpObj->ItemBank[9]	+= JewelCount;	break;
			case 20:	lpObj->ItemBank[10] += JewelCount;	break;
			case 21:	lpObj->ItemBank[11] += JewelCount;	break;
			case 22:	lpObj->ItemBank[12] += JewelCount;	break;
			case 23:	lpObj->ItemBank[13] += JewelCount;	break;
			case 24:	lpObj->ItemBank[14] += JewelCount;	break;
			case 25:	lpObj->ItemBank[15] += JewelCount;	break;
			case 26:	lpObj->ItemBank[16] += JewelCount;	break;
			case 27:	lpObj->ItemBank[17] += JewelCount;	break;
			case 28:	lpObj->ItemBank[18] += JewelCount;	break;
			case 29:	lpObj->ItemBank[19] += JewelCount;	break;
			case 30:	lpObj->ItemBank[20] += JewelCount;	break;
			case 31:	lpObj->ItemBank[21] += JewelCount;	break;
			case 32:	lpObj->ItemBank[22] += JewelCount;	break;
			case 33:	lpObj->ItemBank[23] += JewelCount;	break;
			case 34:	lpObj->ItemBank[24] += JewelCount;	break;
			case 35:	lpObj->ItemBank[25] += JewelCount;	break;
			case 36:	lpObj->ItemBank[26] += JewelCount;	break;
			case 37:	lpObj->ItemBank[27] += JewelCount;	break;
			case 38:	lpObj->ItemBank[28] += JewelCount;	break;
			case 39:	lpObj->ItemBank[29] += JewelCount;	break;
		}

		if(JewelIndex >= 10 && JewelIndex < 20)
		{
			gItemManager.InventoryDelItem(aIndex, Slot);
			gItemManager.GCItemDeleteSend(aIndex, Slot, 1);
		} 
		else
		{
			gItemManager.DeleteInventoryItemCount(lpObj,lpObj->Inventory[Slot].m_Index,lpObj->Inventory[Slot].m_Level,JewelCount);
		}		
		
		SDHP_CUSTOM_JEWELBANK_SEND pMsg = { 0 };
		pMsg.header.set(0xF7, 0x04, sizeof(pMsg));
		pMsg.index = lpObj->Index;
		memcpy(pMsg.account, lpObj->Account, sizeof(pMsg.account));
		pMsg.type = JewelType;
		pMsg.count = JewelCount;
		gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
		this->GCCustomJewelBankInfoSend(lpObj);
	}
}
void CCustomJewelBank::JewelBankWithDrawRecv(PSBMSG_JEWELBANKWITHDRAW_RECV* lpMsg, int aIndex)
{
	if (!this->Enable) return;
	LPOBJ lpObj = &gObj[aIndex];

	int Type = lpMsg->type;
	int Count = lpMsg->count;

	if (gObjIsConnectedGP(aIndex) == 0 || lpObj->Interface.use != 0 || lpObj->ChaosLock != 0 || lpObj->TradeDuel == 1 || Type < 0 || Count < 0)
	{
		return;
	}
	if (lpObj->Interface.type == INTERFACE_CHAOS_BOX || lpObj->Interface.type == INTERFACE_TRADE || lpObj->Interface.type == INTERFACE_CASH_SHOP || lpObj->Interface.type == INTERFACE_TRAINER)
	{
		return;
	}
	int FreeSpaces = gItemManager.CheckItemInventorySpaceCount(lpObj, 1, 1);

	if (FreeSpaces <= 0)
	{
		gNotice.GCNoticeSend(lpObj->Index, 1, 0, 0, 0, 0, 0, this->GetMessage(1));
		return;
	}
	int JewelCount = Count;
	if (Count == 99)
	{
		JewelCount = FreeSpaces;

		if (JewelCount > this->JewelMaxCount)
		{
			JewelCount = this->JewelMaxCount;
		}
	}
	
	switch (Type)
	{
		case 0: if (Count == 99 && lpObj->ItemBank[0] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[0];
							   lpObj->ItemBank[0] = 0;		}
					   else if(lpObj->ItemBank[0] < JewelCount){return;}else{
							   lpObj->ItemBank[0] -= JewelCount;}
		break;
		case 1:	if (Count == 99 && lpObj->ItemBank[1] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[1];
							   lpObj->ItemBank[1] = 0;		}
					   else if(lpObj->ItemBank[1] < JewelCount){return;}else{
							   lpObj->ItemBank[1] -= JewelCount;}
		break;
		case 2:	if (Count == 99 && lpObj->ItemBank[2] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[2];
							   lpObj->ItemBank[2] = 0;		}
					   else if(lpObj->ItemBank[2] < JewelCount){return;}else{
							   lpObj->ItemBank[2] -= JewelCount;}
		break;
		case 3:	if (Count == 99 && lpObj->ItemBank[3] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[3];
							   lpObj->ItemBank[3] = 0;		}
					   else if(lpObj->ItemBank[3] < JewelCount){return;}else{
							   lpObj->ItemBank[3] -= JewelCount;}
		break;
		case 4: if (Count == 99 && lpObj->ItemBank[4] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[4];
							   lpObj->ItemBank[4] = 0;		}
					   else if(lpObj->ItemBank[4] < JewelCount){return;}else{
							   lpObj->ItemBank[4] -= JewelCount;}
		break;
		case 5:	if (Count == 99 && lpObj->ItemBank[5] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[5];
							   lpObj->ItemBank[5] = 0;		}
					   else if(lpObj->ItemBank[5] < JewelCount){return;}else{
							   lpObj->ItemBank[5] -= JewelCount;}
		break;
		case 6:	if (Count == 99 && lpObj->ItemBank[6] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[6];
							   lpObj->ItemBank[6] = 0;		}
					   else if(lpObj->ItemBank[6] < JewelCount){return;}else{
							   lpObj->ItemBank[6] -= JewelCount;}
		break;
		case 7:	if (Count == 99 && lpObj->ItemBank[7] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[7];
							   lpObj->ItemBank[7] = 0;		}
					   else if(lpObj->ItemBank[7] < JewelCount){return;}else{
							   lpObj->ItemBank[7] -= JewelCount;}
		break;
		case 8:	if (Count == 99 && lpObj->ItemBank[8] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[8];
							   lpObj->ItemBank[8] = 0;		}
					   else if(lpObj->ItemBank[8] < JewelCount){return;}else{
							   lpObj->ItemBank[8] -= JewelCount;}
		break;
		case 9:	if (Count == 99 && lpObj->ItemBank[9] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[9];
							   lpObj->ItemBank[9] = 0;		}
					   else if(lpObj->ItemBank[9] < JewelCount){return;}else{
							   lpObj->ItemBank[9] -= JewelCount;}
		break;
		case 20:if (Count == 99 && lpObj->ItemBank[10] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[10];
							   lpObj->ItemBank[10] = 0;		}
					   else if(lpObj->ItemBank[10] < JewelCount){return;}else{
							   lpObj->ItemBank[10] -= JewelCount;}
		break;
		case 21:if (Count == 99 && lpObj->ItemBank[11] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[11];
							   lpObj->ItemBank[11] = 0;		}
					   else if(lpObj->ItemBank[11] < JewelCount){return;}else{
							   lpObj->ItemBank[11] -= JewelCount;}
		break;
		case 22:if (Count == 99 && lpObj->ItemBank[12] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[12];
							   lpObj->ItemBank[12] = 0;		}
					   else if(lpObj->ItemBank[12] < JewelCount){return;}else{
							   lpObj->ItemBank[12] -= JewelCount;}
		break;
		case 23:if (Count == 99 && lpObj->ItemBank[13] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[13];
							   lpObj->ItemBank[13] = 0;		}
					   else if(lpObj->ItemBank[13] < JewelCount){return;}else{
							   lpObj->ItemBank[13] -= JewelCount;}
		break;
		case 24:if (Count == 99 && lpObj->ItemBank[14] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[14];
							   lpObj->ItemBank[14] = 0;		}
					   else if(lpObj->ItemBank[14] < JewelCount){return;}else{
							   lpObj->ItemBank[14] -= JewelCount;}
		break;
		case 25:if (Count == 99 && lpObj->ItemBank[15] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[15];
							   lpObj->ItemBank[15] = 0;		}
					   else if(lpObj->ItemBank[15] < JewelCount){return;}else{
							   lpObj->ItemBank[15] -= JewelCount;}
		break;
		case 26:if (Count == 99 && lpObj->ItemBank[16] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[16];
							   lpObj->ItemBank[16] = 0;		}
					   else if(lpObj->ItemBank[16] < JewelCount){return;}else{
							   lpObj->ItemBank[16] -= JewelCount;}
		break;
		case 27:if (Count == 99 && lpObj->ItemBank[17] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[17];
							   lpObj->ItemBank[17] = 0;		}
					   else if(lpObj->ItemBank[17] < JewelCount){return;}else{
							   lpObj->ItemBank[17] -= JewelCount;}
		break;
		case 28:if (Count == 99 && lpObj->ItemBank[18] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[18];
							   lpObj->ItemBank[18] = 0;		}
					   else if(lpObj->ItemBank[18] < JewelCount){return;}else{
							   lpObj->ItemBank[18] -= JewelCount;}
		break;
		case 29:if (Count == 99 && lpObj->ItemBank[19] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[19];
							   lpObj->ItemBank[19] = 0;		}
					   else if(lpObj->ItemBank[19] < JewelCount){return;}else{
							   lpObj->ItemBank[19] -= JewelCount;}
		break;	
		case 30:
			if (Count == 99 && lpObj->ItemBank[20] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[20];
							   lpObj->ItemBank[20] = 0;		}
					   else if(lpObj->ItemBank[20] < JewelCount){return;}else{
							   lpObj->ItemBank[20] -= JewelCount;}
		break;	
		case 31:
			if (Count == 99 && lpObj->ItemBank[21] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[21];
							   lpObj->ItemBank[21] = 0;		}
					   else if(lpObj->ItemBank[21] < JewelCount){return;}else{
							   lpObj->ItemBank[21] -= JewelCount;}
		break;	
		case 32:
			if (Count == 99 && lpObj->ItemBank[22] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[22];
							   lpObj->ItemBank[22] = 0;		}
					   else if(lpObj->ItemBank[22] < JewelCount){return;}else{
							   lpObj->ItemBank[22] -= JewelCount;}
		break;	
		case 33:
			if (Count == 99 && lpObj->ItemBank[23] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[23];
							   lpObj->ItemBank[23] = 0;		}
					   else if(lpObj->ItemBank[23] < JewelCount){return;}else{
							   lpObj->ItemBank[23] -= JewelCount;}
		break;	
		case 34:
			if (Count == 99 && lpObj->ItemBank[24] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[24];
							   lpObj->ItemBank[24] = 0;		}
					   else if(lpObj->ItemBank[24] < JewelCount){return;}else{
							   lpObj->ItemBank[24] -= JewelCount;}
		break;	
		case 35:
			if (Count == 99 && lpObj->ItemBank[25] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[25];
							   lpObj->ItemBank[25] = 0;		}
					   else if(lpObj->ItemBank[25] < JewelCount){return;}else{
							   lpObj->ItemBank[25] -= JewelCount;}
		break;	
		case 36:
			if (Count == 99 && lpObj->ItemBank[26] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[26];
							   lpObj->ItemBank[26] = 0;		}
					   else if(lpObj->ItemBank[26] < JewelCount){return;}else{
							   lpObj->ItemBank[26] -= JewelCount;}
		break;	
		case 37:
			if (Count == 99 && lpObj->ItemBank[27] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[27];
							   lpObj->ItemBank[27] = 0;		}
					   else if(lpObj->ItemBank[27] < JewelCount){return;}else{
							   lpObj->ItemBank[27] -= JewelCount;}
		break;	
		case 38:
			if (Count == 99 && lpObj->ItemBank[28] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[28];
							   lpObj->ItemBank[28] = 0;		}
					   else if(lpObj->ItemBank[28] < JewelCount){return;}else{
							   lpObj->ItemBank[28] -= JewelCount;}
		break;	
		case 39:
			if (Count == 99 && lpObj->ItemBank[29] < JewelCount)	{
				  JewelCount = lpObj->ItemBank[29];
							   lpObj->ItemBank[29] = 0;		}
					   else if(lpObj->ItemBank[29] < JewelCount){return;}else{
							   lpObj->ItemBank[29] -= JewelCount;}
		break;	
	}

	int ItemIndex = this->GetJewelSimpleIndex(Type);
	if (ItemIndex < 0)
	{
		return;
	}
	int ItemLevel = 0;
	int stack = 0;
	if (Count != 99)
	{
		if (Type < 10)
		{
			if (JewelCount == 10)
			{
				ItemIndex = this->GetJewelBundleIndex(Type);
			}
			else if (JewelCount == 20)
			{
				ItemIndex = this->GetJewelBundleIndex(Type);
				ItemLevel = 1;
			}
			else if (JewelCount == 30)
			{
				ItemIndex = this->GetJewelBundleIndex(Type);
				ItemLevel = 2;
			}
		}
		else if (Type > 10)
		{
			ItemLevel = 0;
			stack = JewelCount;
		}
	}
	if (Count == 99)
	{
		for (int i = 0; i < JewelCount; i++)
		{
			GDCreateItemSend(aIndex, 0xEB, 0, 0, ItemIndex, ItemLevel, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0xFF, 0);
		}
	}
	else
	{
		GDCreateItemSend(aIndex, 0xEB, 0, 0, ItemIndex, ItemLevel, stack, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0xFF, 0);
	}

	SDHP_CUSTOM_JEWELBANK_SEND pMsg = { 0 };
	pMsg.header.set(0xF7, 0x04, sizeof(pMsg));
	pMsg.index = lpObj->Index;
	memcpy(pMsg.account, lpObj->Account, sizeof(pMsg.account));
	pMsg.type = Type;
	pMsg.count = -(JewelCount);
	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
	this->GCCustomJewelBankInfoSend(lpObj);
}

void CCustomJewelBank::CustomJewelBankInfoSend(int index)
{
	LPOBJ lpObj = &gObj[index];

	if (gObjIsConnectedGP(index) == 0)
	{
		return;
	}
	SDHP_CUSTOM_JEWELBANK_INFO_SEND pMsg = { 0 };
	pMsg.header.set(0xF7, 0x05, sizeof(pMsg));
	pMsg.index = lpObj->Index;
	memcpy(pMsg.account, lpObj->Account, sizeof(pMsg.account));
	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
}

void CCustomJewelBank::CustomJewelBankInfoRecv(SDHP_CUSTOM_JEWELBANK_INFO_RECV* lpMsg)
{
	LPOBJ lpObj = &gObj[lpMsg->index];

	if (gObjIsConnectedGP(lpMsg->index) == 0)
	{
		return;
	}
	for (int M = 0; M < MAX_ITEM_SLOT; M++)
	{
		lpObj->ItemBank[M] = lpMsg->ItemBank[M];
	}
	this->GCCustomJewelBankInfoSend(lpObj);
}

void CCustomJewelBank::GDCustomJewelBankAddJewel(LPOBJ lpObj, int type, int qtd)
{
	switch (type)
	{
		case 0:		lpObj->ItemBank[0]	+= qtd; break; //"Ngọc Ước Nguyện"
		case 1:		lpObj->ItemBank[1]	+= qtd; break; //"Ngọc Tâm Linh"
		case 2:		lpObj->ItemBank[2]	+= qtd; break; //"Ngọc Sinh Mệnh"
		case 3:		lpObj->ItemBank[3]	+= qtd; break; //"Ngọc Sáng Tạo"
		case 4:		lpObj->ItemBank[4]	+= qtd; break; //"Đá Hộ Mệnh"
		case 5:		lpObj->ItemBank[5]	+= qtd; break; //"Đá Tạo Hóa"
		case 6:		lpObj->ItemBank[6]	+= qtd; break; //"Đá Nguyên Thủy"
		case 7:		lpObj->ItemBank[7]	+= qtd; break; //"Ngọc Hỗn Nguyên"
		case 8:		lpObj->ItemBank[8]	+= qtd; break; //"Đá Cấp Thấp"
		case 9:		lpObj->ItemBank[9]	+= qtd; break; //"Đá Cấp Cao"
		case 20:	lpObj->ItemBank[10] += qtd; break; //"Cụm Ngọc Ước Nguyện"
		case 21:	lpObj->ItemBank[11] += qtd; break; //"Cụm Ngọc Tâm Linh"	
		case 22:	lpObj->ItemBank[12] += qtd; break; //"Cụm Ngọc Sinh Mệnh"
		case 23:	lpObj->ItemBank[13] += qtd; break; //"Cụm Ngọc Sáng Tạo"	
		case 24:	lpObj->ItemBank[14] += qtd; break; //"Cụm Đá Hộ Mệnh"	
		case 25:	lpObj->ItemBank[15] += qtd; break; //"Cụm Đá Nguyên Thủy"
		case 26:	lpObj->ItemBank[16] += qtd; break; //"Cụm Đá Tạo Hóa"
		case 27:	lpObj->ItemBank[17] += qtd; break; //"Cụm Ngọc Hỗn Nguyên"
		case 28:	lpObj->ItemBank[18] += qtd; break; //"Cụm Đá Tinh Luyện 1"
		case 29:	lpObj->ItemBank[19] += qtd; break; //"Cụm Đá Tinh Luyện 2"
		case 30:	lpObj->ItemBank[20] += qtd; break; //"Ngọc Cấp Độ"
		case 31:	lpObj->ItemBank[21] += qtd; break; //"Ngọc Tuyệt Chiêu"
		case 32:	lpObj->ItemBank[22] += qtd; break; //"Ngọc May Mắn"
		case 33:	lpObj->ItemBank[23] += qtd; break; //"Ngọc Tính Năng"
		case 34:	lpObj->ItemBank[24] += qtd; break; //"Ngọc Hoàn Hảo"
		case 35:	lpObj->ItemBank[25] += qtd; break; //"Ngọc Socket"	
		case 36:	lpObj->ItemBank[26] += qtd; break; //"Ngọc Thần Loại 1"
		case 37:	lpObj->ItemBank[27] += qtd; break; //"Ngọc Thần Loại 2"
		case 38:	lpObj->ItemBank[28] += qtd; break; //"Ngọc Full"
		case 39:	lpObj->ItemBank[29] += qtd; break; //"Ngọc Nâng Cấp"
	}

	SDHP_CUSTOM_JEWELBANK_SEND pMsg = { 0 };
	pMsg.header.set(0xF7, 0x04, sizeof(pMsg));
	pMsg.index = lpObj->Index;
	memcpy(pMsg.account, lpObj->Account, sizeof(pMsg.account));
	pMsg.type = type;
	pMsg.count = qtd;
	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
	this->GCCustomJewelBankInfoSend(lpObj);
}

void CCustomJewelBank::GDCustomJewelBankDelJewel(LPOBJ lpObj, int type, int qtd)
{
	switch (type)
	{
		case 0:		lpObj->ItemBank[0]	-= qtd; break;
		case 1:		lpObj->ItemBank[1]	-= qtd; break;
		case 2:		lpObj->ItemBank[2]	-= qtd; break;
		case 3:		lpObj->ItemBank[3]	-= qtd; break;
		case 4:		lpObj->ItemBank[4]	-= qtd; break;
		case 5:		lpObj->ItemBank[5]	-= qtd; break;
		case 6:		lpObj->ItemBank[6]	-= qtd; break;
		case 7:		lpObj->ItemBank[7]	-= qtd; break;
		case 8:		lpObj->ItemBank[8]	-= qtd; break;
		case 9:		lpObj->ItemBank[9]	-= qtd; break;
		case 20:	lpObj->ItemBank[10] -= qtd; break;
		case 21:	lpObj->ItemBank[11] -= qtd; break;
		case 22:	lpObj->ItemBank[12] -= qtd; break;
		case 23:	lpObj->ItemBank[13] -= qtd; break;
		case 24:	lpObj->ItemBank[14] -= qtd; break;
		case 25:	lpObj->ItemBank[15] -= qtd; break;
		case 26:	lpObj->ItemBank[16] -= qtd; break;
		case 27:	lpObj->ItemBank[17] -= qtd; break;
		case 28:	lpObj->ItemBank[18] -= qtd; break;
		case 29:	lpObj->ItemBank[19] -= qtd; break;
		case 30:	lpObj->ItemBank[20] -= qtd; break;
		case 31:	lpObj->ItemBank[21] -= qtd; break;
		case 32:	lpObj->ItemBank[22] -= qtd; break;
		case 33:	lpObj->ItemBank[23] -= qtd; break;
		case 34:	lpObj->ItemBank[24] -= qtd; break;
		case 35:	lpObj->ItemBank[25] -= qtd; break;
		case 36:	lpObj->ItemBank[26] -= qtd; break;
		case 37:	lpObj->ItemBank[27] -= qtd; break;
		case 38:	lpObj->ItemBank[28] -= qtd; break;
		case 39:	lpObj->ItemBank[29] -= qtd; break;
	}

	SDHP_CUSTOM_JEWELBANK_SEND pMsg = { 0 };
	pMsg.header.set(0xF7, 0x04, sizeof(pMsg));
	pMsg.index = lpObj->Index;
	memcpy(pMsg.account, lpObj->Account, sizeof(pMsg.account));
	pMsg.type = type;
	pMsg.count = -(qtd);
	gDataServerConnection.DataSend((BYTE*)&pMsg, sizeof(pMsg));
	this->GCCustomJewelBankInfoSend(lpObj);
}