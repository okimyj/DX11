#pragma once
#include "global.h"
#include "ResPtr.h"
class CRes;
class CMesh;
class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CResPtr<CMesh>>		m_mapMesh;

public:
	void Init();

private:
	int AddMesh(const wstring& _strKey, CMesh* _pMesh);
	CMesh* FindMesh(const wstring& _strKey);

public:
	template <typename T>
	CRes* Load(const wstring& _strKey, const wstring& _strFilePath=L"");	

};

template<typename T>
inline CRes * CResMgr::Load(const wstring & _strKey, const wstring & _strFilePath)
{
	const type_info& info = typeid(T);
	if (&info == &typeid(CMesh))
	{
		// Mesh �� �ڵ�θ� ������ file���� �ҷ��� �� ������ �ٷ� return ����.
		return FindMesh(_strKey);
	}
	return NULL;
}
