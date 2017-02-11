#include "LightsParse.h"
#include "HelpFuncs.h"

std::string lights_parser::beg_tag = "<lights>";
std::string lights_parser::end_tag = "</lights>";
std::string lights_parser::parse_tag(std::ifstream &file, std::string &line){
	return parse_by_tags(file, line, beg_tag, end_tag);
}