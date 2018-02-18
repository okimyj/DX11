#pragma once
#include "Component.h"
class CAnimation;
class CAnimator :
	public CComponent
{
private:
	map<wstring, CAnimation*>		m_mapAnim;
	CAnimation*								m_pCurAnim;
	bool											m_bRepeat;
public:
	virtual int Update() { return 0; }
	virtual int FinalUpdate();
public:
	void PlayAnimation(const wstring& _strKey, bool _bRepeat = true);
	void LoadAnimation2D(const wstring& _strKey, const wstring& _strFolderPath);
public:
	virtual CLONE(CAnimator);
	CAnimator();
	virtual ~CAnimator();
};

