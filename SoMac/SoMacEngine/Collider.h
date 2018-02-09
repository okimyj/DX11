#pragma once
#include "Component.h"
enum class COLLIDER_TYPE
{
	COL_2D,
	COL_3D,
	NONE,
};
class CCollider :
	public CComponent

{
	static UINT g_iColID;
private:
	UINT						m_iColID;
	COLLIDER_TYPE		m_eType;
public:
	virtual void OnCollisionEnter(CCollider* _pOther);
	virtual void OnCollision(CCollider* _pOther);
	virtual void OnCollisionExit(CCollider* _pOther);
public:
	UINT GetColID() { return m_iColID; }
	COLLIDER_TYPE GetColliderType() { return m_eType; }
public:
	CCollider();
	CCollider(COLLIDER_TYPE _eType);
	virtual ~CCollider();
};

