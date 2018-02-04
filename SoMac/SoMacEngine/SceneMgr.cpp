#include "SceneMgr.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Script.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
#include "BulletScript.h"
#include "Prefab.h"
#include "Material.h"
#include "TestScene.h"


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
	m_pCurScene = new CTestScene();
	m_pCurScene->Init();
	/*
	m_pCurScene = new CScene();
	// -- 임시 테스트 씬 구성.
	CreateTestScene();
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

void CSceneMgr::CreateTestScene()
{
	// Scene 에 Layer 추가. 
	// 현재는 추가할 Layer가 없으므로 추가하지 않는다.
	m_pCurScene->AddLayer(L"PlayerLayer");
	m_pCurScene->AddLayer(L"MonsterLayer");
	// Texture Load.
	CTexture* pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet", L"Texture\\bullet.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player", L"Texture\\player.png");
	/*
	for (int i = 0; i<8; ++i)
	{
		wstring strIdx = to_wstring(i);
		pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player" + strIdx, L"Texture\\player" + strIdx + L".png");
	}
	*/
	CreateMaterial();

	CreateGameObject();
}

void CSceneMgr::CreateMaterial()
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	int iData = 1;
	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Player");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"PlayerMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Bullet");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"BulletMaterial", pMaterial);

}

void CSceneMgr::CreateGameObject()
{
	// -- Create Bullet Prefab --//
	CGameObject* pBullet = CGameObject::CreateGameObject(L"Bullet");
	pBullet->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pBullet->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"BulletMaterial"));
	pBullet->AddComponent<CScript>(new CBulletScript);
	CResMgr::GetInst()->AddPrefab(L"Bullet", pBullet);



	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(LAYER_DEFAULT);
	pCamera->GetCamera()->AddRenderTargetLayer(L"PlayerLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"MonsterLayer");
	AddGameObject(pCamera, LAYER_CAMERA);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	pObj->AddComponent<CScript>(new CPlayerScript);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"PlayerMaterial"));
	AddGameObject(pObj, L"PlayerLayer");


	pObj = CGameObject::CreateGameObject(L"Enemy1");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->GetTransform()->SetLocalPosition(Vec3(-100.f, -100.f, 99.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"Default"));
	AddGameObject(pObj, L"MonsterLayer");

	/*
	pObj = CGameObject::CreateGameObject(L"Enemy2");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->GetTransform()->SetLocalPosition(Vec3(100.f, 100.f, 99.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"ColorShader"));
	m_pCurScene->FindLayer(L"MonsterLayer")->AddGameObject(pObj);
	*/
}
