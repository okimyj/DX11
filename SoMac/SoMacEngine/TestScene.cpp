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
#include "ItemScript.h"

#include "Prefab.h"

CTestScene::CTestScene()
{
	
}


CTestScene::~CTestScene()
{
	Safe_Delete_List(m_listEnemyPool);
	Safe_Delete_List(m_listItemPool);
	
}

void CTestScene::Init()
{
	AddLayer(L"ItemLayer");
	AddLayer(L"PlayerLayer");
	AddLayer(L"PlayerBulletLayer");
	AddLayer(L"MonsterLayer");
	AddLayer(L"MonsterBulletLayer");
	// -- Texture Load --//
	CTexture* pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet", L"Texture\\bullet.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Player", L"Texture\\player.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Enemy", L"Texture\\enemy.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"PlayerPlanet", L"Texture\\miniPlayer.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"EnemyBullet", L"Texture\\bullet_enemy.png");
	pText = (CTexture*)CResMgr::GetInst()->Load<CTexture>(L"HeartItem", L"Texture\\item.png");
	

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
		pEnemy->Awake();
		pEnemy->Start();

		srand(time(NULL));
		float y = rand() % ((WINSIZE_Y / 100) /2);
		Vec3 vPos = pEnemy->GetTransform()->GetLocalPosition();
		Vec3 vScale = pEnemy->GetTransform()->GetLocalScale();
		vPos.x = -WINSIZE_X / 2.f + vScale.x / 2.f;

		vPos.y = y * 100.f;
		vPos.z = 10.f;
		pEnemy->GetTransform()->SetLocalPosition(vPos);
		
		if (rand() % 2)
		{
			CGameObject* pItem = PopItemObj();
			pItem->Awake();
			pItem->Start();
			srand(time(NULL));
			float y = rand() % ((WINSIZE_Y / 100) / 2);
			float x = rand() % ((WINSIZE_X / 100) / 2);

			Vec3 vPos = pItem->GetTransform()->GetLocalPosition();
			Vec3 vScale = pItem->GetTransform()->GetLocalScale();

			vPos.y = y * 100.f;
			vPos.x = x * 100.f;
			vPos.z = 9.f;
			pItem->GetTransform()->SetLocalPosition(vPos);

		}
		
	}
	CheckCollide();
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

	pMaterial = new CMaterial;
	pMaterial->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	iData = 0;
	pTex = (CTexture*)CResMgr::GetInst()->Load <CTexture>(L"HeartItem");
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &pTex);
	CResMgr::GetInst()->AddMaterial(L"HeartMaterial", pMaterial);
	


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

	// -- Create Item Prefab -- //
	pPrefab = CGameObject::CreateGameObject(L"HeartItem");
	pPrefab->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pPrefab->GetMeshRender()->SetMaterial((CMaterial*)CResMgr::GetInst()->Load<CMaterial>(L"HeartMaterial"));
	pPrefab->AddComponent<CScript>(new CItemScript);
	CResMgr::GetInst()->AddPrefab(L"ItemPrefab", pPrefab);
}
void CTestScene::CreateGameObject()
{
	// -- Create Camera & Add to Camera Layer
	CGameObject* pCamera = CGameObject::CreateCamera(L"MainCamera");
	pCamera->GetCamera()->AddRenderTargetLayer(LAYER_DEFAULT);
	pCamera->GetCamera()->AddRenderTargetLayer(L"ItemLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"PlayerLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"PlayerBulletLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"MonsterLayer");
	pCamera->GetCamera()->AddRenderTargetLayer(L"MonsterBulletLayer");

	FindLayer(LAYER_CAMERA)->AddGameObject(pCamera);

	//-- create GameObject & Add to Default Layer.
	CGameObject* pObj = CGameObject::CreateGameObject(L"Player");
	m_pPlayer = (CPlayerScript*)pObj->AddComponent<CScript>(new CPlayerScript);
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


CGameObject * CTestScene::PopItemObj()
{
	list<CGameObject*>::iterator iter = m_listItemPool.begin();
	CGameObject* pObj = NULL;
	if (iter == m_listItemPool.end())
		pObj = CreateItem();
	else
	{
		pObj = (*iter);
		m_listItemPool.erase(iter);
	}

	FindLayer(L"ItemLayer")->AddGameObject(pObj);
	return pObj;
}

CGameObject * CTestScene::CreateItem()
{
	if (NULL == m_pItemPrefab)
		m_pItemPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"ItemPrefab");
	CGameObject* pItem = (CGameObject*)m_pItemPrefab->Instantiate();

	return pItem;
}



void CTestScene::PushItemObj(CGameObject * _pObj)
{
	FindLayer(L"ItemLayer")->RemoveGameObject(_pObj);
	m_listItemPool.push_back(_pObj);
}


void CTestScene::CheckCollide()
{
	{
		CLayer* pLayer = FindLayer(L"ItemLayer");
		list<CGameObject*>& listObj = pLayer->GetObjList();
		list<CGameObject*>::iterator iter = listObj.begin();
		for (; iter != listObj.end();)
		{
			if (m_pPlayer->CheckCollide((*iter)))
			{
				m_pPlayer->AddPlanet();
				iter = listObj.erase(iter);
			}
			else
				++iter;
		}
	}
	{
		CLayer* pLayer = FindLayer(L"MonsterBulletLayer");
		list<CGameObject*>& listObj = pLayer->GetObjList();
		list<CGameObject*>::iterator iter = listObj.begin();
	
		for (; iter != listObj.end();)
		{
			if (m_pPlayer->CheckCollide((*iter)))
			{
				m_pPlayer->RemovePlanet();
				iter = listObj.erase(iter);
			}
			else
				++iter;
		}
	}
}