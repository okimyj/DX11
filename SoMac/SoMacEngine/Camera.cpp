#include "Camera.h"
#include "SceneMgr.h"
#include "Scene.h"
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
		//m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	}
	
	return RET_SUCCESS;
}

int CCamera::FinalUpdate()
{
	// Projection ��ȯ��� ���ϱ�
	g_Transform.matProj = m_matProj; // MatrixOrthographicLH(WINSIZE_X, WINSIZE_Y, 1.f, 1000.f);
	//g_Transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matProj = XMMatrixTranspose(g_Transform.matProj);
	return 0;
}


void CCamera::ToggleRenderTargetLayer(const wstring& _strLayerName)
{
	if (IsRenderTargetLayer(_strLayerName))
		RemoveRenderTargetLayer(_strLayerName);
	else
		AddRenderTargetLayer(_strLayerName);
}

void CCamera::AddRenderTargetLayer(const wstring& _strLayerName)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayerName);
	int iIdx = pLayer->GetLayerIndex();
	m_iRenderLayerFlag |= (1 << iIdx);
}

void CCamera::RemoveRenderTargetLayer(const wstring& _strLayerName)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayerName);
	int iIdx = pLayer->GetLayerIndex();
	m_iRenderLayerFlag &= ~(1 << iIdx);
}

bool CCamera::IsRenderTargetLayer(const wstring& _strLayerName)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLayer = pCurScene->FindLayer(_strLayerName);
	int iIdx = pLayer->GetLayerIndex();
	return (m_iRenderLayerFlag & (1 << iIdx));
}

bool CCamera::IsRenderTargetLayer(CLayer * _pLayer)
{
	int iIdx = _pLayer->GetLayerIndex();
	return (m_iRenderLayerFlag & (1 << iIdx));
}

