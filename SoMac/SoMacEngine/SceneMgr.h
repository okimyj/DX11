#pragma once
#include "global.h"
class CScene;
class CSceneMgr
{
	SINGLE(CSceneMgr);
private:
	CScene*		m_pCurScene;
	CScene*		m_pPrevScene;
public :
	
public:
	void Init();
	int Update();
	void Render();
//	void ChangeScene()

};

