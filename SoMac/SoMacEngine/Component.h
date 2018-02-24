#pragma once
#include "global.h"
class CGameObject;
class CTransform;
class CMeshRenderer;
class CCollider;
class CAnimator;
class CCamera;
class CComponent
{
private:
	CGameObject*	m_pObj;
	
public:
	virtual CComponent* Clone() = 0;
	virtual void Awake() {};
	virtual void Start() {};
	virtual int Update() = 0;
	virtual int LateUpdate() { return 0; }
	virtual int FinalUpdate() { return 0; }
	virtual void Render() {};
private:
	void SetGameObject(CGameObject* _pObj) { m_pObj = _pObj; }

protected:
	CGameObject* GameObject() { return m_pObj; }
	CGameObject* ParentObject();
	CTransform* Transform();
	CMeshRenderer* MeshRenderer();
	CAnimator* Animator();
	CCollider* Collider();
	CCamera* Camera();

public:
	CComponent();
	virtual ~CComponent();
	
	friend class CGameObject;
};

