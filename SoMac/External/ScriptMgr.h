#pragma once
struct tScriptInfo
{
	wstring strScriptName;
	DWORD dwTypeID;
};
class CScript;
class CGameObject;
class CScriptMgr
{
public:
	static void GetScriptInfo(vector<tScriptInfo>& _vec);
	static CScript* GetScript(DWORD _dwTypeID);
	static CScript* GetScript(const wstring& _strScriptName);
	static const wchar_t* GetScriptName(CScript* _pScript);
private:
	CScriptMgr() {};
	~CScriptMgr() {};
};

