#include "Animation2D.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Device.h"


CAnimation2D::CAnimation2D()
	: m_iCurFrame(0)
	, m_fAccTime(0.f)
{
}


CAnimation2D::~CAnimation2D()
{
}

int CAnimation2D::FinalUpdate()
{
	if (!m_bEnable || m_vecFrame.size() <= 0)
		return RET_FAILED;
	float fDT = CTimeMgr::GetInst()->DeltaTime();
	m_fAccTime += fDT;
	if (m_vecFrame[m_iCurFrame].fTerm <= m_fAccTime)
	{
		m_fAccTime = 0.f;
		++m_iCurFrame;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = 0;
			m_bEnable = false;
		}
		else
		{
			// TODO : update mesh.
		}
	}
	return 0;
}



int CAnimation2D::ApplyData()
{
	tAnimInfo tInfo = {};
	tInfo.vAnim.x = 1;
	tInfo.vUV.x = m_vecFrame[m_iCurFrame].vLeftTop.x;
	tInfo.vUV.y = m_vecFrame[m_iCurFrame].vLeftTop.y;
	tInfo.vUV.z = m_vecFrame[m_iCurFrame].fWidth;
	tInfo.vUV.w = m_vecFrame[m_iCurFrame].fHeight;

	const CBUFFER* pBuffer = CDevice::GetInst()->FindConstBuffer(L"AnimationInfo");
	D3D11_MAPPED_SUBRESOURCE tSub = {};

	CONTEXT->Map(pBuffer->pBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, &tInfo, pBuffer->iSize);
	CONTEXT->Unmap(pBuffer->pBuffer, 0);

	CONTEXT->VSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->HSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->DSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->CSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->GSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);
	CONTEXT->PSSetConstantBuffers(pBuffer->iRegister, 1, &pBuffer->pBuffer);

	if (NULL != m_vecFrame[m_iCurFrame].pTexture)
		m_vecFrame[m_iCurFrame].pTexture->ApplyData(16, (UINT)SHADER_TYPE::ST_PIXEL);


	return RET_SUCCESS;
}


bool CAnimation2D::Load(const wstring & _strFolderPath)
{
	// window 함수임.
	WIN32_FIND_DATA tData = {};
	
	wstring strFullPath = CPathMgr::GetResourcePath();
	strFullPath += _strFolderPath;	

	// FIndFirstFile 을 사용 하는 탐색기(?)에 대한 handle. 커널 오브젝트(운영체제 내부에서 동작하는 것.)
	// FindNextFile 의 인자로 사용 됨.
	HANDLE hHandle = FindFirstFile(wstring(strFullPath + L"\\" + L"*.*").c_str(), &tData);
	if (INVALID_HANDLE_VALUE == hHandle)
		return RET_FAILED;
	tFrameInfo tInfo = {};
	do
	{
		// load Texture;
		CTexture* pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(tData.cFileName, _strFolderPath + L"\\" + tData.cFileName);
		// resource load Failed.
		if (NULL == pTexture)
			continue;

		// make frame info.
		tInfo = {};
		tInfo.pTexture = pTexture;
		tInfo.vLeftTop = Vec2(0.f, 0.f);
		tInfo.fWidth = 1.f;
		tInfo.fHeight = 1.f;
		tInfo.fTerm = 0.05f;

		m_vecFrame.push_back(tInfo);

	} while (FindNextFile(hHandle, &tData));
	
	return RET_SUCCESS;
}


bool CAnimation2D::LoadMultiAnimation(const wstring & _strFolderPath, const wstring & _strFullPath, map<wstring, CAnimation*> _mapAnim)
{
	wstring strFilePath = _strFullPath + L"\\desc.txt";
	FILE* pFile = NULL;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	return false;
}


