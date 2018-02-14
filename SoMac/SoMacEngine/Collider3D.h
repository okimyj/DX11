#pragma once
#include "Collider.h"
class CCollider3D :
	public CCollider
{
public:
	virtual bool Is2DCollider() { return false; }
	virtual bool Is3DCollider() { return true; }
public:
	CCollider3D();
	virtual ~CCollider3D();
};

