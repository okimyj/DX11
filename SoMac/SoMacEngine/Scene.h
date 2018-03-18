#pragma once
#include "global.h"
// 하나의 Scene 에는 여러개의 Layer가 들어올 수 있다. 
// 등록된 Layer 들 간의 충돌체크 여부를 결정 할 수 있다. 
class CLayer;
class CGameObject;
class CScene
{
private:
	map<wstring, CLayer*>		m_mapLayer;
	vector<CLayer*>				m_vecLayer;		// array로 해도 상관 x.
	// set : 자료구조의 하나. map과 동일한 탐색 방식을 가짐(레드블렉이진트리:중위순회)
	// map과 동일하지만 key, value pair가 아니라 key 값 만을 가진다. 아마 push, pop 개념인듯.
	set<UINT>						m_setLayerIdx;
	CGameObject*							m_pMainCamera;
public:
	virtual void Init() {}
	virtual void Awake();
	virtual void Start();
	virtual int Update();
	int LateUpdate();
	int FinalUpdate();
	void Render();
public :
	int AddLayer(const wstring& _strLayerName, bool _bZOrder = false);
	CLayer* FindLayer(const wstring& _strLayerName);
	CGameObject* FindObject(Vec2 _vWindowPos, Vec2 _vResolution, UINT _iMask=0);
	Vec2 ScreenToWorldPosition(Vec2 _vWindowPos, Vec2 _vResolution);
	CGameObject* GetMainCamera();
private:
private:
	void GetAllParentObjects(list<CGameObject*>& _listOut);
	UINT GetLayerIndex();
	vector<CLayer*>&	GetVecLayer() { return m_vecLayer; }
public:
	CScene();
	virtual ~CScene();
	friend class CCollisionMgr;
	friend class CHierachyTreeDlg;
};

