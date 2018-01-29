#include "EnemyScript.h"
#include "Transform.h"

CEnemyScript::CEnemyScript()
	: m_fAccrueDT(0.f)
	, m_fSpeed(100.f)
{
}


CEnemyScript::~CEnemyScript()
{
}

void CEnemyScript::Awake()
{
	Transform()->SetLocalScale(Vec3(30.f, 30.f, 1.f));
}

void CEnemyScript::Start()
{
}

int CEnemyScript::Update()
{
	float fDT = DT();
	m_fAccrueDT += fDT;
	if (m_fAccrueDT >= 1.f)
	{
		srand(time(NULL));
		m_iCurDir = rand() % 5;
		m_fAccrueDT = 0.f;
	}
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
		m_fAccrueDT = 1.f;
	else
		Transform()->SetLocalPosition(vPos);
	Transform()->SetLocalRotation(vRot);
	return 0;
}

