#include <iostream>

char *caesar_encode(const char *input, unsigned char shift = 13){
	shift %= 26;
	unsigned short inputLength = strlen(input);
	char *output = (char *)malloc(sizeof(char) * inputLength + 1);
	for (unsigned char i = 0; i < inputLength; i++){
		if (input[i] > 64 && input[i] < 91)
			output[i] = ((input[i] - 'A' + shift) % 26) + 'A';
		else
			output[i] = input[i];
	}
	output[inputLength] = 0;
	return output;
}
char *caesar_decode(char *input, unsigned char shift){
	return caesar_encode(input,26 - (shift % 26));
}

int main(){
	char *string = "HELLO MY NAME IS BEBE";
	string = caesar_encode(string,25);
	std::cout << string << std::endl;
	string = caesar_decode(string,25);
	std::cout << string << std::endl;
	getchar();
	return 0;
}