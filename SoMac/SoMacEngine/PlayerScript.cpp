#include "PlayerScript.h"
#include "GameObject.h"
#include "BulletScript.h"
#include "ResMgr.h"
#include "ShaderMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "Mesh.h"
#include "Texture.h"
#include "TextureAnimator.h"
#include "TextureAnim.h"
CPlayerScript::CPlayerScript()
{
}


CPlayerScript::~CPlayerScript()
{
}


void CPlayerScript::Awake()
{
	CTextureAnimator* pTextureAnimator = (CTextureAnimator*)GetGameObject()->AddComponent<CTextureAnimator>(new CTextureAnimator);
	CTextureAnim* idleAnim = new CTextureAnim(L"Player", 0, 7, 10, true);
	pTextureAnimator->AddAnimation(L"Idle", idleAnim);
}

void CPlayerScript::Start()
{
	CTextureAnimator* animator = (CTextureAnimator*)GetGameObject()->GetComponent<CTextureAnimator>();
	animator->Play(L"Idle");
	Transform()->SetLocalPosition(Vec3(0.f, 0.f, 100.f));
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
	Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
}

int CPlayerScript::Update()
{
	
	float fDT = DT();
	
	Vec3 vPos = Transform()->GetLocalPosition();
	Vec3 vRot = Transform()->GetLocalRotation();

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_LEFT, KEY_STATE::HOLD))
	{
		vPos.x -= 100.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_RIGHT, KEY_STATE::HOLD))
	{
		vPos.x += 100.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_UP, KEY_STATE::HOLD))
	{
		vPos.y += 100.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_DOWN, KEY_STATE::HOLD))
	{
		vPos.y -= 100.f * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Y, KEY_STATE::HOLD))
	{
		vRot.y += XM_2PI * fDT;
	}

	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_Z, KEY_STATE::HOLD))
	{
		vPos.z += 100.f * fDT;
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_SPACE, KEY_STATE::DOWN))
	{
		Shoot();
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::DOWN))
	{
		MeshRender()->SetRSType(RASTERIZE_TYPE::WIRE);
	}



	Transform()->SetLocalPosition(vPos);
	Transform()->SetLocalRotation(vRot);
	return RET_SUCCESS;
}

void CPlayerScript::Shoot()
{
	CBulletScript* bullectComp = CreateBullet();
	if (NULL != bullectComp)
	{
		bullectComp->SetInitPosition(Transform()->GetLocalPosition());
		bullectComp->Awake();
		bullectComp->Start();
	}
	// TODO : SetTarget

}

CBulletScript* CPlayerScript::CreateBullet()
{
	/*
	CGameObject* pObj = CGameObject::CreateGameObject(L"Bullet");
	pObj->GetMeshRender()->SetMesh((CMesh*)CResMgr::GetInst()->Load<CMesh>(L"RectMesh"));
	pObj->GetMeshRender()->SetTexture((CTexture*)CResMgr::GetInst()->Load<CTexture>(L"Bullet"));
	pObj->GetMeshRender()->SetShader(CShaderMgr::GetInst()->FindShader(L"TextureShader"));
	CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
	return (CBulletScript*)pObj->AddComponent<CScript>(new CBulletScript);
	*/
	if(NULL == m_bulletPrefab)
		m_bulletPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"Bullet");
	if (NULL != m_bulletPrefab)
	{
		CGameObject* pObj = m_bulletPrefab->Instantiate();
		CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
		return ((CBulletScript*)pObj->GetComponent<CBulletScript>());
	}
	
	return NULL;
}
