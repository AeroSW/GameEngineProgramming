// Filename:	GameParser
// Author:	Kenneth Cornett
// Date:	Feb 26, 2017

#ifndef PARSERS_GAMEPARSER_H
#define PARSERS_GAMEPARSER_H

#include "Parser.h"

#include <vector>
#include <string>

class gameparser : public parser{
	private:
		const static std::string my_tag;
		const static std::string my_type;


	public:
		gameparser(const std::string &doc_name);
		virtual ~gameparser();
		
};

#endif
