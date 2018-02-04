#pragma once
#include "global.h"
class CShader;
class CSampler;
class CBlendState;
class CShaderMgr
{
	SINGLE(CShaderMgr);
private:
	map<wstring, CBlendState*>		m_mapBlendState;
	map<wstring, CSampler*>			m_mapSampler;
	map<wstring, CShader*>			m_mapShader;
	
public:
	void Init();


public :
	CBlendState* FindBlendState(const wstring& _strKey);
	CShader* FindShader(const wstring& _strKey);
	CSampler* FindSampler(const wstring& _strKey);
private:
	int AddBlendState(const wstring& _strKey, CBlendState* _pState);
	int AddShader(const wstring& _strKey, CShader* _pShader);
	int AddSampler(const wstring& _strKey, CSampler* _pSampler);

	void CreateBlendState();
	void CreateSampler();
	void CreateShader();
	
};

