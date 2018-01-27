//Simples stack template with nested iterator
#ifndef ITERSTACKTEMPLATE_H
#define ITERSTACKTEMPLATE_H
#include "require.h"
#include <iostream>

template<typename T, int ssize = 100>
class StackTemplate{
	T stack[ssize];
	int top;
public:
	StackTemplate() : top(0){}
	void push(const T& i){
		require(top < ssize, "Too many push()es");
		stack[top++] = i;
	}
	T pop(){
		require(top > 0, "Too many pop()es");
		return stack[--top];
	}
	class iterator;
	friend class iterator;
	class iterator{
		StackTemplate& s;
		int index;
	public:
		iterator(StackTemplate& st): s(st), index(0){}
		iterator(StackTemplate& st, bool): s(st), index(s.top){}
		T operator*() const { return s.stack[index]; }
		T operator++(){
			require(index < s.top, "iterator moved out of range");
			return s.stack[++index];
		}
		T operator++(int){
			require(index < s.top, "iterator moved out of range");
			return s.stack[index++];
		}
		iterator& operator+=(int amount){
			require(index + amount < s.top, "StackTemplate::iterator::operator+=() tried to moved out of range");
			index += amount;
			return *this;
		}
		bool operator==(const iterator& rv) const{
			return index == rv.index;
		}
		bool operator!=(const iterator& rv) const{
			return index != rv.index;
		}
		friend std::ostream& operator<<(std::ostream& os, const iterator& it){
			return os<<*it;
		}
	};
	iterator begin(){
		return iterator(*this);
	}
	iterator end(){
		return iterator(*this, true);
	}
};

#endif // ITERSTACKTEMPLATE_H