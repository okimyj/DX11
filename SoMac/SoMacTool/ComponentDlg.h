#pragma once
#include "afxdialogex.h"
class CGameObject;
class CComponentDlg :
	public CDialogEx
{
protected:
	CGameObject*		m_pTargetObj;
	wchar_t*				m_pName;
public:
	virtual void Update(CGameObject* _pObj, bool _bForce = false) = 0;
	const wchar_t* GetName() { return m_pName; }

protected:
	void SetFocusGameView();

public:
	void InitTarget() { m_pTargetObj = NULL; }
	CComponentDlg();
	CComponentDlg(UINT nIDTemplate, CWnd* pParent = NULL);
	virtual ~CComponentDlg();
	virtual void OnOK();
	virtual void OnCancel();
};



