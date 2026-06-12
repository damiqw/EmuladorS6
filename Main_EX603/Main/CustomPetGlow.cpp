#include "stdafx.h"
#include "CustomPetGlow.h"

cRenderMesh cRender;

cRenderMesh::cRenderMesh()
{
	this->m_RenderMeshPet.clear();
}
cRenderMesh::~cRenderMesh()
{
}

void cRenderMesh::Load(RENDER_MESH * info)
{
	for( int n = 0; n < MAX_PET_GLOW; n++)
	{
		if(info[n].Index < 0 || info[n].Index >= MAX_PET_GLOW)
		{
			return;
		}
		this->m_RenderMeshPet.push_back(info[n]);
	}
}