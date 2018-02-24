
// CaculatorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "Caculator.h"
#include "CaculatorDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCaculatorDlg ��ȭ ����
CCaculatorDlg::CCaculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CACULATOR_DIALOG, pParent)
	, m_strInput(_T(""))
	, m_bEntered(true)
	, m_bFirstCalc(true)
	, m_iLastResult(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCaculatorDlg::~CCaculatorDlg()
{
}

void CCaculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strInput);
	DDX_Control(pDX, IDC_EDIT1, m_editInput);
	DDX_Control(pDX, IDC_EDIT2, m_editResult);
	DDX_Control(pDX, IDC_EDIT3, m_editResultList);
}

//void CCaculatorDlg::OnOK()
//{
//	
//}
//
//void CCaculatorDlg::OnCancel()
//{
//	//::EndDialog(m_hWnd, IDCANCEL);
//	//EndDialog(IDCANCEL);
//	CDialog::OnCancel();
//}

BEGIN_MESSAGE_MAP(CCaculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON0, IDC_BUTTON9, &CCaculatorDlg::OnBnClickedButton)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_PLUS, IDC_BUTTON_DIVISION, &CCaculatorDlg::OnBnClickedOperator)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CCaculatorDlg::OnBnClinckedCalc)
	ON_BN_CLICKED(IDC_BUTTON_ERASE, &CCaculatorDlg::OnBnClickedErase)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCaculatorDlg::OnBnClickedClear)
	
END_MESSAGE_MAP()


// CCaculatorDlg �޽��� ó����
BOOL CCaculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	m_editInput.SetWindowTextW(L"0");
	
	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CCaculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CCaculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CCaculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCaculatorDlg::OnOK()
{
}

void CCaculatorDlg::OnBnClickedButton(UINT _id)
{	
	UINT iNum = _id - 2000;
	
	CString str;
	m_editInput.GetWindowTextW(str);
	
	int iOuput = _wtoi(str.GetBuffer());	
	iOuput *= 10;
	if (!m_bEntered)
	{
		str.Format(L"%d", iNum);
	}
	else
	{
		iOuput += iNum;
		str.Format(L"%d", iOuput);
	}
	m_bEntered = true;
	m_editInput.SetWindowTextW(str);
}

//void CCaculatorDlg::OnBnClickedButton1()
//{
//	// ::SetDlgItemText(m_hWnd, IDC_EDIT1, L"1");
//	// m_strOutput = L"1";
//	// UpdateData(false); // true ���� ����, false ���� ����	
//
//	m_editInput.SetWindowTextW(L"1");
//}


void CCaculatorDlg::OnBnClickedOperator(UINT _id)
{
	m_curOperator = _id;
	if (!m_bEntered)
	{

	}
	ApplyCalc();

	CString str;
	str.Format(L"%d", m_iLastResult);
	m_editInput.SetWindowTextW(str);
}

void CCaculatorDlg::ApplyCalc()
{
	
	CString str;
	m_editInput.GetWindowTextW(str);
	int iInput = _wtoi(str.GetBuffer());
	m_editResult.GetWindowTextW(str);
	switch (m_curOperator)
	{
	case IDC_BUTTON_PLUS:
		m_iLastResult += iInput;
		str.Format(L"%s%d%s", str, iInput, L"+");
		break;
	case IDC_BUTTON_SUB:
		m_iLastResult -= iInput;
		str.Format(L"%s%d%s", str, iInput, L"-");
		break;
	case IDC_BUTTON_MULTIPLY:
		m_iLastResult = m_bFirstCalc ? iInput : m_iLastResult * iInput;
		str.Format(L"%s%d%s", str, iInput, L"*");
		break;
	case IDC_BUTTON_DIVISION:
		m_iLastResult = m_bFirstCalc ? iInput : m_iLastResult / iInput;
		str.Format(L"%s%d%s", str, iInput, L"/");
		break;
	}
	m_bFirstCalc = false;
	m_bEntered = false;
	m_editResult.SetWindowTextW(str);
}

void CCaculatorDlg::OnBnClinckedCalc()
{
	ApplyCalc();
	
	CString strResult;
	strResult.Format(L"%d", m_iLastResult);
	m_editInput.SetWindowTextW(strResult);
		
	CString str;
	m_editResultList.GetWindowTextW(str);
	wstring addString = str;
	m_editResult.GetWindowTextW(str);
	str.Delete(str.GetLength() - 1, 1);
	addString += str + L"="+ strResult + "\r\n";
	m_editResultList.SetWindowTextW(addString.c_str());
	
	m_editResult.SetWindowTextW(L"");
	m_iLastResult = 0;
	m_bFirstCalc = true;
}


void CCaculatorDlg::OnBnClickedErase()
{
	CString str;
	m_editInput.GetWindowTextW(str);
	str.Delete(str.GetLength()-1, 1);
	if (str == L"")
		str = L"0";
	m_editInput.SetWindowTextW(str);
}

void CCaculatorDlg::OnBnClickedClear()
{
	m_editInput.SetWindowTextW(L"0");
	m_editResult.SetWindowTextW(L"");
	m_iLastResult = 0;
	m_bEntered = false;
	m_bFirstCalc = true;
}

