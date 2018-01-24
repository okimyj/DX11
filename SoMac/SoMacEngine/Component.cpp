#include "Component.h"
#include "Transform.h"
#include "GameObject.h"

CComponent::CComponent()
{
}


CComponent::~CComponent()
{
}


CTransform * CComponent::Transform()
{
	return m_pObj->GetTransform();
}

CMeshRender * CComponent::MeshRender()
{
	return m_pObj->GetMeshRender();
}