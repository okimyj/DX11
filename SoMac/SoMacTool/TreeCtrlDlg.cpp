#include "stdafx.h"
#include "TreeCtrlDlg.h"



CTreeCtrlDlg::CTreeCtrlDlg()
{
}

CTreeCtrlDlg::CTreeCtrlDlg(UINT nIDTemplate, CWnd * pParent)
	: CDialogEx(nIDTemplate, pParent)
{
}


CTreeCtrlDlg::~CTreeCtrlDlg()
{
}

HTREEITEM CTreeCtrlDlg::AddItem(const wstring & _strName, DWORD_PTR _dwData, HTREEITEM _hParent)
{
	TVINSERTSTRUCT tItem = {};
	tItem.hParent = _hParent;
	tItem.hInsertAfter = TVI_SORT;		// insert �� ������ ��� ����. 
	tItem.item.pszText = const_cast<wchar_t*>(_strName.c_str());		// const_cast �������ϸ� �Ⱦ��°� ����. 
	tItem.item.iImage = 0;					// ������ �̹���.
	tItem.item.iSelectedImage = 0;
	tItem.item.mask = TVIF_TEXT;		// ���ڿ� �����͸� ����ϰڴ�. TVIF_TEXT �ȳ־��ָ� ���ڿ� �־��൵ ǥ�� �ȵ�. 

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tItem);
	m_ctrlTree.SetItemData(hItem, _dwData);

	return hItem;
}

void CTreeCtrlDlg::MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// �̵� ��ų �������� ������ �˾Ƴ���.
	wchar_t arrName[255] = {};
	TV_ITEMW item = {};
	item.hItem = _hSrcItem;
	item.pszText = arrName;
	item.cchTextMax = sizeof(arrName);
	item.mask = TVIF_TEXT | TVIF_HANDLE;				// ���� �ȿ� �ؽ�Ʈ ������, �ڵ� ������ ���Խ��Ѽ� �����´�. 
	m_ctrlTree.GetItem(&item);
	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	// �̵��� �������� ���� add.
	HTREEITEM hCopyItem = AddItem(arrName, dwData, _hDestItem);

	// ���� �����ۿ� �ڽ��� �ִٸ� �ڽ��� dest�� �ؼ� ���ȣ��. 
	vector<HTREEITEM> vecChildren;
	GetChildren(_hSrcItem, vecChildren);
	for (UINT i = 0; i < vecChildren.size(); ++i)
	{
		MoveItem(vecChildren[i], hCopyItem);
	}
	// ���� �������� ���� ���¿��ٸ� �̵��ϴ� ������ ���� ���·� ���Բ� �Ѵ�. 
	if (item.state & TVIS_EXPANDED)
	{
		m_ctrlTree.Expand(hCopyItem, TVE_EXPAND);
	}
	// ���� �������� ���� ���´�. 
	if (NULL != _hDestItem)
	{
		m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
	}
	// ������ ������ ����.
	m_ctrlTree.DeleteItem(_hSrcItem);

	// ī�� �������� ����.
	m_ctrlTree.SelectItem(hCopyItem);
}

void CTreeCtrlDlg::GetChildren(HTREEITEM _hItem, vector<HTREEITEM>& _vecOut)
{
	if (!m_ctrlTree.ItemHasChildren(_hItem))
		return;

	HTREEITEM hChild = m_ctrlTree.GetChildItem(_hItem);

	while (true)
	{
		_vecOut.push_back(hChild);
		hChild = m_ctrlTree.GetNextSiblingItem(hChild);

		if (NULL == hChild)
			break;
	}

}

void CTreeCtrlDlg::DeleteChildren(HTREEITEM _hItem)
{
	if (!m_ctrlTree.ItemHasChildren(_hItem))
		return;

	HTREEITEM hChild = m_ctrlTree.GetChildItem(_hItem);
	HTREEITEM hNextChild = NULL;

	while (true)
	{
		hNextChild = m_ctrlTree.GetNextSiblingItem(hChild);
		m_ctrlTree.DeleteItem(hChild);
		hChild = hNextChild;

		if (NULL == hChild)
			break;
	}
}
