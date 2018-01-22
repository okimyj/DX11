#pragma once
#include "global.h"
class CPathMgr
{
	// static 함수만을 담고 있는 class. 객체화 하지 않는다. 
private:
	CPathMgr();
	~CPathMgr();

public:
	static void Init();
public:
	static wchar_t m_szResPath[255];
	static wchar_t* GetResourcePath() { return m_szResPath; }
};

