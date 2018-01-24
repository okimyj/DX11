#include "Transform.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Device.h"


CTransform::CTransform()
	: m_vPos(Vec3(0.f, 0.f, 1.f))
	, m_vScale(Vec3(100.f, 100.f, 100.f))
	, m_vRot(Vec3(0.f, 0.f, 0.f))
{
}


CTransform::~CTransform()
{
}

int CTransform::Update()
{
	bool bKeyPress = false;
	float fDT = CTimeMgr::GetInst()->DeltaTime();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
		m_vPos.x -= 100.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
		m_vPos.x += 100.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Y, KEY_STATE::HOLD))
	{
		m_vRot.y += XM_2PI * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z, KEY_STATE::HOLD))
	{
		m_vPos.z += 100.f * fDT;
	}
	return 0;
}

int CTransform::LateUpdate()
{
	return 0;
}

int CTransform::FinalUpdate()
{
	XMMATRIX matScale = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z);
	XMMATRIX matTransform = XMMatrixTranslation(m_vPos.x, m_vPos.y, m_vPos.z);
	XMMATRIX matRot = XMMatrixRotationX(m_vRot.x);
	matRot *= XMMatrixRotationY(m_vRot.y);
	matRot *= XMMatrixRotationZ(m_vRot.z);
	m_matWorld = matScale * matRot * matTransform;
	return 0;
}

void CTransform::ApplyData()
{
	g_Transform.matWorld = m_matWorld;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);
	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"Transform");

	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);

	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);			// StartSlot(0) : Register 번호.
}
