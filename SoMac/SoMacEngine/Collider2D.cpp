#include "Collider2D.h"

#include "ResMgr.h"
#include "Material.h"
#include "Mesh.h"
#include "Device.h"
#include "Shader.h"
CCollider2D::CCollider2D()
{
}


CCollider2D::~CCollider2D()
{
}

void CCollider2D::Awake()
{
	m_pMaterial = (CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"ColliderMaterial");
	m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(L"ColliderRectMesh");
}

void CCollider2D::Render()
{
	if (m_pMaterial == NULL || m_pMesh == NULL)
		return;

	// Transform Á¤º¸ update
	ApplyData();

	m_pMaterial->SetParamData(SHADER_PARAM::INT_0, &m_iCollision);
	m_pMaterial->ApplyData();

	m_pMesh->SetShader(m_pMaterial->GetShader());
	m_pMesh->ApplyData();

	CDevice::GetInst()->SetRasterizer(RASTERIZE_TYPE::NONE);

	m_pMesh->Render();
}

