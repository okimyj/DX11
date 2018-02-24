#pragma once



// CButtonView form view

class CButtonView : public CFormView
{
	DECLARE_DYNCREATE(CButtonView)

protected:
	CButtonView();           // protected constructor used by dynamic creation
	virtual ~CButtonView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUTTONVIEW };
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


