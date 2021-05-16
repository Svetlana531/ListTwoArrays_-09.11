#pragma once
#include "ListIterator.h"
#include <iostream>
#include <string>
#include <fstream>

#define DEFAULT_MEM 100

template<class T>
class List
{
private:
	int* pLinks;		// Указатели
	T*   Data;			// Значения
	int  Head;			// Указатель первый элемент
	int	 Mem;			// Выделенная память
	int	 Count;			// Кол-во элементов в списке

public:
	List(int _Mem = DEFAULT_MEM);
	List(List<T>& _list);
	~List();

	int  GetMem();	 					// Выделенная память
	int  GetCount();					// Кол-во элементов в списке
	T	 GetData(int pos);				// Вернуть значение в списке по позиции

	bool isEmpty();						// Проверка на пустоту
	bool isFull();						// Проверка на переполненность

	void ins_Front(T Val);				// Вставка в начало
	void ins_Back(T Val);				// Вставка в конец

	void del_Front();					// Удалить в начале 
	void del_Back();					// Удалить в конце
	void del_List();					// Удалить список

	void ins_Value(int Val, int pos);	// Вставить значение по позиции
	void del_Value(int pos);			// Удалить  значение по позиции

	void print();						// Вывести элементы в консоль

	bool search(int data);				// Найти значение в списке по значению

	List<T>* findSpecialElements(int K);// Возвращает список в котором каждый элемент делится на цело на K

	void WriteFile(std::string path);	// Запись в файл
	void ReadFile(std::string path);	// Чтение с файла 

	friend class ListIterator<T>;		// Для доступа к полям класса
};


template<class T>
List<T>::List(int _Mem)
{
	Mem = _Mem;
	Count = 0;
	pLinks = new int[_Mem];
	Data = new T[_Mem];
	for (int i = 0; i < _Mem; i++)
	{
		pLinks[i] = -5;
		Data[i] = 0;
	}
	Head = -1;
}

template<class T>
inline List<T>::List(List<T>& _list)
{
	Mem = _list.Mem;
	Count = _list.Count;
	pLinks = new int[Mem];
	Data = new int[Mem];
	for (int i = 0; i < _list.Mem; i++)
	{
		pLinks[i] = _list.pLinks[i];
		Data[i] = _list.Data[i];
	}
	Head = _list.Head;
}

template<class T>
inline List<T>::~List()
{
	delete[] pLinks;
	delete[] Data;
	Mem = 0;
}

template<class T>
inline int List<T>::GetMem()
{
	return this->Mem;
}

template<class T>
inline int List<T>::GetCount()
{
	return this->Count;
}

template<class T>
inline T List<T>::GetData(int pos)
{
	if (pos >= 0 && pos < Count)
	{
		return Data[pos];
	}
	else { throw std::logic_error("Going beyond the array boundaries!"); }
}

template<class T>
inline bool List<T>::isEmpty()
{
	return Head == -1;
}

template<class T>
inline bool List<T>::isFull()
{
	return Count == Mem;
}

template<class T>
inline void List<T>::ins_Front(T Val)
{
	if (isFull())
		throw "List is Full";

	if (isEmpty())
	{
		Head = 0;
		this->Data[Head] = Val;
		pLinks[Head] = -1;
	}
	else
	{
		int index = 0;
		while (pLinks[index] != -5)
			index++;

		this->Data[index] = Val;
		pLinks[index] = Head;
		Head = index;
	}
	Count++;
}

template<class T>
inline void List<T>::ins_Back(T Val)
{
	if (isFull())
		throw "List is Full";

	if (isEmpty())
	{
		Head = 0;
		this->Data[Head] = Val;
		pLinks[Head] = -1;
	}
	else
	{
		int last = Head;
		for (int i = 0; i < Count; i++)
		{
			if (pLinks[last] != -1)
				last = pLinks[last];
			else
				break;
		}
		int current = 0;
		for (int i = 0; i < Mem; i++)
		{
			if (pLinks[i] == -5)
			{
				current = i;
				break;
			}
		}
		this->Data[current] = Val;
		pLinks[last] = current;
		pLinks[current] = -1;
	};

	Count++;
}

