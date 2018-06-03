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



void CCamera::UpdateInstancing()
{
}

int CCamera::Update()
{
	return 0;
}

int CCamera::LateUpdate()
{
	// View 변환 행렬 구하기. 
	m_matView = XMMatrixIdentity();			//  XMMatrixIdentity() : 단위행렬.

	// Vec3이 *= 연산을 제공 했다면.. 
	// Matrix도 구조체의 메모리가 선형메모리구조이기 때문에 memcpy로 해주어도 상관없다. 
	Vec3 vPos = Transform()->GetLocalPosition();
	m_matView._41 = -vPos.x; m_matView._42 = -vPos.y; m_matView._43 = -vPos.z;

	if (m_bPerspective)
	{
		m_matProj = XMMatrixPerspectiveFovLH(m_fFOV, (float)WINSIZE_X / (float)WINSIZE_Y
			, m_fNear, m_fFar);
	}
	else
	{
		m_matProj = XMMatrixOrthographicLH(m_fWidth * m_fScale, m_fHeight * m_fScale, m_fNear, m_fFar);
		//m_matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	}
	
	return RET_SUCCESS;
}

void CCamera::ApplyData()
{
	// Projection 변환행렬 구하기
	g_Transform.matProj = XMMatrixTranspose(m_matProj); // MatrixOrthographicLH(WINSIZE_X, WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matView = XMMatrixTranspose(m_matView);
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

void CCamera::Save(FILE * _pFile)
{
	UINT iType = (UINT)COMPONENT_TYPE::CAMERA;
	WriteUINT(iType, _pFile);
	WriteBool(m_bPerspective, _pFile);
	WriteFloat(m_fFOV, _pFile);
	WriteFloat(m_fWidth, _pFile);
	WriteFloat(m_fHeight, _pFile);
	WriteFloat(m_fScale, _pFile);
	WriteFloat(m_fNear, _pFile);
	WriteFloat(m_fFar, _pFile);
	WriteUINT(m_iRenderLayerFlag, _pFile);
}

void CCamera::Load(FILE * _pFile)
{
	m_bPerspective = ReadBool(_pFile);
	m_fFOV = ReadFloat(_pFile);
	m_fWidth = ReadFloat(_pFile);
	m_fHeight = ReadFloat(_pFile);
	m_fScale = ReadFloat(_pFile);
	m_fNear = ReadFloat(_pFile);
	m_fFar = ReadFloat(_pFile);
	m_iRenderLayerFlag = ReadUINT(_pFile);
}