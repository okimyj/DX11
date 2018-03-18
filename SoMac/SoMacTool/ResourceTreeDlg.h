#pragma once
#include "TreeCtrlDlg.h"

// CResourceTreeDlg dialog

class CResourceTreeDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CResourceTreeDlg)

public:
	CResourceTreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CResourceTreeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RESOURCETREEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	virtual BOOL OnInitDialog();
	void UpdateTreeControl();
private:
	HTREEITEM m_hMeshRoot;
	HTREEITEM m_hTextureRoot;
	HTREEITEM m_hMaterialRoot;
	HTREEITEM m_hPrefabRoot;
	HTREEITEM m_hCloneRoot;
};
