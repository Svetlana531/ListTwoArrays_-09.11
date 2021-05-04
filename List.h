#pragma once

#include "ListIterator.h"
#include <iostream>
#include <string>
#include <fstream>

#define DEFAULT_MEM 10

class List
{
protected:
	int* First;		 // Элементы в начале
	int* Last;		 // Элементы в конце
	
	ListIterator it; // Итератор

	int memF;		 // Кол-во выделенной памяти начала
	int memL;		 // Кол-во выделенной памяти конца
	void Resize(bool CheckIndex);  // Перевыделение памяти

public:
	List();
	~List();

	int GetListLenght();	 	 // Длинна спискаx
	bool IsEmpty();				 // Проверка на пустоту

	void InsFirst(int Val);		 // Вставка в начало
	void InsLast(int Val);		 // Вставка в конец

	void DelFirst();			 // Удалить в начале 
	void DelLast();				 // Удалить в конце
	void DelList();				 // Удалить список

	void InsValue(int Val, int pos);	// Вставить значение по позиции
	void DelValue(int pos);				// Удалить  значение по позиции

	void print();						// Вывести элементы в консоль

	bool search(int data);				// Найти значение в списке по значению
	int	 get(int pos);					// Вернуть значение в списке по позиции
	bool IsSort();						// Отсортирован ли список по возрастанию

	List* findSpecialElements(int K);	// Возвращает список в котором каждый элемент делится на цело на K

	void WriteFile(std::string path);	// Запись в файл
	void ReadFile(std::string path);	// Чтение с файла 
};

inline void List::Resize(bool CheckIndex)
{
	// false = First, true = Last
	if (!CheckIndex)
	{
		int* tmp = new int[it.curr_F()];

		for (int i = 0; i < it.curr_F(); i++)
		{
			tmp[i] = First[i];
		}

		delete First;
		memF += DEFAULT_MEM;
		First = new int[memF];

		for (int i = 0; i < it.curr_F(); i++)
		{
			First[i] = tmp[i];
		}
	}
	else
	{
		int* tmp = new int[it.curr_L()];

		for (int i = 0; i < it.curr_L(); i++)
		{
			tmp[i] = Last[i];
		}

		delete Last;
		memL += DEFAULT_MEM;
		Last = new int[memL];

		for (int i = 0; i < it.curr_L(); i++)
		{
			Last[i] = tmp[i];
		}
	}
}

inline List::List()
{
	memF = DEFAULT_MEM;
	memL = DEFAULT_MEM;

	First = new int[memF];
	Last  = new int[memL];
}

inline List::~List()
{
	delete First;
	delete Last;
	memF = 0;
	memL = 0;
	it.~ListIterator();
}

inline int List::GetListLenght()
{
	return it.GetLenght();
}

inline bool List::IsEmpty()
{
	if (GetListLenght() == 0) return true;
	else return false;
}

inline void List::InsFirst(int Val)
{
	if (it.curr_F() + 1 <= memF)
	{
		int* tmp = new int[it.curr_F() + 1];

		for (int i = 0; i < it.curr_F(); i++)
		{
			tmp[i + 1] = First[i];
		}
		tmp[0] = Val;
		it.next_F();

		for (int i = 0; i < it.curr_F(); i++)
		{
			First[i] = tmp[i];
		}
	}
	else
	{
		Resize(false);
		InsFirst(Val);
	}
}

inline void List::InsLast(int Val)
{
	if (it.curr_L() + 1 <= memL)
	{
		Last[it.curr_L()] = Val;
		it.next_L();
	}
	else
	{
		Resize(true);
		InsLast(Val);
	}
}

inline void List::DelFirst()
{
	if (it.curr_F() > 0)
	{
		for (int i = 0; i < it.curr_F() - 1; i++)
		{
			First[i] = First[i + 1];
		}
		it.del_F();
	}
}

inline void List::DelLast()
{
	if (it.curr_L() > 0)
	{
		for (int i = 0; i < it.curr_L() - 1; i++)
		{
			Last[i] = Last[i + 1];
		}
		it.del_L();
	}
}


inline void List::DelList()
{
	delete First;
	delete Last;

	First = new int[DEFAULT_MEM];
	Last = new int[DEFAULT_MEM];

	memF = DEFAULT_MEM;
	memL = DEFAULT_MEM;
	
	it.~ListIterator();
}

