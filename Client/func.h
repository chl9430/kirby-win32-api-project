#pragma once

template<typename T>
void Safe_Delete_Vec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		delete _vec[i];
	}

	_vec.clear();
}

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator  iter = _map.begin(); // ���ø����� �̳�Ŭ������ ������ �� �տ� typename�� �ٿ�����Ѵ�

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}

bool WScanf(wchar_t* _pOutBuff, FILE* _pFile);