#pragma once
#include "global.h"
class CGameObject;
class CTransform;
class CMeshRender;
class CComponent
{
private:
	CGameObject*	m_pObj;
public:
	virtual void Awake() {};
	virtual void Start() {};
	virtual int Update() = 0;
	virtual int LateUpdate() { return 0; }
	virtual int FinalUpdate() { return 0; }
	virtual void Render() {};
private:
	void SetGameObject(CGameObject* _pObj) { m_pObj = _pObj; }

protected:
	CGameObject* GetGameObject() { return m_pObj; }
	CTransform* Transform();
	CMeshRender* MeshRender();
	



public:
	CComponent();
	virtual ~CComponent();
	
	friend class CGameObject;
};

