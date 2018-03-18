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
	tItem.hInsertAfter = TVI_SORT;		// insert 한 다음에 어떻게 할지. 
	tItem.item.pszText = const_cast<wchar_t*>(_strName.c_str());		// const_cast 어지간하면 안쓰는게 좋음. 
	tItem.item.iImage = 0;					// 아이콘 이미지.
	tItem.item.iSelectedImage = 0;
	tItem.item.mask = TVIF_TEXT;		// 문자열 데이터를 사용하겠다. TVIF_TEXT 안넣어주면 문자열 넣어줘도 표시 안됨. 

	HTREEITEM hItem = m_ctrlTree.InsertItem(&tItem);
	m_ctrlTree.SetItemData(hItem, _dwData);

	return hItem;
}

void CTreeCtrlDlg::MoveItem(HTREEITEM _hSrcItem, HTREEITEM _hDestItem)
{
	// 이동 시킬 아이템의 정보를 알아낸다.
	wchar_t arrName[255] = {};
	TV_ITEMW item = {};
	item.hItem = _hSrcItem;
	item.pszText = arrName;
	item.cchTextMax = sizeof(arrName);
	item.mask = TVIF_TEXT | TVIF_HANDLE;				// 정보 안에 텍스트 정보와, 핸들 정보를 포함시켜서 가져온다. 
	m_ctrlTree.GetItem(&item);
	DWORD_PTR dwData = m_ctrlTree.GetItemData(_hSrcItem);

	// 이동할 아이템을 새로 add.
	HTREEITEM hCopyItem = AddItem(arrName, dwData, _hDestItem);

	// 원본 아이템에 자식이 있다면 자신을 dest로 해서 재귀호출. 
	vector<HTREEITEM> vecChildren;
	GetChildren(_hSrcItem, vecChildren);
	for (UINT i = 0; i < vecChildren.size(); ++i)
	{
		MoveItem(vecChildren[i], hCopyItem);
	}
	// 원본 아이템이 열린 상태였다면 이동하는 곳에도 열린 상태로 가게끔 한다. 
	if (item.state & TVIS_EXPANDED)
	{
		m_ctrlTree.Expand(hCopyItem, TVE_EXPAND);
	}
	// 들어가는 목적지를 열어 놓는다. 
	if (NULL != _hDestItem)
	{
		m_ctrlTree.Expand(_hDestItem, TVE_EXPAND);
	}
	// 원본을 아이템 삭제.
	m_ctrlTree.DeleteItem(_hSrcItem);

	// 카피 아이템을 선택.
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
