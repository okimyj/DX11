#include "PathMgr.h"
// static ���� �ʱ�ȭ. 
wchar_t CPathMgr::m_szResPath[255] = {};

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
	wcscat_s(m_szResPath, 255, L"\\Bin\\Resources\\");
}
