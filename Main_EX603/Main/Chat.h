#pragma once

struct ChatTextObj
{
	int unk1;
	BYTE unk4;
	BYTE unk6;
	BYTE unk7;
	BYTE unk8;
	BYTE unk9;
	BYTE unk10;
	BYTE unk11;
	BYTE unk12;
	BYTE unk13;
	BYTE unk14;
	BYTE unk15;
	BYTE unk16;
	BYTE unk17;
	BYTE unk18;
	BYTE unk19;
	BYTE unk20_;
	DWORD unk20;
	DWORD unk24;
	BYTE gap1[46];
};

class cChat
{
public:
	cChat();
	~cChat();
	void CreateMessage(char* strID, char* strText, int MsgType);
	void CreatePlayerHeadMessage(char* m, int i);
private:

};

extern cChat Chat;