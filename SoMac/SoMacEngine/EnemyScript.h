#pragma once
#include "PlayerScript.h"
class CBulletScript;
class CPrefab;
class CTestScene;
class CEnemyScript :
	public CPlayerScript
{
private:
	float			m_fAccrueDT;
	int				m_iCurDir;
	float			m_fSpeed;
	CPrefab*		m_bulletPrefab;
	CTestScene*	m_pTestScene;
public:
	void SetTestScene(CTestScene* _pScene) { m_pTestScene = _pScene; }
	virtual CEnemyScript* Clone() { return new CEnemyScript(*this); }
	
	virtual void Awake();
	virtual void Start();
	virtual int Update();
private:
	void Die();
	void Shoot();
	CBulletScript* CreateBullet();
public:
	CEnemyScript();
	CEnemyScript(const CEnemyScript& _pOther);
	virtual ~CEnemyScript();
};

