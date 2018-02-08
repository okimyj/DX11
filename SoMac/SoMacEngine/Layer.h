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
	list<CGameObject*>		m_listParentObj;			// 최 상위 부모 오브젝트 리스트.  // 최상위 부모로부터 awake, start, update.. 등등 호출 받는다.
	list<CGameObject*>		m_listObj;						// 전체 오브젝트 리스트.

	UINT								m_iIdx;
	bool								m_bZOrder;			// z-order를 사용 할지 안할지.


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

	void AddGameObject(CGameObject* _pObj, bool _bApplyChild=true);
	void RemoveGameObject(CGameObject* _pObj);
	void RemoveParentObject(CGameObject* _pObj);
	
	void SetZOrder(bool _bZorder) { m_bZOrder = _bZorder; }
private:
	
public:
	CLayer();
	~CLayer();
	friend class CScene;
	friend class CTestScene;
};

