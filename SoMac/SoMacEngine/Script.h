#pragma once
#include "Component.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

#include "Transform.h"
#include "MeshRender.h"
#include "Camera.h"
class CScript :
	public CComponent
{
public :
	
protected:
	float DT() { return CTimeMgr::GetInst()->DeltaTime(); }

public:
	CScript();
	virtual ~CScript();
};

