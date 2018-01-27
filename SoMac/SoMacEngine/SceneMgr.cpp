#include "SceneMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRender.h"
#include "Mesh.h"
#include "Texture.h"
#include "PlayerScript.h"



CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL)
	, m_pPrevScene(NULL)
{
}


CSceneMgr::~CSceneMgr()
{
	SAFE_DELETE(m_pCurScene);
	SAFE_DELETE(m_pPrevScene);
}

void CSceneMgr::Init()
{
	// -- �ӽ� �׽�Ʈ �� ����.
	m_pCurScene = new CScene();
	// Scene �� Layer �߰�. 
		// ����� �߰��� Layer�� �����Ƿ� �߰����� �ʴ´�.

	// Texture Load.
	CTexture* pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Test", L"Texture\\Test.bmp");

	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(LAYER_DEFAULT);
	m_pCurScene->FindLayer(LAYER_CAMERA)->AddGameObject(pCamera);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	pObj->AddComponent<CScript>(new CPlayerScript);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetTexture((CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Test"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	m_pCurScene->FindLayer(LAYER_DEFAULT)->AddGameObject(pObj);

	pObj = CGameObject::CreateGameObject(L"Monster");
	pObj->GetTransform()->SetLocalPosition(Vec3(100.f, 100.f, 100.f));
	pObj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	m_pCurScene->FindLayer(LAYER_DEFAULT)->AddGameObject(pObj);
}

int CSceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->LateUpdate ();
	m_pCurScene->FinalUpdate();
	return RET_SUCCESS;
}

void CSceneMgr::Render()
{
	m_pCurScene->Render();
}

