#pragma once
#include "global.h"
// �ϳ��� Scene ���� �������� Layer�� ���� �� �ִ�. 
// ��ϵ� Layer �� ���� �浹üũ ���θ� ���� �� �� �ִ�. 
class CLayer;
class CGameObject;
class CScene
{
private:
	map<wstring, CLayer*>		m_mapLayer;
	vector<CLayer*>				m_vecLayer;		// array�� �ص� ��� x.
	// set : �ڷᱸ���� �ϳ�. map�� ������ Ž�� ����� ����(���������Ʈ��:������ȸ)
	// map�� ���������� key, value pair�� �ƴ϶� key �� ���� ������. �Ƹ� push, pop �����ε�.
	set<UINT>						m_setLayerIdx;
	CGameObject*							m_pMainCamera;
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
	CGameObject* FindObject(Vec2 _vWindowPos, Vec2 _vResolution, UINT _iMask=0);
	Vec2 ScreenToWorldPosition(Vec2 _vWindowPos, Vec2 _vResolution);
	CGameObject* GetMainCamera();
private:
private:
	void GetAllParentObjects(list<CGameObject*>& _listOut);
	UINT GetLayerIndex();
	vector<CLayer*>&	GetVecLayer() { return m_vecLayer; }
public:
	CScene();
	virtual ~CScene();
	friend class CCollisionMgr;
	friend class CHierachyTreeDlg;
};

