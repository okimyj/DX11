
// SoMacTool.h : SoMacTool ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CSoMacToolApp:
// �� Ŭ������ ������ ���ؼ��� SoMacTool.cpp�� �����Ͻʽÿ�.
//

class CSoMacToolApp : public CWinApp
{
public:
	CSoMacToolApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnIdle(LONG lCount);
};

extern CSoMacToolApp theApp;
