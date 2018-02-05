#pragma once
#include "Script.h"
class CItemScript :
	public CScript
{
public:
	virtual CItemScript* Clone() { return new CItemScript(*this); }
	virtual void Awake();
	virtual void Start();
	virtual int Update();
public:
	CItemScript();
	virtual ~CItemScript();
};

