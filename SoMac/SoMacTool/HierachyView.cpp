// HierachyView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "HierachyView.h"


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
