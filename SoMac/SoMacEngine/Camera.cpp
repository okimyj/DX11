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
	// View ��ȯ ��� ���ϱ�. 
	m_matView = XMMatrixIdentity();			//  XMMatrixIdentity() : �������.

	// Vec3�� *= ������ ���� �ߴٸ�.. 
	// Matrix�� ����ü�� �޸𸮰� �����޸𸮱����̱� ������ memcpy�� ���־ �������. 
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

