#include <iostream>
#include <math.h>
int main(){
	long double pi = 0;
	std::cout.precision(30);
	std::cout << 4.0 * (4 * atan(1.0/5.0) - atan(1.0/239.0));
	getchar();
	return 0;
}