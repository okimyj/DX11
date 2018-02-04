#include "TestScene.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Layer.h"
#include "ShaderMgr.h"
#include "Texture.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "PlayerScript.h"
#include "BulletScript.h"
#include "EnemyScript.h"
#include "PlayerPlanet.h"

#include "Prefab.h"

CTestScene::CTestScene()
{
	
}


CTestScene::~CTestScene()
{
	Safe_Delete_List(m_listEnemyPool);
}

void CTestScene::Init()
{
	AddLayer(L"PlayerLayer");
	AddLayer(L"MonsterLayer");
	// -- Texture Load --//
	CTexture* pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet", L"Texture\\bullet.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player", L"Texture\\player.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Enemy", L"Texture\\enemy.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"PlayerPlanet", L"Texture\\miniPlayer.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"EnemyBullet", L"Texture\\bullet_enemy.png");
	

	CreateMaterial();
	CreatePrefab();
	CreateGameObject();
} 

int CTestScene::Update()
{
	float fDT = CTimeMgr::GetInst()->DeltaTime();
	m_fAccureDT += fDT;
	if (m_fAccureDT >= 2.f)
	{
		m_fAccureDT = 0.f;
		CGameObject* pEnemy = PopEnemyObj();
		srand(time(NULL));
		float y = rand() % ((WINSIZE_Y / 100) /2);
		Vec3 vPos = pEnemy->GetTransform()->GetLocalPosition();
		Vec3 vScale = pEnemy->GetTransform()->GetLocalScale();
		vPos.x = -WINSIZE_X / 2.f + vScale.x / 2.f;

		vPos.y = y * 100.f;
		vPos.z = 10.f;
		pEnemy->GetTransform()->SetLocalPosition(vPos);
	}

	// 마지막에 parent update 호출.
	CScene::Update();
	return RET_SUCCESS;
}



void CTestScene::CreateMaterial()
{
	//-- Create Material --//
	CMaterial* pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	int iData = 0;
	CTexture* pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Player");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"PlayerMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"PlayerPlanet");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"PlayerPlanetMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Bullet");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"BulletMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"Enemy");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"EnemyMaterial", pMaterial);

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"EnemyBullet");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"EnemyBulletMaterial", pMaterial);
	
}
void CTestScene::CreatePrefab()
{
	// -- Create Bullet Prefab --//
	CGameObject* pPrefab = CGameObject::CreateGameObject(L"Bullet");
	pPrefab->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"BulletMaterial"));
	pPrefab->AddComponent<CScript>(new CBulletScript);
	CResMgr::GetInst()->AddPrefab(L"Bullet", pPrefab);
	
	// --  Create Planet Prefab -- //
	pPrefab = CGameObject::CreateGameObject(L"PlayerPlanet");
	pPrefab->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"PlayerPlanetMaterial"));
	pPrefab->AddComponent<CScript>(new CPlayerPlanet);
	CResMgr::GetInst()->AddPrefab(L"PlayerPlanet", pPrefab);
	
	// -- Create Enemy Prefab --//
	pPrefab = CGameObject::CreateGameObject(L"EnemyPrefab");
	pPrefab->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"EnemyMaterial"));
	pPrefab->AddComponent<CScript>(new CEnemyScript);
	CResMgr::GetInst()->AddPrefab(L"Enemy", pPrefab);

	// -- Create Enemy Bulleft Prefab --//
	pPrefab = CGameObject::CreateGameObject(L"EnemyBullet");
	pPrefab->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"EnemyBulletMaterial"));
	pPrefab->AddComponent<CScript>(new CBulletScript);
	CResMgr::GetInst()->AddPrefab(L"EnemyBullet", pPrefab);
}
void CTestScene::CreateGameObject()
{
	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(LAYER_DEFAULT);
	pCamera->GetCamera()->AddRenderTargetLayer(L"PlayerLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"MonsterLayer");
	FindLayer(LAYER_CAMERA)->AddGameObject(pCamera);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	pObj->AddComponent<CScript>(new CPlayerScript);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"PlayerMaterial"));
	FindLayer(L"PlayerLayer")->AddGameObject(pObj);
	/*
	pObj = CGameObject::CreateGameObject(L"Enemy1");
	pObj->AddComponent<CScript>(new CEnemyScript);
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"EnemyMaterial"));
	FindLayer(L"MonsterLayer")->AddGameObject(pObj);
	*/
}

CGameObject * CTestScene::PopEnemyObj()
{
	list<CGameObject*>::iterator iter = m_listEnemyPool.begin();
	CGameObject* pObj = NULL;
	if (iter == m_listEnemyPool.end())
		pObj = CreateEnemy();
	else
	{
		pObj = (*iter);
		m_listEnemyPool.erase(iter);
	}
		
	FindLayer(L"MonsterLayer")->AddGameObject(pObj);

	
	return pObj;
}


CGameObject* CTestScene::CreateEnemy()
{
	if (NULL == m_pEnemyPrefab)
		m_pEnemyPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Enemy");
	CGameObject* pEnemy = (CGameObject*)m_pEnemyPrefab->Instantiate();
	
	return pEnemy;
}

void CTestScene::PushEnemyObj(CGameObject * _pObj)
{
	FindLayer(L"MonsterLayer")->RemoveGameObject(_pObj);
	m_listEnemyPool.push_back(_pObj);
}

