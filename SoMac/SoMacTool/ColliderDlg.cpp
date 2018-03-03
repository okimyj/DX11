// ColliderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ColliderDlg.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "Collider.h"

// CColliderDlg dialog

IMPLEMENT_DYNAMIC(CColliderDlg, CDialogEx)

CColliderDlg::CColliderDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_COLLIDERDLG, pParent)
{

}

CColliderDlg::~CColliderDlg()
{
}

void CColliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_ckbApplyScale);
	int iStrtIdx = IDC_OFF_POS_X;
	for (int i = 0; i < 6; ++i)
	{
		DDX_Control(pDX, iStrtIdx + i, m_arrEdit[i]);
	}
}




BEGIN_MESSAGE_MAP(CColliderDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_OFF_POS_X, IDC_OFF_SCALE_Z, &CColliderDlg::OnEnSetfocus)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_OFF_POS_X, IDC_OFF_SCALE_Z, &CColliderDlg::OnEnKillfocus)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_OFF_POS_X, IDC_OFF_SCALE_Z, &CColliderDlg::OnEnChange)
	ON_BN_CLICKED(IDC_CHECK1, &CColliderDlg::OnClickedApplyScale)
END_MESSAGE_MAP()


// CColliderDlg message handlers

void CColliderDlg::Update(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;

	CCollider* pCollider = m_pTargetObj->GetCollider();
	Vec3 vValues[2] = { pCollider->GetOffsetPos(), pCollider->GetOffsetScale() };
	CString str;
	for (int i = 0; i < 6; ++i)
	{
		int controlID = m_arrEdit[i].GetDlgCtrlID();
		if (controlID != m_iFocusedEditID)
		{
			str.Format(L"%.2f", vValues[i / 3][i % 3]);
			m_arrEdit[i].SetWindowTextW(str);
		}
	}
	m_ckbApplyScale.SetCheck(pCollider->GetApplyScale());
}
void CColliderDlg::OnEnSetfocus(UINT _id)
{
	m_iFocusedEditID = _id;
}

void CColliderDlg::OnEnKillfocus(UINT _id)
{
	m_iFocusedEditID = -1;
}

void CColliderDlg::OnEnChange(UINT _id)
{
	if (m_iFocusedEditID != _id)
		return;
	int index = _id - IDC_OFF_POS_X;
	CString str;
	m_arrEdit[index].GetWindowTextW(str);
	float f = _wtof(str.GetBuffer());
	if (_id <= IDC_OFF_POS_Z)
	{
		Vec3 vOffsetPos = m_pTargetObj->GetCollider()->GetOffsetPos();
		vOffsetPos[index % 3] = f;
		m_pTargetObj->GetCollider()->SetOffsetPos(vOffsetPos);
	}
	else if (_id <= IDC_OFF_SCALE_Z)
	{
		Vec3 vOffsetScale = m_pTargetObj->GetCollider()->GetOffsetScale();
		vOffsetScale[index % 3] = f;
		m_pTargetObj->GetCollider()->SetOffsetScale(vOffsetScale);
	}
}

void CColliderDlg::OnOK()
{
	if (m_iFocusedEditID != -1)
	{
		SetFocusGameView();
		m_iFocusedEditID = -1;
	}
}


void CColliderDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}


void CColliderDlg::OnClickedApplyScale()
{
	CCollider* pCollider = m_pTargetObj->GetCollider();
	pCollider->SetApplyScale(!pCollider->GetApplyScale());
}
