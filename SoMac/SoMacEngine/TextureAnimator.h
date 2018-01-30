#pragma once
#include "Component.h"
class CTexture;
class CTextureAnim;
class CTextureAnimator :
	public CComponent
{
private:
	map<wstring, CTextureAnim*>			m_mapAnim;		// key : anim name.
	CTextureAnim*									m_pCurrentAnim;

public:
	void AddAnimation(const wstring& _strKey, CTextureAnim* _pAnim);
	void Play(const wstring& _strName);
public:
	virtual CTextureAnimator* Clone() { return new CTextureAnimator(*this); }
	virtual void Start();
	virtual int Update();
public:
	CTextureAnimator();
	CTextureAnimator(const CTextureAnimator& _pOther);
	virtual ~CTextureAnimator();
};

