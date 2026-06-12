#pragma once
#define WD_81KARUTAN2			81
#define WD_ENDMAP				150

typedef struct
{
	int world;
	int LineText;
	char MapName[30];
	char lpszMp3[30];
}PathMap;

class CUIMapName
{
public:
	CUIMapName(void);
	virtual ~CUIMapName(void);
	bool OpenScritp(char* path);

	PathMap m_MapInfo[MAX_CUSTOM_MAP];
};
extern CUIMapName g_pUIMapName;