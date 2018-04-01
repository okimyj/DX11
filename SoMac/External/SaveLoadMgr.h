#pragma once
#include "define.h"
class CSaveLoadMgr
{
	SINGLE(CSaveLoadMgr);
public:
	void SaveScene(const wstring& _strFilePath);
	void LoadScene(const wstring& _strFilePath);
private:
	void SaveLayer(CLayer* _pLayer, FILE* _pFile);

	// scene 을 저장 한다. -> Scene에 포함된 Layer를 저장한다. 
	// 해당 Scene 에서만 사용하는 GameObject..... 
	// 모든 Object는 Prefab 이다. 
	// Prefab을 저장한다.

};

