#include <iostream>
#include <string>

short dayOfYear(int year, int month, int day){
	unsigned char months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
	short output = 0;
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
		months[1] = 29;
	for (int i = 0; i < month - 1; i++)
		output += months[i];
	return output + day;
}

int main(){
	std::string y, m, d;
	std::cout << "Year: ";
	std::getline(std::cin,y);
	std::cout << "Month: ";
	std::getline(std::cin,m);
	std::cout << "Day: ";
	std::getline(std::cin,d);
	std::cout << dayOfYear(std::stoi(y),std::stoi(m),std::stoi(d));
	getchar();
	return 0;
}