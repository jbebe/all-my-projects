#pragma once

#include <iostream>
#include <regex>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "bf_utils.h"

template <typename T>
std::string regexReplaceCallback(
	T &&input, 
	std::regex pattern, 
	std::function<std::string(std::string) > callback) 
{
	std::sregex_iterator matchIt{input.begin(), input.end(), pattern};
	std::sregex_iterator end;
	std::ostringstream resultBuffer;
	size_t inputOffset = 0;

	while (matchIt != end) {
		size_t matchPos = matchIt->position();
		size_t matchSize = matchIt->str().size();

		resultBuffer << input.substr(inputOffset, matchPos - inputOffset);
		resultBuffer << callback(matchIt->str());

		inputOffset = matchPos + matchSize;
		matchIt++;
	}

	resultBuffer << input.substr(inputOffset, input.size());

	return resultBuffer.str();
}

//
// Brainfuck namespace a bf specifikus valtozokert es fuggvenyekert
//

namespace BF {

	//
	// removeComments
	// eltunteti a nem-brainfuck utasitasokat a kodbol
	//
	
	void removeComments(std::string &input){
		std::regex notOpsPattern(R"([^\+\-\<\>\[\]\.\,]+)");
		
		input = std::regex_replace(input, notOpsPattern, "");
	}

	//
	// cleanSemantic
	// callback alapján hajt végre műveletet a stringen
	//
	
	void cleanSemantic(std::string &inputScript) {
		std::ostringstream cmdsBuffer;
		
		/* simplify same ops */
		std::regex pattern(R"([\+\-]+|[\<\>]+)");
		cmdsBuffer << regexReplaceCallback(inputScript, pattern, simplifySameOps);

		
		inputScript = cmdsBuffer.str();
	}

	//
	// simplifySameOps
	// eltunteti a redundans utasitasokat (pl. +- vagy <>)
	//
	
	std::string simplifySameOps(std::string input) {
		char a = input[0];
		auto diffIt = std::find_if(input.begin(), input.end(), [a](char c) {
			return c != a; 
		});
		char b = (diffIt != input.end()) ? *diffIt : a;

		if (b != a) {
			size_t aLen = std::count_if(input.begin(), input.end(), [a](char c) {
				return c == a; });
			size_t bLen = std::count_if(input.begin(), input.end(), [b](char c) {
				return c == b; });
			input.clear();
			if (aLen > bLen)
				input.insert(0, aLen - bLen, a);
			else
				input.insert(0, bLen - aLen, b);
		}

		return input;
	}
	
	//
	// translateToILSwitch
	// IL kodra forditas kozben itt kolonbozteti meg az utasitasokat 
	// és rakja a taroloba az IL peldanyt
	//
	
	void translateToILSwitch(std::sregex_iterator &matchIt, std::vector<BFILType> &ilData){
		const std::string &matchStr = (*matchIt).str();
		switch (matchStr[0]) {
		case '+':
			ilData.emplace_back(ADD, matchStr.size());
			//std::cout << "(ADD, " << matchStr.size() << ")" << std::endl;
			break;
		case '-':
			ilData.emplace_back(ADD, -matchStr.size());
			//std::cout << "(ADD, -" << matchStr.size() << ")" << std::endl;
			break;
		case '<':
			ilData.emplace_back(SHIFT, -matchStr.size());
			//std::cout << "(SHIFT, -" << matchStr.size() << ")" << std::endl;
			break;
		case '>':
			ilData.emplace_back(SHIFT, matchStr.size());
			//std::cout << "(SHIFT, " << matchStr.size() << ")" << std::endl;
			break;
		case '[':
			ilData.emplace_back(LOOP_START);
			//std::cout << "(LOOP_START)" << std::endl;
			++depth;
			translateToILSub(++matchIt, ilData.back().node);
			break;
		case '.':
			ilData.emplace_back(PRINT, matchStr.size());
			//std::cout << "(PRINT, " << matchStr.size() << ")" << std::endl;
			break;
		case ',':
			ilData.emplace_back(INPUT, matchStr.size());
			//std::cout << "(INPUT, " << matchStr.size() << ")" << std::endl;
			break;
		default: break;
		}
		matchIt++;
	}
	
