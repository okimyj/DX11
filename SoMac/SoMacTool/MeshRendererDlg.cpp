// MeshRendererDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "MeshRendererDlg.h"
#include "afxdialogex.h"


// CMeshRendererDlg dialog

IMPLEMENT_DYNAMIC(CMeshRendererDlg, CDialogEx)

CMeshRendererDlg::CMeshRendererDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_MESHRENDERERDLG, pParent)
{

}

CMeshRendererDlg::~CMeshRendererDlg()
{
}


void CMeshRendererDlg::Update(CGameObject * _pObj)
{
}

void CMeshRendererDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMeshRendererDlg, CDialogEx)
END_MESSAGE_MAP()


// CMeshRendererDlg message handlers


void CMeshRendererDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}
