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
	UINT									m_arrColMatrix[MAX_LAYER];		// ·¹ÀÌ¾î collision check box.
	map<ULONGLONG, bool>	m_mapColID;

public:
	int Update();

private:
	void CollisionLayer(CLayer* _pLeft, CLayer* _pRight);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
public:
	int ToggleCollsionLayer(const wstring& _strLeft, const wstring& _strRight);
	int SetCollsionLayer(const wstring& _strLeft, const wstring& _strRight);
	int ResetCollsionLayer(const wstring& _strLeft, const wstring& _strRight);


};

