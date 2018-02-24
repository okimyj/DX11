#pragma once



// CHierachyView form view

class CHierachyView : public CFormView
{
	DECLARE_DYNCREATE(CHierachyView)

protected:
	CHierachyView();           // protected constructor used by dynamic creation
	virtual ~CHierachyView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HIERACHYVIEW };
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


