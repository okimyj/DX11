#pragma once
#include "global.h"
class CGameObject;
class CComponent
{
private:
	CGameObject*	m_pObj;
public:
	virtual void Awake() {};
	virtual void Start() {};
	virtual int Update() = 0;
	virtual void Render() {};

private:
	void SetGameObject(CGameObject* _pObj) { m_pObj = _pObj; }
	CGameObject* GetGameObject() { return m_pObj; }

public:
	CComponent();
	virtual ~CComponent();
	
	friend class CGameObject;
};

