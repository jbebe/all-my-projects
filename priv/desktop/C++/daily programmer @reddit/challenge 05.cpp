#include <time.h>
#include <iostream>
#include <string>

char *random_string(unsigned char length){
	char *random = (char *)malloc(sizeof(char) * length + 1);
	random[length] = 0;
	length--;
	do {
		random[length] = rand()%26 + 'a';
	} while (length--);
	return random;
}

int main(){
	srand(time(NULL));
	int	num_of_rnd, rnd_length;
	std::cout << "How much? [1-255] ";
	std::cin >> num_of_rnd;
	std::cout << "How long? [6-16] ";
	std::cin >> rnd_length;
	while (num_of_rnd--){
		std::cout << (int)num_of_rnd << " - " << random_string(rnd_length) << std::endl;
	}
	std::cin >> num_of_rnd;
	return 0;
}