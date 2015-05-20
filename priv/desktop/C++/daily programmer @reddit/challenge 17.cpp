#include <iostream>
#include <regex>

int main(){
	std::string first = "Daily Programmer",
				second = "aeiou ";
	std::cout << std::regex_replace(first,std::regex("["+second+"]"),"");
	getchar();
	return 0;
}