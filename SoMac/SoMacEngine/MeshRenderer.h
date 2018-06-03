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
	CResPtr<CMaterial>  m_pMtrl;
	RASTERIZE_TYPE		m_eRSType;

public:
	// 멤버 변수들이 pointer 들이지만 다 리소스 포인터임. 하나만 있어야 하는것들. 
	virtual CLONE(CMeshRenderer);
	virtual int Update() { return 0; }
	virtual void Render();

public:
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetMaterial(CMaterial* _pMaterial) { m_pMtrl = _pMaterial; }
	void SetRSType(RASTERIZE_TYPE _eType) { m_eRSType = _eType; }
	
	CMesh* GetMesh() { return m_pMesh; };
	CMaterial* GetSharedMaterial() { return m_pMtrl; }
	CMaterial* GetMaterial();
	RASTERIZE_TYPE GetRSType() { return m_eRSType; }
	ULONG64 GetInstID();
public:
	virtual void Save(FILE* _pFile);
	virtual void Load(FILE* _pFile);
public:
	CMeshRenderer();
	CMeshRenderer(const CMeshRenderer& _pOther);
	virtual ~CMeshRenderer();
};

