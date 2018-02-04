#pragma once
#include "Script.h"

class CBulletScript;
class CTexture;
class CPrefab;
class CPlayerPlanet;
class CPlayerScript :
	public CScript
{
private :
	float				m_fSpeed;
	CPrefab*		m_bulletPrefab;
	CPrefab*		m_planetPrefab;
	list<CPlayerPlanet*>		m_listPlanet;
public :
	virtual CPlayerScript* Clone() { return new CPlayerScript(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
private:
	void Shoot();
	CBulletScript* CreateBullet();

	void AddPlanet();
	CPlayerPlanet* CreatePlanet();
	
public:
	CPlayerScript();
	virtual ~CPlayerScript();
	friend class CPlayerPlanet;
};

