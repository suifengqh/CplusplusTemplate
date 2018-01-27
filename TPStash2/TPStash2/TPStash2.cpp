#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "require.h"
#include "TPStash2.h"
using namespace std;
class Int{
	int i;
public:
	Int(int ii = 0) : i(ii){
		cout<< ">" << i << ' '<<endl;
	}
	~Int(){
		cout<< "~" << i << ' '<<endl;
	}
	operator int() const {return i;}
	friend ostream& operator<<(ostream& os, const Int& x){
		return os << "Int: "<<x.i;
	}
	friend ostream& operator<<(ostream& os, const Int* x){
		return os << "Int: "<<x->i;
	}
};

int main(){
	PStash<Int> ints;
	for(int i = 0; i < 30; ++i){
		ints.add(new Int(i));
	}
	cout<<endl;
	PStash<Int>::iterator it = ints.begin();
	it += 5;
	PStash<Int>::iterator it2 = it + 10;
	for(; it != it2; it++){
		delete it.remove();
	}
	cout<<endl;
	for(it = ints.begin(); it != ints.end(); ++it){
		if(*it){
			cout<<*it<<endl;
		}
	}

	cout<<"\n-------------\n";
	ifstream in("TPStash2.cpp");
	assure(in, "TPStash2.cpp");
	PStash<string> strings;
	string line;
	while(getline(in, line)){
		strings.add(new string(line));
	}
	PStash<string>::iterator sit = strings.begin();
	while(sit != strings.end()){
		cout<<**sit<<endl;
		++sit;
	}
	sit = strings.begin();
	int n = 26;
	sit += n;
	while(sit != strings.end()){
		cout<<n++<<": "<<**sit<<endl;
		++sit;
	}

	return 0;
}