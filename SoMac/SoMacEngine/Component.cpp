#include "Component.h"
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

CMeshRenderer * CComponent::MeshRender()
{
	return m_pObj->GetMeshRender();
}