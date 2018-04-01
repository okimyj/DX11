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
	bool				m_bAlive;
public:
	void SetTestScene(CTestScene* _pScene) { m_pTestScene = _pScene; }
	virtual CLONE(CEnemyScript);
	
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

