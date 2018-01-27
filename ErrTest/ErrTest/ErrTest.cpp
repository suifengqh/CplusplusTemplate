#include "require.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
	int i = 1;
	require(i, "value must be nonzero");
	requireArgs(argc, 1);
	requireMinArgs(argc, 1);
	ifstream in(argv[1]);
	assure(in, argv[1]);
	ifstream nofile("nofile.xxx");
	//assure(nofile);
	ofstream out("tmp.txt");
	assure(out);

	return 0;
}