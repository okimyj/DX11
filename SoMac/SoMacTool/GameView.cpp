// GameView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "GameView.h"


// CGameView

IMPLEMENT_DYNCREATE(CGameView, CFormView)

CGameView::CGameView()
	: CFormView(IDD_GAMEVIEW)
{

}

CGameView::~CGameView()
{
}

void CGameView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameView, CFormView)
END_MESSAGE_MAP()


// CGameView diagnostics

#ifdef _DEBUG
void CGameView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CGameView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CGameView message handlers
