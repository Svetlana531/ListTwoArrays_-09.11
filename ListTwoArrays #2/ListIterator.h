#pragma once
#include "List.h"

template<class T>
class List;

template<class T>
class ListIterator
{
private:
	List<T>& list;
	int index;
public:
	ListIterator(List<T>& _list, int _index) : list(_list), index(_index) {}
	~ListIterator() {}

	bool CheckNext()
	{
		return (list.pLinks[index] != -1);
	}
	void GoNext()
	{
		if (!CheckNext())
			throw "List is end!";
		index = list.pLinks[index];
	}

	ListIterator<T> operator++(int)
	{
		GoNext();
		return (*this);
	}

	T GetData()
	{
		return list.Data[index];
	}
};