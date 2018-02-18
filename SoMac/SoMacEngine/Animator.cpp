#include "Animator.h"
#include "Animation2D.h"
#include "MeshRenderer.h"

CAnimator::CAnimator()
	: m_pCurAnim(NULL)
	, m_bRepeat(true)
{
}


CAnimator::~CAnimator()
{
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
