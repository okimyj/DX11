// ComponentView.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ComponentView.h"
#include "GameObject.h"
#include "TransformDlg.h"
#include "MeshRendererDlg.h"
#include "ColliderDlg.h"
#include "AnimatorDlg.h"
// CComponentView

IMPLEMENT_DYNCREATE(CComponentView, CFormView)

CComponentView::CComponentView()
	: CFormView(IDD_COMPONENTVIEW)
	, m_arrDlg{}
	, m_pTargetObj(NULL)
{

}

CComponentView::~CComponentView()
{
}

void CComponentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

void CComponentView::SetGameObject(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
}



void CComponentView::UpdateComponents()
{
	if (NULL == m_pTargetObj)
		return;

	INT iStartY = 0;
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// 해당 dialog가 없거나 targetObject 에 component가 없으면 다음꺼.
		if (NULL == m_arrDlg[i] || NULL == m_pTargetObj->GetComponent((COMPONENT_TYPE)i))
			continue;

		RECT rt = {};
		m_arrDlg[i]->GetWindowRect(&rt);
		m_arrDlg[i]->ShowWindow(true);
		m_arrDlg[i]->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
		m_arrDlg[i]->Update(m_pTargetObj);
		iStartY += rt.bottom - rt.top - 1;
	}
}

BEGIN_MESSAGE_MAP(CComponentView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
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


int CComponentView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM] = new CTransformDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->Create(IDD_TRANSFORMDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::TRANSFORM]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER] = new CMeshRendererDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->Create(IDD_MESHRENDERERDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::MESHRENDER]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER] = new CColliderDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->Create(IDD_COLLIDERDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR] = new CAnimatorDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->Create(IDD_ANIMATORDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->UpdateWindow();

	return 0;
}

void CComponentView::Update()
{
	UpdateComponents();
}

void CComponentView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: Add your message handler code here
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (NULL != m_arrDlg[i])
			m_arrDlg[i]->DestroyWindow();
	}
}
