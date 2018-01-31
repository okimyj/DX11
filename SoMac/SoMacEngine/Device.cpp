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
	map<wstring, CBUFFER>::iterator iter = m_mapConstBuffer.begin();
	for (; iter != m_mapConstBuffer.end(); ++iter)
	{
		SAFE_RELEASE(iter->second.pBuffer);
	}
	for (int i = 0; i < (UINT)RASTERIZE_TYPE::END; ++i)
	{
		SAFE_RELEASE(m_arrRasterizer[i]);
	}
}

int CDevice::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;
	m_bWindow = _bWindow;
	// 장치 초기화.
	int iFlag = 0;
	// debug 모드일 때만 debug flag를 더해준다. 
#ifdef _DEBUG
		iFlag |= D3D11_CREATE_DEVICE_DEBUG;	
#endif 
	D3D_FEATURE_LEVEL eFeatureLv = (D3D_FEATURE_LEVEL)0;
	if FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, iFlag, 0, 0, D3D11_SDK_VERSION, &m_pDevice, &eFeatureLv, &m_pContext))
	{
		return RET_FAILED;
	}

	// 멀티 샘플 체크. 현재 device의 지원 가능 수준 check.
	// 멀티 샘플 : 오브젝트 간의 경계 부분을 부드럽게 만드는 것. 경계선 주변 색상을 추출해서 평준화.
	m_pDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m_iMSLev);
	if (0 > m_iMSLev)
	{
		MessageBox(_hWnd, L"그래픽 카드 노노해.", L"실패", MB_OK);
		return RET_FAILED;
	}

	// 스왚 체인 생성
	if (FAILED(CreateSwapChain()))
	{
		return RET_FAILED;
	}

	// RenderTargetView, DepthStencilView
	if (FAILED(CreateView()))
	{
		return RET_FAILED;
	}

	// View Port 설정
	D3D11_VIEWPORT tViewPortDesc = {};

	tViewPortDesc.Width = WINSIZE_X;
	tViewPortDesc.Height = WINSIZE_Y;

	// 최소, 최대 깊이 값.
	tViewPortDesc.MinDepth = 0;
	tViewPortDesc.MaxDepth = 1;

	// 좌상단
	tViewPortDesc.TopLeftX = 0;
	tViewPortDesc.TopLeftY = 0;

	m_pContext->RSSetViewports(1, &tViewPortDesc);

	CreateRasterizerState();
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

	// 화면 갱신률		-- 60fps.
	tDesc.BufferDesc.RefreshRate.Numerator = 60;
	tDesc.BufferDesc.RefreshRate.Denominator = 1;

	// 버퍼 용도 지정
	tDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 창모드 설정
	tDesc.OutputWindow = m_hWnd;
	tDesc.Windowed = m_bWindow;

	// 멀티 샘플	. 1개 ->  사용안함.
	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;

	// 출력 이후에 버퍼내용 저장할 필요 없음
	tDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 추가 버퍼 개수
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
	// SwapChain 으로 부터 생성되어있는 버퍼 얻기
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	SAFE_RELEASE(pBackBuffer);

	m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pTargetView);
	
	// Depth Stencil Texture
	D3D11_TEXTURE2D_DESC tDesc = {};
	tDesc.Width = WINSIZE_X;
	tDesc.Height = WINSIZE_Y;

	// MipLevel : 특정 캐릭터가 멀리 있는 경우, 텍스쳐의 해상도가 커봐야 의미 없기 때문에 최적화를 위해서 미리 작은 사이즈의 텍스쳐를 만들어두는데, level이 1이면 이를 사용하지 않음.
	tDesc.MipLevels = 1;		
	tDesc.ArraySize = 1;
	tDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	tDesc.SampleDesc.Count = 1;
	tDesc.SampleDesc.Quality = 0;
	
	/* Usage : GPU와 System Memory 간 통신시의 옵션.
			D3D11_USAGE_DEFAULT : GPU에 의한 읽기, 쓰기가 가능한 리소스. 
			D3D11_USAGE_IMMUTABLE : GPU에서만 읽기만 할수 있는 리소스, GUP에 의해 기록될 수 없고, CPU에서 접근 할 수 없다.
			D3D11_USAGE_DYNAMIC : GPU에서는 읽기만, CPU에서는 쓰기만 가능한 리소스, 프레임당 최소 1회 이상 CPU에 의해 업데이트 될 리소스에 적합.
			D3D11_USAGE_STAGING : GPU에서 CPU로 데이터 전송(복사)를 할 수 있는 리소스.
	*/
	tDesc.Usage = D3D11_USAGE_DEFAULT;
	tDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	if (FAILED(m_pDevice->CreateTexture2D(&tDesc, 0, &m_pDepthStencilTex)))
	{
		return RET_FAILED;
	}
	// DepthStencilView의 Desc는 꼭 넣지 않아도 됨. default 설정 사용.
	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilTex, 0, &m_pDepthStencilView)))
	{
		return RET_FAILED;
	}
	// 
	m_pContext->OMSetRenderTargets(1, &m_pTargetView, m_pDepthStencilView);

	return RET_SUCCESS;
}

int CDevice::CreateRasterizerState()
{
	// default rasterizer. null 이면 기본 값 사용하니 null로 채워버림.
	m_arrRasterizer[(UINT)RASTERIZE_TYPE::BACK] = NULL;
	D3D11_RASTERIZER_DESC tDesc = {};
	tDesc.FillMode = D3D11_FILL_WIREFRAME;
	tDesc.CullMode = D3D11_CULL_NONE;
	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::WIRE]);

	tDesc.FillMode = D3D11_FILL_SOLID;
	tDesc.CullMode = D3D11_CULL_FRONT;
	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::FRONT]);
	
	tDesc.FillMode = D3D11_FILL_SOLID;
	tDesc.CullMode = D3D11_CULL_NONE;
	m_pDevice->CreateRasterizerState(&tDesc, &m_arrRasterizer[(UINT)RASTERIZE_TYPE::NONE]);
	return 0;
}


int CDevice::CreateConstBuffer(const wstring & _strKey, UINT _iSize, D3D11_USAGE _eUsage, UINT _iRegister)
{
	CBUFFER tBuffer = {};

	// Create Constant Buffer .
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = _iSize;
	tBufferDesc.Usage = _eUsage;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (D3D11_USAGE_DYNAMIC == tBufferDesc.Usage)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, NULL, &tBuffer.pBuffer)))
	{
		return RET_FAILED;
	}
	tBuffer.iRegister = _iRegister;
	tBuffer.iSize = _iSize;
	m_mapConstBuffer.insert(make_pair(_strKey, tBuffer));
}

CBUFFER * CDevice::FindConstBuffer(const wstring & _strKey)
{
	map<wstring, CBUFFER>::iterator iter = m_mapConstBuffer.find(_strKey);
	if (iter == m_mapConstBuffer.end())
		return NULL;

	return &iter->second;
}