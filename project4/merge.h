#ifndef _MERGE_H
#define _MERGE_H

#include <vector>


#include <string>
#include <sstream>
#include <cctype>

//	Merge Match
//	Checks if 'merge' is a possible merge of two
//	given words, A and B.
//		Returns 
//			either the valid merged string of the two strings,
//			with the letters from A capitalized, ended with a 
//			newline char '\n'
//
//			or, if 'merge' is NOT VALID, returns the string
//			'*** NOT A MERGE ***\n'
std::string mergeMatch(std::string A, std::string B, std::string merge); 


#endif //_MERGE_H
