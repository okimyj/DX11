#pragma once
#include "afxdialogex.h"

class CTreeCtrlDlg :
	public CDialogEx
{
protected:
	CTreeCtrl		m_ctrlTree;
protected:
	// ������ : AddItem �ص� wstring �� �ٲ� �޸� ���Ҵ��� �Ͼ�� ��� 
	// wstring �� �ڱⰡ ����Ű�� ���ڿ��� ���Ҵ��ؼ� �ּҴ� �ٲٴµ� �̻��� ���� �������� �ȴ�. 
	// �׷��� �̸��� �ٲ�� ��쿡 �˾�ä�� noti ���־����. 
	// HTREEITEM Tree Control �� ����  Item�� handle ��. 
	// �̸� �̿��ؼ� �ش� item�� �ڽ��̳� ����, �θ���� ������ �� �ִ�. 
	HTREEITEM AddItem(const wstring& _strName, DWORD_PTR _dwData, HTREEITEM _hParent = NULL);
	void MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem);
	void GetChildren(HTREEITEM _hItem, vector<HTREEITEM>& _vecOut);
	void DeleteChildren(HTREEITEM _hItem);


public:
	CTreeCtrlDlg();
	CTreeCtrlDlg(UINT nIDTemplate, CWnd*pParent = NULL);
	virtual ~CTreeCtrlDlg();
};



// â�� ���� �Ǵ� Ÿ�̹�. -> Scene �� object�� ����, ����, �θ��� ���� ��. -> Layer�� ���� ��ȭ�� �ִ�. 