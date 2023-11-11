#include "hash.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>

// Takes word(s) and makes them all lowercase (clean)
void clean(std::string &word){
    for(int i = 0; i < word.length(); i++){
        (word)[i] = std::tolower((word)[i]);
    }

    return;
}
char clean(char ch){
    return std::tolower(ch);
}

//  Checks if a word is valid according to the rules. 
    //  no word over 20char
    //  end with \n
    //  words w/ digits ARE VALID, dont check them.
    //  convert to lowercase
    //  valid characters are 
    //      letters (capital A – Z and lowercase a - z), 
    //      digits (0 - 9), 
    //      dashes (-), 
    //      and apostrophes (').
//  clean() the word before bringing here
bool isValid(std::string &word){
    if(word.length() > 19) return false;
    for( char ch : word ){
        if((ch >= 'a' && ch <= 'z')) { continue; }
        if((ch >= '0' && ch <= '9')) { continue; }
        if(ch == '\'') { continue; }
        if(ch == '-') { continue; }

        return false;
    }
    return true;

}
bool isValid(char ch){
    if((ch >= 'a') && (ch <= 'z')) { return true; }
    if((ch >= '0') && (ch <= '9')) { return true; }
    if(ch == '\'') { return true; }
    if(ch == '-') { return true; }

    return false;
}

int makeDictionary(std::string &wordfilestring, hashTable *d){
    std::string line;
    std::ifstream wordfile;
    wordfile.open(wordfilestring);

    clock_t start = clock();
    //parse and form hash table
    while(std::getline(wordfile, line)){
        clean(line);
        if(isValid(line)){
            switch (d->insert(line)){
                case 0:
                    break;
                case 1:
                    //  Already Hashed, not fatal
                    break;
                case 2:
                    //	Malloc fail, fatal
                    return -1;
					break;
                default:
                    //	Unexpected Error Occured
                    break;
            }
		std::cout << "hashed: " + line << std::endl;
        }

        //  else, not valid
    }
    clock_t end = clock();
    std::cout << "Total time (in seconds) to load dictionary: " + std::to_string((double)(end - start) / CLOCKS_PER_SEC) << std::endl;
    return 0;
}

//  checks if word is in hastTable dictionary d
//  true - Word found
//  false - Word not found
bool spellcheck(std::string &word, hashTable *d){
	if(!(d->contains(word))){
        return false;
    }
    return true;
}

int main(){

    hashTable *dict = new hashTable();

    std::string wordfilestring;
    std::cout << "Enter name of dictionary: ";
    std::cin >> wordfilestring;
    
    makeDictionary(wordfilestring, dict);

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

	//https://stackoverflow.com/questions/20167685/measuring-cpu-time-in-c
    clock_t start = clock();
    std::string word;
    int lineno = 1;
    
    char ch = clean(infile.get());
    while(42){
        if(ch == EOF) { break; }
        bool digit = ((ch >= '0') && (ch <= '9'));

        int length = 0;
        while(isValid(ch)){
            length++;
            if(length > 20){ 
                while(isValid(ch)){
                    ch = clean(infile.get());
                }
                break; 
            }
            word.push_back(ch);
            ch = clean(infile.get());
            if(digit == false && ((ch >= '0') && (ch <= '9'))) { digit = true; }
        }
        
		//analyze word, as long as theres no digits
		if(!digit) {
            if(!(spellcheck(word, dict))){
                if((length > 20)){
                    outfile << "Long word at line " + std::to_string(lineno) + ", starts: "+ word << std::endl;
                }
                else{
                    outfile << "Unknown word at line " + std::to_string(lineno) + ": " + word << std::endl;
                }
            }
        }

        //work back
        digit = false;
        while(!isValid(ch)){
            if(ch == '\n') { lineno++; }
            if(ch == EOF) { break; }
            ch = clean(infile.get());
        }
        word = "";
    }
    clock_t end = clock();
    std::cout << "Total time (in seconds) to check document: " + std::to_string((double)(end - start) / CLOCKS_PER_SEC) << std::endl;

    delete dict;

    return 0;
}

