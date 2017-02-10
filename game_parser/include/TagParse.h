#ifndef TAGPARSE_H_
#define TAGPARSE_H_

#include <fstream>
#include <string>

struct tag_parser{
	virtual std::string parse_tag(std::ifstream &file, std::string &line) = 0;
};

#endif