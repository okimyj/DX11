// ResourceTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ResourceTreeDlg.h"
#include "afxdialogex.h"
#include "ResMgr.h"
#include "ResPtr.h"
#include "Res.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "Prefab.h"


// CResourceTreeDlg dialog

IMPLEMENT_DYNAMIC(CResourceTreeDlg, CDialogEx)

CResourceTreeDlg::CResourceTreeDlg(CWnd* pParent /*=NULL*/)
	: CTreeCtrlDlg(IDD_RESOURCETREEDLG, pParent)
{

}

CResourceTreeDlg::~CResourceTreeDlg()
{

}

void CResourceTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
}


BEGIN_MESSAGE_MAP(CResourceTreeDlg, CDialogEx)
END_MESSAGE_MAP()

void CResourceTreeDlg::PostNcDestroy()
{
	delete this;
	CDialogEx::PostNcDestroy();
}

BOOL CResourceTreeDlg::OnInitDialog()
{
	CTreeCtrlDlg::OnInitDialog();
	CResMgr::GetInst()->SetUpdateCallback(std::bind(&CResourceTreeDlg::UpdateTreeControl, this));
	m_hMeshRoot = AddItem(L"Mesh", NULL, NULL);
	m_hTextureRoot = AddItem(L"Texture", NULL, NULL);
	m_hMaterialRoot = AddItem(L"Material", NULL, NULL);
	m_hPrefabRoot = AddItem(L"Prefab", NULL, NULL);
	m_hCloneRoot = AddItem(L"Clone", NULL, NULL);
	return TRUE;
}

void CResourceTreeDlg::UpdateTreeControl()
{
	// rootItem 만 두고 모두 Delete. (Resource type 이름으로 된 최상위 item).
	HTREEITEM hRoot = m_ctrlTree.GetRootItem();
	while (NULL != hRoot)
	{
		DeleteChildren(hRoot);
		hRoot = m_ctrlTree.GetNextItem(hRoot, TVGN_NEXT);
	}

	map<wstring, CResPtr<CMesh>>& mapMesh = CResMgr::GetInst()->GetMeshMap();
	map<wstring, CResPtr<CTexture>>& mapTexture = CResMgr::GetInst()->GetTextureMap();
	map<wstring, CResPtr<CMaterial>>& mapMaterial = CResMgr::GetInst()->GetMaterialMap();
	map<wstring, CResPtr<CPrefab>>& mapPrefab = CResMgr::GetInst()->GetPrefabMap();
	vector<CResPtr<CRes>>& vecCloneRes = CResMgr::GetInst()->GetCloneVector();

	map<wstring, CResPtr<CMesh>>::iterator iterMesh = mapMesh.begin();
	for (; iterMesh != mapMesh.end(); ++iterMesh)
		AddItem(iterMesh->second->GetKey(), (DWORD_PTR)((CRes*)iterMesh->second), m_hMeshRoot);

	map<wstring, CResPtr<CTexture>>::iterator iterTexture = mapTexture.begin();
	for (; iterTexture != mapTexture.end(); ++iterTexture)
		AddItem(iterMesh->second->GetKey(), (DWORD_PTR)((CRes*)iterMesh->second), m_hTextureRoot);

	map<wstring, CResPtr<CMaterial>>::iterator iterMaterial = mapMaterial.begin();
	for(; iterMaterial != mapMaterial.end(); ++iterMaterial)
		AddItem(iterMaterial->second->GetKey(), (DWORD_PTR)((CRes*)iterMaterial->second), m_hMaterialRoot);


	map<wstring, CResPtr<CPrefab>>::iterator iterPrefab = mapPrefab.begin();
	for(; iterPrefab != mapPrefab.end(); ++iterPrefab)
		AddItem(iterPrefab->second->GetKey(), (DWORD_PTR)((CRes*)iterPrefab->second), m_hPrefabRoot);

	for(UINT i=0; i<vecCloneRes.size(); ++i)
		AddItem(vecCloneRes[i]->GetKey(), (DWORD_PTR)((CRes*)vecCloneRes[i]), m_hCloneRoot);

}
