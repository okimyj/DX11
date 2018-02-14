#include "Collider.h"
#include "Transform.h"
#include "Device.h"
UINT CCollider::g_iColID = 0;
CCollider::CCollider()
	: m_iColID(g_iColID++)
	, m_pMesh(NULL)
	, m_pMaterial(NULL)
	, m_iCollision(0)
	, m_vObjPos{}
	, m_vOffsetPos{}
	, m_vOffsetScale{}
	, m_matColliderWorld{}
	, m_bApplyScale(false)
{
}


CCollider::~CCollider()
{
}



void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	m_iCollision = 1;
}

void CCollider::OnCollision(CCollider * _pOther)
{
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	m_iCollision = 0;
}

int CCollider::FinalUpdate()
{
	m_vObjPos = Transform()->GetWorldPosition();
	if (m_bApplyScale)
	{
		m_matColliderWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	}
	else
	{
		Vec3 objScale = Transform()->GetWorldScale();
		objScale = m_vOffsetScale / objScale;
		m_matColliderWorld = XMMatrixScaling(objScale.x, objScale.y, objScale.z);
	}
	m_matColliderWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);
	m_matColliderWorld *= Transform()->GetWorldMatrix();
	return RET_SUCCESS;
}

void CCollider::ApplyData()
{
	g_Transform.matWorld = m_matColliderWorld;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);

	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"Transform");
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);
	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
}

