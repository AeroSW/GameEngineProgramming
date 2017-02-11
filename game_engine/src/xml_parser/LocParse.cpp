#include "LocParse.h"
#include "HelpFuncs.h"

std::string loc_parser::beg_tag = "<loc>";
std::string loc_parser::end_tag = "</loc>";
std::string loc_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}