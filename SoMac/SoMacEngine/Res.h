#pragma once
#include "global.h"
class CRes
{
private :
	int		m_iRefCnt;
public:
	void AddRef() { ++m_iRefCnt; }
	void SubRef() { --m_iRefCnt; }
	virtual void UpdateData() {};
public:
	CRes();
	virtual ~CRes();
};

