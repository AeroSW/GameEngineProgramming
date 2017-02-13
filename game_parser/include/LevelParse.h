#ifndef LEVELPARSE_H_
#define LEVELPARSE_H_

#include "TagParse.h"
#include <string>

struct lvl_parser : public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	// line should be the current line.
	// This means that when passed into this parser's function,
	// it should contain <level> and whatever comes after it.
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif