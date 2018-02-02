#include "ResPtr.h"
#include "Mesh.h"
#include "Texture.h"
#include "Prefab.h"
#include "Material.h"
template class CResPtr<CMesh>;
template class CResPtr<CTexture>;
template class CResPtr<CPrefab>;
template class CResPtr<CMaterial>;

template <typename T>
CResPtr<T>::CResPtr()
	: m_pTarget(NULL)
{
}

template<typename T>
CResPtr<T>::CResPtr(const CResPtr & _ptr)
	:m_pTarget(_ptr.m_pTarget)
{
	if (NULL != m_pTarget)
		m_pTarget->AddRef();
}

template<typename T>
CResPtr<T>::CResPtr(T * _target)
	: m_pTarget(_target)
{
	if(NULL != m_pTarget)
		m_pTarget->AddRef();
}

template <typename T>
CResPtr<T>::~CResPtr()
{
	if (NULL != m_pTarget)
		m_pTarget->SubRef();
}
template <typename T>
void CResPtr<T>::operator = (const CResPtr & _ptr)
{
	if (NULL != m_pTarget)
	{
		m_pTarget->SubRef();
	}
	m_pTarget = _ptr.m_pTarget;
	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
	}
}
template<typename T>
void CResPtr<T>::operator=(T * _pTarget)
{
	if (NULL != m_pTarget)
	{
		m_pTarget->SubRef();
	}
	m_pTarget = _pTarget;
	if (NULL != m_pTarget)
	{
		m_pTarget->AddRef();
	}
}