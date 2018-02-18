#include "Animation2D.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Material.h"




CAnimation2D::CAnimation2D()
	: m_iCurFrame(0)
	, m_fAccTime(0.f)
{
}


CAnimation2D::~CAnimation2D()
{
}

int CAnimation2D::ApplyData(CMaterial* pMaterial)
{
	
	int iData = 0;
	int iData1 = 1;
	pMaterial->SetParamData(SHADER_PARAM::INT_0, &iData);
	pMaterial->SetParamData(SHADER_PARAM::INT_1, &iData1);
	pMaterial->SetParamData(SHADER_PARAM::TEXTURE_0, &m_vecFrame[m_iCurFrame].pTexture);
	Vec4 vec = Vec4(m_vecFrame[m_iCurFrame].vLeftTop.x, m_vecFrame[m_iCurFrame].vLeftTop.y, m_vecFrame[m_iCurFrame].fWidth, m_vecFrame[m_iCurFrame].fHeight);
	pMaterial->SetParamData(SHADER_PARAM::VEC4_0, &vec);
	
	return 0;
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

