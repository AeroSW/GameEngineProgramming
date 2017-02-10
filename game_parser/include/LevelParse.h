#ifndef LEVELPARSE_H_
#define LEVELPARSE_H_

#include "TagParse.h"

struct lvl_parser : public tag_parser{
	// line should be the current line.
	// This means that when passed into this parser's function,
	// it should contain <level> and whatever comes after it.
	std::string parse_tag(std::ifstream &file, std::string &line);
}

#endif