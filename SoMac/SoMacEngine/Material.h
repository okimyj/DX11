#pragma once
#include "Res.h"
struct tShaderParam_EX : public tShaderParam 
{
	void* pData;
};
class CShader;
class CMaterial :
	public CRes
{
private:
	CShader*									m_pShader;
	vector<tShaderParam_EX>			m_vecShaderParam;
public:
	void SetShader(CShader* _pShader);
	CShader* GetShader() { return m_pShader; }
private:
	void ClearShaderParam();
	void ConvertShaderParam();

public:
	void SetParamData(SHADER_PARAM _eParam, void* _pData);
public:
	virtual void ApplyData();
	virtual CMaterial* Clone() { return new CMaterial(*this); }
public:
	CMaterial();
	CMaterial(const CMaterial& _pOther);
	virtual ~CMaterial();
};

