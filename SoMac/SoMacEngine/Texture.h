#pragma once
#include "Res.h"
class CTexture :
	public CRes
{
	ScratchImage	*							m_pImage;
	ID3D11Texture2D*						m_pTexture;
	ID3D11ShaderResourceView*		m_pView;
public:
	static CTexture* Create(const wstring& _strFileName);
	const ID3D11ShaderResourceView* GetView() { return m_pView; }
	float GetWidth() { return m_pImage->GetMetadata().width; }
	float GetHeight() { return m_pImage->GetMetadata().height; }
public:
	virtual void ApplyData(UINT _iRegister, UINT _iTiming);
public:
	CTexture();
	virtual ~CTexture();
};

