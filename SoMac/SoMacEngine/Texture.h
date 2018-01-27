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
public:
	virtual void ApplyData();
public:
	CTexture();
	virtual ~CTexture();
};

