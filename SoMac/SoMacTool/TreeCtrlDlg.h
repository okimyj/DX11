#pragma once
#include "afxdialogex.h"

class CTreeCtrlDlg :
	public CDialogEx
{
protected:
	CTreeCtrl		m_ctrlTree;
protected:
	// 문제점 : AddItem 해둔 wstring 이 바뀌어서 메모리 재할당이 일어나는 경우 
	// wstring 은 자기가 가르키는 문자열은 재할당해서 주소는 바꾸는데 이상한 값이 보여지게 된다. 
	// 그래서 이름이 바뀌는 경우에 알아채서 noti 해주어야함. 
	// HTREEITEM Tree Control 에 들어가는  Item의 handle 값. 
	// 이를 이용해서 해당 item의 자식이나 형제, 부모등을 가져올 수 있다. 
	HTREEITEM AddItem(const wstring& _strName, DWORD_PTR _dwData, HTREEITEM _hParent = NULL);
	void MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem);
	void GetChildren(HTREEITEM _hItem, vector<HTREEITEM>& _vecOut);
	void DeleteChildren(HTREEITEM _hItem);


public:
	CTreeCtrlDlg();
	CTreeCtrlDlg(UINT nIDTemplate, CWnd*pParent = NULL);
	virtual ~CTreeCtrlDlg();
};



// 창이 갱신 되는 타이밍. -> Scene 에 object가 생성, 삭제, 부모의 변경 등. -> Layer에 뭔가 변화가 있다. 