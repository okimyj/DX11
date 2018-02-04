#include "EnemyScript.h"
#include "SceneMgr.h"
#include "Transform.h"
#include "BulletScript.h"
#include "Prefab.h"
#include "TestScene.h"

CEnemyScript::CEnemyScript()
	: m_fAccrueDT(0.f)
	, m_fSpeed(50.f)
{
}

CEnemyScript::CEnemyScript(const CEnemyScript & _pOther)
	: m_fAccrueDT(0.f)
	, m_fSpeed(50.f)
{
}


CEnemyScript::~CEnemyScript()
{
}


void CEnemyScript::Awake()
{
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 1.f));
}

void CEnemyScript::Start()
{
}

void CEnemyScript::Die()
{
	if (NULL != m_pTestScene)
	{
		m_pTestScene->PushEnemyObj(GetGameObject());
	}
}

void CEnemyScript::Shoot()
{
	CBulletScript* bullectComp = CreateBullet();
	if (NULL != bullectComp)
	{
		bullectComp->SetInitPosition(Transform()->GetLocalPosition());
		bullectComp->Awake();
		bullectComp->Start();
	}
}

CBulletScript* CEnemyScript::CreateBullet()
{
	if (NULL == m_bulletPrefab)
		m_bulletPrefab = (CPrefab*)CResMgr::GetInst()->Load<CPrefab>(L"EnemyBullet");

	CGameObject* pObj = m_bulletPrefab->Instantiate();
	CSceneMgr::GetInst()->AddGameObject(pObj, LAYER_DEFAULT);
	return ((CBulletScript*)pObj->GetComponent<CBulletScript>());
}


int CEnemyScript::Update()
{
	float fDT = DT();
	m_fAccrueDT += fDT;
	/*
	
	if (m_fAccrueDT >= 1.f)
	{
		srand(time(NULL));
		m_iCurDir = rand() % 5;
		m_fAccrueDT = 0.f;
	}
	*/
	m_iCurDir = 2;
	Vec3 vPos = Transform()->GetLocalPosition();
	Vec3 vRot = Transform()->GetLocalRotation();
	Vec3 vScale = Transform()->GetLocalScale();
	if (m_iCurDir == 1)
	{
		vPos.x -= m_fSpeed * fDT;
	}
	else if (m_iCurDir == 2)
	{
		vPos.x += m_fSpeed * fDT;
	}
	else if (m_iCurDir == 3)
	{
		vPos.y -= m_fSpeed * fDT;
	}
	else if (m_iCurDir == 4)
	{
		vPos.y += m_fSpeed * fDT;
	}
	else
	{
		vRot.z += 3.14f *fDT;
	}
	// 화면 밖으로 나가는지 check .
	float halfW = vScale.x / 2.f;
	float halfH = vScale.y / 2.f;
	
	if (vPos.x + halfW >= WINSIZE_X/2 || vPos.x - halfW <= -WINSIZE_X / 2
		|| vPos.y + halfH >= WINSIZE_Y/2 || vPos.y - halfH <= -WINSIZE_Y / 2)
		m_fAccrueDT = 0.f;
	else
	{
		Transform()->SetLocalPosition(vPos);
		
		if (m_fAccrueDT >= 2.5f)
		{
			m_fAccrueDT = 0.f;
			Shoot();
		}
	}
	Transform()->SetLocalRotation(vRot);
	return 0;
}

