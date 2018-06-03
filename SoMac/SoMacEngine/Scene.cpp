#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

CScene::CScene()
	:m_pMainCamera(NULL)
{
	// map �� �̸� 32���� layer index�� �־���´�. 
	// �츰 ���� 32�������� layer�� �߰� �� �� ����. 
	for (int i = 0; i < 32; ++i)
	{
		m_setLayerIdx.insert(i);
	}
	// vector resize�� reserve�� ����. 
	// reserve : �޸� ������ �����ϴ� ����. // �⺻�� x ���� �����Ͱ� �� ���°� �ƴ�.
	// resize : �ش� ũ�� ��ŭ �޸� �Ҵ�. // �⺻�� NULL(0)���� �ʱ�ȭ.
	// vector�� push_back �� �� ���� ������ �����ϸ� ���Ҵ�(�޸� �Ҵ�, ����, ����)�� �Ͼ�� ������ 
	// ���� ���� �ִ� ������ ������ �ִ� ��� resize�� �̿��ؼ� �̸� �Ҵ� �س��°� ����. 
	m_vecLayer.resize(MAX_LAYER);

	// ��ü �� ���� Layer ����.
	/*
	AddLayer(LAYER_DEFAULT, true);
	AddLayer(LAYER_TRANSPARENT);
	AddLayer(LAYER_CAMERA);
	*/
}


CScene::~CScene()
{
	// map, vector �ΰ��� ���� ���� �ּҸ� ���� �ϰ� ������ vector �� Safe_Delete.  map�� Ȥ�ø𸣴� clear ������.
	Safe_Delete_Vector(m_vecLayer);
}


void CScene::Awake()
{
	
	


	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->Awake();
		}
	}
}

void CScene::Start()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->Start();
		}
	}
}

int CScene::Update()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->Update();
		}
	}
	return RET_SUCCESS;
}

int CScene::LateUpdate()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->LateUpdate();
		}
	}
	return RET_SUCCESS;
}

int CScene::FinalUpdate()
{
	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->FinalUpdate();
		}
	}
	return RET_SUCCESS;
}

void CScene::Render()
{
	// Camera Layer �� ����.
	CLayer* pCamLayer = FindLayer(LAYER_CAMERA);
	list<CGameObject*>& listObj = pCamLayer->GetObjList();
	list<CGameObject*>::iterator iter = listObj.begin();
	for (; iter != listObj.end(); ++iter)
	{
		CCamera* pCamComp = (*iter)->GetCamera();
		if (NULL == pCamComp)
			continue;
		pCamComp->ApplyData();
		for (int i = 0; i < MAX_LAYER; ++i)
		{
			if (NULL != m_vecLayer[i] && pCamComp->IsRenderTargetLayer(m_vecLayer[i]))
			{
				m_vecLayer[i]->Render();
			}
		}
	}

	for (int i = 0; i < MAX_LAYER; ++i)
	{
		if (NULL != m_vecLayer[i])
		{
			m_vecLayer[i]->Render();
		}
	}
}

int CScene::AddLayer(const wstring & _strLayerName, bool _bZOrder)
{
	CLayer* pLayer = FindLayer(_strLayerName);
	if (NULL != pLayer)
		return RET_FAILED;
	
	pLayer = new CLayer();
	UINT iLayerIdx = GetLayerIndex();
	pLayer->SetLayerIndex(iLayerIdx);
	pLayer->SetLayerName(_strLayerName);
	pLayer->SetZOrder(_bZOrder);

	// map �� �߰����ְ�, �迭���� �ش� �ε����� �־��ش�.
	m_mapLayer.insert(make_pair(_strLayerName, pLayer));
	m_vecLayer[iLayerIdx] = pLayer;
	return RET_SUCCESS;
}
int CScene::AddLayer(CLayer* _pLayer)
{
	if (FindLayer(_pLayer->GetLayerName()))
		assert(NULL);
	UINT iLayerIndex = GetLayerIndex();

	if (NULL != m_vecLayer[iLayerIndex])
		assert(NULL);
	set<UINT>::iterator iter = m_setLayerIdx.find(iLayerIndex);
	if (m_setLayerIdx.end() != iter)
		m_setLayerIdx.erase(iter);
	m_mapLayer.insert(make_pair(_pLayer->GetLayerName(), _pLayer));
	m_vecLayer[iLayerIndex] = _pLayer;
	return RET_SUCCESS;
}
CLayer * CScene::FindLayer(const wstring & _strLayerName)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter == m_mapLayer.end())
		return NULL;
	return iter->second;
}


void CScene::GetAllParentObjects(list<CGameObject*>& _listOut)
{
	for (UINT i = 0; i < m_vecLayer.size(); ++i)
	{
		if (NULL == m_vecLayer[i])
			continue;
		list<CGameObject*> list = m_vecLayer[i]->GetParentObjList();
		_listOut.insert(_listOut.end(), list.begin(), list.end());
	}
}

UINT CScene::GetLayerIndex()
{
	// ���� ������ layer ������ �� ��� ������ assert. 
	if (m_setLayerIdx.empty())
		assert(NULL);
	UINT iIndex = *(m_setLayerIdx.begin());
	m_setLayerIdx.erase(m_setLayerIdx.begin());
	return iIndex;
}


CGameObject * CScene::FindObject(Vec2 _vWindowPos, Vec2 _vResolution, UINT _iMask)
{
	Vec2 vWorldPos = ScreenToWorldPosition(_vWindowPos, _vResolution);
	for (UINT i = 0; i < m_vecLayer.size(); ++i)
	{
		if (NULL == m_vecLayer[i])
			continue;

		int iIdx = m_vecLayer[i]->GetLayerIndex();
		if (_iMask==0 || _iMask & (1 << iIdx))
		{
			CGameObject* pTarget = m_vecLayer[i]->FindObject(vWorldPos);
			if (NULL != pTarget)
				return pTarget;
		}
	}
	return NULL;
}

Vec2 CScene::ScreenToWorldPosition(Vec2 _vWindowPos, Vec2 _vResolution)
{
	Vec2 vRatio;
	vRatio.x = WINSIZE_X / _vResolution.x;
	vRatio.y = WINSIZE_Y / _vResolution.y;

	Vec2 vWindowPos = Vec2(_vWindowPos.x * vRatio.x, _vWindowPos.y * vRatio.y);
	Vec2 vWorldPos;
	vWorldPos.x = vWindowPos.x - (WINSIZE_X / 2.f);
	vWorldPos.y = (WINSIZE_Y / 2.f) - vWindowPos.y;
	CGameObject* pMainCamera = GetMainCamera();
	float fScale = pMainCamera->GetCamera()->GetScale();
	Vec3 vCamWorldPos = pMainCamera->GetTransform()->GetWorldPosition();
	
	vWorldPos = Vec2(vWorldPos.x * fScale + vCamWorldPos.x
			, vWorldPos.y * fScale + vCamWorldPos.y);

	return vWorldPos;
}

CGameObject * CScene::GetMainCamera()
{
	if (NULL == m_pMainCamera)
	{
		CLayer* pCamLayer = FindLayer(LAYER_CAMERA);
		m_pMainCamera = pCamLayer->FindObjectByTag(TAG_MAIN_CAMERA);
	}
	return m_pMainCamera;
}

