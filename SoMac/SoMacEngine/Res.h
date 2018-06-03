#pragma once
#include "global.h"
class CRes
{
private:
	static UINT g_iID;
private:
	int				m_iRefCnt;
	UINT			m_iResID;
	wstring		m_strKey;
	wstring		m_strPath;
	
public:
	void AddRef() { ++m_iRefCnt; }
	void SubRef() { --m_iRefCnt; }
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }
	void SetPath(const wstring& _strPath) { m_strPath = _strPath; }
	const wstring& GetPath() { return m_strPath; }
	UINT GetResID() { return m_iResID; }
	int GetRefCount() { return m_iRefCnt; }
public :
	virtual void Save(FILE* _pFile);
	static CRes* Load(FILE* _pFile) {};
	virtual CRes* Clone(CRes* _pOther) { return new CRes(*this); }
	virtual void ApplyData() {};
public:
	CRes();
	CRes(const CRes& _pOther);
	virtual ~CRes();
};

