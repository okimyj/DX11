#pragma once
#include "global.h"
#include "afxwin.h"


// CComponentView form view
class CGameObject;
class CComponentDlg;
class CComponentView : public CFormView
{
	DECLARE_DYNCREATE(CComponentView)

protected:
	CComponentView();           // protected constructor used by dynamic creation
	virtual ~CComponentView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COMPONENTVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	CGameObject*		m_pTargetObj;
	CComponentDlg*	m_arrDlg[(UINT)COMPONENT_TYPE::END];
	CButton m_btAC;
	CComboBox m_cbAC;
	bool m_bACFocused;

public:
	void SetGameObject(CGameObject* _pObj, bool _bForce = false);
	void UpdateComponents();
	void Update();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnAddComponentClicked();
	
	afx_msg void OnSetFocusACCombo();
	afx_msg void OnKillFocusACCombo();
	afx_msg void OnSelchangeACCombo();
};


