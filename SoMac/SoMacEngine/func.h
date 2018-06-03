#pragma once
#include "global.h"
int GetSizeOfFormat(DXGI_FORMAT _eFormat);

template<typename T>
void Safe_Delete_List(list<T>& _list)
{
	list<T>::iterator iter = _list.begin();

	for (; iter != _list.end(); ++iter)
	{
		SAFE_DELETE(*iter);
	}
	
}

template<typename T>
void Safe_Delete_List_ResPtr(list<T>& _list)
{
	list<T>::iterator iter = _list.begin();

	for (; iter != _list.end(); ++iter)
	{
		(*iter).Delete();
	}

}


template<typename T>
void Safe_Delete_Vector(vector<T> _vec)
{
	for (int i = 0; i < _vec.size(); ++i)
	{
		SAFE_DELETE(_vec[i]);
	}
}

template<typename T>
void Safe_Delete_Vector_ResPtr(vector<T> _vec)
{
	for (int i = 0; i < _vec.size(); ++i)
	{
		_vec[i].Delete();
	}
}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2> _map)
{
	map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
}

template<typename T1, typename T2>
void Safe_Delete_Map_ResPtr(map<T1, T2> _map)
{
	map<T1, T2>::iterator iter = _map.begin();
	for (; iter != _map.end(); ++iter)
	{
		iter->second.Delete();
	}
}
void WriteBool(const bool& _bool, FILE* _pFile);
bool ReadBool(FILE* _pFile);
void WriteByte(const BYTE& _byte, FILE* _pFile);
BYTE ReadByte(FILE* _pFile);
void WriteFloat(const float& _float, FILE* _pFile);
float ReadFloat(FILE* _pFile);
void WriteInt(const int& _int, FILE* _pFile);
int ReadInt(FILE* _pFile);
void WriteUINT(const UINT& _i, FILE* _pFile);
UINT ReadUINT(FILE* _pFile);
void WriteVec3(const Vec3& _vec, FILE* _pFile);
Vec3 ReadVec3(FILE* _pFile);
void WriteVec2(const Vec2& _vec, FILE* _pFile);
Vec2 ReadVec2(FILE* _pFile);
void WriteWString(const wstring& _str, FILE* _pFile);
wchar_t* ReadWString(FILE* _pFile);
template<typename T>
void WriteValue(const T& _value, FILE* _pFile)
{
	fwrite(&_value, sizeof(T), 1, _pFile);
}
template<typename T>
T ReadValue(FILE* _pFile)
{
	T value;
	fread(&value, sizeof(T), 1, _pFile);
	return value;
}
class CRes;
template<typename T>
void WriteResourceKey(T* _pRes, FILE* _pFile)
{
	BYTE bRes = 0;
	if (NULL != _pRes)
		bRes = 1;

	WriteByte(bRes, _pFile);

	if (bRes)
	{
		WriteWString(_pRes->GetKey(), _pFile);
	}
}
wchar_t* ReadResourceKey(FILE* _pFile);
