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
#include "ScriptDlg.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Collider2D.h"
#include "Animator.h"
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
	DDX_Control(pDX, IDC_BUTTON1, m_btAC);
	DDX_Control(pDX, IDC_COMBO1, m_cbAC);
	m_btAC.ShowWindow(false);
	m_cbAC.ShowWindow(false);
	
}

void CComponentView::SetGameObject(CGameObject * _pObj, bool _bForce)
{
	if (!_bForce && m_pTargetObj == _pObj)
		return;

	m_pTargetObj = _pObj;
	m_cbAC.ResetContent();
	INT iStartY = 0;
	UINT iIndex = 0;
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// 해당 dialog가 없거나 targetObject 에 component가 없으면 다음꺼.
		if (NULL == m_pTargetObj || NULL == m_arrDlg[i] || NULL == m_pTargetObj->GetComponent((COMPONENT_TYPE)i))
		{
			if (NULL != m_arrDlg[i])
			{
				m_arrDlg[i]->ShowWindow(false);
				
				m_cbAC.InsertString(iIndex, m_arrDlg[i]->GetName());
				m_cbAC.SetItemData(iIndex++, i);
		
			}				
			continue;
		}
		RECT rt = {};
		m_arrDlg[i]->GetWindowRect(&rt);
		m_arrDlg[i]->ShowWindow(true);
		m_arrDlg[i]->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
		m_arrDlg[i]->Update(m_pTargetObj);
		iStartY += rt.bottom - rt.top - 1;
	}

	if (NULL == m_pTargetObj)
	{
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->ShowWindow(false);
		m_btAC.ShowWindow(false);
	}
	else
	{
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->ShowWindow(true);
		RECT rt = {};
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->GetWindowRect(&rt);
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->ShowWindow(true);
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->SetWindowPos(NULL, 0, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
		m_arrDlg[(UINT)COMPONENT_TYPE::END]->Update(m_pTargetObj);
		iStartY += rt.bottom - rt.top - 1;

		m_btAC.ShowWindow(true);
		m_btAC.GetWindowRect(&rt);
		ScreenToClient(&rt);
		iStartY += 35;
		m_btAC.SetWindowPos(NULL, rt.left, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
		iStartY += rt.bottom - rt.top + 10;
		m_cbAC.GetWindowRect(&rt);
		ScreenToClient(&rt);
		m_cbAC.SetWindowPos(NULL, rt.left, iStartY, rt.right - rt.left, rt.bottom - rt.top, 0);
	}
	m_cbAC.ShowWindow(false);
}



void CComponentView::UpdateComponents()
{
	if (NULL == m_pTargetObj)
		return;
	
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		// 해당 dialog가 없거나 targetObject 에 component가 없으면 다음꺼.
		if (NULL == m_pTargetObj || NULL == m_arrDlg[i] || NULL == m_pTargetObj->GetComponent((COMPONENT_TYPE)i))
		{
			continue;
		}
		m_arrDlg[i]->Update(m_pTargetObj);
	}
}

BEGIN_MESSAGE_MAP(CComponentView, CFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CComponentView::OnAddComponentClicked)
	ON_CBN_SETFOCUS(IDC_COMBO1, &CComponentView::OnSetFocusACCombo)
	ON_CBN_KILLFOCUS(IDC_COMBO1, &CComponentView::OnKillFocusACCombo)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CComponentView::OnSelchangeACCombo)
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

	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER_2D] = new CColliderDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER_2D]->Create(IDD_COLLIDERDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER_2D]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::COLLIDER_2D]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR] = new CAnimatorDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->Create(IDD_ANIMATORDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::ANIMATOR]->UpdateWindow();

	m_arrDlg[(UINT)COMPONENT_TYPE::END] = new CScriptDlg;
	m_arrDlg[(UINT)COMPONENT_TYPE::END]->Create(IDD_SCRIPTDLG, this);
	m_arrDlg[(UINT)COMPONENT_TYPE::END]->ShowWindow(false);
	m_arrDlg[(UINT)COMPONENT_TYPE::END]->UpdateWindow();

	return 0;
}

void CComponentView::Update()
{
	UpdateComponents();
}

void CComponentView::OnAddComponentClicked()
{
	m_cbAC.ShowWindow(true);
}

void CComponentView::OnSetFocusACCombo()
{
	m_bACFocused = true;
}

void CComponentView::OnKillFocusACCombo()
{
	m_bACFocused = false;
}


void CComponentView::OnSelchangeACCombo()
{
	int iSelected = m_cbAC.GetCurSel();
	if (-1 == iSelected)
		return;
	UINT compType = m_cbAC.GetItemData(iSelected);
	switch (compType)
	{
	case (UINT)COMPONENT_TYPE::TRANSFORM:
		m_pTargetObj->AddComponent<CTransform>(new CTransform);
		break;
	case (UINT)COMPONENT_TYPE::MESHRENDER:
		m_pTargetObj->AddComponent<CMeshRenderer>(new CMeshRenderer);
		break;
	case (UINT)COMPONENT_TYPE::CAMERA:
		m_pTargetObj->AddComponent<CCamera>(new CCamera);
		break;
	case (UINT)COMPONENT_TYPE::COLLIDER_2D:
		m_pTargetObj->AddComponent<CCollider2D>(new CCollider2D);
		break;
	case (UINT)COMPONENT_TYPE::ANIMATOR:
		m_pTargetObj->AddComponent<CAnimator>(new CAnimator);
		break;
	}
	SetGameObject(m_pTargetObj, true);
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
