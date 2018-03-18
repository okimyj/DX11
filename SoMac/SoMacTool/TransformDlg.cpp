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
	m_pName = L"Transform";
}

CTransformDlg::~CTransformDlg()
{
}

void CTransformDlg::Update(CGameObject * _pObj, bool _bForce)
{
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;
	m_editName.SetWindowTextW(_pObj->GetTag().c_str());
	m_editLayerName.SetWindowTextW(_pObj->GetLayerName().c_str());
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
	DDX_Control(pDX, IDC_OBJ_NAME, m_editName);
	DDX_Control(pDX, IDC_LAYER_NAME, m_editLayerName);
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
	if (m_iFocusedEditID != _id)
		return;
	int index = _id - IDC_POS_X;
	CString str;
	m_arrEdit[index].GetWindowTextW(str);
	float f = _wtof(str.GetBuffer());
	if (_id <= IDC_POS_Z)
	{
		Vec3 vPos = m_pTargetObj->GetTransform()->GetLocalPosition();
		vPos[index % 3] = f;
		m_pTargetObj->GetTransform()->SetLocalPosition(vPos);
	}
	else if (_id <= IDC_ROT_Z)
	{
		Vec3 vRot = m_pTargetObj->GetTransform()->GetLocalRotation();
		vRot[index % 3] = f;
		m_pTargetObj->GetTransform()->SetLocalRotation(vRot);
	}
	else if (_id <= IDC_SCALE_Z)
	{
		Vec3 vScale = m_pTargetObj->GetTransform()->GetLocalScale();
		vScale[index % 3] = f;
		m_pTargetObj->GetTransform()->SetLocalScale(vScale);
	}
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

void CTransformDlg::OnOK()
{
	if (m_iFocusedEditID != -1)
	{
		SetFocusGameView();
		m_iFocusedEditID = -1;
	}
}
