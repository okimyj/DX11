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
CPlayerScript::CPlayerScript()
	: m_fSpeed(200.f)
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
	Transform()->SetLocalScale(Vec3(423.f/4.f, 700.f/4.f, 1.f));
	Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
}

int CPlayerScript::Update()
{
	
	float fDT = DT();
	
	Vec3 vPos = Transform()->GetLocalPosition();
	Vec3 vRot = Transform()->GetLocalRotation();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
		vPos.x -= m_fSpeed * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
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
		vPos.z += m_fSpeed * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE, KEY_STATE::DOWN))
	{
		Shoot();
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::DOWN))
	{
		MeshRender()->SetRSType(RASTERIZE_TYPE::WIRE);
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
	CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
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

CPlayerPlanet * CPlayerScript::CreatePlanet()
{
	if (NULL == m_planetPrefab)
		m_planetPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"PlayerPlanet");

	CGameObject* pObj = m_planetPrefab->Instantiate();
	CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
	return ((CPlayerPlanet*)pObj->GetComponent<CPlayerPlanet>());
}
