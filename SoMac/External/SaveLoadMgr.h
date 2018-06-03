#pragma once
#include "define.h"

class CLayer;
class CGameObject;
class CSaveLoadMgr
{
	SINGLE(CSaveLoadMgr);
public:
	void SaveScene(const wstring& _strFilePath);
	void LoadScene(const wstring& _strFilePath);
private:
	void SaveLayer(CLayer* _pLayer, FILE* _pFile);
	CLayer* LoadLayer(FILE* _pFile);
	void SaveGameObject(CGameObject* _pObj, FILE* _pFile);
	CGameObject* LoadGameObject(FILE* _pFile);
	// scene �� ���� �Ѵ�. -> Scene�� ���Ե� Layer�� �����Ѵ�. 
	// �ش� Scene ������ ����ϴ� GameObject..... 
	// ��� Object�� Prefab �̴�. 
	// Prefab�� �����Ѵ�.

};

