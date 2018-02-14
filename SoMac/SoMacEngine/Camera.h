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
	// ����
	float			m_fFOV;			// Field Of View.
	// ����
	float			m_fWidth;
	float			m_fHeight;
	float			m_fScale;
	// ����
	float			m_fNear;
	float			m_fFar;

	UINT			m_iRenderLayerFlag;
public:
	virtual CLONE(CCamera);
	virtual int Update();
	virtual int LateUpdate();
	virtual int FinalUpdate();

	void ToggleRenderTargetLayer(const wstring& _strLayerName);
	void AddRenderTargetLayer(const wstring& _strLayerName);
	void RemoveRenderTargetLayer(const wstring& _strLayerName);
	
	bool IsRenderTargetLayer(const wstring& _strLayerName);
	bool IsRenderTargetLayer(CLayer* _pLayer);
public:
	CCamera();
	~CCamera();
};

