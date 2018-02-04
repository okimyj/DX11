#pragma once
#include "global.h"
class CRes
{
private:
	int				m_iRefCnt;
	wstring		m_strKey;
	wstring		m_strPath;
public:
	void AddRef() { ++m_iRefCnt; }
	void SubRef() { --m_iRefCnt; }
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }
	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }
	const wstring& GetPath() { return m_strPath; }
public :
	virtual CRes* Clone(CRes* _pOther) { return new CRes(*this); }
	virtual void ApplyData() {};
public:
	CRes();
	CRes(const CRes& _pOther);
	virtual ~CRes();
};

