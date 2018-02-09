#include "Collider.h"
UINT CCollider::g_iColID = 0;
CCollider::CCollider()
	: m_iColID(g_iColID++)
	, m_eType(COLLIDER_TYPE::NONE)
{
}

CCollider::CCollider(COLLIDER_TYPE _eType)
	: m_iColID(g_iColID++)
	, m_eType(_eType)
{
}


CCollider::~CCollider()
{
}



void CCollider::OnCollisionEnter(CCollider * _pOther)
{
}

void CCollider::OnCollision(CCollider * _pOther)
{
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
}

