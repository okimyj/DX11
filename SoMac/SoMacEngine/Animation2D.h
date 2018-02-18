#pragma once
#include "Animation.h"
#include "ResPtr.h"
class CTexture;
class CMaterial;
struct tFrameInfo
{
	CResPtr<CTexture>	pTexture;
	Vec2							vLeftTop;			// Textrue ���� width, height��ŭ ������ ���� ��ġ.
	float							fWidth;
	float							fHeight;
	float							fTerm;			// �ش� frame �� �ӹ��� �ִ� �ð�.

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
	virtual int FinalUpdate();
	virtual int ApplyData(CMaterial* pMaterial);
public:
	CAnimation2D();
	virtual ~CAnimation2D();
};

