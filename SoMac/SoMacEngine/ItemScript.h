#pragma once
#include "Script.h"
class CItemScript :
	public CScript
{
public:
	virtual CLONE(CItemScript);
	virtual void Awake();
	virtual void Start();
	virtual int Update();
public:
	CItemScript();
	virtual ~CItemScript();
};

