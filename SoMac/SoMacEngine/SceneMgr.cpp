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
#include "CameraScript.h"
#include "Prefab.h"
#include "Material.h"
#include "TestScene.h"
#include "Collider2D.h"
#include "CollisionMgr.h"
#include "Animator.h"

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
	m_pCurScene = new CScene();
	
	m_pCurScene->Awake();
	m_pCurScene->Start();
}

int CSceneMgr::Update()
{
	m_pCurScene->Update();
	m_pCurScene->LateUpdate ();
	m_pCurScene->FinalUpdate();
	CCollisionMgr::GetInst()->Update();
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

void CSceneMgr::RemoveGameObject(CGameObject * _pObj, const wstring & _strLayerName)
{
	wstring layerName = _strLayerName;
	if (layerName == L"")
		layerName = LAYER_DEFAULT;
	m_pCurScene->FindLayer(layerName)->RemoveGameObject(_pObj);
}

CLayer * CSceneMgr::GetCurSceneLayer(const wstring & _strLayerName)
{
	return GetCurScene()->FindLayer(_strLayerName);
}

void CSceneMgr::CreateTestScene()
{
	CreateMaterial();

	CreateGameObject();
}

void CSceneMgr::CreateMaterial()
{
	CMaterial* pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"StandardShader"));
	int iData = 0;
	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Player");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::INT_1, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"PlayerMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Bullet");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"BulletMaterial", pMaterial);

	
	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"CartoonShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Cartoon");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"CartoonMaterial", pMaterial);
	
}

void CSceneMgr::CreateGameObject()
{
	// -- Create Bullet Prefab --//
	CGameObject* pBullet = CGameObject::CreateGameObject(L"Bullet");
	pBullet->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pBullet->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"BulletMaterial"));
	pBullet->AddComponent<CScript>(new CBulletScript);
	CResMgr::GetInst()->AddPrefab(L"Bullet", pBullet);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	CPlayerScript* pPlayer = (CPlayerScript*)pObj->AddComponent<CScript>(new CPlayerScript);
	pObj->AddComponent<CCollider>(new CCollider2D);
	pObj->AddComponent<CAnimator>(new CAnimator);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"StandardMaterial"));
	pObj->GetCollider()->SetOffsetScale(Vec3(1.1f, 1.1f, 1.1f));
//	pObj->GetAnimator()->LoadAnimation2D(L"Explosion_00", L"Texture\\Animation\\Explosion");
//	pObj->GetAnimator()->LoadAnimation2D(L"Explosion_01", L"Texture\\Animation\\Explosion_01");
	pObj->GetAnimator()->LoadAnimation2D(L"Explosion", L"Texture\\Animation\\Explosion");
	pObj->GetAnimator()->LoadAnimation2D(L"Rabbit", L"Texture\\Animation\\Rabbit\\");
	pObj->GetAnimator()->LoadAnimation2D(L"Player", L"Texture\\Animation\\Player");

	pObj->GetAnimator()->PlayAnimation(L"Player_Right_Idle");
	AddGameObject(pObj, L"PlayerLayer");


	pObj = CGameObject::CreateGameObject(L"Enemy1");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->AddComponent<CCollider>(new CCollider2D);
	pObj->GetTransform()->SetLocalPosition(Vec3(-100.f, -100.f, 99.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"Default"));
	pObj->GetCollider()->SetOffsetScale(Vec3(1.1f, 1.1f, 1.1f));
	AddGameObject(pObj, L"MonsterLayer");
	/*
	pObj = CGameObject::CreateGameObject(L"Cartoon");
	pObj->AddComponent<CCollider>(new CCollider2D);
	
	pObj->GetTransform()->SetLocalPosition(Vec3(0, 0, 100.f));
	pObj->GetTransform()->SetLocalScale(Vec3(WINSIZE_X, WINSIZE_Y, 1.f));
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"CartoonMaterial"));
	pObj->GetCollider()->SetOffsetScale(Vec3(1.1f, 1.1f, 1.1f));
	AddGameObject(pObj, L"MonsterLayer");
	*/
}
