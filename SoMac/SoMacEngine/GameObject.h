#pragma once
#include "global.h"
#include "Component.h"
class CTransform;
class CMeshRender;
class CCamera;
class CGameObject
{
public:
	static CGameObject* CreateGameObject(const wstring& _strTag = L"");
	static CGameObject* CreateCamera(const wstring& _strTag = L"");
	
private:
	CComponent*	m_arrComp[(UINT)COMPONENT_TYPE::END];
	wstring				m_strTag;

public:
	void Awake();
	void Start();

	int Update();
	int LateUpdate();

	int FinalUpdate();			// world행렬을 최종적으로 계산해 놓기 위한 단계임.
	void Render();
	
public :
	template<typename T>
	CComponent* GetComponent();
	template<typename T>
	CComponent* AddComponent(CComponent* _pCom=NULL);

public:
	CMeshRender* GetMeshRender() { return (CMeshRender*)m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CTransform* GetTransform() { return (CTransform*)m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CCamera* GetCamera() { return (CCamera*)m_arrComp[(UINT)COMPONENT_TYPE::CAMERA]; }
	const wstring& GetTag() { return m_strTag; }
	void SetTag(const wstring& _strTag) { m_strTag = _strTag; }

public:
	CGameObject();
	~CGameObject();
};

template<typename T>
CComponent* CGameObject::GetComponent()
{
	const type_info& info = typeid(T);
	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM];
	}
	if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER];
	}
	return NULL;
}
template<typename T>
CComponent* CGameObject::AddComponent(CComponent* _pComp)
{
	const type_info& info = typeid(T);
	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM] = _pComp;
	}
	if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER] = _pComp;
	}
	if (info.hash_code() == typeid(CCamera).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::CAMERA] = _pComp;
	}
	_pComp->SetGameObject(this);
	return _pComp;
}

