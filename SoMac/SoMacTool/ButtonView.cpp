// ButtonView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ButtonView.h"


// CButtonView

IMPLEMENT_DYNCREATE(CButtonView, CFormView)

CButtonView::CButtonView()
	: CFormView(IDD_BUTTONVIEW)
{

}

CButtonView::~CButtonView()
{
}

void CButtonView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CButtonView, CFormView)
END_MESSAGE_MAP()


// CButtonView diagnostics

#ifdef _DEBUG
void CButtonView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CButtonView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CButtonView message handlers
