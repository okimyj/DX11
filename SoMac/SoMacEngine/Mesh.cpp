#include "Mesh.h"
#include "Device.h"
#include "Shader.h"
CMesh::CMesh()
	: m_pVertexBuffer(NULL)
	, m_iVtxCount(0)
	, m_iVtxSize(0)
	, m_eVtxUsage(D3D11_USAGE_DEFAULT)
	, m_pVtxSysMem(NULL)
	, m_pIndexBuffer(NULL)
	, m_iIdxCount(0)
	, m_iIdxSize(0)
	, m_eIdxUsage(D3D11_USAGE_DEFAULT)
	, m_eIdxFormat(DXGI_FORMAT_UNKNOWN)
	, m_pIdxSysMem(NULL)
	, m_iLayoutOffset(0)
{
	

}


CMesh::~CMesh()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
	SAFE_RELEASE(m_pLayout);

	SAFE_DELETE(m_pVtxSysMem);
	SAFE_DELETE(m_pIdxSysMem);
}

CMesh * CMesh::Create(UINT _iVtxCount, UINT _iVtxSize, D3D11_USAGE _eVtxUsage, void * _pVtxSysMem
	, UINT _iIdxCount, UINT _iIdxSize, D3D11_USAGE _eIdxUsage, DXGI_FORMAT _eIdxFormat, void * _pIdxSysMem
	, D3D11_PRIMITIVE_TOPOLOGY _eTopology)
{
	// 메모리 측면의 용도 :BindFlag , 쓰임새 측면의 용도 : Usage
	// Usage의 설정이 Dynamic 일 때만 CPU_ACCESS_WRITE 옵션을 사용 할 수 있다. 
	D3D11_BUFFER_DESC tBufferDesc = {};
	tBufferDesc.ByteWidth = _iVtxSize * _iVtxCount;
	tBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tBufferDesc.Usage = _eVtxUsage;
	// dynamic 일 경우에만 write flag를 사용 할 수 있다. 
	if (D3D11_USAGE_DYNAMIC == tBufferDesc.Usage)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	
	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _pVtxSysMem;
	ID3D11Buffer* pVB = NULL;
	// Create Vertex Buffer.
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, &pVB)))
	{
		return NULL;
	}
	// Create Index Buffer.
	memset(&tBufferDesc, 0, sizeof(D3D11_BUFFER_DESC));
	tBufferDesc.ByteWidth = _iIdxSize * _iIdxCount;
	tBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	tBufferDesc.Usage = _eIdxUsage;
	if (D3D11_USAGE_DYNAMIC == tBufferDesc.Usage)
		tBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	tSub.pSysMem = _pIdxSysMem;

	ID3D11Buffer* pIB = NULL;
	if (FAILED(DEVICE->CreateBuffer(&tBufferDesc, &tSub, &pIB)))
	{
		return NULL;
	}

	CMesh* pMesh = new CMesh();
	pMesh->m_pVertexBuffer = pVB;
	pMesh->m_iVtxCount = _iVtxCount;
	pMesh->m_iVtxSize = _iVtxSize;
	pMesh->m_eVtxUsage = _eVtxUsage;
	pMesh->SetVtxSysMem(_pVtxSysMem, _iVtxSize, _iVtxCount);


	//pMesh->m_pSysMemory
	pMesh->m_pIndexBuffer = pIB;
	pMesh->m_iIdxCount = _iIdxCount;
	pMesh->m_iIdxSize = _iIdxSize;
	pMesh->m_eIdxUsage = _eIdxUsage;
	pMesh->m_eIdxFormat = _eIdxFormat;
	pMesh->SetVtxSysMem(_pIdxSysMem, _iIdxSize, _iIdxCount);
	pMesh->m_eTopology = _eTopology;


	pMesh->SetVtxSysMem(_pVtxSysMem, _iVtxSize, _iVtxCount);
	pMesh->SetIdxSysMem(_pIdxSysMem, _iIdxSize, _iIdxCount);
	return pMesh;
}

