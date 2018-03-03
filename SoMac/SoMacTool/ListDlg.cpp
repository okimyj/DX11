// ListDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "ListDlg.h"
#include "afxdialogex.h"
#include "Mesh.h"
#include "Material.h"

// CListDlg dialog

IMPLEMENT_DYNAMIC(CListDlg, CDialogEx)

CListDlg::CListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LISTDLG, pParent)
{

}

CListDlg::~CListDlg()
{

}

void CListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CListDlg, CDialogEx)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CListDlg::OnNMDblclkList)
END_MESSAGE_MAP()


// CListDlg message handlers

BOOL CListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	if (RESOURCE_TYPE::MESH == m_eType)
	{
		map<wstring, CResPtr<CMesh>>& mapMesh = CResMgr::GetInst()->GetMeshMap();
		map<wstring, CResPtr<CMesh>>::iterator iter = mapMesh.begin();
		// mesh �̸����� �̸� �־���ڰ� ���� vector �ε� vector �� ����� ��ġ�� ���Ҵ��� �ϹǷ� �� �޸� �ּҰ� �ٲ��. 
		// �׷��ϱ� ���Ҵ��� �Ͼ�� �ʵ��� �̸� reserve�� �س��´�.
		m_vecText.reserve(mapMesh.size());
		for (int i = 0; iter != mapMesh.end(); ++iter, ++i)
		{
			m_vecText.push_back(iter->first.c_str());
			LVITEM tItem = {};
			tItem.iItem = i;			// item index.
			tItem.pszText = m_vecText[i].GetBuffer();
			// ok ��ư�� ������ �� �ٷ� �ش� �������� lParam ���� �ּҰ��� ���� �� �ֵ���.
			CRes* pRes = iter->second;
			tItem.lParam = (LPARAM)pRes;
			tItem.mask = LVIF_TEXT | LVIF_PARAM;

			m_listCtrl.InsertItem(&tItem);
		}
	}
	else if (RESOURCE_TYPE::MATERIAL == m_eType)
	{
		map<wstring, CResPtr<CMaterial>>& mapMaterial = CResMgr::GetInst()->GetMaterialMap();
		map<wstring, CResPtr<CMaterial>>::iterator iter = mapMaterial.begin();
		m_vecText.reserve(mapMaterial.size());
		for (int i = 0; iter != mapMaterial.end(); ++iter, ++i) 
		{
			m_vecText.push_back(iter->first.c_str());
			LVITEM tItem = {};
			tItem.iItem = i;
			tItem.pszText = m_vecText[i].GetBuffer();
			CRes* pRes = iter->second;
			tItem.lParam = (LPARAM)pRes;
			tItem.mask = LVIF_TEXT | LVIF_PARAM;
			m_listCtrl.InsertItem(&tItem);
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CListDlg::OnNMDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	OnOK();
	*pResult = 0;
}

void CListDlg::OnOK()
{
	int iIdx = m_listCtrl.GetSelectionMark();
	if (-1 == iIdx)
	{
		// �ƹ��͵� ���� ���� ����.
		EndDialog(NULL);
	}
	else
	{
		LPARAM lp = m_listCtrl.GetItemData(iIdx);
		EndDialog(lp);
		//CDialogEx::OnOK();
	}
	
}


void CListDlg::OnCancel()
{
	EndDialog(NULL);
	//CDialogEx::OnCancel();
	// OnOK �� OnCancel �̳� �Ѵ� �ȿ��� ON_OK �ΰ� ���� �� int �� �Ѱ���. �̷��� �ص� �Ȱ�.
}
