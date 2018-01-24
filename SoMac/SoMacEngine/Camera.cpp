#include "Camera.h"
#include "Transform.h"

CCamera::CCamera()
	: m_bPerspective(false)
	, m_fFOV(XM_PI / 4.f)
	, m_fWidth(WINSIZE_X)
	, m_fHeight(WINSIZE_Y)
	, m_fScale(1.f)
	, m_fNear(1.f)
	, m_fFar(1000.f)
{
}


CCamera::~CCamera()
{
}


int CCamera::Update()
{
	return 0;
}

int CCamera::LateUpdate()
{
	// View 변환 행렬 구하기. 
	m_matView = XMMatrixIdentity();			//  XMMatrixIdentity() : 단위행렬.

	// Vec3이 *= 연산을 제공 했다면.. 
	// Matrix도 구조체의 메모리가 선형메모리구조이기 때문에 memcpy로 해주어도 상관없다. 
	Vec3 vPos = Transform()->GetLocalPosition();
	m_matView._41 = -vPos.x;
	m_matView._42 = -vPos.y;
	m_matView._43 = -vPos.z;

	
	return 0;
}

int CCamera::FinalUpdate()
{
	return 0;
}

