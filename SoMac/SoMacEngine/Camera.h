#pragma once
#include "Component.h"
union uInstID
{
	struct {
		UINT iMesh;
		UINT iMtrl;
	};
	ULONG64 llID;
};

class CLayer;
class CCamera :
	public CComponent
{
private:
	Matrix		m_matView;
	Matrix		m_matProj;

	bool			m_bPerspective;
	// 원근
	float			m_fFOV;			// Field Of View.
	// 직교
	float			m_fWidth;
	float			m_fHeight;
	float			m_fScale;
	// 공통
	float			m_fNear;
	float			m_fFar;

	UINT			m_iRenderLayerFlag;

	// Instancing Group.
	map<ULONG64, vector<CGameObject*>>	m_mapInstGroup;
	vector<CGameObject*>				m_vecSingleObj;
	vector<CGameObject*>				m_vecToolObj;

public:
	
	virtual int Update();
	virtual int LateUpdate();
	void ApplyData();
	void ToggleRenderTargetLayer(const wstring& _strLayerName);
	void AddRenderTargetLayer(const wstring& _strLayerName);
	void RemoveRenderTargetLayer(const wstring& _strLayerName);
	
	bool IsRenderTargetLayer(const wstring& _strLayerName);
	bool IsRenderTargetLayer(CLayer* _pLayer);

	void SetScale(float _fScale) { m_fScale = _fScale; }
	float GetScale() { return m_fScale; }

	void SetFar(float _fFar) { m_fFar = _fFar; }
	float GetFar() { return m_fFar; }

	const Matrix& GetProjMatrix() { return m_matProj; }
	const Matrix& GetViewMatrix() { return m_matView; }

	void AddToolObj(CGameObject* _pObj) { m_vecToolObj.push_back(_pObj); }
public:
	void UpdateInstancing();
public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);
	virtual CLONE(CCamera);
public:
	CCamera();
	~CCamera();
};

