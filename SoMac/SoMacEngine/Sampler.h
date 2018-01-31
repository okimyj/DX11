#pragma once
#include "global.h"
class CSampler
{
private:
	D3D11_SAMPLER_DESC		m_tDesc;
	ID3D11SamplerState*		m_pState;
	UINT									m_iRegister;
public:
	static CSampler* Create(D3D11_FILTER _eFilter, UINT _iRegister
		, D3D11_TEXTURE_ADDRESS_MODE _eUAddress
		, D3D11_TEXTURE_ADDRESS_MODE _eVAddress
		, D3D11_TEXTURE_ADDRESS_MODE _eWAddress = D3D11_TEXTURE_ADDRESS_WRAP);
	void ApplyData(UINT _iState);

public:
	CSampler(D3D11_SAMPLER_DESC _tDesc, ID3D11SamplerState* _pState, UINT _iRegister);
	~CSampler();
};

