#pragma once
#include "global.h"
// 하나의 Scene에는 여러개의 Layer가 있다.
// 하나의 Layer 에는 여러개의 GameObject가 배치된다. 
// Layer간의 충돌체크 처리가 가능하다. 
class CGameObject;
class CLayer
{
private:
	wstring							m_strLayerName;
	list<CGameObject*>		m_listObj;
public:
	void Awake();
	void Start();
	int Update();
	int LateUpdate();
	int FinalUpdate();

	void Render();

public:
	CLayer();
	~CLayer();
};

