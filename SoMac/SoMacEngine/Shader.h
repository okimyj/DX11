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
class CShader
{
private:
	ID3DBlob*						m_pVSBlob;		// Vertext Shader Blob.
	ID3DBlob*						m_pPSBlob;		// Pixel Shader Blob.

	ID3DBlob*						m_pVSErrBlob;		// shader compile ���н� error, warning ���ڿ��� �޾ƿ� blob.
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

