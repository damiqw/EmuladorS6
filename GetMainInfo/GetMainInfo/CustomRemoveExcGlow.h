#pragma once

struct JCItemnoGlow
{
	int ItemIndex;
	int IndexTexture;
};

class JCRemoveGLow
{
public:
	JCRemoveGLow();
	~JCRemoveGLow();
	bool Load(char * Path);
public:
	JCItemnoGlow m_JCRemoveGlow[ MAX_NOGLOW ];
};

extern JCRemoveGLow JCRemoveGlow;