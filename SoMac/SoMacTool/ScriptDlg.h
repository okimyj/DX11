#pragma once
#include "ComponentDlg.h"
#include "afxwin.h"

// CScriptDlg dialog

class CScriptDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CScriptDlg)

public:
	CScriptDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CScriptDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCRIPTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void Update(CGameObject* _pObj, bool _bForce = false);

private:
	CComboBox m_cbScript;
	CListBox m_listScript;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo();
};
