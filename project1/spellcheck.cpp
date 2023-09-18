#include "hash.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>


void clean(std::string &word){
    //std::cout << word << std::endl;
    for(int i = 0; i < word.length(); i++){
        (word)[i] = std::tolower((word)[i]);
    }
    //std::cout << word<< std::endl ;
    return;
}

//  clean the word before bringing here
bool isValid(std::string &word){
    if(word.length() > 20) return false;
    for( char ch : word ){
        if((ch >= 97 || ch <= 122)) { continue; }
        if((ch >= 48 || ch <= 57)) { continue; }
        if(ch == 39) { continue; }
        if(ch == 45) { continue; }

        return false;
    }
    return true;

}
//  clean the word before bringing here
bool isValid(char ch){
    if((ch >= 'a' || ch <= 'z')) { return true; }
    if((ch >= '0' || ch <= '9')) { return true; }
    if(ch == '\'') { return true; }
    if(ch == '-') { return true; }
    
    return false;
}

int makeDictionary(std::string &wordfilestring, hashTable *d){
    std::string line;
    std::ifstream wordfile;
    wordfile.open(wordfilestring);

    //parse and form hash table
    while(std::getline(wordfile, line)){
        clean(line);
        if(isValid(line)){
            switch (d->insert(line)){
                case 0:
                    break;
                case 1:
                    std::cout << "Already Hashed" << std::endl;
                    break;
                case 2:
                    std::cout << "Malloc fail" << std::endl;
                    break;
                default:
                    std::cout << "Insert: Unexpected Error Occured" << std::endl;
                    break;
            }
        }
        else{
            std::cout << "bigsad" << std::endl;
        }
    }
    return 0;
}

int main(){

    hashTable *dict = new hashTable();

    std::string wordfilestring;

    std::cout << "Enter name of dictionary: ";
    std::cin >> wordfilestring;
    
    std::ifstream infile;
    std::string infilestring;

    std::cout << "Enter name of input file: ";
    std::cin >> infilestring;
    infile.open(infilestring);
    
    std::ofstream outfile;
    std::string outfilestring;

    std::cout << "Enter name of output file: ";
    std::cin >> outfilestring;
    outfile.open(outfilestring);

    // da rules:
    //  no word over 20char
    //  end with \n
    //  words w/ digits ARE VALID, dont check them.
    //  convert to lowercase
    //  valid characters are 
    //      letters (capital A – Z and lowercase a - z), 
    //      digits (0 - 9), 
    //      dashes (-), 
    //      and apostrophes (').

    makeDictionary(wordfilestring, dict);

    std::string line;
    int lineno = 0;
    while(std::getline(infile, line)){
        lineno++;
    }

    delete dict;

    return 0;
}

