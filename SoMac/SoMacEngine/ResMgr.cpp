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
	Safe_Delete_Map(m_mapMesh);
	Safe_Delete_Map(m_mapTexture);
	Safe_Delete_Map(m_mapPrefab);
	Safe_Delete_Map(m_mapMaterial);
}

void CResMgr::Init()
{
	CreateDefaultMesh();
	CreateDefaultMaterial();
}
void CResMgr::CreateDefaultMesh()
{
	//== Create Default Mesh ==//
	VTX arrVtx[4] = {};
	arrVtx[0].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[0].vUV = Vec2(0.f, 1.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[1].vUV = Vec2(0.f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);


	arrVtx[2].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[2].vUV = Vec2(1.f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	arrVtx[3].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[3].vUV = Vec2(1.f, 1.f);
	arrVtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	INDEX16 arrIdx[2] = {};

	arrIdx[0] = INDEX16(0, 1, 3);
	arrIdx[1] = INDEX16(1, 2, 3);

	// Create Mesh.
	int iIdxCount = 6;			// Dx9 에서는 Index의 개수 (arrIdx.size = 2)였는데, 11에서는 정점의 개수임. (6)
	CMesh* pMesh = CMesh::Create(4, sizeof(VTX), D3D11_USAGE_DEFAULT, arrVtx
		, iIdxCount, INDEX16::size(), D3D11_USAGE_DEFAULT, INDEX16::format(), arrIdx);
	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	AddMesh(L"RectMesh", pMesh);
}

void CResMgr::CreateDefaultMaterial()
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	AddMaterial(L"Default", pMaterial);
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

	return RET_SUCCESS;
}

int CResMgr::AddMaterial(const wstring & _strKey, CMaterial * _pMaterial)
{
	CMaterial* pMaterial = FindMaterial(_strKey);
	if (NULL != pMaterial || NULL == _pMaterial)
		return RET_FAILED;
	_pMaterial->SetKey(_strKey);
	m_mapMaterial.insert(make_pair(_strKey, _pMaterial));
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


