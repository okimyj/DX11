#include "BlendState.h"
#include "Device.h"

CBlendState::CBlendState()
	: m_tDesc{}
	, m_pBlendState(NULL)
	, m_bMRT(false)
{
}


CBlendState::~CBlendState()
{
}

void CBlendState::AddRenderTargetBlendDesc(UINT _iIdx, const D3D11_RENDER_TARGET_BLEND_DESC & _tTargetDesc)
{
	m_tDesc.RenderTarget[_iIdx] = _tTargetDesc;
}

void CBlendState::Create()
{
	m_tDesc.IndependentBlendEnable = m_bMRT;
	m_tDesc.AlphaToCoverageEnable = false;		// 끄던가 켜던가 별 차이 없어서 끔. 나중에 찾아보자.
	if (FAILED(DEVICE->CreateBlendState(&m_tDesc, &m_pBlendState)))
	{
		assert(NULL);
	}
}

void CBlendState::ApplyData()
{
	// FLOAT BlendFactor : Blend State 옵션을 Factor로 만든 경우 그 값을 지정해 줄 때 사용. 
	// UINT SampleMask : 마지막에 한번 더 Masking.. 별 짓을 다함.
	CONTEXT->OMSetBlendState(m_pBlendState, NULL, 0xffffff);
}

