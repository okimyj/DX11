#pragma once
#include "afxwin.h"
#include "global.h"
#include "ComponentDlg.h"

// CAnimatorDlg dialog

class CAnimatorDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CAnimatorDlg)

public:
	CAnimatorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAnimatorDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANIMATORDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual void Update(CGameObject* _pObj);

	afx_msg void OnBnClickedButton1();
	afx_msg void OnSetFocusAnimComb();
	afx_msg void OnKillFocusAnimComb();
	afx_msg void OnChangeAnimComb();
	afx_msg void OnSelectedAnimComb();

	bool						m_bFocusAnimComb;
	CComboBox			m_cbAnim;
	CButton m_ckRepeat;
	

	virtual void PostNcDestroy();
	afx_msg void OnBnClickedCheck1();
	
};
