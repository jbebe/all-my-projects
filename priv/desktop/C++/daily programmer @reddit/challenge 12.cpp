#include <iostream>
#include <string>
#include <array>

std::string dayOfWeek(int y, int m, int d){
	std::array<std::string,7> sDay = {
		"Saturday",
		"Sunday",
		"Monday",
		"Tuesday",
		"Wednesday",
		"Thursday",
		"Friday"
	};
	if (m < 3) {
	    m += 12;
	    --y;
	}
	int C = y % 100,
		D = y / 100,
		W = 13 * (m + 1) / 5,
		X = C / 4,
		Y = D / 4,
		Z = W + X + Y + d + C - (2 * D),
		day = Z % 7;
	if (day < 0)
	    day += 7;
	return sDay.at(day);
}

int main(){
	std::cout << "2013-06-29: " << dayOfWeek(2013,6,29);
	getchar();
	return 0;
}