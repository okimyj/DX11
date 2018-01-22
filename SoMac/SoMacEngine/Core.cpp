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



// Vertex ���� �迭
//VTX g_arrVtx[4] = {};

ID3D11Buffer* g_pTransformBuffer = NULL; // Constant Buffer.
tTransform g_Transform;

// player �� ���� ��������
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


	// GameObject ���� .
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
	// �ﰢ�� �̵�. 
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
		// ���ؽ� ���� �簻��
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
	// World ��ȯ ��� ���ϱ�.
	g_Transform.matWorld = XMMatrixIdentity();
	XMMATRIX matScale = XMMatrixScaling(g_vScale.x, g_vScale.y, g_vScale.z);
	XMMATRIX matTransform = XMMatrixTranslation(g_vPos.x, g_vPos.y, g_vPos.z);
	XMMATRIX matRot = XMMatrixRotationX(g_vRot.x);
	matRot *= XMMatrixRotationY(g_vRot.y);
	matRot *= XMMatrixRotationZ(g_vRot.z);

	g_Transform.matWorld = matScale * matRot * matTransform;
	g_Transform.matWorld = XMMatrixTranspose(g_Transform.matWorld);

	// View ��ȯ��� ���ϱ�
	g_Transform.matView = XMMatrixIdentity();

	// Projection ��ȯ��� ���ϱ�
	g_Transform.matProj = XMMatrixPerspectiveFovLH(XM_PI / 4.f, (float)WINSIZE_X / (float)WINSIZE_Y, 1.f, 1000.f);
	g_Transform.matProj = XMMatrixTranspose(g_Transform.matProj);



	// ������۷� ������ �ű�
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(g_pTransformBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &g_Transform, sizeof(tTransform));
	CONTEXT->Unmap(g_pTransformBuffer, 0);
	
	


	return 0;
}

void CCore::render()
{
	CDevice::GetInst()->ClearTarget();


	// �ﰢ�� �ϳ� �׸���.  (�ش� mesh�� vertex blob�� ����ȴ�.)
	// Ư�� mesh�� �׸��� shader�� ��������. shader�� ��������� layout�� ��� shader�� �ٲ� �� ���� ��� ���� ����־�� ��. 
	
	CONTEXT->VSSetConstantBuffers(0, 1, &g_pTransformBuffer);			// StartSlot(0) : Register ��ȣ.
	g_pObj->Render();

	CDevice::GetInst()->Present();
}
