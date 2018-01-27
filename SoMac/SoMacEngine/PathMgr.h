#pragma once
#include "global.h"
class CPathMgr
{
	// static �Լ����� ��� �ִ� class. ��üȭ ���� �ʴ´�. 
private:
	CPathMgr();
	~CPathMgr();

public:
	static void Init();
public:
	static wchar_t m_szResPath[255];
	static wchar_t m_szExtension[20];
	static wchar_t* GetResourcePath() { return m_szResPath; }
	static wchar_t* GetExtension(const wchar_t* _pFileName);
};

