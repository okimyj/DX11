#include "PlayerPlanet.h"
#include "PlayerScript.h"
CPlayerPlanet::CPlayerPlanet()
	: m_fSpeed(100.f)
	, m_pOwner(NULL)
{
}


CPlayerPlanet::~CPlayerPlanet()
{
}


void CPlayerPlanet::Awake()
{
	Transform()->SetLocalScale(Vec3(50.f, 50.f, 1.f));
	Vec3 vPos = m_pOwner->Transform()->GetLocalPosition();
	vPos.x += 100.f;
	m_fAngle = 0.f;
	Transform()->SetLocalPosition(vPos);

}

void CPlayerPlanet::Start()
{
}

int CPlayerPlanet::Update()
{
	float fDT = DT();
	Vec3 vPos = Transform()->GetLocalPosition();
	/*
	m_fAngle += 3.14f* fDT;
	Vec3 vPos2 = Vec3(100.f * m_fAngle, 0.f, 0.f);
	*/

	return 0;
}


