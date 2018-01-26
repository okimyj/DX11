#pragma once
#include "Script.h"
class CPlayerScript :
	public CScript
{
public :
	virtual void Awake();
	virtual void Start();
	virtual int Update();
	
public:
	CPlayerScript();
	virtual ~CPlayerScript();
};

