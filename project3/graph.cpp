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
	edgeCount = 0;
}

//	Adds an edge to a vertex, with an associated cost
//		0 on success
//		1 if theres a vertex with the same name in the 
//			edge list already 
int Graph::Vertex::addEdge(Graph::Vertex &v, int c){
	for (auto &temp_edge : edges){
		if(temp_edge.destination->name == v.name) { return 1; }
	}

	edge e;
	e.destination = &v;
	e.cost = c;

	edges.push_back(e);
	edgeCount++;

	return 0;
}

//	Prints out Vertex info.
void Graph::Vertex::printVertexInfo(){
	std::cout << name << ' '<< edgeCount << std::endl;
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
		
		vertexCount++;
	}

	return getVertex(name);
}

//		------
//		PUBLIC
//		------

Graph::Graph(){
	verticeMap = new hashTable(100);
	vertexCount = 0;
}

//	Builds graph from specifed graph file
//	Handles the format:
//		<starting vertice name> <destination name> <cost>
void Graph::buildGraph(std::string &filename) {
	std::ifstream input(filename);
	if(!input){
		std::cerr << "Error: cannot access" << filename << std::endl;
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

		std::string focus_str;
		ss >> focus_str;

		std::string dest_str;
		ss >> dest_str;

		int cost;
		ss >> cost;
		
		//	Assemble verticies as specified
		//	These will take care of bookkeeping
		//		No duplicate vertices, hashmap maitenance
		Vertex *focus = addVertex(focus_str);
		Vertex *dest = addVertex(dest_str);
		focus->addEdge(*dest, cost);
	}
	
}

//	Runs Dijkstra's algorithm to determine the shortest path from
//	a given vertex, v.
void Graph::runDijkstras(std::string &st){
	//	Establish known vertex
	Vertex *focus = getVertex(st);
	focus->dist = 0;
	focus->known = true;

	heap unknownQueue = heap(vertexCount + 1);

	int knownCount = 1;
	while(knownCount < vertexCount){
		//	Grab edges from known vertex
		//	Each key is focus dist (dist from s), plus cost to get there
		for(Vertex::edge &e : focus->edges){
			e.destination->printVertexInfo();
			if(e.destination->dist == -1 || e.destination->dist > e.cost + focus->dist){
				e.destination->dist = e.cost + focus->dist;
				e.destination->prev = focus;
			}
			
			unknownQueue.insert(e.destination->name,
								e.destination->dist,
								e.destination);
		}
		while(focus->known){
			//BUG: Focus ptr not changing?
			std::string fuck;
			unknownQueue.deleteMin(&fuck, nullptr, nullptr);
			focus = getVertex(fuck);
		}
		focus->known = true;
		knownCount++;
	}
print:

//james notes
//distances evaulate fine
//deletemin not getting ptr????
//prev ptr not setting????
	//	Print output
	for(auto &v : v_buf){ 
		if(v.dist == -1 && !(v.known)){
			std::cout << v.name << ": NO PATH\n";
			continue;
		}
		
		Vertex *p = v.prev;;
		std::list<std::string> backtrack;
		backtrack.push_front(v.name);
		
		std::cout << v.name << ": "<< v.dist <<" [";
		while(p != nullptr){
			backtrack.push_front(p->name);
			p = p->prev;
		}
	}

	return;
}

//	Detects whether or not a vertex has been "seen" yet by the graph
//		true if detected
//		false if not detected
bool Graph::withinGraph(std::string &v){
	return verticeMap->contains(v);
}
