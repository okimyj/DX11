#pragma once
#include "global.h"
class CTexture;
class CMeshRender;
class CTextureAnim
{
private:
	CMeshRender*		m_pTargetMesh;
	vector<CTexture*>		m_vecTexture;
	bool						m_bLoop;
	float						m_fFPS;
	float						m_fAccrueDT;
	int							m_iAnimIdx;

	wstring					m_strAnimPrefix;
	int							m_iStartIdx;
	int							m_iEndIdx;
public:
	void SetTargetMesh(CMeshRender* _pMesh) { m_pTargetMesh = _pMesh; }
	void LoadTexture(const wstring& _strPrefix, int _iStartIdx, int _iEndIdx);
	// call TextrueAnimator.
	void Init();
	int Update(float _dt);		
	void Reset(bool _bWithAnimIndex=true);


public:
	CTextureAnim();
	CTextureAnim(CMeshRender* _pTargetMeshRender, const wstring& _strAnimPrefix, int _iStartIdx, int _iEndIdx, float _fFPS, bool _bLoop);
	virtual ~CTextureAnim();
};

