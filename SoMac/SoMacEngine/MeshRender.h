#pragma once
#include "Component.h"
#include "ResPtr.h"
class CMesh;
class CTexture;
class CShader;
class CMeshRender :
	public CComponent
{
private:
	CResPtr<CMesh>		m_pMesh;
	CTexture*					m_pTexture;
	CShader*					m_pShader;
public:
	virtual int Update() { return 0; }
	virtual void Render();
	
public:
	void SetShader(CShader* _pShader) { m_pShader = _pShader; }
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }
public:
	CMeshRender();
	virtual ~CMeshRender();
};

