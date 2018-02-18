#include "PlayerScript.h"
#include "BulletScript.h"
#include "PlayerPlanet.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "Mesh.h"
#include "Texture.h"
#include "Prefab.h"
#include "TextureAnimator.h"
#include "TextureAnim.h"
#include "Material.h"
#include "TestScene.h"
CPlayerScript::CPlayerScript()
	: m_fSpeed(300.f)
	, m_bIsLeft(true)
{
}


CPlayerScript::~CPlayerScript()
{
}


void CPlayerScript::Awake()
{
//	CTextureAnimator* pTextureAnimator = (CTextureAnimator*)GetGameObject()->AddComponent<CTextureAnimator>(new CTextureAnimator);
//	CTextureAnim* idleAnim = new CTextureAnim(L"Player", 0, 7, 10, true);
//	pTextureAnimator->AddAnimation(L"Idle", idleAnim);
}

void CPlayerScript::Start()
{
//	CTextureAnimator* animator = (CTextureAnimator*)GetGameObject()->GetComponent<CTextureAnimator>();
//	animator->Play(L"Idle");
	Transform()->SetLocalPosition(Vec3(0.f, 0.f, 10.f));
	Transform()->SetLocalScale(Vec3(423.f/5.f, 700.f/5.f, 1.f));
	Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
}


bool CPlayerScript::CheckCollide(CGameObject * _pObj)
{
	Vec3 vPos = Transform()->GetLocalPosition();
	Vec3 vScale = Transform()->GetLocalScale();
	Vec3 vTargetPos = _pObj->GetTransform()->GetLocalPosition();
	Vec3 vTargetScale = _pObj->GetTransform()->GetLocalScale();
	
	float diffX = abs(vPos.x - vTargetPos.x) - (vScale.x/2 + vTargetScale.x/2);
	float diffY = abs(vPos.y - vTargetPos.y) - (vScale.y / 2 + vTargetScale.y / 2);
	if (diffX <= 0 && diffY <= 0)
	{
		return true;
	}
	return false;
}

/*
void CPlayerScript::Collide(CGameObject* _pObj) 
{
	if (_pObj->GetTag() == L"EnemyBullet (Clone)")
	{
		
	}
	else if (_pObj->GetTag() == L"HeartItem (Clone)")
	{
		AddPlanet();
		m_pTestScene->PushItemObj(_pObj);
	}
}
*/
int CPlayerScript::Update()
{
	
	float fDT = DT();
	
	Vec3 vPos = Transform()->GetLocalPosition();
	Vec3 vRot = Transform()->GetLocalRotation();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
//		m_bIsLeft = true;
		vPos.x -= m_fSpeed * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
//		m_bIsLeft = false;
		vPos.x += m_fSpeed * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_UP, KEY_STATE::HOLD))
	{
		vPos.y += m_fSpeed * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_DOWN, KEY_STATE::HOLD))
	{
		vPos.y -= m_fSpeed * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Y, KEY_STATE::HOLD))
	{
		vRot.y += XM_2PI * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z, KEY_STATE::HOLD))
	{
		vRot.z += XM_PI *fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE, KEY_STATE::DOWN))
	{
		Shoot();
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::DOWN))
	{
		MeshRenderer()->SetRSType(RASTERIZE_TYPE::WIRE);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::DOWN))
	{
		AddPlanet();
	}
	
	Transform()->SetLocalPosition(vPos);
	Transform()->SetLocalRotation(vRot);
	return RET_SUCCESS;
}

void CPlayerScript::Shoot()
{
	static UINT idx = 0;
	CBulletScript* bullectComp = CreateBullet();
	if (NULL != bullectComp)
	{
		bullectComp->SetInitPosition(Transform()->GetLocalPosition());
		bullectComp->SetDirection(m_bIsLeft ? Vec3(-1.f, 0.f, 0.f) : Vec3(1.f, 0.f, 0.f));
		bullectComp->Awake();
		bullectComp->Start();
		if (++idx % 2)
		{
			bullectComp->SetGrayScale();
		}
	}

}

CBulletScript* CPlayerScript::CreateBullet()
{
	if(NULL == m_bulletPrefab)
		m_bulletPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Bullet");
	
	CGameObject* pObj = m_bulletPrefab->Instantiate();
	CSceneMgr::GetInst()->AddGameObject(pObj, L"PlayerBulletLayer");
	return ((CBulletScript*)pObj->GetComponent<CBulletScript>());
}


void CPlayerScript::AddPlanet()
{
	CPlayerPlanet* pPlanet = CreatePlanet();
	pPlanet->SetOwner(this);
	pPlanet->Awake();
	pPlanet->Start();
	m_listPlanet.push_back(pPlanet);
}

void CPlayerScript::RemovePlanet()
{
	list<CPlayerPlanet*>::iterator iter = m_listPlanet.begin();


	if (iter == m_listPlanet.end())
	{
		// sub hp.
	}
	else
	{
		CSceneMgr::GetInst()->RemoveGameObject((*iter)->GameObject(), LAYER_DEFAULT);
		m_listPlanetPool.push_back(*(iter));
		m_listPlanet.erase(iter);
	}
	
	
}

CPlayerPlanet * CPlayerScript::CreatePlanet()
{
	list<CPlayerPlanet*>::iterator iter = m_listPlanetPool.begin();
	if (iter != m_listPlanetPool.end())
	{
		CSceneMgr::GetInst()->AddGameObject((*iter)->GameObject(), LAYER_DEFAULT);
		return (*iter);
	}
	if (NULL == m_planetPrefab)
		m_planetPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"PlayerPlanet");

	CGameObject* pObj = m_planetPrefab->Instantiate();
	pObj->SetParent(GameObject());
	//CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
	return ((CPlayerPlanet*)pObj->GetComponent<CPlayerPlanet>());
}
