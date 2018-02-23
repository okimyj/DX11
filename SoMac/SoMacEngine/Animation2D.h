#pragma once
#include "Animation.h"
#include "ResPtr.h"
class CTexture;
struct tFrameInfo
{
	CResPtr<CTexture>	pTexture;
	Vec2							vLeftTop;			// Textrue 에서 width, height만큼 가져올 기준 위치.
	float							fWidth;
	float							fHeight;
	float							fTerm;			// 해당 frame 에 머물러 있는 시간.
};
struct tDescInfo
{
	wstring		strTexName;
	wstring		strAnimName;
	Vec2			vLeftTop;
	Vec2			vSize;
	UINT			iFrameCount;
};
class CAnimation2D :
	public CAnimation
{
private:
	vector<tFrameInfo>	m_vecFrame;
	UINT							m_iCurFrame	;			// 현재 프레임 index.
	float							m_fAccTime;		// 누적시간이 frameInfo 의 fTerm을 넘어서는 순간 다음 프레임으로 넘긴다.

public:
	virtual bool Load(const wstring& _strFolderPath);
	static bool LoadMultiAnimation(const wstring& _strFolderPath, const wstring& _strFullPath, map<wstring, CAnimation*> _mapAnim);
	virtual int FinalUpdate();
	virtual int ApplyData();
private:
	void AddFrame(const tFrameInfo& _tFrame) { m_vecFrame.push_back(_tFrame); }
	virtual CLONE(CAnimation2D);
public:
	CAnimation2D();
	virtual ~CAnimation2D();
};

