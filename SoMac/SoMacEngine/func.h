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