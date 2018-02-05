#pragma once
#include "Scene.h"
class CPrefab;
class CGameObject;
class CPlayerScript;
class CTestScene :
	public CScene
{
private:
	float								m_fAccureDT;
	CPrefab*						m_pEnemyPrefab;
	CPrefab*						m_pItemPrefab;
	list<CGameObject*>		m_listEnemyPool;
	list<CGameObject*>		m_listItemPool;
	CPlayerScript*				m_pPlayer;
public:
	virtual void Init();

private:
	virtual int Update();
	void CreateMaterial();
	void CreatePrefab();
	void CreateGameObject();

	CGameObject* PopEnemyObj();
	CGameObject* CreateEnemy();

	CGameObject* PopItemObj();
	CGameObject* CreateItem();

	void CheckCollide();

public:
	void PushEnemyObj(CGameObject* _pObj);
	void PushItemObj(CGameObject* _pObj);
public:
	CTestScene();
	virtual ~CTestScene();
};

