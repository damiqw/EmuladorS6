#pragma once

struct CUSTOM_POSITION_INFO
{
	int		Index;
	int		ItemIndex;
	float	translationX;
	float	translationY;
	float	RotationX;
	float	RotationY;
	float	RotationZ;
	float	Scale;
	float	ScaleDrop;
};

class cCustomPosition
{
public:
	cCustomPosition();
	virtual ~cCustomPosition();
	void Init();
	bool Load(char* path);
	void SetInfo(CUSTOM_POSITION_INFO info);
public:
	CUSTOM_POSITION_INFO m_CustomPositionInfo[MAX_POSITION_ITEM];
};

extern cCustomPosition gCustomPosition;
