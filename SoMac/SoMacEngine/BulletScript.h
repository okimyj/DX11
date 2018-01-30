#pragma once
#include "Script.h"

class CBulletScript :
	public CScript
{
private:
	Vec3			m_vInitPos;
	float			m_fSpeed;
	

public:
	virtual CBulletScript* Clone() { return new CBulletScript(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
	

	void SetInitPosition(Vec3 _vPos) { m_vInitPos = _vPos;}
public:
	CBulletScript();
	virtual ~CBulletScript();
};

