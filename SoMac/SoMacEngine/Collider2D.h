#pragma once
#include "Collider.h"
class CCollider2D :
	public CCollider
{
public:
	
	virtual void Awake();
	virtual int Update() { return 0; }
	virtual void Render();
	
public:
	virtual bool Is2DCollider() { return true; }
	virtual bool Is3DCollider() { return false; }
	
public:
	virtual CLONE(CCollider2D);
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);

	CCollider2D();
	virtual ~CCollider2D();
};

