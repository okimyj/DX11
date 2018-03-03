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
	void ChangeAnimation(const wstring& _strKey, UINT _iStartFrameIdx = 0);
	void ApplyData();
	static void Disable();

	map<wstring, CAnimation*>& GetAnimationMap() { return m_mapAnim; }
	CAnimation* GetCurAnim() { return m_pCurAnim; }
	bool IsRepeat() { return m_bRepeat; }
	void SetRepeat(bool _bRepeat) { m_bRepeat = _bRepeat; }

private:
	CAnimation* FindAnimation(const wstring& _strKey);
public:
	virtual CLONE(CAnimator);
	CAnimator();
	CAnimator(const CAnimator& _other);
	virtual ~CAnimator();
};

