#pragma once
#include "Component.h"
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
public:
	virtual int Update();
	virtual int LateUpdate();
	virtual int FinalUpdate();

	void ToggleRenderTargetLayer(CLayer* _pLayer);
	void AddRenderTargetLayer(CLayer* _pLayer);
	void RemoveRenderTargetLayer(CLayer* _pLayer);
	
	bool IsRenderTargetLayer(CLayer* _pLayer);
public:
	CCamera();
	~CCamera();
};

