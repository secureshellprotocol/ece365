#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

#include "merge.h"

int main(){
	
	std::string input_string;
	std::cout << "Enter name of input file: ";
	std::cin >> input_string;

	std::ifstream input(input_string);
	if(!input.is_open()){ 
		std::cerr << "Input cannot be accessed!" << std::endl;
		exit(1);
	}

	std::string output_string;
	std::cout << "Enter name of output file: "; 
	std::cin >> output_string;
	
	std::ofstream output(output_string);
	if(!output.is_open()){ 
		std::cerr << "Cannot create output file!" << std::endl;
		exit(1);
	}
	
	std::string A = "";
	std::string B = ""; 
	std::string mergeString = "";

	input >> A;
	input >> B;
	input >> mergeString;

	while(!input.fail() || !input.eof()){
		std::cout << A << '\n' << B << '\n' << mergeString << '\n';
		std::cout << mergeMatch(A, B, mergeString) << '\n';

		input >> A;
		input >> B;
		input >> mergeString;
	}

	//clean mess
	input.close();
	output.close();

	return 0;
}
