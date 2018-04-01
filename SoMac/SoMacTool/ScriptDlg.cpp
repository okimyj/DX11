// ScriptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ScriptDlg.h"
#include "afxdialogex.h"
#include "../External/ScriptMgr.h"

#include "GameObject.h"
#include "Script.h"
// CScriptDlg dialog

IMPLEMENT_DYNAMIC(CScriptDlg, CDialogEx)

CScriptDlg::CScriptDlg(CWnd* pParent /*=NULL*/)
	: CComponentDlg(IDD_SCRIPTDLG, pParent)
{
	m_pName = L"Script";
}

CScriptDlg::~CScriptDlg()
{
}

void CScriptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbScript);
	DDX_Control(pDX, IDC_LIST2, m_listScript);
}

BOOL CScriptDlg::OnInitDialog()
{
	CComponentDlg::OnInitDialog();

	vector<tScriptInfo> vecScriptInfo;
	CScriptMgr::GetScriptInfo(vecScriptInfo);
	for (UINT i = 0; i < vecScriptInfo.size(); ++i)
	{
		m_cbScript.InsertString(i, vecScriptInfo[i].strScriptName.c_str());
		m_cbScript.SetItemData(i, vecScriptInfo[i].dwTypeID);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}
void CScriptDlg::Update(CGameObject * _pObj, bool _bForce)
{
	// list 갱신은 항상 해야하는게 아니기 때문에 타겟이 다르거나 강제로 update를 호출 했을 때만 갱신한다.
	if (m_pTargetObj != _pObj || _bForce)
	{
		m_pTargetObj = _pObj;
		m_listScript.ResetContent();
		list<CScript*> listScript = m_pTargetObj->GetScriptList();
		list<CScript*>::iterator iter = listScript.begin();
		for (int i=0; iter != listScript.end(); ++iter, ++i)
		{
			CString strName = CScriptMgr::GetScriptName(*iter);
			m_listScript.InsertString(i, strName);
		}
	}
	m_pTargetObj = _pObj;
	if (NULL == m_pTargetObj)
		return;

}


BEGIN_MESSAGE_MAP(CScriptDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CScriptDlg::OnSelchangeCombo)
END_MESSAGE_MAP()


// CScriptDlg message handlers




void CScriptDlg::OnSelchangeCombo()
{
	int iIdx = m_cbScript.GetCurSel();
	if (-1 == iIdx)
		return;
	DWORD dwTypeID = m_cbScript.GetItemData(iIdx);

	CScript* pScript = CScriptMgr::GetScript(dwTypeID);
	m_pTargetObj->AddComponent<CScript>(pScript);
	Update(m_pTargetObj, true);
	SetFocusGameView();
}
