#include "CollisionMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "Collider.h"

CCollisionMgr::CCollisionMgr()
	: m_arrColMatrix{}
{
}


CCollisionMgr::~CCollisionMgr()
{
}

int CCollisionMgr::Update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CLayer*>& vecLayer = pCurScene->GetVecLayer();
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if ((m_arrColMatrix[i] >> j) & 1)
			{
				CollisionLayer(vecLayer[i], vecLayer[j]);
			}
		}

	}
	return 0;
}

void CCollisionMgr::CollisionLayer(CLayer * _pLeft, CLayer * _pRight)
{
	list<CGameObject*>& listLeft = _pLeft->GetObjList();
	list<CGameObject*>& listRight = _pRight->GetObjList();

	list<CGameObject*>::iterator iterLeft = listLeft.begin();
	list<CGameObject*>::iterator iterRight;
	CCollider* pLeft = NULL;
	CCollider* pRight = NULL;

	for (; iterLeft != listLeft.end(); ++iterLeft)
	{
		pLeft = (*iterLeft)->GetCollider();
		if (NULL == pLeft)
			continue;
		iterRight = listRight.begin();
		for (; iterRight != listRight.end(); ++iterRight)
		{
			pRight = (*iterRight)->GetCollider();
			if (NULL == pRight || pLeft->Is2DCollider() != pRight->Is2DCollider())
				continue;
			
			if (pRight->GetColID() < pLeft->GetColID())
			{
				CCollider* pTemp;
				pTemp = pLeft;
				pLeft = pRight;
				pRight = pTemp;
			}
			
			COL_ID id;
			id.iLeftID = pLeft->GetColID();
			id.iRightID = pRight->GetColID();

			map<ULONGLONG, bool>::iterator iterID = m_mapColID.find(id.llID);
			bool bPrevCollided = false;
			if (iterID == m_mapColID.end())
			{
				m_mapColID.insert(make_pair(id.llID, false));
				iterID = m_mapColID.find(id.llID);
			}
			else
				bPrevCollided = iterID->second;
			if (IsCollision(pLeft, pRight))
			{
				//�浹 ����.
				if (bPrevCollided)
				{
					// �������� �浹 �߾���. �浹 ��.
					pLeft->OnCollision(pRight);
					pRight->OnCollision(pLeft);
				}
				else
				{
					// ó�� �浹 �ߴ�. 
					pLeft->OnCollisionEnter(pRight);
					pRight->OnCollisionEnter(pLeft);
					iterID->second = true;
				}
			}
			else
			{
				// �浹 ����.
				if (bPrevCollided)
				{
					// ������ �浹 �߾���. �浹���� �� �����. 
					pLeft->OnCollisionExit(pRight);
					pRight->OnCollisionExit(pLeft);
					iterID->second = false;
				}
			}
		}
	}

}

bool CCollisionMgr::IsCollision(CCollider * _pLeftCol, CCollider * _pRightCol)
{
	Vec3 vProj[4] = {};
	Vec3 vSource[4] = {};
	Vec3 vCenter = _pRightCol->GetWorldPos() - _pLeftCol->GetWorldPos();
	GetProjAxis(_pLeftCol->GetWorldMatrix(), vProj, vSource);		// ���� �浹ü�� ������, ���� ���� ��������.
	GetProjAxis(_pRightCol->GetWorldMatrix(), vProj+2, vSource+2);		// ������ �浹ü�� ������, ���� ���� ��������.

	// ���� �Ұ��� ������ �ϴ� ���� : 
	// ���ͳ��� ������ �Ѵ�. -> ���� ��ҳ��� ���� ����.
	// x*x1 + y*y1 + z*z1  // ������ ��� ���� ���� �������� ���⸸ ���´�. (��Į��)
	// == A������ ���� * B ������ ���� * cos��Ÿ ( �غ�/���� )
	
	for (int i = 0; i < 4; ++i)
	{
		float fDist = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			// source���͸� Proj ���� ������ �������������� ����.
			fDist += abs(vSource[j].Dot(vProj[i]));
		}
		fDist /= 2.f;
		// ������ ���������� center vector�� ������Ų��.
		float fCenter = abs(vCenter.Dot(vProj[i]));
		if (fCenter > fDist)
			return false;
	}
	return true;
}

