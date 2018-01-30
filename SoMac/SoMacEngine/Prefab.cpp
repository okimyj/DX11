#include "Prefab.h"
#include "GameObject.h"

CPrefab::CPrefab(CGameObject * _pObj)
	: m_pObj(_pObj)
{

}

CPrefab::~CPrefab()
{
}

CGameObject * CPrefab::Instantiate()
{
	
	return m_pObj->Clone();
}
