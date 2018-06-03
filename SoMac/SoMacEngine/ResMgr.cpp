#include "ResMgr.h"
#include "ShaderMgr.h"
#include "Mesh.h"
#include "Texture.h"
#include "Prefab.h"
#include "Material.h"


CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	Safe_Delete_Map_ResPtr(m_mapMesh);
	Safe_Delete_Map_ResPtr(m_mapTexture);
	Safe_Delete_Map_ResPtr(m_mapPrefab);
	Safe_Delete_Map_ResPtr(m_mapMaterial);
	Safe_Delete_Vector_ResPtr(m_vecCloneRes);
}

void CResMgr::Init()
{
	CreateDefaultMesh();
	CreateDefaultMaterial();
}
void CResMgr::NotifyUpdate()
{
#ifdef _SOMAC_TOOL
	CallbackUpdate();
#endif
}
void CResMgr::CreateDefaultMesh()
{
	//== Create Default Mesh ==//
	vector<VTX> vecVtx; VTX v;
	vector<WORD> vecIdx;
	
	
	v.vPos = Vec3(-0.5f, -0.5f, 0.f);
	v.vUV = Vec2(0.f, 1.f);
	v.vColor = Vec4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(-0.5f, 0.5f, 0.f);
	v.vUV = Vec2(0.f, 0.f);
	v.vColor = Vec4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, 0.5f, 0.f);
	v.vUV = Vec2(1.f, 0.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vec3(0.5f, -0.5f, 0.f);
	v.vUV = Vec2(1.f, 1.f);
	v.vColor = Vec4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0); vecIdx.push_back(1); vecIdx.push_back(3);
	vecIdx.push_back(1); vecIdx.push_back(2); vecIdx.push_back(3);
	
	// == Create Rect Mesh. ==//
	int iIdxCount = 6;			// Dx9 에서는 Index의 개수 (arrIdx.size = 2)였는데, 11에서는 정점의 개수임. (6)
	CMesh* pMesh = CMesh::Create(vecVtx.size(), sizeof(VTX), D3D11_USAGE_DEFAULT, &vecVtx[0]
		, vecIdx.size(), INDEX16::size(), D3D11_USAGE_DEFAULT, INDEX16::format(), &vecIdx[0]);
	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	AddMesh(L"RectMesh", pMesh);

	// == Create Collider RectMesh ==//
	vecIdx.clear();
	vecIdx.push_back(0); vecIdx.push_back(1); 
	vecIdx.push_back(2); vecIdx.push_back(3); vecIdx.push_back(0);

	pMesh = CMesh::Create(vecVtx.size(), sizeof(VTX), D3D11_USAGE_DEFAULT, &vecVtx[0], vecIdx.size(), INDEX16::size()
		, D3D11_USAGE_DEFAULT, INDEX16::format(), &vecIdx[0], D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	AddMesh(L"ColliderRectMesh", pMesh);
}

void CResMgr::CreateDefaultMaterial()
{
	//== Create Default Material ==//
	CMaterial* pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	AddMaterial(L"Default", pMaterial);
	//== Create Collider Material == //
	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"ColliderShader"));
	AddMaterial(L"ColliderMaterial", pMaterial);
	//== Create Standard Materail ==//
	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"Standard2DShader"));
	CResMgr::GetInst()->AddMaterial(L"StandardMaterial", pMaterial);

}

int CResMgr::AddMesh(const wstring & _strKey, CMesh * _pMesh)
{
	CMesh* pMesh = FindMesh(_strKey);
	if (NULL != pMesh || NULL == _pMesh)
	{
		return RET_FAILED;
	}
	_pMesh->SetKey(_strKey);
	m_mapMesh.insert(make_pair(_strKey, _pMesh));
	NotifyUpdate();
	return RET_SUCCESS;
}

int CResMgr::AddPrefab(const wstring & _strKey, CGameObject * _pObj)
{
	CPrefab* pPrefab = FindPrefab(_strKey);
	if (NULL != pPrefab || NULL == _pObj)
		return RET_FAILED;
	pPrefab = new CPrefab(_pObj);
	pPrefab->SetKey(_strKey);
	m_mapPrefab.insert(make_pair(_strKey, pPrefab));
	NotifyUpdate();
	return RET_SUCCESS;
}

