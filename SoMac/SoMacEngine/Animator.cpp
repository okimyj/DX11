#include "Animator.h"
#include "Animation2D.h"
#include "MeshRenderer.h"
#include "Device.h"
#include "PathMgr.h"
#include "shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")

CAnimator::CAnimator()
	: m_pCurAnim(NULL)
	, m_bRepeat(true)
{
}
// frameIndex, AccTime등 때문에 깊은 복사 해야함.
CAnimator::CAnimator(const CAnimator& _other)
	: CComponent(_other)
	, m_pCurAnim(NULL)
	, m_bRepeat(_other.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _other.m_mapAnim.begin();
	for (; iter != _other.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = iter->second->Clone();
		pAnim->SetAnimator(this);
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}
}


CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}


int CAnimator::FinalUpdate()
{
	
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->FinalUpdate();
		if (m_bRepeat && !m_pCurAnim->IsEnable())
			m_pCurAnim->SetEnable(true);
	}
		
	return 0;
}

void CAnimator::PlayAnimation(const wstring & _strKey, bool _bRepeat)
{
	m_bRepeat = _bRepeat;
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);
	if (iter != m_mapAnim.end())
	{
		m_pCurAnim = iter->second;
		m_pCurAnim->SetEnable(true);
	}
	else
		m_pCurAnim = NULL;
}

// _strFolderPath : 상대경로.
void CAnimator::LoadAnimation2D(const wstring & _strKey, const wstring & _strFolderPath)
{
	wstring strFullPath = CPathMgr::GetResourcePath();
	strFullPath += _strFolderPath;
	// desc.txt 가 있는지 없는지 check. shlwapi 사용.
	if (PathFileExists(wstring(strFullPath + L"\\desc.txt").c_str()))
	{
		CAnimation2D::LoadMultiAnimation(_strFolderPath, strFullPath, m_mapAnim);
		int a = 10;
	}
	else
	{
		CAnimation2D* pAnim = new CAnimation2D;
		if (!pAnim->Load(_strFolderPath, strFullPath))
		{
			MessageBox(NULL, L"2D Animation Load Failed.", L"Animation Load error.", MB_OK);
			assert(NULL);
		}
		pAnim->SetKey(_strKey);
		m_mapAnim.insert(make_pair(_strKey, pAnim));
	}
}

void CAnimator::ChangeAnimation(const wstring & _strKey, UINT _iStartFrameIdx)
{
	CAnimation* pAnim = FindAnimation(_strKey);
	if (NULL == pAnim)
		return;

	m_pCurAnim = pAnim;
	m_pCurAnim->SetFrameIdx(_iStartFrameIdx);
}

void CAnimator::ApplyData()
{
	if (NULL != m_pCurAnim)
	{
		m_pCurAnim->ApplyData();
	}
}

void CAnimator::Disable()
{
	// animation을 사용하지 않는 meshRenderer가 Render 에서 호출한다. 
	// register 에 나는 Animation이다. 라고 저장되어 있는 값을 변경하기 위해서.
	tAnimInfo tInfo = {};
	tInfo.vAnim.x = 0;
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
}

CAnimation * CAnimator::FindAnimation(const wstring & _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);
	if (iter == m_mapAnim.end())
		return NULL;

	return iter->second;
}
