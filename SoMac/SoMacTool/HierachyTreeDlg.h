#pragma once
#include "TreeCtrlDlg.h"
#include "afxcmn.h"

// CHierachyTreeDlg dialog
class CGameObject;
class CHierachyTreeDlg : public CTreeCtrlDlg
{
	DECLARE_DYNAMIC(CHierachyTreeDlg)

public:
	CHierachyTreeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CHierachyTreeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERACHYTREEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();

private:
	HTREEITEM		m_hDragItem;
	HTREEITEM		m_hTargetItem;
private:
	void AddGameObject(CGameObject* _pObj, HTREEITEM _pParent);
public:
	virtual BOOL OnInitDialog();
	void UpdateTreeControl();
	afx_msg void OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBeginDragTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
