#include "IterStackTemplate.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(){
	StackTemplate<int> is;
	for(int i = 0; i < 20; ++i){
		is.push(i);
	}
	cout<<"Traverse the whole StackTemplate"<<endl;
	StackTemplate<int>::iterator it = is.begin();
	while(it != is.end()){
		cout<<it++<<endl;
	}
	cout<<"Traverse a portion"<<endl;
	StackTemplate<int>::iterator start = is.begin(), end = is.begin();
	start += 5;
	end += 15;
	cout<<"start = "<<start<<endl;
	cout<<"end = "<<end<<endl;
	while(start != end){
		cout<<start++<<endl;
	}
	ifstream in("IterStackTemplateTest.cpp");
	assure(in, "IterStackTemplateTest.cpp");
	string line;
	StackTemplate<string> strings;
	while(getline(in, line)){
		strings.push(line);
	}
	StackTemplate<string>::iterator sb = strings.begin(), se = strings.end();
	while(sb != se){
		cout<<sb++<<endl;
	}
	return 0;
}