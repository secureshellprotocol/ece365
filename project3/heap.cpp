#include "hash.h"
#include "heap.h"
#include <climits>
#include <iostream>

//******
//PUBLIC
//******

//
// heap - The constructor allocates space for the nodes of the heap
// and the mapping (hash table) based on the specified capacity
//
heap::heap(int size){
	map = new hashTable(size*2);
	data.resize(size+1);

	//form sentinel node
	data[0].id = "sent";
	data[0].key = INT_MIN;
	data[0].pData = nullptr;

	capacity = size;	//does not account for sentinel node
	currentSize = 0;	//nothing has been inserted yet
}

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
int heap::insert(std::string &id, int key, void *pv){
	//Filled Up!
	if(currentSize + 1 > capacity){
		return 1;
	}
	//Already exists!
	if(map->contains(id)){
		return 2;
	}
	currentSize++;

	//insert at rightmost bottom node
	//create map entry
	data[currentSize].id = id;
	data[currentSize].key = key;
	data[currentSize].pData = pv;
	
	map->insert(data[currentSize].id, &data[currentSize]);

	//percolate up from bottom
	percolateUp(currentSize);

	return 0;
}

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
int heap::setKey(std::string &id, int key){
	//map does not to be updated, only node in data.
	//lookup node in map, and access node ptr
	bool retVal;
	node *n = static_cast<node *> (map->getPointer(id, &retVal));
	if(retVal) { 

		int pos = getPos(n);

		//Case 1: new key is greater than the last key
		//	Must percolate down
		if(key > n->key){
			n->key = key;
			percolateDown(pos);
		}
		
		//Case 2: new key is less than last key
		if(key < n->key){
			n->key = key;
			percolateUp(pos);
		}

		//Case 3: its the same key.
	}

	return !(retVal);
}

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
int heap::remove(std::string &id, int *key, void *ppData){
	if(currentSize == 0){
		//there is no heap
		return 1;
	}

	bool retVal;
	node *rm = static_cast<node *> (map->getPointer(id, &retVal));

	//check if id DNE in map
	if(retVal == false){
		return 1;
	}

	currentSize--; //heap is one smaller
	
	//clean map	
	if(key != nullptr){
		*key = rm->key;
	}
	if(ppData != nullptr){
		ppData = rm->pData;
	}
	map->remove(id);

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
int heap::deleteMin(std::string *id, int *key, void *ppData){
	if(id != nullptr){
		*id = data[1].id;
	}
	if(key != nullptr){
		*key = data[1].key;
	}
	if(ppData != nullptr){
		ppData = &(data[1].pData);
	}
	
	return remove(data[1].id, nullptr, nullptr);
}

void heap::printHeap(){
	for(int i = 1; i <= currentSize; i++){
		std::cout << data[i].key << ", " << data[i].id << std::endl;	
	}

	return;
}

//*******
//PRIVATE
//*******

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
			//
			//reverse the =
			//call setptr
			//data[(currentPos * 2) + cp] = data[currentPos];
			data[currentPos] = data[(currentPos * 2) + cp];
			map->setPointer(data[currentPos].id, &data[currentPos]);

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


