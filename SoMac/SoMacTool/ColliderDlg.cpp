// ColliderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ColliderDlg.h"
#include "afxdialogex.h"


// CColliderDlg dialog

IMPLEMENT_DYNAMIC(CColliderDlg, CDialogEx)

CColliderDlg::CColliderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COLLIDERDLG, pParent)
{

}

CColliderDlg::~CColliderDlg()
{
}

void CColliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CColliderDlg, CDialogEx)
END_MESSAGE_MAP()


// CColliderDlg message handlers
