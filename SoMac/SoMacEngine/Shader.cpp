#include "Shader.h"
#include "Device.h"

CShader::CShader()
	: m_pVSBlob(NULL)
	, m_pPSBlob(NULL)
	, m_pVSErrBlob(NULL)
	, m_pPSErrBlob(NULL)
	, m_pVS(NULL)
	, m_pPS(NULL)
{
}


CShader::~CShader()
{
	SAFE_RELEASE(m_pVSBlob);
	SAFE_RELEASE(m_pPSBlob);
	SAFE_RELEASE(m_pVSErrBlob);
	SAFE_RELEASE(m_pPSErrBlob);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
}


int CShader::CreateVertexShader(wstring _strFilePath, char * _pFuncName, int _iHigh, int _iLow)
{
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag |= D3D10_SHADER_DEBUG;
#endif
	
	// Shader code compile. -> 결과 binary를 blob에 넣는다. 
	//-- Create Vertex Shader --//
	char strVersion[255] = "";
	sprintf_s(strVersion, "vs_%d_%d", _iHigh, _iLow);
	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _pFuncName, strVersion, iFlag, 0, &m_pVSBlob, &m_pVSErrBlob)))
	{
		return RET_FAILED;
	}
	if (FAILED(DEVICE->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize()
		, NULL, &m_pVS)))
	{
		return RET_FAILED;
	}
	
	return RET_SUCCESS;
}

int CShader::CreatePixelShader(wstring _strFilePath, char * _pFuncName, int _iHigh, int _iLow)
{
	UINT iFlag = 0;
#ifdef _DEBUG
	iFlag |= D3D10_SHADER_DEBUG;
#endif
	//-- Create Pixel Shader --//
	char strVersion[255] = "";
	sprintf_s(strVersion, "ps_%d_%d", _iHigh, _iLow);
	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _pFuncName, strVersion, iFlag, 0, &m_pPSBlob, &m_pPSErrBlob)))
	{
		return RET_FAILED;
	}
	if (FAILED(DEVICE->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize()
		, NULL, &m_pPS)))
	{
		return RET_FAILED;
	}
	return RET_SUCCESS;
}

void CShader::ApplyData()
{
	CONTEXT->VSSetShader(m_pVS, NULL, NULL);
	CONTEXT->PSSetShader(m_pPS, NULL, NULL);
}
