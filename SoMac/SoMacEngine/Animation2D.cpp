#include "Animation2D.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Device.h"
#include <atlstr.h>  

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


bool CAnimation2D::Load(const wstring & _strFolderPath, const wstring& _strFullPath)
{
	// window 함수임.
	WIN32_FIND_DATA tData = {};
	
	// FIndFirstFile 을 사용 하는 탐색기(?)에 대한 handle. 커널 오브젝트(운영체제 내부에서 동작하는 것.)
	// FindNextFile 의 인자로 사용 됨.
	HANDLE hHandle = FindFirstFile(wstring(_strFullPath + L"\\" + L"*.*").c_str(), &tData);
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


bool CAnimation2D::LoadMultiAnimation(const wstring & _strFolderPath, const wstring & _strFullPath, map<wstring, CAnimation*>& _mapAnim)
{
	wstring strFilePath = _strFullPath + L"\\desc.txt";
	FILE* pFile = NULL;		
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");

	wchar_t szBuffer[255] = {};
	tDescInfo tInfo = {};
	vector<tDescInfo> vecInfo;
	// 우선 애니메이션의 정보를 읽어서 tDescInfo 자료형으로 만들어 vecInfo에 저장.
	while (true)
	{
		// fwscanf_s : file의 끝까지 읽으면 -1을 반환한다.
		if (-1 == fwscanf_s(pFile, L"%s", szBuffer, 255))
			break;
		// wcscmp : 문자열 비교 함수. 
		// result == 0 : 두 문자열이 같다. / result < 0 : String2가 더 크다. / result > 0 : String1가 더 크다. 
		if (wcscmp(szBuffer, L"[ANIMATION]") == 0)
		{
			// 여러개의 텍스쳐를 사용하는지 아닌지.
			fwscanf_s(pFile, L"%d", &tInfo.bMultipleTexture);
			// Texture Name
			fwscanf_s(pFile, L"%s", szBuffer, 255);
			tInfo.strTexName = szBuffer;
			// Animation Name
			fwscanf_s(pFile, L"%s", szBuffer, 255);
			tInfo.strAnimName = szBuffer;
			if (!tInfo.bMultipleTexture)
			{
				// left top
				fwscanf_s(pFile, L"%f%f", &tInfo.vLeftTop.x, &tInfo.vLeftTop.y);
				// size
				fwscanf_s(pFile, L"%f%f", &tInfo.vSize.x, &tInfo.vSize.y);	
			}
			else
			{
				// startIndex
				fwscanf_s(pFile, L"%d", &tInfo.iStartIdx);
			}
			
			// frameCount
			fwscanf_s(pFile, L"%d", &tInfo.iFrameCount);
			vecInfo.push_back(tInfo);
		}
	}
	// fopen 했으면 반드시 fclose.
	fclose(pFile);

	// 읽어온 정보들로 Animation 생성.
	for (UINT i = 0; i < vecInfo.size(); ++i)
	{
		CAnimation2D* pAnim = MakeOneAnim(vecInfo[i], _strFolderPath);
		_mapAnim.insert(make_pair(pAnim->GetKey(), pAnim));
	}
	return RET_SUCCESS;
}

CAnimation2D * CAnimation2D::MakeOneAnim(tDescInfo & _tDesc, const wstring& _strFolderPath)
{
	CAnimation2D* pAnim = new CAnimation2D;
	pAnim->SetKey(_tDesc.strAnimName);
	if (_tDesc.bMultipleTexture)
	{
		CString str;
		wstring strTextureName;
		wstring strTexturePath;
		CTexture* pTexture;
		for (UINT i = 0; i < _tDesc.iFrameCount; ++i)
		{
			
			str.Format(_tDesc.strTexName.c_str(), i);
			strTextureName = str.GetBuffer();
			strTexturePath = _strFolderPath + L"\\" + strTextureName;
			pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(strTextureName, strTexturePath);
			tFrameInfo tFrame = {};
			tFrame.pTexture = pTexture;
			tFrame.fWidth = 1.f;
			tFrame.fHeight = 1.f;
			tFrame.vLeftTop = { 0.f, 0.f };
			tFrame.fTerm = 0.05f;
			pAnim->AddFrame(tFrame);
		}
	}
	else
	{
		wstring strTexturePath = _strFolderPath + L"\\" + _tDesc.strTexName;
		CTexture* pTexture = (CTexture*)CResMgr::GetInst()->Load<CTexture>(_tDesc.strTexName, strTexturePath);
		for (UINT i = 0; i < _tDesc.iFrameCount; ++i)
		{
			tFrameInfo tFrame = {};
			tFrame.pTexture = pTexture;
			tFrame.fWidth = _tDesc.vSize.x / pTexture->GetWidth();
			tFrame.fHeight = _tDesc.vSize.y / pTexture->GetHeight();
			// 무조건 1열로 오른쪽으로 진행된다고 가정.
			tFrame.vLeftTop.x = _tDesc.vLeftTop.x / pTexture->GetWidth() + (i * tFrame.fWidth);
			tFrame.vLeftTop.y = _tDesc.vLeftTop.y / pTexture->GetHeight();
			tFrame.fTerm = 0.05f;
			pAnim->AddFrame(tFrame);
		}
	}
	
	return pAnim;
}


