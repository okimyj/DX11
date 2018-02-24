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

	return 0;
}