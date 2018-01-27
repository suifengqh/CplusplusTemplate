#ifndef TPSTASH_H
#define TPSTASH_H
#include <iostream>
using namespace std;

template<class T , int incr = 10>
class PStash
{
	int quantity;//Number of storage spaces
	int next;//Next empty space
	T** storage;
	void inflate(int increase = incr);
public:
	PStash() : quantity(0) , next(0) , storage(NULL) {}
	~PStash();
	int add(T* element);
	T* operator[](int index) const;//Fetch
	T* remove(int index);
	int count() const {return next;}
};

template<class T , int incr>
int PStash<T , incr>::add(T* element)
{
	if(next >= quantity)
	{
		inflate(incr);
	}
	storage[next++] = element;
	return next-1;
}

template<class T , int incr>
PStash<T , incr>::~PStash()
{
	for(int i = 0 ; i < next ; i++)
	{
		delete storage[i];
		storage[i] = NULL;
	}
	delete[] storage;
}

template<class T , int incr>
T* PStash<T , incr>::operator[](int index) const
{
	if(index < 0 || index >= next)
	{
		cout<<"PStash::operator[] index invaild."<<endl;
		return NULL;
	}
	if(storage[index] == NULL)
	{
		cout<<"PStash::operator[] returned null pointer."<<endl;
		return NULL;
	}
	return storage[index];
}

template<class T , int incr>
T* PStash<T , incr>::remove(int index)
{
	T* v = operator[](index);
	if(v != NULL)
	{
		storage[index] = NULL;
	}
	return v;
}

template<class T , int incr>
void PStash<T , incr>::inflate(int increase /* = incr */)
{
	const int psz = sizeof(T*);
	T** st = new T*[quantity + increase];
	memset(st , 0 , psz * (quantity + increase));
	memcpy(st , storage , quantity * psz);
	quantity += increase;
	delete[] storage;
	storage = st;
}
#endif//TPSTASH_H