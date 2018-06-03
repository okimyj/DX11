#pragma once
#include "Component.h"
#include "ResPtr.h"

class CMesh;
class CMaterial;
class CCollider :
	public CComponent

{
	static UINT g_iColID;
protected:
	UINT							m_iColID;
	CResPtr<CMesh>		m_pMesh;
	CResPtr<CMaterial>	m_pMaterial;
	int								m_iCollision;			// �浹 ���ο� ���� red, green. // 1:true, 0:false

	Vec3							m_vObjPos;			// �浹ü�� GameObject�� ��ġ. 
	Vec3							m_vOffsetPos;		// GameObject�� ������ ����� ��ġ. 
	Vec3							m_vOffsetScale;		// GameObject�� ������ ����� ũ��.

	Matrix						m_matColliderWorld;			// �浹ü�� World Matrix.

	bool							m_bApplyScale;					// GameObject�� ũ�⿡ ������ ������ �ȹ�����.

public:
	void SetOffsetPos(const Vec3& _vPos) { m_vOffsetPos = _vPos; }
	void SetOffsetScale(const Vec3& _vScale) { m_vOffsetScale = _vScale; }
	const Vec3& GetOffsetPos() { return m_vOffsetPos; }
	const Vec3& GetOffsetScale() { return m_vOffsetScale; }
	Vec3 GetWorldPos() { return m_vObjPos + m_vOffsetPos; }
	const Matrix& GetWorldMatrix() { return m_matColliderWorld; }
	void SetApplyScale(bool _bApplyScale) { m_bApplyScale = _bApplyScale; }
	bool GetApplyScale() { return m_bApplyScale; }
public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
	virtual bool Is2DCollider() = 0;
	virtual bool Is3DCollider() = 0;
	virtual int FinalUpdate();
	void ApplyData();
public:
	UINT GetColID() { return m_iColID; }
	
public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);
	CCollider();
	CCollider(const CCollider& _pOther);
	virtual ~CCollider();
};

