#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Camera.h"

CScene::CScene()
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
	AddLayer(LAYER_DEFAULT, true);
	AddLayer(LAYER_TRANSPARENT);
	AddLayer(LAYER_CAMERA);
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

CLayer * CScene::FindLayer(const wstring & _strLayerName)
{
	map<wstring, CLayer*>::iterator iter = m_mapLayer.find(_strLayerName);
	if (iter == m_mapLayer.end())
		return NULL;
	return iter->second;
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

