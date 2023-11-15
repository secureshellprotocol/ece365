//	Library for parsing in data and returning a directed graph

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "graph.h"
#include "hash.h"
#include "heap.h"

//		-------
//		PRIVATE
//		-------

//	Vertex Construtor
//		Single, named vertex with no associated edges.
Graph::Vertex::Vertex(std::string &n){
	name = n;
}

//	Adds an edge to a vertex, with an associated cost
void Graph::Vertex::addEdge(Graph::Vertex &v, int c){
	edge e;
	e.destination = &v;
	e.cost = c;

	edges.push_back(e);

	return;
}

//	Prints out Vertex info.
void Graph::Vertex::printVertexInfo(){
	std::cout << name << ' '<< edges.size() << std::endl;
	for(auto &e : edges){
		std::cout << '\t' << e.destination->name << ' ' << e.cost << std::endl;
	} 
	
	return;
}

//	Getter for handling a vertice
//	Just here to handle the static_cast from null* to Vertex*
//		Returns ptr to Vertex if it exists in verticeMap
//		Otherwise, returns nullptr
Graph::Vertex *Graph::getVertex(std::string &name){
	bool b;
	Vertex *v = static_cast<Vertex *>(verticeMap->getPointer(name, &b));
	if(b){
		return v;
	}
	return nullptr;
}

//	Adds a vertex to verticeMap
//	Stores vertex data in vertex buffer v_buf
//		and a ptr to this data is put in verticeMap's record
//	If a vertex with the same name already exists in verticeMap's records,
//		nothing is done.
Graph::Vertex *Graph::addVertex(std::string &name){
	if(!withinGraph(name)){
		//construct vertice
		Vertex v = Vertex(name);
	
		v_buf.push_back(v);	
		verticeMap->insert(name, &(v_buf.back()));
	}

	return getVertex(name);
}

//		------
//		PUBLIC
//		------

//	Builds a graph and an accompanying hash map for
//	quick vertice access
Graph::Graph(){
	verticeMap = new hashTable();
}
//Destructs graph and deletes hash table
Graph::~Graph(){
	delete verticeMap;
}

//	Builds graph from specifed graph file
//
//	Handles the format:
//		<starting vertice name> <destination name> <cost>
void Graph::buildGraph(std::string &filename) {
	std::ifstream input(filename);
	if(!input){
		std::cerr << "Error: cannot access " << filename << std::endl;
		exit(1);
	}
	
	while(1) {
		std::string line;
		std::getline(input, line);
		std::stringstream ss(line);
		
		//	Break Condition: nothing left to read
		if(input.eof() || input.fail()){
			break;
		}

		//	Grab:	focus/source
		//			destination
		//			cost to get there
		//		and form a vertex (if source dne) with
		//		an edge to the dest vertex (if destination dne
		//		and edge to destination dne)
		std::string focus_str;
		ss >> focus_str;

		std::string dest_str;
		ss >> dest_str;

		unsigned int cost;
		ss >> cost;
		
		//	Assemble verticies as specified
		//	These will take care of bookkeeping
		//		No duplicate vertices, and does hashmap maitenance
		Vertex *focus = addVertex(focus_str);
		Vertex *dest = addVertex(dest_str);
		focus->addEdge(*dest, cost);
	}
	input.close();
	
	return;	
}

//	Runs Dijkstra's algorithm to determine the shortest path from
//	a given vertex, v.
void Graph::runDijkstras(std::string &st){
	//	Establish known vertex
	Vertex *focus = getVertex(st);
	focus->dist = 0;

	heap unknownQueue = heap(v_buf.size());

	//	Insert every node into priority queue
	for(Vertex &v : v_buf){
		unknownQueue.insert(v.name, v.dist, &v);
	}

	while(!unknownQueue.deleteMin(nullptr, nullptr, &focus)){
		if(focus->dist == INT_MAX) break; 	//	no path to next node
	
		//	loop through edges of focus
		//	calcuate dist and update destination's dist if
		//	calculated dist < current dist on destination
		for(auto e : focus->edges){
			unsigned int calculatedDist = focus->dist + e.cost;
			
			if(calculatedDist < e.destination->dist){
				e.destination->dist = calculatedDist;
				e.destination->prev = focus;
			
				//Update position in heap
				unknownQueue.setKey(e.destination->name, e.destination->dist);
			}
		}
	}

	return;
}

//	Writes out vertice buffer to file
void Graph::writeOutVBuf(std::string outfile_str){
	//	Print output
	std::ofstream outfile;
	outfile.open(outfile_str);

	for(auto &v : v_buf){ 
		if(v.dist == INT_MAX){
			outfile << v.name << ": NO PATH\n";
			continue;
		}
		
		Vertex *p = v.prev;
		
		outfile << v.name << ": "<< v.dist <<" [";
		std::string outbuf;

		//	Iterate through prev's
		while(p != nullptr){
			std::string temp = p->name + ", ";
	
			outbuf.insert(0, temp);

			p = p->prev;
		}
		outfile << outbuf << v.name << "]\n";
	}
	outfile.close();

	return;
}


//	Detects whether or not a vertex has been "seen" yet by the graph
//		true if detected
//		false if not detected
bool Graph::withinGraph(std::string &v){
	return verticeMap->contains(v);
}
