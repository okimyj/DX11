#include "MeshRenderer.h"
#include "Device.h"
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"
#include "ResMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Camera.h"
CMeshRenderer::CMeshRenderer()
	: m_pMesh(NULL)
	, m_pMtrl(NULL)
	, m_eRSType(RASTERIZE_TYPE::BACK)
{
}

CMeshRenderer::CMeshRenderer(const CMeshRenderer & _pOther)
	: m_pMesh(_pOther.m_pMesh)
	, m_pMtrl(_pOther.m_pMtrl)
	, m_eRSType(_pOther.m_eRSType)
{
	
}


CMeshRenderer::~CMeshRenderer()
{
	
}


CMaterial * CMeshRenderer::GetMaterial()
{
	if (NULL == m_pMtrl)
		return NULL;

	m_pMtrl = m_pMtrl->Clone();

	CResMgr::GetInst()->AddCloneResource(m_pMtrl);

	return m_pMtrl;
}



void CMeshRenderer::Render()
{
	if (NULL == m_pMtrl || NULL == m_pMesh)
		return;
	Transform()->ApplyData();

	m_pMtrl->ApplyData();
	m_pMesh->SetShader(m_pMtrl->GetShader());
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

ULONG64 CMeshRenderer::GetInstID()
{
	if (m_pMesh == NULL || m_pMtrl == NULL)
		return 0;

	uInstID id;
	id.iMesh = m_pMesh->GetResID();
	id.iMtrl = m_pMtrl->GetResID();

	return id.llID;
}
void CMeshRenderer::Save(FILE * _pFile)
{
	/*
	CResPtr<CMesh>		m_pMesh;
	CMaterial*					m_pSharedMaterial;
	CMaterial*					m_pMaterial;
	CMaterial*					m_pCloneMaterial;
	RASTERIZE_TYPE		m_eRSType;
	*/
	UINT iType = (UINT)COMPONENT_TYPE::MESHRENDERER;
	WriteUINT(iType, _pFile);
	// Mesh 정보
	// Mesh Key, Mesh 상대 경로 저장.
	WriteResourceKey(m_pMesh.GetTarget(), _pFile);
	// Material 정보 저장 
	WriteResourceKey(m_pMtrl.GetTarget(), _pFile);
	// RS Type 저장
	WriteUINT((UINT)m_eRSType, _pFile);
	
}

void CMeshRenderer::Load(FILE * _pFile)
{
	wstring strKey;
	// Mesh 정보.
	strKey = ReadResourceKey(_pFile);
	m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(strKey);
	// Material 정보.
	strKey = ReadResourceKey(_pFile);
	m_pMtrl = (CMaterial*)CResMgr::GetInst()->Load<CMaterial>(strKey);
	// RS Type
	m_eRSType = (RASTERIZE_TYPE)ReadUINT(_pFile);

}