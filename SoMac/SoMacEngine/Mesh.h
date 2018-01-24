#pragma once
#include "Res.h"
class CShader;
class CMesh
	: public CRes
{
private:
	ID3D11Buffer*		m_pVertexBuffer;
	UINT						m_iVtxCount;
	UINT						m_iVtxSize;
	D3D11_USAGE		m_eVtxUsage;
	void*						m_pVtxSysMem;

	ID3D11Buffer*		m_pIndexBuffer;
	UINT						m_iIdxCount;
	UINT						m_iIdxSize;
	D3D11_USAGE		m_eIdxUsage;
	DXGI_FORMAT		m_eIdxFormat;
	void*						m_pIdxSysMem;

	D3D11_PRIMITIVE_TOPOLOGY m_eTopology;

	// Input Layout.
	// DX는 전달해주는 정점 데이터의 내부가 어떻게 생겼는지 몰라. 
	// position, rotation, texture, color 등 어디서부터 어디까지는 이거 저거 하는 구조를 Shader에 알려주기 위해 사용.
	ID3D11InputLayout*		m_pLayout;

	vector<D3D11_INPUT_ELEMENT_DESC> m_vecLayoutDesc;
	UINT														m_iLayoutOffset;

public :
	static CMesh* Create(UINT _iVtxCount, UINT _iVtxSize, D3D11_USAGE _eVtxUsage, void* _pVtxSysMem
		, UINT _iIdxCount, UINT _iIdxSize, D3D11_USAGE _eIdxUsage, DXGI_FORMAT _eIdxFormat, void* _pIdxSysMem
		, D3D11_PRIMITIVE_TOPOLOGY _eTopology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void SetVtxSysMem(void* _pSysMem, UINT _iVtxSize, UINT _iVtxCount);
	void SetIdxSysMem(void* _pSysMem, UINT _iIdxSize, UINT _iIdxCount);

	void AddLayoutDesc(char* _pSemanticName, int _iSemanticIdx, DXGI_FORMAT _eFormat, int _iInputSlot, int _iInstancing);
	int SetShader(CShader* _pShader);
	int SetShader(ID3DBlob* _pBlob);
	virtual void ApplyData();
	void Render();
public:
	CMesh();
	virtual ~CMesh();
};

