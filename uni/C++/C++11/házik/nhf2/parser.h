#pragma once

//
// STL headers
//

#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

//
// Intermediate Language tipus
// command: (javallottan) enum tipusu szimbolum az adott utasitashoz
//

template <typename CMD_TYPE>
struct ILType {
	CMD_TYPE command;
	ILType(CMD_TYPE ct) : command{ct} {}
};

//
// Parser interfesz
// parseable az input (string) és ilData tarolja a vegleges IL kodot)
//

template <typename PARSETYPE, typename ILTYPE>
class Parser {
protected:
	PARSETYPE parseable;
	std::vector<ILTYPE> ilData;
public:

	//
	// ezek a konstruktorok csak kart okoznanak
	//

	Parser() = delete;
	Parser(const Parser &) = delete;
	Parser(Parser &&) = delete;

	//
	// karaktertomb alapu konstruktor (cast stringre)
	//

	Parser(const char *input) : parseable{input}, ilData{} {}

	Parser(std::string &input) : parseable{input} {}

	//
	// file alapu konstruktor (hivo kezeli az eroforrast)
	//

	Parser(std::ifstream &file) : ilData{} {
		if (file.fail())
			throw std::runtime_error("[error] unable to open script from file");
		parseable = std::string{std::istreambuf_iterator<char>
			{file}, std::istreambuf_iterator<char>
			{}};
	}

	//
	// parse fuggveny
	// implementalni kell, hogy mukodjon a parser
	//

	virtual void parse() = 0;

	virtual ~Parser() {}
	
};
