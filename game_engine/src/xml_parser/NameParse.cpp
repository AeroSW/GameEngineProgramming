#include "NameParse.h"
#include "HelpFuncs.h"

std::string name_parser::beg_tag = "<name>";
std::string name_parser::end_tag = "</name>";
std::string name_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}