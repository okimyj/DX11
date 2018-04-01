#include "stdafx.h"
#include "ScriptMgr.h"
#include "ScriptCode\BulletScript.h"
#include "ScriptCode\CameraScript.h"
#include "ScriptCode\EnemyScript.h"
#include "ScriptCode\ItemScript.h"
#include "ScriptCode\PlayerPlanet.h"
#include "ScriptCode\PlayerScript.h"

void CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec)
{
	_vec.push_back(tScriptInfo{L"BulletScript", typeid(CBulletScript).hash_code()});
	_vec.push_back(tScriptInfo{L"CameraScript", typeid(CCameraScript).hash_code()});
	_vec.push_back(tScriptInfo{L"EnemyScript", typeid(CEnemyScript).hash_code()});
	_vec.push_back(tScriptInfo{L"ItemScript", typeid(CItemScript).hash_code()});
	_vec.push_back(tScriptInfo{L"PlayerPlanet", typeid(CPlayerPlanet).hash_code()});
	_vec.push_back(tScriptInfo{L"PlayerScript", typeid(CPlayerScript).hash_code()});
}

CScript * CScriptMgr::GetScript(DWORD _dwTypeID)
{
	if(typeid(CBulletScript).hash_code() == _dwTypeID)
		return new CBulletScript;
	if(typeid(CCameraScript).hash_code() == _dwTypeID)
		return new CCameraScript;
	if(typeid(CEnemyScript).hash_code() == _dwTypeID)
		return new CEnemyScript;
	if(typeid(CItemScript).hash_code() == _dwTypeID)
		return new CItemScript;
	if(typeid(CPlayerPlanet).hash_code() == _dwTypeID)
		return new CPlayerPlanet;
	if(typeid(CPlayerScript).hash_code() == _dwTypeID)
		return new CPlayerScript;
}

CScript * CScriptMgr::GetScript(const wstring & _strScriptName)
{
	if(L"BulletScript" == _strScriptName)
		return new CBulletScript;
	if(L"CameraScript" == _strScriptName)
		return new CCameraScript;
	if(L"EnemyScript" == _strScriptName)
		return new CEnemyScript;
	if(L"ItemScript" == _strScriptName)
		return new CItemScript;
	if(L"PlayerPlanet" == _strScriptName)
		return new CPlayerPlanet;
	if(L"PlayerScript" == _strScriptName)
		return new CPlayerScript;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	if (NULL != dynamic_cast<CBulletScript*>(_pScript))
		return L"BulletScript";
	if (NULL != dynamic_cast<CCameraScript*>(_pScript))
		return L"CameraScript";
	if (NULL != dynamic_cast<CEnemyScript*>(_pScript))
		return L"EnemyScript";
	if (NULL != dynamic_cast<CItemScript*>(_pScript))
		return L"ItemScript";
	if (NULL != dynamic_cast<CPlayerPlanet*>(_pScript))
		return L"PlayerPlanet";
	if (NULL != dynamic_cast<CPlayerScript*>(_pScript))
		return L"PlayerScript";
}
