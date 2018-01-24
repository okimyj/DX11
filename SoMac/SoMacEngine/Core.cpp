#include "Core.h"
#include "PathMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "Device.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRender.h"


#include "Mesh.h"
#include "Shader.h"

// ID3D11Buffer* g_pVB = NULL;		// Vertex Buffer.		GPU에 정점 정보를 전달 할 수 있는 버퍼.
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

// player 의 월드 상태정보
XMFLOAT3	g_vPos = XMFLOAT3(0.f, 0.f, 100.f);
XMFLOAT3	g_vScale = XMFLOAT3(100.f, 100.f, 100.f);
XMFLOAT3	g_vRot = XMFLOAT3(0.f, 0.f, 0.f);

// GameObjcet
CGameObject* g_pObj = NULL;
CMesh* g_pMesh = NULL;
CCore::CCore()
	: m_hWnd(NULL)
{
}


CCore::~CCore()
{
	SAFE_DELETE(g_pObj);
	SAFE_DELETE(g_pMesh);
}

int CCore::init(HWND _hWnd, bool _bWindow)
{
	m_hWnd = _hWnd;
	if (FAILED(CDevice::GetInst()->init(_hWnd, _bWindow)))
	{
		// "" -> 멀티 바이트 (1byte or 2byte 사용)
		// L"" -> 와이드 바이트 (무조건 2byte 사용)
		MessageBox(_hWnd, L"장치 초기화 실패", L"실패", MB_OK);
		return RET_FAILED;
	}
	// Manager Initialize.
	CPathMgr::Init();
	CKeyMgr::GetInst()->Init();
	CTimeMgr::GetInst()->Init();
	CResMgr::GetInst()->Init();
	CShaderMgr::GetInst()->Init();
	
	// == Create Buffer ================================
	// clear color set.
	CDevice::GetInst()->SetClearColor(100, 100, 100,1);
	//-- Create Constance Buffer -- //
	CDevice::GetInst()->CreateConstBuffer(L"Transform", sizeof(tTransform), D3D11_USAGE_DYNAMIC, 0);

	// GameObject 생성 .
	g_pObj = new CGameObject();
	g_pObj->AddComponent<CTransform>();
	g_pObj->AddComponent<CMeshRender>();
	g_pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	g_pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));

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
	
	g_pObj->Update();
	g_pObj->FinalUpdate();

	// View 변환행렬 구하기
	g_Transform.matView = XMMatrixIdentity();

	// Projection 변환행렬 구하기
	g_Transform.matProj = XMMatrixOrthographicLH(WINSIZE_X, WINSIZE_Y, 1.f, 1000.f);
	//g_Transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matProj = XMMatrixTranspose(g_Transform.matProj);



	return 0;
}

void CCore::render()
{
	CDevice::GetInst()->ClearTarget();

	// 삼각형 하나 그리기.  (해당 mesh와 vertex blob과 연결된다.)
	// 특정 mesh를 그리는 shader는 여러가지. shader와 연결관계인 layout은 어떠한 shader가 바뀔 때 마다 계속 새로 잡아주어야 함. 
	g_pObj->Render();

	CDevice::GetInst()->Present();
}
