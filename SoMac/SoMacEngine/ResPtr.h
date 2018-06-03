#pragma once
class CRes;
template <typename T>
class CResPtr
{
private:
	T*		m_pTarget;
public:
	operator T* () { return m_pTarget; }
	T* operator -> () { return m_pTarget; }
	// 실제 resource pointer 반환.
	CRes* GetTarget() { return (CRes*)m_pTarget; }
public:
	void operator = (const CResPtr& _ptr);
	void operator = (T* _pTarget);

	void Delete();

public:
	CResPtr();
	CResPtr(const CResPtr& _ptr);
	CResPtr(T* _target);
	~CResPtr();
};
