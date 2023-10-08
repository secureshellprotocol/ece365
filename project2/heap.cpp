#include "hash.h"
#include "heap.h"
#include <climits>
#include <iostream>

// Constructor creates a hash table as big as the next largest prime of
// "size". 	
heap::heap(int size){
	map = new hashTable(size*2);
	data.resize(size+1);

	//form sentinel node
	data[0].id = "penis";
	data[0].key = INT_MIN;
	data[0].pData = nullptr;

	capacity = size;	//does not account for sentinel node
	currentSize = 0;	//nothing has been inserted yet
}

// Inserts and properly sorts an id into the heap, based
// on the provided key.
//  Returns 0 if the node is inserted successfully.
int heap::insert(std::string &id, int key){
	if(currentSize + 1 > capacity){
		std::cout << "Heap has reached capacity" << std::endl;
		return 1;
	}
	currentSize++;

	//insert at rightmost bottom node
	//create map entry
	data[currentSize].id = id;
	data[currentSize].key = key;
	data[currentSize].pData = nullptr;

	map->insert(data[currentSize].id, &data[currentSize]);

	//percolate up from bottom
	percolateUp(currentSize);

	return 0;
}

// Changes the key value for a given id
// 	Returns 0 if id is successfully changed
// 	Returns 1 if id DNE in heap
int heap::setKey(std::string &id, int key){
	//map does not to be updated, only node in data.
	//lookup node in map, and access node ptr
	bool retVal;
	node *n = static_cast<node *> (map->getPointer(id, &retVal));
	if(retVal) { 
		n->key = key;
		int pos = getPos(n);

		//Case 1: new key is greater than the last key
		//	Must percolate down
		if(key > n->key){
			percolateDown(pos);
		}
		
		//Case 2: new key is less than last key
		if(key < n->key){
			percolateUp(pos);
		}

		//Case 3: its the same key.
	}

	return retVal;
}

// Deletes a given id in the heap.
//  Returns 0 if id is successfully deleted
//  Returns 1 if id is DNE in heap
int heap::remove(std::string &id, int *key){
	if(currentSize == 0){
		//there is no heap
		return 1;
	}

	currentSize--; //heap is one smaller
	
	bool retVal;
	node *rm = static_cast<node *> (map->getPointer(id, &retVal));

	//check if id DNE in map
	if(retVal == false){
		return 1;
	}
	//clean map
	map->remove(id);
	*key = rm->key;

	//sanity check -- not deleting a heap of size 1
	if(currentSize == 0){
		//We can just leave, it'll be overwritten on the next insert.
		return 0;
	}

	node n = data[currentSize + 1];
	
	//get the index we're rm'ing -- this is the "hole" starting pos
	int currentPos = getPos(rm);
	data[currentPos] = n;

	//figure out which way to percolate -- these should take care of the
	//mapping operations for us
	if(data[currentPos].key < data[currentPos/2].key){
		percolateUp(currentPos);
	}
	else{
		percolateDown(currentPos);
	}

	return 0;
}

// Deletes smallest key in heap.
//  Returns 0 if id is successfully deleted
//  Returns 1 if id is DNE in heap.
int heap::deleteMin(std::string *id, int *key){
	*id = data[1].id;

	return remove(data[1].id, key);
}

//moves an element up until:
//	element being moved up < parent
void heap::percolateUp(int currentPos){
	//currentPos - index to percolate up from
	node n = data[currentPos];

	while((currentPos > 1) && (n.key < data[currentPos/2].key)){
		//slide down
		data[currentPos] = data[currentPos/2];
		//update ptr to node in hashTable after sliding down to currentPos
		map->setPointer(data[currentPos].id, &data[currentPos]);

		currentPos = currentPos/2; //update focus, hole is now at currentPos/2
	}

	//insert hole and update map to match hole
	data[currentPos] = n;
	map->setPointer(n.id, &data[currentPos]);
	return;
}

//Returns an integer indicating which child is the smaller child
//for a parent node 
//	0 for left child or both children	L
//	1 for right child					R
//	2 for OOB	
int heap::determineSmallestChild(int currentPos){
	//L OOB, therefore R also OOB
	if(currentPos * 2 > currentSize){
		return 2;
	}
	//R OOB, L is at the rightmost bottom node of heap
	else if((currentPos * 2 + 1) > currentSize){
		return 0;
	}
	//If you're here, both exist.
	//if L > R
	if(data[currentPos * 2].key > data[(currentPos * 2) + 1].key){
		return 1;
	}
	//therefore, L < R || L == R
	else {
		return 0;
	}
}

//moves an element down until:
//	element being moved down > smallest child
void heap::percolateDown(int currentPos){
	//	as it moves, each child is compared. The smaller of the two is
	//	chosen to be compared against the element we are percolating down.

	//currentPos < currentSize
	node n = data[currentPos];
	while(currentPos <= currentSize){
		int cp = determineSmallestChild(currentPos);
		
		//Both DNE, you're at a leaf, cant get any lower
		if(cp == 2) {
			break;
		}

		//check if element > target child
		if(n.key > data[(currentPos * 2) + cp].key){
			//slide child up
			data[(currentPos * 2) + cp] = data[currentPos];
			//update position to be at childs position
			currentPos = (currentPos * 2) + cp;
		}
		else { //n.key < childs key
			break;
		}
	}

	//insert hole and update map to match hole
	data[currentPos] = n;
	map->setPointer(n.id, &data[currentPos]);
	return;
}

//get position of node in DATA VECTOR. NOT THE MAP.
int heap::getPos(node *pn){
	return pn - &data[0];

}
