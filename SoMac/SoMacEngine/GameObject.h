#pragma once
#include "global.h"
#include "Component.h"

template<typename T>
struct ID { typedef T type; };


class CTransform;
class CMeshRenderer;
class CCamera;
class CTextureAnimator;
class CScript;
class CLayer;
class CCollider;
class CAnimator;
class CGameObject
{
public:
	static CGameObject* CreateGameObject(const wstring& _strTag = L"");
	static CGameObject* CreateCamera(const wstring& _strTag = L"");

public:
	CLONE(CGameObject);
private:
	wstring				m_strTag;
	wstring				m_strLayerName;
	CComponent*	m_arrComp[(UINT)COMPONENT_TYPE::END];
	list<CScript*>	m_listScript;

	CGameObject*				m_pParent;
	list<CGameObject*>		m_listChild;
	
	
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
	CComponent* GetComponent(COMPONENT_TYPE _eType) { return m_arrComp[(UINT)_eType]; }
	template<typename T>
	CComponent* AddComponent(CComponent* _pComp) { return AddComponent(_pComp, ID<T>()); }
	
private:
	template<typename T>
	CComponent* AddComponent(CComponent* _pComp, ID<T> _id);
	CComponent* AddComponent(CComponent* _pComp, ID<CScript>);

public:
	CMeshRenderer* GetMeshRender() { return (CMeshRenderer*)m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER]; }
	CTransform* GetTransform() { return (CTransform*)m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM]; }
	CCamera* GetCamera() { return (CCamera*)m_arrComp[(UINT)COMPONENT_TYPE::CAMERA]; }
	CCollider* GetCollider() { return (CCollider*)m_arrComp[(UINT)COMPONENT_TYPE::COLLIDER]; }
	CAnimator* GetAnimator() { return (CAnimator*)m_arrComp[(UINT)COMPONENT_TYPE::ANIMATOR]; }
	const wstring& GetTag() { return m_strTag; }
	void SetTag(const wstring& _strTag) { m_strTag = _strTag; }
	
	
	void SetParent(CGameObject* _pParent, bool _bApplyLayer = true);
	CGameObject* GetParentObject() { return m_pParent; }
	list<CGameObject*>& GetChildList() { return m_listChild; }
	list<CScript*>& GetScriptList() { return m_listScript; }

	bool IsMouseOn(Vec2 _vWorldPos);

	bool HasParent() { return NULL != m_pParent; }
	
private:
	void ClearParent();
	void AddChild(CGameObject* _pChild);
	void RemoveChild(CGameObject* _pChild);
	

private:
	
	void SetLayerName(const wstring& _strName) { m_strLayerName = _strName; }
	const wstring& GetLayerName() { return m_strLayerName; }

public:
	CGameObject();
	CGameObject(const CGameObject& _pOther);
	~CGameObject();

	friend class CLayer;
};

template<typename T>
CComponent* CGameObject::GetComponent()
{
	const type_info& info = typeid(T);
	if (info.hash_code() == typeid(CTransform).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::TRANSFORM];
	}
	else if (info.hash_code() == typeid(CMeshRenderer).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER];
	}
	else if (info.hash_code() == typeid(CCamera).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::CAMERA];
	}
	else if (info.hash_code() == typeid(CCollider).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::COLLIDER];
	}
	else if (info.hash_code() == typeid(CAnimator).hash_code())
	{
		return m_arrComp[(UINT)COMPONENT_TYPE::ANIMATOR];
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
	if (info.hash_code() == typeid(CMeshRenderer).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::MESHRENDER] = _pComp;
	}
	if (info.hash_code() == typeid(CCamera).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::CAMERA] = _pComp;
	}
	if (info.hash_code() == typeid(CCollider).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::COLLIDER] = _pComp;
	}
	if (info.hash_code() == typeid(CAnimator).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::ANIMATOR] = _pComp;
	}
	if (info.hash_code() == typeid(CTextureAnimator).hash_code())
	{
		m_arrComp[(UINT)COMPONENT_TYPE::TEXTURE_ANIMATOR] = _pComp;
	}
	_pComp->SetGameObject(this);
	return _pComp;
}


