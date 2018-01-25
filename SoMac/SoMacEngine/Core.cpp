#include "Core.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"
#include "Device.h"

// ID3D11Buffer* g_pVB = NULL;		// Vertex Buffer.		GPU�� ���� ������ ���� �� �� �ִ� ����.
// ID3D11Buffer* g_pIB = NULL;			// Index Buffer.
// ID3D11InputLayout*	g_pLayout = NULL;
//-> Mesh
/*
ID3DBlob* g_pVSBlob = NULL;		// Vertext Shader Blob.
ID3DBlob* g_pPSBlob = NULL;		// Pixel Shader Blob.

ID3D11VertexShader*	g_pVS;			// Vertex Shader.
ID3D11PixelShader*		g_pPS;			// Pixel Shader.
-> Shader */

//ID3D11Buffer* g_pTransformBuffer = NULL; // Constant Buffer.
//-> Device
tTransform g_Transform;

CCore::CCore()
	: m_hWnd(NULL)
{
}


CCore::~CCore()
{
}

int CCore::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;
	if (FAILED(CDevice::GetInst()->init(_hWnd, _bWindow)))
	{
		// "" -> ��Ƽ ����Ʈ (1byte or 2byte ���)
		// L"" -> ���̵� ����Ʈ (������ 2byte ���)
		MessageBox(_hWnd, L"��ġ �ʱ�ȭ ����", L"����", MB_OK);
		return RET_FAILED;
	}
	// Manager Initialize.
	CPathMgr::Init();
	CKeyMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CResMgr::GetInst()->Init();
	CShaderMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	
	// == Create Buffer ================================
	// clear color set.
	CDevice::GetInst()->SetClearColor(100, 100, 100,1);
	//-- Create Constance Buffer -- //
	CDevice::GetInst()->CreateConstBuffer(L"Transform", sizeof(tTransform), D3D11_USAGE_DYNAMIC, 0);

	return RET_SUCCESS;
}

int CCore::run()
{
	update();

	render();
	return 0;
}

int CCore::update()
{
	CKeyMgr::GetInst()->update();
	CTimeMgr::GetInst()->update();
	CSceneMgr::GetInst()->Update();
	// View ��ȯ��� ���ϱ�
	g_Transform.matView = XMMatrixIdentity();

	// Projection ��ȯ��� ���ϱ�
	g_Transform.matProj = XMMatrixOrthographicLH(WINSIZE_X, WINSIZE_Y, 1.f, 1000.f);
	//g_Transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matProj = XMMatrixTranspose(g_Transform.matProj);



	return 0;
}

void CCore::render()
{
	CDevice::GetInst()->ClearTarget();
	CSceneMgr::GetInst()->Render();
	// �ﰢ�� �ϳ� �׸���.  (�ش� mesh�� vertex blob�� ����ȴ�.)
	// Ư�� mesh�� �׸��� shader�� ��������. shader�� ��������� layout�� ��� shader�� �ٲ� �� ���� ��� ���� ����־�� ��. 

	CDevice::GetInst()->Present();
}
