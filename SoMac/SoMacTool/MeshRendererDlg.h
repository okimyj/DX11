#pragma once
#include "ComponentDlg.h"
#include "afxwin.h"

// CMeshRendererDlg dialog

class CMeshRendererDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CMeshRendererDlg)

public:
	CMeshRendererDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMeshRendererDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHRENDERERDLG };
#endif
public:
	virtual void Update(CGameObject* _pObj, bool _bForce = false);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSetFocusRsTypeCombo();
	afx_msg void OnKillFocusRsTypeCombo();
	afx_msg void OnChangeRSTypeCombo();
	afx_msg void OnSelectedRSTypeCombo();
	CComboBox	m_cbRSType;
	bool				m_bFocusRSType;
	CEdit				m_editMesh;
	CEdit				m_editMtrl;
	
	
	afx_msg void OnClickedMeshBtn();
	afx_msg void OnClickedMtrlBtn();
};
