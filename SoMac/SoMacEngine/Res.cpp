#include "Res.h"
#include "func.h"


UINT CRes::g_iID = 0;
CRes::CRes()
	: m_iRefCnt(0)
	, m_iResID(g_iID++)
{
}

CRes::CRes(const CRes & _pOther)
	: m_iRefCnt(0)
	, m_iResID(g_iID++)
	, m_strKey(_pOther.m_strKey+L"(Clone)")
	, m_strPath(_pOther.m_strPath)
{
}


CRes::~CRes()
{
}

void CRes::Save(FILE * _pFile)
{
	WriteWString(m_strKey, _pFile);
	WriteWString(m_strPath, _pFile);
}