#include "stdafx.h"
#include "ComponentDlg.h"
#include "MainFrm.h"

CComponentDlg::CComponentDlg()
	:m_pTargetObj(NULL)
{
}

CComponentDlg::CComponentDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
	, m_pTargetObj(NULL)
{
}


CComponentDlg::~CComponentDlg()
{
}

void CComponentDlg::SetFocusGameView()
{
	::SetFocus(((CMainFrame*)AfxGetApp()->m_pMainWnd)->GetGameViewHwnd());
}

void CComponentDlg::OnOK()
{
}


void CComponentDlg::OnCancel()
{	
}
