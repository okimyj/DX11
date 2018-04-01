#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

#include "PathMgr.h"

vector<wstring> g_vecName;
int main()
{
	CPathMgr::Init();
	wstring strExternalPath = CPathMgr::GetExternalPath();
	wstring strScriptMgr = strExternalPath + L"ScriptMgr.cpp";

	// 1. 현재 존재하는 모든 스크립트 파일을 알아낸다. 
	wstring strScriptCode = strExternalPath + L"ScriptCode\\*.h";
	WIN32_FIND_DATA tData = {};
	HANDLE handle = FindFirstFile(strScriptCode.c_str(), &tData);
	if (INVALID_HANDLE_VALUE == handle)
		return 0;
	while(true)
	{
		g_vecName.push_back(wstring(tData.cFileName).substr(0, wcslen(tData.cFileName) - 2));
		if (!FindNextFile(handle, &tData))
			break;
	}
	FindClose(handle);
	
	FILE* pFile = NULL;
	_wfopen_s(&pFile, strScriptMgr.c_str(), L"w");
	//-- 헤더 입력 -----------------------------------------------//
	fwprintf_s(pFile, L"#include \"stdafx.h\"\n");
	fwprintf_s(pFile, L"#include \"ScriptMgr.h\"\n");
	wstring strFormat = L"#include \"ScriptCode\\%s.h\"\n";
	for (UINT i = 0; i < g_vecName.size(); ++i)
	{
		fwprintf_s(pFile, strFormat.c_str(), g_vecName[i].c_str());
	}
	
	//-- 함수 작성 ---------------------------------------------//
	//-- void CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec) --//
	fwprintf_s(pFile, L"\nvoid CScriptMgr::GetScriptInfo(vector<tScriptInfo>& _vec)\n{\n");
	strFormat = L"\t_vec.push_back(tScriptInfo{L\"%s\", typeid(C%s).hash_code()});\n";
	for (UINT i = 0; i < g_vecName.size(); ++i)
	{
		fwprintf_s(pFile, strFormat.c_str(), g_vecName[i].c_str(), g_vecName[i].c_str());
	}
	fwprintf_s(pFile, L"}\n");
	
	//-- CScript * CScriptMgr::GetScript(DWORD _dwTypeID) --//
	fwprintf_s(pFile, L"\nCScript * CScriptMgr::GetScript(DWORD _dwTypeID)\n{\n");
	strFormat = L"\tif(typeid(C%s).hash_code() == _dwTypeID)\n\t\treturn new C%s;\n";
	for (UINT i = 0; i < g_vecName.size(); ++i)
	{
		fwprintf_s(pFile, strFormat.c_str(), g_vecName[i].c_str(), g_vecName[i].c_str());
	}
	fwprintf_s(pFile, L"}\n");
	
	//-- CScript * CScriptMgr::GetScript(const wstring & _strScriptName) --//
	fwprintf_s(pFile, L"\nCScript * CScriptMgr::GetScript(const wstring & _strScriptName)\n{\n");
	strFormat = L"\tif(L\"%s\" == _strScriptName)\n\t\treturn new C%s;\n";
	for (UINT i = 0; i < g_vecName.size(); ++i)
	{
		fwprintf_s(pFile, strFormat.c_str(), g_vecName[i].c_str(), g_vecName[i].c_str());
	}
	fwprintf_s(pFile, L"}\n");

	//-- const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript) --//
	fwprintf_s(pFile, L"\nconst wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)\n{\n");
	strFormat = L"\tif (NULL != dynamic_cast<C%s*>(_pScript))\n\t\treturn L\"%s\";\n";
	for (UINT i = 0; i < g_vecName.size(); ++i)
	{
		fwprintf_s(pFile, strFormat.c_str(), g_vecName[i].c_str(), g_vecName[i].c_str());
	}
	fwprintf_s(pFile, L"}\n");
	fclose(pFile);
}

