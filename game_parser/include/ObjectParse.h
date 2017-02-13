#ifndef OBJECTPARSE_H_
#define OBJECTPARSE_H_

#include "TagParse.h"

struct object_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct mesh_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};
struct mat_parser: public tag_parser{
	static std::string beg_tag;
	static std::string end_tag;
	std::string get_beg_tag();
	std::string get_end_tag();
	std::string parse_tag(std::ifstream &file, std::string &line);
};

#endif