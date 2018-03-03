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
	CMaterial*					m_pSharedMaterial;
	CMaterial*					m_pMaterial;
	CMaterial*					m_pCloneMaterial;
	RASTERIZE_TYPE		m_eRSType;
public:
	// ��� �������� pointer �������� �� ���ҽ� ��������. �ϳ��� �־�� �ϴ°͵�. 
	virtual CLONE(CMeshRenderer);
	virtual int Update() { return 0; }
	virtual void Render();

public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CMaterial* _pMaterial);
	void SetRSType(RASTERIZE_TYPE _eType) { m_eRSType = _eType; }


	CMesh* GetMesh() { return m_pMesh; }
	CMaterial* GetMaterial();
	CMaterial* GetSharedMaterial();
	RASTERIZE_TYPE GetRSType() { return m_eRSType; }
public:
	CMeshRenderer();
	CMeshRenderer(const CMeshRenderer& _pOther);
	virtual ~CMeshRenderer();
};

