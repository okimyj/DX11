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
	m_tDesc.AlphaToCoverageEnable = false;		// ������ �Ѵ��� �� ���� ��� ��. ���߿� ã�ƺ���.
	if (FAILED(DEVICE->CreateBlendState(&m_tDesc, &m_pBlendState)))
	{
		assert(NULL);
	}
}

void CBlendState::ApplyData()
{
	// FLOAT BlendFactor : Blend State �ɼ��� Factor�� ���� ��� �� ���� ������ �� �� ���. 
	// UINT SampleMask : �������� �ѹ� �� Masking.. �� ���� ����.
	CONTEXT->OMSetBlendState(m_pBlendState, NULL, 0xffffff);
}

