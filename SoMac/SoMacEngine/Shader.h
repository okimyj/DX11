#pragma once
#include "global.h"
/*
shader�� ���� ��
���� ��� ������� ���踦 �Ѵ�.
-> shader�� �������ִ� ���� ������ ��� ������ �ɼ� �ۿ� ����.
�ʿ��� ������ material ������
but, �츮�� unity�� ����ϰ� �Ϸ��� ���� ������ �Ұ���
-> material ���� �� �ٽ� ����.
*/
class CSampler;
class CBlendState;
struct SAMPLER_INFO
{
	CSampler*		pSampler;
	UINT				iTiming;			// � Shader ������ sampler�� �������ٰ���.
};
class CShader
{
private:
	ID3DBlob*						m_pVSBlob;		// Vertext Shader Blob.
	ID3DBlob*						m_pPSBlob;		// Pixel Shader Blob.

	ID3DBlob*						m_pVSErrBlob;		// shader compile ���н� error, warning ���ڿ��� �޾ƿ� blob.
	ID3DBlob*						m_pPSErrBlob;

	ID3D11VertexShader*	m_pVS;			// Vertex Shader.
	ID3D11PixelShader*		m_pPS;			// Pixel Shader.

	vector<SAMPLER_INFO>	m_vecSampler;		// �ϳ��� shader ���� ������ �ܰ� ���� �������� sampler�� ���� �� �ִ�. define.SHADER_TYPE ����.
	vector<tShaderParam>	m_vecShaderParam;
	CBlendState*					m_pBlendState;
public:
	ID3DBlob* GetVSBlob() { return m_pVSBlob; }
	ID3DBlob* GetPSBlob() { return m_pPSBlob; }
public:
	int CreateVertexShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	int CreatePixelShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	void ApplyData();

public:
	void SetBlendState(CBlendState* _pState) { m_pBlendState = _pState; }
	// state �� �������� flag �� �������� �Ѿ�� �� �ֵ��� UINT�� ��.
	void AddSampler(CSampler* _pSampler, UINT _iTiming) { m_vecSampler.push_back(SAMPLER_INFO{ _pSampler, _iTiming }); }
	void AddShaderParam(SHADER_PARAM _eParam, UINT _iTiming);
	vector<tShaderParam>& GetShaderParam() { return m_vecShaderParam; }
public:
	CShader();
	~CShader();
};

