#pragma once
#include "global.h"
union COL_ID
{
	struct 
	{
		UINT	iLeftID;
		UINT iRightID;
	};
	ULONGLONG llID;
};
class CCollider;
class CLayer;

class CCollisionMgr
{
	SINGLE(CCollisionMgr);

private:
	UINT									m_arrColMatrix[MAX_LAYER];		// 레이어 collision check box.
	map<ULONGLONG, bool>	m_mapColID;

public:
	int Update();

private:
	void CollisionLayer(CLayer* _pLeft, CLayer* _pRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
	void GetProjAxis(const Matrix& _matWorld, Vec3* _vProj, Vec3* _vSource);		// 투영 축을 얻어오는 함수.
public:
	int ToggleCollsionLayer(const wstring& _strLeft, const wstring& _strRight);
	int SetCollsionLayer(const wstring& _strLeft, const wstring& _strRight);
	int ResetCollsionLayer(const wstring& _strLeft, const wstring& _strRight);


};

