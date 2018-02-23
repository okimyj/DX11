
// CaculatorDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <iostream>
using namespace std;
// CCaculatorDlg 대화 상자
class CCaculatorDlg : public CDialogEx
{
// 생성입니다.
public:
	CCaculatorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CCaculatorDlg();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CACULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	//virtual void OnOK();
	//virtual void OnCancel();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
