#pragma once
#include "Res.h"
class CGameObject;
class CPrefab : public 
	CRes
{
private :
	CGameObject	*			m_pObj;

public:
	CGameObject* Instantiate();
	CGameObject* gameObject() { return m_pObj; }
public:
	CPrefab(CGameObject* _pObj);
	~CPrefab();
};

