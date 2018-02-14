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
bool g_bShowCollider = true;
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
	CreateConstBuffer();
	// Manager Initialize.
	CPathMgr::Init();
	CKeyMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CShaderMgr::GetInst()->Init();
	CResMgr::GetInst()->Init();
	CSceneMgr::GetInst()->Init();
	
	
	
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

void CCore::CreateConstBuffer()
{
	// == Create Buffer ================================
	// clear color set.
	CDevice::GetInst()->SetClearColor(100, 100, 100, 1);
	//-- Create Constance Buffer -- //
	CDevice::GetInst()->CreateConstBuffer(L"Transform", sizeof(tTransform), D3D11_USAGE_DYNAMIC, 0);
	// == Create Int Buffer ======
	CDevice::GetInst()->CreateConstBuffer(g_SPName[(UINT)SHADER_PARAM::INT_END]
		, sizeof(int) * ((UINT)SHADER_PARAM::INT_END - (UINT)SHADER_PARAM::INT_0)
		, D3D11_USAGE_DYNAMIC, g_SPRegister[(UINT)SHADER_PARAM::INT_END]);
	// == Create Float Buffer ======
	CDevice::GetInst()->CreateConstBuffer(g_SPName[(UINT)SHADER_PARAM::FLOAT_END]
		, sizeof(float) * ((UINT)SHADER_PARAM::FLOAT_END - (UINT)SHADER_PARAM::FLOAT_0)
		, D3D11_USAGE_DYNAMIC, g_SPRegister[(UINT)SHADER_PARAM::FLOAT_END]);
	// == Create Vec4 Buffer ======
	CDevice::GetInst()->CreateConstBuffer(g_SPName[(UINT)SHADER_PARAM::VEC4_END]
		, sizeof(Vec4) * ((UINT)SHADER_PARAM::VEC4_END - (UINT)SHADER_PARAM::VEC4_0)
		, D3D11_USAGE_DYNAMIC, g_SPRegister[(UINT)SHADER_PARAM::VEC4_END]);
}
