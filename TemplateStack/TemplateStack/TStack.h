//Templatized Stack with nested iterator
#ifndef TSTACK_H
#define TSTACK_H
#include <cstdlib>

template<class T> class Stack{
	struct Link{
		T* data;
		Link* next;
		Link(T* dat, Link* nxt): data(dat), next(nxt){}
	}* head;
public:
	Stack(): head(NULL){}
	~Stack();
	void push(T* dat){
		head = new Link(dat, head);
	}
	T* peak() const{
		return head ? head->data : NULL;
	}
	T* pop();

	class iterator;
	friend class iterator;
	class iterator{
		typename Stack<T>::Link* p;
	public:
		iterator(const Stack<T>& tl) : p(tl.head) {}
		iterator(const iterator& tl) : p(tl.p) {}
		iterator() : p(NULL) {}
		bool operator++(){
			if(p->next){
				p = p->next;
			}
			else{
				p = NULL;
			}
			return bool(p);
		}
		bool operator++(int){
			return operator++();
		}
		T* current() const{
			if(!p)
				return NULL;
			return p->data;
		}
		T* operator->() const{
			require(p != NULL, "Stack::iterator::operator->returns NULL");
			return current();
		}
		T* operator*() const{
			return current();
		}
		operator bool() const{
			return bool(p);
		}
		bool operator==(const iterator&) const{
			return p == NULL;
		}
		bool operator!=(const iterator&) const{
			return p != NULL;
		}
 	};
	iterator begin() const{
		return iterator(*this);
	}
	iterator end() const{
		return iterator();
	}
};

template<class T> Stack<T>::~Stack(){
	while(head){
		delete pop();
	}
}

template<class T> T* Stack<T>::pop(){
	if(head == NULL)
		return NULL;
	T* result = head->data;
	Link* oldHead = head;
	head = head->next;
	delete oldHead;
	return result;
}
#endif