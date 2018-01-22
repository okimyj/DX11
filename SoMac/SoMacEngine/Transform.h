#pragma once
#include "Component.h"
class CTransform :
	public CComponent
{
private:
	Vec3			m_vPos;
	Vec3			m_vScale;
	Vec3			m_vRotation;

	Matrix		m_matWorld;
public :
	
	virtual int Update();
	virtual int RateUpdate();
	virtual int FinalUpdate();
public:
	CTransform();
	virtual ~CTransform();
};

