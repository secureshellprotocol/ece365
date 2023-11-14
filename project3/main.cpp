#include "graph.h"
#include "hash.h"
#include "heap.h"
#include <cctype>
int main(){
	std::string infile_str;
	std::cout << "Enter input file name: ";
	std::cin >> infile_str;

	Graph myGraph = Graph();
	myGraph.buildGraph(infile_str);
	
	std::string focusVertex_str;
	while(!myGraph.withinGraph(focusVertex_str)){
		std::cout << "Enter name of starting vertex: ";
		std::cin >> focusVertex_str;
	}


	clock_t start = clock();
	myGraph.runDijkstras(focusVertex_str);	
	clock_t end = clock();
	
	std::cout << "Total time (in seconds) to run Dijkstra's: " << std::to_string((double)(end - start) / CLOCKS_PER_SEC) << std::endl;

	std::string outfile_str;
	std::cout << "Enter output file name: ";
	std::cin >> outfile_str;
	
	myGraph.writeOutVBuf(outfile_str);

	return 0;
}
