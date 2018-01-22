#pragma once
#include "global.h"
class CShader;
class CShaderMgr
{
	SINGLE(CShaderMgr);
public:
	void Init();
private:
	map<wstring, CShader*>	m_mapShader;
public :
	int AddShader(wstring _strKey, CShader* _pShader);
	CShader* FindShader(wstring _strKey);

};

