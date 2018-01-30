#pragma once
#include "Script.h"

class CBulletScript;
class CTexture;
class CPrefab;
class CPlayerScript :
	public CScript
{
private :
	CPrefab*		m_bulletPrefab;
public :
	virtual CPlayerScript* Clone() { return new CPlayerScript(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
private:
	void Shoot();
	CBulletScript* CreateBullet();
public:
	CPlayerScript();
	virtual ~CPlayerScript();
};

