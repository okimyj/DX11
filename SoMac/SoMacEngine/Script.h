#pragma once
#include "Component.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
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

public:
	CScript();
	virtual ~CScript();
};

