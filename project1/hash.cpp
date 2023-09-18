#include "hash.h"
#include <iostream>

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable(int size){
    int primeCap = getPrime(size);
    this->capacity = primeCap;
    this->filled = 0;

    this->data = new std::vector<hashItem>(primeCap);
    for(int i = 0; i < this->capacity; i++){
        (*this->data)[i].isOccupied = false;
        (*this->data)[i].isDeleted = false;
    }
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv){
    //check for rehash capacity (filled 50%)
    if((this->capacity/2) < this->filled){
        int code = this->rehash();
        if(code == 2) { return code; }
    }

    unsigned int hashedKey = this->hash(key);

    //check for occupation
    int i = 0;
    while((*this->data)[hashedKey+i].isOccupied){
        if(key == (*this->data)[hashedKey+i].key){
            (*this->data)[hashedKey+i].isDeleted = false;

            return 1;
        }
        i++;
    }

    (*this->data)[hashedKey+i].key = key;
    (*this->data)[hashedKey+i].isOccupied = true;
    (*this->data)[hashedKey+i].pv = pv;
    this->filled++;

    return 0;
}

// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
    if(this->findPos(key) != -1) { return true; }

    //else
    return false;
}

// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return nullptr.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void *hashTable::getPointer(const std::string &key, bool *b){
    //unimplemented
    return nullptr;
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv){
    //unimplemented
    return -1;
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key){
    //unimplemented
    return -1;
}

// The hash function.
// Taken from Class Textbook
unsigned int hashTable::hash(const std::string &key){
    unsigned int hashVal = 0;
    for( char ch : key ){
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % capacity;
}

// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
    //hash the key
    unsigned int hashedKey = this->hash(key);
    
    int i = 0;
    while(hashedKey+i < this->capacity){
        //return if not occupied
        if(!((*this->data)[hashedKey+i].isOccupied)) { return -1; }
        //return if deleted
        if(((*this->data)[hashedKey+i].isDeleted)) { return -1; } 
        //check if key matches
        if(key == (*this->data)[hashedKey+i].key){ return (hashedKey+i); }
        i++;
    }

    return -1;
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
    //  retrieve old capacity and issue a new prime
    int oldCap = this->capacity;
    this->capacity = this->getPrime(oldCap * 2);

    //  tuck away old data pointer
    //  have data point to new vector of hashItems
    std::vector<hashTable::hashItem> *oldData = this->data;
    try{
        this->data = new std::vector<hashItem>(this->capacity);
    } catch (const std::bad_alloc& e) {
        //  memory alloc failed, oops!
        return false;
    }

    for(int i = 0; i < oldCap; i++){
        if(((*oldData)[i].isOccupied == true) && ((*oldData)[i].isDeleted == false)){
            this->insert((*oldData)[i].key, (*oldData)[i].pv);
        }
    }

    delete oldData;
    return true;
}

// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
// If `size` exceeds 3145739, getPrime fails
unsigned int hashTable::getPrime(int size){
    int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151,
        12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739};
    
    for(int i = 0; i < 17; i++){ 
        if(size < primes[i]) {
            return primes[i];
        }
    }

    return -1;
}