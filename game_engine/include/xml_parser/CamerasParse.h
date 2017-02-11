#ifndef CAMERASPARSE_H_
#define CAMERASPARSE_H_

#include "TagParse.h"

struct cams_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif