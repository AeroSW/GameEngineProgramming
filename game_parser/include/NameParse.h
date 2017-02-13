#ifndef NAMEPARSE_H_
#define NAMEPARSE_H_

#include "TagParse.h"

struct name_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif