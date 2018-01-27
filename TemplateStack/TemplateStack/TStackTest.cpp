#include "TStack.h"
#include "require.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	ifstream in("TStackTest.cpp");
	assure(in, "TStackTest.cpp");
	Stack<string> testlines;
	string line;
	while(getline(in, line)){
		testlines.push(new string(line));
	}
	int i = 0;
	Stack<string>::iterator it = testlines.begin();
	Stack<string>::iterator* it2 = NULL;
	while(it != testlines.end()){
		cout<<it->c_str()<<endl;
		it++;
		if(++i == 10){
			it2 = new Stack<string>::iterator(it);
		}
	}
	cout<<(*it2)->c_str()<<endl;
	return 0;
}