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

//ID3D11Buffer* g_pTransformBuffer = NULL; // Constant Buffer.
//-> Device
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
	//-- Create Constance Buffer -- //
	CDevice::GetInst()->CreateConstBuffer(L"Transform", sizeof(tTransform), D3D11_USAGE_DYNAMIC, 0);

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
	g_pObj->FinalUpdate();

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

	// �ﰢ�� �ϳ� �׸���.  (�ش� mesh�� vertex blob�� ����ȴ�.)
	// Ư�� mesh�� �׸��� shader�� ��������. shader�� ��������� layout�� ��� shader�� �ٲ� �� ���� ��� ���� ����־�� ��. 
	g_pObj->Render();

	CDevice::GetInst()->Present();
}
