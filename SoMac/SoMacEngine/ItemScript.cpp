#include "ItemScript.h"



void CItemScript::Awake()
{
}

void CItemScript::Start()
{
	Transform()->SetLocalScale(Vec3(30.f, 30.f, 1.f));
}

int CItemScript::Update()
{
	return 0;
}

CItemScript::CItemScript()
{
}


CItemScript::~CItemScript()
{
}
