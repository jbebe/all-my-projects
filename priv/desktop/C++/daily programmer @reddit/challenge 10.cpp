#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::string sort(std::string input){
	std::vector<char> chars;
	for (int i = 0; i < input.length(); i++)
		chars.push_back(input.at(i));
	std::sort(chars.begin(),chars.end());
	input = "";
	for (std::vector<char>::iterator it = chars.begin(); it != chars.end(); ++it)
		input += *it;
	return input;
}

int main(){
	std::string input;
	std::cout << "Input: ";
	std::getline(std::cin,input);
	std::cout << sort(input);
	getchar();
	return 0;
}