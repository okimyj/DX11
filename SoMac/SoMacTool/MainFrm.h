
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "MySplitterWnd.h"
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CMySplitterWnd m_MainSplitter;
	CMySplitterWnd m_SubSplitter;
public:
	HWND GetGameViewHwnd() { return m_SubSplitter.GetPane(1, 0)->m_hWnd; }
	CWnd* GetComponentView() { return m_MainSplitter.GetPane(0, 2); }      
	void Update();
// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);

	afx_msg void OnGameObjectEmpty();
	afx_msg void OnGameObjectRect();
	afx_msg void OnGameObjectStdAnim();

	DECLARE_MESSAGE_MAP()

};


