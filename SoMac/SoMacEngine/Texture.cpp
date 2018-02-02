#include "Texture.h"
#include "Device.h"
#include "PathMgr.h"


CTexture::CTexture()
	: m_pImage(NULL)
	, m_pTexture(NULL)
	, m_pView(NULL)
{ 
}


CTexture::~CTexture()
{
	SAFE_DELETE(m_pImage);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pView);
}


CTexture * CTexture::Create(const wstring & _strFileName)
{
	// 확장자 종류 별로 분기해서 리소스 로드. 
	wstring strExtension = CPathMgr::GetExtension(_strFileName.c_str());
	ScratchImage* pImage = new ScratchImage;
	bool bFailed = false;
	if (strExtension == L".dds" || strExtension == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(_strFileName.c_str(), DDS_FLAGS_NONE, NULL, *pImage)))
		{
			bFailed = true;
		}
	}
	else if(strExtension == L".tga" || strExtension == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(_strFileName.c_str(), NULL, *pImage)))
		{
			bFailed = true;
		}
	}
	else
	{	// 나머지 .png, .jpg, .jpeg, .bmp 등등...
		if (FAILED(LoadFromWICFile(_strFileName.c_str(), WIC_FLAGS_NONE, NULL, *pImage)))
		{
			bFailed = true;
		}
	}
	if (bFailed)
	{
		SAFE_DELETE(pImage);
		return NULL;
	}
	ID3D11ShaderResourceView* pView = NULL;
	if (FAILED(CreateShaderResourceView(DEVICE, pImage->GetImages(), pImage->GetImageCount(), pImage->GetMetadata(), &pView)))
	{
		SAFE_DELETE(pImage);
		return NULL;
	}
	CTexture* pTexture = new CTexture;
	pTexture->m_pImage = pImage;
	pTexture->m_pView = pView;
	pView->GetResource((ID3D11Resource**)(&pTexture->m_pTexture));			// ref Count 증가.

	return pTexture;
}

void CTexture::ApplyData(UINT _iRegister, UINT _iTiming)
{
	if (_iTiming & (UINT)SHADER_TYPE::ST_VERTEX)
		CONTEXT->VSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_HULL)
		CONTEXT->HSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_DOMAIN)
		CONTEXT->DSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_GEOMETRY)
		CONTEXT->GSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_COMPUTE)
		CONTEXT->CSSetShaderResources(_iRegister, 1, &m_pView);
	if (_iTiming & (UINT)SHADER_TYPE::ST_PIXEL)
		CONTEXT->PSSetShaderResources(_iRegister, 1, &m_pView);
}
