#pragma once
#include "Scene.h"
class CPrefab;
class CGameObject;
class CTestScene :
	public CScene
{
private:
	float								m_fAccureDT;
	CPrefab*						m_pEnemyPrefab;
	list<CGameObject*>		m_listEnemyPool;
public:
	virtual void Init();

private:
	virtual int Update();
	void CreateMaterial();
	void CreatePrefab();
	void CreateGameObject();

	CGameObject* PopEnemyObj();
	CGameObject* CreateEnemy();
public:
	void PushEnemyObj(CGameObject* _pObj);
public:
	CTestScene();
	virtual ~CTestScene();
};

