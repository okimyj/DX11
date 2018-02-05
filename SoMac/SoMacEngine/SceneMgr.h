#pragma once
#include "global.h"
class CScene;
class CGameObject;
class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_pCurScene;
	CScene*		m_pPrevScene;
public :
	
public:
	void Init();
	
	int Update();
	void Render();
	void AddGameObject(CGameObject* _pObj, const wstring& _strLayerName=L"");
	void RemoveGameObject(CGameObject* _pObj, const wstring& _strLayerName = L"");
//	void ChangeScene()

public:
	CScene* GetCurScene() { return m_pCurScene; }
#ifdef _DEBUG
public:
	void CreateTestScene();
	void CreateMaterial();
	void CreateGameObject();
#endif // _DEBUG

};

