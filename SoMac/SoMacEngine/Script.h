#pragma once
#include "Component.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Collider.h"
#include "Animator.h"
class CScript :
	public CComponent
{
public :
	virtual void Awake() {};
	virtual void Start() {};
	virtual int Update() { return 0; }
protected:
	float DT() { return CTimeMgr::GetInst()->DeltaTime(); }
public :
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

	virtual CScript* Clone() = 0;
	virtual void Save(FILE* _pFile) {}
	virtual void Load(FILE* _pFile) {}
public:
	CScript();
	virtual ~CScript();
};

