#include "graph.h"
#include "hash.h"
#include "heap.h"
int main(){
	std::string filename;
	std::cout << "Enter input file name: ";
	std::cin >> filename;

	Graph amazeballs = Graph();
	amazeballs.buildGraph(filename);
	
	std::string focusVertex = "v1";
	amazeballs.runDijkstras(focusVertex);	

	return 0;
}