void CMesh::SetVtxSysMem(void * _pSysMem, UINT _iVtxSize, UINT _iVtxCount)
{
	SAFE_DELETE(m_pVtxSysMem);
	m_iVtxSize = _iVtxSize;
	m_iVtxCount = _iVtxCount;
	m_pVtxSysMem = malloc(_iVtxSize * _iVtxCount);
	memcpy(m_pVtxSysMem, _pSysMem, _iVtxSize * _iVtxCount);
}

void CMesh::SetIdxSysMem(void * _pSysMem, UINT _iIdxSize, UINT _iIdxCount)
{
	SAFE_DELETE(m_pIdxSysMem);
	m_iIdxSize = _iIdxSize;
	m_iIdxCount = _iIdxCount;
	m_pVtxSysMem = malloc(_iIdxSize * _iIdxCount);
	memcpy(m_pVtxSysMem, _pSysMem, _iIdxSize * _iIdxCount);
}

void CMesh::AddLayoutDesc(char * _pSemanticName, int _iSemanticIdx, DXGI_FORMAT _eFormat, int _iInputSlot, int _iInstancing)
{
	// == Create Input Layout ================================
	// 전달해주는 정점 데이터의 내부 구조를 shader에게 알려주는 것. 
	// Layout의 요소 순서와 정점 데이터의 요소 순서는 반드시 같아야 한다. 
	// shader 에서는 노상관, 그래도 맞춰주는게 보기는 좋겠지. 
	D3D11_INPUT_ELEMENT_DESC tDesc = {};
	tDesc.SemanticName = _pSemanticName;
	tDesc.SemanticIndex = _iSemanticIdx;		// 같은 종류의 semantic 에 대해서 증가하는 index.
	tDesc.Format = _eFormat;
	tDesc.InputSlot = _iInputSlot;					// 0~15사이의 값. 
	tDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	tDesc.InstanceDataStepRate = _iInstancing;		// 나중에 최적화 할 때 필요. (인스턴싱).
	tDesc.AlignedByteOffset = m_iLayoutOffset;
	m_iLayoutOffset += GetSizeOfFormat(_eFormat);
	m_vecLayoutDesc.push_back(tDesc);
}

int CMesh::SetShader(CShader * _pShader)
{
	SAFE_RELEASE(m_pLayout);
	// shader랑 연동 되는 시점에 create.
	if (FAILED(DEVICE->CreateInputLayout(&m_vecLayoutDesc[0], m_vecLayoutDesc.size(), _pShader->GetVSBlob()->GetBufferPointer()
		, _pShader->GetVSBlob()->GetBufferSize(), &m_pLayout)))
	{
		return RET_FAILED;
	}
	return RET_SUCCESS;
}

int CMesh::SetShader(ID3DBlob * _pBlob)
{
	SAFE_RELEASE(m_pLayout);
	
	// shader랑 연동 되는 시점에 create.
	if (FAILED(DEVICE->CreateInputLayout(&m_vecLayoutDesc[0], m_vecLayoutDesc.size(), _pBlob->GetBufferPointer()
		, _pBlob->GetBufferSize(), &m_pLayout)))
	{
		return RET_FAILED;
	}
	
	return RET_SUCCESS;
}

void CMesh::UpdateData()
{
	UINT iOffset = 0;
	UINT iStride = m_iVtxSize;			// 정점 데이터 1개의 size.
	CONTEXT->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &iStride, &iOffset);																			// CONTEXT->Draw(3, 0); // 그냥 그릴 때 사용. 
	CONTEXT->IASetIndexBuffer(m_pIndexBuffer, m_eIdxFormat, 0);
	CONTEXT->IASetPrimitiveTopology(m_eTopology);		// 정점을 읽어서 어떤 모양을 만들건지?
	CONTEXT->IASetInputLayout(m_pLayout);
}

void CMesh::Render()
{
	CONTEXT->DrawIndexed(m_iIdxCount, 0, 0);
}