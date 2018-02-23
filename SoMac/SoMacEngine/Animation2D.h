#pragma once
#include "Animation.h"
#include "ResPtr.h"
class CTexture;
struct tFrameInfo
{
	CResPtr<CTexture>	pTexture;
	Vec2							vLeftTop;			// Textrue ���� width, height��ŭ ������ ���� ��ġ.
	float							fWidth;
	float							fHeight;
	float							fTerm;			// �ش� frame �� �ӹ��� �ִ� �ð�.
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
	UINT							m_iCurFrame	;			// ���� ������ index.
	float							m_fAccTime;		// �����ð��� frameInfo �� fTerm�� �Ѿ�� ���� ���� ���������� �ѱ��.

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

