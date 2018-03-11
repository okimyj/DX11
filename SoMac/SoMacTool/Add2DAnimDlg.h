#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAdd2DAnimDlg dialog
class CGameObject;
class CAdd2DAnimDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAdd2DAnimDlg)

public:
	CAdd2DAnimDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAdd2DAnimDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADD2DANIMDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedMultiTextureCheckBtn();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedSelectPathButton();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	void SetTargetObject(CGameObject* _pObj) { m_pTargetObj = _pObj; }
private:
	CGameObject	*	m_pTargetObj;
	CEdit m_editFolderPath;
	CEdit m_editTextureName;
	CEdit m_editAnimName;
	CButton m_cbMultiTexture;
	CEdit m_editStartIdx;
	CEdit m_editFrameNum;
	CEdit m_editLeft;
	CEdit m_editTop;
	CEdit m_editWidth;
	CEdit m_editHeight;
	CListCtrl m_listBox;
	bool m_bFocusPathEdit;

private:
	void UpdateFolderPath();
	void SetActiveControl(CEdit& _control, bool _bActive);

public:
	afx_msg void OnSetfocusPathEdit();
	afx_msg void OnKillfocusPathEdit();
	afx_msg void OnClickedAdd();
	afx_msg void OnClickedAppend();
};
