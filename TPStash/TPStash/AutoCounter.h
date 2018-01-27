#ifndef AUTOCOUNTER_H
#define AUTOCOUNTER_H
#include <iostream>
#include <set>
#include <string>
using namespace std;

class AutoCounter
{
	static int count;
	int id;
	class CleanupCheck
	{
		std::set<AutoCounter*> trace;
	public:
		void add(AutoCounter* ap)
		{
			trace.insert(ap);
		}
		void remove(AutoCounter* ap)
		{
			if(trace.erase(ap) != 1)
			{
				cout<<"Attempt to delete AutoCounter twice."<<endl;
			}
		}
		~CleanupCheck()
		{
			cout<<"~CleanupCheck()"<<endl;
			if(trace.size() != 0)
			{
				cout<<"All AutoCounter objects not cleaned up."<<endl;
			}
		}
	};
	static CleanupCheck verifier;
	AutoCounter() : id(count++)
	{
		verifier.add(this);
		cout<<"created["<<id<<"]"<<endl;
	}
	AutoCounter(const AutoCounter&);
	void operator=(const AutoCounter&);
public:
	static AutoCounter* create()
	{
		return new AutoCounter();
	}
	~AutoCounter()
	{
		cout<<"destorying["<<id<<"]"<<endl;
		verifier.remove(this);
	}
	friend ostream& operator<<(ostream& os , const AutoCounter& ac)
	{
		return os<<"AutoCounter"<<ac.id;
	}
	friend ostream& operator<<(ostream& os , const AutoCounter* ac)
	{
		return os<<"AutoCounter"<<ac->id;
	}
};
#endif//AUTOCOUNTER_H