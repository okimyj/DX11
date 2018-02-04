#pragma once
#include "global.h"
// 하나의 Scene에는 여러개의 Layer가 있다.
// 하나의 Layer 에는 여러개의 GameObject가 배치된다. 
// Layer간의 충돌체크 처리가 가능하다. 
class CScene;
class CGameObject;
class CLayer
{
private:
	wstring							m_strLayerName;
	UINT								m_iIdx;
	list<CGameObject*>		m_listObj;
public:
	void Awake();
	void Start();
	int Update();
	int LateUpdate();
	int FinalUpdate();
	void Render();
private:
	void SetLayerIndex(UINT _iIdx) { m_iIdx = _iIdx; }
	void SetLayerName(const wstring& _strName) { m_strLayerName = _strName; }
	list<CGameObject*>& GetObjList() { return m_listObj; }
public:
	UINT GetLayerIndex() { return m_iIdx; }
	const wstring& GetLayerName() { return m_strLayerName; }
	void AddGameObject(CGameObject* _pObj);
	void RemoveGameObject(CGameObject* _pObj);
public:
	CLayer();
	~CLayer();
	friend class CScene;
};

