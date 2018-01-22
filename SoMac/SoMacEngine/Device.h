#pragma once
#include "global.h"
class CDevice
{
	SINGLE(CDevice);
private:
	HWND			m_hWnd;				// 장치 출력 윈도우.
	bool				m_bWindow;			// 창 모드 = true, 전체화면 = false.
	// -- 이것들은 소멸자에서 반드시 Release 해줄 것.
	ID3D11Device*						m_pDevice;		// 디바이스. memory 관련.
	ID3D11DeviceContext	*			m_pContext;		// 컨텍스트. 렌더링, 출력 기능 담당.  rendering 관련.

	IDXGISwapChain*					m_pSwapChain;		// 픽셀 쉐이더 까지 끝난 결과가 그려짐. 
																			// 다중 버퍼(보통은 더블 : 1번을 앞에 보여주고 2번에 다음 프레임 장면을 그려서 번갈아 보여주는 방식.)
																			// 3중도 있긴 있는데 1프레임 이전 정보를 저장해야 할 때 사용 (모션블러 같은거 사용시?) -> 잘 안쓰고 지연 렌더링으로 대체해서 사용함.

	ID3D11RenderTargetView*		m_pTargetView;		// 렌더 타겟.
	ID3D11DepthStencilView*		m_pDepthStencilView;	// 스텐실 뷰.
	ID3D11Texture2D*					m_pDepthStencilTex;
	// DepthStencilBuffer : 3byte 는 깊이, 1byte는 Stencil 용도. 
	// 카메라에서 바라보았을 때 가려지는지 판단. 기존에 입력 되어 있는 값보다 작으면 기록.
	// 스텐실 - 영역잠금처리?.. 보통 거울이나 반사되는 물체를 그릴 때 많이 사용. 

	UINT					m_iMSLev;		// 멀티 샘플링 레벨.
	float					m_fCol[4];		// 초기화 컬러.

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
		// depth 는 3byte Depth, 1byte Stencil로 이루어짐. 클리어 할 flag를 넘겨줌. 둘다 clear 할거니까 | 연산.
	}
	void Present() { m_pSwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return m_pDevice; }
	ID3D11DeviceContext* GetContext() { return m_pContext; }
private:
	int CreateSwapChain();
	int CreateView();
};

