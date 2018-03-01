#pragma once
#include "ComponentDlg.h"

// CMeshRendererDlg dialog

class CMeshRendererDlg : public CComponentDlg
{
	DECLARE_DYNAMIC(CMeshRendererDlg)

public:
	CMeshRendererDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMeshRendererDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESHRENDERERDLG };
#endif
public:
	virtual void Update(CGameObject* _pObj);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
};
