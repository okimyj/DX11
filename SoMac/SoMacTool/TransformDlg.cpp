// TransformDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "TransformDlg.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "Transform.h"

// CTransformDlg dialog

IMPLEMENT_DYNAMIC(CTransformDlg, CDialogEx)

CTransformDlg::CTransformDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_TRANSFORMDLG, pParent)
{

}

CTransformDlg::~CTransformDlg()
{
}

void CTransformDlg::Update(CGameObject * _pObj)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;
	
	CTransform* pTrans = m_pTargetObj->GetTransform();
	Vec3 vTransform[3] = { pTrans->GetLocalPosition(),  pTrans->GetLocalRotation(), pTrans->GetLocalScale() };
	CString str;
	for (int i = 0; i < 9; ++i)
	{
		int controlID = m_arrEdit[i].GetDlgCtrlID();
		if (controlID != m_iFocusedEditID)
		{
			str.Format(L"%.2f", vTransform[i / 3][i % 3]);
			m_arrEdit[i].SetWindowTextW(str);
		}
	}
		
	
}

void CTransformDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	int iStartID = IDC_POS_X;
	for (int i = 0; i < 9; ++i)
	{
		DDX_Control(pDX, iStartID++, m_arrEdit[i]);
	}
}

void CTransformDlg::OnEnSetfocus(UINT _id)
{
	m_iFocusedEditID = _id;
}

void CTransformDlg::OnEnKillfocus(UINT _id)
{
	m_iFocusedEditID = -1;
}

void CTransformDlg::OnEnChange(UINT _id)
{

}


BEGIN_MESSAGE_MAP(CTransformDlg, CDialogEx)
	ON_CONTROL_RANGE(EN_SETFOCUS, IDC_POS_X, IDC_SCALE_Z, &CTransformDlg::OnEnSetfocus)
	ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_POS_X, IDC_SCALE_Z, &CTransformDlg::OnEnKillfocus)
	ON_CONTROL_RANGE(EN_CHANGE, IDC_POS_X, IDC_SCALE_Z, &CTransformDlg::OnEnChange)
END_MESSAGE_MAP()


// CTransformDlg message handlers


void CTransformDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CComponentDlg::PostNcDestroy();
}
