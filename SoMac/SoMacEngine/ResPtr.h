#pragma once
#include "Mesh.h"
#include "Texture.h"
#include "Prefab.h"
template <typename T>
class CResPtr
{
private:
	T*		m_pTarget;
public:
	operator T* () { return m_pTarget; }
	T* operator -> () { return m_pTarget; }
public:
	void operator = (const CResPtr& _ptr);
	void operator = (T* _pTarget);

public:
	CResPtr();
	CResPtr(const CResPtr& _ptr);
	CResPtr(T* _target);
	~CResPtr();
};

