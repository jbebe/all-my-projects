#include <iostream>
#include <regex>

int main(){
	std::string number;
	std::regex pattern("((\\(\\d{3}\\))|\\d{3})? ?(([\\.\\-\\ ]?\\d{3}){2}\\d)");
	for (;;){
		std::cout << "type telephone number: ";
		std::getline(std::cin,number);
		if (std::regex_match(number, pattern))
			std::cout << "SUCCESS\n";
		else 
			std::cout << "WRONG\n";
	}
	return 0;
}