#include "LevelParse.h"
#include "HelpFuncs.h"

std::string lvl_parser::beg_tag = "<level>";
std::string lvl_parser::end_tag = "</level>";
std::string lvl_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}