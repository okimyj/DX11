#include "Layer.h"
#include "GameObject.h"


CLayer::CLayer()
	:m_strLayerName(L"")
	, m_iIdx(-1)
{
}


CLayer::~CLayer()
{
	Safe_Delete_List(m_listObj);
}


void CLayer::Awake()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->Awake();
	}
}

void CLayer::Start()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->Start();
	}
}

int CLayer::Update()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->Update();
	}
	return 0;
}

int CLayer::LateUpdate()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->LateUpdate();
	}
	return 0;
}

int CLayer::FinalUpdate()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->FinalUpdate();
	}
	return 0;
}

void CLayer::Render()
{
	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		(*iter)->Render();
	}
}

void CLayer::AddGameObject(CGameObject * _pObj)
{
	m_listObj.push_back(_pObj);
}

void CLayer::RemoveGameObject(CGameObject * _pObj)
{
	m_listObj.remove(_pObj);
}
