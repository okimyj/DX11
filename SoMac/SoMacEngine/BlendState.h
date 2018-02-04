#pragma once
#include "global.h"
class CBlendState
{
private:
	D3D11_BLEND_DESC		m_tDesc;
	bool								m_bMRT;		// Multi Render Target.
	ID3D11BlendState*		m_pBlendState;

public:
	void SetMRT(bool _bTrue) { m_bMRT = _bTrue; }
	void AddRenderTargetBlendDesc(UINT _iIdx, const D3D11_RENDER_TARGET_BLEND_DESC& _tTargetDesc);
	void Create();
	void ApplyData();
public:
	CBlendState();
	~CBlendState();
};

