#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAdd2DAnimDlg dialog

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

private:
	CEdit m_editFolderPath;
	CString m_strTextureName;
	CEdit m_editAnimName;
	CButton m_cbMultiTexture;
	CEdit m_editStartIdx;
	CEdit m_editFrameNum;
	CEdit m_editLeft;
	CEdit m_editTop;
	CEdit m_editWidth;
	CEdit m_editHeight;
	CListCtrl m_listBox;

private:
	void UpdateFolderPath();
	void SetActiveControl(CEdit& _control, bool _bActive);

};
