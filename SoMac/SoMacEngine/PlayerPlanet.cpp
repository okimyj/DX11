#include "PlayerPlanet.h"
#include "PlayerScript.h"
CPlayerPlanet::CPlayerPlanet()
	: m_fRadius(100.f)
	, m_pOwner(NULL)
{
}

CPlayerPlanet::CPlayerPlanet(const CPlayerPlanet & _pOther)
	: m_fRadius(_pOther.m_fRadius)
	, m_pOwner(NULL)
	, m_fRadian(0.f)
{
}


CPlayerPlanet::~CPlayerPlanet()
{
}


void CPlayerPlanet::Awake()
{
	Transform()->SetLocalScale(Vec3(175.f/3.f, 220.f/3.f, 1.f));
	Vec3 vPos = m_pOwner->Transform()->GetLocalPosition();
	vPos.y += m_fRadius;
	m_fRadian = 0.f;
	Transform()->SetLocalPosition(vPos);

}

void CPlayerPlanet::Start()
{
}

int CPlayerPlanet::Update()
{
	float fDT = DT();
	m_fRadian += 3.14f * fDT;
	if (m_fRadian >= 3.14f * 2)
		m_fRadian = 0.f;
	Vec3 vOwnerPos = m_pOwner->Transform()->GetLocalPosition();
	float x = m_fRadius * sin(m_fRadian);
	float y = m_fRadius * cos(m_fRadian);
	vOwnerPos.x += x;
	vOwnerPos.y += y;
	Transform()->SetLocalPosition(vOwnerPos);

	return 0;
}


