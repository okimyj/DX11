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
		for (UINT j = 0; j < MAX_LAYER; ++j)
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
			if (NULL == pRight || pLeft->GetColliderType() != pRight->GetColliderType())
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
				m_mapColID.insert(make_pair(id.llID, false));
			bPrevCollided = iterID->second;
			if (IsCollision(pLeft, pRight))
			{
				//충돌 했음.
				if (bPrevCollided)
				{
					// 이전에도 충돌 했었다. 충돌 중.
					pLeft->OnCollision(pRight);
					pRight->OnCollision(pLeft);
				}
				else
				{
					// 처음 충돌 했다. 
					pLeft->OnCollisionEnter(pRight);
					pRight->OnCollisionEnter(pLeft);
					iterID->second = true;
				}
			}
			else
			{
				// 충돌 안함.
				if (bPrevCollided)
				{
					// 이전에 충돌 했었다. 충돌에서 막 벗어났다. 
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
	return false;
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
	UINT iRightIdx = pLeft->GetLayerIndex();
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
