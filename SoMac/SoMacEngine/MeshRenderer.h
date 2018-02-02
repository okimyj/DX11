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
	// ��� �������� pointer �������� �� ���ҽ� ��������. �ϳ��� �־�� �ϴ°͵�. 
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

