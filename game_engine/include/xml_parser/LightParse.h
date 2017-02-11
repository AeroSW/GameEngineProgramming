#ifndef LIGHTPARSE_H_
#define LIGHTPARSE_H_

#include "TagParse.h"

struct light_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif