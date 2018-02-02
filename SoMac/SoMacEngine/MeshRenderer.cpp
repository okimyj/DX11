#include "MeshRenderer.h"
#include "Device.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

CMeshRenderer::CMeshRenderer()
	: m_pMesh(NULL)
	, m_pMaterial(NULL)
	, m_eRSType(RASTERIZE_TYPE::BACK)
{
}


CMeshRenderer::~CMeshRenderer()
{
}


void CMeshRenderer::Render()
{
	if (NULL == m_pMaterial || NULL == m_pMesh)
		return;
	Transform()->ApplyData();

	m_pMaterial->ApplyData();
	m_pMesh->SetShader(m_pMaterial->GetShader());
	m_pMesh->ApplyData();
	CDevice::GetInst()->SetRasterizer(m_eRSType);
	m_pMesh->Render();
}