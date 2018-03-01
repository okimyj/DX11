#pragma once
#include "global.h"


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
public:
	void SetGameObject(CGameObject* _pObj);
	void UpdateComponents();
	void Update();

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};


