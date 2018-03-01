#pragma once
#include "ComponentDlg.h"

// CTransformDlg dialog

class CTransformDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CTransformDlg)

public:
	CTransformDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransformDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSFORMDLG };
#endif
public:
	virtual void Update(CGameObject* _pObj);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

public:
	CEdit m_arrEdit[9];
	UINT m_iFocusedEditID;
	afx_msg void OnEnSetfocus(UINT _id);
	afx_msg void OnEnKillfocus(UINT _id);
	afx_msg void OnEnChange(UINT _id);
};
