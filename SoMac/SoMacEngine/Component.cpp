#include "Component.h"
#include "GameObject.h"

CComponent::CComponent()
{
}


CComponent::~CComponent()
{
}


CGameObject * CComponent::GetParentObject()
{
	return m_pObj->GetParentObject();
}

CTransform * CComponent::Transform()
{
	return m_pObj->GetTransform();
}

CMeshRenderer * CComponent::MeshRender()
{
	return m_pObj->GetMeshRender();
}

CCollider * CComponent::Collider()
{
	return m_pObj->GetCollider();
}
