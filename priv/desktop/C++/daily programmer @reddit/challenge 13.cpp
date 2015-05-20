#include <iostream>
#include <string>
#include <algorithm>

int main(){
	std::string input;
	std::cout << "give me a string: ";
	std::getline(std::cin,input);
	char *string = new char[input.length()+1];
	std::strcpy (string, input.c_str());
	int size = sizeof(string)/sizeof(string[0]) - 1;
	std::sort(string, string+size);
	do std::cout << string << "\n";
		while(std::next_permutation(string, string+size));
	getchar();
	return 0;
}