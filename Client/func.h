#pragma once

template<typename T1, typename T2>
void Safe_Delete_Map(map<T1, T2>& _map)
{
	typename map<T1, T2>::iterator  iter = _map.begin(); // 템플릿에서 이너클래스를 쓰려면 맨 앞에 typename을 붙여줘야한다

	for (; iter != _map.end(); ++iter)
	{
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}