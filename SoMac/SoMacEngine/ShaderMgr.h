#pragma once
#include "global.h"
class CShader;
class CSampler;
class CShaderMgr
{
	SINGLE(CShaderMgr);
private:
	map<wstring, CShader*>	m_mapShader;
	map<wstring, CSampler*> m_mapSampler;
public:
	void Init();


public :
	CShader* FindShader(wstring _strKey);
	CSampler* FindSampler(wstring _strKey);
private:
	int AddShader(wstring _strKey, CShader* _pShader);
	int AddSampler(wstring _strKey, CSampler* _pSampler);
	void CreateSampler();
	void CreateShader();
};

