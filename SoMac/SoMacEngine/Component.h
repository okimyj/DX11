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
	
	virtual void Awake() { isAwake = true; }
	virtual void Start() {};
	virtual int Update() = 0;
	virtual int LateUpdate() { return 0; }
	virtual int FinalUpdate() { return 0; }
	virtual void Render() {};
	bool enabled = true;
	bool isAwake = false;

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
	virtual void Save(FILE* _pFile) {};
	virtual void Load(FILE* _pFile) {};
	virtual CComponent* Clone() = 0;

public:
	CComponent();
	virtual ~CComponent();
	
	friend class CGameObject;
};

