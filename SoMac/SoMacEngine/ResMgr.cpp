#include "ResMgr.h"
#include "Mesh.h"


CResMgr::CResMgr()
{
}


CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapMesh);
}

void CResMgr::Init()
{
	//== Create Default Mesh ==//
	VTX arrVtx[4] = {};
	arrVtx[0].vPos = Vec3(-0.5f, -0.5f, 0.f);
	arrVtx[0].vColor = Vec4(1.f, 0.f, 0.f, 1.f);

	arrVtx[1].vPos = Vec3(-0.5f, 0.5f, 0.f);
	arrVtx[1].vColor = Vec4(0.f, 1.f, 0.f, 1.f);

	arrVtx[2].vPos = Vec3(0.5f, 0.5f, 0.f);
	arrVtx[2].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	arrVtx[3].vPos = Vec3(0.5f, -0.5f, 0.f);
	arrVtx[3].vColor = Vec4(0.f, 0.f, 1.f, 1.f);

	INDEX16 arrIdx[2] = {};

	arrIdx[0] = INDEX16(0, 1, 3);
	arrIdx[1] = INDEX16(1, 2, 3);

	// Create Mesh.
	int iIdxCount = 6;			// Dx9 에서는 Index의 개수 (arrIdx.size = 2)였는데, 11에서는 정점의 개수임. (6)
	CMesh* pMesh = CMesh::Create(4, sizeof(VTX), D3D11_USAGE_DEFAULT, arrVtx
		, iIdxCount, INDEX16::size(), D3D11_USAGE_DEFAULT, INDEX16::format(), arrIdx);
	pMesh->AddLayoutDesc("POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0);
	pMesh->AddLayoutDesc("COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	AddMesh(L"RectMesh", pMesh);
}

int CResMgr::AddMesh(const wstring & _strKey, CMesh * _pMesh)
{
	CMesh* pMesh = FindMesh(_strKey);
	if (NULL != pMesh || NULL == _pMesh)
	{
		return RET_FAILED;
	}
	m_mapMesh.insert(make_pair(_strKey, _pMesh));

	return RET_SUCCESS;
}

CMesh * CResMgr::FindMesh(const wstring & _strKey)
{
	map<wstring, CResPtr<CMesh>>::iterator iter = m_mapMesh.find(_strKey);
	if (iter == m_mapMesh.end())
		return NULL;
	return iter->second;
}
