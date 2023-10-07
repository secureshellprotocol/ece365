#ifndef	_HEAP_H
#define	_HEAP_H

#include <string>
#include <vector>

#include "hash.h"

class heap{

	public:
		// Constructor creates a hash table as big as the next largest prime of
		// "size". 	
		heap(int size = 1);

		int insert(std::string &id, int key);

		int setKey(std::string &id, int key);

		int remove(std::string &id, int key);

		int deletMin(std::string &id, int key);
	private:
		class node { //heap node
			std::string id;	//this gets hashed	
			int key;
			void *pData;	
		}

		std::vector<node> *data;	//binary tree of nodes
		hashTable map;				//map of id->node ptr

		//moves an element up until
		//	element being moved up < parent
		void percolateUp(int currentPos);
		
		//moves an element down until
		//	element being moved down > parent
		//
		//	as it moves, each child is compared. The smaller of the two is
		//	chosen to be compared against the element we are percolating down.
		void percolateDown(int currentPos);
		
		//get position of node in DATA VECTOR. NOT THE MAP.
		int getPos(node *pn);
}

#endif	//_HEAP_H
