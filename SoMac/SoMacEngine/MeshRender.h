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
	RASTERIZE_TYPE		m_eRSType;
public:
	// ��� �������� pointer �������� �� ���ҽ� ��������. �ϳ��� �־�� �ϴ°͵�. 
	virtual CMeshRender* Clone() { return new CMeshRender(*this); }
	virtual int Update() { return 0; }
	virtual void Render();
	
public:
	void SetShader(CShader* _pShader) { m_pShader = _pShader; }
	void SetMesh(CMesh* _pMesh) { m_pMesh = _pMesh; }
	void SetTexture(CTexture* _pTexture) { m_pTexture = _pTexture; }
	void SetRSType(RASTERIZE_TYPE _eType) { m_eRSType = _eType; }
public:
	CMeshRender();
	virtual ~CMeshRender();
};

