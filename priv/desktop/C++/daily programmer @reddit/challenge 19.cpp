#include <iostream>
#include <string>

std::string shortcut2number(std::string input){
	char key[] = "22233344455566677778889999";
	for (int i = 0; i < input.length(); i++){
		if (input[i] >= 'A' && input[i] <= 'Z')
			input[i] = key[input[i]-'A'];
	}
	return input;
}

int main(){
	//1-800-COMCAST
	std::string input;
	std::getline(std::cin,input);
	std::cout << shortcut2number(input);
	getchar();
	return 0;
}