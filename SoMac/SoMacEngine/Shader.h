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
class CShader
{
private:
	ID3DBlob*						m_pVSBlob;		// Vertext Shader Blob.
	ID3DBlob*						m_pPSBlob;		// Pixel Shader Blob.

	ID3DBlob*						m_pVSErrBlob;		// shader compile 실패시 error, warning 문자열을 받아올 blob.
	ID3DBlob*						m_pPSErrBlob;

	ID3D11VertexShader*	m_pVS;			// Vertex Shader.
	ID3D11PixelShader*		m_pPS;			// Pixel Shader.

public:
	ID3DBlob* GetVSBlob() { return m_pVSBlob; }
	ID3DBlob* GetPSBlob() { return m_pPSBlob; }
public:
	int CreateVertexShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	int CreatePixelShader(wstring _strFilePath, char* _pFuncName, int _iHigh, int _iLow);
	void UpdateData();
public:
	CShader();
	~CShader();
};

