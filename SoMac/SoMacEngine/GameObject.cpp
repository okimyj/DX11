#include "GameObject.h"
#include "SceneMgr.h"
#include "Layer.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Script.h"

CGameObject::CGameObject()
	: m_arrComp{}
{
}

CGameObject::CGameObject(const CGameObject & _pOther)
	: m_strTag(_pOther.m_strTag)
	, m_arrComp{}
	, m_listScript{}
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != _pOther.m_arrComp[i])
		{
			m_arrComp[i] = _pOther.m_arrComp[i]->Clone();
			m_arrComp[i]->SetGameObject(this);
		}
	}
	list<CScript*>::const_iterator iter = _pOther.m_listScript.begin();
	for (; iter != _pOther.m_listScript.end(); ++iter)
	{
		CScript* pScript = (*iter)->Clone();
		pScript->SetGameObject(this);
		m_listScript.push_back(pScript);
	}
}


CGameObject::~CGameObject()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrComp[i]);
	}
	Safe_Delete_List(m_listScript);

}

CGameObject * CGameObject::CreateGameObject(const wstring& _strTag)
{
	CGameObject* pObj = new CGameObject();
	pObj->AddComponent<CTransform>(new CTransform);
	pObj->AddComponent<CMeshRenderer>(new CMeshRenderer);
	pObj->SetTag(_strTag);
	return pObj;
}

CGameObject * CGameObject::CreateCamera(const wstring& _strTag)
{
	CGameObject* pObj = CGameObject::CreateGameObject(_strTag);
	pObj->AddComponent<CCamera>(new CCamera);
	return pObj;
}



void CGameObject::Awake()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Awake();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->Awake();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->Awake();
	}
}

void CGameObject::Start()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Start();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->Start();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->Start();
	}
}

int CGameObject::Update()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Update();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->Update();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->Update();
	}
	return RET_SUCCESS;
}

int CGameObject::LateUpdate()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->LateUpdate();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->LateUpdate();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->LateUpdate();
	}
	return RET_SUCCESS;
}

int CGameObject::FinalUpdate()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->FinalUpdate();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->FinalUpdate();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->FinalUpdate();
	}
	return RET_SUCCESS;
}

void CGameObject::Render()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Render();
	}
	list<CScript*>::iterator iter = m_listScript.begin();
	for (; iter != m_listScript.end(); ++iter)
	{
		(*iter)->Render();
	}
	list<CGameObject*>::iterator iterChild = m_listChild.begin();
	for (; iterChild != m_listChild.end(); ++iterChild)
	{
		(*iterChild)->Render();
	}
}

CComponent* CGameObject::AddComponent(CComponent* _pComp, ID<CScript>)
{
	m_listScript.push_back((CScript*)_pComp);
	_pComp->SetGameObject(this);
	return _pComp;
}

void CGameObject::SetParent(CGameObject * _pParent, bool _bApplyLayer)
{
	// 이미 부모 오브젝트가 있었고, set 하려는 부모가 현재 부모와 다른 오브젝트인 경우 clear.
	// Layer 관련 된 것은 어차피 부모오브젝트 기반으로 호출 되기 때문에 빼주지 않아도 된다. 내 layer는 내 layer 일 뿐임.
	if(HasParent() && m_pParent != _pParent)
		ClearParent();

	m_pParent = _pParent;

	if (NULL != m_pParent)
	{
		m_pParent->AddChild(this);
		if (_bApplyLayer)
			CSceneMgr::GetInst()->GetCurSceneLayer(m_pParent->GetLayerName())->AddGameObject(this);
	}
	
}

void CGameObject::ClearParent()
{
	m_pParent->RemoveChild(this);
	m_pParent = NULL;
}


void CGameObject::AddChild(CGameObject * _pChild)
{
	// 혹시 이미 들어있을 수 있으니 한번 지우고 다시 넣어준다.
	RemoveChild(_pChild);
	m_listChild.push_back(_pChild);
}

void CGameObject::RemoveChild(CGameObject * _pChild)
{
	list<CGameObject*>::iterator iter = m_listChild.begin();
	for (; iter != m_listChild.end(); ++iter)
	{
		if (*iter == _pChild)
		{
			m_listChild.erase(iter);
			break;
		}
	}
	
}
