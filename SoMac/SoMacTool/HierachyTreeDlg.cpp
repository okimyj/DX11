// HierachyTreeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "HierachyTreeDlg.h"
#include "afxdialogex.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "MainFrm.h"
#include "ComponentView.h"
// CHierachyTreeDlg dialog

IMPLEMENT_DYNAMIC(CHierachyTreeDlg, CDialogEx)

CHierachyTreeDlg::CHierachyTreeDlg(CWnd* pParent /*=NULL*/)
	: CTreeCtrlDlg(IDD_HIERACHYTREEDLG, pParent)
	, m_hDragItem(NULL)
{

}

CHierachyTreeDlg::~CHierachyTreeDlg()
{
}

void CHierachyTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
}
void CHierachyTreeDlg::PostNcDestroy()
{
	delete this;
	CDialogEx::PostNcDestroy();
}

BEGIN_MESSAGE_MAP(CHierachyTreeDlg, CDialogEx)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CHierachyTreeDlg::OnSelchangedTree)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE1, &CHierachyTreeDlg::OnBeginDragTree)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CHierachyTreeDlg message handlers


BOOL CHierachyTreeDlg::OnInitDialog()
{
	CTreeCtrlDlg::OnInitDialog();

	CSceneMgr::GetInst()->SetUpdateCallback(std::bind(&CHierachyTreeDlg::UpdateTreeControl, this));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CHierachyTreeDlg::UpdateTreeControl()
{
	// ���콺 �巡�� ���̶�� return. �巡�װ� ���� �� ������ ȣ�� ���ش�.
	if (NULL != m_hDragItem)
		return;
	// Tree Control ����.
	m_ctrlTree.DeleteAllItems();
	// item�� ������ �⺻������ String�̴�. Second Data �� GameObject�� �ּҰ�.
	
	// 1. ��� GameObject �� ���´�. 
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	list<CGameObject*> listParentObjs;
	pCurScene->GetAllParentObjects(listParentObjs);
	list<CGameObject*>::iterator iter = listParentObjs.begin();

	for (; iter != listParentObjs.end(); ++iter)
	{
		AddGameObject((*iter), NULL);
	}
}

void CHierachyTreeDlg::AddGameObject(CGameObject * _pObj, HTREEITEM _pParent)
{
	HTREEITEM hItem = AddItem((_pObj)->GetTag(), (DWORD_PTR)_pObj, _pParent);
	list<CGameObject*>& listChildObj = _pObj->GetChildList();
	list<CGameObject*>::iterator iter = listChildObj.begin();
	for (; iter != listChildObj.end(); ++iter)
	{
		AddGameObject((*iter), hItem);
	}
}

void CHierachyTreeDlg::OnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (NULL != m_hDragItem)
		return;

	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	pNMTreeView->itemNew.hItem;
	CGameObject* pObj = (CGameObject*)m_ctrlTree.GetItemData(pNMTreeView->itemNew.hItem);
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	((CComponentView*)pMainFrame->GetComponentView())->SetGameObject(pObj);
	*pResult = 0;
}

void CHierachyTreeDlg::OnBeginDragTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	m_hDragItem = pNMTreeView->itemNew.hItem;
	CGameObject* pObj = (CGameObject*)m_ctrlTree.GetItemData(pNMTreeView->itemNew.hItem);
	// ���콺 �̺�Ʈ�� �����Ѵ�. 
	SetCapture();

	*pResult = 0;
}




void CHierachyTreeDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (NULL == m_hDragItem)
		return;
	
	// ��ü Screen ���� position ���� ����. 
	::ClientToScreen(m_hWnd, &point);
	// tree contrl �������� position ����.
	m_ctrlTree.ScreenToClient(&point);
	// hit test.
	m_hTargetItem = m_ctrlTree.HitTest(point);

	if (NULL != m_hTargetItem)
		m_ctrlTree.SelectDropTarget(m_hTargetItem);

	CTreeCtrlDlg::OnMouseMove(nFlags, point);
}


void CHierachyTreeDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (NULL == m_hDragItem)
		return;
	// ���콺 �̺�Ʈ ������ �����Ѵ�. 
	ReleaseCapture();

	// ���̶���Ʈ ����. 
	m_ctrlTree.SelectDropTarget(NULL);

	// �������� �ڱ� �ڽ��̰ų� �θ��� ��� x.
	if (m_hDragItem == m_hTargetItem
		|| m_hTargetItem == m_ctrlTree.GetNextItem(m_hDragItem, TVGN_PARENT))
		return;
	
	CGameObject* pDragObj = (CGameObject*)m_ctrlTree.GetItemData(m_hDragItem);
	if (NULL == m_hTargetItem)
		pDragObj->SetParent(NULL);
	else
	{
		CGameObject* pTargetObj = (CGameObject*)m_ctrlTree.GetItemData(m_hTargetItem);
		pDragObj->SetParent(pTargetObj);
	}
	MoveItem(m_hDragItem, m_hTargetItem);
	m_hDragItem = NULL;
	m_hTargetItem = NULL;
	UpdateTreeControl();
	CTreeCtrlDlg::OnLButtonUp(nFlags, point);
}
