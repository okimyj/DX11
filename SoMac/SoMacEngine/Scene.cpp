#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Camera.h"

CScene::CScene()
	:m_pMainCamera(NULL)
{
	// map 에 미리 32개의 layer index를 넣어놓는다. 
	// 우린 이제 32개까지만 layer를 추가 할 수 있음. 
	for (int i = 0; i < 32; ++i)
	{
		m_setLayerIdx.insert(i);
	}
	// vector resize와 reserve의 차이. 
	// reserve : 메모리 공간을 예약하는 개념. // 기본값 x 아직 데이터가 들어간 상태가 아님.
	// resize : 해당 크기 만큼 메모리 할당. // 기본값 NULL(0)으로 초기화.
	// vector는 push_back 할 때 마다 공간이 부족하면 재할당(메모리 할당, 복사, 삭제)이 일어나기 때문에 
	// 지금 같이 최대 개수가 정해져 있는 경우 resize를 이용해서 미리 할당 해놓는게 낫다. 
	m_vecLayer.resize(MAX_LAYER);

	// 전체 씬 공통 Layer 생성.
	/*
	AddLayer(LAYER_DEFAULT, true);
	AddLayer(LAYER_TRANSPARENT);
	AddLayer(LAYER_CAMERA);
	*/
}


CScene::~CScene()
{
	// map, vector 두개가 서로 같은 주소를 참조 하고 있으니 vector 만 Safe_Delete.  map은 혹시모르니 clear 해주자.
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
	// Camera Layer 를 얻어옴.
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

	// map 에 추가해주고, 배열에도 해당 인덱스에 넣어준다.
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
	// 만약 정해진 layer 개수를 다 사용 했으면 assert. 
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

