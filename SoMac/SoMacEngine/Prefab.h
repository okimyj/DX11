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

public:
	CPrefab(CGameObject* _pObj);
	~CPrefab();
};

