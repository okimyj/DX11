#pragma once
#include "afxdialogex.h"
class CGameObject;
class CComponentDlg :
	public CDialogEx
{
protected:
	CGameObject*		m_pTargetObj;
public:
	virtual void Update(CGameObject* _pObj) = 0;
protected:
	void SetFocusGameView();
public:
	CComponentDlg();
	CComponentDlg(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CComponentDlg();
	virtual void OnOK();
	virtual void OnCancel();
};



