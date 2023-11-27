
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>

#define NAM "*** NOT A MERGE ***"

int weightMatrix[1001][1001];

//	Merge Match
//	Checks if 'merge' is a possible merge of two
//	given words, A and B.
//		Returns 
//			either the valid merged string of the two strings,
//			with the letters from A capitalized
//
//			or, if 'merge' is NOT VALID, returns the string
//			'*** NOT A MERGE ***'
std::string mergeMatch(std::string A, std::string B, std::string C){ 
	
	std::string result;

	for(int i = 0; i < 1001; i++){
		weightMatrix[i][0] = -1;
		weightMatrix[0][i] = -1;
	}

	for(i = 0; i < A.length(); i++){
		
	}

	for(int i = 0; i < A.length(); i++){
		for(int j = 0; j < B.length(); j++){
			std::cout << weightMatrix[i][j];
		}	
		std::cout << '\n';
	}




	return result;
}
