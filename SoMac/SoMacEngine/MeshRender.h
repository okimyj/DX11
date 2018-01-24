#pragma once
#include "Component.h"
#include "ResPtr.h"
class CMesh;
class CShader;
class CMeshRender :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	CShader*					m_pShader;
public:
	virtual int Update() { return 0; }
	virtual void Render();
	
public:
	void SetShader(CShader* _pShader) { m_pShader = _pShader; }
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
public:
	CMeshRender();
	virtual ~CMeshRender();
};

