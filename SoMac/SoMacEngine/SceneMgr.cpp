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



CSceneMgr::CSceneMgr()
	: m_pCurScene(NULL)
	, m_pPrevScene(NULL)
{
}


CSceneMgr::~CSceneMgr()
{

}

void CSceneMgr::Init()
{
	// -- 임시 테스트 씬 구성.
	m_pCurScene = new CScene();
	// Scene 에 Layer 추가. 
		// 현재는 추가할 Layer가 없으므로 추가하지 않는다.

	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(m_pCurScene->FindLayer(LAYER_DEFAULT));
	m_pCurScene->FindLayer(LAYER_CAMERA)->AddGameObject(pCamera);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	pObj->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, 100.f));
	pObj->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
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

