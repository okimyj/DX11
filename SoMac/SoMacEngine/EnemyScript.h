#pragma once
#include "PlayerScript.h"
class CEnemyScript :
	public CPlayerScript
{
private:
	float			m_fAccrueDT;
	int				m_iCurDir;
	float			m_fSpeed;
public:
	virtual CEnemyScript* Clone() { return new CEnemyScript(*this); }
	
	virtual void Awake();
	virtual void Start();
	virtual int Update();

public:
	CEnemyScript();
	virtual ~CEnemyScript();
};

