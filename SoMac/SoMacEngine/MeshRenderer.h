#pragma once
#include "Component.h"
#include "ResPtr.h"
class CMesh;
class CMaterial;
class CMeshRenderer :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	CMaterial*					m_pMaterial;
	RASTERIZE_TYPE		m_eRSType;
public:
	// 멤버 변수들이 pointer 들이지만 다 리소스 포인터임. 하나만 있어야 하는것들. 
	virtual CMeshRenderer* Clone() { return new CMeshRenderer(*this); }
	virtual int Update() { return 0; }
	virtual void Render();
	
public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CMaterial* _pMaterial) { m_pMaterial = _pMaterial; }
	void SetRSType(RASTERIZE_TYPE _eType) { m_eRSType = _eType; }
	CMaterial* GetMaterial() { return m_pMaterial;	}
public:
	CMeshRenderer();
	virtual ~CMeshRenderer();
};

