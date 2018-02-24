// ComponentView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ComponentView.h"


// CComponentView

IMPLEMENT_DYNCREATE(CComponentView, CFormView)

CComponentView::CComponentView()
	: CFormView(IDD_COMPONENTVIEW)
{

}

CComponentView::~CComponentView()
{
}

void CComponentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CComponentView, CFormView)
END_MESSAGE_MAP()


// CComponentView diagnostics

#ifdef _DEBUG
void CComponentView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CComponentView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CComponentView message handlers
