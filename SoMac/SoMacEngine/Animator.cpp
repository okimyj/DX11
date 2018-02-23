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
		m_pCurAnim->ApplyData(MeshRenderer()->GetMaterial());
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
	CAnimation2D* pAnim = new CAnimation2D;
	if (!pAnim->Load(_strFolderPath))
	{
		MessageBox(NULL, L"2D Animation Load Failed.", L"Animation Load error.", MB_OK);
		assert(NULL);
	}
	pAnim->SetKey(_strKey);
	m_mapAnim.insert(make_pair(_strKey, pAnim));

}

void CAnimator::ChangeAnimation(const wstring & _strKey, UINT _iStartFrameIdx)
{
}

void CAnimator::ApplyData()
{
}

void CAnimator::Disable()
{
}

CAnimation * CAnimator::FindAnimation(const wstring & _strKey)
{
	return nullptr;
}
