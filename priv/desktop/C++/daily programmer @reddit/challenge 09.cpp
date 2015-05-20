#include <iostream>
#include <string>

int main(){
	int counter = 99;
	std::string lyrics = "";
	while (counter){
		lyrics += std::to_string(counter) + " bottle";
		if (counter != 1)
			lyrics += "s";
		lyrics += " of beer on the wall, ";
		lyrics += std::to_string(counter) + " bottle";
		if (counter != 1)
			lyrics += "s";
		lyrics += " of beer. Take one down and pass it around, ";
		if (counter-1 == 0)
			lyrics += "no more ";
		else 
			lyrics += std::to_string(counter-1) + " ";
		lyrics += "bottle";
		if (counter != 2)
			lyrics += "s";
		lyrics += " of beer on the wall. ";
		std::cout << lyrics;
		lyrics = "";
		counter--;
	}
	std::cout <<	" No more bottles of beer on the wall, no more bottles of beer."
					" Go to the store and buy some more, 99 bottles of beer on the wall. ";
	getchar();
	return 0;
}