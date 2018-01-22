#pragma once
#include "global.h"
class CDevice
{
	SINGLE(CDevice);
private:
	HWND			m_hWnd;				// ��ġ ��� ������.
	bool				m_bWindow;			// â ��� = true, ��üȭ�� = false.
	// -- �̰͵��� �Ҹ��ڿ��� �ݵ�� Release ���� ��.
	ID3D11Device*						m_pDevice;		// ����̽�. memory ����.
	ID3D11DeviceContext	*			m_pContext;		// ���ؽ�Ʈ. ������, ��� ��� ���.  rendering ����.

	IDXGISwapChain*					m_pSwapChain;		// �ȼ� ���̴� ���� ���� ����� �׷���. 
																			// ���� ����(������ ���� : 1���� �տ� �����ְ� 2���� ���� ������ ����� �׷��� ������ �����ִ� ���.)
																			// 3�ߵ� �ֱ� �ִµ� 1������ ���� ������ �����ؾ� �� �� ��� (��Ǻ� ������ ����?) -> �� �Ⱦ��� ���� ���������� ��ü�ؼ� �����.

	ID3D11RenderTargetView*		m_pTargetView;		// ���� Ÿ��.
	ID3D11DepthStencilView*		m_pDepthStencilView;	// ���ٽ� ��.
	ID3D11Texture2D*					m_pDepthStencilTex;
	// DepthStencilBuffer : 3byte �� ����, 1byte�� Stencil �뵵. 
	// ī�޶󿡼� �ٶ󺸾��� �� ���������� �Ǵ�. ������ �Է� �Ǿ� �ִ� ������ ������ ���.
	// ���ٽ� - �������ó��?.. ���� �ſ��̳� �ݻ�Ǵ� ��ü�� �׸� �� ���� ���. 

	UINT					m_iMSLev;		// ��Ƽ ���ø� ����.
	float					m_fCol[4];		// �ʱ�ȭ �÷�.

public:
	int init(HWND _hWnd, bool _bWindow);
	
	void SetClearColor(float _fCol[4]) { memcpy(m_fCol, _fCol, sizeof(float) * 4); }
	
	void SetClearColor(int R, int G, int B, int A) 
	{
		float fCol[4] = { R / 255.f, G / 255.f , B / 255.f , A / 255.f };
		SetClearColor(fCol);
	}
	
	void ClearTarget()
	{
		m_pContext->ClearRenderTargetView(m_pTargetView, m_fCol);
		m_pContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		// depth �� 3byte Depth, 1byte Stencil�� �̷����. Ŭ���� �� flag�� �Ѱ���. �Ѵ� clear �ҰŴϱ� | ����.
	}
	void Present() { m_pSwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }
private:
	int CreateSwapChain();
	int CreateView();
};

