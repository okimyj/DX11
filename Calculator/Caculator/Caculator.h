
// Caculator.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CCaculatorApp:
// �� Ŭ������ ������ ���ؼ��� Caculator.cpp�� �����Ͻʽÿ�.
//

class CCaculatorApp : public CWinApp
{
public:
	CCaculatorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CCaculatorApp theApp;