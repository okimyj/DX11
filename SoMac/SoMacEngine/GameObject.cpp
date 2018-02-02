#include "GameObject.h"
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
	return 0;
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
	return 0;
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
	return 0;
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
}

CComponent* CGameObject::AddComponent(CComponent* _pComp, ID<CScript>)
{
	m_listScript.push_back((CScript*)_pComp);
	_pComp->SetGameObject(this);
	return _pComp;
}