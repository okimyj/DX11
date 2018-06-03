#include "stdafx.h"
#include "SaveLoadMgr.h"

#include "ScriptMgr.h"

#include "Scene.h"
#include "SceneMgr.h"
#include "Layer.h"
#include "GameObject.h"
#include "Component.h"
#include "Script.h"
#include "prefab.h"

#include "Transform.h"
#include "MeshRenderer.h"
#include "Collider2D.h"
#include "Animator.h"
#include "Camera.h"
CSaveLoadMgr::CSaveLoadMgr()
{
}

CSaveLoadMgr::~CSaveLoadMgr()
{
}
//== Save ============================================================//
void CSaveLoadMgr::SaveScene(const wstring & _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb");
	if (NULL == pFile)
		assert(NULL);

	//-- Save Resource.
	CResMgr::GetInst()->SaveResource(pFile);

	//-- Save Prefab.
	map<wstring, CResPtr<CPrefab>>& mapPrefab = CResMgr::GetInst()->GetPrefabMap();
	UINT iCount = mapPrefab.size();
	WriteUINT(iCount, pFile);
	map<wstring, CResPtr<CPrefab>>::iterator prefabIter = mapPrefab.begin();
	for (; prefabIter != mapPrefab.end(); ++prefabIter)
	{
		WriteResourceKey((CRes*)prefabIter->second, pFile);
		SaveGameObject(prefabIter->second->gameObject(), pFile);
	}

	//-- Save Scene.
	CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
	//-- Layer Count.
	iCount = pScene->GetLayerCount();
	WriteUINT(iCount, pFile);
	vector<CLayer*>& vecLayer = pScene->GetVecLayer();
	for (UINT i = 0; i < vecLayer.size(); ++i)
	{
		if (NULL != vecLayer[i])
			SaveLayer(vecLayer[i], pFile);
	}
	fclose(pFile);
}

void CSaveLoadMgr::SaveLayer(CLayer * _pLayer, FILE * _pFile)
{
	// Layer Index.
	WriteUINT(_pLayer->GetLayerIndex() , _pFile);
	// Layer name.
	WriteWString(_pLayer->GetLayerName(), _pFile);
	// Parent Obj Count.
	list<CGameObject*> listParent = _pLayer->GetParentObjList();
	WriteUINT(listParent.size(), _pFile);
	// Save Parent Obj
	list<CGameObject*>::iterator iter = listParent.begin();
	for (; iter != listParent.end(); ++iter)
	{
		SaveGameObject((*iter), _pFile);
	}
}

void CSaveLoadMgr::SaveGameObject(CGameObject * _pObj, FILE * _pFile)
{
	// Tag.
	WriteWString(_pObj->GetTag(), _pFile);
	// Component.
	UINT i = (UINT)COMPONENT_TYPE::TRANSFORM;
	for (i; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pComp = _pObj->GetComponent((COMPONENT_TYPE)i);
		if (NULL == pComp)
			continue;
		pComp->Save(_pFile);
	}

	// Load 할 때 COMPONENT_TYPE::END 를 만나면 Component 마감으로 간주.
	WriteUINT((UINT)COMPONENT_TYPE::END, _pFile);

	// Script.
	list<CScript*> listScript = _pObj->GetScriptList();
	WriteUINT(listScript.size(), _pFile);
	list<CScript*>::iterator scriptIter = listScript.begin();
	for (; scriptIter != listScript.end(); ++scriptIter)
	{
		WriteWString(CScriptMgr::GetScriptName(*scriptIter), _pFile);
		(*scriptIter)->Save(_pFile);
	}
	// Child Count.
	list<CGameObject*> listChild = _pObj->GetChildList();
	WriteUINT(listChild.size(), _pFile);
	list<CGameObject*>::iterator childIter = listChild.begin();
	for (; childIter != listChild.end(); ++childIter)
	{
		SaveGameObject((*childIter), _pFile);
	}
}
//== Load ============================================================//
void CSaveLoadMgr::LoadScene(const wstring & _strFilePath)
{
	FILE* pFile = NULL;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");
	if (NULL == pFile)
		assert(NULL);
	// Resource Load.
	CResMgr::GetInst()->LoadResource(pFile);
	//-- Load Prefab.
	UINT iCount = ReadUINT(pFile);
	wstring strKey;
	for (UINT i = 0; i < iCount; ++i)
	{
		strKey = ReadWString(pFile);
		CGameObject* pObj = LoadGameObject(pFile);
		CResMgr::GetInst()->AddPrefab(strKey, pObj);
	}

	//-- Load Scene.
	CScene* pScene = new CScene;
	// Layer Count.
	iCount = ReadUINT(pFile); 
	for (UINT i = 0; i < iCount; ++i)
	{
		CLayer* pLayer = LoadLayer(pFile);
		pScene->AddLayer(pLayer);
	}
	CSceneMgr::GetInst()->ChangeScene(pScene);
	
	fclose(pFile);
}


CLayer * CSaveLoadMgr::LoadLayer(FILE * _pFile)
{
	CLayer* pLayer = new CLayer;
	// Layer Index.
	pLayer->SetLayerIndex(ReadUINT(_pFile));
	// Layer Name.
	pLayer->SetLayerName(ReadWString(_pFile));
	// Parent Object Count
	UINT iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		CGameObject* pObj = LoadGameObject(_pFile);
		pLayer->AddGameObject(pObj);
	}
	return pLayer;
}

CGameObject * CSaveLoadMgr::LoadGameObject(FILE * _pFile)
{
	CGameObject* pObj = new CGameObject;
	// Tag.
	pObj->SetTag(ReadWString(_pFile));
	// Component.
	UINT iType = 0;
	CComponent* pComp = NULL;
	while (iType != (UINT)COMPONENT_TYPE::END)
	{
		iType = ReadUINT(_pFile);
		switch (iType)
		{
		case (UINT)COMPONENT_TYPE::TRANSFORM:
			pObj->AddComponent<CTransform>(new CTransform)->Load(_pFile);
			break;
		case (UINT)COMPONENT_TYPE::MESHRENDERER:
			pObj->AddComponent<CMeshRenderer>(new CMeshRenderer)->Load(_pFile);
			break;
		case (UINT)COMPONENT_TYPE::CAMERA:
			pObj->AddComponent<CCamera>(new CCamera)->Load(_pFile);
			break;
		case (UINT)COMPONENT_TYPE::COLLIDER_2D:
			pObj->AddComponent<CCollider2D>(new CCollider2D)->Load(_pFile);
			break;
		case (UINT)COMPONENT_TYPE::COLLIDER_3D:
			
			break;
		case (UINT)COMPONENT_TYPE::ANIMATOR:
			pObj->AddComponent<CAnimator>(new CAnimator)->Load(_pFile);
			break;
		}
	}
	
	// Script.
	wstring strScriptName;
	UINT iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		strScriptName = ReadWString(_pFile);
		CScript* pScript = CScriptMgr::GetScript(strScriptName);
		pObj->AddComponent<CScript*>(pScript)->Load(_pFile);
	}
	// Child Count.
	iCount = ReadUINT(_pFile);
	for (UINT i = 0; i < iCount; ++i)
	{
		CGameObject* pChild = LoadGameObject(_pFile);
		pChild->SetParent(pObj);
	}
	
	return pObj;
}
