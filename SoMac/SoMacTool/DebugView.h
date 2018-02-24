#pragma once



// CDebugView form view

class CDebugView : public CFormView
{
	DECLARE_DYNCREATE(CDebugView)

protected:
	CDebugView();           // protected constructor used by dynamic creation
	virtual ~CDebugView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEBUGVIEW };
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
};


