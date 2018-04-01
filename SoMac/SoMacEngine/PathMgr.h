#pragma once
class CPathMgr
{
private:
	static wchar_t m_szResPath[255];
	static wchar_t m_szExternalPath[255];
	static wchar_t m_szExtension[20];
private:
	// static �Լ����� ��� �ִ� class. ��üȭ ���� �ʴ´�. 
	CPathMgr();
	~CPathMgr();
	
public:
	static void Init();
public:
	static wchar_t* GetResourcePath() { return m_szResPath; }
	static wchar_t* GetExternalPath() { return m_szExternalPath; }
	static wchar_t* GetExtension(const wchar_t* _pFileName);
};

