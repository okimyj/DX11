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
	void SetLocalPosition(Vec3 _vPos) { m_vPos = _vPos; }
	Vec3 GetLocalPosition() { return m_vPos; }
	void SetLocalScale(Vec3 _vScale) { m_vScale = _vScale; }
	Vec3 GetLocalScale() { return m_vScale; }
	void SetLocalRotation(Vec3 _vRot) { m_vRot = _vRot; }
	Vec3 GetLocalRotation() { return m_vRot; }
public:
	CTransform();
	virtual ~CTransform();
	friend class CMeshRender;
};

