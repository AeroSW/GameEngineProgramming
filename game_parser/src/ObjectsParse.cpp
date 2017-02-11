#include "ObjectsParse.h"
#include "HelpFuncs.h"

std::string objects_parser::beg_tag = "<objects>";
std::string objects_parser::end_tag = "</objects>";
std::string objects_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}