#include "hash.h"
#include <vector>
#include <string>
#include <iostream>

int main(){

    hashTable *dict = new hashTable();

    for(int i = 0; i < 150000; i++){
        dict->insert("sugoma"+std::to_string(i));
        //std::cout << "sugoma"+std::to_string(i);
    }    

    //contains check
    std::cout << std::endl << dict->contains("sugoma2");
    std::cout << std::endl << dict->contains("yourmom");



    delete dict;

    return 0;
}