#include "PathMgr.h"
#include <string>
#include <Windows.h>
// static ���� �ʱ�ȭ. 
wchar_t CPathMgr::m_szResPath[255] = {};
wchar_t CPathMgr::m_szExternalPath[255] = {};
wchar_t CPathMgr::m_szExtension[20] = {};
CPathMgr::CPathMgr()
{
}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	// ���� ��θ� �˾� �� ������ �� ������ �ѹ��� �� �ϴ°� ���ʿ� �ؼ��̱⵵ ������, 
	// window �Լ����� CurrentDirectory�� �ٲٴ� ��찡 �־ ���α׷� �������ڸ��� �̸� ���س��´�.
	// Resource ���� ������ ���� ��θ� ���Ѵ�. 

	GetCurrentDirectory(255, m_szResPath);

	// �� �ܰ� ���� ��� ���ϱ�. 
	int iLen = wcslen(m_szResPath);
	for (int i = iLen-1; i > 0; --i)
	{
		if (m_szResPath[i] == L'\\')
		{
			wmemset(m_szResPath + i, 0, iLen - i);
			break;
		}
	}
	wcscpy_s(m_szExternalPath, 255, m_szResPath);
	wcscat_s(m_szResPath, 255, L"\\Bin\\Resources\\");
	wcscat_s(m_szExternalPath, 255, L"\\External\\");
}

wchar_t * CPathMgr::GetExtension(const wchar_t * _pFileName)
{
	_wsplitpath_s(_pFileName, NULL, 0, NULL, 0, NULL, 0, m_szExtension, 20);
	return m_szExtension;
}
