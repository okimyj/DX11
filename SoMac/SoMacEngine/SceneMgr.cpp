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
#include "Script.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
#include "BulletScript.h"
#include "Prefab.h"



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
	// -- 임시 테스트 씬 구성.
	m_pCurScene = new CScene();
	// Scene 에 Layer 추가. 
		// 현재는 추가할 Layer가 없으므로 추가하지 않는다.
	m_pCurScene->AddLayer(L"PlayerLayer");
	m_pCurScene->AddLayer(L"MonsterLayer");
	// Texture Load.
	CTexture* pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet", L"Texture\\bullet.png"); 
	for(int i=0; i<8; ++i)
	{
		wstring strIdx = to_wstring(i);
		pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player"+strIdx, L"Texture\\player" + strIdx + L".png");
	}

	// -- Create Bullet Prefab --//
	CGameObject* pBullet = CGameObject::CreateGameObject(L"Bullet");
	pBullet->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pBullet->GetMeshRender()->SetTexture((CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet"));
	pBullet->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	pBullet->AddComponent<CScript>(new CBulletScript);
	CResMgr::GetInst()->AddPrefab(L"Bullet", pBullet);

	

	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(LAYER_DEFAULT);
	pCamera->GetCamera()->AddRenderTargetLayer(L"PlayerLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"MonsterLayer");
	m_pCurScene->FindLayer(LAYER_CAMERA)->AddGameObject(pCamera);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	pObj->AddComponent<CScript>(new CPlayerScript);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetTexture((CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player0"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	m_pCurScene->FindLayer(L"PlayerLayer")->AddGameObject(pObj);


	pObj = CGameObject::CreateGameObject(L"Enemy1");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->GetTransform()->SetLocalPosition(Vec3(-100.f, -100.f, 99.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	m_pCurScene->FindLayer(L"MonsterLayer")->AddGameObject(pObj);
	/*
	pObj = CGameObject::CreateGameObject(L"Enemy2");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->GetTransform()->SetLocalPosition(Vec3(100.f, 100.f, 99.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	m_pCurScene->FindLayer(L"MonsterLayer")->AddGameObject(pObj);
	*/
	m_pCurScene->Awake();
	m_pCurScene->Start();
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

void CSceneMgr::AddGameObject(CGameObject * _pObj, const wstring & _strLayerName)
{
	wstring layerName = _strLayerName;
	if (layerName == L"")
		layerName = LAYER_DEFAULT;
	m_pCurScene->FindLayer(layerName)->AddGameObject(_pObj);
}
