#pragma once
#include "global.h"
#include "ResPtr.h"
#include "PathMgr.h"
#include "Texture.h"

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
	vector<CResPtr<CRes>>					m_vecCloneRes;
public:
	void Init();
private:
	void CreateDefaultMesh();
	void CreateDefaultMaterial();
public :
	int AddPrefab(const wstring& _strKey, CGameObject* _pPrefab);
	int AddMaterial(const wstring& _strKey, CMaterial* _pMaterial);
	void AddCloneResource(CRes* _pRes) { m_vecCloneRes.push_back(_pRes); }
private:
	int AddMesh(const wstring& _strKey, CMesh* _pMesh);
	
	CPrefab* FindPrefab(const wstring& _strKey);
	CMesh* FindMesh(const wstring& _strKey);
	CTexture* FindTexture(const wstring& _strKey);
	CMaterial* FindMaterial(const wstring& _strKey);
private:
	map<wstring, CResPtr<CMesh>>& GetMeshMap() { return m_mapMesh; }
	map<wstring, CResPtr<CMaterial>>& GetMaterialMap() { return m_mapMaterial; }
public:
	template <typename T>
	CRes* Load(const wstring& _strKey, const wstring& _strFilePath=L"");	

	friend class CListDlg;
};

template<typename T>
inline CRes * CResMgr::Load(const wstring & _strKey, const wstring & _strFilePath)
{
	const type_info& info = typeid(T);
	if (&info == &typeid(CMesh))
	{
		// Mesh �� �ڵ�θ� ������ file���� �ҷ��� �� ������ �ٷ� return ����.
		return (CRes*)FindMesh(_strKey);
	}
	else if (&info == &typeid(CTexture))
	{
		// Texture Key�� filePath�� ��ģ�ɷ� ����Ѵ�. 
		// �ٸ� �������� ���� �̸��� texture�� ���� �� �ִ�.
		wstring newKey = _strFilePath + _strKey;
	
		CTexture* pTexture = FindTexture(newKey);
		if (NULL != pTexture)
			return (CRes*)pTexture;
		wstring strFullPath = CPathMgr::GetResourcePath();
		strFullPath += _strFilePath;
		pTexture = CTexture::Create(strFullPath);
		if (NULL == pTexture)
			return NULL;
		pTexture->SetKey(newKey);
		pTexture->SetPath(_strFilePath);
		m_mapTexture.insert(make_pair(newKey, pTexture));
		return (CRes*)pTexture;
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
