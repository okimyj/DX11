#pragma once
#include "global.h"
#include "ResPtr.h"
#include "PathMgr.h"
class CRes;
class CMesh;
class CTexture;
class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CResPtr<CMesh>>		m_mapMesh;
	map<wstring, CResPtr<CTexture>>		m_mapTexture;

public:
	void Init();

private:
	int AddMesh(const wstring& _strKey, CMesh* _pMesh);
	CMesh* FindMesh(const wstring& _strKey);
	CTexture* FindTexture(const wstring& _strKey);
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
		// Mesh 는 코드로만 만들지 file에서 불러올 일 없으니 바로 return 하자.
		return FindMesh(_strKey);
	}
	else if (&info == &typeid(CTexture))
	{
		CTexture* pTexture = FindTexture(_strKey);
		if (NULL != pTexture)
			return pTexture;
		wstring strFullPath = CPathMgr::GetResourcePath();
		strFullPath += _strFilePath;
		pTexture = CTexture::Create(strFullPath);
		if (NULL == pTexture)
			return NULL;
		pTexture->SetKey(_strKey);
		pTexture->SetPath(_strFilePath);
		m_mapTexture.insert(make_pair(_strKey, pTexture));
		return pTexture;
	}
	return NULL;
}
