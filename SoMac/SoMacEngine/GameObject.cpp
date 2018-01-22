#include "GameObject.h"



void CGameObject::Awake()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		m_arrComp[i]->Awake();
	}
}

void CGameObject::Start()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		m_arrComp[i]->Start();
	}
}

int CGameObject::Update()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		m_arrComp[i]->Update();
	}
	return 0;
}

int CGameObject::LateUpdate()
{
	
	return 0;
}

int CGameObject::FinalUpdate()
{
	return 0;
}

void CGameObject::Render()
{
	for (int i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		m_arrComp[i]->Render();
	}
}

CGameObject::CGameObject()
{
}


CGameObject::~CGameObject()
{
}