inline void List::InsValue(int Val, int pos)
{
	if (pos == 0)
	{
		InsFirst(Val);
		return;
	}
	if (pos > 0 && pos <= GetListLenght())
	{
		if (pos < it.curr_F())
		{
			if (it.curr_F() + 1 > memF) { Resize(false); }

			int* left = new int[it.curr_F() / 2 + 1];
			int* right = new int[it.curr_F() / 2 + 1];

			for (int i = 0; i < pos; i++)
			{
				left[i] = First[i];
			}

			int j = 0;
			for (int i = pos; i < it.curr_F(); i++)
			{
				right[j] = First[i];
				j++;
			}

			for (int i = 0; i < pos; i++)
			{
				First[i] = left[i];
			}
			First[pos] = Val;

			it.next_F();
			j = 0;
			for (int i = pos + 1; i < it.curr_F(); i++)
			{
				First[i] = right[j];
				j++;
			}
		}
		else
		{
			if (it.curr_L() + 1 > memL) { Resize(true); }

			int* left = new int[it.curr_L() / 2 + 1];
			int* right = new int[it.curr_L() / 2 + 1];

			for (int i = 0; i < pos - it.curr_F(); i++)
			{
				left[i] = Last[i]; 
			}

			int j = 0;
			for (int i = pos - it.curr_F(); i < it.curr_L(); i++)
			{
				right[j] = Last[i];
				j++;
			}

			for (int i = 0; i < pos - it.curr_F(); i++)
			{
				Last[i] = left[i];
			}
			Last[pos - it.curr_F()] = Val;

			it.next_L();
			j = 0;
			for (int i = pos + 1 - it.curr_F(); i < it.curr_L(); i++)
			{
				Last[i] = right[j];
				j++;
			}
		}
	}
	else { throw "Error: index was outside the array"; }
}

inline void List::DelValue(int pos)
{
	if (pos == 0)
	{
		DelFirst();
	}
	if (pos == GetListLenght())
	{
		DelLast();
	}
	if (pos > 0 && pos < GetListLenght())
	{
		if (pos <= it.curr_F())
		{
			int* tmp = new int[it.curr_F()];
			int j = 0;
			for (int i = 0; i < it.curr_F(); i++)
			{
				if (i == pos) { continue; }
				tmp[j] = First[i];
				j++;
			}
			it.del_F();
			for (int i = 0; i < it.curr_F(); i++)
			{
				First[i] = tmp[i];
			}
		}
		else
		{
			int* tmp = new int[it.curr_L()];
			int j = 0;
			for (int i = 0; i < it.curr_L(); i++)
			{
				if (i == pos - it.curr_F()) { continue; }
				tmp[j] = Last[i];
				j++;
			}
			it.del_L();
			for (int i = 0; i < it.curr_L(); i++)
			{
				Last[i] = tmp[i];
			}
		}
	}
}
 

inline void List::print()
{
	for (int i = 0; i < it.curr_F(); i++)
	{
		std::cout << First[i] << "->";
	}
	for (int i = 0; i < it.curr_L(); i++)
	{
		std::cout << Last[i] << "->";
	}
	std::cout << "Size: " << GetListLenght() << std::endl;
}

inline bool List::search(int data)
{
	for (int i = 0; i < it.curr_F(); i++)
	{
		if (First[i] == data) { return true; }
	}
	for (int i = 0; i < it.curr_L(); i++)
	{
		if (Last[i] == data) { return true; }
	}
	return false;
}

inline int List::get(int pos)
{
	if (pos >= 0 && pos <= GetListLenght())
	{
		if (pos <= it.curr_F())
		{
			for (int i = 0; i < it.curr_F(); i++)
			{
				if (i == pos) { return First[i]; }
			}
		}
		else
		{
			for (int i = 0; i < it.curr_L(); i++)
			{
				if (i == pos - it.curr_F()) { return Last[i]; }
			}
		}
	}
	return -1000;	// Not found
}

inline bool List::IsSort()
{
	for (int i = 0; i < it.curr_F() - 1; i++)
	{
		if (First[i] > First[i + 1]) { return false; }
	}
	for (int i = 0; i < it.curr_L() - 1; i++)
	{
		if (Last[i] > Last[i + 1]) { return false; }
	}
}

inline List* List::findSpecialElements(int K)
{
	List* res = new List();

	for (int i = 0; i < it.curr_F() - 1; i++)
	{
		if (First[i] % K == 0) { res->InsFirst(First[i]); }
	}
	for (int i = 0; i < it.curr_L() - 1; i++)
	{
		if (Last[i] % K == 0) { res->InsLast(Last[i]); }
	}
	
	return res;
}

inline void List::WriteFile(std::string path)
{
	std::ofstream file(path, std::ios::trunc);
	if (file.is_open())
	{
		for (int i = 0; i < it.curr_F(); i++)
		{
			file << First[i] << "->";
		}
		for (int i = 0; i < it.curr_L(); i++)
		{
			file << Last[i] << "->";
		}
	}
	else
	{
		std::cout << "FILE IS NOT OPEN!\n";
	}
	file.close();
}

inline void List::ReadFile(std::string path)
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
					InsLast(val[i_val]);
					i_val++;
					str.clear();
					i++;
					continue;
				}
				str += buf[i];
			}
		}
	}
	else
	{
		std::cout << "FILE IS NOT OPEN!\n";
	}
	file.close();
}
