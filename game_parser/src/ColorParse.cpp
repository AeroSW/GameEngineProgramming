#include "ColorParse.h"
#include "HelpFuncs.h"

std::string color_parser::beg_tag = "<color>";
std::string color_parser::end_tag = "</color>";
std::string color_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}