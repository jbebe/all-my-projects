#pragma once

//
// own headers
//

#include "parser.h"
#include "bf_utils.h"

//
// BFParser
// egy Parser implementacio ami a parse-olando szoveget 
// string-kent tarolja, es az IL kodot BFType tipuskent tarolja
//

namespace BF {

	class BFParser : public Parser<std::string, BF::BFILType> {
	public:

		BFParser(const char *);

		BFParser(std::string &);

		BFParser(std::ifstream &);

		//
		// parse
		// Ezt a fuggvenyt kell megvalositani ahhoz, 
		// hogy az implementacio feldolgozza a kodot
		// 

		void parse() override;

	};

}
