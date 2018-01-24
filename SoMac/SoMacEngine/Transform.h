#pragma once
#include "Component.h"
class CMeshRender;
class CTransform :
	public CComponent
{
private:
	Vec3			m_vPos;
	Vec3			m_vScale;
	Vec3			m_vRot;

	Matrix		m_matWorld;
public :
	virtual int Update();
	virtual int LateUpdate();
	virtual int FinalUpdate();

private:
	void ApplyData();

public : 
	Vec3 GetLocalPosition() { return m_vPos; }
	Vec3 GetLocalScale() { return m_vScale; }
	Vec3 GetLocalRotation() { return m_vRot; }
public:
	CTransform();
	virtual ~CTransform();
	friend class CMeshRender;
};

