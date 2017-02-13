#ifndef COLORPARSE_H_
#define COLORPARSE_H_

#include "TagParse.h"

struct color_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif