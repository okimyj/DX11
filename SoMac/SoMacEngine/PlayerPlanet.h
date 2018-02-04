#pragma once
#include "Script.h"
class CPlayerScript;
class CPlayerPlanet : 
	public CScript
{
private:
	float						m_fSpeed;
	float						m_fAngle;
	CPlayerScript*		m_pOwner;

public:
	void SetOwner(CPlayerScript* _pOwner) { m_pOwner = _pOwner; }
	virtual CPlayerPlanet* Clone() { return new CPlayerPlanet(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
public:
	CPlayerPlanet();
	~CPlayerPlanet();
};

