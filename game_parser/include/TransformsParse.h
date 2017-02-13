#ifndef TRANSFORMSPARSE_H_
#define TRANSFORMSPARSE_H_

#include "TagParse.h"

struct transforms_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct trans_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct rotat_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct scale_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif