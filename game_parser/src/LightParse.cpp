#include "LightParse.h"
#include "HelpFuncs.h"

std::string light_parser::beg_tag = "<light>";
std::string light_parser::end_tag = "</light>";
std::string light_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}