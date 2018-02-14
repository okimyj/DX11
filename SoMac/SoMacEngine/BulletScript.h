#pragma once
#include "Script.h"

class CBulletScript :
	public CScript
{
private:
	Vec3			m_vDir;			// 단위벡터. 길이 1.
	Vec3			m_vInitPos;
	float			m_fSpeed;



public:
	virtual CLONE(CBulletScript);
	virtual void Awake();
	virtual void Start();
	virtual int Update();


	void SetInitPosition(Vec3 _vPos) { m_vInitPos = _vPos; }
	void SetSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void SetDirection(Vec3 _vDir) { m_vDir = _vDir; }
	void SetGrayScale();
public:
	CBulletScript();
	virtual ~CBulletScript();
};

