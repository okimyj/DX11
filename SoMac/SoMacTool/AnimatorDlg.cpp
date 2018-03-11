// AnimatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "AnimatorDlg.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "Animator.h"
#include "Animation.h"
#include "Add2DAnimDlg.h"
// CAnimatorDlg dialog

IMPLEMENT_DYNAMIC(CAnimatorDlg, CDialogEx)

CAnimatorDlg::CAnimatorDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_ANIMATORDLG, pParent)
{
	m_pName = L"Animator";
}

CAnimatorDlg::~CAnimatorDlg()
{
}

void CAnimatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANIM_COMB, m_cbAnim);
	DDX_Control(pDX, IDC_CHECK1, m_ckRepeat);
}


BEGIN_MESSAGE_MAP(CAnimatorDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnimatorDlg::OnBnClickedButton1)
	ON_CBN_SETFOCUS(IDC_ANIM_COMB, &CAnimatorDlg::OnSetFocusAnimComb)
	ON_CBN_KILLFOCUS(IDC_ANIM_COMB, &CAnimatorDlg::OnKillFocusAnimComb)
	ON_CBN_EDITCHANGE(IDC_ANIM_COMB, &CAnimatorDlg::OnChangeAnimComb)
	ON_CBN_SELCHANGE(IDC_ANIM_COMB, &CAnimatorDlg::OnSelectedAnimComb)
	ON_BN_CLICKED(IDC_CHECK1, &CAnimatorDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CAnimatorDlg message handlers


void CAnimatorDlg::Update(CGameObject* _pObj, bool _bForce)
{
	
	// list를 갱신하는건 계속 update 해야하는 부분이 아니기 때문에 현재 target과 update 되는 object가 다를 때만 실행한다.
	if(m_pTargetObj != _pObj || _bForce)
	{
		m_bFocusAnimComb = false;
		m_cbAnim.Clear();
		if (NULL == _pObj)
		{
			m_pTargetObj = NULL;
			return;
		}

		map<wstring, CAnimation*> mapAnim = _pObj->GetAnimator()->GetAnimationMap();
		map<wstring, CAnimation*>::iterator iter = mapAnim.begin();
		for (int i = 0; iter != mapAnim.end(); ++iter, ++i)
		{
			m_cbAnim.InsertString(i, iter->first.c_str());
		}		
	}
	
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;
	CAnimator* pAnimator = m_pTargetObj->GetAnimator();
	m_ckRepeat.SetCheck(pAnimator->IsRepeat());
	if (!m_bFocusAnimComb)
	{
		if (NULL != pAnimator->GetCurAnim())
			m_cbAnim.SelectString(-1, pAnimator->GetCurAnim()->GetKey().c_str());
		else
		{
			m_cbAnim.SetCurSel(-1);
		}

	}
	
}

void CAnimatorDlg::OnBnClickedButton1()
{
	CAdd2DAnimDlg dlg;
	dlg.SetTargetObject(m_pTargetObj);
	dlg.DoModal();
	Update(m_pTargetObj, true);
}

void CAnimatorDlg::OnSetFocusAnimComb()
{
	m_bFocusAnimComb = true;

}

void CAnimatorDlg::OnKillFocusAnimComb()
{
	m_bFocusAnimComb = false;
}

void CAnimatorDlg::OnChangeAnimComb()
{
	m_cbAnim.SelectString(-1, m_pTargetObj->GetAnimator()->GetCurAnim()->GetKey().c_str());
}


void CAnimatorDlg::OnSelectedAnimComb()
{
	int iSel = m_cbAnim.GetCurSel();
	CString str;
	m_cbAnim.GetLBText(iSel, str);
	m_pTargetObj->GetAnimator()->ChangeAnimation(str.GetBuffer());
	SetFocusGameView();
	
}



void CAnimatorDlg::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class
	delete this;
	CDialogEx::PostNcDestroy();
}


void CAnimatorDlg::OnBnClickedCheck1()
{
	CAnimator* pAnimator = m_pTargetObj->GetAnimator();
	pAnimator->SetRepeat(!pAnimator->IsRepeat());
	SetFocusGameView();
}
