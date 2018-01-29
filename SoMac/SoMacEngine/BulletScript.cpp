#include "BulletScript.h"

CBulletScript::CBulletScript()
	:m_fSpeed(200.f)
{
}


CBulletScript::~CBulletScript()
{
}


void CBulletScript::Awake()
{
}

void CBulletScript::Start()
{
	m_vInitPos.z = m_vInitPos.z -1;
	Transform()->SetLocalPosition(m_vInitPos);
	Transform()->SetLocalScale(Vec3(25.f, 17.f, 1.f));
	Transform()->SetLocalRotation(Vec3(0.f, 0.f, 0.f));
}

int CBulletScript::Update()
{
	float fDT = DT();
	Vec3 vPos = Transform()->GetLocalPosition();
	vPos.x += m_fSpeed*fDT;
	Transform()->SetLocalPosition(vPos);
	return RET_SUCCESS;
}

