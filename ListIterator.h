#pragma once

class ListIterator {
private:
	int indexF;		
	int indexL;

public:
	ListIterator();
	~ListIterator();

	int GetLenght();

	int curr_F();
	int curr_L();

	void next_F();
	void next_L();

	void del_F();
	void del_L();


};

inline ListIterator::ListIterator()
{
	indexF = 0;
	indexL = 0;
}

inline ListIterator::~ListIterator()
{
	indexF = 0;
	indexL = 0;
}

int ListIterator::GetLenght()
{
	return indexF + indexL;
}

inline int ListIterator::curr_F()
{
	return indexF;
}

inline int ListIterator::curr_L()
{
	return indexL;
}

inline void ListIterator::next_F()
{
	indexF++;
}

inline void ListIterator::next_L()
{
	indexL++;
}

inline void ListIterator::del_F()
{
	if (indexF != 0)
	{
		indexF--;
	}
}

inline void ListIterator::del_L()
{
	if (indexL != 0)
	{
		indexL--;
	}
}