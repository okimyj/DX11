#include "MeshRenderer.h"
#include "Device.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
CMeshRenderer::CMeshRenderer()
	: m_pMesh(NULL)
	, m_pMaterial(NULL)
	, m_pCloneMaterial(NULL)
	, m_eRSType(RASTERIZE_TYPE::BACK)
{
}

CMeshRenderer::CMeshRenderer(const CMeshRenderer & _pOther)
	: m_pMesh(_pOther.m_pMesh)
	, m_pSharedMaterial(_pOther.m_pSharedMaterial)
	, m_pMaterial(_pOther.m_pSharedMaterial)
	, m_pCloneMaterial(NULL)
	, m_eRSType(_pOther.m_eRSType)
{
	
}


CMeshRenderer::~CMeshRenderer()
{
	
}

void CMeshRenderer::SetMaterial(CMaterial * _pMaterial)
{
	// 원본 material 이랑 다른 material 인 경우. 복사된 material 이 있는 경우 NULL.
	if (m_pSharedMaterial != _pMaterial)
	{
		// 어차피 ResMgr 에서 Clone 리소스 들도 관리하고 있으니 여기서 Delete 는 해주지 않는다.
		m_pCloneMaterial = NULL;
	}
	m_pSharedMaterial = _pMaterial; 
	m_pMaterial = _pMaterial;
}

CMaterial * CMeshRenderer::GetMaterial()
{
	if (NULL == m_pSharedMaterial)
		return NULL;

	if (NULL == m_pCloneMaterial)
	{
		m_pCloneMaterial = m_pSharedMaterial->Clone();
		CResMgr::GetInst()->AddCloneResource(m_pCloneMaterial);
		
	}
	m_pMaterial = m_pCloneMaterial;
	
	return m_pCloneMaterial;
}

CMaterial * CMeshRenderer::GetSharedMaterial()
{
	return m_pSharedMaterial;
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

	if (Animator())
	{
		Animator()->ApplyData();
	}
	else
	{
		CAnimator::Disable();
	}

	m_pMesh->Render();

//	if (g_bShowCollider && NULL != Collider())
	if (NULL != Collider())
		Collider()->Render();

}