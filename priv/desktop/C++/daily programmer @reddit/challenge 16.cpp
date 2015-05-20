#include <iostream>
#include <fstream>
#include <string>

void printAligned(const char *location, const bool isright, const unsigned char width){
	std::ifstream file(location);
	std::string line;
	while (std::getline(file, line)){
		while (isright && line.length() < width - 1)
			line = " " + line;
		std::cout << line << std::endl;
	}
}

int main(){
	printAligned("text.txt",true,75);
	getchar();
	return 0;
}