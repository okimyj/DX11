#pragma once
#include "global.h"
class CMaterial;
class CAnimation
{
protected:
	wstring			m_strKey;
	bool				m_bEnable;

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }
	virtual bool Load(const wstring& _strFolderPath) = 0;
	virtual int FinalUpdate() = 0;
	virtual int ApplyData(CMaterial* pMaterial)=0;
	void SetEnable(bool _bEnable) { m_bEnable = _bEnable; }
	bool IsEnable() { return m_bEnable; }
public:
	CAnimation();
	virtual ~CAnimation();
};