	//
	// translateToILSub
	// IL kodra forditas kozben ez a rekurziv fuggveny hivodik meg
	// translateToIL helyett, ha egy loop-nal jar a fordito
	//
	
	void translateToILSub(std::sregex_iterator &matchIt, std::vector<BFILType> &ilData) {
		while ((*matchIt).str()[0] != ']') {
			//std::cout << std::setfill(' ') << std::setw(depth*4) << ' ';
			translateToILSwitch(matchIt, ilData);
		}
		--depth;
	}
	
	//
	// translateToIL
	// IL kodra forditast vegzi
	// minden operatorra "one or many" tipusu match van
	// igy tudjuk mennyi az ertekuk
	//

	void translateToIL(std::string parseable, std::vector<BFILType> &ilData) {
		std::regex pattern(R"([\+]+|[\-]+|[\<]+|[\>]+|\[|\]|[\.]+|[\,])");
		std::sregex_iterator matchIt{parseable.begin(), parseable.end(), pattern};
		std::sregex_iterator end;
		
		while (matchIt != end)
			translateToILSwitch(matchIt, ilData);
	}
	
	//
	// checkSyntax
	// ellenorzi a szintaxist es kivetelt dob ha valami nem valid
	//

	void checkSyntax(std::string &input) {
		size_t tape_position = TAPE_SIZE / 2;
		std::for_each(input.begin(), input.end(), [&tape_position](char c) {
			if (c == '<') tape_position--;
			else if (c == '>') tape_position++;
		});
		if (tape_position >= TAPE_SIZE)
			throw std::runtime_error("[error] code shifts out of tape size");

		size_t loopOpenCount = std::count(input.begin(), input.end(), '[');
		size_t loopCloseCount = std::count(input.begin(), input.end(), ']');
		if (loopOpenCount != loopCloseCount)
			throw std::runtime_error("[error] non-matching brackets");
		
		if (input.find("[]") != std::string::npos)
			throw std::runtime_error("[error] possible infinite loop or useless statement in code");
	}
	
	//
	// translateToCSub
	// az IL kodbol C kodra forditast rekurzivan vegzo fuggveny
	// (sok benne a hardcode-olt string, de nincs ertelme valtoztatni rajtuk)
	//
	
	std::string translateToCSub(std::ostringstream &os, std::vector<BFILType> &ilData, size_t depth){
		std::string padding;
		padding.insert(0, depth*4, ' ');
		for (auto it : ilData){
			switch (it.command){
				case ADD:
					os << padding << "*ptr += " << it.value << ";\n";
					break;
				case SHIFT:
					os << padding << "ptr += " << it.value << ";\n";
					break;
				case LOOP_START:
					os << padding << "while (*ptr != 0){" << "\n";
					translateToCSub(os, it.node, depth + 1);
					os << padding << "}\n";
					break;
				case ZERO:
					os << padding << "*ptr = 0;\n";
					break;
				case PRINT:
					for (int i = 0; i < it.value; i++)
						os << padding << "putchar(*ptr);\n";
					break;
				case INPUT:
					for (int i = 0; i < it.value; i++)
						os << padding << "*ptr = getchar();\n";
					break;
				default: break;
			}
		}
	}
	
	//
	// translateToC
	// az IL kodbol C kodra forditast vegzo fuggveny
	// csak a vazat adja meg a kodnak, utana atadja a vezerlest 
	// a translateToCSub fuggvenynek
	//
	
	std::string translateToC(std::vector<BFILType> &ilData){
		std::ostringstream buffer;
		buffer << "#include <stdio.h>\n\nint main(void){\n    char tape[0xffff];\n    char *ptr = tape + (0xffff/2);\n    /* generated code starts --> */\n";
		translateToCSub(buffer, ilData, 1);
		buffer << "    /* <-- generated code ends */\n    return 0;\n}\n";
		return buffer.str();
	}
	
	//
	// optimizeIL
	// atirja a lenullazo "[-]", "[+]" loop-okat ZERO tipusra
	//
	
	void optimizeIL(std::vector<BFILType> &ilData){
		for (BFILType &cmd : ilData){
			if (cmd.command == LOOP_START && 
				cmd.node.size() == 1 &&
				cmd.node[0].command == ADD
			){
				cmd.command = ZERO;
			}
		}
	}
}
