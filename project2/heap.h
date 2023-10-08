#ifndef	_HEAP_H
#define	_HEAP_H

#include <string>
#include <vector>
#include <climits>

#include "hash.h"

class heap{

	public:
		// Constructor creates a hash table as big as the next largest prime of
		// "size". 	
		heap(int size = 1);

		// Inserts and properly sorts an id into the heap, based
		// on the provided key.
		//  Returns 0 if the node is inserted successfully.
		int insert(std::string &id, int key);

		// Changes the key value for a given id
		// 	Returns 0 if id is successfully changed
		// 	Returns 1 if id DNE in heap
		int setKey(std::string &id, int key);

		// Lazy-deletes a given id in the heap.
		//  Returns 0 if id is successfully deleted
		//  Returns 1 if id is DNE in heap
		int remove(std::string &id, int *key);

		// Lazy-deletes smallest key in heap.
		//  Returns 0 if id is successfully deleted
		//  Returns 1 if id is DNE in heap.
		int deleteMin(std::string *id, int *key);
	
	private:
		typedef struct node_t { //heap node
			std::string id;	//this gets hashed	
			int key = INT_MAX;
			void *pData;	
		} node;

		int capacity;
		int currentSize;

		std::vector<node> data;	//binary tree of nodes
		
		hashTable *map;	//map of id->node ptr
									//used for setKey and remove, in order
									//to quickly find indicies of "id"'s in
									//the data vector 

		//moves an element up until
		//	element being moved up < parent
		void percolateUp(int currentPos);
		
		//Returns an integer indicating which child is the smaller child
		//for a parent node
		//	0 for left child or both children
		//	1 for right child
		//	2 for OOB
		int determineSmallestChild(int currentPos);

		//moves an element down until
		//	element being moved down > parent
		//
		//	as it moves, each child is compared. The smaller of the two is
		//	chosen to be compared against the element we are percolating down.
		void percolateDown(int currentPos);
		
		//get position of node in DATA VECTOR. NOT THE MAP.
		int getPos(node *pn);
};

#endif	//_HEAP_H
