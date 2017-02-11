#ifndef TRANSFORMSPARSE_H_
#define TRANSFORMSPARSE_H_

#include "TagParse.h"

struct transforms_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	transforms_parser();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct trans_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	trans_parser();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct rotat_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	rotat_parser();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct scale_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	scale_parser();
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif