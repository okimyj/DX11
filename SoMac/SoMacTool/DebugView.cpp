// DebugView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "DebugView.h"


// CDebugView

IMPLEMENT_DYNCREATE(CDebugView, CFormView)

CDebugView::CDebugView()
	: CFormView(IDD_DEBUGVIEW)
{

}

CDebugView::~CDebugView()
{
}

void CDebugView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDebugView, CFormView)
END_MESSAGE_MAP()


// CDebugView diagnostics

#ifdef _DEBUG
void CDebugView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDebugView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDebugView message handlers
