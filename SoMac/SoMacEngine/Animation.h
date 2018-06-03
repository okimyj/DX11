#pragma once
#include "global.h"
class CAnimator;
class CAnimation
{
protected:
	CAnimator*		m_pAnimator;
	wstring				m_strKey;
	bool					m_bEnable;

	UINT					m_iCurFrame;
	float					m_fAccTime;
	bool					m_b2DAnim;

public:
	void SetKey(const wstring& _strKey) { m_strKey = _strKey; }
	const wstring& GetKey() { return m_strKey; }

	void SetAnimator(CAnimator* _pAnimator) { m_pAnimator = _pAnimator; }
	void SetFrameIdx(UINT _iFrameIdx) { m_iCurFrame = _iFrameIdx; }

	virtual bool Load(const wstring& _strFolderPath, const wstring& _strFullPath) = 0;
	virtual int FinalUpdate() = 0;
	virtual int ApplyData()=0;
	void SetEnable(bool _bEnable) { m_bEnable = _bEnable; }
	bool IsEnable() { return m_bEnable; }
	bool Is2DAnim() { return m_b2DAnim; }
public:
	void Save(FILE* _pFile);
	void Load(FILE* _pFile);
	virtual CAnimation* Clone() = 0;
	CAnimation();
	virtual ~CAnimation();
};

