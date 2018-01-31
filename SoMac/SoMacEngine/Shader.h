#pragma once
#include "global.h"
/*
shader를 만들 때
보통 상속 기반으로 설계를 한다.
-> shader에 전달해주는 변수 때문에 상속 구조가 될수 밖에 없다.
필요한 변수는 material 정보들
but, 우리는 unity랑 비슷하게 하려고 단일 구조로 할거임
-> material 만들 때 다시 설명.
*/
class CSampler;
struct SAMPLER_INFO
{
	CSampler*		pSampler;
	UINT				iState;			// 어떤 Shader 시점에 sampler를 셋팅해줄건지.
};
class CShader
{
private:
	ID3DBlob*						m_pVSBlob;		// Vertext Shader Blob.
	ID3DBlob*						m_pPSBlob;		// Pixel Shader Blob.

	ID3DBlob*						m_pVSErrBlob;		// shader compile 실패시 error, warning 문자열을 받아올 blob.
	ID3DBlob*						m_pPSErrBlob;

	ID3D11VertexShader*	m_pVS;			// Vertex Shader.
	ID3D11PixelShader*		m_pPS;			// Pixel Shader.

	vector<SAMPLER_INFO>	m_vecSampler;		// 하나의 shader 에서 렌더링 단계 별로 여러개의 sampler를 가질 수 있다. define.SHADER_TYPE 참조.
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

