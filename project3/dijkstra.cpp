#include "graph.h"


int main(){
	std::string filename;
	cout << "Enter input file name: "
	cin >> filename;

	Graph amazeballs;
	amazeballs.buildGraph(filename);
	return;
}
