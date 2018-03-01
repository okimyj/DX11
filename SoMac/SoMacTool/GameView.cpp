// GameView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "GameView.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "GameObject.h"
#include "MainFrm.h"
#include "ComponentView.h"
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
	ON_WM_LBUTTONUP()
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


void CGameView::OnLButtonUp(UINT nFlags, CPoint point)
{
	RECT rt = {};
	GetWindowRect(&rt);
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CGameObject* pObj = pCurScene->FindObject(Vec2((float)point.x, (float)point.y), Vec2((float)rt.right - rt.left, (float)rt.bottom - rt.top));
	if (NULL != pObj)
	{
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
		CComponentView* pCompView = (CComponentView*)pMainFrame->GetComponentView();
		pCompView->SetGameObject(pObj);
	}
	CFormView::OnLButtonUp(nFlags, point);
}
