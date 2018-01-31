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
struct SAMPLER_INFO
{
	CSampler*		pSampler;
	UINT				iState;			// � Shader ������ sampler�� �������ٰ���.
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
public:
	ID3DBlob* GetVSBlob() { return m_pVSBlob; }
	ID3DBlob* GetPSBlob() { return m_pPSBlob; }
public:
	int CreateVertexShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	int CreatePixelShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	void AddSampler(CSampler* _pSampler, SHADER_TYPE _eState) { m_vecSampler.push_back(SAMPLER_INFO{ _pSampler, (UINT)_eState }); }
	void ApplyData();
public:
	CShader();
	~CShader();
};

