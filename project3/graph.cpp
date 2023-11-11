//	Library for parsing in data and returning a directed graph
//	Mostly inspired from Prof. Sable's file import code for DSA1 P3

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>



class Graph {
private:
	
	//private vertice class
	//	responsible for maintaining its edges + costs
	//	Graph class will be responsible for maintaining the list of all of them
	class Vertice {
	private:
		struct Edge {
			std::string destination;
			int cost;
		};

	public:
		std::string name;
		std::list<Edge> edges;

		Vertice(std::string &n){
			name = n;

		}
	};

	list<Vertice> graph;

	//Checks if a vertice is in graph
	//	returns 1 for false
	//	returns 0 for true
	
public:
	Graph(int size){
			
	}

	//	Builds graph from specifed graph file
	//	Handles the format:
	//		<starting vertice name> <destination name> <cost>
	void buildGraph(const std::string &filename) {
		std::ifstream input(filename);
		if(!input){
			std::cerr << "Error: cannot access" << filename << std::endl;
			exit(1);
		}
		
		do {
			std::string line;
			std::getline(input, line);
			std::stringstream ss(line);

			std::string start;
			ss >> start;

			std::string dest;
			ss >> dest;

			int size;
			ss >> size;

			std::cout << start << " " << dest << " " << size << '\n';
			//see if starting vertice is in list
			
			//see if ending vertice is in list
			//	if not, add it to the list	

		} while (!input.eof());
		
	}
};
