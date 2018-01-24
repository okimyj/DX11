#include "Scene.h"
#include "Layer.h"

CScene::CScene()
{
	// map 에 미리 32개의 layer index를 넣어놓는다. 
	// 우린 이제 32개까지만 layer를 추가 할 수 있음. 
	for (int i = 0; i < 32; ++i)
	{
		m_setLayerIdx.insert(i);
	}
}


CScene::~CScene()
{
}


void CScene::Awake()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Awake();
	}
}

void CScene::Start()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Start();
	}
}

int CScene::Update()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Update();
	}
	return 0;
}

int CScene::LateUpdate()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->LateUpdate();
	}
	return 0;
}

int CScene::FinalUpdate()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->FinalUpdate();
	}
	return 0;
}

void CScene::Render()
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	for (; iter != m_mapLayer.end(); ++iter)
	{
		iter->second.pLayer->Render();
	}
}

int CScene::AddLayer(const wstring & _strLayerName)
{
	CLayer* pLayer = FindLayer(_strLayerName);
	if (NULL != pLayer)
		return RET_FAILED;
	tLayerInfo tInfo = {};
	tInfo.pLayer = new CLayer();
	tInfo.iLayerIdx = GetLayerIndex();
	m_mapLayer.insert(make_pair(_strLayerName, tInfo));
	return 0;
}

CLayer * CScene::FindLayer(const wstring & _strLayerName)
{
	map<wstring, tLayerInfo>::iterator iter = m_mapLayer.begin();
	if (iter == m_mapLayer.end())
		return NULL;
	return iter->second.pLayer;
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

