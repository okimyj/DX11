
// CaculatorDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <iostream>
using namespace std;
// CCaculatorDlg ��ȭ ����
class CCaculatorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCaculatorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	virtual ~CCaculatorDlg();
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CACULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.

	//virtual void OnOK();
	//virtual void OnCancel();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	afx_msg void OnBnClickedButton(UINT _id);
	CString		m_strInput;
	CEdit			m_editInput;
	afx_msg void OnBnClickedOperator(UINT _id);
	afx_msg void OnBnClinckedCalc();
	afx_msg void OnBnClickedErase();
	afx_msg void OnBnClickedClear();
	void ApplyCalc();
	
	CEdit m_editResult;
private:
	vector<UINT>			m_vecValues;
	UINT							m_curOperator;
	vector<UINT>			m_vecOperatorID;
	vector<wstring>		m_vecOperator;
	bool							m_bFirstCalc;
	bool							m_bEntered;
	UINT							m_iLastResult;
	CFont						m_bigFont;
public:
	CEdit m_editResultList;
};
