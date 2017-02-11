#ifndef OBJECTSPARSE_H_
#define OBJECTSPARSE_H_

#include "TagParse.h"

struct objects_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif