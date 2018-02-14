#pragma once
#include "Component.h"
class CMeshRenderer;
class CTransform :
	public CComponent
{
private:
	Vec3			m_vPos;
	Vec3			m_vScale;
	Vec3			m_vRot;

	Matrix		m_matWorld;
public :
	// �Ϲ� ���鸸 ������ �⺻ ���� ������ �̿��ص� ��� x. 
	virtual CLONE(CTransform);
	virtual int Update();
	virtual int LateUpdate();
	virtual int FinalUpdate();

private:
	void ApplyData();

public : 
	void SetLocalPosition(Vec3 _vPos) { m_vPos = _vPos; }
	Vec3 GetLocalPosition() { return m_vPos; }
	Vec3 GetWorldPosition();
	void SetLocalScale(Vec3 _vScale) { m_vScale = _vScale; }
	Vec3 GetLocalScale() { return m_vScale; }
	Vec3 GetWorldScale();
	void SetLocalRotation(Vec3 _vRot) { m_vRot = _vRot; }
	Vec3 GetLocalRotation() { return m_vRot; }

	Matrix GetWorldMatrix() { return m_matWorld; }
public:
	CTransform();
	virtual ~CTransform();
	friend class CMeshRenderer;
};

