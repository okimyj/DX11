#pragma once
#include "global.h"
// �ϳ��� Scene ���� �������� Layer�� ���� �� �ִ�. 
// ��ϵ� Layer �� ���� �浹üũ ���θ� ���� �� �� �ִ�. 
class CLayer;
struct tLayerInfo 
{
	CLayer*		pLayer;
	UINT			iLayerIdx;
};
class CScene
{
private:
	map<wstring, tLayerInfo>		m_mapLayer;
	// set : �ڷᱸ���� �ϳ�. map�� ������ Ž�� ����� ����(���������Ʈ��:������ȸ)
	// map�� ���������� key, value pair�� �ƴ϶� key �� ���� ������. �Ƹ� push, pop �����ε�.
	set<UINT>							m_setLayerIdx;
public:
	void Awake();
	void Start();
	int Update();
	int LateUpdate();
	int FinalUpdate();
	void Render();
public :
	int AddLayer(const wstring& _strLayerName);
	CLayer* FindLayer(const wstring& _strLayerName);
private:
	UINT GetLayerIndex();
public:
	CScene();
	~CScene();
};

