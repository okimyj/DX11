// Add2DAnimDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoMacTool.h"
#include "Add2DAnimDlg.h"
#include "afxdialogex.h"
#include "PathMgr.h"
#include "GameObject.h"
#include "Animator.h"

// CAdd2DAnimDlg dialog

IMPLEMENT_DYNAMIC(CAdd2DAnimDlg, CDialogEx)

CAdd2DAnimDlg::CAdd2DAnimDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD2DANIMDLG, pParent)
{

}

CAdd2DAnimDlg::~CAdd2DAnimDlg()
{
}

void CAdd2DAnimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editFolderPath);
	DDX_Control(pDX, IDC_EDIT4, m_editAnimName);
	DDX_Control(pDX, IDC_CHECK1, m_cbMultiTexture);
	DDX_Control(pDX, IDC_EDIT5, m_editStartIdx);
	DDX_Control(pDX, IDC_EDIT6, m_editFrameNum);
	DDX_Control(pDX, IDC_EDIT7, m_editLeft);
	DDX_Control(pDX, IDC_EDIT8, m_editTop);
	DDX_Control(pDX, IDC_EDIT9, m_editWidth);
	DDX_Control(pDX, IDC_EDIT10, m_editHeight);
	DDX_Control(pDX, IDC_LIST4, m_listBox);
	DDX_Control(pDX, IDC_EDIT3, m_editTextureName);
}


BEGIN_MESSAGE_MAP(CAdd2DAnimDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAdd2DAnimDlg::OnClickedSelectPathButton)
	ON_BN_CLICKED(IDC_CHECK1, &CAdd2DAnimDlg::OnClickedMultiTextureCheckBtn)
	ON_NOTIFY(NM_CLICK, IDC_LIST4, &CAdd2DAnimDlg::OnNMClickList)
	ON_EN_SETFOCUS(IDC_EDIT1, &CAdd2DAnimDlg::OnSetfocusPathEdit)
	ON_EN_KILLFOCUS(IDC_EDIT1, &CAdd2DAnimDlg::OnKillfocusPathEdit)
	ON_BN_CLICKED(IDOK, &CAdd2DAnimDlg::OnClickedCreate)
END_MESSAGE_MAP()


// CAdd2DAnimDlg message handlers
BOOL CAdd2DAnimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString strFolderInitPath = CPathMgr::GetResourcePath();
	strFolderInitPath += L"Texture\\Animation";
	m_editFolderPath.SetWindowTextW(strFolderInitPath);
	OnClickedMultiTextureCheckBtn();
	UpdateFolderPath();
	return TRUE;
}

void CAdd2DAnimDlg::OnOK()
{
	if (m_bFocusPathEdit)
	{
		UpdateFolderPath();
	}
}


// CAddAnimDlg message handlers
int CALLBACK Proc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if (uMsg == BFFM_INITIALIZED)
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	return 0;
}

void CAdd2DAnimDlg::OnClickedSelectPathButton()
{
	BROWSEINFO br = {};
	br.lpfn = Proc;
	CString strFolderInitPath;
	m_editFolderPath.GetWindowTextW(strFolderInitPath);
	br.lParam = (LPARAM)strFolderInitPath.GetBuffer();
	br.ulFlags = BIF_USENEWUI;
	br.hwndOwner = m_hWnd;
	br.lpszTitle = L"Select Folder Path";
	LPITEMIDLIST pidl = NULL;
	if ((pidl = SHBrowseForFolder(&br)) != NULL)
	{
		wchar_t buffer[MAX_PATH];
		if (SHGetPathFromIDList(pidl, buffer))
		{
			strFolderInitPath = buffer;
			m_editFolderPath.SetWindowTextW(strFolderInitPath);
		}
	}
	UpdateFolderPath();
}


