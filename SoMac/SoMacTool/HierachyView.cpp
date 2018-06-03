// HierachyView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "HierachyView.h"
#include "HierachyTreeDlg.h"
#include "ResourceTreeDlg.h"

// CHierachyView

IMPLEMENT_DYNCREATE(CHierachyView, CFormView)

CHierachyView::CHierachyView()
	: CFormView(IDD_HIERACHYVIEW)
{

}

CHierachyView::~CHierachyView()
{
}

void CHierachyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHierachyView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CHierachyView diagnostics

#ifdef _DEBUG
void CHierachyView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CHierachyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHierachyView message handlers




int CHierachyView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pHierachyTree = new CHierachyTreeDlg;
	m_pHierachyTree->Create(IDD_HIERACHYTREEDLG, this);
	m_pHierachyTree->ShowWindow(true);
	m_pHierachyTree->UpdateWindow();


	m_pResourceTree = new CResourceTreeDlg;
	m_pResourceTree->Create(IDD_RESOURCETREEDLG, this);
	m_pResourceTree->ShowWindow(true);
	m_pResourceTree->UpdateWindow();

	
	return 0;
}


void CHierachyView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	UINT iStartY = 0;
	m_pHierachyTree->SetWindowPos(NULL, 0, iStartY, cx, cy *0.6f, 0);
	RECT rt = {};
	m_pHierachyTree->GetWindowRect(&rt);
	iStartY += rt.bottom - rt.top;
	m_pResourceTree->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, cy *0.4f, 0);
	// TODO: Add your message handler code here
}

void CHierachyView::Init()
{
	m_pHierachyTree->Init();
	m_pResourceTree->Init();
}