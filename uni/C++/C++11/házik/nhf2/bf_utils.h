#pragma once

//
// STL headers
//

#include <regex>
#include <string>

//
// own headers
//

#include "parser.h"

// ezt nem tudom hova kene rakni. egyszeru stl kiegeszites
std::string regexReplaceCallback(std::string &&, std::regex, std::function<std::string(std::string)>);

//
// Brainfuck namespace a bf specifikus valtozokert es fuggvenyekert
//

namespace BF {
	
	constexpr int TAPE_SIZE = 0xffff;

	enum ILCommands {
		ADD, SHIFT, LOOP_START, PRINT, INPUT, ZERO
	};

	struct BFILType : ILType<ILCommands> {
		int value;
		std::vector<BFILType> node;
		BFILType(ILCommands ct, int value = 0) : ILType{ct}, value{value}, node{} {}
	};
	
	static size_t depth = 0;

	void removeComments(std::string &);

	void cleanSemantic(std::string &);

	static std::string simplifySameOps(std::string);

	void checkSyntax(std::string &);
	
	void translateToIL(std::string, std::vector<BFILType> &);
	
	static void translateToILSub(std::sregex_iterator &, std::vector<BFILType> &);
	
	std::string translateToC(std::vector<BFILType> &);
	
	static std::string translateToCSub(std::ostringstream &, std::vector<BFILType> &, size_t);
	
	void optimizeIL(std::vector<BFILType> &);
	
}
