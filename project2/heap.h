#ifndef	_HEAP_H
#define	_HEAP_H

#include <string>
#include <vector>
#include <climits>

#include "hash.h"

class heap{

	public:
		//
		// heap - The constructor allocates space for the nodes of the heap
		// and the mapping (hash table) based on the specified capacity
		//
		heap(int size);

		//
		// insert - Inserts a new node into the binary heap
		//
		// Inserts a node with the specified id string, key,
		// and optionally a pointer.  They key is used to
		// determine the final position of the new node.
		//
		// Returns:
		//   0 on success
		//   1 if the heap is already filled to capacity
		//   2 if a node with the given id already exists (but the heap
		//     is not filled to capacity)
		//
		int insert(std::string &id, int key, void *pv = nullptr);

		//
		// setKey - set the key of the specified node to the specified value
		//
		// I have decided that the class should provide this member function
		// instead of two separate increaseKey and decreaseKey functions.
		//
		// Returns:
		//   0 on success
		//   1 if a node with the given id does not exist
		//
		int setKey(std::string &id, int key);

		//
		// remove - delete the node with the specified id from the binary heap
		//
		// If pKey is supplied, write to that address the key of the node
		// being deleted. If ppData is supplied, write to that address the
		// associated void pointer.
		//
		// Returns:
		//   0 on success
		//   1 if a node with the given id does not exist
		//
		int remove(std::string &id, int *key = nullptr, void *ppData = nullptr);

		//
		// deleteMin - return the data associated with the smallest key
		//             and delete that node from the binary heap
		//
		// If pId is supplied (i.e., it is not nullptr), write to that address
		// the id of the node being deleted. If pKey is supplied, write to
		// that address the key of the node being deleted. If ppData is
		// supplied, write to that address the associated void pointer.
		//
		// Returns:
		//   0 on success
		//   1 if the heap is empty
		//
		int deleteMin(std::string *id = nullptr, int *key = nullptr, void *ppData = nullptr);

		//debug function -- prints heap
		void printHeap();

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

