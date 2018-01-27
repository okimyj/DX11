#include "MeshRender.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"

CMeshRender::CMeshRender()
{
}


CMeshRender::~CMeshRender()
{
}


void CMeshRender::Render()
{
	if (NULL == m_pShader || NULL == m_pMesh)
		return;
	Transform()->ApplyData();
	m_pShader->ApplyData();
	if (NULL != m_pTexture)
	{
		m_pTexture->ApplyData();
	}
	m_pMesh->SetShader(m_pShader);
	m_pMesh->ApplyData();
	m_pMesh->Render();
}