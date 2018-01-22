#include "ShaderMgr.h"
#include "PathMgr.h"
#include "Shader.h"

CShaderMgr::CShaderMgr()
{

}


CShaderMgr::~CShaderMgr()
{
	Safe_Delete_Map(m_mapShader);
}

void CShaderMgr::Init()
{
	// == Create Shader ================================
	wstring strPath = CPathMgr::GetResourcePath();
	strPath += L"Shader\\Standard.fx";

	CShader* pShader = new CShader();
	pShader->CreateVertexShader(strPath, "VS_Color", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Color", 5, 0);

	CShaderMgr::GetInst()->AddShader(L"ColorShader", pShader);
}

int CShaderMgr::AddShader(wstring _strKey, CShader * _pShader)
{
	CShader* pShader = FindShader(_strKey);
	if (NULL != pShader)
		return RET_FAILED;

	m_mapShader.insert(make_pair(_strKey, _pShader));

	return RET_SUCCESS;
}

CShader * CShaderMgr::FindShader(wstring _strKey)
{
	map<wstring, CShader*>::iterator iter = m_mapShader.find(_strKey);

	if (iter == m_mapShader.end())
		return NULL;


	return iter->second;
}
