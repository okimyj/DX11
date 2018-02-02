#pragma once
#include "global.h"
#include "ResPtr.h"
#include "PathMgr.h"

class CRes;
class CMesh;
class CTexture;
class CPrefab;
class CGameObject;
class CMaterial;
class CResMgr
{
	SINGLE(CResMgr);
private:
	map<wstring, CResPtr<CMesh>>		m_mapMesh;
	map<wstring, CResPtr<CTexture>>		m_mapTexture;
	map<wstring, CResPtr<CPrefab>>		m_mapPrefab;
	map<wstring, CResPtr<CMaterial>>	m_mapMaterial;
public:
	void Init();
private:
	void CreateDefaultMesh();
	void CreateDefaultMaterial();
public :
	int AddPrefab(const wstring& _strKey, CGameObject* _pPrefab);
	int AddMaterial(const wstring& _strKey, CMaterial* _pMaterial);
	
private:
	int AddMesh(const wstring& _strKey, CMesh* _pMesh);
	
	CPrefab* FindPrefab(const wstring& _strKey);
	CMesh* FindMesh(const wstring& _strKey);
	CTexture* FindTexture(const wstring& _strKey);
	CMaterial* FindMaterial(const wstring& _strKey);
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
		return (CRes*)FindMesh(_strKey);
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
	else if (&info == &typeid(CPrefab))
	{
		return (CRes*)FindPrefab(_strKey);
	}
	else if (&info == &typeid(CMaterial))
	{
		return (CRes*)FindMaterial(_strKey);
	}
	return NULL;
}
