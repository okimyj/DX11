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
	Vec3 vProj[4] = {};
	Vec3 vSource[4] = {};
	Vec3 vCenter = _pRightCol->GetWorldPos() - _pLeftCol->GetWorldPos();
	GetProjAxis(_pLeftCol->GetWorldMatrix(), vProj, vSource);		// 왼쪽 충돌체의 투영축, 투영 벡터 가져오기.
	GetProjAxis(_pRightCol->GetWorldMatrix(), vProj+2, vSource+2);		// 오른쪽 충돌체의 투영축, 투영 벡터 가져오기.

	// 내적 할거임 내적을 하는 이유 : 
	// 벡터끼리 내적을 한다. -> 각각 요소끼리 곱한 총합.
	// x*x1 + y*y1 + z*z1  // 내적의 결과 값은 힘은 없어지고 방향만 남는다. (스칼라)
	// == A벡터의 길이 * B 벡터의 길이 * cos세타 ( 밑변/빗변 )
	
	for (int i = 0; i < 4; ++i)
	{
		float fDist = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			// source벡터를 Proj 벡터 쪽으로 투영시켰을때의 길이.
			fDist += abs(vSource[j].Dot(vProj[i]));
		}
		fDist /= 2.f;
		// 현재의 투영축으로 center vector를 내적시킨다.
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
	// 원본의 좌표. 원래는 mesh 에 접근해서 가져와도 되는데.. 어차피 바뀔 일 거의 없으니 그냥 이렇게 하자. 나중에 수정.
	Vec3 vLocal[4] = { Vec3(-0.5f, -0.5f, 0.f), Vec3(-0.5f, 0.5f, 0.f)
								, Vec3(0.5f, 0.5f, 0.f), Vec3(0.5f, -0.5f, 0.f) };
	Vec3 vOut1 = XMVector3TransformCoord(vLocal[2].Convert(), _matWorld);
	Vec3 vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);

	_vSource[0] = vOut1 - vOut2;			// 투영 시킬 벡터. Local 1 -> 2 로 향하는 벡터.
	_vSource[0].z = 0.f;						// 2D니까 z값 무시. 평면으로 끌어오면 사선으로 틀어져서 겹치지 않았더라도 겹쳐보이니까.
	_vProj[0] = _vSource[0];				
	_vProj[0].Normalize();	// 투영 축.

	vOut1 = XMVector3TransformCoord(vLocal[0].Convert(), _matWorld);
	vOut2 = XMVector3TransformCoord(vLocal[1].Convert(), _matWorld);
	
	_vSource[1] = vOut1 - vOut2;		// 투영 시킬 벡터. Local1 -> 0 으로 향하는 벡터.
	_vSource[1].z = 0.f;
	_vProj[1] = _vSource[1];
	_vProj[1].Normalize();		// 투영 축.
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
