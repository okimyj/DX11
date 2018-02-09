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
class CScript :
	public CComponent
{
public :
	virtual CScript* Clone() = 0;
	virtual void Awake() {};
	virtual void Start() {};
	virtual int Update() { return 0; }
protected:
	float DT() { return CTimeMgr::GetInst()->DeltaTime(); }
public :
	virtual void OnCollisionEnter(CCollider* _pOther) {};
	virtual void OnCollision(CCollider* _pOther) {};
	virtual void OnCollisionExit(CCollider* _pOther) {};

public:
	CScript();
	virtual ~CScript();
};