int CResMgr::AddMaterial(const wstring & _strKey, CMaterial * _pMaterial)
{
	CMaterial* pMaterial = FindMaterial(_strKey);
	if (NULL != pMaterial || NULL == _pMaterial)
		return RET_FAILED;
	_pMaterial->SetKey(_strKey);
	m_mapMaterial.insert(make_pair(_strKey, _pMaterial));
	NotifyUpdate();
	return 0;
}


CPrefab * CResMgr::FindPrefab(const wstring & _strKey)
{
	map<wstring, CResPtr<CPrefab>>::iterator iter = m_mapPrefab.find(_strKey);
	if (iter == m_mapPrefab.end())
		return NULL;
	return iter->second;
}

CMesh * CResMgr::FindMesh(const wstring & _strKey)
{
	map<wstring, CResPtr<CMesh>>::iterator iter = m_mapMesh.find(_strKey);
	if (iter == m_mapMesh.end())
		return NULL;
	return iter->second;
}

CTexture * CResMgr::FindTexture(const wstring & _strKey)
{
	map<wstring, CResPtr<CTexture>>::iterator iter = m_mapTexture.find(_strKey);
	if (iter == m_mapTexture.end())
		return NULL;
	return iter->second;
}

CMaterial * CResMgr::FindMaterial(const wstring & _strKey)
{
	map<wstring, CResPtr<CMaterial>>::iterator iter = m_mapMaterial.find(_strKey);
	if (iter == m_mapMaterial.end())
		return NULL;
	return iter->second;
}

void CResMgr::SaveResource(FILE* _pFile)
{
	int iRefCount = 0;
	//-- Mesh --//
	UINT iCount = m_mapMesh.size();
	WriteUINT(iCount, _pFile);
	map<wstring, CResPtr<CMesh>>::iterator iter = m_mapMesh.begin();
	for (; iter != m_mapMesh.end(); ++iter)
	{
		iRefCount = iter->second->GetRefCount();
		WriteInt(iRefCount, _pFile);
		if (1 < iRefCount)
			iter->second.GetTarget()->Save(_pFile);
	}
	//-- Texture --//
	iCount = m_mapTexture.size();
	WriteUINT(iCount, _pFile);
	map<wstring, CResPtr<CTexture>>::iterator texIter = m_mapTexture.begin();
	for (; texIter != m_mapTexture.end(); ++texIter)
	{
		iRefCount = texIter->second->GetRefCount();
		WriteInt(iRefCount, _pFile);
		if (1 < iRefCount)
			texIter->second.GetTarget()->Save(_pFile);
	}
	//-- Material --//
	iCount = m_mapMaterial.size();
	WriteUINT(iCount, _pFile);
	map<wstring, CResPtr<CMaterial>>::iterator mtrlIter = m_mapMaterial.begin();
	for (; mtrlIter != m_mapMaterial.end(); ++mtrlIter)
	{
		iRefCount = mtrlIter->second->GetRefCount();
		WriteInt(iRefCount, _pFile);
		if (1 < iRefCount)
			mtrlIter->second.GetTarget()->Save(_pFile);
	}

	//-- Sound --//

}
void CResMgr::LoadResource(FILE* _pFile)
{
	int iRefCount = 0;
	wstring strKey;
	wstring strPath;
	//-- Mesh --//
	UINT iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		iRefCount = ReadInt(_pFile);
		if (1 < iRefCount)
		{
			strKey = ReadWString(_pFile);
			strPath = ReadWString(_pFile);
			Load<CMesh>(strKey, strPath);
		}
	}
	//-- Texture --//
	iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		iRefCount = ReadInt(_pFile);
		if (1 < iRefCount)
		{
			strKey = ReadWString(_pFile);
			strPath = ReadWString(_pFile);
			Load<CTexture>(strKey, strPath);
		}
	}
	//-- Material --//
	iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		iRefCount = ReadInt(_pFile);
		if (1 < iRefCount)
		{
			strKey = ReadWString(_pFile);
			strPath = ReadWString(_pFile);
			Load<CMaterial>(strKey, strPath);
		}
	}
	//-- Sound --//
}