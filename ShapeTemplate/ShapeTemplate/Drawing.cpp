#include "TPStash2.h"
#include "TStack.h"
#include "Shape.h"
#include <vector>
using namespace std;

class Drawing : public PStash<Shape>{
public:
	~Drawing(){cout<<"~Drawing"<<endl;}
};

class Plan : public Stack<Shape>{
public:
	~Plan(){cout<<"~Plan"<<endl;}
};

class Schematic : public vector<Shape*>{
public:
	~Schematic(){cout<<"~Schematic"<<endl;}
};

template<class Iter>
void drawAll(Iter start, Iter end){
	while(start != end){
		(*start)->draw();
		++start;
	}
}

int main(){
	Drawing d;
	d.add(new Circle);
	d.add(new Square);
	d.add(new Line);
	
	Plan p;
	p.push(new Line);
	p.push(new Square);
	p.push(new Circle);

	Schematic s;
	s.push_back(new Square);
	s.push_back(new Circle);
	s.push_back(new Line);

	Shape* sarray[] = {
		new Circle, new Square, new Line
	};
	cout<<"Drawing d"<<endl;
	drawAll(d.begin(), d.end());
	cout<<"Plan p"<<endl;
	drawAll(p.begin(), p.end());
	cout<<"Schematic s"<<endl;
	drawAll(s.begin(), s.end());
	cout<<"Array sarray"<<endl;
	drawAll(sarray, sarray + sizeof(sarray) / sizeof(sarray[0]));

	for(vector<Shape*>::iterator it = s.begin(); it != s.end(); ++it){
		delete *it;
	}

	for(int it = 0; it < sizeof(sarray) / sizeof(sarray[0]) ; ++it){
		delete sarray[it];
	}

	cout<<"End of main"<<endl;

	return 0;
}