// MeshRendererDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "MeshRendererDlg.h"
#include "afxdialogex.h"

#include "GameObject.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Material.h"

#include "ListDlg.h"
// CMeshRendererDlg dialog

IMPLEMENT_DYNAMIC(CMeshRendererDlg, CDialogEx)

CMeshRendererDlg::CMeshRendererDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_MESHRENDERERDLG, pParent)
{
	m_pName = L"MeshRenderer";
}

CMeshRendererDlg::~CMeshRendererDlg()
{
}

void CMeshRendererDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RS_TYPE_COM, m_cbRSType);
	DDX_Control(pDX, IDC_MESH_EDIT, m_editMesh);
	DDX_Control(pDX, IDC_MTRL_EDIT, m_editMtrl);
}

void CMeshRendererDlg::Update(CGameObject * _pObj, bool _bForce)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;
	CString str;
	CMeshRenderer* pMeshRenderer = m_pTargetObj->GetMeshRender();
	str = L"";
	if (NULL != pMeshRenderer->GetMesh())
		str = pMeshRenderer->GetMesh()->GetKey().c_str();	
	m_editMesh.SetWindowTextW(str);
	str = L"";
	if(NULL != pMeshRenderer->GetSharedMaterial())
		str = pMeshRenderer->GetSharedMaterial()->GetKey().c_str();
	
	m_editMtrl.SetWindowTextW(str);
	if (!m_bFocusRSType)
	{
		int iSel = (UINT)m_pTargetObj->GetMeshRender()->GetRSType();
		m_cbRSType.SetCurSel(iSel);
	}
	
}



BEGIN_MESSAGE_MAP(CMeshRendererDlg, CDialogEx)
	ON_CBN_SETFOCUS(IDC_RS_TYPE_COM, &CMeshRendererDlg::OnSetFocusRsTypeCombo)
	ON_CBN_KILLFOCUS(IDC_RS_TYPE_COM, &CMeshRendererDlg::OnKillFocusRsTypeCombo)
	ON_CBN_EDITCHANGE(IDC_RS_TYPE_COM, &CMeshRendererDlg::OnChangeRSTypeCombo)
	ON_CBN_SELCHANGE(IDC_RS_TYPE_COM, &CMeshRendererDlg::OnSelectedRSTypeCombo)
	ON_BN_CLICKED(IDC_MESH_BTN, &CMeshRendererDlg::OnClickedMeshBtn)
	ON_BN_CLICKED(IDC_MTRL_BTN, &CMeshRendererDlg::OnClickedMtrlBtn)
END_MESSAGE_MAP()


// CMeshRendererDlg message handlers


void CMeshRendererDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}



BOOL CMeshRendererDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();

	// TODO:  Add extra initialization here

	
	m_cbRSType.InsertString(0, L"FRONT");
	m_cbRSType.InsertString(1, L"BACK");
	m_cbRSType.InsertString(2, L"WIRE_FRAME");
	m_cbRSType.InsertString(3, L"NONE");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeshRendererDlg::OnSetFocusRsTypeCombo()
{
	m_bFocusRSType = true;
}

void CMeshRendererDlg::OnKillFocusRsTypeCombo()
{
	m_bFocusRSType = false;
}

// combo box를 눌렀을 때.
void CMeshRendererDlg::OnChangeRSTypeCombo()
{
	int iSelected = (UINT)m_pTargetObj->GetMeshRender()->GetRSType();
	m_cbRSType.SetCurSel(iSelected);
}

// combo box의 무언가를 선택 했을 때.
void CMeshRendererDlg::OnSelectedRSTypeCombo()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbRSType.GetCurSel();
	m_pTargetObj->GetMeshRender()->SetRSType((RASTERIZE_TYPE)iSel);
	SetFocusGameView();
}


void CMeshRendererDlg::OnClickedMeshBtn()
{
	CListDlg listDlg;
	listDlg.SetInitType(RESOURCE_TYPE::MESH);
	// 내부에서 선택된 Mesh의 주소값을 반환한다.
	CMesh* pMesh =  (CMesh*)listDlg.DoModal();
	if (NULL == pMesh)
		return;

	m_pTargetObj->GetMeshRender()->SetMesh(pMesh);
	SetFocusGameView();
}


void CMeshRendererDlg::OnClickedMtrlBtn()
{
	CListDlg listDlg;
	listDlg.SetInitType(RESOURCE_TYPE::MATERIAL);	
	CMaterial* pMaterial = (CMaterial*)listDlg.DoModal();
	if (NULL == pMaterial)
		return;
	m_pTargetObj->GetMeshRender()->SetMaterial(pMaterial);
	SetFocusGameView();
}
