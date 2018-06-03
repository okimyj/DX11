
#include "Collider.h"
#include "Transform.h"
#include "Device.h"
#include "GameObject.h"
#include "Script.h"
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
	, m_bApplyScale(true)
{
}

CCollider::CCollider(const CCollider & _pOther)
	: m_iColID(g_iColID++)
	, m_pMesh(_pOther.m_pMesh)
	, m_pMaterial(_pOther.m_pMaterial)
	, m_iCollision(_pOther.m_iCollision)
	, m_vObjPos(_pOther.m_vObjPos)
	, m_vOffsetPos(_pOther.m_vOffsetPos)
	, m_vOffsetScale(_pOther.m_vOffsetScale)
	, m_matColliderWorld(_pOther.m_matColliderWorld)
	, m_bApplyScale(_pOther.m_bApplyScale)
{
}


CCollider::~CCollider()
{
}



void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	m_iCollision = 1;
	list<CScript*>& listScript = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollisionEnter(_pOther);
	}
}

void CCollider::OnCollision(CCollider * _pOther)
{
	list<CScript*>& listScript = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollision(_pOther);
	}
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	m_iCollision = 0;
	list<CScript*>& listScript = GameObject()->GetScriptList();
	list<CScript*>::iterator iter = listScript.begin();
	for (; iter != listScript.end(); ++iter)
	{
		(*iter)->OnCollisionExit(_pOther);
	}
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

	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);

	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);			// StartSlot(0) : Register 번호.
}



void CCollider::Save(FILE * _pFile)
{
	WriteResourceKey(m_pMesh.GetTarget(), _pFile);
	WriteResourceKey(m_pMaterial.GetTarget(), _pFile);
	
	WriteVec3(m_vObjPos, _pFile);
	WriteVec3(m_vOffsetPos, _pFile);
	WriteVec3(m_vOffsetScale, _pFile);
	WriteBool(m_bApplyScale, _pFile);
}
void CCollider::Load(FILE * _pFile)
{
	wstring strKey;
	strKey = ReadResourceKey(_pFile);
	if (!strKey.empty())
		m_pMesh = (CMesh*)CResMgr::GetInst()->Load<CMesh>(strKey);
	
	strKey = ReadResourceKey(_pFile);
	if (!strKey.empty())
		m_pMaterial = (CMaterial*)CResMgr::GetInst()->Load<CMaterial>(strKey);

	m_vObjPos = ReadVec3(_pFile);
	m_vOffsetPos = ReadVec3(_pFile);
	m_vOffsetScale = ReadVec3(_pFile);
	m_bApplyScale = ReadBool(_pFile);
}