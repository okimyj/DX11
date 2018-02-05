#include "TextureAnim.h"
#include "ResMgr.h"
#include "Texture.h"
#include "MeshRenderer.h"
#include "Material.h"



CTextureAnim::CTextureAnim()
	: m_pTargetMesh(NULL)
	, m_strAnimPrefix(0)
	, m_iStartIdx(0)
	, m_iEndIdx(0)
	, m_fFPS(0)
	, m_bLoop(false)
{
}

CTextureAnim::CTextureAnim(const CTextureAnim * _pOther)
	: m_pTargetMesh(NULL)
	, m_vecTexture(_pOther->m_vecTexture)
	, m_bLoop(_pOther->m_bLoop)
	, m_fFPS(_pOther->m_fFPS)
	, m_fAccrueDT(0)
	, m_iAnimIdx(0)
	, m_strAnimPrefix(_pOther->m_strAnimPrefix)
	, m_iStartIdx(_pOther->m_iStartIdx)
	, m_iEndIdx(_pOther->m_iEndIdx)
	
	
{
	
}

CTextureAnim::CTextureAnim(const wstring & _strAnimPrefix, int _iStartIdx, int _iEndIdx, float _fFPS, bool _bLoop)
	: m_pTargetMesh(NULL)
	, m_vecTexture{}
	, m_bLoop(_bLoop)
	, m_fFPS(_fFPS)
	, m_fAccrueDT(0)
	, m_iAnimIdx(0)
	, m_strAnimPrefix(_strAnimPrefix)
	, m_iStartIdx(_iStartIdx)
	, m_iEndIdx(_iEndIdx)

{
	
}


CTextureAnim::~CTextureAnim()
{

}


void CTextureAnim::LoadTexture(const wstring & _strPrefix, int _iStartIdx, int _iEndIdx)
{
	m_vecTexture.resize(_iEndIdx - _iStartIdx +1);
	int iIdx = 0;
	for (int i = _iStartIdx; i <= _iEndIdx; ++i)
	{
		m_vecTexture[iIdx++] = (CTexture*)CResMgr::GetInst()->Load<CTexture>(_strPrefix + to_wstring(i));

	}
}

void CTextureAnim::Init()
{
	LoadTexture(m_strAnimPrefix, m_iStartIdx, m_iEndIdx);
}

int CTextureAnim::Update(float _dt)
{
	if (NULL == m_pTargetMesh)
		return RET_FAILED;

	m_fAccrueDT += _dt;
	
	if (1.f/m_fFPS <= m_fAccrueDT)
	{
		++m_iAnimIdx;
		if (m_iAnimIdx >= m_vecTexture.size())
		{
			if (m_bLoop)
				m_iAnimIdx = 0;
			else
				return RET_FAILED;
		}
		m_fAccrueDT = 0;
		CTexture* pTexture = m_vecTexture[m_iAnimIdx];
		if (NULL != pTexture)
			m_pTargetMesh->GetMaterial()->SetParamData(SHADER_PARAM::TEXTURE_0, &pTexture);
		//	m_pTargetMesh->SetTexture(pTexture);
	}
	return RET_SUCCESS;
}

void CTextureAnim::Reset(bool _bWithAnimIndex)
{
	if (_bWithAnimIndex)
		m_iAnimIdx = 0;
	m_fAccrueDT = 0;
}
