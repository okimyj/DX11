#include "PlayerScript.h"
#include "GameObject.h"


CPlayerScript::CPlayerScript()
{
}


CPlayerScript::~CPlayerScript()
{
}


void CPlayerScript::Awake()
{
	
}

void CPlayerScript::Start()
{
	Transform()->SetLocalPosition(Vec3(0.f, 0.f, 100.f));
	Transform()->SetLocalScale(Vec3(100.f, 100.f, 100.f));
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
	Transform()->SetLocalPosition(vPos);
	Transform()->SetLocalRotation(vRot);
	return RET_SUCCESS;
}