void CCollisionMgr::GetProjAxis(const Matrix & _matWorld, Vec3 * _vProj, Vec3 * _vSource)
{
	/*		1 ------ 2
			|		    |
			|		    |
			0 ------ 3	*/
	// ������ ��ǥ. ������ mesh �� �����ؼ� �����͵� �Ǵµ�.. ������ �ٲ� �� ���� ������ �׳� �̷��� ����. ���߿� ����.
	Vec3 vLocal[4] = { Vec3(-0.5f, -0.5f, 0.f), Vec3(-0.5f, 0.5f, 0.f)
								, Vec3(0.5f, 0.5f, 0.f), Vec3(0.5f, -0.5f, 0.f) };
	Vec3 vOut1 = XMVector3TransformCoord(vLocal[2].Convert(), _matWorld);
	Vec3 vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);

	_vSource[0] = vOut1 - vOut2;			// ���� ��ų ����. Local 1 -> 2 �� ���ϴ� ����.
	_vSource[0].z = 0.f;						// 2D�ϱ� z�� ����. ������� ������� �缱���� Ʋ������ ��ġ�� �ʾҴ��� ���ĺ��̴ϱ�.
	_vProj[0] = _vSource[0];				
	_vProj[0].Normalize();	// ���� ��.

	vOut1 = XMVector3TransformCoord(vLocal[0].Convert(), _matWorld);
	vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);
	
	_vSource[1] = vOut1 - vOut2;		// ���� ��ų ����. Local1 -> 0 ���� ���ϴ� ����.
	_vSource[1].z = 0.f;
	_vProj[1] = _vSource[1];
	_vProj[1].Normalize();		// ���� ��.
}

int CCollisionMgr::ToggleCollsionLayer(const wstring & _strLeft, const wstring & _strRight)
{
	CScene * pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeft = pCurScene->FindLayer(_strLeft);
	CLayer* pRight = pCurScene->FindLayer(_strRight);
	if (NULL == pLeft || NULL == pRight)
		return RET_FAILED;
	
	UINT iLeftIdx = pLeft->GetLayerIndex();
	UINT iRightIdx = pLeft->GetLayerIndex();
	if (iRightIdx < iLeftIdx)
	{
		UINT iTemp = iLeftIdx;
		iLeftIdx = iRightIdx;
		iRightIdx = iTemp;
	}
	if (m_arrColMatrix[iLeftIdx] & (1 << iRightIdx))
		m_arrColMatrix[iLeftIdx] &= ~(1 << iRightIdx);		// reset.
	else
		m_arrColMatrix[iLeftIdx] |= (1 << iRightIdx);			// set.


	return RET_SUCCESS;
}

int CCollisionMgr::SetCollsionLayer(const wstring & _strLeft, const wstring & _strRight)
{
	CScene * pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeft = pCurScene->FindLayer(_strLeft);
	CLayer* pRight = pCurScene->FindLayer(_strRight);
	if (NULL == pLeft || NULL == pRight)
		return RET_FAILED;

	UINT iLeftIdx = pLeft->GetLayerIndex();
	UINT iRightIdx = pRight->GetLayerIndex();
	if (iRightIdx < iLeftIdx)
	{
		UINT iTemp = iLeftIdx;
		iLeftIdx = iRightIdx;
		iRightIdx = iTemp;
	}
	m_arrColMatrix[iLeftIdx] |= (1 << iRightIdx);			// set.
	return RET_SUCCESS;
}

int CCollisionMgr::ResetCollsionLayer(const wstring & _strLeft, const wstring & _strRight)
{
	CScene * pCurScene = CSceneMgr::GetInst()->GetCurScene();
	CLayer* pLeft = pCurScene->FindLayer(_strLeft);
	CLayer* pRight = pCurScene->FindLayer(_strRight);
	if (NULL == pLeft || NULL == pRight)
		return RET_FAILED;

	UINT iLeftIdx = pLeft->GetLayerIndex();
	UINT iRightIdx = pLeft->GetLayerIndex();
	if (iRightIdx < iLeftIdx)
	{
		UINT iTemp = iLeftIdx;
		iLeftIdx = iRightIdx;
		iRightIdx = iTemp;
	}
	m_arrColMatrix[iLeftIdx] &= ~(1 << iRightIdx);		// reset.
	return RET_SUCCESS;
}
