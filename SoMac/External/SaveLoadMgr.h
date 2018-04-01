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

	// scene �� ���� �Ѵ�. -> Scene�� ���Ե� Layer�� �����Ѵ�. 
	// �ش� Scene ������ ����ϴ� GameObject..... 
	// ��� Object�� Prefab �̴�. 
	// Prefab�� �����Ѵ�.

};

