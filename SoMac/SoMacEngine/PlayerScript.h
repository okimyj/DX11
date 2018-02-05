#pragma once
#include "Script.h"

class CBulletScript;
class CTexture;
class CPrefab;
class CPlayerPlanet;
class CTestScene;
class CPlayerScript :
	public CScript
{
private :
	float				m_fSpeed;
	CPrefab*		m_bulletPrefab;
	CPrefab*		m_planetPrefab;
	bool				m_bIsLeft;
	list<CPlayerPlanet*>		m_listPlanet;
	CTestScene*					m_pTestScene;
	list<CPlayerPlanet*>		m_listPlanetPool;
public :
	virtual CPlayerScript* Clone() { return new CPlayerScript(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
	
	bool CheckCollide(CGameObject* _pObj);
	void AddPlanet();
	void RemovePlanet();
private:
	void Shoot();
	CBulletScript* CreateBullet();
	CPlayerPlanet* CreatePlanet();
	
public:
	CPlayerScript();
	virtual ~CPlayerScript();
	friend class CPlayerPlanet;
};

