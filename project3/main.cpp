#include "graph.h"
#include "hash.h"
#include "heap.h"
int main(){
	std::string infile_str;
	std::cout << "Enter input file name: ";
	std::cin >> infile_str;

	Graph amazeballs = Graph();
	amazeballs.buildGraph(infile_str);
	
	std::string focusVertex_str;
	std::cout << "Enter name of starting vertex: ";
	std::cin >> focusVertex_str;

	amazeballs.runDijkstras(focusVertex_str);	
	
	std::string outfile_str;
	std::cout << "Enter output file name: ";
	std::cin >> outfile_str;
	
	amazeballs.writeOutVBuf(outfile_str);

	return 0;
}
