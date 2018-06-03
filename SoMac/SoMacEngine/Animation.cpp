#include "Animation.h"



CAnimation::CAnimation()
	: m_bEnable(false)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_b2DAnim(false)
{
}


CAnimation::~CAnimation()
{
}


void CAnimation::Save(FILE * _pFile)
{
	WriteResourceKey(this, _pFile);
	WriteBool(m_bEnable, _pFile);
	WriteInt(m_iCurFrame, _pFile);
}

void CAnimation::Load(FILE * _pFile)
{
	m_strKey = ReadResourceKey(_pFile);
	m_bEnable = ReadBool(_pFile);
	m_iCurFrame = ReadInt(_pFile);
}