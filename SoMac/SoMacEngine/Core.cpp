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



// Vertex 전역 배열
//VTX g_arrVtx[4] = {};

ID3D11Buffer* g_pTransformBuffer = NULL; // Constant Buffer.
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
	SAFE_RELEASE(g_pTransformBuffer);
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
	
	// Create Constant Buffer .
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = sizeof(tTransform);
	tBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, NULL, &g_pTransformBuffer)))
	{
		return RET_FAILED;
	}


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
	bool bKeyPress = false;
	float fDT = CTimeMgr::GetInst()->DeltaTime();
	// 삼각형 이동. 
	/*
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
		for (int i = 0; i < 4; ++i)
			g_arrVtx[i].vPos.x -= 0.2 * fDT;
		bKeyPress = true;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
		for (int i = 0; i < 4; ++i)
			g_arrVtx[i].vPos.x += 0.2 * fDT;
		bKeyPress = true;
	}
	if (bKeyPress)
	{
		D3D11_MAPPED_SUBRESOURCE tSub = {};
		// 버텍스 버퍼 재갱신
		CONTEXT->Map(g_pVB, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
		memcpy(tSub.pData, g_arrVtx, sizeof(VTX) * 4);
		CONTEXT->Unmap(g_pVB, 0);
	}
	*/
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
		g_vPos.x -= 100.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
		g_vPos.x += 100.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Y, KEY_STATE::HOLD))
	{
		g_vRot.y += XM_2PI * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z, KEY_STATE::HOLD))
	{
		g_vPos.z += 100.f * fDT;
	}
	// World 변환 행렬 구하기.
	g_Transform.matWorld = XMMatrixIdentity();
	XMMATRIX matScale = XMMatrixScaling(g_vScale.x, g_vScale.y, g_vScale.z);
	XMMATRIX matTransform = XMMatrixTranslation(g_vPos.x, g_vPos.y, g_vPos.z);
	XMMATRIX matRot = XMMatrixRotationX(g_vRot.x);
	matRot *= XMMatrixRotationY(g_vRot.y);
	matRot *= XMMatrixRotationZ(g_vRot.z);

	g_Transform.matWorld = matScale * matRot * matTransform;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);

	// View 변환행렬 구하기
	g_Transform.matView = XMMatrixIdentity();

	// Projection 변환행렬 구하기
	g_Transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matProj = XMMatrixTranspose(g_Transform.matProj);



	// 상수버퍼로 데이터 옮김
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(g_pTransformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, sizeof(tTransform));
	CONTEXT->Unmap(g_pTransformBuffer, 0);
	
	


	return 0;
}

void CCore::render()
{
	CDevice::GetInst()->ClearTarget();


	// 삼각형 하나 그리기.  (해당 mesh와 vertex blob과 연결된다.)
	// 특정 mesh를 그리는 shader는 여러가지. shader와 연결관계인 layout은 어떠한 shader가 바뀔 때 마다 계속 새로 잡아주어야 함. 
	
	CONTEXT->VSSetConstantBuffers(0, 1, &g_pTransformBuffer);			// StartSlot(0) : Register 번호.
	g_pObj->Render();

	CDevice::GetInst()->Present();
}
