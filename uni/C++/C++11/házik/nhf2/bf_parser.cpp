#pragma once

//
// STL headers
//

#include <iostream>
#include <fstream>

//
// own headers
//

#include "bf_parser.h"

//
// BFParser implementacio
//

BF::BFParser::BFParser(const char *input) : Parser{input} {}

BF::BFParser::BFParser(std::string &input) : Parser{input} {}

BF::BFParser::BFParser(std::ifstream &file) : Parser{file} {}

//
// parse implementacio
//

void BF::BFParser::parse() {
	
	// kommentek eltavolitasa
	removeComments(parseable);
	
	// nyers kodban szintaktikai hibak keresese
	checkSyntax(parseable);
	
	// kodoptimalizacio
	cleanSemantic(parseable);
	
	// kod atalakitasa atmeneti nyelvve
	translateToIL(parseable, ilData);
	
	// IL optimalizacio
	optimizeIL(ilData);
	
	// ilData-ban levo IL kod atalakitasa C programma
	std::ofstream ofs{"bf.c"};
	//std::cout << BF::translateToC(ilData);
	ofs << translateToC(ilData);
	ofs.close();

	// forras lefuttatasa
	system("gcc bf.c -O3 -s -o bf.exe && bf.exe");
}