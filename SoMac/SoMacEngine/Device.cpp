#include "Device.h"



CDevice::CDevice()
	: m_hWnd(NULL), m_bWindow(false)
	, m_pDevice(NULL), m_pContext(NULL)
	, m_pSwapChain(NULL), m_pTargetView(NULL)
	, m_pDepthStencilView(NULL), m_pDepthStencilTex(NULL)
	, m_iMSLev(4), m_fCol{}
{
}


CDevice::~CDevice()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pContext);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pTargetView);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pDepthStencilTex);
}

int CDevice::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;
	m_bWindow = _bWindow;
	// ��ġ �ʱ�ȭ.
	int iFlag = 0;
	// debug ����� ���� debug flag�� �����ش�. 
#ifdef _DEBUG
		iFlag |= D3D11_CREATE_DEVICE_DEBUG;	
#endif 
	D3D_FEATURE_LEVEL eFeatureLv = (D3D_FEATURE_LEVEL)0;
	if FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, iFlag, 0, 0, D3D11_SDK_VERSION, &m_pDevice, &eFeatureLv, &m_pContext))
	{
		return RET_FAILED;
	}

	// ��Ƽ ���� üũ. ���� device�� ���� ���� ���� check.
	// ��Ƽ ���� : ������Ʈ ���� ��� �κ��� �ε巴�� ����� ��. ��輱 �ֺ� ������ �����ؼ� ����ȭ.
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iMSLev);
	if (0 > m_iMSLev)
	{
		MessageBox(_hWnd, L"�׷��� ī�� �����.", L"����", MB_OK);
		return RET_FAILED;
	}

	// ���� ü�� ����
	if (FAILED(CreateSwapChain()))
	{
		return RET_FAILED;
	}

	// RenderTargetView, DepthStencilView
	if (FAILED(CreateView()))
	{
		return RET_FAILED;
	}

	// View Port ����
	D3D11_VIEWPORT tViewPortDesc = {};

	tViewPortDesc.Width = WINSIZE_X;
	tViewPortDesc.Height = WINSIZE_Y;

	// �ּ�, �ִ� ���� ��.
	tViewPortDesc.MinDepth = 0;
	tViewPortDesc.MaxDepth = 1;

	// �»��
	tViewPortDesc.TopLeftX = 0;
	tViewPortDesc.TopLeftY = 0;

	m_pContext->RSSetViewports(1, &tViewPortDesc);


	return 0;
}

int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC tDesc = {};
	tDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// 8bit R, 8bit G, 8bit B, 8bit A.
	tDesc.BufferDesc.Width = WINSIZE_X;
	tDesc.BufferDesc.Height = WINSIZE_Y;

	tDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// ȭ�� ���ŷ�		-- 60fps.
	tDesc.BufferDesc.RefreshRate.Numerator = 60;
	tDesc.BufferDesc.RefreshRate.Denominator = 1;

	// ���� �뵵 ����
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// â��� ����
	tDesc.OutputWindow = m_hWnd;
	tDesc.Windowed = m_bWindow;

	// ��Ƽ ����	. 1�� ->  ������.
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	// ��� ���Ŀ� ���۳��� ������ �ʿ� ����
	tDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// �߰� ���� ����
	tDesc.BufferCount = 1;

	IDXGIDevice* pDXGIDevice = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIFactory* pFactory = NULL;

	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	if (FAILED(pFactory->CreateSwapChain(m_pDevice, &tDesc, &m_pSwapChain)))
	{
		return RET_FAILED;
	}
	SAFE_RELEASE(pDXGIDevice);
	SAFE_RELEASE(pAdapter);
	SAFE_RELEASE(pFactory);
	return RET_SUCCESS;
}

int CDevice::CreateView()
{
	ID3D11Texture2D*	pBackBuffer = NULL;
	// SwapChain ���� ���� �����Ǿ��ִ� ���� ���
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	SAFE_RELEASE(pBackBuffer);

	m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pTargetView);
	
	// Depth Stencil Texture
	D3D11_TEXTURE2D_DESC tDesc = {};
	tDesc.Width = WINSIZE_X;
	tDesc.Height = WINSIZE_Y;

	// MipLevel : Ư�� ĳ���Ͱ� �ָ� �ִ� ���, �ؽ����� �ػ󵵰� Ŀ���� �ǹ� ���� ������ ����ȭ�� ���ؼ� �̸� ���� �������� �ؽ��ĸ� �����δµ�, level�� 1�̸� �̸� ������� ����.
	tDesc.MipLevels = 1;		
	tDesc.ArraySize = 1;
	tDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	
	/* Usage : GPU�� System Memory �� ��Ž��� �ɼ�.
			D3D11_USAGE_DEFAULT : GPU�� ���� �б�, ���Ⱑ ������ ���ҽ�. 
			D3D11_USAGE_IMMUTABLE : GPU������ �б⸸ �Ҽ� �ִ� ���ҽ�, GUP�� ���� ��ϵ� �� ����, CPU���� ���� �� �� ����.
			D3D11_USAGE_DYNAMIC : GPU������ �б⸸, CPU������ ���⸸ ������ ���ҽ�, �����Ӵ� �ּ� 1ȸ �̻� CPU�� ���� ������Ʈ �� ���ҽ��� ����.
			D3D11_USAGE_STAGING : GPU���� CPU�� ������ ����(����)�� �� �� �ִ� ���ҽ�.
	*/
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	if (FAILED(m_pDevice->CreateTexture2D(&tDesc, 0, &m_pDepthStencilTex)))
	{
		return RET_FAILED;
	}
	// DepthStencilView�� Desc�� �� ���� �ʾƵ� ��. default ���� ���.
	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, 0, &m_pDepthStencilView)))
	{
		return RET_FAILED;
	}
	// 
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthStencilView);

	return RET_SUCCESS;
}