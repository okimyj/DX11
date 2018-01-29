#include "TextureAnimator.h"
#include "TextureAnim.h"
#include "TimeMgr.h"
CTextureAnimator::CTextureAnimator()
	: m_mapAnim{}
{
}


CTextureAnimator::~CTextureAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CTextureAnimator::Play(const wstring & _strName)
{
	map<wstring, CTextureAnim*>::iterator iter = m_mapAnim.find(_strName);
	if (m_mapAnim.end() == iter)
		return;
	m_pCurrentAnim = iter->second;
}

void CTextureAnimator::Start()
{
	map<wstring, CTextureAnim*>::iterator iter = m_mapAnim.begin();
	for (; iter != m_mapAnim.end(); ++iter)
	{
		iter->second->Init();
	}
}

int CTextureAnimator::Update()
{
	if (m_pCurrentAnim)
	{
		int result = m_pCurrentAnim->Update(CTimeMgr::GetInst()->DeltaTime());
		if (FAILED(result))
			m_pCurrentAnim = NULL;
		// TODO : check finished anim & finished callback.
	}
	return RET_SUCCESS;
}