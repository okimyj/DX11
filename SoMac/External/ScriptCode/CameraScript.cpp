#include "stdafx.h"
#include "CameraScript.h"

CCameraScript::CCameraScript()
	:m_fScale(1.f)
{
}


CCameraScript::~CCameraScript()
{
}

int CCameraScript::Update()
{
	// -- camera scale --//
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_PAGEUP, KEY_STATE::HOLD))
	{
		m_fScale += DT();
		Camera()->SetScale(m_fScale);
	}
	else if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_PAGEDOWN, KEY_STATE::HOLD))
	{
		m_fScale -= DT();
		Camera()->SetScale(m_fScale);
	}
	// -- camera position --//
	Vec3 vPos = Transform()->GetLocalPosition();
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_W, KEY_STATE::HOLD))
	{
		vPos.y -= 500.f*DT();
		Transform()->SetLocalPosition(vPos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_S, KEY_STATE::HOLD))
	{
		vPos.y += 500.f*DT();
		Transform()->SetLocalPosition(vPos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_A, KEY_STATE::HOLD))
	{
		vPos.x += 500.f*DT();
		Transform()->SetLocalPosition(vPos);
	}
	if (CKeyMgr::GetInst()->GetKeyState(KEY_TYPE::KEY_D, KEY_STATE::HOLD))
	{
		vPos.x -= 500.f*DT();
		Transform()->SetLocalPosition(vPos);
	}

	return 0;
}