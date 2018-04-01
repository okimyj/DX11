#pragma once
class CPathMgr
{
private:
	static wchar_t m_szResPath[255];
	static wchar_t m_szExternalPath[255];
	static wchar_t m_szExtension[20];
private:
	// static 함수만을 담고 있는 class. 객체화 하지 않는다. 
	CPathMgr();
	~CPathMgr();
	
public:
	static void Init();
public:
	static wchar_t* GetResourcePath() { return m_szResPath; }
	static wchar_t* GetExternalPath() { return m_szExternalPath; }
	static wchar_t* GetExtension(const wchar_t* _pFileName);
};

