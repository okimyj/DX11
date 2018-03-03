#pragma once
#include "afxcmn.h"
#include "ResMgr.h"

enum class RESOURCE_TYPE
{
	MESH,
	MATERIAL,
	END,
};

// CListDlg dialog
class CListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListDlg)

public:
	CListDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl					m_listCtrl;
	vector<CString>		m_vecText;
	RESOURCE_TYPE		m_eType;

public:
	void SetInitType(RESOURCE_TYPE _eType) { m_eType = _eType; }
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnOK();
	virtual void OnCancel();
	
};
