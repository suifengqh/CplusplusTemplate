//Templatized PStash with nested iterator
#ifndef TPSTASH2_H
#define TPSTASH2_H
#include "require.h"
#include <cstdlib>

template<class T, int incr = 20>
class PStash{
	int quantity;
	int next;
	T** storage;
	void inflate(int increase = incr);
public:
	PStash() : quantity(0), storage(NULL), next(0) {}
	~PStash();
	int add(T* element);
	T* operator[](int index) const;
	T* remove(int index);
	int count() const{
		return next;
	}
	//Nested iterator class
	class iterator;
	friend class iterator;
	class iterator{
		typename PStash<T>& ps;
		int index;
	public:
		iterator(PStash& pStash) : ps(pStash), index(0) {}
		iterator(PStash& pStash, bool) : ps(pStash), index(pStash.next) {}
		iterator(const iterator& rv) : ps(rv.ps), index(rv.index) {}
		iterator& operator=(const iterator& rv){
			ps = rv.ps;
			index = rv.index;
			return *this;
		}
		iterator& operator++(){
			require(++index <= ps.next, "PStash::iterator::operator++ moves index out of bounds");
			return *this;
		}
		iterator& operator++(int){
			return operator++();
		}
		iterator& operator--(){
			require(--index >= 0, "PStash::iterator::operator-- moves index out of bounds");
			return *this;
		}
		iterator& operator--(int){
			return operator--();
		}
		iterator& operator+=(int amount){
			require(index + amount < ps.next && index + amount >= 0, "PStash::iterator::operator+= attempt to index out of bounds");
			index += amount;
			return *this;
		}
		iterator& operator-=(int amount){
			require(index - amount < ps.next && index - amount >= 0, "PStash::iterator::operator+= attempt to index out of bounds");
			index -= amount;
			return *this;
		}
		iterator operator+(int amount) const{
			iterator ret(*this);
			ret += amount;
			return ret;
		}
		T* current() const{
			return ps.storage[index];
		}
		T* operator*() const{
			return current();
		}
		T* operator->() const{
			require(ps.storage[index] != NULL, "PStash::iterator::operator-> returns NULL");
			return current();
		}
		T* remove(){
			return ps.remove(index);
		}
		bool operator==(const iterator& rv) const{
			return index == rv.index;
		}
		bool operator!=(const iterator& rv) const{
			return index != rv.index;
		}
	};
	iterator begin(){
		return iterator(*this);
	}
	iterator end(){
		return iterator(*this, true);
	}
};

template<class T, int incr>
PStash<T, incr>::~PStash(){
	for(int i = 0; i < next; ++i){
		delete storage[i];
		storage[i] = NULL;
	}
	delete[] storage;
}

template<class T, int incr>
int PStash<T, incr>::add(T* element){
	if(next >= quantity){
		inflate();
	}
	storage[next++] = element;
	return (next - 1);
}

template<class T, int incr>
inline T* PStash<T, incr>::operator[](int index) const{
	require(index >= 0, "PStash::operator[] index negative");
	if(index >= next)
		return NULL;
	require(storage[index] != NULL, "PStash::operator[] returned null pointer");
	return storage[index];
}

template<class T, int incr>
T* PStash<T, incr>::remove(int index){
	T* v = operator[](index);
	storage[index] = NULL;
	return v;
}

template<class T, int incr>
void PStash<T, incr>::inflate(int increase){
	const int tsz = sizeof(T*);
	T** st = new T*[quantity + increase];
	memset(st , 0 , tsz * (quantity + increase));
	memcpy(st, storage, tsz * quantity);
	quantity += increase;
	delete[] storage;
	storage = st;
}
#endif