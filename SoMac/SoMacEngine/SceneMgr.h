#pragma once
#include "global.h"
class CScene;
class CLayer;
class CGameObject;

class CSceneMgr
{
public:
	
	SINGLE(CSceneMgr);
private:
	CScene*		m_pCurScene;
	CScene*		m_pPrevScene;
#ifdef _SOMAC_TOOL
	using voidFunc = std::function<void()>;
	voidFunc m_updateCallback;
public:
	void SetUpdateCallback(const voidFunc& _func) { m_updateCallback = _func; }
private:
	void CallbackUpdate() { if (NULL != m_updateCallback)m_updateCallback(); };
#endif

public:
	void Init();
	void NotifyUpdate();
	int Update();
	void Render();
	void AddGameObject(CGameObject* _pObj, const wstring& _strLayerName=L"");
	void RemoveGameObject(CGameObject* _pObj, const wstring& _strLayerName = L"");
//	void ChangeScene()

public:
	CScene* GetCurScene() { return m_pCurScene; }
	CLayer* GetCurSceneLayer(const wstring& _strLayerName);


#ifdef _DEBUG
public:
	void CreateTestScene();
	void CreateMaterial();
	void CreateGameObject();
#endif // _DEBUG
	friend class CHierachyTreeDlg;
};

