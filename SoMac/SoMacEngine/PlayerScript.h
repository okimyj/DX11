#pragma once
#include "Script.h"

class CBulletScript;
class CTexture;
class CPlayerScript :
	public CScript
{

public :
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

