#include "Camera.h"
#include "Transform.h"
#include "Layer.h"

CCamera::CCamera()
	: m_bPerspective(false)
	, m_fFOV(XM_PI / 4.f)
	, m_fWidth(WINSIZE_X)
	, m_fHeight(WINSIZE_Y)
	, m_fScale(1.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)
	, m_iRenderLayerFlag(0)
{
}


CCamera::~CCamera()
{
}


int CCamera::Update()
{
	return 0;
}

int CCamera::LateUpdate()
{
	// View ��ȯ ��� ���ϱ�. 
	m_matView = XMMatrixIdentity();			//  XMMatrixIdentity() : �������.

	// Vec3�� *= ������ ���� �ߴٸ�.. 
	// Matrix�� ����ü�� �޸𸮰� �����޸𸮱����̱� ������ memcpy�� ���־ �������. 
	Vec3 vPos = Transform()->GetLocalPosition();
	m_matView._41 = -vPos.x;
	m_matView._42 = -vPos.y;
	m_matView._43 = -vPos.z;

	if (m_bPerspective)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, (float)WINSIZE_X / (float)WINSIZE_Y
			, m_fNear, m_fFar);
	}
	else
	{
		m_matProj = XMMatrixOrthographicLH(m_fWidth, m_fHeight, m_fNear, m_fFar);
	}
	
	return RET_SUCCESS;
}

int CCamera::FinalUpdate()
{
	return 0;
}


void CCamera::ToggleRenderTargetLayer(CLayer * _pLayer)
{
	if (IsRenderTargetLayer(_pLayer))
		RemoveRenderTargetLayer(_pLayer);
	else
		AddRenderTargetLayer(_pLayer);
}

void CCamera::AddRenderTargetLayer(CLayer * _pLayer)
{
	int iIdx = _pLayer->GetLayerIndex();
	m_iRenderLayerFlag |= (1 << iIdx);
}

void CCamera::RemoveRenderTargetLayer(CLayer * _pLayer)
{
	int iIdx = _pLayer->GetLayerIndex();
	m_iRenderLayerFlag &= ~(1 << iIdx);
}

bool CCamera::IsRenderTargetLayer(CLayer * _pLayer)
{
	int iIdx = _pLayer->GetLayerIndex();
	return (m_iRenderLayerFlag & (1 << iIdx));
}

