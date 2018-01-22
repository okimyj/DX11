#include "MeshRender.h"
#include "Shader.h"
#include "Mesh.h"

CMeshRender::CMeshRender()
{
}


CMeshRender::~CMeshRender()
{
}


void CMeshRender::Render()
{
	m_pShader->UpdateData();
	m_pMesh->SetShader(m_pShader);
	m_pMesh->UpdateData();
	m_pMesh->Render();
}