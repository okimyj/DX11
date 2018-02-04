#include "Material.h"
#include "Shader.h"
#include "Texture.h"
#include "Device.h"
// shader 에서 변수를 설정 할 때 최소 16byte 단위로 설정해야 한다. 때문에 int 4개씩 묶은거.
UINT g_SPRegister[(UINT)SHADER_PARAM::END] = 
{
	1, // INT_0,
	1, // INT_1,
	1, // INT_2,
	1, // INT_3,
	1, // INT_END,

	2, // FLOAT_0,
	2, // FLOAT_1,
	2, // FLOAT_2,
	2, // FLOAT_3,
	2, // FLOAT_END,

	3, // VEC4_0,
	3, // VEC4_1,
	3, // VEC4_2,
	3, // VEC4_3,
	3, // VEC4_END,

	0, // TEXTURE_0,
	1, // TEXTURE_1,
	2, // TEXTURE_2,
	3, // TEXTURE_3,
	0, // TEXTURE_END,
};
wchar_t* g_SPName[(UINT)SHADER_PARAM::END] = 
{
	L"INT_0",
	L"INT_1",
	L"INT_2",
	L"INT_3",
	L"INT_END",
	L"FLOAT_0",
	L"FLOAT_1",
	L"FLOAT_2",
	L"FLOAT_3",
	L"FLOAT_END",
	L"VEC4_0",
	L"VEC4_1",
	L"VEC4_2",
	L"VEC4_3",
	L"VEC4_END",
	L"TEXTURE_0",
	L"TEXTURE_1",
	L"TEXTURE_2",
	L"TEXTURE_3",
	L"TEXTURE_END",
};

CMaterial::CMaterial()
	: m_pShader(NULL)
{
}

CMaterial::CMaterial(const CMaterial & _pOther)
	: m_pShader(_pOther.m_pShader)
	, m_vecShaderParam(_pOther.m_vecShaderParam)
{
	for (UINT i = 0; i < m_vecShaderParam.size(); ++i)
	{
		switch (m_vecShaderParam[i].eShaderParam)
		{
		case SHADER_PARAM::INT_0 :
		case SHADER_PARAM::INT_1:
		case SHADER_PARAM::INT_2:
		case SHADER_PARAM::INT_3:
		{
			m_vecShaderParam[i].pData = new int;
			memcpy(m_vecShaderParam[i].pData, _pOther.m_vecShaderParam[i].pData, sizeof(int));
		}
		break;
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
		{
			m_vecShaderParam[i].pData = new float;
			memcpy(m_vecShaderParam[i].pData, _pOther.m_vecShaderParam[i].pData, sizeof(float));
		}
		break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
		{
			m_vecShaderParam[i].pData = new Vec4;
			memcpy(m_vecShaderParam[i].pData, _pOther.m_vecShaderParam[i].pData, sizeof(Vec4));
		}
		break;
		case SHADER_PARAM::TEXTURE_0:
		case SHADER_PARAM::TEXTURE_1:
		case SHADER_PARAM::TEXTURE_2:
		case SHADER_PARAM::TEXTURE_3:
		{
			m_vecShaderParam[i].pData = new void*;
			memcpy(m_vecShaderParam[i].pData, _pOther.m_vecShaderParam[i].pData, sizeof(void*));
		}
		break;
		}
	}
}


CMaterial::~CMaterial()
{
	ClearShaderParam();
}


void CMaterial::SetShader(CShader * _pShader)
{
	if (_pShader == m_pShader)
		return;
	m_pShader = _pShader;
	ClearShaderParam();
	if (NULL != m_pShader)
	{
		ConvertShaderParam();
	}
}

void CMaterial::ClearShaderParam()
{
	for (UINT i = 0; i < m_vecShaderParam.size(); ++i)
	{
		SAFE_DELETE(m_vecShaderParam[i].pData);
	}
	m_vecShaderParam.clear();
}

void CMaterial::ConvertShaderParam()
{
	vector<tShaderParam>& vecParam = m_pShader->GetShaderParam();
	for (UINT i = 0; i < vecParam.size(); ++i)
	{
		tShaderParam_EX tParam = {};
		tParam.eShaderParam = vecParam[i].eShaderParam;
		tParam.iRegister = vecParam[i].iRegister;
		tParam.iTiming = vecParam[i].iTiming;
		switch (vecParam[i].eShaderParam)
		{
		case SHADER_PARAM::INT_0:
		case SHADER_PARAM::INT_1:
		case SHADER_PARAM::INT_2:
		case SHADER_PARAM::INT_3:
		{
			tParam.pData = new int;
		}
			break;
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
		{
			tParam.pData = new float;
		}
			break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
		{
			tParam.pData = new Vec4;
		}
			break;
		case SHADER_PARAM::TEXTURE_0:
		case SHADER_PARAM::TEXTURE_1:
		case SHADER_PARAM::TEXTURE_2:
		case SHADER_PARAM::TEXTURE_3:
		{
			tParam.pData = new void*;
		}
			break;
		default:
			continue;
		}
		m_vecShaderParam.push_back(tParam);

	}
}

