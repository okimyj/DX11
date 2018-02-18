#include "Component.h"
#include "GameObject.h"

CComponent::CComponent()
{
}


CComponent::~CComponent()
{
}


CGameObject * CComponent::ParentObject()
{
	return m_pObj->GetParentObject();
}

CTransform * CComponent::Transform()
{
	return m_pObj->GetTransform();
}

CMeshRenderer * CComponent::MeshRenderer()
{
	return m_pObj->GetMeshRender();
}

CAnimator * CComponent::Animator()
{
	return m_pObj->GetAnimator();
}

CCollider * CComponent::Collider()
{
	return m_pObj->GetCollider();
}
