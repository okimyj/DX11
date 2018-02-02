#include "Sampler.h"
#include "Device.h"

CSampler::CSampler(D3D11_SAMPLER_DESC _tDesc, ID3D11SamplerState * _pState, UINT _iRegister)
	: m_tDesc(_tDesc)
	, m_pState(_pState)
	, m_iRegister(_iRegister)
{
}

CSampler::~CSampler()
{
	SAFE_RELEASE(m_pState);
}



CSampler * CSampler::Create(D3D11_FILTER _eFilter, UINT _iRegister
	, D3D11_TEXTURE_ADDRESS_MODE _eUAddress
	, D3D11_TEXTURE_ADDRESS_MODE _eVAddress
	, D3D11_TEXTURE_ADDRESS_MODE _eWAddress)
{
	D3D11_SAMPLER_DESC tDesc = {};
	tDesc.Filter = _eFilter;
	tDesc.AddressU = _eUAddress;
	tDesc.AddressV = _eVAddress;
	tDesc.AddressW = _eWAddress;

	ID3D11SamplerState* pState = NULL;
	if (FAILED(DEVICE->CreateSamplerState(&tDesc, &pState)))
	{
		assert(NULL);
		return NULL;
	}
	return new CSampler(tDesc, pState, _iRegister);
}

void CSampler::ApplyData(UINT _iState)
{
	// 알맞은 시점에 sampler set.
	// Shader 에서 호출한다.
	if(_iState & (UINT)SHADER_TYPE::ST_VERTEX)
		CONTEXT->VSSetSamplers(m_iRegister, 1, &m_pState);
	if (_iState & (UINT)SHADER_TYPE::ST_HULL)
		CONTEXT->HSSetSamplers(m_iRegister, 1, &m_pState);
	if (_iState & (UINT)SHADER_TYPE::ST_DOMAIN)
		CONTEXT->DSSetSamplers(m_iRegister, 1, &m_pState);
	if (_iState & (UINT)SHADER_TYPE::ST_GEOMETRY)
		CONTEXT->GSSetSamplers(m_iRegister, 1, &m_pState);
	if (_iState & (UINT)SHADER_TYPE::ST_COMPUTE)
		CONTEXT->CSSetSamplers(m_iRegister, 1, &m_pState);
	if (_iState & (UINT)SHADER_TYPE::ST_PIXEL)
		CONTEXT->PSSetSamplers(m_iRegister, 1, &m_pState);
}

