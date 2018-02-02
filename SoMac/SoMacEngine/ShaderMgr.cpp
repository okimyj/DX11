#include "ShaderMgr.h"
#include "PathMgr.h"
#include "Shader.h"
#include "Sampler.h"

CShaderMgr::CShaderMgr()
{

}


CShaderMgr::~CShaderMgr()
{
	Safe_Delete_Map(m_mapShader);
	Safe_Delete_Map(m_mapSampler);
}

void CShaderMgr::Init()
{
	CreateSampler();
	CreateShader();
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

int CShaderMgr::AddSampler(wstring _strKey, CSampler * _pSampler)
{
	CSampler* pSampler = FindSampler(_strKey);
	if (NULL != pSampler)
		return RET_FAILED;
	m_mapSampler.insert(make_pair(_strKey, _pSampler));
	return RET_SUCCESS;
}

CSampler * CShaderMgr::FindSampler(wstring _strKey)
{
	map<wstring, CSampler*>::iterator iter = m_mapSampler.find(_strKey);
	if (iter == m_mapSampler.end())
		return NULL;
	return iter->second;
}

void CShaderMgr::CreateSampler()
{
	// == Create Default Sampler ==============================
	CSampler* pSampler = CSampler::Create(D3D11_FILTER_ANISOTROPIC, 0, D3D11_TEXTURE_ADDRESS_WRAP, D3D11_TEXTURE_ADDRESS_WRAP);
	AddSampler(L"DefaultSampler", pSampler);
}


void CShaderMgr::CreateShader()
{
	// == Create Color Shader ================================
	CShader* pShader = new CShader();
	wstring strPath = CPathMgr::GetResourcePath();
	strPath += L"Shader\\Standard.fx";
	pShader->CreateVertexShader(strPath, "VS_Color", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Color", 5, 0);

	CShaderMgr::GetInst()->AddShader(L"ColorShader", pShader);

	// == Create Texture Shader ===============================
	pShader = new CShader();
	strPath = CPathMgr::GetResourcePath();
	strPath += L"Shader\\Standard.fx";
	pShader->CreateVertexShader(strPath, "VS_Texture", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Texture", 5, 0);
	pShader->AddSampler(FindSampler(L"DefaultSampler"), ((UINT)SHADER_TYPE::ST_PIXEL));
	pShader->AddShaderParam(SHADER_PARAM::TEXTURE_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::INT_0, (UINT)SHADER_TYPE::ST_PIXEL);
	CShaderMgr::GetInst()->AddShader(L"TextureShader", pShader);
}
