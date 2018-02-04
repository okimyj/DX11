#include "Res.h"



CRes::CRes()
	: m_iRefCnt(0)
{
}

CRes::CRes(const CRes & _pOther)
	: m_iRefCnt(0)
	, m_strKey(_pOther.m_strKey+L"(Clone)")
	, m_strPath(_pOther.m_strPath)
{
}


CRes::~CRes()
{
}
