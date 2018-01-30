#pragma once
#include "global.h"
#include "Component.h"

template<typename T>
struct ID { typedef T type; };


class CTransform;
class CMeshRender;
class CCamera;
class CTextureAnimator;
class CScript;

class CGameObject
{
public:
	static CGameObject* CreateGameObject(const wstring& _strTag = L"");
	static CGameObject* CreateCamera(const wstring& _strTag = L"");
public:
	CGameObject* Clone() { return new CGameObject(*this); }
private:
	wstring				m_strTag;
	CComponent*	m_arrComp[(UINT)COMPONENT_TYPE::END];
	list<CScript*>	m_listScript;
	
	
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
	CComponent* AddComponent(CComponent* _pComp) { return AddComponent(_pComp, ID<T>()); }
	
private:
	template<typename T>
	CComponent* AddComponent(CComponent* _pComp, ID<T> _id);
	CComponent* AddComponent(CComponent* _pComp, ID<CScript>);
public:
	CMeshRender* GetMeshRender() { return (CMeshRender*)m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CTransform* GetTransform() { return (CTransform*)m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CCamera* GetCamera() { return (CCamera*)m_arrComp[(UINT)COMPONENT_TYPE::CAMERA]; }
	const wstring& GetTag() { return m_strTag; }
	void SetTag(const wstring& _strTag) { m_strTag = _strTag; }

public:
	CGameObject();
	CGameObject(const CGameObject& _pOther);
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
	else if (info.hash_code() == typeid(CMeshRender).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER];
	}
	else if (info.hash_code() == typeid(CCamera).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::CAMERA];
	}
	else if (info.hash_code() == typeid(CTextureAnimator).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::TEXTURE_ANIMATOR];
	}
	else
	{
		list<CScript*>::iterator iter = m_listScript.begin();
		for (; iter != m_listScript.end(); ++iter)
		{
			if (dynamic_cast<T*>(*iter))
			{
				return *iter;
			}
		}
	}
	return NULL;
}

template<typename T>
CComponent* CGameObject::AddComponent(CComponent* _pComp, ID<T>)
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
	if (info.hash_code() == typeid(CTextureAnimator).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::TEXTURE_ANIMATOR] = _pComp;
	}
	_pComp->SetGameObject(this);
	return _pComp;
}


