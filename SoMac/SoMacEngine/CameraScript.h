#pragma once
#include "Script.h"
class CCameraScript :
	public CScript
{
private:
	float		m_fScale;
public:
	virtual int Update();

public:
	virtual CLONE(CCameraScript);
	CCameraScript();
	virtual ~CCameraScript();
};

