#pragma once
#include "global.h"
// �ϳ��� Scene ���� �������� Layer�� ���� �� �ִ�. 
// ��ϵ� Layer �� ���� �浹üũ ���θ� ���� �� �� �ִ�. 
class CLayer;
class CScene
{
private:
	map<wstring, CLayer*>		m_mapLayer;
	vector<CLayer*>				m_vecLayer;		// array�� �ص� ��� x.
	// set : �ڷᱸ���� �ϳ�. map�� ������ Ž�� ����� ����(���������Ʈ��:������ȸ)
	// map�� ���������� key, value pair�� �ƴ϶� key �� ���� ������. �Ƹ� push, pop �����ε�.
	set<UINT>						m_setLayerIdx;
public:
	virtual void Init() {}
	virtual void Awake();
	virtual void Start();
	virtual int Update();
	int LateUpdate();
	int FinalUpdate();
	void Render();
public :
	int AddLayer(const wstring& _strLayerName, bool _bZOrder = false);
	CLayer* FindLayer(const wstring& _strLayerName);
private:
	UINT GetLayerIndex();
public:
	CScene();
	virtual ~CScene();
};

