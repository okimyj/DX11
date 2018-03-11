#pragma once
#include "ComponentDlg.h"
#include "afxwin.h"


// CColliderDlg dialog

class CColliderDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CColliderDlg)

public:
	CColliderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColliderDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COLLIDERDLG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual void Update(CGameObject* _pObj, bool _bForce = false);
	virtual void PostNcDestroy();
	virtual void OnOK();

	CEdit			m_arrEdit[6];
	UINT			m_iFocusedEditID;
	CButton		m_ckbApplyScale;

	afx_msg void OnEnSetfocus(UINT _id);
	afx_msg void OnEnKillfocus(UINT _id);
	afx_msg void OnEnChange(UINT _id);
	afx_msg void OnClickedApplyScale();
};