void CMaterial::SetParamData(SHADER_PARAM _eParam, void * _pData)
{
	UINT idx = -1;
	for (int i = 0; i < m_vecShaderParam.size(); ++i)
	{
		if (m_vecShaderParam[i].eShaderParam == _eParam)
		{
			idx = i;
			break;
		}
	}
	if (idx == -1)
		return;
	switch (m_vecShaderParam[idx].eShaderParam)
	{
		case SHADER_PARAM::INT_0:
		case SHADER_PARAM::INT_1:
		case SHADER_PARAM::INT_2:
		case SHADER_PARAM::INT_3:
		{
			*((int*)m_vecShaderParam[idx].pData) = *((int*)_pData);
		}
		break;
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
		{
			*((float*)m_vecShaderParam[idx].pData) = *((float*)_pData);
		}
		break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
		{
			*((Vec4*)m_vecShaderParam[idx].pData) = *((Vec4*)_pData);
		}
		break;
		case SHADER_PARAM::TEXTURE_0:
		case SHADER_PARAM::TEXTURE_1:
		case SHADER_PARAM::TEXTURE_2:
		case SHADER_PARAM::TEXTURE_3:
		{
			*((CTexture**)m_vecShaderParam[idx].pData) = *((CTexture**)_pData);
		}
		break;
		default:
			break;
	}
}


void CMaterial::ApplyData()
{
	if (NULL == m_pShader)
		assert(NULL);

	m_pShader->ApplyData();

	int iArr[(UINT)SHADER_PARAM::INT_END - (UINT)SHADER_PARAM::INT_0] = {};
	float fArr[(UINT)SHADER_PARAM::FLOAT_END - (UINT)SHADER_PARAM::FLOAT_0] = {};
	Vec4 vecArr[(UINT)SHADER_PARAM::VEC4_END - (UINT)SHADER_PARAM::VEC4_0] = {};
	void* dataArr[3] = { iArr, fArr, vecArr };
	bool bFlag[3] = { false, false, false };
	for (UINT i = 0; i < m_vecShaderParam.size(); ++i)
	{
		switch (m_vecShaderParam[i].eShaderParam)
		{
		case SHADER_PARAM::INT_0:
		case SHADER_PARAM::INT_1:
		case SHADER_PARAM::INT_2:
		case SHADER_PARAM::INT_3:
			iArr[(UINT)m_vecShaderParam[i].eShaderParam - (UINT)SHADER_PARAM::INT_0] = *((int*)m_vecShaderParam[i].pData);
			bFlag[0] = true;
		break;
		case SHADER_PARAM::FLOAT_0:
		case SHADER_PARAM::FLOAT_1:
		case SHADER_PARAM::FLOAT_2:
		case SHADER_PARAM::FLOAT_3:
			fArr[(UINT)m_vecShaderParam[i].eShaderParam - (UINT)SHADER_PARAM::FLOAT_0] = *((float*)m_vecShaderParam[i].pData);
			bFlag[1] = true;
		break;
		case SHADER_PARAM::VEC4_0:
		case SHADER_PARAM::VEC4_1:
		case SHADER_PARAM::VEC4_2:
		case SHADER_PARAM::VEC4_3:
			vecArr[(UINT)m_vecShaderParam[i].eShaderParam - (UINT)SHADER_PARAM::VEC4_0] = *((Vec4*)m_vecShaderParam[i].pData);
			bFlag[2] = true;
		break;
		case SHADER_PARAM::TEXTURE_0:
		case SHADER_PARAM::TEXTURE_1:
		case SHADER_PARAM::TEXTURE_2:
		case SHADER_PARAM::TEXTURE_3:
			(*(CTexture**)m_vecShaderParam[i].pData)->ApplyData(m_vecShaderParam[i].iRegister, m_vecShaderParam[i].iTiming);
		break;
		}
	}
	// static 구문은 딱 한번만 실행. 매번 얻어오기엔 비효율적이니까.
	static const CBUFFER* arrConstBuffer[3] =
	{
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::INT_END]),
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::FLOAT_END]),
		CDevice::GetInst()->FindConstBuffer(g_SPName[(UINT)SHADER_PARAM::VEC4_END])
	};
	int arrNum = sizeof(dataArr) / sizeof(void*);
	for (int i = 0; i < arrNum; ++i)
	{
		if (!bFlag[i])
			continue;
		D3D11_MAPPED_SUBRESOURCE tSub = {};
		CONTEXT->Map(arrConstBuffer[i]->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
		memcpy(tSub.pData, dataArr[i], arrConstBuffer[i]->iSize);
		CONTEXT->Unmap(arrConstBuffer[i]->pBuffer, 0);
		CONTEXT->VSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->HSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->DSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->GSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->CSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
		CONTEXT->PSSetConstantBuffers(arrConstBuffer[i]->iRegister, 1, &arrConstBuffer[i]->pBuffer);
	}
}
