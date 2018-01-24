#pragma once
#include "global.h"
// �ϳ��� Scene���� �������� Layer�� �ִ�.
// �ϳ��� Layer ���� �������� GameObject�� ��ġ�ȴ�. 
// Layer���� �浹üũ ó���� �����ϴ�. 
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

