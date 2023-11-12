#include "graph.h"
#include "hash.h"
#include "heap.h"
#include "dijkstra.h"

int main(){
	std::string filename;
	std::cout << "Enter input file name: ";
	std::cin >> filename;

	Graph amazeballs = Graph();
	amazeballs.buildGraph(filename);
	
		

	return 0;
}
