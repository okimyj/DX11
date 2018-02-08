#include "Layer.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "Transform.h"

CLayer::CLayer()
	:m_strLayerName(L"")
	, m_bZOrder(false)
	, m_iIdx(-1)
{
}


CLayer::~CLayer()
{
	Safe_Delete_List(m_listObj);
	Safe_Delete_List(m_listParentObj);
}


void CLayer::Awake()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->Awake();
	}
}

void CLayer::Start()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->Start();
	}
}

int CLayer::Update()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->Update();
	}
	return 0;
}

int CLayer::LateUpdate()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->LateUpdate();
	}
	return 0;
}

int CLayer::FinalUpdate()
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		(*iter)->FinalUpdate();
	}
	return 0;
}

void CLayer::Render()
{
	if (m_bZOrder)
	{
		static list<CGameObject*> listSortObj;
		listSortObj = m_listParentObj;
		listSortObj.sort([](CGameObject* _pLeft, CGameObject* _pRight) {return _pLeft->GetTransform()->GetLocalPosition().z > _pRight->GetTransform()->GetLocalPosition().z; });
		list<CGameObject*>::iterator iter = listSortObj.begin();
		for (; iter != listSortObj.end(); ++iter)
		{
			(*iter)->Render();
		}
	}
	else
	{
		list<CGameObject*>::iterator iter = m_listParentObj.begin();
		for (; iter != m_listParentObj.end(); ++iter)
		{
			(*iter)->Render();
		}
	}
}

void CLayer::AddGameObject(CGameObject * _pObj, bool _bApplyChild)
{
	// _pObj�� �ֻ��� �θ���(�θ� ���ٸ�) parentList �� �־��ش�.
	if (!_pObj->HasParent())
	{
		m_listParentObj.push_back(_pObj);
	}
	// layer �� ���� �� object list ���� (�ڽĵ���� ���� �´ٰ� �ϴ� ��� �б� ó��).
	list<CGameObject*> listSource;
	if (_bApplyChild)
	{
		list<CGameObject*> queue;
		queue.push_back(_pObj);
		list<CGameObject*>::iterator iter = queue.begin();
		for (; iter != queue.end();)
		{
			queue.insert(queue.end(), (*iter)->GetChildList().begin(), (*iter)->GetChildList().end());

			if ((*iter)->GetLayerName() != m_strLayerName)
				listSource.push_back(*iter);

			iter = queue.erase(iter);
		}
	}
	else
	{
		if(_pObj->GetLayerName() != m_strLayerName)
			listSource.push_back(_pObj);
	}

	// object ���� �̹� �ٸ� ���̾ ��� �־��ٸ� �ش� ���̾�� ���� ���־���Ѵ�.
	list<CGameObject*>::iterator iter = listSource.begin();
	for (; iter != listSource.end(); ++iter)
	{
		CLayer* pLayer = CSceneMgr::GetInst()->GetCurSceneLayer((*iter)->GetLayerName());
		if (NULL != pLayer)
		{
			pLayer->RemoveGameObject(*iter);
		}
		(*iter)->SetLayerName(m_strLayerName);
	}
	m_listObj.insert(m_listObj.end(), listSource.begin(), listSource.end());
}

void CLayer::RemoveGameObject(CGameObject * _pObj)
{
	// _pObj�� �ֻ��� �θ� ������Ʈ���ٸ� RemoveParentObject ȣ��.
	if (!_pObj->HasParent())
		RemoveParentObject(_pObj);

	list<CGameObject*>::iterator iter = m_listObj.begin();
	for (; iter != m_listObj.end(); ++iter)
	{
		if (*iter == _pObj)
		{
			(*iter)->SetLayerName(L"");
			m_listObj.erase(iter);
			return;
		}
	}
}

void CLayer::RemoveParentObject(CGameObject * _pObj)
{
	list<CGameObject*>::iterator iter = m_listParentObj.begin();
	for (; iter != m_listParentObj.end(); ++iter)
	{
		if (*iter == _pObj)
		{
			m_listParentObj.erase(iter);
			return;
		}
	}
	
}
