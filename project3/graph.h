#ifndef _GRAPH_H
#define _GRAPH_H

//	Library for parsing in data and returning a directed graph

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <climits>

#include "hash.h"

class Graph {
private:
	
	//private vertex class
	//	responsible for maintaining its edges + costs
	//	Graph class will be responsible for maintaining the list of vertices in
	//	the graph itself. Realistically, an edge should only be added when the 
	//	Graph class invokes such an action.
	class Vertex {
	public:
		typedef struct edge_t {
			Vertex *destination;
			unsigned int cost;
		} edge;

		std::list<edge> edges;
		std::string name;

		//Dijkstra's routines
		Vertex *prev = nullptr;			//Previous node in dijkstras path
		unsigned int dist = INT_MAX;	//Distance from source vertex

		Vertex(std::string &n);

		//	Adds an edge to a vertex, with an associated cost
		void addEdge(Vertex &v, int cost);

		//	Prints out Vertex info.
		void printVertexInfo();
	};
	
	std::list<Vertex> v_buf;	//buffer for every vertice in graph to live
	hashTable *verticeMap;		//map for accessing vertex in graph

	//	Getter for getting a vertex
	//	Just here to handle the static_cast from null* to Vertex*
	Vertex *getVertex(std::string &v);

	//	Adds vertex to map verticeMap
	//	Stores vertex data in vertex buffer v_buf
	//		and a ptr to this data is put in verticeMap's record
	//	If a vertex with the same name already exists in verticeMap's records
	//		nothing is done.
	//	In both cases, a ptr to the vertice is returned.
	Vertex *addVertex(std::string &name);

public:
	//	Builds a graph and an accompanyning hash map for
	//	quick vertice access
	Graph();
	//	Destructs graph and deletes hash table
	~Graph();

	//	Builds graph from specifed graph file
	//	
	//	Handles the format:
	//		<starting vertice name> <destination name> <cost>
	//	
	//	This WILL define the single source of truth on what is and is not in
	//	the graph. 
	void buildGraph(std::string &filename);
	
	//	Runs Dijkstra's algorithm to determine the shortest path
	//	from a given vertex, v
	void runDijkstras(std::string &st);
	
	//	Writes out vertice buffer to file.
	void writeOutVBuf(std::string outfile_str);
	
	//	Detects whether or not a vertex has been "seen" yet by the graph
	//		true if detected
	//		false if not detected
	bool withinGraph(std::string &v);
};
#endif //_GRAPH_H