void CAdd2DAnimDlg::UpdateFolderPath()
{
	CString strFolderInitPath;
	m_editFolderPath.GetWindowTextW(strFolderInitPath);
	WIN32_FIND_DATA tData = {};
	HANDLE hHandle = FindFirstFile(wstring(strFolderInitPath + L"//" + "*.*").c_str(), &tData);
	m_listBox.DeleteAllItems();
	int iIdx = 0;
	do {
		CString strEXT = CPathMgr::GetExtension(tData.cFileName);
		if (strEXT != L".png" && strEXT != L".PNG" && strEXT != L".jpg" && strEXT != L".JPG" && strEXT != L".jpeg" && strEXT != L".JPEG" && strEXT != L".bmp" && strEXT != L".BMP")
			continue;
		m_listBox.InsertItem(iIdx++, tData.cFileName);
	} while (FindNextFile(hHandle, &tData));
}

void CAdd2DAnimDlg::SetActiveControl(CEdit& _control, bool _bActive)
{
	_control.SendMessage(EM_SETREADONLY, _bActive ? 0 : 1, 0);
}

void CAdd2DAnimDlg::OnClickedMultiTextureCheckBtn()
{
	int iCheck = m_cbMultiTexture.GetCheck();
	
	// active
	SetActiveControl(m_editStartIdx, iCheck);
	SetActiveControl(m_editTextureName, iCheck);
	// inactive
	SetActiveControl(m_editLeft, !iCheck);
	SetActiveControl(m_editTop, !iCheck);
	SetActiveControl(m_editWidth, !iCheck);
	SetActiveControl(m_editHeight, !iCheck);
//	SetActiveControl(m_editFrameNum, !iCheck);
	
}

void CAdd2DAnimDlg::OnNMClickList(NMHDR * pNMHDR, LRESULT * pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	int iIdx = m_listBox.GetSelectionMark();
	if (-1 != iIdx)
	{
		m_editTextureName.SetWindowTextW(m_listBox.GetItemText(iIdx, 0));
	}
	*pResult = 0;
}


void CAdd2DAnimDlg::OnSetfocusPathEdit()
{
	m_bFocusPathEdit = true;
}


void CAdd2DAnimDlg::OnKillfocusPathEdit()
{
	m_bFocusPathEdit = false;
}


void CAdd2DAnimDlg::OnClickedCreate()
{
	CString strFolderPath;
	m_editFolderPath.GetWindowTextW(strFolderPath);
	wstring strFilePath = strFolderPath + L"\\desc.txt";
	FILE* pFile = NULL;
	_wfopen_s(&pFile, strFilePath.c_str(), L"a+, ccs=UNICODE");
	CString str;
	CString strAnimName;
	CString writeStr;
	int iMultiTexture = m_cbMultiTexture.GetCheck();
	writeStr = L"\n[ANIMATION]\n";
	str.Format(L"%d", iMultiTexture);
	writeStr += str + L"\n";
	m_editTextureName.GetWindowTextW(str);
	writeStr += str + L"\n";
	m_editAnimName.GetWindowTextW(strAnimName);
	writeStr += strAnimName + L"\n";
	if (iMultiTexture)
	{
		m_editStartIdx.GetWindowTextW(str);
		writeStr += str + L"\n";
	}
	else
	{
		m_editLeft.GetWindowTextW(str);
		writeStr += str + L" ";
		m_editTop.GetWindowTextW(str);
		writeStr += str + L"\n";
		m_editWidth.GetWindowTextW(str);
		writeStr += str + L" ";
		m_editHeight.GetWindowTextW(str);
		writeStr += str + L"\n";
	}
	m_editFrameNum.GetWindowTextW(str);
	writeStr += str + L"\n";
	fwprintf_s(pFile, writeStr.GetBuffer());
	fclose(pFile);
	if (NULL != m_pTargetObj)
	{
		CString resourcePath = CPathMgr::GetResourcePath();
		resourcePath = strFolderPath.Mid(resourcePath.GetLength(), strFolderPath.GetLength());
		CAnimator* pAnimator = m_pTargetObj->GetAnimator();
		pAnimator->LoadAnimation2D(strAnimName.GetBuffer(), resourcePath.GetBuffer());
	}
	CDialogEx::OnOK();
}
