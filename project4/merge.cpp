
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
	//	"left" comparison
	//		Compares A and C at the same index
	//	"up" comparison
	//		Compares B and C at the same index
	//
	//	the directions come from the direction we "look" on the matrix.
	//	We look "left" to compare A and C, so we can later walk back and
	//		eliminate an entire column when constructing the string merge
	//	We look "up" to compare B and C, so we can later walk back and
	//		eliminate an entire row when constructing the string merge


	std::string result;

	if( A.length() + B.length() != C.length()){
		result = NAM;
		return result;
	}

	//	initialize Row 0 and Column 0 with '-1'.
	for(long unsigned int i = 0; i <= A.length(); i++){
		weightMatrix[i][0] = -1;
	}
	for(long unsigned int j = 0; j <= B.length(); j++){
		weightMatrix[0][j] = -1;
	}

	//	Analyze row 0
	//	Analogous to doing only "left" comparisons
	for(long unsigned int i = 1; i <= A.length(); i++){
		if( A[i-1] == C[i-1] ){
			weightMatrix[i][0] = weightMatrix[i-1][0] + 1;
		}
	}

	//	Analyze col 0
	//	Analogous to doing only "up" comparisons
	for(long unsigned int j = 1; j <= B.length(); j++){
		if( B[j-1] == C[j-1] ){
			weightMatrix[0][j] = weightMatrix[0][j-1] + 1;
		}
	}

	//	Start at weightMatrix[1][1]
	//	walk down every column and compute the weight
	//	using "up" and "left" operations

	for(long unsigned int i = 1; i <= A.length(); i++){
		for(long unsigned int j = 1; j <= B.length(); j++){
			
			//left op
			if( weightMatrix[i-1][j] != -1 && A[i - 1] == C[i + j - 1] ){
				weightMatrix[i][j] = weightMatrix[i-1][j] + 1;
				continue;
			}

			//up op
			if( weightMatrix[i][j-1] != -1 && B[j - 1] == C[i + j - 1] ){
				weightMatrix[i][j] = weightMatrix[i][j-1] + 1;
				continue;
			}

			weightMatrix[i][j] = -1;
		}
	}



	//	Can we step back?
	if(weightMatrix[A.length()][B.length()] == -1){
		result = NAM;
		return result;
	}
	
	//	We can step back.
	//	Start from [A.length()][B.length()] and either
	//		step UP and eliminate a row (pop from B)
	//		step LEFT and eliminate a col (pop from A)
	//	
	//	We step UP sooner than we step LEFT, since we prefer
	//		B to be further
	while(A.length() || B.length()){
		int focus = weightMatrix[A.length()][B.length()];
		
		//	look UP
		if(!B.empty() && weightMatrix[A.length()][B.length() - 1] == focus - 1){
			//step UP
			result.insert(0, 1, B.back());
			B.pop_back();
			C.pop_back();
			
			continue;
		}

		//	look LEFT
		if(!A.empty() && weightMatrix[A.length() - 1][B.length()] == focus - 1){
			//step LEFT
			result.insert(0, 1, toupper(A.back()));
			A.pop_back();
			C.pop_back();

			continue;
		}
	
		result = NAM;
		return result;
	}

	return result;
}
