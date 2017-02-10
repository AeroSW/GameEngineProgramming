#ifndef NAMEPARSE_H_
#define NAMEPARSE_H_

#include "TagParse.h"

struct name_parser: public tag_parser{
	std::string parse_tag(std::ifstream &file, std::string &line);
}

#endif