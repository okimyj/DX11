#include "PathMgr.h"
// static 변수 초기화. 
wchar_t CPathMgr::m_szResPath[255] = {};

CPathMgr::CPathMgr()
{
}


CPathMgr::~CPathMgr()
{
}

void CPathMgr::Init()
{
	// 폴더 경로를 알아 올 때마다 이 과정을 한번씩 더 하는게 불필요 해서이기도 하지만, 
	// window 함수에서 CurrentDirectory를 바꾸는 경우가 있어서 프로그램 시작하자마자 미리 구해놓는다.
	// Resource 폴더 까지의 절대 경로를 구한다. 

	GetCurrentDirectory(255, m_szResPath);

	// 한 단계 상위 경로 구하기. 
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
