#pragma once
#include "global.h"
class CCore
{
	SINGLE(CCore);
private:
	HWND m_hWnd;
public:
	int init(HWND _hWnd, bool _bWindow);
	int run();

private:
	int update();
	void render();

};

