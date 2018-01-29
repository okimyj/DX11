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
	void AddAnimation(const wstring& _strKey, CTextureAnim* _pAnim) 
	{ 
		m_mapAnim.insert(make_pair(_strKey, _pAnim)); 
		int a = 1;
	}
	void Play(const wstring& _strName);
	virtual void Start();
	virtual int Update();
public:
	CTextureAnimator();
	virtual ~CTextureAnimator();
};

