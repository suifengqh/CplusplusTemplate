#include "AutoCounter.h"
#include "TPStash.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	PStash<AutoCounter> acStash;
	for(int i = 0 ; i < 10 ; i++)
	{
		acStash.add(AutoCounter::create());
	}
	cout<<"Removing 5 manually:"<<endl;
	for(int i = 0 ; i < 5 ; i++)
	{
		delete acStash.remove(i);
	}
	cout<<"Remove two without deleting them:"<<endl;
	cout<<acStash.remove(5)<<endl;
	cout<<acStash.remove(6)<<endl;
	cout<<"The destructor cleans up the rest:"<<endl;
	ifstream in("TPStashTest.cpp");
	PStash<string> stringStash;
	string line;
	while(getline(in , line))
	{
		stringStash.add(new string(line));
	}
	for(int i = 0 ; stringStash[i] ; i++)
	{
		cout<<"stringStash["<<i<<"] = "<<*stringStash[i]<<endl;
	}
	return 0;
}