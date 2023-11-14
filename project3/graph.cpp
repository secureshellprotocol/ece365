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
//		0 on success
//		1 if theres a vertex with the same name in the 
//			edge list already 
int Graph::Vertex::addEdge(Graph::Vertex &v, int c){
	/*
	for (auto &temp_edge : edges){
		if(temp_edge.destination->name == v.name) { 
			return 1; 
		}
	}
	*/
	edge e;
	e.destination = &v;
	e.cost = c;

	edges.push_back(e);

	return 0;
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

Graph::Graph(){
	verticeMap = new hashTable(100);
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

		int cost;
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
	focus->known = true;

	heap unknownQueue = heap(v_buf.size() + 1);

	int knownCount = 1;
	bool emptyQueue = 0;
	while(knownCount < v_buf.size() && !emptyQueue){
		//	Grab edges from known vertex
		//	Each key is focus dist (dist from s), plus cost to get there
		for(Vertex::edge &e : focus->edges){
			if(e.destination->dist == -1 || e.destination->dist > e.cost + focus->dist){
				e.destination->dist = e.cost + focus->dist;
				e.destination->prev = getVertex(focus->edge);
			}
			
			//	Insert all edges from focus
			//	into unknownQueue
			unknownQueue.insert(e.destination->name,
								e.destination->dist,
								e.destination);
		}
		//	From unknownQueue, grabs the next dest
		//	with the lowest attached dist.
		while(focus->known){
			if(unknownQueue.deleteMin(nullptr, nullptr, &focus)){
				//queue is empty, theres no path
				emptyQueue = true;
				break; 			
			}
		}
		//	This next dest becomes known.
		focus->known = true;
		knownCount++;
	}

	return;
}
void Graph::writeOutVBuf(std::string outfile_str){
	//	Print output
	std::ofstream outfile;
	outfile.open(outfile_str);

	for(auto v : v_buf){ 
		if(v.dist == -1 && !(v.known)){
			outfile << v.name <<": NO PATH\n";
			continue;
		}
				
		outfile << v.name << ": "<< v.dist <<" [";
	
		Vertex *p = v.prev;
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
