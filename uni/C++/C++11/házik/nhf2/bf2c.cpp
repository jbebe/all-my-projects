#include <iostream>

#include "bf_parser.h"

int main() {

	std::ifstream ifs{"mandelbrot.bf"};
	
	try {
		BF::BFParser bfp{ifs};
		bfp.parse();
	} catch (std::runtime_error &ex) {
		std::cout << ex.what() << std::endl;
	}
	
	ifs.close();
	
	return 0;
}
