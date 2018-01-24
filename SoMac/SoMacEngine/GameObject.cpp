#include "GameObject.h"

CGameObject::CGameObject()
	: m_arrComp{}
{
}


CGameObject::~CGameObject()
{
}


void CGameObject::Awake()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Awake();
	}
}

void CGameObject::Start()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Start();
	}
}

int CGameObject::Update()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->Update();
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
	return 0;
}

int CGameObject::FinalUpdate()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrComp[i])
			m_arrComp[i]->FinalUpdate();
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
}

