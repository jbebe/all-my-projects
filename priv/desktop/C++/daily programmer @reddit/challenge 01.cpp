#include <iostream>

unsigned char digitalroot(unsigned long number){
	unsigned char output = 0;
	while (number){
		output += number%10;
		number /= 10;
	}
	return output > 9 ? digitalroot(output) : output;
}

int main(){
	unsigned long num;
	std::cout << "Gimme nombre: ";
	std::cin >> num;
	std::cout << (int)digitalroot(num);
	std::cin >> num;
	return 0;
}