template<class T>
inline void List<T>::del_Front()
{
	if (isEmpty())
		throw "List is empty";

	if (pLinks[Head] == -1)
	{
		pLinks[Head] = -5;
		Head = -1;
	}
	else
	{
		int first = pLinks[Head];
		pLinks[Head] = -5;
		Head = first;
	}
	Count--;
}

template<class T>
inline void List<T>::del_Back()
{
	if (isEmpty())
		throw "List is empty";

	if (pLinks[Head] == -1)
	{
		pLinks[Head] = -5;
		Head = -1;
	}
	else
	{
		int last = Head;
		int prev = 0;
		for (int i = 0; i < Count; i++)
			if (pLinks[last] != -1)
			{
				prev = last;
				last = pLinks[last];
			}
			else
			{
				pLinks[last] = -5;
				pLinks[prev] = -1;
			}
	}
	Count--;
}

template<class T>
inline void List<T>::del_List()
{
	for (int i = 0; i < Count; i++)
	{
		pLinks[i] = -5;
		Data[i] = 0;
	}
	Head = -1;
	Count = 0;
}

template<class T>
inline void List<T>::ins_Value(int Val, int pos)
{
	if (isFull())
		throw "List is full";

	if (pos < 0 || pos > Count)
		throw "Going beyond the array boundaries!";

	if (pos == 0)
		ins_Front(Val);
	else
	{
		int current = 0;
		while (pLinks[current] != -5)
			current++;

		int previous = Head;
		int counter = 0;

		while (counter != pos - 1)
		{
			if (pLinks[previous] == -1)
				break;
			previous = pLinks[previous];
			counter++;
		}

		this->Data[current] = Val;
		pLinks[current] = pLinks[previous];
		pLinks[previous] = current;
		Count++;
	}
}

template<class T>
inline void List<T>::del_Value(int pos)
{
	if (pos < 0 || pos >= Count)
		throw "Going beyond the array boundaries!";

	if (pos == 0)
	{
		del_Front();
	}
	else
	{
		int del = Head;
		int prev = 0;

		int i = 0;
		while (i != pos)
		{
			if (i == pos - 1)
				prev = del;
			del = pLinks[del];
			i++;
		}

		pLinks[prev] = pLinks[del];
		pLinks[del] = -5;
		Count--;
	}
}


template<class T>
inline void List<T>::print()
{
	if (isEmpty())
		throw "List is empty";

	ListIterator<int> it(*this, Head);
	while(it.CheckNext())
	{
		std::cout << it.GetData() << "->";
		it++;
	}
	std::cout << it.GetData();
}

template<class T>
inline bool List<T>::search(int data)
{
	if (isEmpty())
		throw "List is empty";

	ListIterator<int> it(*this, Head);
	while (it.CheckNext())
	{
		if (it.GetData() == data)
			return true;
		it++;
	}

	return false;
}

template<class T>
inline List<T>* List<T>::findSpecialElements(int K)
{
	List<T>* res = new List<T>(Count);

	ListIterator<int> it(*this, Head);
	while (it.CheckNext())
	{
		if (it.GetData() % K == 0)
		{
			res->ins_Back(it.GetData());
		}
		it++;
	}

	return res;
}

template<class T>
inline void List<T>::WriteFile(std::string path)
{
	if (isEmpty())
		throw "List is empty";

	std::ofstream file(path, std::ios::trunc);
	if (file.is_open())
	{
		ListIterator<int> it(*this, Head);
		while (it.CheckNext())
		{
			file << it.GetData() << "->";
			it++;
		}
		file << it.GetData();
	}
	else
	{
		std::cout << "FILE IS NOT OPEN!\n";
	}
	file.close();
}

template<class T>
inline void List<T>::ReadFile(std::string path)
{
	std::ifstream file(path, std::ios::in);
	if (file.is_open())
	{
		std::string buf;
		int val[250];
		int i_val = 0;
		std::string str;
		while (std::getline(file, buf))
		{
			for (int i = 0; i < buf.size(); i++)
			{
				if (buf[i] == '-' && buf[i + 1] == '>')
				{
					val[i_val] = std::atoi(str.c_str());
					ins_Back(val[i_val]);
					i_val++;
					str.clear();
					i++;
					continue;
				}
				str += buf[i];
			}
		}
		ins_Back(std::atoi(str.c_str()));
	}
	else
	{
		std::cout << "FILE IS NOT OPEN!\n";
	}
	file.close();
}

