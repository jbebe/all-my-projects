#include <iostream>
#include <string>

std::string triangle(int height, int length = 1){
	int temp_length = length;
	std::string output = "";
	while (temp_length--) 
		output += "@";
	output += "\n";
	if (--height == 0) return output;
	return output + triangle(height, length + 1);
}

int main(){
	std::cout << triangle(5);

	getchar();
	return 0;
}