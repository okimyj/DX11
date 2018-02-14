#include "ShaderMgr.h"
#include "PathMgr.h"
#include "BlendState.h"
#include "Shader.h"
#include "Sampler.h"


CShaderMgr::CShaderMgr()
{

}


CShaderMgr::~CShaderMgr()
{
	Safe_Delete_Map(m_mapShader);
	Safe_Delete_Map(m_mapSampler);
	Safe_Delete_Map(m_mapBlendState);
}

void CShaderMgr::Init()
{
	CreateBlendState();
	CreateSampler();
	CreateShader();
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
	pShader->SetBlendState(FindBlendState(L"AlphaBlend"));

	pShader->AddShaderParam(SHADER_PARAM::TEXTURE_0, (UINT)SHADER_TYPE::ST_PIXEL);
	pShader->AddShaderParam(SHADER_PARAM::INT_0, (UINT)SHADER_TYPE::ST_PIXEL);

	CShaderMgr::GetInst()->AddShader(L"TextureShader", pShader);

	// == Create Collider Shader ===============================
	pShader = new CShader();
	strPath = CPathMgr::GetResourcePath();
	strPath += L"Shader\\Standard.fx";
	pShader->CreateVertexShader(strPath, "VS_Collider", 5, 0);
	pShader->CreatePixelShader(strPath, "PS_Collider", 5, 0);
	pShader->AddShaderParam(SHADER_PARAM::INT_0, (UINT)SHADER_TYPE::ST_PIXEL);
	CShaderMgr::GetInst()->AddShader(L"ColliderShader", pShader);
}


int CShaderMgr::AddBlendState(const wstring & _strKey, CBlendState * _pState)
{
	CBlendState* pState = FindBlendState(_strKey);
	if (NULL != pState)
		return RET_FAILED;

	m_mapBlendState.insert(make_pair(_strKey, _pState));

	return RET_SUCCESS;
}

CBlendState * CShaderMgr::FindBlendState(const wstring & _strKey)
{
	map<wstring, CBlendState*>::iterator iter = m_mapBlendState.find(_strKey);
	if (iter == m_mapBlendState.end())
		return NULL;

	return iter->second;
}
int CShaderMgr::AddShader(const wstring& _strKey, CShader * _pShader)
{
	CShader* pShader = FindShader(_strKey);
	if (NULL != pShader)
		return RET_FAILED;

	m_mapShader.insert(make_pair(_strKey, _pShader));

	return RET_SUCCESS;
}



CShader * CShaderMgr::FindShader(const wstring& _strKey)
{
	map<wstring, CShader*>::iterator iter = m_mapShader.find(_strKey);

	if (iter == m_mapShader.end())
		return NULL;


	return iter->second;
}

int CShaderMgr::AddSampler(const wstring& _strKey, CSampler * _pSampler)
{
	CSampler* pSampler = FindSampler(_strKey);
	if (NULL != pSampler)
		return RET_FAILED;
	m_mapSampler.insert(make_pair(_strKey, _pSampler));
	return RET_SUCCESS;
}

void CShaderMgr::CreateBlendState()
{
	CBlendState* pState = new CBlendState;
	pState->SetMRT(false);
	D3D11_RENDER_TARGET_BLEND_DESC tDesc = {};
	tDesc.BlendEnable = true;
	tDesc.BlendOp = D3D11_BLEND_OP_ADD;					// color blending 계산 방식. 
	tDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;				// 원본의 계수 옵션.
	tDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	// 목적지의 계수 옵션. // Inverse Source Alpha.

	tDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;			// alpha blending 계산 방식. 
	tDesc.SrcBlendAlpha = D3D11_BLEND_ONE;				
	tDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
	tDesc.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

	pState->AddRenderTargetBlendDesc(0, tDesc);
	// 원래는 8개 다 채워주어야 하는데 우리는  Single Render Target이니까. 아직 필요 x.
	//pState->AddRenderTargetBlendDesc(1, tDesc);
	//pState->AddRenderTargetBlendDesc(2, tDesc);
	// ... 
	// pState->AddRenderTargetBlendDesc(8, tDesc);
	pState->Create();

	AddBlendState(L"AlphaBlend", pState);
}

CSampler * CShaderMgr::FindSampler(const wstring& _strKey)
{
	map<wstring, CSampler*>::iterator iter = m_mapSampler.find(_strKey);
	if (iter == m_mapSampler.end())
		return NULL;
	return iter->second;
}

